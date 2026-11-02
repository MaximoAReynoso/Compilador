/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20241231

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

    /* Copiar los parámetros a los formales en el orden indicado:*/
    for (int k = 0; k < inv.cant_orden; k++) {
        int idx = inv.orden[k] - 1; /* 1-based a 0-based*/
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
                char ambito_fn[256];
                snprintf(ambito_fn, sizeof(ambito_fn), "%s:%s",
                         fn->ambito ? fn->ambito : "main",
                         fn->nombre_original ? fn->nombre_original : fn->lexema);
                char *mangled_p = construir_mangled_name(pf->nombre, ambito_fn);
                s_formal = buscar_simbolo(obtener_tabla_simbolos(), mangled_p);
                free(mangled_p);
            }
        }

        /* 1. Emitir destino (parámetro formal)*/
        if (s_formal != NULL) {
            polaca_emitir_simbolo(s_formal, inv.linea);
        }

        /* 2. Emitir valor del parámetro real correspondiente*/
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

        /* 3. Emitir asignación :=*/
        if (s_formal != NULL) {
            polaca_emitir_operador(":=", inv.linea);
        }
    }

    /* 4. Emitir llamado CALL*/
    if (fn != NULL) {
        polaca_emitir_simbolo(fn, inv.linea);
    }
    polaca_emitir_operador("CALL", inv.linea);

    if (inv.nombre_fn) free(inv.nombre_fn);
}
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 188 "src/gramatica.y"
typedef union YYSTYPE {
    struct Simbolo *simbolo;
    int val_int;
    int tipo_dato;
    const char *cadena;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 223 "y.tab.c"

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
    0,    0,    0,    0,    5,    5,    8,    8,    9,    9,
    9,    9,    9,   14,   14,    1,    1,   10,   15,   15,
   13,   11,   11,   11,   11,   16,   18,   17,   17,   17,
   19,   19,   21,   12,   20,   20,   24,   24,   22,   22,
   22,   23,   23,   25,   25,    6,    6,    7,    7,    7,
    7,   26,   26,   26,   26,   26,   31,   31,   27,   27,
    4,    4,    4,   30,   30,   30,   30,   32,   32,   32,
   32,   32,   33,   33,   33,   33,   33,   35,   35,   35,
   36,   36,   36,   34,   38,   34,   37,   37,   37,   37,
   37,   37,   37,   39,   39,   41,   40,   40,   44,   43,
   43,   45,   45,   45,   45,   42,   47,   47,   48,   49,
   50,   51,   50,   46,   46,    3,    3,    3,    3,    3,
    3,    3,    3,    3,   28,   28,   28,   28,   52,   54,
   54,   56,   53,   53,   29,   57,   57,   57,   57,   57,
   57,   57,   58,   59,   59,   55,    2,    2,    2,    2,
    2,    2,
};
static const YYINT yylen[] = {                            2,
    4,    3,    4,    3,    1,    0,    2,    1,    2,    2,
    2,    2,    2,    3,    2,    1,    1,    2,    3,    1,
    2,    5,    4,    8,    7,    4,    3,    3,    2,    1,
    2,    1,    0,    7,    1,    0,    3,    1,    1,    3,
    2,    2,    1,    2,    2,    3,    3,    3,    2,    3,
    2,    1,    1,    1,    1,    1,    4,    3,    3,    3,
    1,    3,    4,    4,    4,    3,    2,    3,    3,    3,
    3,    1,    3,    3,    3,    3,    1,    3,    3,    1,
    3,    3,    1,    1,    0,    6,    1,    3,    4,    1,
    1,    4,    1,    4,    3,    2,    4,    3,    4,    3,
    3,    3,    3,    1,    1,    1,    3,    1,    2,    0,
    1,    0,    4,    1,    1,    1,    1,    2,    2,    2,
    2,    1,    2,    2,    3,    3,    5,    5,    4,    3,
    1,    1,    1,    2,    3,    8,    4,    7,    5,    3,
    3,    4,    1,    1,    1,    3,    1,    1,    1,    1,
    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,   16,   17,    0,    0,    0,    0,    0,    8,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   33,   20,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    7,    9,   10,   11,   12,   13,    0,    0,   30,
    0,    0,    0,    0,    0,    0,   27,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   52,   53,
   54,   55,   56,    0,    0,    0,    4,   31,    0,    0,
   29,    0,    0,    1,   19,   35,    0,    0,    0,   51,
    0,    0,    0,  116,  117,  114,  115,    0,    0,    0,
    0,   93,    0,    0,   77,   84,   90,   91,  110,  110,
  122,    0,   67,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   47,    0,   49,  133,    0,    0,    0,   46,
   28,    0,   23,   39,    0,    0,    0,    0,   62,    0,
   96,   85,    0,    0,    0,    0,  118,  119,  123,  120,
  121,  124,  149,  150,  151,  152,    0,    0,  147,  148,
    0,    0,    0,    0,    0,  108,    0,    0,    0,    0,
   66,    0,   58,    0,    0,    0,    0,  140,    0,    0,
   50,   48,  134,  126,  132,  131,  125,    0,  144,  145,
  135,  143,   22,   38,   41,    0,    0,    0,    0,   43,
    0,    0,   63,    0,    0,    0,    0,  129,    0,   70,
    0,   71,    0,    0,   75,   73,   76,   74,    0,  110,
    0,    0,  109,    0,    0,   65,   64,   57,  142,    0,
  137,    0,    0,   40,    0,   44,   45,   34,   42,    0,
   25,    0,   99,   89,   92,  128,    0,   94,  107,    0,
   97,  127,    0,  139,    0,  130,   37,   24,    0,    0,
    0,   83,    0,  104,    0,  105,    0,    0,    0,   86,
    0,    0,    0,    0,  101,    0,  100,    0,    0,  138,
    0,    0,   81,   82,  102,  103,  136,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  257,  275,  277,  278,  283,  287,  288,  292,  295,  296,
  297,  298,  299,  300,  301,  303,  305,  257,  292,  302,
  257,  257,  288,  302,  257,  276,  302,  256,  271,  293,
  257,  296,   59,   59,   59,   59,   59,  288,  304,  306,
  304,  271,  293,   44,  308,  302,   40,  256,  257,  256,
  257,  268,  273,  274,  279,  291,  294,  313,  314,  315,
  316,  317,  318,  339,  344,  294,   59,  257,   44,   41,
  306,   41,  294,   59,  257,  257,  307,   40,   40,   59,
   46,   91,  257,  258,  259,  266,  267,  284,   40,   43,
   45,  290,  319,  320,  321,  324,  326,  327,  328,  331,
  333,  342,  256,   40,   40,  257,   40,   61,  342,  261,
   61,  256,  272,  313,   59,  293,  313,  340,  282,  272,
  306,  292,  293,  271,  285,  309,  304,   41,  257,  319,
   40,   61,   46,   91,   40,  342,  258,  259,  333,  258,
  259,  333,  262,  263,  264,  265,   43,   45,   60,   62,
  289,   42,   47,  329,  334,  335,  336,  329,   41,  260,
   41,  319,   41,  319,   61,  342,  290,   41,  319,  319,
   59,   59,   59,  256,  269,  270,  341,  343,  293,  313,
  345,  346,  293,  257,  271,  311,  297,  298,  310,  312,
   41,  292,   93,  325,  257,  319,  319,   41,  340,  256,
  320,  256,  320,  319,  256,  321,  256,  321,   41,   44,
  257,  319,  337,   41,  340,   41,   41,   41,  280,  290,
   41,  280,  340,  271,   44,   59,   59,  272,  312,  292,
  293,   40,   40,   93,   41,  341,   91,  330,  335,   61,
  330,  341,  280,  290,  290,  270,  257,  293,  257,  322,
  323,  324,  256,  258,  332,  333,  338,  290,  281,   41,
   43,   45,   42,   47,   93,   44,   93,  319,  281,  290,
  323,  323,  324,  324,  258,  333,  290,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          6,
    7,  151,   92,   56,    8,  116,   57,    9,   10,   11,
   12,   13,   14,   15,   20,   16,   39,   17,   40,   77,
   45,  126,  189,  186,  190,  117,   59,   60,   61,   62,
   63,   93,   94,   95,  250,  251,   96,  194,   97,   98,
   99,  154,  238,  100,  255,  101,  155,  156,  157,  213,
  257,   64,  118,  177,  102,  178,   65,  181,  182,
};
static const YYINT yysindex[] = {                      -161,
  195, -240,    0,    0, -128,    0, -235, -210,  223,    0,
    5,   11,   17,   28,   38,  112,  112, -199, -136,   64,
    0,    0, -199,   64,  130,  144,   64,  344,  344,   77,
 -199,    0,    0,    0,    0,    0,    0,  -80,  -28,    0,
   19,  344,   95,  -76,  -64,   64,    0,  160,  174,  166,
   -3,  -36,  -32,  215,  -40,  -59,  303,  176,    0,    0,
    0,    0,    0,  323,  -10,  331,    0,    0,  112,  223,
    0, -210,  331,    0,    0,    0, -233,  112,  226,    0,
   27,  114,  138,    0,    0,    0,    0,  250,  114,  295,
  297,    0,  389,  125,    0,    0,    0,    0,    0,    0,
    0,  259,    0,   -6,   -1,  346,  114,  299,  273,  114,
  114,  266,    0,  272,    0,    0,  284,  -83,  323,    0,
    0, -210,    0,    0, -124,  112,   40,  223,    0,  -14,
    0,    0,   49,  114,  114,  167,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -20,  200,    0,    0,
  114,  230,  246,  308,  311,    0,  262,  325,  323,  327,
    0,  529,    0,  588,   70,  338,  107,    0,  352,  352,
    0,    0,    0,    0,    0,    0,    0,  323,    0,    0,
    0,    0,    0,    0,    0,  -43,  337,  349,    4,    0,
  223, -210,    0,  379,  382,   12,  591,    0,  136,    0,
  125,    0,  125,  352,    0,    0,    0,    0,  342,    0,
  404,  352,    0,  342,  136,    0,    0,    0,    0,  268,
    0,  299,  178,    0,  196,    0,    0,    0,    0, -210,
    0,  265,    0,    0,    0,    0,  -62,    0,    0,    0,
    0,    0,  299,    0,  180,    0,    0,    0,   16,  594,
  169,    0,  376,    0,    1,    0,  114,  190,  299,    0,
  265,  265,  265,  265,    0,   68,    0,  352,  299,    0,
  169,  169,    0,    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                      -105,
 -105,    0,    0,    0,    0,    0,    0,    0, -103,    0,
    0,    0,    0,    0,    0,    0,    0,  116,    0,  431,
    0,    0,    0,  432,  116,    0,  434,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   42,    0,    0,
    0,    0,  485,    0,  -88,  435,    0,    0,    0,    0,
  -51,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -105,
    0,    0,  507,    0,    0,    0,    0,    0,  139,    0,
    0,    0,    6,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   96,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  400,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -105,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  475,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  477,  236,    0,    0,  466,  474,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -105,    0,    0,    0,   30,    0,    0,    0,    0,    0,
  120,    0,  147,  157,    0,    0,    0,    0,   59,    0,
  583,  171,    0,   83,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -25,
    0,    0,    0,    0,    0,    0,    0,    0,  566,    0,
  597,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  258,    0,    0,
  600,  603,    0,    0,    0,    0,    0,
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
    0,    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
   93,    0,  -74,    0,   10,  355,  102,    0,  527, -120,
 -107,    0,    0,    0,    7,    0,   15,    0,  -15,    0,
    0,    0,    0,    0,  350,  426,    0,    0,    0,    0,
    0,  433,  316,  329,    0,  214,  247,    0,    0,    0,
    0,  440,  328,    0,    0,  -63,    0,  340,    0,    0,
    0,    0, -100, -104,  -22,    0,    0,    0,    0,
};
#define YYTABLESIZE 690
static const YYINT yytable[] = {                        107,
  225,  111,   90,   89,   91,  187,   90,  104,   91,   61,
   19,   24,   70,   27,   85,   69,   21,  112,  188,  112,
  108,   25,   90,   71,   91,   71,  139,  142,  147,   46,
  148,   41,  109,  167,  161,  199,   90,  124,   91,  163,
   26,   90,   81,   91,  266,   28,   87,   87,   87,   87,
   87,  125,   87,  121,  147,  131,  148,   22,  215,   72,
   29,  133,   69,   33,   87,   87,  136,   87,  187,   34,
   88,   88,   88,   88,   88,   35,   88,  223,  193,  122,
  191,  188,   32,   69,  166,   32,   36,   82,   88,   88,
  220,   88,  127,  267,  236,    1,   37,   23,   87,   95,
   95,   95,   95,   95,  234,   95,  134,   44,   38,   38,
  242,   71,   90,    2,   91,    3,    4,   95,   95,   28,
   95,    5,   88,   98,   98,   98,   98,   98,   22,   98,
   66,   38,  184,   38,   42,   67,   72,  192,   72,   72,
   72,   98,   98,   73,   98,  244,  185,  245,    3,    4,
    6,   95,    5,   74,   72,   72,   90,   72,   91,   20,
   68,   38,   68,   68,   68,    6,  152,    5,  258,   47,
   38,  153,  174,  256,   20,   98,   68,  131,   68,   68,
   75,   68,   36,  133,  270,  175,  176,   69,   72,   69,
   69,   69,   76,  253,  277,  254,   36,  146,  132,   78,
  230,  110,  276,   86,   87,   69,   69,  198,   69,   61,
  263,  111,   68,   79,  111,  264,  106,   84,   85,   38,
   83,   84,   85,  103,   80,   86,   87,  224,  134,   86,
   87,  112,  112,  112,  115,  200,   83,   84,   85,   69,
  112,  112,   90,   88,   91,   86,   87,   88,    3,    4,
   83,   84,   85,  160,  105,   83,   84,   85,  112,   86,
   87,   87,   87,   88,   86,   87,  128,   87,   87,   87,
   87,  119,   90,   87,   91,  228,   87,   88,   87,   87,
    3,    4,   88,  129,   87,   88,   88,   87,   90,  135,
   91,   88,   88,   88,   88,    3,    4,   88,  113,  159,
   88,  113,   88,   88,   90,  195,   91,   90,   88,   91,
   90,   88,   91,  168,   95,   95,    3,    4,   32,   32,
   95,   95,   95,   95,  171,  275,   95,   84,   85,   95,
  172,   95,   95,   86,   87,   86,   87,   95,   98,   98,
   95,   90,  173,   91,   98,   98,   98,   98,  209,  219,
   98,   72,   72,   98,  210,   98,   98,   72,   72,   72,
   72,   98,   30,   72,   98,  214,   72,  216,   72,   72,
   83,   84,   85,   43,   72,   68,   68,   72,  221,   86,
   87,   68,   68,   68,   68,  131,  222,   68,    3,    4,
   68,  133,   68,   68,  147,  226,  148,   88,   68,   48,
   49,   68,   69,   69,  175,  176,  165,  227,   69,   69,
   69,   69,  146,  146,   69,   26,   26,   69,  232,   69,
   69,  233,   28,   51,  146,   69,  123,  146,   69,  146,
  146,  147,  237,  148,   52,  146,  134,   29,  146,   53,
   54,   87,   87,  131,   87,   55,   87,  246,  149,  133,
  150,   18,  247,   58,   58,  202,   83,   84,   85,   87,
  259,   87,  201,  203,  240,   86,   87,   58,  265,    2,
  269,    3,    4,  179,  271,  272,  183,    5,  252,   31,
  206,  208,  114,   88,    2,  205,   83,   84,   85,   21,
   15,  114,   18,   14,  134,   86,   87,    2,  114,    3,
    4,  207,   83,   84,   85,    5,    3,  252,  252,  273,
  274,   86,   87,   88,  130,  106,   85,  141,  211,   84,
   85,  249,   84,   85,   59,   84,   85,   86,   87,   88,
   86,   87,   60,   86,   87,   32,  162,  164,  229,  158,
    0,  241,  169,  170,  180,   88,  231,  243,   88,  239,
    0,    0,  137,  138,  140,  141,   84,   85,  112,   51,
   86,   87,   86,   87,   86,   87,  196,  197,    0,  217,
   52,  147,    0,  148,  113,   53,   54,    0,   28,   51,
    0,   55,    0,  204,  248,    0,  112,   51,    0,  212,
   52,    0,    0,   29,    0,   53,   54,    0,   52,   50,
   51,   55,  120,   53,   54,    0,   87,   87,   87,   55,
   87,   52,   87,    0,    0,    0,   53,   54,    0,    0,
    0,    0,   55,   87,   87,   87,   87,   87,  218,   87,
  147,  235,  148,  147,  260,  148,  261,   80,  262,   80,
   78,   80,   78,   79,   78,   79,    0,   79,    0,    0,
  143,  144,  145,  146,    0,    0,    0,    0,    0,    0,
    0,   87,   87,   87,   87,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  268,
};
static const YYINT yycheck[] = {                         40,
   44,   61,   43,   40,   45,  126,   43,   40,   45,   61,
    1,    5,   41,    7,   40,   44,  257,   43,  126,   45,
   61,  257,   43,   39,   45,   41,   90,   91,   43,   23,
   45,   17,   55,  108,   41,  136,   43,  271,   45,   41,
  276,   43,   46,   45,   44,  256,   41,   42,   43,   44,
   45,  285,   47,   69,   43,   40,   45,  257,  159,   41,
  271,   46,   44,   59,   59,   60,   89,   62,  189,   59,
   41,   42,   43,   44,   45,   59,   47,  178,   93,   70,
   41,  189,   41,   44,  107,   44,   59,   91,   59,   60,
  165,   62,   78,   93,  199,  257,   59,    5,   93,   41,
   42,   43,   44,   45,   93,   47,   91,   44,   16,   17,
  215,  127,   43,  275,   45,  277,  278,   59,   60,  256,
   62,  283,   93,   41,   42,   43,   44,   45,  257,   47,
   29,   39,  257,   41,  271,   59,   41,  128,   43,   44,
   45,   59,   60,   42,   62,  220,  271,  222,  277,  278,
  256,   93,  256,   59,   59,   60,   43,   62,   45,   44,
   41,   69,   43,   44,   45,  271,   42,  271,  243,   40,
   78,   47,  256,  237,   59,   93,  257,   40,   59,   60,
  257,   62,  271,   46,  259,  269,  270,   41,   93,   43,
   44,   45,  257,  256,  269,  258,  285,   41,   61,   40,
  191,  261,  266,  266,  267,   59,   60,   41,   62,  261,
   42,   41,   93,   40,   44,   47,  257,  258,  259,  127,
  257,  258,  259,  256,   59,  266,  267,  271,   91,  266,
  267,  257,  258,  259,   59,  256,  257,  258,  259,   93,
  266,  267,   43,  284,   45,  266,  267,  284,  277,  278,
  257,  258,  259,  260,   40,  257,  258,  259,  284,  266,
  267,  256,  257,  284,  266,  267,   41,  262,  263,  264,
  265,  282,   43,  268,   45,  272,  271,  284,  273,  274,
  277,  278,  284,  257,  279,  256,  257,  282,   43,   40,
   45,  262,  263,  264,  265,  277,  278,  268,   41,   41,
  271,   44,  273,  274,   43,  257,   45,   43,  279,   45,
   43,  282,   45,   41,  256,  257,  277,  278,  277,  278,
  262,  263,  264,  265,   59,  258,  268,  258,  259,  271,
   59,  273,  274,  266,  267,  266,  267,  279,  256,  257,
  282,   43,   59,   45,  262,  263,  264,  265,   41,  280,
  268,  256,  257,  271,   44,  273,  274,  262,  263,  264,
  265,  279,    8,  268,  282,   41,  271,   41,  273,  274,
  257,  258,  259,   19,  279,  256,  257,  282,   41,  266,
  267,  262,  263,  264,  265,   40,  280,  268,  277,  278,
  271,   46,  273,  274,   43,   59,   45,  284,  279,  256,
  257,  282,  256,  257,  269,  270,   61,   59,  262,  263,
  264,  265,  256,  257,  268,  277,  278,  271,   40,  273,
  274,   40,  256,  257,  268,  279,   72,  271,  282,  273,
  274,   43,   91,   45,  268,  279,   91,  271,  282,  273,
  274,   42,   43,   40,   45,  279,   47,  270,   60,   46,
   62,  257,  257,   28,   29,  256,  257,  258,  259,   60,
  281,   62,  147,  148,   61,  266,  267,   42,   93,  275,
  281,  277,  278,  119,  261,  262,  122,  283,  232,  257,
  152,  153,   57,  284,    0,  256,  257,  258,  259,   59,
   59,   66,   59,   59,   91,  266,  267,  275,   73,  277,
  278,  256,  257,  258,  259,  283,    0,  261,  262,  263,
  264,  266,  267,  284,   82,   41,   40,  282,  257,  258,
  259,  257,  258,  259,   59,  258,  259,  266,  267,  284,
  266,  267,   59,  266,  267,    9,  104,  105,  189,  100,
   -1,  214,  110,  111,  119,  284,  192,  280,  284,  210,
   -1,   -1,  258,  259,  258,  259,  258,  259,  256,  257,
  266,  267,  266,  267,  266,  267,  134,  135,   -1,   41,
  268,   43,   -1,   45,  272,  273,  274,   -1,  256,  257,
   -1,  279,   -1,  151,  230,   -1,  256,  257,   -1,  157,
  268,   -1,   -1,  271,   -1,  273,  274,   -1,  268,  256,
  257,  279,  272,  273,  274,   -1,   41,   42,   43,  279,
   45,  268,   47,   -1,   -1,   -1,  273,  274,   -1,   -1,
   -1,   -1,  279,   41,   42,   43,   44,   45,   41,   47,
   43,   41,   45,   43,   41,   45,   43,   41,   45,   43,
   41,   45,   43,   41,   45,   43,   -1,   45,   -1,   -1,
  262,  263,  264,  265,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  262,  263,  264,  265,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,
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
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
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
#ifndef NULL
#define NULL (void*)0
#endif
static const char *const yyname[] = {

"$end",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"'('","')'","'*'","'+'","','",
"'-'","'.'","'/'",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"';'",
"'<'","'='","'>'",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
"'['",NULL,"']'",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,"error","ID","CTE","CTE_FLOAT","MULT_STRING",
"ASSIGN","GE","LE","EQ","NE","OUT_OF_RANGE","ERROR_LEXICO","IF","ELSE","END_IF",
"BEGIN","END","POUT","RET","CLASS","FUNCTION","INTEGER","SINGLEF","FROM","TO",
"BY","REPEAT","COMPTIME","TOSF","EXTENDS","$accept","programa","tipo_dato",
"operador_relacional","constante_con_signo","destino_asignacion",
"bloque_declarativo","bloque_ejecutable","lista_ejecutables",
"lista_declaraciones","declaracion","declaracion_variable",
"declaracion_funcion","declaracion_clase","declaracion_objeto",
"declaracion_comptime","lista_variables","encabezado_funcion",
"lista_parametros","encabezado_funcion_sin_kw","parametro","codigo_clase","$$1",
"encabezado_clase","miembros_clase","lista_clase","miembro","sentencia",
"asignacion","if_sentencia","iteracion","impresion","sentencia_retorno",
"expresion_aritmetica","termino","operando","expresion_sin_asignacion",
"termino_sin_asignacion","operando_base","$$2","llamada_con_orden",
"llamada_metodo_con_orden","llamada_encabezado","parametros_reales",
"orden_evaluacion","llamada_metodo_encabezado","lista_enteros",
"constante_invalida","lista_parametros_reales","parametro_real_item",
"iniciar_parametro","parametro_real","$$3","if_encabezado","bloque_if","fin_if",
"condicion","else_encabezado","encabezado_iteracion","cuerpo_iteracion",
"bloque_o_sentencia","illegal-symbol",
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
"expresion_sin_asignacion : expresion_sin_asignacion '+' termino_sin_asignacion",
"expresion_sin_asignacion : expresion_sin_asignacion '-' termino_sin_asignacion",
"expresion_sin_asignacion : termino_sin_asignacion",
"termino_sin_asignacion : termino_sin_asignacion '*' operando_base",
"termino_sin_asignacion : termino_sin_asignacion '/' operando_base",
"termino_sin_asignacion : operando_base",
"operando : operando_base",
"$$2 :",
"operando : ID '=' $$2 '(' expresion_sin_asignacion ')'",
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
"encabezado_iteracion : FROM ID '=' constante_con_signo TO constante_con_signo BY constante_con_signo",
"encabezado_iteracion : FROM '(' condicion ')'",
"encabezado_iteracion : FROM '=' constante_con_signo TO constante_con_signo BY constante_con_signo",
"encabezado_iteracion : FROM ID '=' constante_con_signo constante_con_signo",
"encabezado_iteracion : FROM condicion ')'",
"encabezado_iteracion : FROM '(' condicion",
"encabezado_iteracion : FROM ID '=' TO",
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
static YYParseState *yyps = NULL;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = NULL;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = NULL;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = NULL;

/* End position of lexical value queue */
static YYSTYPE *yylve = NULL;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = NULL;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = NULL;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = NULL;

/* End position of lexical position queue */
static YYLTYPE *yylpe = NULL;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = NULL;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = NULL;

static YYINT  *yylexemes = NULL;
#endif /* YYBTYACC */
#line 983 "src/gramatica.y"

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
#line 1065 "y.tab.c"

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
    if (newss == NULL)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == NULL)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == NULL)
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

    if ((yys = getenv("YYDEBUG")) != NULL)
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
    yyps = yyNewState(0); if (yyps == NULL) goto yyenomem;
    yyps->save = NULL;
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
#line 211 "src/gramatica.y"
	{
        /* Programa finalizado correctamente*/
    }
#line 1740 "y.tab.c"
break;
case 2:
#line 215 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador ; al final del bloque ejecutable."); yyerrok; }
#line 1745 "y.tab.c"
break;
case 3:
#line 217 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador END al final del bloque ejecutable."); yyerrok; }
#line 1750 "y.tab.c"
break;
case 4:
#line 219 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
#line 1755 "y.tab.c"
break;
case 14:
#line 242 "src/gramatica.y"
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
#line 1772 "y.tab.c"
break;
case 15:
#line 256 "src/gramatica.y"
	{ yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
#line 1777 "y.tab.c"
break;
case 16:
#line 260 "src/gramatica.y"
	{ yyval.tipo_dato = TIPO_INTEGER; }
#line 1782 "y.tab.c"
break;
case 17:
#line 261 "src/gramatica.y"
	{ yyval.tipo_dato = TIPO_SINGLEF; }
#line 1787 "y.tab.c"
break;
case 18:
#line 266 "src/gramatica.y"
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
        }
        cant_vars_declaradas = 0;
    }
#line 1804 "y.tab.c"
break;
case 19:
#line 283 "src/gramatica.y"
	{
        if (cant_vars_declaradas < 64) {
            lista_vars_declaradas[cant_vars_declaradas++] = yystack.l_mark[0].simbolo;
        }
    }
#line 1813 "y.tab.c"
break;
case 20:
#line 289 "src/gramatica.y"
	{
        cant_vars_declaradas = 0;
        if (cant_vars_declaradas < 64) {
            lista_vars_declaradas[cant_vars_declaradas++] = yystack.l_mark[0].simbolo;
        }
    }
#line 1823 "y.tab.c"
break;
case 21:
#line 299 "src/gramatica.y"
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
#line 1843 "y.tab.c"
break;
case 22:
#line 319 "src/gramatica.y"
	{
        if (tope_fn_decl > 0) tope_fn_decl--;
        polaca_desapilar_actual();
        salir_ambito();
    }
#line 1852 "y.tab.c"
break;
case 23:
#line 325 "src/gramatica.y"
	{
        if (tope_fn_decl > 0) tope_fn_decl--;
        polaca_desapilar_actual();
        salir_ambito();
    }
#line 1861 "y.tab.c"
break;
case 24:
#line 331 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
#line 1866 "y.tab.c"
break;
case 25:
#line 333 "src/gramatica.y"
	{ yyerror("Error: Faltan los parametros de la función."); yyerrok; }
#line 1871 "y.tab.c"
break;
case 26:
#line 338 "src/gramatica.y"
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
#line 1893 "y.tab.c"
break;
case 27:
#line 360 "src/gramatica.y"
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
#line 1915 "y.tab.c"
break;
case 29:
#line 383 "src/gramatica.y"
	{ yyerror("Error: Falta de ',' en declaración de parámetros."); yyerrok; }
#line 1920 "y.tab.c"
break;
case 31:
#line 389 "src/gramatica.y"
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
#line 1949 "y.tab.c"
break;
case 32:
#line 415 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
#line 1954 "y.tab.c"
break;
case 33:
#line 419 "src/gramatica.y"
	{ entrar_ambito(yystack.l_mark[0].simbolo->lexema); }
#line 1959 "y.tab.c"
break;
case 34:
#line 420 "src/gramatica.y"
	{
        salir_ambito();
    }
#line 1966 "y.tab.c"
break;
case 36:
#line 427 "src/gramatica.y"
	{ yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
#line 1971 "y.tab.c"
break;
case 41:
#line 439 "src/gramatica.y"
	{ yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
#line 1976 "y.tab.c"
break;
case 47:
#line 455 "src/gramatica.y"
	{ yyerror("Error: Falta de delimitador de sentencias ejecutables BEGIN."); yyerrok; }
#line 1981 "y.tab.c"
break;
case 50:
#line 462 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 1986 "y.tab.c"
break;
case 51:
#line 464 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 1991 "y.tab.c"
break;
case 57:
#line 477 "src/gramatica.y"
	{
        polaca_emitir_operador("RET", yylineno);
    }
#line 1998 "y.tab.c"
break;
case 58:
#line 481 "src/gramatica.y"
	{
        polaca_emitir_operador("RET", yylineno);
    }
#line 2005 "y.tab.c"
break;
case 59:
#line 488 "src/gramatica.y"
	{
        polaca_emitir_operador(":=", yylineno);
    }
#line 2012 "y.tab.c"
break;
case 60:
#line 492 "src/gramatica.y"
	{ yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
#line 2017 "y.tab.c"
break;
case 61:
#line 497 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[0].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[0].simbolo->lexema);
            s = yystack.l_mark[0].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
        yyval.simbolo = s;
    }
#line 2030 "y.tab.c"
break;
case 62:
#line 507 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-2].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Objeto '%s' no declarado o fuera de alcance.", yystack.l_mark[-2].simbolo->lexema);
            s = yystack.l_mark[-2].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
        polaca_emitir_operador(yystack.l_mark[0].simbolo->lexema, yylineno);
        polaca_emitir_operador(".", yylineno);
        yyval.simbolo = s;
    }
#line 2045 "y.tab.c"
break;
case 63:
#line 519 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-3].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[-3].simbolo->lexema);
            s = yystack.l_mark[-3].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
        polaca_emitir_operador("[]", yylineno);
        yyval.simbolo = s;
    }
#line 2059 "y.tab.c"
break;
case 64:
#line 533 "src/gramatica.y"
	{
        polaca_emitir_operador("POUT", yylineno);
    }
#line 2066 "y.tab.c"
break;
case 65:
#line 537 "src/gramatica.y"
	{
        polaca_emitir_simbolo(yystack.l_mark[-1].simbolo, yylineno);
        polaca_emitir_operador("POUT", yylineno);
    }
#line 2074 "y.tab.c"
break;
case 66:
#line 542 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 2079 "y.tab.c"
break;
case 67:
#line 544 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 2084 "y.tab.c"
break;
case 68:
#line 549 "src/gramatica.y"
	{
        polaca_emitir_operador("+", yylineno);
    }
#line 2091 "y.tab.c"
break;
case 69:
#line 553 "src/gramatica.y"
	{
        polaca_emitir_operador("-", yylineno);
    }
#line 2098 "y.tab.c"
break;
case 70:
#line 557 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '+'."); yyerrok; }
#line 2103 "y.tab.c"
break;
case 71:
#line 559 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '-'."); yyerrok; }
#line 2108 "y.tab.c"
break;
case 73:
#line 565 "src/gramatica.y"
	{
        polaca_emitir_operador("*", yylineno);
    }
#line 2115 "y.tab.c"
break;
case 74:
#line 569 "src/gramatica.y"
	{
        polaca_emitir_operador("/", yylineno);
    }
#line 2122 "y.tab.c"
break;
case 75:
#line 573 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '*'."); yyerrok; }
#line 2127 "y.tab.c"
break;
case 76:
#line 575 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '/'."); yyerrok; }
#line 2132 "y.tab.c"
break;
case 78:
#line 581 "src/gramatica.y"
	{
        polaca_emitir_operador("+", yylineno);
    }
#line 2139 "y.tab.c"
break;
case 79:
#line 585 "src/gramatica.y"
	{
        polaca_emitir_operador("-", yylineno);
    }
#line 2146 "y.tab.c"
break;
case 81:
#line 593 "src/gramatica.y"
	{
        polaca_emitir_operador("*", yylineno);
    }
#line 2153 "y.tab.c"
break;
case 82:
#line 597 "src/gramatica.y"
	{
        polaca_emitir_operador("/", yylineno);
    }
#line 2160 "y.tab.c"
break;
case 85:
#line 605 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-1].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[-1].simbolo->lexema);
            s = yystack.l_mark[-1].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
    }
#line 2172 "y.tab.c"
break;
case 86:
#line 613 "src/gramatica.y"
	{
        polaca_emitir_operador(":=", yylineno);
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-5].simbolo->lexema);
        polaca_emitir_simbolo(s ? s : yystack.l_mark[-5].simbolo, yylineno);
    }
#line 2181 "y.tab.c"
break;
case 87:
#line 622 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[0].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[0].simbolo->lexema);
            s = yystack.l_mark[0].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
    }
#line 2193 "y.tab.c"
break;
case 88:
#line 631 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-2].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Objeto '%s' no declarado o fuera de alcance.", yystack.l_mark[-2].simbolo->lexema);
            s = yystack.l_mark[-2].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
        polaca_emitir_operador(yystack.l_mark[0].simbolo->lexema, yylineno);
        polaca_emitir_operador(".", yylineno);
    }
#line 2207 "y.tab.c"
break;
case 89:
#line 642 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-3].simbolo->lexema);
        polaca_emitir_simbolo(s ? s : yystack.l_mark[-3].simbolo, yylineno);
        polaca_emitir_operador("[]", yylineno);
    }
#line 2216 "y.tab.c"
break;
case 92:
#line 650 "src/gramatica.y"
	{
        polaca_emitir_operador("TOSF", yylineno);
    }
#line 2223 "y.tab.c"
break;
case 93:
#line 654 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            polaca_emitir_simbolo(yystack.l_mark[0].simbolo, yylineno);
        }
    }
#line 2232 "y.tab.c"
break;
case 94:
#line 663 "src/gramatica.y"
	{
        finalizar_invocacion_con_orden();
    }
#line 2239 "y.tab.c"
break;
case 95:
#line 667 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 2244 "y.tab.c"
break;
case 96:
#line 672 "src/gramatica.y"
	{
        iniciar_invocacion(yystack.l_mark[-1].simbolo->lexema, yylineno);
    }
#line 2251 "y.tab.c"
break;
case 97:
#line 679 "src/gramatica.y"
	{
        finalizar_invocacion_con_orden();
    }
#line 2258 "y.tab.c"
break;
case 98:
#line 683 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 2263 "y.tab.c"
break;
case 99:
#line 688 "src/gramatica.y"
	{
        iniciar_invocacion(yystack.l_mark[-1].simbolo->lexema, yylineno);
    }
#line 2270 "y.tab.c"
break;
case 101:
#line 696 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 2275 "y.tab.c"
break;
case 102:
#line 701 "src/gramatica.y"
	{
        long val = parsear_valor_entero(yystack.l_mark[0].simbolo ? yystack.l_mark[0].simbolo->lexema : "0");
        agregar_orden_invocacion((int)val);
    }
#line 2283 "y.tab.c"
break;
case 104:
#line 707 "src/gramatica.y"
	{
        long val = parsear_valor_entero(yystack.l_mark[0].simbolo ? yystack.l_mark[0].simbolo->lexema : "0");
        agregar_orden_invocacion((int)val);
    }
#line 2291 "y.tab.c"
break;
case 109:
#line 725 "src/gramatica.y"
	{
        if (tope_invocaciones > 0) {
            Invocacion *inv = &pila_invocaciones[tope_invocaciones - 1];
            Polaca *p = obtener_polaca_actual();
            polaca_desapilar_actual();
            if (inv->cant_args < 16) {
                inv->args_polaca[inv->cant_args++] = p;
            }
        }
    }
#line 2305 "y.tab.c"
break;
case 110:
#line 739 "src/gramatica.y"
	{
        Polaca *p = crear_polaca("param_tmp");
        polaca_apilar_actual(p);
    }
#line 2313 "y.tab.c"
break;
case 112:
#line 747 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-1].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[-1].simbolo->lexema);
            s = yystack.l_mark[-1].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
    }
#line 2325 "y.tab.c"
break;
case 113:
#line 755 "src/gramatica.y"
	{
        polaca_emitir_operador(":=", yylineno);
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-3].simbolo->lexema);
        polaca_emitir_simbolo(s ? s : yystack.l_mark[-3].simbolo, yylineno);
    }
#line 2334 "y.tab.c"
break;
case 114:
#line 764 "src/gramatica.y"
	{ cant_errores++; }
#line 2339 "y.tab.c"
break;
case 115:
#line 766 "src/gramatica.y"
	{ cant_errores++; }
#line 2344 "y.tab.c"
break;
case 116:
#line 771 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2351 "y.tab.c"
break;
case 117:
#line 775 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2358 "y.tab.c"
break;
case 118:
#line 779 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2365 "y.tab.c"
break;
case 119:
#line 783 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2372 "y.tab.c"
break;
case 120:
#line 787 "src/gramatica.y"
	{
        yyval.simbolo = (yystack.l_mark[0].simbolo != NULL) ? cambiar_signo_constante(yystack.l_mark[0].simbolo, -1) : NULL;
    }
#line 2379 "y.tab.c"
break;
case 121:
#line 791 "src/gramatica.y"
	{
        yyval.simbolo = (yystack.l_mark[0].simbolo != NULL) ? cambiar_signo_constante(yystack.l_mark[0].simbolo, -1) : NULL;
    }
#line 2386 "y.tab.c"
break;
case 122:
#line 795 "src/gramatica.y"
	{
        yyval.simbolo = NULL;
    }
#line 2393 "y.tab.c"
break;
case 123:
#line 799 "src/gramatica.y"
	{
        yyval.simbolo = NULL;
    }
#line 2400 "y.tab.c"
break;
case 124:
#line 803 "src/gramatica.y"
	{
        yyval.simbolo = NULL;
    }
#line 2407 "y.tab.c"
break;
case 126:
#line 811 "src/gramatica.y"
	{ yyerror("Error: Estructura IF mal cerrada (posiblemente falta END_IF o el delimitador ';')."); yyerrok; }
#line 2412 "y.tab.c"
break;
case 127:
#line 813 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
#line 2417 "y.tab.c"
break;
case 128:
#line 815 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
#line 2422 "y.tab.c"
break;
case 129:
#line 820 "src/gramatica.y"
	{
        int celda_bf = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BF", yylineno);
        polaca_apilar_salto(celda_bf);
    }
#line 2431 "y.tab.c"
break;
case 130:
#line 829 "src/gramatica.y"
	{
        int celda_bi = polaca_desapilar_salto();
        polaca_poner_destino(celda_bi, polaca_posicion_actual());
    }
#line 2439 "y.tab.c"
break;
case 131:
#line 834 "src/gramatica.y"
	{
        int celda_bf = polaca_desapilar_salto();
        polaca_poner_destino(celda_bf, polaca_posicion_actual());
    }
#line 2447 "y.tab.c"
break;
case 132:
#line 842 "src/gramatica.y"
	{
        int celda_bi = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BI", yylineno);
        int celda_bf = polaca_desapilar_salto();
        polaca_poner_destino(celda_bf, polaca_posicion_actual());
        polaca_apilar_salto(celda_bi);
    }
#line 2458 "y.tab.c"
break;
case 135:
#line 858 "src/gramatica.y"
	{
        if (tope_from > 0) {
            ContextoFrom ctx = pila_from[--tope_from];

            /* Actualización de variable de control: id := id +/- cte3*/
            polaca_emitir_simbolo(ctx.id_control, yylineno);
            polaca_emitir_simbolo(ctx.id_control, yylineno);
            polaca_emitir_simbolo(ctx.cte3_sym, yylineno);
            polaca_emitir_operador(ctx.ascendente ? "+" : "-", yylineno);
            polaca_emitir_operador(":=", yylineno);

            /* Salto incondicional al inicio de la prueba*/
            int celda_bi = polaca_emitir_celda_vacia(yylineno);
            polaca_poner_destino(celda_bi, ctx.pos_inicio_prueba);
            polaca_emitir_operador("BI", yylineno);

            /* Backpatching: rellenar el BF con la posición siguiente al BI*/
            polaca_poner_destino(ctx.celda_bf, polaca_posicion_actual());
        }
    }
#line 2482 "y.tab.c"
break;
case 136:
#line 882 "src/gramatica.y"
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

        /* 1. Inicialización en Polaca: id, cte1, :=*/
        polaca_emitir_simbolo(id_sym, yylineno);
        polaca_emitir_simbolo(c1, yylineno);
        polaca_emitir_operador(":=", yylineno);

        /* 2. Inicio de prueba para el ciclo*/
        int pos_prueba = polaca_posicion_actual();

        /* 3. Condición de parada (Pág. 6):*/
        /* Si CTE1 <= CTE2: id < CTE2*/
        /* Si CTE1 > CTE2:  id > CTE2*/
        polaca_emitir_simbolo(id_sym, yylineno);
        polaca_emitir_simbolo(c2, yylineno);
        polaca_emitir_operador(asc ? "<" : ">", yylineno);

        int celda_bf = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BF", yylineno);

        /* 4. Guardar contexto en pila para ciclos anidados*/
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
#line 2548 "y.tab.c"
break;
case 138:
#line 946 "src/gramatica.y"
	{ yyerror("Error: Falta identificador (ID) en el encabezado."); yyerrok; }
#line 2553 "y.tab.c"
break;
case 139:
#line 948 "src/gramatica.y"
	{ yyerror("Error: Falta 'TO' en el encabezado de la iteración."); yyerrok; }
#line 2558 "y.tab.c"
break;
case 140:
#line 950 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
#line 2563 "y.tab.c"
break;
case 141:
#line 952 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
#line 2568 "y.tab.c"
break;
case 142:
#line 954 "src/gramatica.y"
	{ yyerror("Error: Falta CTE en el encabezado."); yyerrok; }
#line 2573 "y.tab.c"
break;
case 146:
#line 968 "src/gramatica.y"
	{
        polaca_emitir_operador(yystack.l_mark[-1].cadena, yylineno);
    }
#line 2580 "y.tab.c"
break;
case 147:
#line 974 "src/gramatica.y"
	{ yyval.cadena = "<"; }
#line 2585 "y.tab.c"
break;
case 148:
#line 975 "src/gramatica.y"
	{ yyval.cadena = ">"; }
#line 2590 "y.tab.c"
break;
case 149:
#line 976 "src/gramatica.y"
	{ yyval.cadena = ">="; }
#line 2595 "y.tab.c"
break;
case 150:
#line 977 "src/gramatica.y"
	{ yyval.cadena = "<="; }
#line 2600 "y.tab.c"
break;
case 151:
#line 978 "src/gramatica.y"
	{ yyval.cadena = "=="; }
#line 2605 "y.tab.c"
break;
case 152:
#line 979 "src/gramatica.y"
	{ yyval.cadena = "!="; }
#line 2610 "y.tab.c"
break;
#line 2612 "y.tab.c"
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
