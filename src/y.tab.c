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
                /* Chequeo Tema 22: si el parámetro formal es COMPTIME, el argumento real debe ser comptime*/
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

/* Estado para Tema 24: Clases con código */
static Simbolo *clase_actual_declaracion = NULL;
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 205 "src/gramatica.y"
typedef union YYSTYPE {
    struct Simbolo *simbolo;
    int val_int;
    int tipo_dato;
    const char *cadena;
    InfoExpr info_expr;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 241 "y.tab.c"

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
   27,   27,   28,   28,   30,   30,   11,   11,   12,   12,
   12,   12,   31,   31,   31,   31,   31,   36,   36,   32,
   32,    4,    4,    4,   35,   35,   35,   35,    5,    5,
    5,    5,    5,    6,    6,    6,    6,    6,   37,   37,
   37,   38,   38,   38,    7,   39,    7,    8,    8,    8,
    8,    8,    8,    8,   40,   40,   42,   41,   41,   45,
   44,   44,   46,   46,   46,   46,   43,   48,   48,   49,
   50,    9,   51,    9,   47,   47,    3,    3,    3,    3,
    3,    3,    3,    3,    3,   33,   33,   33,   33,   52,
   54,   54,   56,   53,   53,   34,   57,   57,   57,   57,
   57,   57,   57,   58,   59,   59,   55,    2,    2,    2,
    2,    2,    2,
};
static const YYINT yylen[] = {                            2,
    4,    3,    4,    3,    1,    0,    2,    1,    2,    2,
    2,    2,    2,    3,    2,    1,    1,    2,    3,    1,
    2,    5,    4,    8,    7,    4,    3,    3,    2,    1,
    2,    3,    1,    0,    7,    1,    0,    3,    1,    1,
    3,    2,    2,    1,    2,    2,    3,    3,    3,    2,
    3,    2,    1,    1,    1,    1,    1,    4,    3,    3,
    3,    1,    3,    4,    4,    4,    3,    2,    3,    3,
    3,    3,    1,    3,    3,    3,    3,    1,    3,    3,
    1,    3,    3,    1,    1,    0,    6,    1,    3,    4,
    1,    1,    4,    1,    4,    3,    2,    4,    3,    4,
    3,    3,    3,    3,    1,    1,    1,    3,    1,    2,
    0,    1,    0,    4,    1,    1,    1,    1,    2,    2,
    2,    2,    1,    2,    2,    3,    3,    5,    5,    4,
    3,    1,    1,    1,    2,    3,    8,    4,    7,    5,
    3,    3,    4,    1,    1,    1,    3,    1,    1,    1,
    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,   16,   17,    0,    0,    0,    0,    0,    8,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   34,   20,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    7,    9,   10,   11,   12,   13,    0,    0,    0,
   30,    0,    0,    0,    0,    0,    0,   27,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   53,
   54,   55,   56,   57,    0,    0,    0,    4,    0,   31,
    0,    0,   29,    0,    0,    1,   19,   36,    0,    0,
    0,   52,    0,    0,    0,  117,  118,  115,  116,    0,
    0,    0,    0,   94,    0,    0,   78,   85,   91,   92,
  111,  111,  123,    0,   68,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   48,    0,   50,  134,    0,    0,
    0,   47,   32,   28,    0,   23,   40,    0,    0,    0,
    0,   63,    0,   97,   86,    0,    0,    0,    0,  119,
  120,  124,  121,  122,  125,  150,  151,  152,  153,    0,
    0,  148,  149,    0,    0,    0,    0,    0,  109,    0,
    0,    0,    0,   67,    0,   59,    0,    0,    0,    0,
  141,    0,    0,   51,   49,  135,  127,  133,  132,  126,
    0,  145,  146,  136,  144,   22,   39,   42,    0,    0,
    0,    0,   44,    0,    0,   64,    0,    0,    0,    0,
  130,    0,   71,    0,   72,    0,    0,   76,   74,   77,
   75,    0,  111,    0,    0,  110,    0,    0,   66,   65,
   58,  143,    0,  138,    0,    0,   41,    0,   45,   46,
   35,   43,    0,   25,    0,  100,   90,   93,  129,    0,
   95,  108,    0,   98,  128,    0,  140,    0,  131,   38,
   24,    0,   84,    0,    0,    0,  105,    0,  106,    0,
    0,    0,   87,    0,    0,    0,    0,  102,    0,  101,
    0,    0,  139,    0,    0,   82,   83,  103,  104,  137,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  257,  275,  277,  278,  283,  287,  288,  297,  300,  301,
  302,  303,  304,  305,  306,  308,  310,  257,  297,  307,
  257,  257,  288,  307,  257,  276,  307,  256,  271,  298,
  257,  301,   59,   59,   59,   59,   59,  283,  288,  309,
  311,  309,  271,  298,   44,  313,  307,   40,  256,  257,
  256,  257,  268,  273,  274,  279,  291,  299,  318,  319,
  320,  321,  322,  323,  339,  344,  299,   59,  288,  257,
   44,   41,  311,   41,  299,   59,  257,  257,  312,   40,
   40,   59,   46,   91,  257,  258,  259,  266,  267,  284,
   40,   43,   45,  290,  292,  293,  294,  295,  327,  328,
  329,  332,  334,  342,  256,   40,   40,  257,   40,   61,
  342,  261,   61,  256,  272,  318,   59,  298,  318,  340,
  282,  272,  257,  311,  297,  298,  271,  285,  314,  309,
   41,  257,  292,   40,   61,   46,   91,   40,  342,  258,
  259,  334,  258,  259,  334,  262,  263,  264,  265,   43,
   45,   60,   62,  289,   42,   47,  330,  335,  336,  337,
  330,   41,  260,   41,  292,   41,  292,   61,  342,  290,
   41,  292,  292,   59,   59,   59,  256,  269,  270,  341,
  343,  298,  318,  345,  346,  298,  257,  271,  316,  302,
  303,  315,  317,   41,  297,   93,  326,  257,  292,  292,
   41,  340,  256,  293,  256,  293,  292,  256,  294,  256,
  294,   41,   44,  257,  292,  296,   41,  340,   41,   41,
   41,  280,  290,   41,  280,  340,  271,   44,   59,   59,
  272,  317,  297,  298,   40,   40,   93,   41,  341,   91,
  331,  336,   61,  331,  341,  280,  290,  290,  270,  257,
  298,  257,  295,  324,  325,  256,  258,  333,  334,  338,
  290,  281,   41,   43,   45,   42,   47,   93,   44,   93,
  292,  281,  290,  325,  325,  295,  295,  258,  334,  290,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          6,
    7,  154,   94,   57,   95,   96,   97,   98,  216,    8,
  118,   58,    9,   10,   11,   12,   13,   14,   15,   20,
   16,   40,   17,   41,   79,   46,  129,  192,  189,  193,
  119,   60,   61,   62,   63,   64,  254,  255,  197,   99,
  100,  101,  157,  241,  102,  258,  103,  158,  159,  160,
  260,   65,  120,  180,  104,  181,   66,  184,  185,
};
static const YYINT yysindex[] = {                       -84,
  125, -233,    0,    0, -197,    0, -198, -161,  297,    0,
  -27,  -18,    3,   65,   76,   67,   67, -116, -140,  144,
    0,    0, -116,  144,  152, -142,  144,  353,  353,  146,
 -116,    0,    0,    0,    0,    0,    0,   14,  -17,  -28,
    0,  -15,  353,  166,   10,   37,  144,    0,  163,  189,
  212,  -34,  -36,  -32,  233,  -40,  -55,  322,  244,    0,
    0,    0,    0,    0,  332,   39,  351,    0,   51,    0,
   67,  297,    0, -161,  351,    0,    0,    0, -182,   67,
  274,    0,   79,   43,   15,    0,    0,    0,    0,  299,
   43,   66,  210,    0,  410,   16,    0,    0,    0,    0,
    0,    0,    0,  321,    0,   -6,   -1,   90,   43,  318,
  327,   43,   43,  315,    0,  328,    0,    0,  334,  -80,
  332,    0,    0,    0, -161,    0,    0,  -92,   14,   -8,
  297,    0,    8,    0,    0,  157,   43,   43,  285,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -20,
  200,    0,    0,   43,  229,  241,  360,  365,    0,  252,
  376,  332,  377,    0,  460,    0,  483,   89,  381,  150,
    0,  137,  137,    0,    0,    0,    0,    0,    0,    0,
  332,    0,    0,    0,    0,    0,    0,    0,  -43,  372,
  375,  118,    0,  297, -161,    0,  398,  409,    9,  506,
    0,  -54,    0,   16,    0,   16,  137,    0,    0,    0,
    0,  359,    0,   93,  137,    0,  359,  -54,    0,    0,
    0,    0,  153,    0,  318,  182,    0,  205,    0,    0,
    0,    0, -161,    0,  273,    0,    0,    0,    0,  181,
    0,    0,    0,    0,    0,  318,    0,  183,    0,    0,
    0,  -12,    0,  522,   70,  378,    0,   12,    0,   43,
  201,  318,    0,  273,  273,  273,  273,    0,   71,    0,
  137,  318,    0,   70,   70,    0,    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                      -104,
 -104,    0,    0,    0,    0,    0,    0,    0, -103,    0,
    0,    0,    0,    0,    0,    0,    0,  111,    0,  422,
    0,    0,    0,  424,  111,    0,  430,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    2,    0,
    0,    0,    0,  490,    0,  -74,  432,    0,    0,    0,
    0,  -51,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -104,    0,    0,  502,    0,    0,    0,    0,    0,
  196,    0,    0,    0,   25,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  115,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  418,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -104,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  453,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  464,  230,    0,
    0,  457,  458,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -104,    0,    0,    0,   49,    0,    0,
    0,    0,    0,  142,    0,  382,  172,    0,    0,    0,
    0,   78,    0,  643,  128,    0,  102,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -25,    0,    0,    0,    0,    0,    0,    0,
    0,  571,    0,    0,  588,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  168,    0,    0,  617,  622,    0,    0,    0,    0,    0,
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
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
   33,    0,  325,    0,  408,  126,  198, -138,    0,   26,
  311,  171,    0,  518, -127, -118,    0,    0,    0,  143,
    0,   -3,    0,  -23,    0,    0,    0,    0,    0,  337,
  494,    0,    0,    0,    0,    0,    0,  127,    0,    0,
    0,    0,  431,  317,    0,    0,  -62,    0,  330,    0,
    0,    0, -117, -119,   -9,    0,    0,    0,    0,
};
#define YYTABLESIZE 690
static const YYINT yytable[] = {                        109,
  228,  190,   92,   91,   93,  113,   92,  106,   93,   62,
  191,   83,   72,   42,   86,   71,   73,  113,   73,  113,
  110,  202,   92,   21,   93,   74,   19,  134,   71,  142,
  145,   33,  194,  136,  164,   71,   92,   23,   93,  166,
   34,   92,   33,   93,  218,   33,  111,  124,   39,   39,
  150,  150,  151,  151,  134,  269,   84,  155,   25,   22,
  136,   35,  156,  226,  190,   88,   88,   88,   88,   88,
   69,   88,   39,  191,   39,  135,  130,   26,  137,    3,
    4,  139,  239,   88,   88,   92,   88,   93,  127,   89,
   89,   89,   89,   89,   28,   89,  253,  125,  245,  169,
  196,  237,  128,   39,  270,  137,   73,   89,   89,   29,
   89,  266,   39,   49,   50,   28,  267,   88,   96,   96,
   96,   96,   96,   36,   96,  253,  253,  276,  277,  134,
   43,   92,  134,   93,   37,  136,   96,   96,  136,   96,
   22,   89,   99,   99,   99,   99,   99,   24,   99,   27,
  168,    6,    5,  243,   20,   73,  195,   73,   73,   73,
   99,   99,   39,   99,  187,   47,    6,    5,  112,   20,
   96,  112,    1,   73,   73,  177,   73,  259,  188,  150,
  137,  151,   69,  137,   69,   69,   69,   45,  178,  179,
    2,   48,    3,    4,   99,   92,   37,   93,    5,   67,
   69,   69,   80,   69,   68,  112,  279,   73,  114,   62,
   37,  114,  147,   75,  178,  179,  108,   86,   87,  233,
   85,   86,   87,  105,   76,   88,   89,  227,   81,   88,
   89,  113,  113,  113,   69,  203,   85,   86,   87,   70,
  113,  113,   92,   90,   93,   88,   89,   90,    3,    4,
   85,   86,   87,  163,   38,   85,   86,   87,  113,   88,
   89,    3,    4,   90,   88,   89,   77,   38,    3,    4,
   82,   92,  107,   93,   38,  204,  206,   90,   33,   33,
   88,   88,   90,   92,   33,   93,   88,   88,   88,   88,
    3,    4,   88,   78,   92,   88,   93,   88,   88,   85,
   86,   87,  117,   88,   89,   89,   88,  123,   88,   89,
   89,   89,   89,   89,  131,   92,   89,   93,   30,   89,
  121,   89,   89,  140,  141,  201,   90,   89,  278,   44,
   89,   88,   89,   96,   96,  132,   88,   89,  138,   96,
   96,   96,   96,    3,    4,   96,   86,   87,   96,   38,
   96,   96,  209,  211,   88,   89,   96,   99,   99,   96,
   92,  162,   93,   99,   99,   99,   99,  171,  222,   99,
   73,   73,   99,  174,   99,   99,   73,   73,   73,   73,
   99,   18,   73,   99,  126,   73,  175,   73,   73,  231,
  274,  275,  176,   73,    3,    4,   73,   69,   69,    2,
  212,    3,    4,   69,   69,   69,   69,    5,  213,   69,
   86,   87,   69,  198,   69,   69,  217,  219,   88,   89,
   69,  224,   70,   69,   70,   70,   70,  147,  147,  225,
  229,  182,  246,  230,  170,  186,  256,  235,  257,  147,
   70,   70,  147,   70,  147,  147,   88,   89,  236,  240,
  147,  249,  150,  147,  151,  205,   85,   86,   87,   88,
   88,  250,   88,  262,   88,   88,   89,  143,  144,  152,
  268,  153,   26,   26,   70,   88,   89,   88,   26,   88,
   21,  272,   15,   90,  208,   85,   86,   87,   18,    2,
   14,  133,  223,  107,   88,   89,  210,   85,   86,   87,
  220,    3,  150,   86,  151,  234,   88,   89,  214,   86,
   87,  142,   90,  165,  167,   60,   61,   88,   89,  172,
  173,   59,   59,  221,   90,  150,   32,  151,  232,  252,
   86,   87,  161,  244,    0,   90,   59,    0,   88,   89,
   28,   52,  242,  251,  199,  200,  238,  247,  150,  248,
  151,  116,   53,   31,    0,   29,   90,   54,   55,    0,
  116,  207,  263,   56,  264,    0,  265,  215,  116,    0,
  261,    2,    0,    3,    4,   86,   87,  114,   52,    5,
    0,    0,    0,   88,   89,    0,  273,   28,   52,   53,
    0,    0,    0,  115,   54,   55,  280,    0,    0,   53,
   56,    0,   29,    0,   54,   55,  114,   52,   51,   52,
   56,   88,   88,   88,  183,   88,    0,   88,   53,    0,
   53,    0,  122,   54,   55,   54,   55,    0,   81,   56,
   81,   56,   81,    0,    0,    0,    0,   70,   70,    0,
    0,    0,    0,   70,   70,   70,   70,    0,    0,   70,
    0,    0,   70,    0,   70,   70,    0,   79,    0,   79,
   70,   79,   80,   70,   80,    0,   80,  271,    0,    0,
    0,  146,  147,  148,  149,    0,    0,    0,    0,   88,
   88,   88,   88,   88,   88,   88,   88,   88,    0,   88,
};
static const YYINT yycheck[] = {                         40,
   44,  129,   43,   40,   45,   61,   43,   40,   45,   61,
  129,   46,   41,   17,   40,   44,   40,   43,   42,   45,
   61,  139,   43,  257,   45,   41,    1,   40,   44,   92,
   93,   59,   41,   46,   41,   44,   43,    5,   45,   41,
   59,   43,   41,   45,  162,   44,   56,   71,   16,   17,
   43,   43,   45,   45,   40,   44,   91,   42,  257,  257,
   46,   59,   47,  181,  192,   41,   42,   43,   44,   45,
   38,   47,   40,  192,   42,   61,   80,  276,   91,  277,
  278,   91,  202,   59,   60,   43,   62,   45,  271,   41,
   42,   43,   44,   45,  256,   47,  235,   72,  218,  109,
   93,   93,  285,   71,   93,   91,  130,   59,   60,  271,
   62,   42,   80,  256,  257,  256,   47,   93,   41,   42,
   43,   44,   45,   59,   47,  264,  265,  266,  267,   40,
  271,   43,   40,   45,   59,   46,   59,   60,   46,   62,
  257,   93,   41,   42,   43,   44,   45,    5,   47,    7,
   61,  256,  256,   61,   44,   41,  131,   43,   44,   45,
   59,   60,  130,   62,  257,   23,  271,  271,   41,   59,
   93,   44,  257,   59,   60,  256,   62,  240,  271,   43,
   91,   45,   41,   91,   43,   44,   45,   44,  269,  270,
  275,   40,  277,  278,   93,   43,  271,   45,  283,   29,
   59,   60,   40,   62,   59,  261,  269,   93,   41,  261,
  285,   44,   41,   43,  269,  270,  257,  258,  259,  194,
  257,  258,  259,  256,   59,  266,  267,  271,   40,  266,
  267,  257,  258,  259,   93,  256,  257,  258,  259,  257,
  266,  267,   43,  284,   45,  266,  267,  284,  277,  278,
  257,  258,  259,  260,  283,  257,  258,  259,  284,  266,
  267,  277,  278,  284,  266,  267,  257,  283,  277,  278,
   59,   43,   40,   45,  283,  150,  151,  284,  277,  278,
  256,  257,  284,   43,  283,   45,  262,  263,  264,  265,
  277,  278,  268,  257,   43,  271,   45,  273,  274,  257,
  258,  259,   59,  279,  256,  257,  282,  257,  266,  267,
  262,  263,  264,  265,   41,   43,  268,   45,    8,  271,
  282,  273,  274,  258,  259,   41,  284,  279,  258,   19,
  282,  266,  267,  256,  257,  257,  266,  267,   40,  262,
  263,  264,  265,  277,  278,  268,  258,  259,  271,  283,
  273,  274,  155,  156,  266,  267,  279,  256,  257,  282,
   43,   41,   45,  262,  263,  264,  265,   41,  280,  268,
  256,  257,  271,   59,  273,  274,  262,  263,  264,  265,
  279,  257,  268,  282,   74,  271,   59,  273,  274,  272,
  264,  265,   59,  279,  277,  278,  282,  256,  257,  275,
   41,  277,  278,  262,  263,  264,  265,  283,   44,  268,
  258,  259,  271,  257,  273,  274,   41,   41,  266,  267,
  279,   41,   41,  282,   43,   44,   45,  256,  257,  280,
   59,  121,  280,   59,  110,  125,  256,   40,  258,  268,
   59,   60,  271,   62,  273,  274,  266,  267,   40,   91,
  279,  270,   43,  282,   45,  256,  257,  258,  259,   42,
   43,  257,   45,  281,   47,  266,  267,  258,  259,   60,
   93,   62,  277,  278,   93,  266,  267,   60,  283,   62,
   59,  281,   59,  284,  256,  257,  258,  259,   59,    0,
   59,   84,  168,   41,  266,  267,  256,  257,  258,  259,
   41,    0,   43,   40,   45,  195,  266,  267,  257,  258,
  259,  282,  284,  106,  107,   59,   59,  266,  267,  112,
  113,   28,   29,   41,  284,   43,    9,   45,  192,  257,
  258,  259,  102,  217,   -1,  284,   43,   -1,  266,  267,
  256,  257,  213,  233,  137,  138,   41,  223,   43,  225,
   45,   58,  268,  257,   -1,  271,  284,  273,  274,   -1,
   67,  154,   41,  279,   43,   -1,   45,  160,   75,   -1,
  246,  275,   -1,  277,  278,  258,  259,  256,  257,  283,
   -1,   -1,   -1,  266,  267,   -1,  262,  256,  257,  268,
   -1,   -1,   -1,  272,  273,  274,  272,   -1,   -1,  268,
  279,   -1,  271,   -1,  273,  274,  256,  257,  256,  257,
  279,   41,   42,   43,  121,   45,   -1,   47,  268,   -1,
  268,   -1,  272,  273,  274,  273,  274,   -1,   41,  279,
   43,  279,   45,   -1,   -1,   -1,   -1,  256,  257,   -1,
   -1,   -1,   -1,  262,  263,  264,  265,   -1,   -1,  268,
   -1,   -1,  271,   -1,  273,  274,   -1,   41,   -1,   43,
  279,   45,   41,  282,   43,   -1,   45,  260,   -1,   -1,
   -1,  262,  263,  264,  265,   -1,   -1,   -1,   -1,  262,
  263,  264,  265,   41,   42,   43,   44,   45,   -1,   47,
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
"expresion_aritmetica","termino","operando","operando_base","parametro_real",
"bloque_declarativo","bloque_ejecutable","lista_ejecutables",
"lista_declaraciones","declaracion","declaracion_variable",
"declaracion_funcion","declaracion_clase","declaracion_objeto",
"declaracion_comptime","lista_variables","encabezado_funcion",
"lista_parametros","encabezado_funcion_sin_kw","parametro","codigo_clase","$$1",
"encabezado_clase","miembros_clase","lista_clase","miembro","sentencia",
"asignacion","if_sentencia","iteracion","impresion","sentencia_retorno",
"expresion_sin_asignacion","termino_sin_asignacion","$$2","llamada_con_orden",
"llamada_metodo_con_orden","llamada_encabezado","parametros_reales",
"orden_evaluacion","llamada_metodo_encabezado","lista_enteros",
"constante_invalida","lista_parametros_reales","parametro_real_item",
"iniciar_parametro","$$3","if_encabezado","bloque_if","fin_if","condicion",
"else_encabezado","encabezado_iteracion","cuerpo_iteracion",
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
#line 1257 "src/gramatica.y"

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
#line 1084 "y.tab.c"

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
#line 230 "src/gramatica.y"
	{
        /* Programa finalizado correctamente*/
    }
#line 1759 "y.tab.c"
break;
case 2:
#line 234 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador ; al final del bloque ejecutable."); yyerrok; }
#line 1764 "y.tab.c"
break;
case 3:
#line 236 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador END al final del bloque ejecutable."); yyerrok; }
#line 1769 "y.tab.c"
break;
case 4:
#line 238 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
#line 1774 "y.tab.c"
break;
case 14:
#line 261 "src/gramatica.y"
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
#line 1791 "y.tab.c"
break;
case 15:
#line 275 "src/gramatica.y"
	{ yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
#line 1796 "y.tab.c"
break;
case 16:
#line 279 "src/gramatica.y"
	{ yyval.tipo_dato = TIPO_INTEGER; }
#line 1801 "y.tab.c"
break;
case 17:
#line 280 "src/gramatica.y"
	{ yyval.tipo_dato = TIPO_SINGLEF; }
#line 1806 "y.tab.c"
break;
case 18:
#line 285 "src/gramatica.y"
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
#line 1837 "y.tab.c"
break;
case 19:
#line 316 "src/gramatica.y"
	{
        if (cant_vars_declaradas < 64) {
            lista_vars_declaradas[cant_vars_declaradas++] = yystack.l_mark[0].simbolo;
        }
    }
#line 1846 "y.tab.c"
break;
case 20:
#line 322 "src/gramatica.y"
	{
        cant_vars_declaradas = 0;
        if (cant_vars_declaradas < 64) {
            lista_vars_declaradas[cant_vars_declaradas++] = yystack.l_mark[0].simbolo;
        }
    }
#line 1856 "y.tab.c"
break;
case 21:
#line 332 "src/gramatica.y"
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
#line 1876 "y.tab.c"
break;
case 22:
#line 352 "src/gramatica.y"
	{
        if (tope_fn_decl > 0) tope_fn_decl--;
        polaca_desapilar_actual();
        salir_ambito();
    }
#line 1885 "y.tab.c"
break;
case 23:
#line 358 "src/gramatica.y"
	{
        if (tope_fn_decl > 0) tope_fn_decl--;
        polaca_desapilar_actual();
        salir_ambito();
    }
#line 1894 "y.tab.c"
break;
case 24:
#line 364 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
#line 1899 "y.tab.c"
break;
case 25:
#line 366 "src/gramatica.y"
	{ yyerror("Error: Faltan los parametros de la función."); yyerrok; }
#line 1904 "y.tab.c"
break;
case 26:
#line 371 "src/gramatica.y"
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
#line 1926 "y.tab.c"
break;
case 27:
#line 393 "src/gramatica.y"
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
#line 1948 "y.tab.c"
break;
case 29:
#line 416 "src/gramatica.y"
	{ yyerror("Error: Falta de ',' en declaración de parámetros."); yyerrok; }
#line 1953 "y.tab.c"
break;
case 31:
#line 422 "src/gramatica.y"
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
#line 1982 "y.tab.c"
break;
case 32:
#line 448 "src/gramatica.y"
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
#line 2015 "y.tab.c"
break;
case 33:
#line 478 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
#line 2020 "y.tab.c"
break;
case 34:
#line 482 "src/gramatica.y"
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
#line 2036 "y.tab.c"
break;
case 35:
#line 494 "src/gramatica.y"
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
#line 2065 "y.tab.c"
break;
case 36:
#line 523 "src/gramatica.y"
	{
        if (clase_actual_declaracion != NULL) {
            clase_actual_declaracion->codigo_clase = strdup(yystack.l_mark[0].simbolo->lexema);
        }
    }
#line 2074 "y.tab.c"
break;
case 37:
#line 528 "src/gramatica.y"
	{ yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
#line 2079 "y.tab.c"
break;
case 42:
#line 540 "src/gramatica.y"
	{ yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
#line 2084 "y.tab.c"
break;
case 48:
#line 556 "src/gramatica.y"
	{ yyerror("Error: Falta de delimitador de sentencias ejecutables BEGIN."); yyerrok; }
#line 2089 "y.tab.c"
break;
case 51:
#line 563 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 2094 "y.tab.c"
break;
case 52:
#line 565 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 2099 "y.tab.c"
break;
case 58:
#line 578 "src/gramatica.y"
	{
        polaca_emitir_operador("RET", yylineno);
    }
#line 2106 "y.tab.c"
break;
case 59:
#line 582 "src/gramatica.y"
	{
        polaca_emitir_operador("RET", yylineno);
    }
#line 2113 "y.tab.c"
break;
case 60:
#line 589 "src/gramatica.y"
	{
        Simbolo *dest = yystack.l_mark[-2].simbolo;
        if (dest != NULL) {
            /* Tema 22: Asignación a variable COMPTIME*/
            if (dest->uso == USO_VARIABLE_COMPTIME) {
                if (!yystack.l_mark[0].info_expr.es_comptime) {
                    registrar_error(
                        ETAPA_SEMANTICO,
                        yylineno,
                        "No se puede asignar una expresión no determinable en tiempo de compilación a la variable COMPTIME '%s'.",
                        dest->nombre_original ? dest->nombre_original : dest->lexema
                    );
                } else {
                    dest->valor_comptime_valido = true;
                    dest->valor_int = yystack.l_mark[0].info_expr.val_int;
                    dest->valor_float = yystack.l_mark[0].info_expr.val_float;
                }
            }

            /* Tema 24: Asignación por estructura en objetos con código*/
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
#line 2163 "y.tab.c"
break;
case 61:
#line 636 "src/gramatica.y"
	{ yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
#line 2168 "y.tab.c"
break;
case 62:
#line 641 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[0].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[0].simbolo->lexema);
            s = yystack.l_mark[0].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
        yyval.simbolo = s;
    }
#line 2181 "y.tab.c"
break;
case 63:
#line 651 "src/gramatica.y"
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
#line 2196 "y.tab.c"
break;
case 64:
#line 663 "src/gramatica.y"
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
#line 2210 "y.tab.c"
break;
case 65:
#line 677 "src/gramatica.y"
	{
        polaca_emitir_operador("POUT", yylineno);
    }
#line 2217 "y.tab.c"
break;
case 66:
#line 681 "src/gramatica.y"
	{
        polaca_emitir_simbolo(yystack.l_mark[-1].simbolo, yylineno);
        polaca_emitir_operador("POUT", yylineno);
    }
#line 2225 "y.tab.c"
break;
case 67:
#line 686 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 2230 "y.tab.c"
break;
case 68:
#line 688 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 2235 "y.tab.c"
break;
case 69:
#line 693 "src/gramatica.y"
	{
        polaca_emitir_operador("+", yylineno);
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = (yystack.l_mark[-2].info_expr.tipo == TIPO_SINGLEF || yystack.l_mark[0].info_expr.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
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
#line 2256 "y.tab.c"
break;
case 70:
#line 711 "src/gramatica.y"
	{
        polaca_emitir_operador("-", yylineno);
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = (yystack.l_mark[-2].info_expr.tipo == TIPO_SINGLEF || yystack.l_mark[0].info_expr.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
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
#line 2277 "y.tab.c"
break;
case 71:
#line 729 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '+'."); yyerrok; yyval.info_expr.es_comptime = false; }
#line 2282 "y.tab.c"
break;
case 72:
#line 731 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '-'."); yyerrok; yyval.info_expr.es_comptime = false; }
#line 2287 "y.tab.c"
break;
case 73:
#line 733 "src/gramatica.y"
	{
        yyval.info_expr = yystack.l_mark[0].info_expr;
    }
#line 2294 "y.tab.c"
break;
case 74:
#line 740 "src/gramatica.y"
	{
        polaca_emitir_operador("*", yylineno);
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = (yystack.l_mark[-2].info_expr.tipo == TIPO_SINGLEF || yystack.l_mark[0].info_expr.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
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
#line 2315 "y.tab.c"
break;
case 75:
#line 758 "src/gramatica.y"
	{
        polaca_emitir_operador("/", yylineno);
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = (yystack.l_mark[-2].info_expr.tipo == TIPO_SINGLEF || yystack.l_mark[0].info_expr.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;
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
#line 2341 "y.tab.c"
break;
case 76:
#line 781 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '*'."); yyerrok; yyval.info_expr.es_comptime = false; }
#line 2346 "y.tab.c"
break;
case 77:
#line 783 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '/'."); yyerrok; yyval.info_expr.es_comptime = false; }
#line 2351 "y.tab.c"
break;
case 78:
#line 785 "src/gramatica.y"
	{
        yyval.info_expr = yystack.l_mark[0].info_expr;
    }
#line 2358 "y.tab.c"
break;
case 79:
#line 792 "src/gramatica.y"
	{
        polaca_emitir_operador("+", yylineno);
    }
#line 2365 "y.tab.c"
break;
case 80:
#line 796 "src/gramatica.y"
	{
        polaca_emitir_operador("-", yylineno);
    }
#line 2372 "y.tab.c"
break;
case 82:
#line 804 "src/gramatica.y"
	{
        polaca_emitir_operador("*", yylineno);
    }
#line 2379 "y.tab.c"
break;
case 83:
#line 808 "src/gramatica.y"
	{
        polaca_emitir_operador("/", yylineno);
    }
#line 2386 "y.tab.c"
break;
case 85:
#line 816 "src/gramatica.y"
	{
        yyval.info_expr = yystack.l_mark[0].info_expr;
    }
#line 2393 "y.tab.c"
break;
case 86:
#line 819 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-1].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[-1].simbolo->lexema);
            s = yystack.l_mark[-1].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
    }
#line 2405 "y.tab.c"
break;
case 87:
#line 827 "src/gramatica.y"
	{
        polaca_emitir_operador(":=", yylineno);
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-5].simbolo->lexema);
        polaca_emitir_simbolo(s ? s : yystack.l_mark[-5].simbolo, yylineno);
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.simbolo_ref = s;
        yyval.info_expr.tipo = s ? s->tipo : TIPO_NO_ASIGNADO;
    }
#line 2417 "y.tab.c"
break;
case 88:
#line 839 "src/gramatica.y"
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
            } else {
                yyval.info_expr.es_comptime = true;
                yyval.info_expr.val_int = s->valor_int;
                yyval.info_expr.val_float = s->valor_float;
            }
        } else {
            yyval.info_expr.es_comptime = false;
        }
        polaca_emitir_simbolo(s, yylineno);
    }
#line 2443 "y.tab.c"
break;
case 89:
#line 862 "src/gramatica.y"
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
    }
#line 2460 "y.tab.c"
break;
case 90:
#line 876 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-3].simbolo->lexema);
        polaca_emitir_simbolo(s ? s : yystack.l_mark[-3].simbolo, yylineno);
        polaca_emitir_operador("[]", yylineno);
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.simbolo_ref = s;
        yyval.info_expr.tipo = s ? s->tipo : TIPO_NO_ASIGNADO;
    }
#line 2472 "y.tab.c"
break;
case 91:
#line 885 "src/gramatica.y"
	{
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = TIPO_NO_ASIGNADO;
    }
#line 2481 "y.tab.c"
break;
case 92:
#line 891 "src/gramatica.y"
	{
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.simbolo_ref = NULL;
        yyval.info_expr.tipo = TIPO_NO_ASIGNADO;
    }
#line 2490 "y.tab.c"
break;
case 93:
#line 897 "src/gramatica.y"
	{
        polaca_emitir_operador("TOSF", yylineno);
        yyval.info_expr.es_comptime = yystack.l_mark[-1].info_expr.es_comptime;
        yyval.info_expr.tipo = TIPO_SINGLEF;
        yyval.info_expr.val_float = yystack.l_mark[-1].info_expr.es_comptime ? (double)yystack.l_mark[-1].info_expr.val_int : 0.0;
        yyval.info_expr.val_int = (long)yyval.info_expr.val_float;
        yyval.info_expr.simbolo_ref = NULL;
    }
#line 2502 "y.tab.c"
break;
case 94:
#line 906 "src/gramatica.y"
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
#line 2525 "y.tab.c"
break;
case 95:
#line 929 "src/gramatica.y"
	{
        finalizar_invocacion_con_orden();
    }
#line 2532 "y.tab.c"
break;
case 96:
#line 933 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 2537 "y.tab.c"
break;
case 97:
#line 938 "src/gramatica.y"
	{
        iniciar_invocacion(yystack.l_mark[-1].simbolo->lexema, yylineno);
    }
#line 2544 "y.tab.c"
break;
case 98:
#line 945 "src/gramatica.y"
	{
        finalizar_invocacion_con_orden();
    }
#line 2551 "y.tab.c"
break;
case 99:
#line 949 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 2556 "y.tab.c"
break;
case 100:
#line 954 "src/gramatica.y"
	{
        iniciar_invocacion(yystack.l_mark[-1].simbolo->lexema, yylineno);
    }
#line 2563 "y.tab.c"
break;
case 102:
#line 962 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 2568 "y.tab.c"
break;
case 103:
#line 967 "src/gramatica.y"
	{
        long val = parsear_valor_entero(yystack.l_mark[0].simbolo ? yystack.l_mark[0].simbolo->lexema : "0");
        agregar_orden_invocacion((int)val);
    }
#line 2576 "y.tab.c"
break;
case 105:
#line 973 "src/gramatica.y"
	{
        long val = parsear_valor_entero(yystack.l_mark[0].simbolo ? yystack.l_mark[0].simbolo->lexema : "0");
        agregar_orden_invocacion((int)val);
    }
#line 2584 "y.tab.c"
break;
case 110:
#line 991 "src/gramatica.y"
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
#line 2600 "y.tab.c"
break;
case 111:
#line 1007 "src/gramatica.y"
	{
        Polaca *p = crear_polaca("param_tmp");
        polaca_apilar_actual(p);
    }
#line 2608 "y.tab.c"
break;
case 112:
#line 1015 "src/gramatica.y"
	{
        yyval.info_expr = yystack.l_mark[0].info_expr;
    }
#line 2615 "y.tab.c"
break;
case 113:
#line 1018 "src/gramatica.y"
	{
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-1].simbolo->lexema);
        if (s == NULL) {
            registrar_error(ETAPA_SEMANTICO, yylineno, "Variable o identificador '%s' no declarado o fuera de alcance.", yystack.l_mark[-1].simbolo->lexema);
            s = yystack.l_mark[-1].simbolo;
        }
        polaca_emitir_simbolo(s, yylineno);
    }
#line 2627 "y.tab.c"
break;
case 114:
#line 1026 "src/gramatica.y"
	{
        polaca_emitir_operador(":=", yylineno);
        Simbolo *s = buscar_identificador_semantico(obtener_tabla_simbolos(), yystack.l_mark[-3].simbolo->lexema);
        polaca_emitir_simbolo(s ? s : yystack.l_mark[-3].simbolo, yylineno);
        yyval.info_expr.es_comptime = false;
        yyval.info_expr.tipo = yystack.l_mark[0].info_expr.tipo;
        yyval.info_expr.simbolo_ref = s;
    }
#line 2639 "y.tab.c"
break;
case 115:
#line 1038 "src/gramatica.y"
	{ cant_errores++; }
#line 2644 "y.tab.c"
break;
case 116:
#line 1040 "src/gramatica.y"
	{ cant_errores++; }
#line 2649 "y.tab.c"
break;
case 117:
#line 1045 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2656 "y.tab.c"
break;
case 118:
#line 1049 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2663 "y.tab.c"
break;
case 119:
#line 1053 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2670 "y.tab.c"
break;
case 120:
#line 1057 "src/gramatica.y"
	{
        yyval.simbolo = yystack.l_mark[0].simbolo;
    }
#line 2677 "y.tab.c"
break;
case 121:
#line 1061 "src/gramatica.y"
	{
        yyval.simbolo = (yystack.l_mark[0].simbolo != NULL) ? cambiar_signo_constante(yystack.l_mark[0].simbolo, -1) : NULL;
    }
#line 2684 "y.tab.c"
break;
case 122:
#line 1065 "src/gramatica.y"
	{
        yyval.simbolo = (yystack.l_mark[0].simbolo != NULL) ? cambiar_signo_constante(yystack.l_mark[0].simbolo, -1) : NULL;
    }
#line 2691 "y.tab.c"
break;
case 123:
#line 1069 "src/gramatica.y"
	{
        yyval.simbolo = NULL;
    }
#line 2698 "y.tab.c"
break;
case 124:
#line 1073 "src/gramatica.y"
	{
        yyval.simbolo = NULL;
    }
#line 2705 "y.tab.c"
break;
case 125:
#line 1077 "src/gramatica.y"
	{
        yyval.simbolo = NULL;
    }
#line 2712 "y.tab.c"
break;
case 127:
#line 1085 "src/gramatica.y"
	{ yyerror("Error: Estructura IF mal cerrada (posiblemente falta END_IF o el delimitador ';')."); yyerrok; }
#line 2717 "y.tab.c"
break;
case 128:
#line 1087 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
#line 2722 "y.tab.c"
break;
case 129:
#line 1089 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
#line 2727 "y.tab.c"
break;
case 130:
#line 1094 "src/gramatica.y"
	{
        int celda_bf = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BF", yylineno);
        polaca_apilar_salto(celda_bf);
    }
#line 2736 "y.tab.c"
break;
case 131:
#line 1103 "src/gramatica.y"
	{
        int celda_bi = polaca_desapilar_salto();
        polaca_poner_destino(celda_bi, polaca_posicion_actual());
    }
#line 2744 "y.tab.c"
break;
case 132:
#line 1108 "src/gramatica.y"
	{
        int celda_bf = polaca_desapilar_salto();
        polaca_poner_destino(celda_bf, polaca_posicion_actual());
    }
#line 2752 "y.tab.c"
break;
case 133:
#line 1116 "src/gramatica.y"
	{
        int celda_bi = polaca_emitir_celda_vacia(yylineno);
        polaca_emitir_operador("BI", yylineno);
        int celda_bf = polaca_desapilar_salto();
        polaca_poner_destino(celda_bf, polaca_posicion_actual());
        polaca_apilar_salto(celda_bi);
    }
#line 2763 "y.tab.c"
break;
case 136:
#line 1132 "src/gramatica.y"
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
#line 2787 "y.tab.c"
break;
case 137:
#line 1156 "src/gramatica.y"
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
#line 2853 "y.tab.c"
break;
case 139:
#line 1220 "src/gramatica.y"
	{ yyerror("Error: Falta identificador (ID) en el encabezado."); yyerrok; }
#line 2858 "y.tab.c"
break;
case 140:
#line 1222 "src/gramatica.y"
	{ yyerror("Error: Falta 'TO' en el encabezado de la iteración."); yyerrok; }
#line 2863 "y.tab.c"
break;
case 141:
#line 1224 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
#line 2868 "y.tab.c"
break;
case 142:
#line 1226 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
#line 2873 "y.tab.c"
break;
case 143:
#line 1228 "src/gramatica.y"
	{ yyerror("Error: Falta CTE en el encabezado."); yyerrok; }
#line 2878 "y.tab.c"
break;
case 147:
#line 1242 "src/gramatica.y"
	{
        polaca_emitir_operador(yystack.l_mark[-1].cadena, yylineno);
    }
#line 2885 "y.tab.c"
break;
case 148:
#line 1248 "src/gramatica.y"
	{ yyval.cadena = "<"; }
#line 2890 "y.tab.c"
break;
case 149:
#line 1249 "src/gramatica.y"
	{ yyval.cadena = ">"; }
#line 2895 "y.tab.c"
break;
case 150:
#line 1250 "src/gramatica.y"
	{ yyval.cadena = ">="; }
#line 2900 "y.tab.c"
break;
case 151:
#line 1251 "src/gramatica.y"
	{ yyval.cadena = "<="; }
#line 2905 "y.tab.c"
break;
case 152:
#line 1252 "src/gramatica.y"
	{ yyval.cadena = "=="; }
#line 2910 "y.tab.c"
break;
case 153:
#line 1253 "src/gramatica.y"
	{ yyval.cadena = "!="; }
#line 2915 "y.tab.c"
break;
#line 2917 "y.tab.c"
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
