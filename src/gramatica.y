%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla_simbolos.h"
#include "acciones_semanticas.h"
#include "polaca.h"
#include "errores.h"

extern int yylex(void);
extern int yylineno;
int cant_errores = 0;
void yyerror(const char *s);

/* Arreglo temporal para acumular variables en declaraciones múltiples */
static Simbolo *lista_vars_declaradas[64];
static int cant_vars_declaradas = 0;

/* Contexto para Tema 14 (FROM - REPEAT) */
typedef struct {
    Simbolo *id_control;
    long cte1_val;
    long cte2_val;
    long cte3_val;
    Simbolo *cte1_sym;
    Simbolo *cte2_sym;
    Simbolo *cte3_sym;
    bool ascendente;
    int pos_inicio_prueba;
    int celda_bf;
} ContextoFrom;

static ContextoFrom pila_from[32];
static int tope_from = 0;

static long parsear_valor_entero(const char *lexema) {
    if (!lexema) return 0;
    char buf[64];
    strncpy(buf, lexema, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    char *d = strchr(buf, '$');
    if (d) *d = '\0';
    char *endptr;
    return strtol(buf, &endptr, 10);
}

/* Pila de funciones en declaración para asociar parámetros formales */
static Simbolo *pila_fn_decl[32];
static int tope_fn_decl = 0;

/* Estructura para Tema 19: Orden de evaluación obligatorio de parámetros */
typedef struct {
    Simbolo *fn_simbolo;
    char *nombre_fn;
    Polaca *args_polaca[16];
    bool args_comptime[16];
    int cant_args;
    int orden[16];
    int cant_orden;
    int linea;
} Invocacion;

static Invocacion pila_invocaciones[16];
static int tope_invocaciones = 0;

static void iniciar_invocacion(const char *nombre_fn, int linea) {
    if (tope_invocaciones < 16) {
        Invocacion *inv = &pila_invocaciones[tope_invocaciones++];
        inv->nombre_fn = strdup(nombre_fn ? nombre_fn : "");
        inv->fn_simbolo = buscar_identificador_semantico(obtener_tabla_simbolos(), nombre_fn);
        inv->cant_args = 0;
        inv->cant_orden = 0;
        inv->linea = linea;
    }
}

static void agregar_orden_invocacion(int val) {
    if (tope_invocaciones > 0) {
        Invocacion *inv = &pila_invocaciones[tope_invocaciones - 1];
        if (inv->cant_orden < 16) {
            inv->orden[inv->cant_orden++] = val;
        }
    }
}

static void finalizar_invocacion_con_orden(void) {
    if (tope_invocaciones <= 0) return;
    Invocacion inv = pila_invocaciones[--tope_invocaciones];
    Simbolo *fn = inv.fn_simbolo;

    if (!fn) {
        registrar_error(
            ETAPA_SEMANTICO,
            inv.linea,
            "Función o método '%s' no declarado o fuera de alcance.",
            inv.nombre_fn ? inv.nombre_fn : "?"
        );
    } else {
        if (inv.cant_orden != fn->cant_parametros) {
            registrar_error(
                ETAPA_SEMANTICO,
                inv.linea,
                "El número de valores en el orden de evaluación (%d) no coincide con la cantidad de parámetros formales (%d) de '%s'.",
                inv.cant_orden,
                fn->cant_parametros,
                inv.nombre_fn
            );
        }
        if (inv.cant_args != fn->cant_parametros) {
            registrar_error(
                ETAPA_SEMANTICO,
                inv.linea,
                "Cantidad de parámetros reales (%d) no coincide con los parámetros formales (%d) de '%s'.",
                inv.cant_args,
                fn->cant_parametros,
                inv.nombre_fn
            );
        }
    }

    // Copiar los parámetros a los formales en el orden indicado:
    for (int k = 0; k < inv.cant_orden; k++) {
        int idx = inv.orden[k] - 1; // 1-based a 0-based
        if (idx < 0 || (fn && idx >= fn->cant_parametros)) {
            registrar_error(
                ETAPA_SEMANTICO,
                inv.linea,
                "Índice de orden de evaluación %d fuera de rango [1..%d] en llamada a '%s'.",
                inv.orden[k],
                fn ? fn->cant_parametros : inv.cant_args,
                inv.nombre_fn
            );
            continue;
        }

        Simbolo *s_formal = NULL;
        if (fn != NULL) {
            ParametroFormal *pf = fn->parametros;
            for (int p = 0; p < idx && pf != NULL; p++) {
                pf = pf->siguiente;
            }
            if (pf != NULL) {
                // Chequeo Tema 22: si el parámetro formal es COMPTIME, el argumento real debe ser comptime
                if (pf->es_comptime) {
                    if (idx < inv.cant_args && !inv.args_comptime[idx]) {
                        registrar_error(
                            ETAPA_SEMANTICO,
                            inv.linea,
                            "El parámetro formal '%s' de '%s' es COMPTIME y no puede recibir una expresión no determinable en tiempo de compilación.",
                            pf->nombre,
                            inv.nombre_fn
                        );
                    }
                }

                char ambito_fn[256];
                snprintf(ambito_fn, sizeof(ambito_fn), "%s:%s",
                         fn->ambito ? fn->ambito : "main",
                         fn->nombre_original ? fn->nombre_original : fn->lexema);
                char *mangled_p = construir_mangled_name(pf->nombre, ambito_fn);
                s_formal = buscar_simbolo(obtener_tabla_simbolos(), mangled_p);
                free(mangled_p);
            }
        }

        // 1. Emitir destino (parámetro formal)
        if (s_formal != NULL) {
            polaca_emitir_simbolo(s_formal, inv.linea);
        }

        // 2. Emitir valor del parámetro real correspondiente
        if (idx < inv.cant_args && inv.args_polaca[idx] != NULL) {
            Polaca *p_arg = inv.args_polaca[idx];
            for (int e = 0; e < p_arg->tam; e++) {
                if (p_arg->elementos[e].tipo == POLACA_TIPO_SIMBOLO) {
                    polaca_emitir_simbolo(p_arg->elementos[e].simbolo, p_arg->elementos[e].linea);
                } else if (p_arg->elementos[e].tipo == POLACA_TIPO_OPERADOR) {
                    polaca_emitir_operador(p_arg->elementos[e].operador, p_arg->elementos[e].linea);
                } else if (p_arg->elementos[e].tipo == POLACA_TIPO_DESTINO) {
                    int c = polaca_emitir_celda_vacia(p_arg->elementos[e].linea);
                    polaca_poner_destino(c, p_arg->elementos[e].celda_destino);
                }
            }
        }

        // 3. Emitir asignación :=
        if (s_formal != NULL) {
            polaca_emitir_operador(":=", inv.linea);
        }
    }

    // 4. Emitir llamado CALL
    if (fn != NULL) {
        polaca_emitir_simbolo(fn, inv.linea);
    }
    polaca_emitir_operador("CALL", inv.linea);

    if (inv.nombre_fn) free(inv.nombre_fn);
}

/* Estado para Tema 24: Clases con código */
static Simbolo *clase_actual_declaracion = NULL;
%}

%union {
    struct Simbolo *simbolo;
    int val_int;
    int tipo_dato;
    const char *cadena;
    InfoExpr info_expr;
}

%token <simbolo> ID CTE CTE_FLOAT MULT_STRING

%token ASSIGN GE LE EQ NE
%token OUT_OF_RANGE ERROR_LEXICO

%token IF ELSE END_IF BEGIN END POUT RET CLASS FUNCTION INTEGER SINGLEF
%token FROM TO BY REPEAT COMPTIME TOSF EXTENDS

%type <tipo_dato> tipo_dato
%type <cadena> operador_relacional
%type <simbolo> constante_con_signo destino_asignacion
%type <info_expr> expresion_aritmetica termino operando operando_base parametro_real

%%

programa:
    ID bloque_declarativo bloque_ejecutable ';'
    {
        // Programa finalizado correctamente
    }
  | ID bloque_declarativo bloque_ejecutable 
    { yyerror("Error: Falta el delimitador ; al final del bloque ejecutable."); yyerrok; }
  | ID bloque_declarativo BEGIN lista_ejecutables
    { yyerror("Error: Falta el delimitador END al final del bloque ejecutable."); yyerrok; }
  | bloque_declarativo bloque_ejecutable ';'
    { yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
;

bloque_declarativo:
    lista_declaraciones
  |
;

lista_declaraciones:
    lista_declaraciones declaracion
  | declaracion
;

declaracion:
    declaracion_variable ';'
  | declaracion_funcion ';'
  | declaracion_clase ';'
  | declaracion_objeto ';'
  | declaracion_comptime ';'
;

declaracion_comptime:
    COMPTIME tipo_dato lista_variables
    {
        for (int i = 0; i < cant_vars_declaradas; i++) {
            declarar_identificador(
                obtener_tabla_simbolos(),
                lista_vars_declaradas[i]->lexema,
                ID,
                $2,
                USO_VARIABLE_COMPTIME,
                yylineno
            );
        }
        cant_vars_declaradas = 0;
    }
  | COMPTIME lista_variables
    { yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
;

tipo_dato:
    INTEGER { $$ = TIPO_INTEGER; }
  | SINGLEF { $$ = TIPO_SINGLEF; }
;

declaracion_variable:
    tipo_dato lista_variables
    {
        for (int i = 0; i < cant_vars_declaradas; i++) {
            declarar_identificador(
                obtener_tabla_simbolos(),
                lista_vars_declaradas[i]->lexema,
                ID,
                $1,
                USO_VARIABLE,
                yylineno
            );
            if (clase_actual_declaracion != NULL) {
                AtributoClase *at = calloc(1, sizeof(AtributoClase));
                at->nombre = strdup(lista_vars_declaradas[i]->lexema);
                at->tipo = $1;
                at->siguiente = NULL;
                if (clase_actual_declaracion->atributos == NULL) {
                    clase_actual_declaracion->atributos = at;
                } else {
                    AtributoClase *curr = clase_actual_declaracion->atributos;
                    while (curr->siguiente != NULL) curr = curr->siguiente;
                    curr->siguiente = at;
                }
                clase_actual_declaracion->cant_atributos++;
            }
        }
        cant_vars_declaradas = 0;
    }
;

lista_variables:
    lista_variables ',' ID
    {
        if (cant_vars_declaradas < 64) {
            lista_vars_declaradas[cant_vars_declaradas++] = $3;
        }
    }
  | ID
    {
        cant_vars_declaradas = 0;
        if (cant_vars_declaradas < 64) {
            lista_vars_declaradas[cant_vars_declaradas++] = $1;
        }
    }
;

declaracion_objeto:
    ID lista_variables
    {
        for (int i = 0; i < cant_vars_declaradas; i++) {
            Simbolo *obj = declarar_identificador(
                obtener_tabla_simbolos(),
                lista_vars_declaradas[i]->lexema,
                ID,
                TIPO_CLASE,
                USO_OBJETO,
                yylineno
            );
            if (obj && $1) {
                obj->tipo_clase = strdup($1->lexema);
            }
        }
        cant_vars_declaradas = 0;
    }
;

declaracion_funcion:
    encabezado_funcion lista_parametros ')' bloque_declarativo bloque_ejecutable
    {
        if (tope_fn_decl > 0) tope_fn_decl--;
        polaca_desapilar_actual();
        salir_ambito();
    }
  | encabezado_funcion_sin_kw lista_parametros ')' bloque_ejecutable
    {
        if (tope_fn_decl > 0) tope_fn_decl--;
        polaca_desapilar_actual();
        salir_ambito();
    }
  | tipo_dato FUNCTION error '(' lista_parametros ')' bloque_declarativo bloque_ejecutable
    { yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
  | tipo_dato FUNCTION ID '(' ')' bloque_declarativo bloque_ejecutable
    { yyerror("Error: Faltan los parametros de la función."); yyerrok; }
;

encabezado_funcion:
    tipo_dato FUNCTION ID '('
    {
        Simbolo *fn = declarar_identificador(
            obtener_tabla_simbolos(),
            $3->lexema,
            ID,
            $1,
            USO_FUNCION,
            yylineno
        );
        if (fn && tope_fn_decl < 32) {
            pila_fn_decl[tope_fn_decl++] = fn;
        }
        entrar_ambito($3->lexema);
        char *mangled = construir_mangled_name($3->lexema, obtener_ambito_actual());
        Polaca *pf = crear_polaca(mangled);
        free(mangled);
        polaca_apilar_actual(pf);
    }
;

encabezado_funcion_sin_kw:
    tipo_dato ID '('
    {
        Simbolo *fn = declarar_identificador(
            obtener_tabla_simbolos(),
            $2->lexema,
            ID,
            $1,
            USO_FUNCION,
            yylineno
        );
        if (fn && tope_fn_decl < 32) {
            pila_fn_decl[tope_fn_decl++] = fn;
        }
        entrar_ambito($2->lexema);
        char *mangled = construir_mangled_name($2->lexema, obtener_ambito_actual());
        Polaca *pf = crear_polaca(mangled);
        free(mangled);
        polaca_apilar_actual(pf);
    }
;

lista_parametros:
    lista_parametros ',' parametro
  | lista_parametros parametro
    { yyerror("Error: Falta de ',' en declaración de parámetros."); yyerrok; }
  | parametro
;

parametro:
    tipo_dato ID
    {
        declarar_identificador(
            obtener_tabla_simbolos(),
            $2->lexema,
            ID,
            $1,
            USO_PARAMETRO,
            yylineno
        );
        if (tope_fn_decl > 0 && pila_fn_decl[tope_fn_decl - 1] != NULL) {
            Simbolo *fn = pila_fn_decl[tope_fn_decl - 1];
            ParametroFormal *pf = calloc(1, sizeof(ParametroFormal));
            pf->nombre = strdup($2->lexema);
            pf->tipo = $1;
            pf->siguiente = NULL;
            if (fn->parametros == NULL) {
                fn->parametros = pf;
            } else {
                ParametroFormal *curr = fn->parametros;
                while (curr->siguiente != NULL) curr = curr->siguiente;
                curr->siguiente = pf;
            }
            fn->cant_parametros++;
        }
    }
  | COMPTIME tipo_dato ID
    {
        Simbolo *p_sym = declarar_identificador(
            obtener_tabla_simbolos(),
            $3->lexema,
            ID,
            $2,
            USO_VARIABLE_COMPTIME,
            yylineno
        );
        if (p_sym != NULL) {
            p_sym->valor_comptime_valido = true;
        }
        if (tope_fn_decl > 0 && pila_fn_decl[tope_fn_decl - 1] != NULL) {
            Simbolo *fn = pila_fn_decl[tope_fn_decl - 1];
            ParametroFormal *pf = calloc(1, sizeof(ParametroFormal));
            pf->nombre = strdup($3->lexema);
            pf->tipo = $2;
            pf->es_comptime = true;
            pf->siguiente = NULL;
            if (fn->parametros == NULL) {
                fn->parametros = pf;
            } else {
                ParametroFormal *curr = fn->parametros;
                while (curr->siguiente != NULL) curr = curr->siguiente;
                curr->siguiente = pf;
            }
            fn->cant_parametros++;
        }
    }
  | tipo_dato
    { yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
;

declaracion_clase:
    CLASS ID {
        Simbolo *cls = declarar_identificador(
            obtener_tabla_simbolos(),
            $2->lexema,
            CLASS,
            TIPO_CLASE,
            USO_CLASE,
            yylineno
        );
        clase_actual_declaracion = cls;
        entrar_ambito($2->lexema);
    } codigo_clase encabezado_clase miembros_clase END
    {
        if (clase_actual_declaracion && clase_actual_declaracion->codigo_clase) {
            TablaSimbolos *ts = obtener_tabla_simbolos();
            for (int i = 0; i < TAM_TABLA; i++) {
                for (Simbolo *curr = ts->entradas[i]; curr != NULL; curr = curr->siguiente) {
                    if (curr->uso == USO_CLASE && curr != clase_actual_declaracion && curr->codigo_clase != NULL) {
                        if (strcmp(curr->codigo_clase, clase_actual_declaracion->codigo_clase) == 0) {
                            if (!clases_tienen_misma_estructura(curr, clase_actual_declaracion)) {
                                registrar_error(
                                    ETAPA_SEMANTICO,
                                    yylineno,
                                    "La clase '%s' tiene el mismo código '%s' que la clase '%s', pero sus estructuras no son compatibles.",
                                    clase_actual_declaracion->nombre_original ? clase_actual_declaracion->nombre_original : clase_actual_declaracion->lexema,
                                    clase_actual_declaracion->codigo_clase,
                                    curr->nombre_original ? curr->nombre_original : curr->lexema
                                );
                            }
                        }
                    }
                }
            }
        }
        clase_actual_declaracion = NULL;
        salir_ambito();
    }
;

codigo_clase:
    ID
    {
        if (clase_actual_declaracion != NULL) {
            clase_actual_declaracion->codigo_clase = strdup($1->lexema);
        }
    }
  | { yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
;

lista_clase:
    lista_clase ',' ID
  | ID
;

encabezado_clase:
    BEGIN
  | EXTENDS lista_clase BEGIN
  | EXTENDS BEGIN
    { yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
;

miembros_clase:
    miembros_clase miembro
  | miembro
;

miembro:
    declaracion_variable ';'
  | declaracion_funcion ';'
;

bloque_ejecutable:
    BEGIN lista_ejecutables END
  | error lista_ejecutables END 
    { yyerror("Error: Falta de delimitador de sentencias ejecutables BEGIN."); yyerrok; }
;

lista_ejecutables:
    lista_ejecutables sentencia ';'
  | sentencia ';'
  | lista_ejecutables error ';'
    { yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
  | error ';'
    { yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
;

sentencia:
    asignacion
  | if_sentencia
  | iteracion
  | impresion
  | sentencia_retorno
;

sentencia_retorno:
    RET '(' expresion_aritmetica ')'
    {
        polaca_emitir_operador("RET", yylineno);
    }
  | RET '(' ')'
    {
        polaca_emitir_operador("RET", yylineno);
    }
;

asignacion:
    destino_asignacion ASSIGN expresion_aritmetica
    {
        Simbolo *dest = $1;
        if (dest != NULL) {
            // Tema 22: Asignación a variable COMPTIME
            if (dest->uso == USO_VARIABLE_COMPTIME) {
                if (!$3.es_comptime) {
                    registrar_error(
                        ETAPA_SEMANTICO,
                        yylineno,
                        "No se puede asignar una expresión no determinable en tiempo de compilación a la variable COMPTIME '%s'.",
                        dest->nombre_original ? dest->nombre_original : dest->lexema
                    );
                } else {
                    dest->valor_comptime_valido = true;
                    dest->valor_int = $3.val_int;
                    dest->valor_float = $3.val_float;
                }
            }

            // Tema 24: Asignación por estructura en objetos con código
            if (dest->uso == USO_OBJETO) {
                Simbolo *orig = $3.simbolo_ref;
                if (orig != NULL && orig->uso == USO_OBJETO) {
                    if (dest->tipo_clase && orig->tipo_clase) {
                        if (strcmp(dest->tipo_clase, orig->tipo_clase) != 0) {
                            Simbolo *cls_dest = buscar_identificador_semantico(obtener_tabla_simbolos(), dest->tipo_clase);
                            Simbolo *cls_orig = buscar_identificador_semantico(obtener_tabla_simbolos(), orig->tipo_clase);
                            if (!cls_dest || !cls_orig || !cls_dest->codigo_clase || !cls_orig->codigo_clase ||
                                strcmp(cls_dest->codigo_clase, cls_orig->codigo_clase) != 0) {
                                registrar_error(
                                    ETAPA_SEMANTICO,
                                    yylineno,
                                    "Asignación no permitida: el objeto '%s' (clase '%s') y el objeto '%s' (clase '%s') no poseen el mismo código de clase.",
                                    dest->nombre_original ? dest->nombre_original : dest->lexema,
                                    dest->tipo_clase,
                                    orig->nombre_original ? orig->nombre_original : orig->lexema,
                                    orig->tipo_clase
                                );
                            }
                        }
                    }
                }
            }
        }
        polaca_emitir_operador(":=", yylineno);
    }
  | destino_asignacion '=' expresion_aritmetica
    { yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
;

destino_asignacion:
    ID
    {
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), $1->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", $1->lexema);
            s = $1;
        }
        polaca_emitir_simbolo(s, yylineno);
        $$ = s;
    }
  | ID '.' ID
    {
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), $1->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Objeto '%s' no declarado o fuera de alcance.", $1->lexema);
            s = $1;
        }
        polaca_emitir_simbolo(s, yylineno);
        polaca_emitir_operador($3->lexema, yylineno);
        polaca_emitir_operador(".", yylineno);
        $$ = s;
    }
  | ID '[' expresion_aritmetica ']'
    {
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), $1->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", $1->lexema);
            s = $1;
        }
        polaca_emitir_simbolo(s, yylineno);
        polaca_emitir_operador("[]", yylineno);
        $$ = s;
    }
;

impresion:
    POUT '(' expresion_aritmetica ')'
    {
        polaca_emitir_operador("POUT", yylineno);
    }
  | POUT '(' MULT_STRING ')'
    {
        polaca_emitir_simbolo($3, yylineno);
        polaca_emitir_operador("POUT", yylineno);
    }
  | POUT '(' ')'
    { yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
  | POUT error
    { yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
;

expresion_aritmetica:
    expresion_aritmetica '+' termino
    {
        polaca_emitir_operador("+", yylineno);
        $$.simbolo_ref = NULL;
        $$.tipo = ($1.tipo == TIPO_SINGLEF || $3.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
        if ($1.es_comptime && $3.es_comptime) {
            $$.es_comptime = true;
            if ($$.tipo == TIPO_INTEGER) {
                $$.val_int = $1.val_int + $3.val_int;
                $$.val_float = (double)$$.val_int;
            } else {
                $$.val_float = $1.val_float + $3.val_float;
                $$.val_int = (long)$$.val_float;
            }
        } else {
            $$.es_comptime = false;
        }
    }
  | expresion_aritmetica '-' termino
    {
        polaca_emitir_operador("-", yylineno);
        $$.simbolo_ref = NULL;
        $$.tipo = ($1.tipo == TIPO_SINGLEF || $3.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
        if ($1.es_comptime && $3.es_comptime) {
            $$.es_comptime = true;
            if ($$.tipo == TIPO_INTEGER) {
                $$.val_int = $1.val_int - $3.val_int;
                $$.val_float = (double)$$.val_int;
            } else {
                $$.val_float = $1.val_float - $3.val_float;
                $$.val_int = (long)$$.val_float;
            }
        } else {
            $$.es_comptime = false;
        }
    }
  | expresion_aritmetica '+' error 
    { yyerror("Error: Falta operando en la expresión después de '+'."); yyerrok; $$.es_comptime = false; }
  | expresion_aritmetica '-' error 
    { yyerror("Error: Falta operando en la expresión después de '-'."); yyerrok; $$.es_comptime = false; }
  | termino
    {
        $$ = $1;
    }
;

termino:
    termino '*' operando
    {
        polaca_emitir_operador("*", yylineno);
        $$.simbolo_ref = NULL;
        $$.tipo = ($1.tipo == TIPO_SINGLEF || $3.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
        if ($1.es_comptime && $3.es_comptime) {
            $$.es_comptime = true;
            if ($$.tipo == TIPO_INTEGER) {
                $$.val_int = $1.val_int * $3.val_int;
                $$.val_float = (double)$$.val_int;
            } else {
                $$.val_float = $1.val_float * $3.val_float;
                $$.val_int = (long)$$.val_float;
            }
        } else {
            $$.es_comptime = false;
        }
    }
  | termino '/' operando
    {
        polaca_emitir_operador("/", yylineno);
        $$.simbolo_ref = NULL;
        $$.tipo = ($1.tipo == TIPO_SINGLEF || $3.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
        if ($1.es_comptime && $3.es_comptime) {
            if (($$.tipo == TIPO_INTEGER && $3.val_int == 0) || ($$.tipo == TIPO_SINGLEF && $3.val_float == 0.0)) {
                registrar_error(ETAPA_SEMANTICO, yylineno, "División por cero en evaluación de expresión COMPTIME.");
                $$.es_comptime = false;
            } else {
                $$.es_comptime = true;
                if ($$.tipo == TIPO_INTEGER) {
                    $$.val_int = $1.val_int / $3.val_int;
                    $$.val_float = (double)$$.val_int;
                } else {
                    $$.val_float = $1.val_float / $3.val_float;
                    $$.val_int = (long)$$.val_float;
                }
            }
        } else {
            $$.es_comptime = false;
        }
    }
  | termino '*' error 
    { yyerror("Error: Falta operando en la expresión después de '*'."); yyerrok; $$.es_comptime = false; }
  | termino '/' error 
    { yyerror("Error: Falta operando en la expresión después de '/'."); yyerrok; $$.es_comptime = false; }
  | operando
    {
        $$ = $1;
    }
;

expresion_sin_asignacion:
    expresion_sin_asignacion '+' termino_sin_asignacion
    {
        polaca_emitir_operador("+", yylineno);
    }
  | expresion_sin_asignacion '-' termino_sin_asignacion
    {
        polaca_emitir_operador("-", yylineno);
    }
  | termino_sin_asignacion
;

termino_sin_asignacion:
    termino_sin_asignacion '*' operando_base
    {
        polaca_emitir_operador("*", yylineno);
    }
  | termino_sin_asignacion '/' operando_base
    {
        polaca_emitir_operador("/", yylineno);
    }
  | operando_base
;

operando:
    operando_base
    {
        $$ = $1;
    }
  | ID '=' {
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), $1->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", $1->lexema);
            s = $1;
        }
        polaca_emitir_simbolo(s, yylineno);
    } '(' expresion_sin_asignacion ')'
    {
        polaca_emitir_operador(":=", yylineno);
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), $1->lexema);
        polaca_emitir_simbolo(s ? s : $1, yylineno);
        $$.es_comptime = false;
        $$.simbolo_ref = s;
        $$.tipo = s ? s->tipo : TIPO_NO_ASIGNADO;
    }
;

operando_base:
    ID
    {
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), $1->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", $1->lexema);
            s = $1;
        }
        $$.simbolo_ref = s;
        $$.tipo = s ? s->tipo : TIPO_NO_ASIGNADO;
        if (s != NULL && s->uso == USO_VARIABLE_COMPTIME) {
            if (!s->valor_comptime_valido) {
                registrar_error(ETAPA_SEMANTICO, yylineno, "La variable COMPTIME '%s' se utiliza antes de haber sido inicializada.", $1->lexema);
                $$.es_comptime = false;
            } else {
                $$.es_comptime = true;
                $$.val_int = s->valor_int;
                $$.val_float = s->valor_float;
            }
        } else {
            $$.es_comptime = false;
        }
        polaca_emitir_simbolo(s, yylineno);
    }
  | ID '.' ID
    {
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), $1->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Objeto '%s' no declarado o fuera de alcance.", $1->lexema);
            s = $1;
        }
        polaca_emitir_simbolo(s, yylineno);
        polaca_emitir_operador($3->lexema, yylineno);
        polaca_emitir_operador(".", yylineno);
        $$.es_comptime = false;
        $$.simbolo_ref = s;
        $$.tipo = TIPO_NO_ASIGNADO;
    }
  | ID '[' expresion_aritmetica ']'
    {
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), $1->lexema);
        polaca_emitir_simbolo(s ? s : $1, yylineno);
        polaca_emitir_operador("[]", yylineno);
        $$.es_comptime = false;
        $$.simbolo_ref = s;
        $$.tipo = s ? s->tipo : TIPO_NO_ASIGNADO;
    }
  | llamada_con_orden
    {
        $$.es_comptime = false;
        $$.simbolo_ref = NULL;
        $$.tipo = TIPO_NO_ASIGNADO;
    }
  | llamada_metodo_con_orden
    {
        $$.es_comptime = false;
        $$.simbolo_ref = NULL;
        $$.tipo = TIPO_NO_ASIGNADO;
    }
  | TOSF '(' expresion_aritmetica ')'
    {
        polaca_emitir_operador("TOSF", yylineno);
        $$.es_comptime = $3.es_comptime;
        $$.tipo = TIPO_SINGLEF;
        $$.val_float = $3.es_comptime ? (double)$3.val_int : 0.0;
        $$.val_int = (long)$$.val_float;
        $$.simbolo_ref = NULL;
    }
  | constante_con_signo
    {
        if ($1 != NULL) {
            polaca_emitir_simbolo($1, yylineno);
            $$.es_comptime = true;
            $$.simbolo_ref = $1;
            $$.tipo = $1->tipo;
            if ($1->tipo == TIPO_INTEGER) {
                $$.val_int = parsear_valor_entero($1->lexema);
                $$.val_float = (double)$$.val_int;
            } else {
                $$.val_float = atof($1->lexema);
                $$.val_int = (long)$$.val_float;
            }
        } else {
            $$.es_comptime = false;
            $$.simbolo_ref = NULL;
            $$.tipo = TIPO_NO_ASIGNADO;
        }
    }
;

llamada_con_orden:
    llamada_encabezado parametros_reales ')' orden_evaluacion
    {
        finalizar_invocacion_con_orden();
    }
  | llamada_encabezado parametros_reales ')'
    { yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
;

llamada_encabezado:
    ID '('
    {
        iniciar_invocacion($1->lexema, yylineno);
    }
;

llamada_metodo_con_orden:
    llamada_metodo_encabezado parametros_reales ')' orden_evaluacion
    {
        finalizar_invocacion_con_orden();
    }
  | llamada_metodo_encabezado parametros_reales ')'
    { yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
;

llamada_metodo_encabezado:
    ID '.' ID '('
    {
        iniciar_invocacion($3->lexema, yylineno);
    }
;

orden_evaluacion:
    '[' lista_enteros ']'
  | '[' error ']'
    { yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
;

lista_enteros:
    lista_enteros ',' CTE
    {
        long val = parsear_valor_entero($3 ? $3->lexema : "0");
        agregar_orden_invocacion((int)val);
    }
  | lista_enteros ',' constante_invalida
  | CTE
    {
        long val = parsear_valor_entero($1 ? $1->lexema : "0");
        agregar_orden_invocacion((int)val);
    }
  | constante_invalida
;

parametros_reales:
    lista_parametros_reales
;

lista_parametros_reales:
    lista_parametros_reales ',' parametro_real_item
  | parametro_real_item
;

parametro_real_item:
    iniciar_parametro parametro_real
    {
        if (tope_invocaciones > 0) {
            Invocacion *inv = &pila_invocaciones[tope_invocaciones - 1];
            Polaca *p = obtener_polaca_actual();
            polaca_desapilar_actual();
            if (inv->cant_args < 16) {
                inv->args_polaca[inv->cant_args] = p;
                inv->args_comptime[inv->cant_args] = $2.es_comptime;
                inv->cant_args++;
            }
        }
    }
;

iniciar_parametro:
    /* empty */
    {
        Polaca *p = crear_polaca("param_tmp");
        polaca_apilar_actual(p);
    }
;

parametro_real:
    expresion_aritmetica
    {
        $$ = $1;
    }
  | ID '=' {
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), $1->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", $1->lexema);
            s = $1;
        }
        polaca_emitir_simbolo(s, yylineno);
    } expresion_aritmetica
    {
        polaca_emitir_operador(":=", yylineno);
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), $1->lexema);
        polaca_emitir_simbolo(s ? s : $1, yylineno);
        $$.es_comptime = false;
        $$.tipo = $4.tipo;
        $$.simbolo_ref = s;
    }
;

constante_invalida:
    OUT_OF_RANGE
    { cant_errores++; }
  | ERROR_LEXICO
    { cant_errores++; }
;

constante_con_signo:
    CTE
    {
        $$ = $1;
    }
  | CTE_FLOAT
    {
        $$ = $1;
    }
  | '+' CTE
    {
        $$ = $2;
    }
  | '+' CTE_FLOAT
    {
        $$ = $2;
    }
  | '-' CTE
    {
        $$ = ($2 != NULL) ? cambiar_signo_constante($2, -1) : NULL;
    }
  | '-' CTE_FLOAT
    {
        $$ = ($2 != NULL) ? cambiar_signo_constante($2, -1) : NULL;
    }
  | constante_invalida
    {
        $$ = NULL;
    }
  | '+' constante_invalida
    {
        $$ = NULL;
    }
  | '-' constante_invalida
    {
        $$ = NULL;
    }
;

if_sentencia:
    if_encabezado bloque_if fin_if
  | if_encabezado bloque_if error
    { yyerror("Error: Estructura IF mal cerrada (posiblemente falta END_IF o el delimitador ';')."); yyerrok; }
  | IF condicion ')' bloque_if fin_if
    { yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
  | IF '(' condicion bloque_if fin_if
    { yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
;

if_encabezado:
    IF '(' condicion ')'
    {
        int celda_bf = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BF", yylineno);
        polaca_apilar_salto(celda_bf);
    }
;

fin_if:
    else_encabezado bloque_if END_IF
    {
        int celda_bi = polaca_desapilar_salto();
        polaca_poner_destino(celda_bi, polaca_posicion_actual());
    }
  | END_IF
    {
        int celda_bf = polaca_desapilar_salto();
        polaca_poner_destino(celda_bf, polaca_posicion_actual());
    }
;

else_encabezado:
    ELSE
    {
        int celda_bi = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BI", yylineno);
        int celda_bf = polaca_desapilar_salto();
        polaca_poner_destino(celda_bf, polaca_posicion_actual());
        polaca_apilar_salto(celda_bi);
    }
;

bloque_if:
    bloque_ejecutable
  | sentencia ';'
;

iteracion:
    encabezado_iteracion REPEAT cuerpo_iteracion  
    {
        if (tope_from > 0) {
            ContextoFrom ctx = pila_from[--tope_from];

            // Actualización de variable de control: id := id +/- cte3
            polaca_emitir_simbolo(ctx.id_control, yylineno);
            polaca_emitir_simbolo(ctx.id_control, yylineno);
            polaca_emitir_simbolo(ctx.cte3_sym, yylineno);
            polaca_emitir_operador(ctx.ascendente ? "+" : "-", yylineno);
            polaca_emitir_operador(":=", yylineno);

            // Salto incondicional al inicio de la prueba
            int celda_bi = polaca_emitir_celda_vacia(yylineno);
            polaca_poner_destino(celda_bi, ctx.pos_inicio_prueba);
            polaca_emitir_operador("BI", yylineno);

            // Backpatching: rellenar el BF con la posición siguiente al BI
            polaca_poner_destino(ctx.celda_bf, polaca_posicion_actual());
        }
    }
;

encabezado_iteracion:
    FROM ID '=' constante_con_signo TO constante_con_signo BY constante_con_signo
    {
        Simbolo *id_sym = buscar_identificador_semantico(obtener_tabla_simbolos(), $2->lexema);
        if (!id_sym) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable de control '%s' no declarada o fuera de alcance.", $2->lexema);
            id_sym = $2;
        } else if (id_sym->tipo != TIPO_INTEGER) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "La variable de control '%s' del ciclo FROM debe ser de tipo INTEGER.", $2->lexema);
        }

        Simbolo *c1 = $4;
        Simbolo *c2 = $6;
        Simbolo *c3 = $8;

        if (c1 && c1->tipo != TIPO_INTEGER) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "La constante inicial del ciclo FROM debe ser de tipo INTEGER.");
        }
        if (c2 && c2->tipo != TIPO_INTEGER) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "La constante final (TO) del ciclo FROM debe ser de tipo INTEGER.");
        }
        if (c3 && c3->tipo != TIPO_INTEGER) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "La constante de paso (BY) del ciclo FROM debe ser de tipo INTEGER.");
        }

        long v1 = c1 ? parsear_valor_entero(c1->lexema) : 0;
        long v2 = c2 ? parsear_valor_entero(c2->lexema) : 0;
        long v3 = c3 ? parsear_valor_entero(c3->lexema) : 1;

        bool asc = (v1 <= v2);

        // 1. Inicialización en Polaca: id, cte1, :=
        polaca_emitir_simbolo(id_sym, yylineno);
        polaca_emitir_simbolo(c1, yylineno);
        polaca_emitir_operador(":=", yylineno);

        // 2. Inicio de prueba para el ciclo
        int pos_prueba = polaca_posicion_actual();

        // 3. Condición de parada (Pág. 6):
        // Si CTE1 <= CTE2: id < CTE2
        // Si CTE1 > CTE2:  id > CTE2
        polaca_emitir_simbolo(id_sym, yylineno);
        polaca_emitir_simbolo(c2, yylineno);
        polaca_emitir_operador(asc ? "<" : ">", yylineno);

        int celda_bf = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BF", yylineno);

        // 4. Guardar contexto en pila para ciclos anidados
        if (tope_from < 32) {
            pila_from[tope_from].id_control = id_sym;
            pila_from[tope_from].cte1_val = v1;
            pila_from[tope_from].cte2_val = v2;
            pila_from[tope_from].cte3_val = v3;
            pila_from[tope_from].cte1_sym = c1;
            pila_from[tope_from].cte2_sym = c2;
            pila_from[tope_from].cte3_sym = c3;
            pila_from[tope_from].ascendente = asc;
            pila_from[tope_from].pos_inicio_prueba = pos_prueba;
            pila_from[tope_from].celda_bf = celda_bf;
            tope_from++;
        }
    }
  | FROM '(' condicion ')'
  | FROM '=' constante_con_signo TO constante_con_signo BY constante_con_signo
    { yyerror("Error: Falta identificador (ID) en el encabezado."); yyerrok; }
  | FROM ID '=' constante_con_signo constante_con_signo
    { yyerror("Error: Falta 'TO' en el encabezado de la iteración."); yyerrok; }
  | FROM condicion ')'
    { yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
  | FROM '(' condicion
    { yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
  | FROM ID '=' TO
    { yyerror("Error: Falta CTE en el encabezado."); yyerrok; }
;

cuerpo_iteracion:
    bloque_o_sentencia
;

bloque_o_sentencia:
    bloque_ejecutable
  | sentencia
;

condicion:
    expresion_aritmetica operador_relacional expresion_aritmetica
    {
        polaca_emitir_operador($2, yylineno);
    }
;

operador_relacional:
    '<'  { $$ = "<"; }
  | '>'  { $$ = ">"; }
  | GE   { $$ = ">="; }
  | LE   { $$ = "<="; }
  | EQ   { $$ = "=="; }
  | NE   { $$ = "!="; }
;

%%

void yyerror(const char *s) {
    if (strncmp(s, "syntax error", 12) == 0) {
        return; 
    }

    if (strstr(s, "Sentencia mal formada") != NULL) {
        cant_errores++; 
        registrar_error(ETAPA_SINTACTICO, yylineno, "Sentencia inválida.");
        return;
    }

    cant_errores++;
    const char *mensaje = (strncmp(s, "Error: ", 7) == 0) ? s + 7 : s;
    registrar_error(ETAPA_SINTACTICO, yylineno, "%s", mensaje);
}