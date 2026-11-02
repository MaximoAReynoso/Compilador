#include "tabla_simbolos.h"
#include "errores.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_NIVELES_AMBITO 32

/* Estado de la Pila de Ámbitos (Scope Stack) */
static char *pila_ambitos[MAX_NIVELES_AMBITO];
static int tope_ambitos = 0;
static char buffer_ambito_actual[512] = "";

/* Hash para la tabla hash interna */
static unsigned hash(const char *lexema) {
    unsigned hash_value = 0;
    if (!lexema) return 0;
    while (*lexema != '\0') {
        hash_value = (hash_value * 31) + (unsigned char)(*lexema);
        lexema++;
    }
    return hash_value % TAM_TABLA;
}

void inicializar_tabla(TablaSimbolos *tabla) {
    if (!tabla) return;
    for (int i = 0; i < TAM_TABLA; i++) {
        tabla->entradas[i] = NULL;
    }
}

Simbolo *buscar_simbolo(TablaSimbolos *tabla, const char *lexema) {
    if (!tabla || !lexema) return NULL;
    unsigned index = hash(lexema);
    Simbolo *actual = tabla->entradas[index];

    while (actual != NULL) {
        if (actual->lexema && strcmp(actual->lexema, lexema) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

Simbolo *insertar_simbolo(TablaSimbolos *tabla, const char *lexema, int token) {
    if (!tabla || !lexema) return NULL;

    Simbolo *existe = buscar_simbolo(tabla, lexema);
    if (existe != NULL) {
        existe->cantidad++;
        return existe;
    }

    unsigned index = hash(lexema);
    Simbolo *nuevo_simbolo = calloc(1, sizeof(Simbolo));
    if (nuevo_simbolo == NULL) {
        return NULL;
    }

    nuevo_simbolo->lexema = strdup(lexema);
    if (nuevo_simbolo->lexema == NULL) {
        free(nuevo_simbolo);
        return NULL;
    }

    nuevo_simbolo->token = token;
    nuevo_simbolo->cantidad = 1;
    nuevo_simbolo->tipo = TIPO_NO_ASIGNADO;
    nuevo_simbolo->uso = USO_NO_ASIGNADO;
    nuevo_simbolo->siguiente = tabla->entradas[index];
    tabla->entradas[index] = nuevo_simbolo;

    return nuevo_simbolo;
}

Simbolo *mover_ocurrencia(TablaSimbolos *tabla, Simbolo *simbolo, const char *nuevo_lexema) {
    if (tabla == NULL || simbolo == NULL || nuevo_lexema == NULL) {
        return NULL;
    }

    Simbolo *destino = insertar_simbolo(tabla, nuevo_lexema, simbolo->token);
    if (destino == NULL || destino == simbolo) {
        return destino;
    }

    if (simbolo->cantidad > 1) {
        simbolo->cantidad--;
        return destino;
    }

    unsigned index = hash(simbolo->lexema);
    Simbolo **actual = &tabla->entradas[index];
    while (*actual != NULL && *actual != simbolo) {
        actual = &(*actual)->siguiente;
    }
    if (*actual == simbolo) {
        *actual = simbolo->siguiente;
        if (simbolo->lexema) free(simbolo->lexema);
        if (simbolo->nombre_original) free(simbolo->nombre_original);
        if (simbolo->ambito) free(simbolo->ambito);
        if (simbolo->codigo_clase) free(simbolo->codigo_clase);
        if (simbolo->tipo_clase) free(simbolo->tipo_clase);
        free(simbolo);
    }

    return destino;
}

void modificar_lexema(Simbolo *simbolo, const char *nuevo_lexema) {
    if (simbolo == NULL || nuevo_lexema == NULL) return;
    char *nuevo = strdup(nuevo_lexema);
    if (nuevo == NULL) return;
    free(simbolo->lexema);
    simbolo->lexema = nuevo;
}

static void liberar_simbolo(Simbolo *s) {
    if (!s) return;
    if (s->lexema) free(s->lexema);
    if (s->nombre_original) free(s->nombre_original);
    if (s->ambito) free(s->ambito);
    if (s->codigo_clase) free(s->codigo_clase);
    if (s->tipo_clase) free(s->tipo_clase);
    
    // Liberar parámetros formales si es función
    ParametroFormal *pf = s->parametros;
    while (pf != NULL) {
        ParametroFormal *sig = pf->siguiente;
        if (pf->nombre) free(pf->nombre);
        free(pf);
        pf = sig;
    }

    // Liberar atributos de clase si los hay
    AtributoClase *at = s->atributos;
    while (at != NULL) {
        AtributoClase *sig = at->siguiente;
        if (at->nombre) free(at->nombre);
        free(at);
        at = sig;
    }

    // Liberar clases base si las hay
    if (s->clases_padre) {
        for (int i = 0; i < s->cant_padres; i++) {
            if (s->clases_padre[i]) free(s->clases_padre[i]);
        }
        free(s->clases_padre);
    }

    free(s);
}

void destruir_tabla(TablaSimbolos *tabla) {
    if (!tabla) return;
    for (int i = 0; i < TAM_TABLA; i++) {
        Simbolo *actual = tabla->entradas[i];
        while (actual != NULL) {
            Simbolo *temp = actual;
            actual = actual->siguiente;
            liberar_simbolo(temp);
        }
        tabla->entradas[i] = NULL;
    }
}

const char *tipo_dato_a_string(TipoDato tipo) {
    switch (tipo) {
        case TIPO_INTEGER: return "INTEGER";
        case TIPO_SINGLEF: return "SINGLEF";
        case TIPO_CLASE:   return "CLASE";
        case TIPO_VOID:    return "VOID";
        case TIPO_CADENA:  return "CADENA";
        default:           return "-";
    }
}

const char *uso_simbolo_a_string(UsoSimbolo uso) {
    switch (uso) {
        case USO_VARIABLE:           return "VARIABLE";
        case USO_PARAMETRO:          return "PARAMETRO";
        case USO_FUNCION:            return "FUNCION";
        case USO_CLASE:              return "CLASE";
        case USO_OBJETO:             return "OBJETO";
        case USO_CONSTANTE:          return "CONSTANTE";
        case USO_VARIABLE_COMPTIME:  return "COMPTIME";
        default:                     return "-";
    }
}

/* =========================================================================
 * GESTIÓN DE ÁMBITOS (Scope Stack) y NAME MANGLING
 * ========================================================================= */

static void actualizar_buffer_ambito(void) {
    buffer_ambito_actual[0] = '\0';
    for (int i = 0; i < tope_ambitos; i++) {
        if (i > 0) {
            strcat(buffer_ambito_actual, ":");
        }
        strcat(buffer_ambito_actual, pila_ambitos[i]);
    }
}

void inicializar_gestor_ambitos(void) {
    destruir_gestor_ambitos();
    tope_ambitos = 0;
    // El ámbito inicial raíz es "main"
    pila_ambitos[tope_ambitos++] = strdup("main");
    actualizar_buffer_ambito();
}

void destruir_gestor_ambitos(void) {
    for (int i = 0; i < tope_ambitos; i++) {
        if (pila_ambitos[i]) {
            free(pila_ambitos[i]);
            pila_ambitos[i] = NULL;
        }
    }
    tope_ambitos = 0;
    buffer_ambito_actual[0] = '\0';
}

void entrar_ambito(const char *subambito) {
    if (!subambito) return;
    if (tope_ambitos >= MAX_NIVELES_AMBITO) {
        fprintf(stderr, "Error interno: Profundidad máxima de ámbitos excedida.\n");
        return;
    }
    pila_ambitos[tope_ambitos++] = strdup(subambito);
    actualizar_buffer_ambito();
}

void salir_ambito(void) {
    if (tope_ambitos > 1) { // Mantener siempre al menos el ámbito base "main"
        free(pila_ambitos[--tope_ambitos]);
        pila_ambitos[tope_ambitos] = NULL;
        actualizar_buffer_ambito();
    }
}

const char *obtener_ambito_actual(void) {
    return buffer_ambito_actual;
}

char *construir_mangled_name(const char *nombre, const char *ambito) {
    if (!nombre) return NULL;
    if (!ambito || strlen(ambito) == 0) {
        return strdup(nombre);
    }
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s:%s", nombre, ambito);
    return strdup(buffer);
}

Simbolo *buscar_en_ambito_actual(TablaSimbolos *tabla, const char *nombre) {
    if (!tabla || !nombre) return NULL;
    char *clave = construir_mangled_name(nombre, obtener_ambito_actual());
    Simbolo *s = buscar_simbolo(tabla, clave);
    free(clave);
    return s;
}

Simbolo *buscar_identificador_semantico(TablaSimbolos *tabla, const char *nombre) {
    if (!tabla || !nombre) return NULL;

    // Construcción de la cadena de ámbito para cada nivel desde el tope hacia la raíz
    char scope_temp[512];
    for (int nivel = tope_ambitos; nivel >= 1; nivel--) {
        scope_temp[0] = '\0';
        for (int i = 0; i < nivel; i++) {
            if (i > 0) strcat(scope_temp, ":");
            strcat(scope_temp, pila_ambitos[i]);
        }
        char *clave = construir_mangled_name(nombre, scope_temp);
        Simbolo *s = buscar_simbolo(tabla, clave);
        free(clave);
        if (s != NULL && s->uso != USO_NO_ASIGNADO) {
            return s;
        }
    }

    // Por último, si no se encontró con mangling, buscar el identificador global o directo
    Simbolo *global = buscar_simbolo(tabla, nombre);
    if (global && global->uso != USO_NO_ASIGNADO) {
        return global;
    }

    return NULL;
}

Simbolo *declarar_identificador(
    TablaSimbolos *tabla,
    const char *nombre,
    int token,
    TipoDato tipo,
    UsoSimbolo uso,
    int linea
) {
    if (!tabla || !nombre) return NULL;

    const char *ambito = obtener_ambito_actual();
    Simbolo *existente = buscar_en_ambito_actual(tabla, nombre);

    if (existente != NULL && existente->uso != USO_NO_ASIGNADO) {
        registrar_error(
            ETAPA_SEMANTICO,
            linea,
            "Variable o identificador '%s' redeclarado en el ámbito actual '%s'.",
            nombre,
            ambito
        );
        return NULL;
    }

    char *clave = construir_mangled_name(nombre, ambito);
    Simbolo *nuevo = insertar_simbolo(tabla, clave, token);
    free(clave);

    if (nuevo) {
        nuevo->nombre_original = strdup(nombre);
        nuevo->ambito = strdup(ambito);
        nuevo->tipo = tipo;
        nuevo->uso = uso;
    }

    return nuevo;
}

void imprimir_tabla(TablaSimbolos *tabla) {
    if (!tabla) return;
    printf("\n========================================================================================\n");
    printf("                               TABLA DE SÍMBOLOS                                        \n");
    printf("========================================================================================\n");
    printf("%-28s %-12s %-10s %-12s %-16s %-10s\n",
           "LEXEMA / CLAVE", "TOKEN", "TIPO", "USO", "ÁMBITO", "CANTIDAD");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < TAM_TABLA; i++) {
        Simbolo *actual = tabla->entradas[i];
        while (actual != NULL) {
            // Mostramos todas las entradas con información semántica o constantes
            printf("%-28s %-12d %-10s %-12s %-16s %-10u\n",
                   actual->lexema ? actual->lexema : "?",
                   actual->token,
                   tipo_dato_a_string(actual->tipo),
                   uso_simbolo_a_string(actual->uso),
                   actual->ambito ? actual->ambito : "-",
                   actual->cantidad);
            actual = actual->siguiente;
        }
    }
    printf("========================================================================================\n\n");
}

bool clases_tienen_misma_estructura(Simbolo *c1, Simbolo *c2) {
    if (!c1 || !c2) return false;
    if (c1->cant_atributos != c2->cant_atributos) return false;

    AtributoClase *a1 = c1->atributos;
    AtributoClase *a2 = c2->atributos;
    while (a1 != NULL && a2 != NULL) {
        if (a1->tipo != a2->tipo) return false;
        a1 = a1->siguiente;
        a2 = a2->siguiente;
    }
    return true;
}

static bool buscar_miembro_en_clase_directa(TablaSimbolos *ts, Simbolo *cls, const char *nombre, ResultadoBusquedaMiembro *res) {
    if (!cls || !nombre) return false;

    // 1. Buscar en atributos de la clase
    for (AtributoClase *at = cls->atributos; at != NULL; at = at->siguiente) {
        if (strcmp(at->nombre, nombre) == 0) {
            if (res) {
                res->nombre_clase_origen = cls->nombre_original ? cls->nombre_original : cls->lexema;
                res->tipo = at->tipo;
                res->uso = USO_VARIABLE;
                res->simbolo_metodo = NULL;
            }
            return true;
        }
    }

    // 2. Buscar en métodos de la clase
    char ambito_clase[256];
    snprintf(ambito_clase, sizeof(ambito_clase), "%s:%s",
             cls->ambito ? cls->ambito : "main",
             cls->nombre_original ? cls->nombre_original : cls->lexema);
    char *mangled_metodo = construir_mangled_name(nombre, ambito_clase);
    Simbolo *metodo = buscar_simbolo(ts, mangled_metodo);
    free(mangled_metodo);

    if (metodo != NULL && metodo->uso == USO_FUNCION) {
        if (res) {
            res->nombre_clase_origen = cls->nombre_original ? cls->nombre_original : cls->lexema;
            res->tipo = metodo->tipo_retorno;
            res->uso = USO_FUNCION;
            res->simbolo_metodo = metodo;
        }
        return true;
    }

    return false;
}

bool resolver_miembro_herencia(TablaSimbolos *ts, Simbolo *cls, const char *nombre, int linea, ResultadoBusquedaMiembro *res_final) {
    if (!cls) return false;

    // Paso 1: Si está en la clase propia, se usa directamente (sin ambigüedad)
    ResultadoBusquedaMiembro res_propia;
    if (buscar_miembro_en_clase_directa(ts, cls, nombre, &res_propia)) {
        if (res_final) *res_final = res_propia;
        return true;
    }

    // Paso 2: Si no está en la clase propia, buscar en las clases de las cuales hereda
    if (cls->cant_padres == 0 || cls->clases_padre == NULL) {
        registrar_error(
            ETAPA_SEMANTICO,
            linea,
            "El miembro '%s' no está declarado en la clase '%s'.",
            nombre,
            cls->nombre_original ? cls->nombre_original : cls->lexema
        );
        return false;
    }

    char *primera_base = NULL;
    char *segunda_base = NULL;
    int encontradas = 0;
    ResultadoBusquedaMiembro res_hallada;

    for (int i = 0; i < cls->cant_padres; i++) {
        const char *nom_padre = cls->clases_padre[i];
        Simbolo *padre = buscar_identificador_semantico(ts, nom_padre);
        if (!padre || padre->uso != USO_CLASE) {
            continue;
        }

        ResultadoBusquedaMiembro res_p;
        if (buscar_miembro_en_clase_directa(ts, padre, nombre, &res_p)) {
            encontradas++;
            if (encontradas == 1) {
                primera_base = padre->nombre_original ? padre->nombre_original : padre->lexema;
                res_hallada = res_p;
            } else if (encontradas == 2) {
                segunda_base = padre->nombre_original ? padre->nombre_original : padre->lexema;
            }
        }
    }

    if (encontradas > 1) {
        registrar_error(
            ETAPA_SEMANTICO,
            linea,
            "Ambigüedad por herencia múltiple (Tema 32 - Opción 3): el miembro '%s' se encuentra en más de una clase base ('%s' y '%s').",
            nombre,
            primera_base ? primera_base : "?",
            segunda_base ? segunda_base : "?"
        );
        return false;
    }

    if (encontradas == 1) {
        if (res_final) *res_final = res_hallada;
        return true;
    }

    registrar_error(
        ETAPA_SEMANTICO,
        linea,
        "El miembro '%s' no está declarado en la clase '%s' ni en sus clases heredadas.",
        nombre,
        cls->nombre_original ? cls->nombre_original : cls->lexema
    );
    return false;
}