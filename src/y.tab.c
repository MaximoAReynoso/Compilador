/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20221106

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "src/gramatica.y"
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

static Simbolo *lista_vars_declaradas[64];
static int cant_vars_declaradas = 0;

/* Contexto FROM - REPEAT */
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

static Simbolo *pila_fn_decl[32];
static int tope_fn_decl = 0;

/* Orden de evaluación de parámetros */
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

    for (int k = 0; k < inv.cant_orden; k++) {
        int idx = inv.orden[k] - 1;
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

        if (s_formal != NULL) {
            polaca_emitir_simbolo(s_formal, inv.linea);
        }

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

        if (s_formal != NULL) {
            polaca_emitir_operador(":=", inv.linea);
        }
    }

    if (fn != NULL) {
        polaca_emitir_simbolo(fn, inv.linea);
    }
    polaca_emitir_operador("CALL", inv.linea);

    if (inv.nombre_fn) free(inv.nombre_fn);
}

static Simbolo *clase_actual_declaracion = NULL;
static char *lista_padres_declarados[16];
static int cant_padres_declarados = 0;
static int anidamiento_control_no_comptime = 0;
static bool ultima_condicion_comptime = false;
static bool pila_condicion_comptime[32];
static int tope_condicion = 0;

static void validar_compatibilidad_asignacion(Simbolo *dest, TipoDato tipo_expr, bool es_comptime, long val_int, double val_float, int linea) {
    if (!dest) return;

    if (dest->uso == USO_VARIABLE_COMPTIME) {
        if (!es_comptime) {
            registrar_error(
                ETAPA_SEMANTICO,
                linea,
                "No se puede asignar una expresión no determinable en tiempo de compilación a la variable COMPTIME '%s'.",
                dest->nombre_original ? dest->nombre_original : dest->lexema
            );
        } else if (anidamiento_control_no_comptime > 0) {
            registrar_error(
                ETAPA_SEMANTICO,
                linea,
                "No se puede modificar la variable COMPTIME '%s' dentro de un contexto de control no determinable en tiempo de compilación.",
                dest->nombre_original ? dest->nombre_original : dest->lexema
            );
        } else {
            dest->valor_comptime_valido = true;
            dest->valor_int = val_int;
            dest->valor_float = val_float;
        }
    }

    if (dest->tipo != TIPO_NO_ASIGNADO && tipo_expr != TIPO_NO_ASIGNADO && dest->tipo != TIPO_CLASE && tipo_expr != TIPO_CLASE) {
        if (dest->tipo == TIPO_SINGLEF && tipo_expr == TIPO_INTEGER) {
            registrar_error(
                ETAPA_SEMANTICO,
                linea,
                "Incompatibilidad de tipos en asignación: no se puede asignar INTEGER a SINGLEF sin conversión explícita TOSF."
            );
        } else if (dest->tipo == TIPO_INTEGER && tipo_expr == TIPO_SINGLEF) {
            registrar_error(
                ETAPA_SEMANTICO,
                linea,
                "Incompatibilidad de tipos en asignación: no se puede asignar SINGLEF a INTEGER."
            );
        }
    }
}
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 244 "src/gramatica.y"
typedef union YYSTYPE {
    struct Simbolo *simbolo;
    int val_int;
    int tipo_dato;
    const char *cadena;
    InfoExpr info_expr;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 280 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define ID 257
#define CTE 258
#define CTE_FLOAT 259
#define MULT_STRING 260
#define ASSIGN 261
#define GE 262
#define LE 263
#define EQ 264
#define NE 265
#define OUT_OF_RANGE 266
#define ERROR_LEXICO 267
#define IF 268
#define ELSE 269
#define END_IF 270
#define BEGIN 271
#define END 272
#define POUT 273
#define RET 274
#define CLASS 275
#define FUNCTION 276
#define INTEGER 277
#define SINGLEF 278
#define FROM 279
#define TO 280
#define BY 281
#define REPEAT 282
#define COMPTIME 283
#define TOSF 284
#define EXTENDS 285
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    0,   10,   10,   13,   13,   14,   14,
   14,   14,   14,   19,   19,    1,    1,   15,   20,   20,
   18,   16,   16,   16,   16,   21,   23,   22,   22,   22,
   24,   24,   24,   26,   17,   25,   25,   29,   29,   27,
   27,   27,   28,   28,   30,   30,   30,   31,   11,   11,
   12,   12,   12,   12,   32,   32,   32,   32,   32,   37,
   37,   33,   33,    4,    4,    4,   36,   36,   36,   36,
    5,    5,    5,    5,    5,    6,    6,    6,    6,    6,
    7,   38,    7,    8,    8,    8,    8,    8,    8,    8,
   39,   39,   41,   40,   40,   44,   43,   43,   45,   45,
   45,   45,   42,   47,   47,   48,   49,    9,   50,    9,
   46,   46,    3,    3,    3,    3,    3,    3,    3,    3,
    3,   34,   34,   34,   34,   51,   53,   53,   55,   52,
   52,   35,   58,   58,   56,   56,   56,   56,   56,   56,
   56,   57,   59,   59,   54,    2,    2,    2,    2,    2,
    2,
};
static const YYINT yylen[] = {                            2,
    4,    3,    4,    3,    1,    0,    2,    1,    2,    2,
    2,    2,    2,    3,    2,    1,    1,    2,    3,    1,
    2,    5,    4,    8,    7,    4,    3,    3,    2,    1,
    2,    3,    1,    0,    7,    1,    0,    3,    1,    1,
    3,    2,    2,    1,    2,    2,    2,    2,    3,    3,
    3,    2,    3,    2,    1,    1,    1,    1,    1,    4,
    3,    3,    3,    1,    3,    4,    4,    4,    3,    2,
    3,    3,    3,    3,    1,    3,    3,    3,    3,    1,
    1,    0,    6,    1,    3,    4,    1,    1,    4,    1,
    4,    3,    2,    4,    3,    4,    3,    3,    3,    3,
    1,    1,    1,    3,    1,    2,    0,    1,    0,    4,
    1,    1,    1,    1,    2,    2,    2,    2,    1,    2,
    2,    3,    3,    5,    5,    4,    3,    1,    1,    1,
    2,    3,    1,    1,    8,    4,    7,    5,    3,    3,
    4,    1,    1,    1,    3,    1,    1,    1,    1,    1,
    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,   16,   17,    0,    0,    0,    0,    0,    8,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   34,   20,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    7,    9,   10,   11,   12,   13,    0,    0,    0,
   30,    0,    0,    0,    0,    0,    0,   27,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   55,
   56,   57,   58,   59,    0,    0,    0,    4,    0,   31,
    0,    0,   29,    0,    0,    1,   19,   36,    0,    0,
    0,   54,    0,    0,    0,  113,  114,  111,  112,    0,
    0,    0,    0,   90,    0,    0,   80,   81,   87,   88,
  107,  107,  119,    0,   70,    0,    0,    0,  133,    0,
  134,    0,    0,    0,    0,    0,   50,    0,   52,  130,
    0,    0,    0,   49,   32,   28,    0,   23,   40,    0,
    0,    0,    0,   65,    0,   93,    0,    0,    0,    0,
    0,  115,  116,  120,  117,  118,  121,  148,  149,  150,
  151,    0,    0,  146,  147,    0,    0,    0,    0,    0,
  105,    0,    0,    0,    0,   69,    0,   61,    0,    0,
    0,    0,  139,    0,    0,    0,   53,   51,  131,  123,
  129,  128,  122,    0,  143,  144,  132,  142,   22,   39,
   42,    0,    0,    0,    0,    0,   44,    0,    0,    0,
   66,   82,    0,    0,    0,  126,    0,   73,    0,   74,
    0,    0,   78,   76,   79,   77,    0,  107,    0,    0,
  106,    0,    0,   68,   67,   60,  141,    0,  136,    0,
    0,   41,    0,    0,   45,   46,   35,   43,   47,    0,
   25,    0,   96,   86,   89,  125,    0,   91,  104,    0,
   94,  124,    0,  138,    0,  127,   38,   24,    0,    0,
  101,    0,  102,    0,    0,    0,   83,   98,    0,   97,
    0,    0,  137,   99,  100,  135,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  257,  275,  277,  278,  283,  287,  288,  297,  300,  301,
  302,  303,  304,  305,  306,  308,  310,  257,  297,  307,
  257,  257,  288,  307,  257,  276,  307,  256,  271,  298,
  257,  301,   59,   59,   59,   59,   59,  283,  288,  309,
  311,  309,  271,  298,   44,  313,  307,   40,  256,  257,
  256,  257,  268,  273,  274,  279,  291,  299,  319,  320,
  321,  322,  323,  324,  338,  343,  299,   59,  288,  257,
   44,   41,  311,   41,  299,   59,  257,  257,  312,   40,
   40,   59,   46,   91,  257,  258,  259,  266,  267,  284,
   40,   43,   45,  290,  292,  293,  294,  295,  326,  327,
  328,  331,  333,  341,  256,   40,   40,  257,  261,   40,
   61,  341,  345,  261,   61,  256,  272,  319,   59,  298,
  319,  339,  282,  272,  257,  311,  297,  298,  271,  285,
  314,  309,   41,  257,  292,   40,   61,   46,   91,   40,
  341,  258,  259,  333,  258,  259,  333,  262,  263,  264,
  265,   43,   45,   60,   62,  289,   42,   47,  329,  334,
  335,  336,  329,   41,  260,   41,  292,   41,  292,   61,
  345,  341,   41,  290,  292,  292,   59,   59,   59,  256,
  269,  270,  340,  342,  298,  319,  344,  346,  298,  257,
  271,  316,  285,  302,  303,  315,  317,  318,   41,  297,
   93,   40,  257,  292,  292,   41,  339,  256,  293,  256,
  293,  292,  256,  294,  256,  294,   41,   44,  257,  292,
  296,   41,  339,   41,   41,   41,  280,  290,   41,  280,
  339,  271,   44,  316,   59,   59,  272,  317,   59,  297,
  298,  325,   40,   93,   41,  340,   91,  330,  335,   61,
  330,  340,  280,  290,  290,  270,  257,  298,  292,  256,
  258,  332,  333,  337,  290,  281,   41,   93,   44,   93,
  292,  281,  290,  258,  333,  290,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          6,
    7,  156,   94,   57,   95,   96,   97,   98,  221,    8,
  120,   58,    9,   10,   11,   12,   13,   14,   15,   20,
   16,   40,   17,   41,   79,   46,  131,  196,  192,  197,
  198,  121,   60,   61,   62,   63,   64,  242,   99,  100,
  101,  159,  248,  102,  262,  103,  160,  161,  162,  264,
   65,  122,  183,  104,  184,   66,  187,  113,  188,
};
static const YYINT yysindex[] = {                       -99,
  178, -238,    0,    0, -239,    0, -242, -224,  307,    0,
  -19,   12,   62,   66,  110,   -2,   -2, -196, -164,   94,
    0,    0, -196,   94,  103,   58,   94,  339,  339,  116,
 -196,    0,    0,    0,    0,    0,    0,  142,  -49,  -31,
    0,  -24,  339,  128,  -43,  -37,   94,    0,  157,  163,
  202,   26,  -34,    1,  229,  -40,  -60,  -63,  214,    0,
    0,    0,    0,    0,  335,   11,  238,    0,   27,    0,
   -2,  307,    0, -224,  238,    0,    0,    0, -171,   -2,
  241,    0,   41,   33,    2,    0,    0,    0,    0,  265,
   33,   85,  193,    0,  431,   84,    0,    0,    0,    0,
    0,    0,    0,  275,    0,  -29,  -18,    6,    0,   33,
    0,  278,  283,   33,   33,  264,    0,  268,    0,    0,
  270,  -70,  335,    0,    0,    0, -224,    0,    0, -152,
 -234,  -15,  307,    0,   10,    0,  313,  107,   33,   33,
  165,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  159,  191,    0,    0,   33,  213,  242,  317,  328,
    0,  123,  334,  335,  336,    0,  445,    0,  473,  313,
   79,  342,    0,  118,  170,  170,    0,    0,    0,    0,
    0,    0,    0,  335,    0,    0,    0,    0,    0,    0,
    0,  -36,  144,  347,  350,  281,    0,  368,  307, -224,
    0,    0,  355,   25,  529,    0,  154,    0,   84,    0,
   84,  170,    0,    0,    0,    0,  343,    0,  101,  170,
    0,  343,  154,    0,    0,    0,    0,  266,    0,  283,
  167,    0,  185,  401,    0,    0,    0,    0,    0, -224,
    0,   33,    0,    0,    0,    0,  174,    0,    0,  313,
    0,    0,  283,    0,  184,    0,    0,    0,  536,  375,
    0,  -20,    0,   33,  192,  283,    0,    0,  138,    0,
  170,  283,    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                      -114,
 -114,    0,    0,    0,    0,    0,    0,    0, -111,    0,
    0,    0,    0,    0,    0,    0,    0,  136,    0,  418,
    0,    0,    0,  423,  136,    0,  426,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -13,    0,
    0,    0,    0,  487,    0,  -89,  437,    0,    0,    0,
    0,  -54,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -114,    0,    0,  502,    0,    0,    0,    0,    0,
   57,    0,    0,    0,   15,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  105,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  509,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -114,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  464,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  277,
    0,  233,    0,    0,  454,  460,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -114,    0,
    0,    0,   39,    0,    0,    0,    0,    0,  129,    0,
  369,  210,    0,    0,    0,    0,   68,    0,  611,  115,
    0,   92,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  472,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  263,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  201,    0,    0,    0,    0,    0,
};
#if YYBTYACC
static const YYINT yycindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
   49,    0,  333,    0,  461,  311,  370,    0,    0,   44,
  380,  231,    0,  514, -101,  -94,    0,    0,    0,  148,
    0,    5,    0,  -38,    0,    0,    0,    0,  341,  344,
    0,   21,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  435,  316,    0,    0,  -57,    0,  321,    0,    0,
    0,   -1, -117,   13,    0,    0,    0,  440,    0,
};
#define YYTABLESIZE 774
static const YYINT yytable[] = {                        110,
  115,   73,   92,   73,   93,   91,   64,  233,   92,   72,
   93,  166,   71,   92,   25,   93,   74,   22,   21,   71,
  111,   42,  168,  269,   92,  199,   93,   33,   71,  194,
   33,   28,  126,   26,  144,  147,  195,    3,    4,   33,
  106,  136,    3,    4,   19,  136,   29,  138,   59,   59,
  193,  138,  152,   23,  153,   84,   84,   84,   84,   84,
   22,   84,  137,   59,   39,   39,  170,  152,  112,  153,
   34,   83,  270,   84,   84,   92,   84,   93,  118,   85,
   85,   85,   85,   85,  132,   85,   69,  118,   39,  246,
   39,   28,  139,   73,  194,  118,  139,   85,   85,  129,
   85,  195,  201,  141,  190,  252,   43,   84,   92,   92,
   92,   92,   92,  130,   92,  127,   84,  244,  191,   39,
   35,   92,  172,   93,   36,  157,   92,   92,   39,   92,
  158,   85,   95,   95,   95,   95,   95,   45,   95,  207,
  136,    6,   48,  186,    5,   75,  138,   75,   75,   75,
   95,   95,   24,   95,   27,  108,    6,    1,  108,    5,
   92,  250,  223,   75,   75,   92,   75,   93,   37,   71,
   47,   71,   71,   71,   68,    2,  200,    3,    4,   20,
   39,   37,  231,    5,   95,  180,   76,   71,   71,  263,
   71,  139,  116,   52,   20,   37,   80,   75,  181,  182,
  114,   92,   81,   93,   53,  206,   64,   70,  117,   54,
   55,  275,  152,   77,  153,   56,  108,   86,   87,   78,
  109,   71,   85,   86,   87,   88,   89,   85,   86,   87,
  165,   88,   89,   92,  232,   93,   88,   89,   85,   86,
   87,  110,  240,   90,  110,    3,    4,   88,   89,   90,
  145,   38,    3,    4,   90,   92,  105,   93,   38,   67,
   82,    3,    4,   33,   33,   90,  109,   38,  107,   33,
   84,   84,  119,   75,    3,    4,   84,   84,   84,   84,
   38,  133,   84,  125,   92,   84,   93,   84,   84,   85,
   86,   87,  123,   84,   85,   85,   84,  134,   88,   89,
   85,   85,   85,   85,  140,  109,   85,  109,   92,   85,
   93,   85,   85,   49,   50,  164,   90,   85,  173,  134,
   85,  134,  177,   92,   92,   92,  178,   93,  179,   92,
   92,   92,   92,   26,   26,   92,   86,   87,   92,   26,
   92,   92,  142,  143,   88,   89,   92,   95,   95,   92,
   88,   89,  202,   95,   95,   95,   95,  217,  227,   95,
   75,   75,   95,  203,   95,   95,   75,   75,   75,   75,
   95,  218,   75,   95,  222,   75,  224,   75,   75,  219,
   86,   87,  229,   75,   71,   71,   75,   30,   88,   89,
   71,   71,   71,   71,  243,  274,   71,  230,   44,   71,
  190,   71,   71,   88,   89,  235,   90,   71,  236,   72,
   71,   72,   72,   72,  208,   85,   86,   87,    3,    4,
   28,   52,  181,  182,   88,   89,  239,   72,   72,  260,
   72,  261,   53,  247,   18,   29,  256,   54,   55,   88,
   89,  257,   90,   56,  233,  174,  210,   85,   86,   87,
  145,  146,    2,  128,    3,    4,   88,   89,   88,   89,
    5,   72,  209,  211,  266,  145,  145,  268,  213,   85,
   86,   87,  272,  152,   90,  153,   21,  145,   88,   89,
  145,   15,  145,  145,   18,  225,    2,  152,  145,  153,
  154,  145,  155,  116,   52,   14,   90,  215,   85,   86,
   87,    3,  185,  228,  103,   53,  189,   88,   89,  124,
   54,   55,   62,  226,  140,  152,   56,  153,   63,  109,
  109,  109,   32,   86,   87,   90,  214,  216,  109,  109,
   48,   88,   89,  234,  134,  134,  163,  251,  249,  238,
   86,   87,  134,  134,  135,  253,  109,  171,   88,   89,
   84,   84,  237,   84,    0,   84,  134,    3,    4,    0,
  254,    0,  255,   31,    0,  193,  167,  169,   84,  245,
   84,  152,    0,  153,  175,  176,  267,    0,  152,  241,
  153,    2,    0,    3,    4,  265,    0,    0,    0,    5,
   28,   52,    0,    0,   51,   52,    0,    0,  273,  204,
  205,    0,   53,    0,  276,   29,   53,   54,   55,    0,
    0,   54,   55,   56,    0,    0,  212,   56,    0,  258,
    0,    0,  220,    0,   72,   72,    0,    0,    0,    0,
   72,   72,   72,   72,    0,    0,   72,    0,    0,   72,
    0,   72,   72,    0,    0,    0,    0,   72,    0,    0,
   72,   84,   84,   84,   84,   84,    0,   84,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  148,  149,  150,  151,    0,    0,    0,    0,
    0,    0,  259,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  271,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   84,   84,   84,   84,
};
static const YYINT yycheck[] = {                         40,
   61,   40,   43,   42,   45,   40,   61,   44,   43,   41,
   45,   41,   44,   43,  257,   45,   41,  257,  257,   44,
   61,   17,   41,   44,   43,   41,   45,   41,   44,  131,
   44,  256,   71,  276,   92,   93,  131,  277,  278,   59,
   40,   40,  277,  278,    1,   40,  271,   46,   28,   29,
  285,   46,   43,    5,   45,   41,   42,   43,   44,   45,
  257,   47,   61,   43,   16,   17,   61,   43,   56,   45,
   59,   46,   93,   59,   60,   43,   62,   45,   58,   41,
   42,   43,   44,   45,   80,   47,   38,   67,   40,  207,
   42,  256,   91,  132,  196,   75,   91,   59,   60,  271,
   62,  196,   93,   91,  257,  223,  271,   93,   41,   42,
   43,   44,   45,  285,   47,   72,   91,   93,  271,   71,
   59,   43,  110,   45,   59,   42,   59,   60,   80,   62,
   47,   93,   41,   42,   43,   44,   45,   44,   47,  141,
   40,  256,   40,  123,  256,   41,   46,   43,   44,   45,
   59,   60,    5,   62,    7,   41,  271,  257,   44,  271,
   93,   61,  164,   59,   60,   43,   62,   45,   59,   41,
   23,   43,   44,   45,   59,  275,  133,  277,  278,   44,
  132,  271,  184,  283,   93,  256,   59,   59,   60,  247,
   62,   91,  256,  257,   59,  285,   40,   93,  269,  270,
  261,   43,   40,   45,  268,   41,  261,  257,  272,  273,
  274,  269,   43,  257,   45,  279,  257,  258,  259,  257,
  261,   93,  257,  258,  259,  266,  267,  257,  258,  259,
  260,  266,  267,   43,  271,   45,  266,  267,  257,  258,
  259,   41,  199,  284,   44,  277,  278,  266,  267,  284,
   41,  283,  277,  278,  284,   43,  256,   45,  283,   29,
   59,  277,  278,  277,  278,  284,  261,  283,   40,  283,
  256,  257,   59,   43,  277,  278,  262,  263,  264,  265,
  283,   41,  268,  257,   43,  271,   45,  273,  274,  257,
  258,  259,  282,  279,  256,  257,  282,  257,  266,  267,
  262,  263,  264,  265,   40,   43,  268,   45,   43,  271,
   45,  273,  274,  256,  257,   41,  284,  279,   41,   43,
  282,   45,   59,  256,  257,   43,   59,   45,   59,  262,
  263,  264,  265,  277,  278,  268,  258,  259,  271,  283,
  273,  274,  258,  259,  266,  267,  279,  256,  257,  282,
  266,  267,   40,  262,  263,  264,  265,   41,  280,  268,
  256,  257,  271,  257,  273,  274,  262,  263,  264,  265,
  279,   44,  268,  282,   41,  271,   41,  273,  274,  257,
  258,  259,   41,  279,  256,  257,  282,    8,  266,  267,
  262,  263,  264,  265,   40,  258,  268,  280,   19,  271,
  257,  273,  274,  266,  267,   59,  284,  279,   59,   41,
  282,   43,   44,   45,  256,  257,  258,  259,  277,  278,
  256,  257,  269,  270,  266,  267,   59,   59,   60,  256,
   62,  258,  268,   91,  257,  271,  270,  273,  274,  266,
  267,  257,  284,  279,   44,  113,  256,  257,  258,  259,
  258,  259,  275,   74,  277,  278,  266,  267,  266,  267,
  283,   93,  152,  153,  281,  256,  257,   93,  256,  257,
  258,  259,  281,   43,  284,   45,   59,  268,  266,  267,
  271,   59,  273,  274,   59,   41,    0,   43,  279,   45,
   60,  282,   62,  256,  257,   59,  284,  256,  257,  258,
  259,    0,  123,  171,   41,  268,  127,  266,  267,  272,
  273,  274,   59,   41,  282,   43,  279,   45,   59,  257,
  258,  259,    9,  258,  259,  284,  157,  158,  266,  267,
   59,  266,  267,  193,  258,  259,  102,  222,  218,  196,
  258,  259,  266,  267,   84,  280,  284,  108,  266,  267,
   42,   43,  272,   45,   -1,   47,  280,  277,  278,   -1,
  228,   -1,  230,  257,   -1,  285,  106,  107,   60,   41,
   62,   43,   -1,   45,  114,  115,   41,   -1,   43,  200,
   45,  275,   -1,  277,  278,  253,   -1,   -1,   -1,  283,
  256,  257,   -1,   -1,  256,  257,   -1,   -1,  266,  139,
  140,   -1,  268,   -1,  272,  271,  268,  273,  274,   -1,
   -1,  273,  274,  279,   -1,   -1,  156,  279,   -1,  240,
   -1,   -1,  162,   -1,  256,  257,   -1,   -1,   -1,   -1,
  262,  263,  264,  265,   -1,   -1,  268,   -1,   -1,  271,
   -1,  273,  274,   -1,   -1,   -1,   -1,  279,   -1,   -1,
  282,   41,   42,   43,   44,   45,   -1,   47,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  262,  263,  264,  265,   -1,   -1,   -1,   -1,
   -1,   -1,  242,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  264,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  262,  263,  264,  265,
};
#if YYBTYACC
static const YYINT yyctable[] = {                        -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,
};
#endif
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 285
#define YYUNDFTOKEN 347
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"$end",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,"error","ID","CTE","CTE_FLOAT","MULT_STRING","ASSIGN","GE",
"LE","EQ","NE","OUT_OF_RANGE","ERROR_LEXICO","IF","ELSE","END_IF","BEGIN","END",
"POUT","RET","CLASS","FUNCTION","INTEGER","SINGLEF","FROM","TO","BY","REPEAT",
"COMPTIME","TOSF","EXTENDS","$accept","programa","tipo_dato",
"operador_relacional","constante_con_signo","destino_asignacion",
"expresion_aritmetica","termino","operando","operando_base","parametro_real",
"bloque_declarativo","bloque_ejecutable","lista_ejecutables",
"lista_declaraciones","declaracion","declaracion_variable",
"declaracion_funcion","declaracion_clase","declaracion_objeto",
"declaracion_comptime","lista_variables","encabezado_funcion",
"lista_parametros","encabezado_funcion_sin_kw","parametro","codigo_clase","$$1",
"encabezado_clase","miembros_clase","lista_clase","miembro","sentencia_extends",
"sentencia","asignacion","if_sentencia","iteracion","impresion",
"sentencia_retorno","$$2","llamada_con_orden","llamada_metodo_con_orden",
"llamada_encabezado","parametros_reales","orden_evaluacion",
"llamada_metodo_encabezado","lista_enteros","constante_invalida",
"lista_parametros_reales","parametro_real_item","iniciar_parametro","$$3",
"if_encabezado","bloque_if","fin_if","condicion","else_encabezado",
"encabezado_iteracion","cuerpo_iteracion","asignador_from","bloque_o_sentencia",
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : programa",
"programa : ID bloque_declarativo bloque_ejecutable ';'",
"programa : ID bloque_declarativo bloque_ejecutable",
"programa : ID bloque_declarativo BEGIN lista_ejecutables",
"programa : bloque_declarativo bloque_ejecutable ';'",
"bloque_declarativo : lista_declaraciones",
"bloque_declarativo :",
"lista_declaraciones : lista_declaraciones declaracion",
"lista_declaraciones : declaracion",
"declaracion : declaracion_variable ';'",
"declaracion : declaracion_funcion ';'",
"declaracion : declaracion_clase ';'",
"declaracion : declaracion_objeto ';'",
"declaracion : declaracion_comptime ';'",
"declaracion_comptime : COMPTIME tipo_dato lista_variables",
"declaracion_comptime : COMPTIME lista_variables",
"tipo_dato : INTEGER",
"tipo_dato : SINGLEF",
"declaracion_variable : tipo_dato lista_variables",
"lista_variables : lista_variables ',' ID",
"lista_variables : ID",
"declaracion_objeto : ID lista_variables",
"declaracion_funcion : encabezado_funcion lista_parametros ')' bloque_declarativo bloque_ejecutable",
"declaracion_funcion : encabezado_funcion_sin_kw lista_parametros ')' bloque_ejecutable",
"declaracion_funcion : tipo_dato FUNCTION error '(' lista_parametros ')' bloque_declarativo bloque_ejecutable",
"declaracion_funcion : tipo_dato FUNCTION ID '(' ')' bloque_declarativo bloque_ejecutable",
"encabezado_funcion : tipo_dato FUNCTION ID '('",
"encabezado_funcion_sin_kw : tipo_dato ID '('",
"lista_parametros : lista_parametros ',' parametro",
"lista_parametros : lista_parametros parametro",
"lista_parametros : parametro",
"parametro : tipo_dato ID",
"parametro : COMPTIME tipo_dato ID",
"parametro : tipo_dato",
"$$1 :",
"declaracion_clase : CLASS ID $$1 codigo_clase encabezado_clase miembros_clase END",
"codigo_clase : ID",
"codigo_clase :",
"lista_clase : lista_clase ',' ID",
"lista_clase : ID",
"encabezado_clase : BEGIN",
"encabezado_clase : EXTENDS lista_clase BEGIN",
"encabezado_clase : EXTENDS BEGIN",
"miembros_clase : miembros_clase miembro",
"miembros_clase : miembro",
"miembro : declaracion_variable ';'",
"miembro : declaracion_funcion ';'",
"miembro : sentencia_extends ';'",
"sentencia_extends : EXTENDS lista_clase",
"bloque_ejecutable : BEGIN lista_ejecutables END",
"bloque_ejecutable : error lista_ejecutables END",
"lista_ejecutables : lista_ejecutables sentencia ';'",
"lista_ejecutables : sentencia ';'",
"lista_ejecutables : lista_ejecutables error ';'",
"lista_ejecutables : error ';'",
"sentencia : asignacion",
"sentencia : if_sentencia",
"sentencia : iteracion",
"sentencia : impresion",
"sentencia : sentencia_retorno",
"sentencia_retorno : RET '(' expresion_aritmetica ')'",
"sentencia_retorno : RET '(' ')'",
"asignacion : destino_asignacion ASSIGN expresion_aritmetica",
"asignacion : destino_asignacion '=' expresion_aritmetica",
"destino_asignacion : ID",
"destino_asignacion : ID '.' ID",
"destino_asignacion : ID '[' expresion_aritmetica ']'",
"impresion : POUT '(' expresion_aritmetica ')'",
"impresion : POUT '(' MULT_STRING ')'",
"impresion : POUT '(' ')'",
"impresion : POUT error",
"expresion_aritmetica : expresion_aritmetica '+' termino",
"expresion_aritmetica : expresion_aritmetica '-' termino",
"expresion_aritmetica : expresion_aritmetica '+' error",
"expresion_aritmetica : expresion_aritmetica '-' error",
"expresion_aritmetica : termino",
"termino : termino '*' operando",
"termino : termino '/' operando",
"termino : termino '*' error",
"termino : termino '/' error",
"termino : operando",
"operando : operando_base",
"$$2 :",
"operando : ID '=' '(' $$2 expresion_aritmetica ')'",
"operando_base : ID",
"operando_base : ID '.' ID",
"operando_base : ID '[' expresion_aritmetica ']'",
"operando_base : llamada_con_orden",
"operando_base : llamada_metodo_con_orden",
"operando_base : TOSF '(' expresion_aritmetica ')'",
"operando_base : constante_con_signo",
"llamada_con_orden : llamada_encabezado parametros_reales ')' orden_evaluacion",
"llamada_con_orden : llamada_encabezado parametros_reales ')'",
"llamada_encabezado : ID '('",
"llamada_metodo_con_orden : llamada_metodo_encabezado parametros_reales ')' orden_evaluacion",
"llamada_metodo_con_orden : llamada_metodo_encabezado parametros_reales ')'",
"llamada_metodo_encabezado : ID '.' ID '('",
"orden_evaluacion : '[' lista_enteros ']'",
"orden_evaluacion : '[' error ']'",
"lista_enteros : lista_enteros ',' CTE",
"lista_enteros : lista_enteros ',' constante_invalida",
"lista_enteros : CTE",
"lista_enteros : constante_invalida",
"parametros_reales : lista_parametros_reales",
"lista_parametros_reales : lista_parametros_reales ',' parametro_real_item",
"lista_parametros_reales : parametro_real_item",
"parametro_real_item : iniciar_parametro parametro_real",
"iniciar_parametro :",
"parametro_real : expresion_aritmetica",
"$$3 :",
"parametro_real : ID '=' $$3 expresion_aritmetica",
"constante_invalida : OUT_OF_RANGE",
"constante_invalida : ERROR_LEXICO",
"constante_con_signo : CTE",
"constante_con_signo : CTE_FLOAT",
"constante_con_signo : '+' CTE",
"constante_con_signo : '+' CTE_FLOAT",
"constante_con_signo : '-' CTE",
"constante_con_signo : '-' CTE_FLOAT",
"constante_con_signo : constante_invalida",
"constante_con_signo : '+' constante_invalida",
"constante_con_signo : '-' constante_invalida",
"if_sentencia : if_encabezado bloque_if fin_if",
"if_sentencia : if_encabezado bloque_if error",
"if_sentencia : IF condicion ')' bloque_if fin_if",
"if_sentencia : IF '(' condicion bloque_if fin_if",
"if_encabezado : IF '(' condicion ')'",
"fin_if : else_encabezado bloque_if END_IF",
"fin_if : END_IF",
"else_encabezado : ELSE",
"bloque_if : bloque_ejecutable",
"bloque_if : sentencia ';'",
"iteracion : encabezado_iteracion REPEAT cuerpo_iteracion",
"asignador_from : ASSIGN",
"asignador_from : '='",
"encabezado_iteracion : FROM ID asignador_from constante_con_signo TO constante_con_signo BY constante_con_signo",
"encabezado_iteracion : FROM '(' condicion ')'",
"encabezado_iteracion : FROM asignador_from constante_con_signo TO constante_con_signo BY constante_con_signo",
"encabezado_iteracion : FROM ID asignador_from constante_con_signo constante_con_signo",
"encabezado_iteracion : FROM condicion ')'",
"encabezado_iteracion : FROM '(' condicion",
"encabezado_iteracion : FROM ID asignador_from TO",
"cuerpo_iteracion : bloque_o_sentencia",
"bloque_o_sentencia : bloque_ejecutable",
"bloque_o_sentencia : sentencia",
"condicion : expresion_aritmetica operador_relacional expresion_aritmetica",
"operador_relacional : '<'",
"operador_relacional : '>'",
"operador_relacional : GE",
"operador_relacional : LE",
"operador_relacional : EQ",
"operador_relacional : NE",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
YYLTYPE  yyloc; /* position returned by actions */
YYLTYPE  yylloc; /* position from the lexer */
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
/* variables for the parser stack */
static YYSTACKDATA yystack;
#if YYBTYACC

/* Current parser state */
static YYParseState *yyps = 0;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = 0;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = 0;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = 0;

/* End position of lexical value queue */
static YYSTYPE *yylve = 0;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = 0;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = 0;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = 0;

/* End position of lexical position queue */
static YYLTYPE *yylpe = 0;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = 0;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = 0;

static YYINT  *yylexemes = 0;
#endif /* YYBTYACC */
#line 1484 "src/gramatica.y"

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
#line 1136 "y.tab.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

#if YYBTYACC
    yyps = yyNewState(0); if (yyps == 0) goto yyenomem;
    yyps->save = 0;
#endif /* YYBTYACC */
    yym = 0;
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 1:
#line 269 "src/gramatica.y"
	{
    }
#line 1810 "y.tab.c"
break;
case 2:
#line 272 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador ; al final del bloque ejecutable."); yyerrok; }
#line 1815 "y.tab.c"
break;
case 3:
#line 274 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador END al final del bloque ejecutable."); yyerrok; }
#line 1820 "y.tab.c"
break;
case 4:
#line 276 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
#line 1825 "y.tab.c"
break;
case 14:
#line 299 "src/gramatica.y"
	{
        for (int i = 0; i < cant_vars_declaradas; i++) {
            declarar_identificador(
                obtener_tabla_simbolos(),
                lista_vars_declaradas[i]->lexema,
                ID,
                yystack.l_mark[-1].tipo_dato,
                USO_VARIABLE_COMPTIME,
                yylineno
            );
        }
        cant_vars_declaradas = 0;
    }
#line 1842 "y.tab.c"
break;
case 15:
#line 313 "src/gramatica.y"
	{ yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
#line 1847 "y.tab.c"
break;
case 16:
#line 317 "src/gramatica.y"
	{ yyval.tipo_dato = TIPO_INTEGER; }
#line 1852 "y.tab.c"
break;
case 17:
#line 318 "src/gramatica.y"
	{ yyval.tipo_dato = TIPO_SINGLEF; }
#line 1857 "y.tab.c"
break;
case 18:
#line 323 "src/gramatica.y"
	{
        for (int i = 0; i < cant_vars_declaradas; i++) {
            declarar_identificador(
                obtener_tabla_simbolos(),
                lista_vars_declaradas[i]->lexema,
                ID,
                yystack.l_mark[-1].tipo_dato,
                USO_VARIABLE,
                yylineno
            );
            if (clase_actual_declaracion != NULL) {
                AtributoClase *at = calloc(1, sizeof(AtributoClase));
                at->nombre = strdup(lista_vars_declaradas[i]->lexema);
                at->tipo = yystack.l_mark[-1].tipo_dato;
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
#line 1888 "y.tab.c"
break;
case 19:
#line 354 "src/gramatica.y"
	{
        if (cant_vars_declaradas < 64) {
            lista_vars_declaradas[cant_vars_declaradas++] = yystack.l_mark[0].simbolo;
        }
    }
#line 1897 "y.tab.c"
break;
case 20:
#line 360 "src/gramatica.y"
	{
        cant_vars_declaradas = 0;
        if (cant_vars_declaradas < 64) {
            lista_vars_declaradas[cant_vars_declaradas++] = yystack.l_mark[0].simbolo;
        }
    }
#line 1907 "y.tab.c"
break;
case 21:
#line 370 "src/gramatica.y"
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
            if (obj && yystack.l_mark[-1].simbolo) {
                obj->tipo_clase = strdup(yystack.l_mark[-1].simbolo->lexema);
            }
        }
        cant_vars_declaradas = 0;
    }
#line 1927 "y.tab.c"
break;
case 22:
#line 390 "src/gramatica.y"
	{
        if (tope_fn_decl > 0) tope_fn_decl--;
        polaca_desapilar_actual();
        salir_ambito();
    }
#line 1936 "y.tab.c"
break;
case 23:
#line 396 "src/gramatica.y"
	{
        if (tope_fn_decl > 0) tope_fn_decl--;
        polaca_desapilar_actual();
        salir_ambito();
    }
#line 1945 "y.tab.c"
break;
case 24:
#line 402 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
#line 1950 "y.tab.c"
break;
case 25:
#line 404 "src/gramatica.y"
	{ yyerror("Error: Faltan los parametros de la función."); yyerrok; }
#line 1955 "y.tab.c"
break;
case 26:
#line 409 "src/gramatica.y"
	{
        Simbolo *fn = declarar_identificador(
            obtener_tabla_simbolos(),
            yystack.l_mark[-1].simbolo->lexema,
            ID,
            yystack.l_mark[-3].tipo_dato,
            USO_FUNCION,
            yylineno
        );
        if (fn && tope_fn_decl < 32) {
            pila_fn_decl[tope_fn_decl++] = fn;
        }
        entrar_ambito(yystack.l_mark[-1].simbolo->lexema);
        char *mangled = construir_mangled_name(yystack.l_mark[-1].simbolo->lexema, obtener_ambito_actual());
        Polaca *pf = crear_polaca(mangled);
        free(mangled);
        polaca_apilar_actual(pf);
    }
#line 1977 "y.tab.c"
break;
case 27:
#line 431 "src/gramatica.y"
	{
        Simbolo *fn = declarar_identificador(
            obtener_tabla_simbolos(),
            yystack.l_mark[-1].simbolo->lexema,
            ID,
            yystack.l_mark[-2].tipo_dato,
            USO_FUNCION,
            yylineno
        );
        if (fn && tope_fn_decl < 32) {
            pila_fn_decl[tope_fn_decl++] = fn;
        }
        entrar_ambito(yystack.l_mark[-1].simbolo->lexema);
        char *mangled = construir_mangled_name(yystack.l_mark[-1].simbolo->lexema, obtener_ambito_actual());
        Polaca *pf = crear_polaca(mangled);
        free(mangled);
        polaca_apilar_actual(pf);
    }
#line 1999 "y.tab.c"
break;
case 29:
#line 454 "src/gramatica.y"
	{ yyerror("Error: Falta de ',' en declaración de parámetros."); yyerrok; }
#line 2004 "y.tab.c"
break;
case 31:
#line 460 "src/gramatica.y"
	{
        declarar_identificador(
            obtener_tabla_simbolos(),
            yystack.l_mark[0].simbolo->lexema,
            ID,
            yystack.l_mark[-1].tipo_dato,
            USO_PARAMETRO,
            yylineno
        );
        if (tope_fn_decl > 0 && pila_fn_decl[tope_fn_decl - 1] != NULL) {
            Simbolo *fn = pila_fn_decl[tope_fn_decl - 1];
            ParametroFormal *pf = calloc(1, sizeof(ParametroFormal));
            pf->nombre = strdup(yystack.l_mark[0].simbolo->lexema);
            pf->tipo = yystack.l_mark[-1].tipo_dato;
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
#line 2033 "y.tab.c"
break;
case 32:
#line 486 "src/gramatica.y"
	{
        Simbolo *p_sym = declarar_identificador(
            obtener_tabla_simbolos(),
            yystack.l_mark[0].simbolo->lexema,
            ID,
            yystack.l_mark[-1].tipo_dato,
            USO_VARIABLE_COMPTIME,
            yylineno
        );
        if (p_sym != NULL) {
            p_sym->valor_comptime_valido = true;
        }
        if (tope_fn_decl > 0 && pila_fn_decl[tope_fn_decl - 1] != NULL) {
            Simbolo *fn = pila_fn_decl[tope_fn_decl - 1];
            ParametroFormal *pf = calloc(1, sizeof(ParametroFormal));
            pf->nombre = strdup(yystack.l_mark[0].simbolo->lexema);
            pf->tipo = yystack.l_mark[-1].tipo_dato;
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
#line 2066 "y.tab.c"
break;
case 33:
#line 516 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
#line 2071 "y.tab.c"
break;
case 34:
#line 520 "src/gramatica.y"
	{
        Simbolo *cls = declarar_identificador(
            obtener_tabla_simbolos(),
            yystack.l_mark[0].simbolo->lexema,
            CLASS,
            TIPO_CLASE,
            USO_CLASE,
            yylineno
        );
        clase_actual_declaracion = cls;
        entrar_ambito(yystack.l_mark[0].simbolo->lexema);
    }
#line 2087 "y.tab.c"
break;
case 35:
#line 532 "src/gramatica.y"
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
#line 2116 "y.tab.c"
break;
case 36:
#line 561 "src/gramatica.y"
	{
        if (clase_actual_declaracion != NULL) {
            clase_actual_declaracion->codigo_clase = strdup(yystack.l_mark[0].simbolo->lexema);
        }
    }
#line 2125 "y.tab.c"
break;
case 37:
#line 566 "src/gramatica.y"
	{ yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
#line 2130 "y.tab.c"
break;
case 38:
#line 571 "src/gramatica.y"
	{
        if (cant_padres_declarados < 16) {
            lista_padres_declarados[cant_padres_declarados++] = strdup(yystack.l_mark[0].simbolo->lexema);
        }
    }
#line 2139 "y.tab.c"
break;
case 39:
#line 577 "src/gramatica.y"
	{
        cant_padres_declarados = 0;
        if (cant_padres_declarados < 16) {
            lista_padres_declarados[cant_padres_declarados++] = strdup(yystack.l_mark[0].simbolo->lexema);
        }
    }
#line 2149 "y.tab.c"
break;
case 40:
#line 587 "src/gramatica.y"
	{
        cant_padres_declarados = 0;
    }
#line 2156 "y.tab.c"
break;
case 41:
#line 591 "src/gramatica.y"
	{
        if (clase_actual_declaracion != NULL && cant_padres_declarados > 0) {
            clase_actual_declaracion->clases_padre = malloc(cant_padres_declarados * sizeof(char *));
            clase_actual_declaracion->cant_padres = cant_padres_declarados;
            for (int p = 0; p < cant_padres_declarados; p++) {
                clase_actual_declaracion->clases_padre[p] = lista_padres_declarados[p];
                Simbolo *padre = buscar_identificador_semantico(obtener_tabla_simbolos(), lista_padres_declarados[p]);
                if (!padre || padre->uso != USO_CLASE) {
                    registrar_error(ETAPA_SEMANTICO, yylineno, "La clase base '%s' no está declarada o no es una clase válida.", lista_padres_declarados[p]);
                }
            }
        }
        cant_padres_declarados = 0;
    }
#line 2174 "y.tab.c"
break;
case 42:
#line 606 "src/gramatica.y"
	{ yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
#line 2179 "y.tab.c"
break;
case 48:
#line 622 "src/gramatica.y"
	{
        if (clase_actual_declaracion != NULL && cant_padres_declarados > 0) {
            clase_actual_declaracion->clases_padre = malloc(cant_padres_declarados * sizeof(char *));
            clase_actual_declaracion->cant_padres = cant_padres_declarados;
            for (int p = 0; p < cant_padres_declarados; p++) {
                clase_actual_declaracion->clases_padre[p] = lista_padres_declarados[p];
                Simbolo *padre = buscar_identificador_semantico(obtener_tabla_simbolos(), lista_padres_declarados[p]);
                if (!padre || padre->uso != USO_CLASE) {
                    registrar_error(ETAPA_SEMANTICO, yylineno, "La clase base '%s' no está declarada o no es una clase válida.", lista_padres_declarados[p]);
                }
            }
        }
        cant_padres_declarados = 0;
    }
#line 2197 "y.tab.c"
break;
case 50:
#line 641 "src/gramatica.y"
	{ yyerror("Error: Falta de delimitador de sentencias ejecutables BEGIN."); yyerrok; }
#line 2202 "y.tab.c"
break;
case 53:
#line 648 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 2207 "y.tab.c"
break;
case 54:
#line 650 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 2212 "y.tab.c"
break;
case 60:
#line 663 "src/gramatica.y"
	{
        polaca_emitir_operador("RET", yylineno);
    }
#line 2219 "y.tab.c"
break;
case 61:
#line 667 "src/gramatica.y"
	{
        polaca_emitir_operador("RET", yylineno);
    }
#line 2226 "y.tab.c"
break;
case 62:
#line 674 "src/gramatica.y"
	{
        Simbolo *dest = yystack.l_mark[-2].simbolo;
        if (dest != NULL) {
            validar_compatibilidad_asignacion(dest, yystack.l_mark[0].info_expr.tipo, yystack.l_mark[0].info_expr.es_comptime, yystack.l_mark[0].info_expr.val_int, yystack.l_mark[0].info_expr.val_float, yylineno);

            if (dest->uso == USO_OBJETO) {
                Simbolo *orig = yystack.l_mark[0].info_expr.simbolo_ref;
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
#line 2261 "y.tab.c"
break;
case 63:
#line 706 "src/gramatica.y"
	{ yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
#line 2266 "y.tab.c"
break;
case 64:
#line 711 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[0].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[0].simbolo->lexema);
            s = yystack.l_mark[0].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
        yyval.simbolo = s;
    }
#line 2279 "y.tab.c"
break;
case 65:
#line 721 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-2].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Objeto '%s' no declarado o fuera de alcance.", yystack.l_mark[-2].simbolo->lexema);
            s = yystack.l_mark[-2].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
        polaca_emitir_operador(yystack.l_mark[0].simbolo->lexema, yylineno);
        polaca_emitir_operador(".", yylineno);

        Simbolo *res_sym = s;
        if (s && s->uso == USO_OBJETO && s->tipo_clase) {
            Simbolo *cls = buscar_identificador_semantico(obtener_tabla_simbolos(), s->tipo_clase);
            if (cls) {
                ResultadoBusquedaMiembro res_m;
                if (resolver_miembro_herencia(obtener_tabla_simbolos(), cls, yystack.l_mark[0].simbolo->lexema, yylineno, &res_m)) {
                    res_sym = calloc(1, sizeof(Simbolo));
                    *res_sym = *s;
                    res_sym->tipo = res_m.tipo;
                }
            }
        }
        yyval.simbolo = res_sym;
    }
#line 2307 "y.tab.c"
break;
case 66:
#line 746 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-3].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[-3].simbolo->lexema);
            s = yystack.l_mark[-3].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
        polaca_emitir_operador("[]", yylineno);

        Simbolo *res_sym = s;
        if (s && s->uso == USO_OBJETO && s->tipo_clase) {
            Simbolo *cls = buscar_identificador_semantico(obtener_tabla_simbolos(), s->tipo_clase);
            if (cls) {
                if (yystack.l_mark[-1].info_expr.tipo != TIPO_INTEGER && yystack.l_mark[-1].info_expr.tipo != TIPO_NO_ASIGNADO) {
                    registrar_error(ETAPA_SEMANTICO, yylineno, "El índice de acceso posicional del objeto '%s' debe ser INTEGER.", yystack.l_mark[-3].simbolo->lexema);
                } else if (yystack.l_mark[-1].info_expr.es_comptime) {
                    long idx = yystack.l_mark[-1].info_expr.val_int;
                    if (idx < 0 || idx >= cls->cant_atributos) {
                        registrar_error(
                            ETAPA_SEMANTICO,
                            yylineno,
                            "Índice de atributo %ld fuera de rango [0..%d] en objeto '%s' (clase '%s').",
                            idx,
                            cls->cant_atributos > 0 ? cls->cant_atributos - 1 : 0,
                            s->nombre_original ? s->nombre_original : s->lexema,
                            s->tipo_clase
                        );
                    } else {
                        AtributoClase *at = cls->atributos;
                        for (long a = 0; a < idx && at != NULL; a++) {
                            at = at->siguiente;
                        }
                        if (at != NULL) {
                            res_sym = calloc(1, sizeof(Simbolo));
                            *res_sym = *s;
                            res_sym->tipo = at->tipo;
                        }
                    }
                }
            }
        }
        yyval.simbolo = res_sym;
    }
#line 2354 "y.tab.c"
break;
case 67:
#line 793 "src/gramatica.y"
	{
        polaca_emitir_operador("POUT", yylineno);
    }
#line 2361 "y.tab.c"
break;
case 68:
#line 797 "src/gramatica.y"
	{
        polaca_emitir_simbolo(yystack.l_mark[-1].simbolo, yylineno);
        polaca_emitir_operador("POUT", yylineno);
    }
#line 2369 "y.tab.c"
break;
case 69:
#line 802 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 2374 "y.tab.c"
break;
case 70:
#line 804 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 2379 "y.tab.c"
break;
case 71:
#line 809 "src/gramatica.y"
	{
        polaca_emitir_operador("+", yylineno);
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = (yystack.l_mark[-2].info_expr.tipo == TIPO_SINGLEF || yystack.l_mark[0].info_expr.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
        if (yystack.l_mark[-2].info_expr.tipo != TIPO_NO_ASIGNADO && yystack.l_mark[0].info_expr.tipo != TIPO_NO_ASIGNADO && yystack.l_mark[-2].info_expr.tipo != yystack.l_mark[0].info_expr.tipo) {
            registrar_error(
                ETAPA_SEMANTICO,
                yylineno,
                "Tipos incompatibles en operación aritmética: no se puede operar entre '%s' y '%s' sin conversión explícita TOSF.",
                tipo_dato_a_string(yystack.l_mark[-2].info_expr.tipo),
                tipo_dato_a_string(yystack.l_mark[0].info_expr.tipo)
            );
        }
        if (yystack.l_mark[-2].info_expr.es_comptime && yystack.l_mark[0].info_expr.es_comptime) {
            yyval.info_expr.es_comptime = true;
            if (yyval.info_expr.tipo == TIPO_INTEGER) {
                yyval.info_expr.val_int = yystack.l_mark[-2].info_expr.val_int + yystack.l_mark[0].info_expr.val_int;
                yyval.info_expr.val_float = (double)yyval.info_expr.val_int;
            } else {
                yyval.info_expr.val_float = yystack.l_mark[-2].info_expr.val_float + yystack.l_mark[0].info_expr.val_float;
                yyval.info_expr.val_int = (long)yyval.info_expr.val_float;
            }
        } else {
            yyval.info_expr.es_comptime = false;
        }
    }
#line 2409 "y.tab.c"
break;
case 72:
#line 836 "src/gramatica.y"
	{
        polaca_emitir_operador("-", yylineno);
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = (yystack.l_mark[-2].info_expr.tipo == TIPO_SINGLEF || yystack.l_mark[0].info_expr.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
        if (yystack.l_mark[-2].info_expr.tipo != TIPO_NO_ASIGNADO && yystack.l_mark[0].info_expr.tipo != TIPO_NO_ASIGNADO && yystack.l_mark[-2].info_expr.tipo != yystack.l_mark[0].info_expr.tipo) {
            registrar_error(
                ETAPA_SEMANTICO,
                yylineno,
                "Tipos incompatibles en operación aritmética: no se puede operar entre '%s' y '%s' sin conversión explícita TOSF.",
                tipo_dato_a_string(yystack.l_mark[-2].info_expr.tipo),
                tipo_dato_a_string(yystack.l_mark[0].info_expr.tipo)
            );
        }
        if (yystack.l_mark[-2].info_expr.es_comptime && yystack.l_mark[0].info_expr.es_comptime) {
            yyval.info_expr.es_comptime = true;
            if (yyval.info_expr.tipo == TIPO_INTEGER) {
                yyval.info_expr.val_int = yystack.l_mark[-2].info_expr.val_int - yystack.l_mark[0].info_expr.val_int;
                yyval.info_expr.val_float = (double)yyval.info_expr.val_int;
            } else {
                yyval.info_expr.val_float = yystack.l_mark[-2].info_expr.val_float - yystack.l_mark[0].info_expr.val_float;
                yyval.info_expr.val_int = (long)yyval.info_expr.val_float;
            }
        } else {
            yyval.info_expr.es_comptime = false;
        }
    }
#line 2439 "y.tab.c"
break;
case 73:
#line 863 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '+'."); yyerrok; yyval.info_expr.es_comptime = false; }
#line 2444 "y.tab.c"
break;
case 74:
#line 865 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '-'."); yyerrok; yyval.info_expr.es_comptime = false; }
#line 2449 "y.tab.c"
break;
case 75:
#line 867 "src/gramatica.y"
	{
        yyval.info_expr = yystack.l_mark[0].info_expr;
    }
#line 2456 "y.tab.c"
break;
case 76:
#line 874 "src/gramatica.y"
	{
        polaca_emitir_operador("*", yylineno);
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = (yystack.l_mark[-2].info_expr.tipo == TIPO_SINGLEF || yystack.l_mark[0].info_expr.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
        if (yystack.l_mark[-2].info_expr.tipo != TIPO_NO_ASIGNADO && yystack.l_mark[0].info_expr.tipo != TIPO_NO_ASIGNADO && yystack.l_mark[-2].info_expr.tipo != yystack.l_mark[0].info_expr.tipo) {
            registrar_error(
                ETAPA_SEMANTICO,
                yylineno,
                "Tipos incompatibles en operación aritmética: no se puede operar entre '%s' y '%s' sin conversión explícita TOSF.",
                tipo_dato_a_string(yystack.l_mark[-2].info_expr.tipo),
                tipo_dato_a_string(yystack.l_mark[0].info_expr.tipo)
            );
        }
        if (yystack.l_mark[-2].info_expr.es_comptime && yystack.l_mark[0].info_expr.es_comptime) {
            yyval.info_expr.es_comptime = true;
            if (yyval.info_expr.tipo == TIPO_INTEGER) {
                yyval.info_expr.val_int = yystack.l_mark[-2].info_expr.val_int * yystack.l_mark[0].info_expr.val_int;
                yyval.info_expr.val_float = (double)yyval.info_expr.val_int;
            } else {
                yyval.info_expr.val_float = yystack.l_mark[-2].info_expr.val_float * yystack.l_mark[0].info_expr.val_float;
                yyval.info_expr.val_int = (long)yyval.info_expr.val_float;
            }
        } else {
            yyval.info_expr.es_comptime = false;
        }
    }
#line 2486 "y.tab.c"
break;
case 77:
#line 901 "src/gramatica.y"
	{
        polaca_emitir_operador("/", yylineno);
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = (yystack.l_mark[-2].info_expr.tipo == TIPO_SINGLEF || yystack.l_mark[0].info_expr.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
        if (yystack.l_mark[-2].info_expr.tipo != TIPO_NO_ASIGNADO && yystack.l_mark[0].info_expr.tipo != TIPO_NO_ASIGNADO && yystack.l_mark[-2].info_expr.tipo != yystack.l_mark[0].info_expr.tipo) {
            registrar_error(
                ETAPA_SEMANTICO,
                yylineno,
                "Tipos incompatibles en operación aritmética: no se puede operar entre '%s' y '%s' sin conversión explícita TOSF.",
                tipo_dato_a_string(yystack.l_mark[-2].info_expr.tipo),
                tipo_dato_a_string(yystack.l_mark[0].info_expr.tipo)
            );
        }
        if (yystack.l_mark[-2].info_expr.es_comptime && yystack.l_mark[0].info_expr.es_comptime) {
            if ((yyval.info_expr.tipo == TIPO_INTEGER && yystack.l_mark[0].info_expr.val_int == 0) || (yyval.info_expr.tipo == TIPO_SINGLEF && yystack.l_mark[0].info_expr.val_float == 0.0)) {
                registrar_error(ETAPA_SEMANTICO, yylineno, "División por cero en evaluación de expresión COMPTIME.");
                yyval.info_expr.es_comptime = false;
            } else {
                yyval.info_expr.es_comptime = true;
                if (yyval.info_expr.tipo == TIPO_INTEGER) {
                    yyval.info_expr.val_int = yystack.l_mark[-2].info_expr.val_int / yystack.l_mark[0].info_expr.val_int;
                    yyval.info_expr.val_float = (double)yyval.info_expr.val_int;
                } else {
                    yyval.info_expr.val_float = yystack.l_mark[-2].info_expr.val_float / yystack.l_mark[0].info_expr.val_float;
                    yyval.info_expr.val_int = (long)yyval.info_expr.val_float;
                }
            }
        } else {
            yyval.info_expr.es_comptime = false;
        }
    }
#line 2521 "y.tab.c"
break;
case 78:
#line 933 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '*'."); yyerrok; yyval.info_expr.es_comptime = false; }
#line 2526 "y.tab.c"
break;
case 79:
#line 935 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '/'."); yyerrok; yyval.info_expr.es_comptime = false; }
#line 2531 "y.tab.c"
break;
case 80:
#line 937 "src/gramatica.y"
	{
        yyval.info_expr = yystack.l_mark[0].info_expr;
    }
#line 2538 "y.tab.c"
break;
case 81:
#line 944 "src/gramatica.y"
	{
        yyval.info_expr = yystack.l_mark[0].info_expr;
    }
#line 2545 "y.tab.c"
break;
case 82:
#line 947 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-2].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[-2].simbolo->lexema);
            s = yystack.l_mark[-2].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
    }
#line 2557 "y.tab.c"
break;
case 83:
#line 955 "src/gramatica.y"
	{
        polaca_emitir_operador(":=", yylineno);
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-5].simbolo->lexema);
        polaca_emitir_simbolo(s ? s : yystack.l_mark[-5].simbolo, yylineno);
        validar_compatibilidad_asignacion(s, yystack.l_mark[-1].info_expr.tipo, yystack.l_mark[-1].info_expr.es_comptime, yystack.l_mark[-1].info_expr.val_int, yystack.l_mark[-1].info_expr.val_float, yylineno);
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.simbolo_ref = s;
        yyval.info_expr.tipo = s ? s->tipo : yystack.l_mark[-1].info_expr.tipo;
    }
#line 2570 "y.tab.c"
break;
case 84:
#line 968 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[0].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[0].simbolo->lexema);
            s = yystack.l_mark[0].simbolo;
        }
        yyval.info_expr.simbolo_ref = s;
        yyval.info_expr.tipo = s ? s->tipo : TIPO_NO_ASIGNADO;
        if (s != NULL && s->uso == USO_VARIABLE_COMPTIME) {
            if (!s->valor_comptime_valido) {
                registrar_error(ETAPA_SEMANTICO, yylineno, "La variable COMPTIME '%s' se utiliza antes de haber sido inicializada.", yystack.l_mark[0].simbolo->lexema);
                yyval.info_expr.es_comptime = false;
                polaca_emitir_simbolo(s, yylineno);
            } else {
                yyval.info_expr.es_comptime = true;
                yyval.info_expr.val_int = s->valor_int;
                yyval.info_expr.val_float = s->valor_float;
                char buf_cte[64];
                if (s->tipo == TIPO_SINGLEF) {
                    snprintf(buf_cte, sizeof(buf_cte), "%g", s->valor_float);
                    Simbolo *c_sym = insertar_simbolo(obtener_tabla_simbolos(), buf_cte, CTE_FLOAT);
                    if (c_sym) {
                        c_sym->tipo = TIPO_SINGLEF;
                        c_sym->uso = USO_CONSTANTE;
                    }
                    polaca_emitir_simbolo(c_sym ? c_sym : s, yylineno);
                } else {
                    snprintf(buf_cte, sizeof(buf_cte), "%ld$i", s->valor_int);
                    Simbolo *c_sym = insertar_simbolo(obtener_tabla_simbolos(), buf_cte, CTE);
                    if (c_sym) {
                        c_sym->tipo = TIPO_INTEGER;
                        c_sym->uso = USO_CONSTANTE;
                    }
                    polaca_emitir_simbolo(c_sym ? c_sym : s, yylineno);
                }
            }
        } else {
            yyval.info_expr.es_comptime = false;
            polaca_emitir_simbolo(s, yylineno);
        }
    }
#line 2615 "y.tab.c"
break;
case 85:
#line 1010 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-2].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Objeto '%s' no declarado o fuera de alcance.", yystack.l_mark[-2].simbolo->lexema);
            s = yystack.l_mark[-2].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
        polaca_emitir_operador(yystack.l_mark[0].simbolo->lexema, yylineno);
        polaca_emitir_operador(".", yylineno);
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.simbolo_ref = s;
        yyval.info_expr.tipo = TIPO_NO_ASIGNADO;

        if (s && s->uso == USO_OBJETO && s->tipo_clase) {
            Simbolo *cls = buscar_identificador_semantico(obtener_tabla_simbolos(), s->tipo_clase);
            if (cls) {
                ResultadoBusquedaMiembro res_m;
                if (resolver_miembro_herencia(obtener_tabla_simbolos(), cls, yystack.l_mark[0].simbolo->lexema, yylineno, &res_m)) {
                    yyval.info_expr.tipo = res_m.tipo;
                }
            }
        }
    }
#line 2642 "y.tab.c"
break;
case 86:
#line 1034 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-3].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[-3].simbolo->lexema);
            s = yystack.l_mark[-3].simbolo;
        }
        polaca_emitir_simbolo(s ? s : yystack.l_mark[-3].simbolo, yylineno);
        polaca_emitir_operador("[]", yylineno);
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.simbolo_ref = s;
        yyval.info_expr.tipo = s ? s->tipo : TIPO_NO_ASIGNADO;

        if (s && s->uso == USO_OBJETO && s->tipo_clase) {
            Simbolo *cls = buscar_identificador_semantico(obtener_tabla_simbolos(), s->tipo_clase);
            if (cls) {
                if (yystack.l_mark[-1].info_expr.tipo != TIPO_INTEGER && yystack.l_mark[-1].info_expr.tipo != TIPO_NO_ASIGNADO) {
                    registrar_error(ETAPA_SEMANTICO, yylineno, "El índice de acceso posicional del objeto '%s' debe ser INTEGER.", yystack.l_mark[-3].simbolo->lexema);
                } else if (yystack.l_mark[-1].info_expr.es_comptime) {
                    long idx = yystack.l_mark[-1].info_expr.val_int;
                    if (idx < 0 || idx >= cls->cant_atributos) {
                        registrar_error(
                            ETAPA_SEMANTICO,
                            yylineno,
                            "Índice de atributo %ld fuera de rango [0..%d] en objeto '%s' (clase '%s').",
                            idx,
                            cls->cant_atributos > 0 ? cls->cant_atributos - 1 : 0,
                            s->nombre_original ? s->nombre_original : s->lexema,
                            s->tipo_clase
                        );
                    } else {
                        AtributoClase *at = cls->atributos;
                        for (long a = 0; a < idx && at != NULL; a++) {
                            at = at->siguiente;
                        }
                        if (at != NULL) {
                            yyval.info_expr.tipo = at->tipo;
                        }
                    }
                }
            }
        }
    }
#line 2688 "y.tab.c"
break;
case 87:
#line 1077 "src/gramatica.y"
	{
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = TIPO_NO_ASIGNADO;
    }
#line 2697 "y.tab.c"
break;
case 88:
#line 1083 "src/gramatica.y"
	{
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = TIPO_NO_ASIGNADO;
    }
#line 2706 "y.tab.c"
break;
case 89:
#line 1089 "src/gramatica.y"
	{
        polaca_emitir_operador("TOSF", yylineno);
        yyval.info_expr.es_comptime = yystack.l_mark[-1].info_expr.es_comptime;
        yyval.info_expr.tipo = TIPO_SINGLEF;
        yyval.info_expr.val_float = yystack.l_mark[-1].info_expr.es_comptime ? (double)yystack.l_mark[-1].info_expr.val_int : 0.0;
        yyval.info_expr.val_int = (long)yyval.info_expr.val_float;
        yyval.info_expr.simbolo_ref = NULL;
    }
#line 2718 "y.tab.c"
break;
case 90:
#line 1098 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            polaca_emitir_simbolo(yystack.l_mark[0].simbolo, yylineno);
            yyval.info_expr.es_comptime = true;
            yyval.info_expr.simbolo_ref = yystack.l_mark[0].simbolo;
            yyval.info_expr.tipo = yystack.l_mark[0].simbolo->tipo;
            if (yystack.l_mark[0].simbolo->tipo == TIPO_INTEGER) {
                yyval.info_expr.val_int = parsear_valor_entero(yystack.l_mark[0].simbolo->lexema);
                yyval.info_expr.val_float = (double)yyval.info_expr.val_int;
            } else {
                yyval.info_expr.val_float = atof(yystack.l_mark[0].simbolo->lexema);
                yyval.info_expr.val_int = (long)yyval.info_expr.val_float;
            }
        } else {
            yyval.info_expr.es_comptime = false;
            yyval.info_expr.simbolo_ref = NULL;
            yyval.info_expr.tipo = TIPO_NO_ASIGNADO;
        }
    }
#line 2741 "y.tab.c"
break;
case 91:
#line 1121 "src/gramatica.y"
	{
        finalizar_invocacion_con_orden();
    }
#line 2748 "y.tab.c"
break;
case 92:
#line 1125 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 2753 "y.tab.c"
break;
case 93:
#line 1130 "src/gramatica.y"
	{
        iniciar_invocacion(yystack.l_mark[-1].simbolo->lexema, yylineno);
    }
#line 2760 "y.tab.c"
break;
case 94:
#line 1137 "src/gramatica.y"
	{
        finalizar_invocacion_con_orden();
    }
#line 2767 "y.tab.c"
break;
case 95:
#line 1141 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 2772 "y.tab.c"
break;
case 96:
#line 1146 "src/gramatica.y"
	{
        Simbolo *obj = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-3].simbolo->lexema);
        if (!obj || obj->uso != USO_OBJETO) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "El identificador '%s' no es un objeto válido.", yystack.l_mark[-3].simbolo->lexema);
        } else if (obj->tipo_clase) {
            Simbolo *cls = buscar_identificador_semantico(obtener_tabla_simbolos(), obj->tipo_clase);
            if (cls) {
                ResultadoBusquedaMiembro res_m;
                resolver_miembro_herencia(obtener_tabla_simbolos(), cls, yystack.l_mark[-1].simbolo->lexema, yylineno, &res_m);
            }
        }
        iniciar_invocacion(yystack.l_mark[-1].simbolo->lexema, yylineno);
    }
#line 2789 "y.tab.c"
break;
case 98:
#line 1164 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 2794 "y.tab.c"
break;
case 99:
#line 1169 "src/gramatica.y"
	{
        long val = parsear_valor_entero(yystack.l_mark[0].simbolo ? yystack.l_mark[0].simbolo->lexema : "0");
        agregar_orden_invocacion((int)val);
    }
#line 2802 "y.tab.c"
break;
case 101:
#line 1175 "src/gramatica.y"
	{
        long val = parsear_valor_entero(yystack.l_mark[0].simbolo ? yystack.l_mark[0].simbolo->lexema : "0");
        agregar_orden_invocacion((int)val);
    }
#line 2810 "y.tab.c"
break;
case 106:
#line 1193 "src/gramatica.y"
	{
        if (tope_invocaciones > 0) {
            Invocacion *inv = &pila_invocaciones[tope_invocaciones - 1];
            Polaca *p = obtener_polaca_actual();
            polaca_desapilar_actual();
            if (inv->cant_args < 16) {
                inv->args_polaca[inv->cant_args] = p;
                inv->args_comptime[inv->cant_args] = yystack.l_mark[0].info_expr.es_comptime;
                inv->cant_args++;
            }
        }
    }
#line 2826 "y.tab.c"
break;
case 107:
#line 1209 "src/gramatica.y"
	{
        Polaca *p = crear_polaca("param_tmp");
        polaca_apilar_actual(p);
    }
#line 2834 "y.tab.c"
break;
case 108:
#line 1217 "src/gramatica.y"
	{
        yyval.info_expr = yystack.l_mark[0].info_expr;
    }
#line 2841 "y.tab.c"
break;
case 109:
#line 1220 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-1].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[-1].simbolo->lexema);
            s = yystack.l_mark[-1].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
    }
#line 2853 "y.tab.c"
break;
case 110:
#line 1228 "src/gramatica.y"
	{
        polaca_emitir_operador(":=", yylineno);
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-3].simbolo->lexema);
        polaca_emitir_simbolo(s ? s : yystack.l_mark[-3].simbolo, yylineno);
        validar_compatibilidad_asignacion(s, yystack.l_mark[0].info_expr.tipo, yystack.l_mark[0].info_expr.es_comptime, yystack.l_mark[0].info_expr.val_int, yystack.l_mark[0].info_expr.val_float, yylineno);
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.tipo = yystack.l_mark[0].info_expr.tipo;
        yyval.info_expr.simbolo_ref = s;
    }
#line 2866 "y.tab.c"
break;
case 111:
#line 1241 "src/gramatica.y"
	{ cant_errores++; }
#line 2871 "y.tab.c"
break;
case 112:
#line 1243 "src/gramatica.y"
	{ cant_errores++; }
#line 2876 "y.tab.c"
break;
case 113:
#line 1248 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2883 "y.tab.c"
break;
case 114:
#line 1252 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2890 "y.tab.c"
break;
case 115:
#line 1256 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2897 "y.tab.c"
break;
case 116:
#line 1260 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2904 "y.tab.c"
break;
case 117:
#line 1264 "src/gramatica.y"
	{
        yyval.simbolo = (yystack.l_mark[0].simbolo != NULL) ? cambiar_signo_constante(yystack.l_mark[0].simbolo, -1) : NULL;
    }
#line 2911 "y.tab.c"
break;
case 118:
#line 1268 "src/gramatica.y"
	{
        yyval.simbolo = (yystack.l_mark[0].simbolo != NULL) ? cambiar_signo_constante(yystack.l_mark[0].simbolo, -1) : NULL;
    }
#line 2918 "y.tab.c"
break;
case 119:
#line 1272 "src/gramatica.y"
	{
        yyval.simbolo = NULL;
    }
#line 2925 "y.tab.c"
break;
case 120:
#line 1276 "src/gramatica.y"
	{
        yyval.simbolo = NULL;
    }
#line 2932 "y.tab.c"
break;
case 121:
#line 1280 "src/gramatica.y"
	{
        yyval.simbolo = NULL;
    }
#line 2939 "y.tab.c"
break;
case 123:
#line 1288 "src/gramatica.y"
	{ yyerror("Error: Estructura IF mal cerrada (posiblemente falta END_IF o el delimitador ';')."); yyerrok; }
#line 2944 "y.tab.c"
break;
case 124:
#line 1290 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
#line 2949 "y.tab.c"
break;
case 125:
#line 1292 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
#line 2954 "y.tab.c"
break;
case 126:
#line 1297 "src/gramatica.y"
	{
        if (tope_condicion < 32) {
            pila_condicion_comptime[tope_condicion++] = ultima_condicion_comptime;
        }
        if (!ultima_condicion_comptime) {
            anidamiento_control_no_comptime++;
        }
        int celda_bf = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BF", yylineno);
        polaca_apilar_salto(celda_bf);
    }
#line 2969 "y.tab.c"
break;
case 127:
#line 1312 "src/gramatica.y"
	{
        if (tope_condicion > 0) {
            bool c_comp = pila_condicion_comptime[--tope_condicion];
            if (!c_comp) {
                anidamiento_control_no_comptime--;
            }
        }
        int celda_bi = polaca_desapilar_salto();
        polaca_poner_destino(celda_bi, polaca_posicion_actual());
    }
#line 2983 "y.tab.c"
break;
case 128:
#line 1323 "src/gramatica.y"
	{
        if (tope_condicion > 0) {
            bool c_comp = pila_condicion_comptime[--tope_condicion];
            if (!c_comp) {
                anidamiento_control_no_comptime--;
            }
        }
        int celda_bf = polaca_desapilar_salto();
        polaca_poner_destino(celda_bf, polaca_posicion_actual());
    }
#line 2997 "y.tab.c"
break;
case 129:
#line 1337 "src/gramatica.y"
	{
        int celda_bi = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BI", yylineno);
        int celda_bf = polaca_desapilar_salto();
        polaca_poner_destino(celda_bf, polaca_posicion_actual());
        polaca_apilar_salto(celda_bi);
    }
#line 3008 "y.tab.c"
break;
case 132:
#line 1353 "src/gramatica.y"
	{
        if (tope_from > 0) {
            ContextoFrom ctx = pila_from[--tope_from];

            polaca_emitir_simbolo(ctx.id_control, yylineno);
            polaca_emitir_simbolo(ctx.id_control, yylineno);
            polaca_emitir_simbolo(ctx.cte3_sym, yylineno);
            polaca_emitir_operador(ctx.ascendente ? "+" : "-", yylineno);
            polaca_emitir_operador(":=", yylineno);

            int celda_bi = polaca_emitir_celda_vacia(yylineno);
            polaca_poner_destino(celda_bi, ctx.pos_inicio_prueba);
            polaca_emitir_operador("BI", yylineno);

            polaca_poner_destino(ctx.celda_bf, polaca_posicion_actual());
        }
    }
#line 3029 "y.tab.c"
break;
case 135:
#line 1379 "src/gramatica.y"
	{
        Simbolo *id_sym = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-6].simbolo->lexema);
        if (!id_sym) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable de control '%s' no declarada o fuera de alcance.", yystack.l_mark[-6].simbolo->lexema);
            id_sym = yystack.l_mark[-6].simbolo;
        } else if (id_sym->tipo != TIPO_INTEGER) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "La variable de control '%s' del ciclo FROM debe ser de tipo INTEGER.", yystack.l_mark[-6].simbolo->lexema);
        }

        Simbolo *c1 = yystack.l_mark[-4].simbolo;
        Simbolo *c2 = yystack.l_mark[-2].simbolo;
        Simbolo *c3 = yystack.l_mark[0].simbolo;

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

        polaca_emitir_simbolo(id_sym, yylineno);
        polaca_emitir_simbolo(c1, yylineno);
        polaca_emitir_operador(":=", yylineno);

        int pos_prueba = polaca_posicion_actual();

        polaca_emitir_simbolo(id_sym, yylineno);
        polaca_emitir_simbolo(c2, yylineno);
        polaca_emitir_operador(asc ? "<" : ">", yylineno);

        int celda_bf = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BF", yylineno);

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
#line 3089 "y.tab.c"
break;
case 137:
#line 1437 "src/gramatica.y"
	{ yyerror("Error: Falta identificador (ID) en el encabezado."); yyerrok; }
#line 3094 "y.tab.c"
break;
case 138:
#line 1439 "src/gramatica.y"
	{ yyerror("Error: Falta 'TO' en el encabezado de la iteración."); yyerrok; }
#line 3099 "y.tab.c"
break;
case 139:
#line 1441 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
#line 3104 "y.tab.c"
break;
case 140:
#line 1443 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
#line 3109 "y.tab.c"
break;
case 141:
#line 1445 "src/gramatica.y"
	{ yyerror("Error: Falta CTE en el encabezado."); yyerrok; }
#line 3114 "y.tab.c"
break;
case 145:
#line 1459 "src/gramatica.y"
	{
        ultima_condicion_comptime = (yystack.l_mark[-2].info_expr.es_comptime && yystack.l_mark[0].info_expr.es_comptime);
        if (yystack.l_mark[-2].info_expr.tipo != TIPO_NO_ASIGNADO && yystack.l_mark[0].info_expr.tipo != TIPO_NO_ASIGNADO && yystack.l_mark[-2].info_expr.tipo != yystack.l_mark[0].info_expr.tipo) {
            registrar_error(
                ETAPA_SEMANTICO,
                yylineno,
                "Tipos incompatibles en condición relacional: no se puede comparar entre '%s' y '%s' sin conversión explícita TOSF.",
                tipo_dato_a_string(yystack.l_mark[-2].info_expr.tipo),
                tipo_dato_a_string(yystack.l_mark[0].info_expr.tipo)
            );
        }
        polaca_emitir_operador(yystack.l_mark[-1].cadena, yylineno);
    }
#line 3131 "y.tab.c"
break;
case 146:
#line 1475 "src/gramatica.y"
	{ yyval.cadena = "<"; }
#line 3136 "y.tab.c"
break;
case 147:
#line 1476 "src/gramatica.y"
	{ yyval.cadena = ">"; }
#line 3141 "y.tab.c"
break;
case 148:
#line 1477 "src/gramatica.y"
	{ yyval.cadena = ">="; }
#line 3146 "y.tab.c"
break;
case 149:
#line 1478 "src/gramatica.y"
	{ yyval.cadena = "<="; }
#line 3151 "y.tab.c"
break;
case 150:
#line 1479 "src/gramatica.y"
	{ yyval.cadena = "=="; }
#line 3156 "y.tab.c"
break;
case 151:
#line 1480 "src/gramatica.y"
	{ yyval.cadena = "!="; }
#line 3161 "y.tab.c"
break;
#line 3163 "y.tab.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}
