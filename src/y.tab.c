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

extern int yylex(void);
extern int yylineno;
int cant_errores = 0;
void yyerror(const char *s);
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 13 "src/gramatica.y"
typedef union YYSTYPE {
    struct Simbolo *simbolo;
    int val_int;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 46 "y.tab.c"

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
#define IF 266
#define ELSE 267
#define END_IF 268
#define BEGIN 269
#define END 270
#define POUT 271
#define RET 272
#define CLASS 273
#define FUNCTION 274
#define INTEGER 275
#define SINGLEF 276
#define FROM 277
#define TO 278
#define BY 279
#define REPEAT 280
#define COMPTIME 281
#define TOSF 282
#define EXTENDS 283
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    1,    1,    4,    4,    5,    5,    5,
    5,    5,   10,   10,   12,   12,    6,   11,   11,    9,
    7,    7,    7,   13,   13,   13,   14,   14,    8,   15,
   15,   18,   18,   16,   16,   16,   17,   17,   19,   19,
    2,    2,    3,    3,    3,    3,   20,   20,   20,   20,
   20,   25,   25,   21,   21,   27,   27,   27,   24,   24,
   24,   24,   26,   26,   26,   26,   26,   28,   28,   28,
   28,   28,   29,   29,   29,   29,   29,   29,   29,   31,
   31,   31,   33,   33,   30,   30,   34,   34,   35,   35,
   32,   32,   32,   32,   32,   32,   22,   22,   22,   22,
   38,   38,   23,   23,   39,   39,   39,   39,   39,   39,
   39,   40,   37,   37,   36,   41,   41,   41,   41,   41,
   41,
};
static const YYINT yylen[] = {                            2,
    4,    4,    3,    1,    0,    2,    1,    2,    2,    2,
    2,    2,    2,    2,    1,    1,    2,    3,    1,    2,
    8,    6,    8,    3,    2,    1,    2,    1,    6,    1,
    0,    3,    1,    1,    3,    2,    2,    1,    2,    2,
    3,    3,    3,    2,    3,    2,    1,    1,    1,    1,
    1,    4,    3,    3,    3,    1,    3,    4,    4,    4,
    3,    2,    3,    3,    3,    3,    1,    3,    3,    3,
    3,    1,    1,    3,    4,    5,    7,    4,    1,    3,
    3,    0,    3,    1,    1,    0,    3,    1,    1,    3,
    1,    1,    2,    2,    2,    2,    6,    5,    5,    6,
    3,    1,    3,    3,    8,    4,    7,    5,    3,    3,
    4,    1,    1,    1,    3,    1,    1,    1,    1,    1,
    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,   15,   16,    0,    0,    0,    0,    7,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   19,
   13,    0,    0,    0,    0,    0,    0,    6,    8,    9,
   10,   11,   12,    0,    0,    0,    0,    0,    0,   30,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   47,
   48,   49,   50,   51,    0,    0,    0,    3,    0,    0,
    0,    0,    1,   18,   34,    0,    0,   46,    0,    0,
    0,   91,   92,    0,    0,    0,    0,    0,    0,   72,
   79,    0,   62,    0,    0,    0,    0,    0,    0,    0,
   42,    0,   44,    0,    0,    0,  113,  114,  112,    0,
   41,    0,    0,   26,    0,    0,   33,   36,    0,    0,
    0,    0,   38,   57,    0,    0,    0,    0,    0,    0,
   93,   94,   95,   96,  118,  119,  120,  121,    0,    0,
  116,  117,    0,    0,    0,    0,    0,   61,    0,   53,
    0,    0,    0,    0,  109,   45,   43,    0,    0,  104,
  103,   27,    0,    0,   25,    0,    0,   35,    0,   39,
   40,   29,   37,   58,    0,    0,    0,    0,   88,    0,
    0,    0,    0,    0,   65,    0,   66,    0,    0,   70,
   68,   71,   69,    0,   60,   59,   52,  111,    0,  106,
    0,   24,   22,    0,    0,   32,    0,    0,    0,    0,
   75,   78,    0,    0,  102,   99,   98,    0,  108,    0,
    0,    0,    0,    0,   76,   87,    0,  100,   97,    0,
    0,    0,   23,   21,    0,   84,    0,    0,  101,    0,
  107,   81,    0,   80,   77,  105,   83,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  257,  273,  275,  276,  281,  285,  286,  289,  290,  291,
  292,  293,  294,  295,  297,  257,  286,  296,  257,  257,
  291,  296,  297,  256,  269,  287,  257,  290,   59,   59,
   59,   59,   59,  257,  274,  296,  269,  287,   44,  257,
  300,  256,  257,  266,  271,  272,  277,  288,  305,  306,
  307,  308,  309,  310,  312,  324,  288,   59,   40,  256,
  257,  288,   59,  257,  269,  283,  301,   59,   46,   91,
  257,  258,  259,  282,   40,   43,   45,  311,  313,  314,
  317,  321,  256,   40,   40,  257,   40,   61,  321,  256,
  270,  305,   59,  261,   61,  256,  287,  305,  322,  325,
  270,  297,  298,  299,   40,   40,  257,  269,  303,  291,
  292,  302,  304,  257,  311,   40,   46,   91,   40,  321,
  258,  259,  258,  259,  262,  263,  264,  265,   43,   45,
   60,   62,  326,   42,   47,   41,  260,   41,  311,   41,
  311,   61,  321,  317,   41,   59,   59,  311,  311,  280,
  280,  257,   44,   41,  299,  298,  298,  269,   44,   59,
   59,  270,  304,   93,  257,  311,  315,  319,  320,  257,
  311,  311,   41,  322,  256,  313,  256,  313,  311,  256,
  314,  256,  314,  322,   41,   41,   41,  278,  317,   41,
  278,  299,  287,   41,   41,  257,   61,   41,   44,   40,
   93,   41,  322,  267,  268,  323,  323,  278,  317,  317,
  286,  286,  311,   91,  316,  320,  315,  256,  323,  322,
  317,  279,  287,  287,  256,  258,  318,   41,  268,  279,
  317,   93,   44,   93,  316,  317,  258,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          6,
    7,   97,   48,    8,    9,   10,   11,   12,   13,   14,
   18,   15,  103,  104,   41,   67,  112,  109,  113,   98,
   50,   51,   52,   53,   54,   78,   55,   79,   80,  167,
  215,   81,  227,  168,  169,   82,   99,  206,   56,  100,
  133,
};
static const YYINT yysindex[] = {                       -86,
  214, -234,    0,    0, -224,    0, -255,  253,    0,   -4,
    7,   29,   75,   98, -183,  -97, -119,  121,  -87,    0,
    0,  121,  -97,  342,  342,  122,  -97,    0,    0,    0,
    0,    0,    0,  148, -102,  121,  342,  135,  -43,    0,
 -239,  139,  -20,  -36,  -24,  165,  -40,  282,  161,    0,
    0,    0,    0,    0,  -59,  294,  311,    0,  -67,  188,
  197,  311,    0,    0,    0, -101,  -67,    0,   40,  -14,
    3,    0,    0,  246,  -14,  -23,   11,  141,   68,    0,
    0,  267,    0,  -33,  -28,   67,  -14,  124,  272,  255,
    0,  260,    0,  -14,  -14,  265,    0,    0,    0,   50,
    0,   78,    1,    0,  -67,  -67,    0,    0,    6,  277,
  283,  -63,    0,    0,   25,  140,   84,  -14,  -14,  152,
    0,    0,    0,    0,    0,    0,    0,    0,  -18,  129,
    0,    0,  -14,  133,  137,  318,  314,    0,  371,    0,
  410,  -25,  316,   74,    0,    0,    0,   69,   69,    0,
    0,    0,  -67, -255,    0,   23,   45,    0,  101,    0,
    0,    0,    0,    0,   71,   69,  322,  320,    0,  325,
   47,  425,  318,  -76,    0,   68,    0,   68,   69,    0,
    0,    0,    0,  -76,    0,    0,    0,    0,  -11,    0,
  124,    0,    0,  253,  253,    0,  -14,  287,  140,  140,
    0,    0,  -52,  318,    0,    0,    0,  124,    0,   95,
 -255, -255,   69,  -79,    0,    0,  338,    0,    0,  112,
  123,  124,    0,    0,  324,    0,    2,  287,    0,  124,
    0,    0,  149,    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                      -117,
 -117,    0,    0,    0,    0,    0,    0, -110,    0,    0,
    0,    0,    0,    0,    0,   62,    0,  354, -153,    0,
    0,  361,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   62,    0,  374,    0,    0,    0,    0,
    0,    0,  -50,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  434,    0,    0,    0,    0,    0,    0,    0,    0,
   -6,    0,    0,    0,    0,    0,    0,    0,   60,    0,
    0,    0,    0,    0,    0,  385,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   58,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  395,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  335,    0,    0,    0,    0,  193,  196,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  458,   21,    0,  396,    0,   16,
    0,    0,    0,    0,    0,   82,    0,  104,  169,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -117, -117,    0,    0,   38,    0,  395,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   94,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   38,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
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
    0,    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
    5,  189,  136,    0,  431,   17,  -19,    0,    0,    0,
  128,  351,  184,  -84,    0,    0,    0,    0,  330,  461,
    0,    0,    0,    0,    0,  397,    0,  162,  177,  243,
  216,  289,    0,    0,  249,   49,  -96, -156,    0,    0,
    0,
};
#define YYTABLESIZE 650
static const YYINT yytable[] = {                         87,
   24,   95,   76,   75,   77,   17,   76,  138,   77,   76,
   56,   77,  140,   25,   76,   84,   77,   76,  155,   77,
   88,   21,   19,  174,   76,   69,   77,  207,   76,   65,
   77,   76,   20,   77,   73,   73,   73,   73,   73,  184,
   73,  154,  116,   66,  153,  233,  219,  111,  117,  159,
    3,    4,   73,   73,   29,   73,   74,   74,   74,   74,
   74,   89,   74,  194,   89,   30,  153,  129,  192,  130,
   70,  155,  155,   34,   74,   74,  203,   74,   82,   82,
   82,   82,   82,  110,   82,  195,   73,   31,  153,  129,
   35,  130,  111,  118,  234,   89,   82,   82,   28,   82,
   67,   28,   67,   67,   67,   19,  116,  220,   74,  134,
  116,  129,  117,  130,  135,   31,  117,  164,   67,   67,
   19,   67,   63,  120,   63,   63,   63,  142,  110,   31,
   82,  197,   22,   32,   90,  143,   24,   90,    5,  201,
   63,   63,   36,   63,   64,    4,   64,   64,   64,   37,
   36,    5,   67,   60,   61,  107,   33,  118,    4,   20,
   57,  118,   64,   64,   39,   64,   76,  108,   77,   40,
    1,   76,   62,   77,   63,   76,  225,   77,  226,   76,
   58,   77,   76,  129,   77,  130,    2,   59,    3,    4,
  204,  205,  173,   63,    5,   26,   64,   68,  211,  212,
  131,   94,  132,  218,   85,   38,  162,    3,    4,  115,
   56,    3,    4,   64,  204,  205,   86,   72,   73,   93,
   71,   72,   73,   71,   72,   73,  137,  105,   71,   72,
   73,   83,   72,   73,  121,  122,  106,  175,   71,   72,
   73,   74,   71,   72,   73,   74,   72,   73,   74,   73,
   73,   54,  188,   74,   55,   73,   73,   73,   73,   73,
   73,   73,   73,   74,   73,   73,  208,   74,  123,  124,
   73,   74,   74,   73,  158,    3,    4,   74,   74,   74,
   74,   74,   74,   74,   74,  119,   74,   74,  156,  157,
  176,  178,   74,   82,   82,   74,  114,    3,    4,   82,
   82,   82,   82,   82,   82,   82,   82,  136,   82,   82,
  181,  183,  145,  146,   82,   67,   67,   82,  147,    3,
    4,   67,   67,   67,   67,   67,   67,   67,   67,  151,
   67,   67,   28,   28,  152,  160,   67,   63,   63,   67,
  170,  161,  193,   63,   63,   63,   63,   63,   63,   63,
   63,  191,   63,   63,  185,   23,  190,  196,   63,   64,
   64,   63,  198,  199,  200,   64,   64,   64,   64,   64,
   64,   64,   64,  222,   64,   64,  144,  214,  228,  229,
   64,   72,   73,   64,  177,   71,   72,   73,  180,   71,
   72,   73,  182,   71,   72,   73,  165,   72,   73,  223,
  224,  230,  125,  126,  127,  128,  237,   24,   43,  102,
   74,  186,   20,  129,   74,  130,  232,   44,   74,   14,
   25,   74,   45,   46,  115,  115,   73,   73,   47,   73,
  189,   73,   17,    2,  115,   86,   85,  115,   28,  115,
  115,  163,  217,  235,   73,  115,   73,  216,   54,    0,
  187,   55,  129,  102,  130,  102,  102,    0,    0,   54,
   54,    0,   55,   55,    0,  202,  115,  129,    0,  130,
   16,    0,   54,    0,    0,   55,    0,  209,    0,  210,
  139,  141,    0,    0,   49,   49,    2,    0,    3,    4,
  148,  149,    0,    0,    5,    0,  221,   49,   73,   73,
   73,   73,   73,  102,   73,    0,  102,  102,   92,   27,
  231,    0,  166,    0,  171,  172,    0,   92,  236,    0,
   42,   43,   92,    0,    0,    2,    0,    3,    4,  179,
   44,    0,    0,    5,    0,   45,   46,   90,   43,    0,
    0,   47,    0,    0,  150,    0,    0,   44,    0,   96,
   43,   91,   45,   46,    0,    0,   49,    0,   47,   44,
    0,    0,   25,    0,   45,   46,   90,   43,    0,    0,
   47,    0,    0,   24,   43,    0,   44,    0,    0,    0,
  101,   45,   46,   44,    0,    0,   25,   47,   45,   46,
  110,  110,    0,  213,   47,  166,  166,   42,   43,    0,
  110,    0,    0,  110,    0,  110,  110,   44,    0,    0,
    0,  110,   45,   46,    0,    0,    0,    0,   47,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   73,   73,   73,   73,
};
static const YYINT yycheck[] = {                         40,
  256,   61,   43,   40,   45,    1,   43,   41,   45,   43,
   61,   45,   41,  269,   43,   40,   45,   43,  103,   45,
   61,    5,  257,  120,   43,   46,   45,  184,   43,  269,
   45,   43,  257,   45,   41,   42,   43,   44,   45,  136,
   47,   41,   40,  283,   44,   44,  203,   67,   46,   44,
  275,  276,   59,   60,   59,   62,   41,   42,   43,   44,
   45,   41,   47,   41,   44,   59,   44,   43,  153,   45,
   91,  156,  157,  257,   59,   60,  173,   62,   41,   42,
   43,   44,   45,   67,   47,   41,   93,   59,   44,   43,
  274,   45,  112,   91,   93,   47,   59,   60,   41,   62,
   41,   44,   43,   44,   45,   44,   40,  204,   93,   42,
   40,   43,   46,   45,   47,  269,   46,   93,   59,   60,
   59,   62,   41,   75,   43,   44,   45,   61,  112,  283,
   93,   61,    5,   59,   41,   87,  256,   44,  256,   93,
   59,   60,   15,   62,   41,  256,   43,   44,   45,  269,
   23,  269,   93,  256,  257,  257,   59,   91,  269,  257,
   25,   91,   59,   60,   44,   62,   43,  269,   45,  257,
  257,   43,   37,   45,   93,   43,  256,   45,  258,   43,
   59,   45,   43,   43,   45,   45,  273,   40,  275,  276,
  267,  268,   41,   59,  281,    7,   93,   59,  194,  195,
   60,  261,   62,  256,   40,   17,  270,  275,  276,   41,
  261,  275,  276,  257,  267,  268,  257,  258,  259,   59,
  257,  258,  259,  257,  258,  259,  260,   40,  257,  258,
  259,  256,  258,  259,  258,  259,   40,  256,  257,  258,
  259,  282,  257,  258,  259,  282,  258,  259,  282,  256,
  257,   59,  278,  282,   59,  262,  263,  264,  265,  266,
  267,  268,  269,  282,  271,  272,  278,  282,  258,  259,
  277,  256,  257,  280,  269,  275,  276,  262,  263,  264,
  265,  266,  267,  268,  269,   40,  271,  272,  105,  106,
  129,  130,  277,  256,  257,  280,  257,  275,  276,  262,
  263,  264,  265,  266,  267,  268,  269,   41,  271,  272,
  134,  135,   41,   59,  277,  256,  257,  280,   59,  275,
  276,  262,  263,  264,  265,  266,  267,  268,  269,  280,
  271,  272,  275,  276,  257,   59,  277,  256,  257,  280,
  257,   59,  154,  262,  263,  264,  265,  266,  267,  268,
  269,  278,  271,  272,   41,    5,   41,  257,  277,  256,
  257,  280,   41,   44,   40,  262,  263,  264,  265,  266,
  267,  268,  269,  279,  271,  272,   88,   91,   41,  268,
  277,  258,  259,  280,  256,  257,  258,  259,  256,  257,
  258,  259,  256,  257,  258,  259,  257,  258,  259,  211,
  212,  279,  262,  263,  264,  265,  258,  256,  257,   59,
  282,   41,   59,   43,  282,   45,   93,  266,  282,   59,
  269,  282,  271,  272,  256,  257,   42,   43,  277,   45,
  142,   47,   59,    0,  266,   41,   41,  269,    8,  271,
  272,  112,  200,  228,   60,  277,   62,  199,  256,   -1,
   41,  256,   43,  103,   45,  105,  106,   -1,   -1,  267,
  268,   -1,  267,  268,   -1,   41,   70,   43,   -1,   45,
  257,   -1,  280,   -1,   -1,  280,   -1,  189,   -1,  191,
   84,   85,   -1,   -1,   24,   25,  273,   -1,  275,  276,
   94,   95,   -1,   -1,  281,   -1,  208,   37,   41,   42,
   43,   44,   45,  153,   47,   -1,  156,  157,   48,  257,
  222,   -1,  116,   -1,  118,  119,   -1,   57,  230,   -1,
  256,  257,   62,   -1,   -1,  273,   -1,  275,  276,  133,
  266,   -1,   -1,  281,   -1,  271,  272,  256,  257,   -1,
   -1,  277,   -1,   -1,  280,   -1,   -1,  266,   -1,  256,
  257,  270,  271,  272,   -1,   -1,   96,   -1,  277,  266,
   -1,   -1,  269,   -1,  271,  272,  256,  257,   -1,   -1,
  277,   -1,   -1,  256,  257,   -1,  266,   -1,   -1,   -1,
  270,  271,  272,  266,   -1,   -1,  269,  277,  271,  272,
  256,  257,   -1,  197,  277,  199,  200,  256,  257,   -1,
  266,   -1,   -1,  269,   -1,  271,  272,  266,   -1,   -1,
   -1,  277,  271,  272,   -1,   -1,   -1,   -1,  277,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,  265,
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
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 283
#define YYUNDFTOKEN 327
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
"ASSIGN","GE","LE","EQ","NE","IF","ELSE","END_IF","BEGIN","END","POUT","RET",
"CLASS","FUNCTION","INTEGER","SINGLEF","FROM","TO","BY","REPEAT","COMPTIME",
"TOSF","EXTENDS","$accept","programa","bloque_declarativo","bloque_ejecutable",
"lista_ejecutables","lista_declaraciones","declaracion","declaracion_variable",
"declaracion_funcion","declaracion_clase","declaracion_objeto",
"declaracion_comptime","lista_variables","tipo_dato","lista_parametros",
"parametro","codigo_clase","encabezado_clase","miembros_clase","lista_clase",
"miembro","sentencia","asignacion","if_sentencia","iteracion","impresion",
"sentencia_retorno","expresion_aritmetica","destino","termino","operando",
"parametros_reales","orden_evaluacion","constante_con_signo","lista_enteros",
"lista_parametros_reales","parametro_real","condicion","bloque_o_sentencia",
"fin_if","encabezado_iteracion","cuerpo_iteracion","operador_relacional",
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : programa",
"programa : ID bloque_declarativo bloque_ejecutable ';'",
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
"declaracion_comptime : COMPTIME declaracion_variable",
"declaracion_comptime : COMPTIME lista_variables",
"tipo_dato : INTEGER",
"tipo_dato : SINGLEF",
"declaracion_variable : tipo_dato lista_variables",
"lista_variables : lista_variables ',' ID",
"lista_variables : ID",
"declaracion_objeto : ID lista_variables",
"declaracion_funcion : tipo_dato FUNCTION ID '(' lista_parametros ')' bloque_declarativo bloque_ejecutable",
"declaracion_funcion : tipo_dato ID '(' lista_parametros ')' bloque_ejecutable",
"declaracion_funcion : tipo_dato FUNCTION error '(' lista_parametros ')' bloque_declarativo bloque_ejecutable",
"lista_parametros : lista_parametros ',' parametro",
"lista_parametros : lista_parametros parametro",
"lista_parametros : parametro",
"parametro : tipo_dato ID",
"parametro : tipo_dato",
"declaracion_clase : CLASS ID codigo_clase encabezado_clase miembros_clase END",
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
"asignacion : destino ASSIGN expresion_aritmetica",
"asignacion : destino '=' expresion_aritmetica",
"destino : ID",
"destino : ID '.' ID",
"destino : ID '[' expresion_aritmetica ']'",
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
"operando : ID",
"operando : ID '.' ID",
"operando : ID '[' expresion_aritmetica ']'",
"operando : ID '(' parametros_reales ')' orden_evaluacion",
"operando : ID '.' ID '(' parametros_reales ')' orden_evaluacion",
"operando : TOSF '(' expresion_aritmetica ')'",
"operando : constante_con_signo",
"orden_evaluacion : '[' lista_enteros ']'",
"orden_evaluacion : '[' error ']'",
"orden_evaluacion :",
"lista_enteros : lista_enteros ',' CTE",
"lista_enteros : CTE",
"parametros_reales : lista_parametros_reales",
"parametros_reales :",
"lista_parametros_reales : lista_parametros_reales ',' parametro_real",
"lista_parametros_reales : parametro_real",
"parametro_real : expresion_aritmetica",
"parametro_real : ID '=' expresion_aritmetica",
"constante_con_signo : CTE",
"constante_con_signo : CTE_FLOAT",
"constante_con_signo : '+' CTE",
"constante_con_signo : '+' CTE_FLOAT",
"constante_con_signo : '-' CTE",
"constante_con_signo : '-' CTE_FLOAT",
"if_sentencia : IF '(' condicion ')' bloque_o_sentencia fin_if",
"if_sentencia : IF condicion ')' bloque_o_sentencia fin_if",
"if_sentencia : IF '(' condicion bloque_o_sentencia fin_if",
"if_sentencia : IF '(' condicion ')' bloque_o_sentencia error",
"fin_if : ELSE bloque_o_sentencia END_IF",
"fin_if : END_IF",
"iteracion : encabezado_iteracion cuerpo_iteracion REPEAT",
"iteracion : encabezado_iteracion error REPEAT",
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
#line 379 "src/gramatica.y"

void yyerror(const char *s) {
    const char *COLOR_ROJO = "\033[1;31m";
    const char *COLOR_AMARILLO = "\033[1;33m";
    const char *COLOR_RESET = "\033[0m";

    if (strncmp(s, "syntax error", 12) == 0) {
        return; 
    }

    if (strstr(s, "Sentencia mal formada") != NULL) {
        cant_errores++; 
        fprintf(stderr, "%s[ERROR DE SINTAXIS]%s %sLínea %d:%s Sentencia inválida. Es posible que falte un delimitador estructural (como 'END_IF' o ';') o un operador.\n", 
                COLOR_ROJO, COLOR_RESET, COLOR_AMARILLO, yylineno, COLOR_RESET);
        return;
    }

    cant_errores++;
    const char *mensaje = (strncmp(s, "Error: ", 7) == 0) ? s + 7 : s;
    
    fprintf(stderr, "%s[ERROR DE SINTAXIS]%s %sLínea %d:%s %s\n", 
            COLOR_ROJO, COLOR_RESET, COLOR_AMARILLO, yylineno, COLOR_RESET, mensaje);
}
#line 816 "y.tab.c"

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
#line 29 "src/gramatica.y"
	{
        if (cant_errores == 0) {
            printf("[SINT] Estructura Programa, en línea %d\n", yylineno);
            printf("Sintaxis correcta: Programa reconocido con éxito.\n"); 
        } else {
            printf("Sintaxis incorrecta: finalizado con %d error(es).\n", cant_errores);
        }
    }
#line 1496 "y.tab.c"
break;
case 2:
#line 38 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador END al final del bloque ejecutable."); yyerrok; }
#line 1501 "y.tab.c"
break;
case 3:
#line 40 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
#line 1506 "y.tab.c"
break;
case 14:
#line 64 "src/gramatica.y"
	{ yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
#line 1511 "y.tab.c"
break;
case 17:
#line 74 "src/gramatica.y"
	{ printf("[SINT] Estructura Variable, en línea %d\n", yylineno); }
#line 1516 "y.tab.c"
break;
case 20:
#line 84 "src/gramatica.y"
	{ printf("[SINT] Estructura Objeto, en línea %d\n", yylineno); }
#line 1521 "y.tab.c"
break;
case 21:
#line 89 "src/gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1526 "y.tab.c"
break;
case 22:
#line 91 "src/gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1531 "y.tab.c"
break;
case 23:
#line 93 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
#line 1536 "y.tab.c"
break;
case 25:
#line 99 "src/gramatica.y"
	{ yyerror("Error: Falta de ',' en declaración de parámetros."); yyerrok; }
#line 1541 "y.tab.c"
break;
case 28:
#line 106 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
#line 1546 "y.tab.c"
break;
case 29:
#line 111 "src/gramatica.y"
	{ printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); }
#line 1551 "y.tab.c"
break;
case 31:
#line 116 "src/gramatica.y"
	{ yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
#line 1556 "y.tab.c"
break;
case 36:
#line 128 "src/gramatica.y"
	{ yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
#line 1561 "y.tab.c"
break;
case 42:
#line 144 "src/gramatica.y"
	{ yyerror("Error: Falta de delimitador de sentencias ejecutables BEGIN."); yyerrok; }
#line 1566 "y.tab.c"
break;
case 45:
#line 151 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 1571 "y.tab.c"
break;
case 46:
#line 153 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 1576 "y.tab.c"
break;
case 52:
#line 166 "src/gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1581 "y.tab.c"
break;
case 53:
#line 168 "src/gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1586 "y.tab.c"
break;
case 54:
#line 173 "src/gramatica.y"
	{ printf("[SINT] Estructura ASSIGN, en línea %d\n", yylineno); }
#line 1591 "y.tab.c"
break;
case 55:
#line 175 "src/gramatica.y"
	{ yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
#line 1596 "y.tab.c"
break;
case 59:
#line 186 "src/gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1601 "y.tab.c"
break;
case 60:
#line 188 "src/gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1606 "y.tab.c"
break;
case 61:
#line 190 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1611 "y.tab.c"
break;
case 62:
#line 192 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1616 "y.tab.c"
break;
case 65:
#line 199 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '+'."); yyerrok; }
#line 1621 "y.tab.c"
break;
case 66:
#line 201 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '-'."); yyerrok; }
#line 1626 "y.tab.c"
break;
case 70:
#line 209 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '*'."); yyerrok; }
#line 1631 "y.tab.c"
break;
case 71:
#line 211 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '/'."); yyerrok; }
#line 1636 "y.tab.c"
break;
case 81:
#line 228 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 1641 "y.tab.c"
break;
case 91:
#line 254 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            long valor = strtol(yystack.l_mark[0].simbolo->lexema, NULL, 10);
            if (valor > 32767) {
                printf("\nLínea %d: Error: La constante entera positiva '%s' excede el rango máximo permitido [32767]\n\n", yylineno, yystack.l_mark[0].simbolo->lexema);
            }
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "+%s", yystack.l_mark[0].simbolo->lexema);
            modificar_lexema(yystack.l_mark[0].simbolo, nuevo);
            printf("[SINT] Constante entera positiva, lexema actualizado a: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1657 "y.tab.c"
break;
case 92:
#line 267 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "+%s", yystack.l_mark[0].simbolo->lexema);
            modificar_lexema(yystack.l_mark[0].simbolo, nuevo);
            printf("[SINT] Constante float positiva, lexema actualizado a: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1669 "y.tab.c"
break;
case 93:
#line 276 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            long valor = strtol(yystack.l_mark[0].simbolo->lexema, NULL, 10);
            if (valor > 32767) {
                printf("\nLínea %d: Error: La constante entera positiva '+%s' excede el rango máximo permitido [32767]\n\n", yylineno, yystack.l_mark[0].simbolo->lexema);
            }
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "+%s", yystack.l_mark[0].simbolo->lexema);
            modificar_lexema(yystack.l_mark[0].simbolo, nuevo);
            printf("[SINT] Constante entera positiva (+), lexema actualizado a: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1685 "y.tab.c"
break;
case 94:
#line 289 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "+%s", yystack.l_mark[0].simbolo->lexema);
            modificar_lexema(yystack.l_mark[0].simbolo, nuevo);
            printf("[SINT] Constante float positiva (+), lexema actualizado a: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1697 "y.tab.c"
break;
case 95:
#line 298 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "-%s", yystack.l_mark[0].simbolo->lexema);
            modificar_lexema(yystack.l_mark[0].simbolo, nuevo);
            printf("[SINT] Constante entera negativa, lexema actualizado a: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1709 "y.tab.c"
break;
case 96:
#line 307 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "-%s", yystack.l_mark[0].simbolo->lexema);
            modificar_lexema(yystack.l_mark[0].simbolo, nuevo);
            printf("[SINT] Constante float negativa, lexema actualizado a: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1721 "y.tab.c"
break;
case 97:
#line 319 "src/gramatica.y"
	{ printf("[SINT] Estructura IF, en línea %d\n", yylineno); }
#line 1726 "y.tab.c"
break;
case 98:
#line 321 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
#line 1731 "y.tab.c"
break;
case 99:
#line 323 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
#line 1736 "y.tab.c"
break;
case 100:
#line 325 "src/gramatica.y"
	{ yyerror("Error: Estructura IF mal cerrada (posiblemente falta END_IF o el delimitador ';')."); yyerrok; }
#line 1741 "y.tab.c"
break;
case 101:
#line 330 "src/gramatica.y"
	{ printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); }
#line 1746 "y.tab.c"
break;
case 103:
#line 336 "src/gramatica.y"
	{ printf("[SINT] Estructura ITERACION, en línea %d\n", yylineno); }
#line 1751 "y.tab.c"
break;
case 104:
#line 338 "src/gramatica.y"
	{ yyerror("Error: Falta o hay un error en el cuerpo de la iteración."); yyerrok; }
#line 1756 "y.tab.c"
break;
case 107:
#line 345 "src/gramatica.y"
	{ yyerror("Error: Falta identificador (ID) en el encabezado."); yyerrok; }
#line 1761 "y.tab.c"
break;
case 108:
#line 347 "src/gramatica.y"
	{ yyerror("Error: Falta 'TO' en el encabezado de la iteración."); yyerrok; }
#line 1766 "y.tab.c"
break;
case 109:
#line 349 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
#line 1771 "y.tab.c"
break;
case 110:
#line 351 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
#line 1776 "y.tab.c"
break;
case 111:
#line 353 "src/gramatica.y"
	{ yyerror("Error: Falta CTE en el encabezado."); yyerrok; }
#line 1781 "y.tab.c"
break;
#line 1783 "y.tab.c"
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
