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
#line 14 "src/gramatica.y"
typedef union YYSTYPE {
    struct Simbolo *simbolo;
    int val_int;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 47 "y.tab.c"

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
    0,    0,    0,    0,    1,    1,    4,    4,    5,    5,
    5,    5,    5,   10,   10,   12,   12,    6,   11,   11,
    9,    7,    7,    7,    7,   13,   13,   13,   14,   14,
    8,   15,   15,   18,   18,   16,   16,   16,   17,   17,
   19,   19,    2,    2,    3,    3,    3,    3,   20,   20,
   20,   20,   20,   25,   25,   21,   21,   27,   27,   27,
   24,   24,   24,   24,   26,   26,   26,   26,   26,   28,
   28,   28,   28,   28,   30,   30,   30,   31,   31,   31,
   29,   29,   32,   32,   32,   32,   32,   32,   32,   32,
   32,   34,   34,   36,   36,   36,   36,   33,   38,   38,
   39,   39,   37,   37,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   22,   22,   22,   22,   42,   42,   41,
   41,   23,   43,   43,   43,   43,   43,   43,   43,   44,
   45,   45,   40,   46,   46,   46,   46,   46,   46,
};
static const YYINT yylen[] = {                            2,
    4,    3,    4,    3,    1,    0,    2,    1,    2,    2,
    2,    2,    2,    2,    2,    1,    1,    2,    3,    1,
    2,    8,    6,    8,    7,    3,    2,    1,    2,    1,
    6,    1,    0,    3,    1,    1,    3,    2,    2,    1,
    2,    2,    3,    3,    3,    2,    3,    2,    1,    1,
    1,    1,    1,    4,    3,    3,    3,    1,    3,    4,
    4,    4,    3,    2,    3,    3,    3,    3,    1,    3,
    3,    3,    3,    1,    3,    3,    1,    3,    3,    1,
    1,    5,    1,    3,    4,    5,    7,    4,    6,    4,
    1,    3,    3,    3,    3,    1,    1,    1,    3,    1,
    1,    3,    1,    1,    1,    1,    2,    2,    2,    2,
    1,    2,    2,    6,    5,    5,    6,    3,    1,    1,
    2,    3,    8,    4,    7,    5,    3,    3,    4,    1,
    1,    1,    3,    1,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,   16,   17,    0,    0,    0,    0,    8,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   20,
   14,    0,    0,    0,    0,    0,    0,    7,    9,   10,
   11,   12,   13,    0,    0,    0,    0,    0,    0,   32,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   49,
   50,   51,   52,   53,    0,    0,    0,    4,    0,    0,
    0,    0,    1,   19,   36,    0,    0,   48,    0,    0,
    0,  105,  106,  103,  104,    0,    0,    0,    0,    0,
    0,   74,   81,   91,  111,    0,   64,    0,    0,    0,
    0,    0,    0,    0,   44,    0,   46,    0,    0,    0,
   43,    0,    0,   28,    0,    0,   35,   38,    0,    0,
    0,    0,   40,   59,    0,    0,    0,    0,    0,    0,
    0,  107,  108,  112,  109,  110,  113,  136,  137,  138,
  139,    0,    0,  134,  135,    0,    0,    0,    0,    0,
   63,    0,   55,    0,    0,    0,    0,  127,   47,   45,
    0,    0,  131,  132,  122,  130,   29,    0,    0,   27,
    0,    0,    0,   37,    0,   41,   42,   31,   39,   60,
    0,    0,    0,    0,  100,    0,    0,    0,    0,    0,
  120,    0,    0,   67,    0,   68,    0,    0,   72,   70,
   73,   71,    0,   62,   61,   54,  129,    0,  124,    0,
   26,   23,    0,    0,    0,   34,    0,    0,    0,    0,
    0,    0,   80,    0,   85,   90,    0,  121,    0,  119,
  116,  115,    0,  126,    0,    0,   25,    0,    0,    0,
   86,   99,   82,    0,    0,    0,    0,    0,  117,  114,
    0,    0,    0,   24,   22,    0,   96,    0,   97,    0,
    0,   78,   79,    0,  118,    0,  125,   93,    0,   92,
   87,  123,   94,   95,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  257,  275,  277,  278,  283,  287,  288,  291,  292,  293,
  294,  295,  296,  297,  299,  257,  288,  298,  257,  257,
  293,  298,  299,  256,  271,  289,  257,  292,   59,   59,
   59,   59,   59,  257,  276,  298,  271,  289,   44,  257,
  302,  256,  257,  268,  273,  274,  279,  290,  307,  308,
  309,  310,  311,  312,  314,  330,  290,   59,   40,  256,
  257,  290,   59,  257,  271,  285,  303,   59,   46,   91,
  257,  258,  259,  266,  267,  284,   40,   43,   45,  313,
  315,  316,  319,  322,  324,  327,  256,   40,   40,  257,
   40,   61,  327,  256,  272,  307,   59,  261,   61,  282,
  272,  299,  300,  301,   40,   40,  257,  271,  305,  293,
  294,  304,  306,  257,  313,   40,   61,   46,   91,   40,
  327,  258,  259,  324,  258,  259,  324,  262,  263,  264,
  265,   43,   45,   60,   62,  333,   42,   47,   41,  260,
   41,  313,   41,  313,   61,  327,  322,   41,   59,   59,
  313,  313,  289,  307,  331,  332,  257,   44,   41,  301,
  300,   41,  300,  271,   44,   59,   59,  272,  306,   93,
  257,  313,  320,  325,  326,   40,  257,  313,  313,   41,
  289,  307,  328,  256,  315,  256,  315,  313,  256,  316,
  256,  316,  328,   41,   41,   41,  280,  322,   41,  280,
  301,  289,   41,  288,   41,  257,   61,   41,   44,  257,
  317,  318,  319,   40,   93,   41,  328,   59,  269,  270,
  329,  329,  280,  322,  322,  288,  289,  288,  313,   91,
  321,  326,   41,   43,   45,   42,   47,  320,  256,  329,
  328,  322,  281,  289,  289,  256,  258,  323,  324,  318,
  318,  319,  319,   41,  270,  281,  322,   93,   44,   93,
  321,  322,  258,  324,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          6,
    7,  181,   48,    8,    9,   10,   11,   12,   13,   14,
   18,   15,  103,  104,   41,   67,  112,  109,  113,  182,
   50,   51,   52,   53,   54,   80,   55,   81,   82,  211,
  212,   83,  173,  231,   84,  248,   85,  174,  175,   86,
  183,  221,   56,  155,  156,  136,
};
static const YYINT yysindex[] = {                      -219,
  -82, -229,    0,    0, -104,    0, -178,  195,    0,  -23,
   -5,    2,   11,   36, -224, -152, -149,   94, -143,    0,
    0,   94, -152,  357,  357,   88, -152,    0,    0,    0,
    0,    0,    0,  111,  144,   94,  357,  118,  -70,    0,
 -173,  135,  -22,  -36,  -32,  164,  -40,  306,  166,    0,
    0,    0,    0,    0,  -59,  -66,  336,    0,  130,  215,
  227,  336,    0,    0,    0,  -74,  130,    0,   15,  114,
   71,    0,    0,    0,    0,  236,  114,  210,  216,  389,
  102,    0,    0,    0,    0,  194,    0,   -6,   -1,  138,
  114,  299,  243,  231,    0,  241,    0,  114,  114,  355,
    0,   49,  -28,    0,  130,    4,    0,    0,  -43,  255,
  266,  221,    0,    0,  -26,  262,  291,   86,  114,  114,
  167,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -20,  200,    0,    0,  114,  230,  246,  355,  308,
    0,  465,    0,  466,   70,  314,   99,    0,    0,    0,
  160,  160,    0,    0,    0,    0,    0,  130, -178,    0,
   19,  195,   40,    0,  133,    0,    0,    0,    0,    0,
  328,  160,  346,  351,    0,  265,  376,   -2,  496,  355,
    0,  338,  211,    0,  102,    0,  102,  160,    0,    0,
    0,    0,  211,    0,    0,    0,    0,  268,    0,  299,
    0,    0,  195, -178,  195,    0,  -25,  331,  262,  -34,
  499,  173,    0,  262,    0,    0,  136,    0,  355,    0,
    0,    0,  299,    0,  146, -178,    0, -178,  160,  197,
    0,    0,    0,  265,  265,  265,  265,  392,    0,    0,
  174,  169,  299,    0,    0,  361,    0,  -13,    0,  173,
  173,    0,    0,  331,    0,  299,    0,    0,   68,    0,
    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                      -140,
 -140,    0,    0,    0,    0,    0,    0, -121,    0,    0,
    0,    0,    0,    0,    0,  126,    0,  402,  -85,    0,
    0,  406,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  126,    0,  426,    0,  448,    0,    0,
    0,    0,  -50,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  516,    0,    0,    0,    0,    0,    0,    0,    0,
    6,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   96,    0,    0,    0,    0,    0,    0,    0,    0,  400,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   42,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  251,    0,    0,    0,    0,
  477,  488,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -140,    0,    0,    0,    0,    0,    0,    0,    0,
  553,  258,    0,  484,    0,    0,   30,    0,    0,    0,
    0,    0,    0,    0,  120,    0,  147,  157,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -140,    0, -140,    0,    0,   59,    0,  509,
    0,  546,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  322,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  575,
  592,    0,    0,   83,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,
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
    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
    9,  379,  123,    0,  547,   21,  -33,    0,    0,    0,
  131,  412,  386,  -76,    0,    0,    0,    0,  449,   72,
    0,    0,    0,    0,    0,  483,    0,  362,  363,    0,
  325,  -68,  350,  313,  345,    0,  -49,    0,  360,  -15,
 -125, -171,    0,    0,    0,    0,
};
#define YYTABLESIZE 697
static const YYINT yytable[] = {                         91,
  165,   99,   78,   77,   79,  116,   78,   88,   79,   17,
   58,  118,  159,  193,  176,  158,  132,   78,  133,   79,
   92,  222,   78,   69,   79,   21,  160,   19,  124,  127,
  259,   93,   34,  111,  141,   29,   78,    1,   79,  143,
  132,   78,  133,   79,  162,  240,   83,   83,   83,   83,
   83,   35,   83,   30,  217,    2,  119,    3,    4,  203,
   31,  121,  158,    5,   83,   83,  170,   83,   70,   32,
   84,   84,   84,   84,   84,  146,   84,   24,  111,  260,
  205,  201,   30,  158,  160,   30,  160,  110,   84,   84,
  215,   84,   25,  241,   33,   49,   49,   65,   83,   88,
   88,   88,   88,   88,   20,   88,   24,  213,   49,  176,
  116,   66,   78,   40,   79,    6,  118,   88,   88,   96,
   88,   37,   84,   89,   89,   89,   89,   89,   96,   89,
    6,  117,  110,   96,    5,   22,   69,   39,   69,   69,
   69,   89,   89,  137,   89,   36,   58,   57,  138,    5,
   59,   88,   20,   36,   69,   69,   78,   69,   79,   62,
   65,  119,   65,   65,   65,  213,  213,  252,  253,   20,
  204,  154,    3,    4,   16,   89,   63,  116,   65,   65,
  249,   65,  107,  118,   20,   33,   64,   66,   69,   66,
   66,   66,    2,   68,    3,    4,  108,  133,  145,   33,
    5,   98,  132,   89,  133,   66,   66,  180,   66,  264,
   58,  226,   65,  228,  236,  100,   90,   72,   73,  237,
   71,   72,   73,   87,   97,   74,   75,  164,  119,   74,
   75,   71,   72,   73,  139,  184,   71,   72,   73,   66,
   74,   75,   78,   76,   79,   74,   75,   76,    3,    4,
   71,   72,   73,  140,  105,   71,   72,   73,   76,   74,
   75,   83,   83,   76,   74,   75,  106,   83,   83,   83,
   83,  114,   78,   83,   79,  120,   83,   76,   83,   83,
    3,    4,   76,  148,   83,   84,   84,   83,   78,  149,
   79,   84,   84,   84,   84,    3,    4,   84,  101,  150,
   84,  101,   84,   84,   78,  157,   79,   78,   84,   79,
   78,   84,   79,  166,   88,   88,    3,    4,   30,   30,
   88,   88,   88,   88,  167,  263,   88,   72,   73,   88,
  176,   88,   88,   74,   75,   74,   75,   88,   89,   89,
   88,   78,  177,   79,   89,   89,   89,   89,  194,  197,
   89,   69,   69,   89,  199,   89,   89,   69,   69,   69,
   69,   89,  102,   69,   89,  102,   69,  116,   69,   69,
   71,   72,   73,  118,   69,   65,   65,   69,  200,   74,
   75,   65,   65,   65,   65,   26,  208,   65,  207,  206,
   65,  239,   65,   65,  209,   38,  218,   76,   65,   60,
   61,   65,   66,   66,  219,  220,    3,    4,   66,   66,
   66,   66,  133,  133,   66,  214,   23,   66,  119,   66,
   66,  230,   24,   43,  133,   66,  243,  133,   66,  133,
  133,  132,  254,  133,   44,  133,  147,   25,  133,   45,
   46,   83,   83,  255,   83,   47,   83,    2,  134,  256,
  135,   27,  246,  258,  247,  186,   71,   72,   73,   83,
   21,   83,   74,   75,   15,   74,   75,  122,  123,    2,
  102,    3,    4,  125,  126,   74,   75,    5,  153,  219,
  220,   74,   75,   76,   18,  189,   71,   72,   73,  198,
  161,  163,  168,  185,  187,   74,   75,    3,    4,  190,
  192,  191,   71,   72,   73,  195,  196,  132,  132,  133,
  133,   74,   75,   76,  102,    3,  102,  102,  171,   72,
   73,  210,   72,   73,   98,   72,   73,   74,   75,   76,
   74,   75,  128,   74,   75,   56,  216,  202,  132,  233,
  133,  234,  224,  235,  225,   76,   57,  223,   76,   83,
   83,   83,  115,   83,   28,   83,   72,   73,  250,  251,
  169,   94,   43,  238,   74,   75,  261,  242,  232,  102,
  142,  144,  102,   44,  102,    0,    0,   95,   45,   46,
  151,  152,  227,    0,   47,    0,   77,  257,   77,    0,
   77,   94,   43,   83,   83,   83,   83,   83,  172,   83,
  262,  178,  179,   44,  244,    0,  245,  101,   45,   46,
   24,   43,   42,   43,   47,   75,    0,   75,  188,   75,
    0,    0,   44,    0,   44,   25,    0,   45,   46,   45,
   46,    0,   76,   47,   76,   47,   76,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  128,  129,  130,  131,    0,    0,    0,    0,    0,    0,
    0,   83,   83,   83,   83,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  229,
    0,  172,    0,    0,    0,    0,  172,
};
static const YYINT yycheck[] = {                         40,
   44,   61,   43,   40,   45,   40,   43,   40,   45,    1,
   61,   46,   41,  139,   40,   44,   43,   43,   45,   45,
   61,  193,   43,   46,   45,    5,  103,  257,   78,   79,
   44,   47,  257,   67,   41,   59,   43,  257,   45,   41,
   43,   43,   45,   45,   41,  217,   41,   42,   43,   44,
   45,  276,   47,   59,  180,  275,   91,  277,  278,   41,
   59,   77,   44,  283,   59,   60,   93,   62,   91,   59,
   41,   42,   43,   44,   45,   91,   47,  256,  112,   93,
   41,  158,   41,   44,  161,   44,  163,   67,   59,   60,
   93,   62,  271,  219,   59,   24,   25,  271,   93,   41,
   42,   43,   44,   45,  257,   47,  256,  176,   37,   40,
   40,  285,   43,  257,   45,  256,   46,   59,   60,   48,
   62,  271,   93,   41,   42,   43,   44,   45,   57,   47,
  271,   61,  112,   62,  256,    5,   41,   44,   43,   44,
   45,   59,   60,   42,   62,   15,   59,   25,   47,  271,
   40,   93,  257,   23,   59,   60,   43,   62,   45,   37,
   41,   91,   43,   44,   45,  234,  235,  236,  237,   44,
  162,  100,  277,  278,  257,   93,   59,   40,   59,   60,
  230,   62,  257,   46,   59,  271,  257,   41,   93,   43,
   44,   45,  275,   59,  277,  278,  271,   41,   61,  285,
  283,  261,   43,   40,   45,   59,   60,   41,   62,  259,
  261,  203,   93,  205,   42,  282,  257,  258,  259,   47,
  257,  258,  259,  256,   59,  266,  267,  271,   91,  266,
  267,  257,  258,  259,   41,  256,  257,  258,  259,   93,
  266,  267,   43,  284,   45,  266,  267,  284,  277,  278,
  257,  258,  259,  260,   40,  257,  258,  259,  284,  266,
  267,  256,  257,  284,  266,  267,   40,  262,  263,  264,
  265,  257,   43,  268,   45,   40,  271,  284,  273,  274,
  277,  278,  284,   41,  279,  256,  257,  282,   43,   59,
   45,  262,  263,  264,  265,  277,  278,  268,   41,   59,
  271,   44,  273,  274,   43,  257,   45,   43,  279,   45,
   43,  282,   45,   59,  256,  257,  277,  278,  277,  278,
  262,  263,  264,  265,   59,  258,  268,  258,  259,  271,
   40,  273,  274,  266,  267,  266,  267,  279,  256,  257,
  282,   43,  257,   45,  262,  263,  264,  265,   41,  280,
  268,  256,  257,  271,   41,  273,  274,  262,  263,  264,
  265,  279,   41,  268,  282,   44,  271,   40,  273,  274,
  257,  258,  259,   46,  279,  256,  257,  282,  280,  266,
  267,  262,  263,  264,  265,    7,   41,  268,   61,  257,
  271,  256,  273,  274,   44,   17,   59,  284,  279,  256,
  257,  282,  256,  257,  269,  270,  277,  278,  262,  263,
  264,  265,  256,  257,  268,   40,    5,  271,   91,  273,
  274,   91,  256,  257,  268,  279,  281,  271,  282,  273,
  274,   43,   41,   45,  268,  279,   92,  271,  282,  273,
  274,   42,   43,  270,   45,  279,   47,    0,   60,  281,
   62,  257,  256,   93,  258,  256,  257,  258,  259,   60,
   59,   62,  266,  267,   59,  266,  267,  258,  259,  275,
   59,  277,  278,  258,  259,  266,  267,  283,  100,  269,
  270,  266,  267,  284,   59,  256,  257,  258,  259,  145,
  105,  106,  272,  132,  133,  266,  267,  277,  278,  137,
  138,  256,  257,  258,  259,   41,   41,   43,   43,   45,
   45,  266,  267,  284,  103,    0,  105,  106,  257,  258,
  259,  257,  258,  259,   41,  258,  259,  266,  267,  284,
  266,  267,  282,  266,  267,   59,   41,  159,   43,   41,
   45,   43,  198,   45,  200,  284,   59,  280,  284,   41,
   42,   43,   70,   45,    8,   47,  258,  259,  234,  235,
  112,  256,  257,  214,  266,  267,  254,  223,  209,  158,
   88,   89,  161,  268,  163,   -1,   -1,  272,  273,  274,
   98,   99,  204,   -1,  279,   -1,   41,  243,   43,   -1,
   45,  256,  257,   41,   42,   43,   44,   45,  116,   47,
  256,  119,  120,  268,  226,   -1,  228,  272,  273,  274,
  256,  257,  256,  257,  279,   41,   -1,   43,  136,   45,
   -1,   -1,  268,   -1,  268,  271,   -1,  273,  274,  273,
  274,   -1,   41,  279,   43,  279,   45,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  262,  263,  264,  265,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  262,  263,  264,  265,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  207,
   -1,  209,   -1,   -1,   -1,   -1,  214,
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
   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 285
#define YYUNDFTOKEN 334
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
"BY","REPEAT","COMPTIME","TOSF","EXTENDS","$accept","programa",
"bloque_declarativo","bloque_ejecutable","lista_ejecutables",
"lista_declaraciones","declaracion","declaracion_variable",
"declaracion_funcion","declaracion_clase","declaracion_objeto",
"declaracion_comptime","lista_variables","tipo_dato","lista_parametros",
"parametro","codigo_clase","encabezado_clase","miembros_clase","lista_clase",
"miembro","sentencia","asignacion","if_sentencia","iteracion","impresion",
"sentencia_retorno","expresion_aritmetica","destino","termino","operando",
"expresion_sin_asignacion","termino_sin_asignacion","operando_base",
"parametros_reales","orden_evaluacion","constante_con_signo","lista_enteros",
"constante_invalida","lista_parametros_reales","parametro_real","condicion",
"bloque_if","fin_if","encabezado_iteracion","cuerpo_iteracion",
"bloque_o_sentencia","operador_relacional","illegal-symbol",
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
"declaracion_funcion : tipo_dato FUNCTION ID '(' ')' bloque_declarativo bloque_ejecutable",
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
"expresion_sin_asignacion : expresion_sin_asignacion '+' termino_sin_asignacion",
"expresion_sin_asignacion : expresion_sin_asignacion '-' termino_sin_asignacion",
"expresion_sin_asignacion : termino_sin_asignacion",
"termino_sin_asignacion : termino_sin_asignacion '*' operando_base",
"termino_sin_asignacion : termino_sin_asignacion '/' operando_base",
"termino_sin_asignacion : operando_base",
"operando : operando_base",
"operando : ID '=' '(' expresion_sin_asignacion ')'",
"operando_base : ID",
"operando_base : ID '.' ID",
"operando_base : ID '[' expresion_aritmetica ']'",
"operando_base : ID '(' parametros_reales ')' orden_evaluacion",
"operando_base : ID '.' ID '(' parametros_reales ')' orden_evaluacion",
"operando_base : ID '(' parametros_reales ')'",
"operando_base : ID '.' ID '(' parametros_reales ')'",
"operando_base : TOSF '(' expresion_aritmetica ')'",
"operando_base : constante_con_signo",
"orden_evaluacion : '[' lista_enteros ']'",
"orden_evaluacion : '[' error ']'",
"lista_enteros : lista_enteros ',' CTE",
"lista_enteros : lista_enteros ',' constante_invalida",
"lista_enteros : CTE",
"lista_enteros : constante_invalida",
"parametros_reales : lista_parametros_reales",
"lista_parametros_reales : lista_parametros_reales ',' parametro_real",
"lista_parametros_reales : parametro_real",
"parametro_real : expresion_aritmetica",
"parametro_real : ID '=' expresion_aritmetica",
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
"if_sentencia : IF '(' condicion ')' bloque_if fin_if",
"if_sentencia : IF condicion ')' bloque_if fin_if",
"if_sentencia : IF '(' condicion bloque_if fin_if",
"if_sentencia : IF '(' condicion ')' bloque_if error",
"fin_if : ELSE bloque_if END_IF",
"fin_if : END_IF",
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
#line 403 "src/gramatica.y"

void yyerror(const char *s) {
    const char *COLOR_ROJO = "\033[1;31m";
    const char *COLOR_AMARILLO = "\033[1;33m";
    const char *COLOR_RESET = "\033[0m";

    if (strncmp(s, "syntax error", 12) == 0) {
        return; 
    }

    if (strstr(s, "Sentencia mal formada") != NULL) {
        cant_errores++; 
        fprintf(stderr, "%s[ERROR DE SINTAXIS]%s %sLínea %d:%s Sentencia inválida.\n", 
                COLOR_ROJO, COLOR_RESET, COLOR_AMARILLO, yylineno, COLOR_RESET);
        return;
    }

    cant_errores++;
    const char *mensaje = (strncmp(s, "Error: ", 7) == 0) ? s + 7 : s;
    
    fprintf(stderr, "%s[ERROR DE SINTAXIS]%s %sLínea %d:%s %s\n", 
            COLOR_ROJO, COLOR_RESET, COLOR_AMARILLO, yylineno, COLOR_RESET, mensaje);
}
#line 871 "y.tab.c"

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
#line 31 "src/gramatica.y"
	{
        if (cant_errores == 0) {
            printf("[SINT] Estructura Programa, en línea %d\n", yylineno);
            printf("Sintaxis correcta: Programa reconocido con éxito.\n"); 
        } else {
            printf("Sintaxis incorrecta: finalizado con %d error(es).\n", cant_errores);
        }
    }
#line 1551 "y.tab.c"
break;
case 2:
#line 40 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador ; al final del bloque ejecutable."); yyerrok; }
#line 1556 "y.tab.c"
break;
case 3:
#line 42 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador END al final del bloque ejecutable."); yyerrok; }
#line 1561 "y.tab.c"
break;
case 4:
#line 44 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
#line 1566 "y.tab.c"
break;
case 15:
#line 68 "src/gramatica.y"
	{ yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
#line 1571 "y.tab.c"
break;
case 18:
#line 78 "src/gramatica.y"
	{ printf("[SINT] Estructura Variable, en línea %d\n", yylineno); }
#line 1576 "y.tab.c"
break;
case 21:
#line 88 "src/gramatica.y"
	{ printf("[SINT] Estructura Objeto, en línea %d\n", yylineno); }
#line 1581 "y.tab.c"
break;
case 22:
#line 93 "src/gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1586 "y.tab.c"
break;
case 23:
#line 95 "src/gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1591 "y.tab.c"
break;
case 24:
#line 97 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
#line 1596 "y.tab.c"
break;
case 25:
#line 99 "src/gramatica.y"
	{ yyerror("Error: Faltan los parametros de la función."); yyerrok; }
#line 1601 "y.tab.c"
break;
case 27:
#line 105 "src/gramatica.y"
	{ yyerror("Error: Falta de ',' en declaración de parámetros."); yyerrok; }
#line 1606 "y.tab.c"
break;
case 30:
#line 112 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
#line 1611 "y.tab.c"
break;
case 31:
#line 117 "src/gramatica.y"
	{ printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); }
#line 1616 "y.tab.c"
break;
case 33:
#line 122 "src/gramatica.y"
	{ yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
#line 1621 "y.tab.c"
break;
case 38:
#line 134 "src/gramatica.y"
	{ yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
#line 1626 "y.tab.c"
break;
case 44:
#line 150 "src/gramatica.y"
	{ yyerror("Error: Falta de delimitador de sentencias ejecutables BEGIN."); yyerrok; }
#line 1631 "y.tab.c"
break;
case 47:
#line 157 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 1636 "y.tab.c"
break;
case 48:
#line 159 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 1641 "y.tab.c"
break;
case 54:
#line 172 "src/gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1646 "y.tab.c"
break;
case 55:
#line 174 "src/gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1651 "y.tab.c"
break;
case 56:
#line 179 "src/gramatica.y"
	{ printf("[SINT] Estructura ASSIGN, en línea %d\n", yylineno); }
#line 1656 "y.tab.c"
break;
case 57:
#line 181 "src/gramatica.y"
	{ yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
#line 1661 "y.tab.c"
break;
case 61:
#line 192 "src/gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1666 "y.tab.c"
break;
case 62:
#line 194 "src/gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1671 "y.tab.c"
break;
case 63:
#line 196 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1676 "y.tab.c"
break;
case 64:
#line 198 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1681 "y.tab.c"
break;
case 67:
#line 205 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '+'."); yyerrok; }
#line 1686 "y.tab.c"
break;
case 68:
#line 207 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '-'."); yyerrok; }
#line 1691 "y.tab.c"
break;
case 72:
#line 215 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '*'."); yyerrok; }
#line 1696 "y.tab.c"
break;
case 73:
#line 217 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '/'."); yyerrok; }
#line 1701 "y.tab.c"
break;
case 88:
#line 245 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 1706 "y.tab.c"
break;
case 89:
#line 247 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 1711 "y.tab.c"
break;
case 93:
#line 255 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 1716 "y.tab.c"
break;
case 103:
#line 281 "src/gramatica.y"
	{ cant_errores++; }
#line 1721 "y.tab.c"
break;
case 104:
#line 283 "src/gramatica.y"
	{ cant_errores++; }
#line 1726 "y.tab.c"
break;
case 105:
#line 288 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            long valor = strtol(yystack.l_mark[0].simbolo->lexema, NULL, 10);
            if (valor > 32767) {
                printf("\nLínea %d: Error: La constante entera positiva '%s' excede el rango máximo permitido [32767]\n\n", yylineno, yystack.l_mark[0].simbolo->lexema);
            }
            printf("[SINT] Constante entera positiva, lexema: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1739 "y.tab.c"
break;
case 106:
#line 298 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            printf("[SINT] Constante float positiva, lexema: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1748 "y.tab.c"
break;
case 107:
#line 304 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            long valor = strtol(yystack.l_mark[0].simbolo->lexema, NULL, 10);
            if (valor > 32767) {
                printf("\nLínea %d: Error: La constante entera positiva '+%s' excede el rango máximo permitido [32767]\n\n", yylineno, yystack.l_mark[0].simbolo->lexema);
            }
            printf("[SINT] Constante entera positiva (+), lexema: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1761 "y.tab.c"
break;
case 108:
#line 314 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            printf("[SINT] Constante float positiva (+), lexema: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1770 "y.tab.c"
break;
case 109:
#line 320 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
        Simbolo *negativo = cambiar_signo_constante(yystack.l_mark[0].simbolo, -1);
        printf("[SINT] Constante entera negativa, lexema actualizado a: '%s' en línea %d\n", negativo->lexema, yylineno);
        }
    }
#line 1780 "y.tab.c"
break;
case 110:
#line 327 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
        Simbolo *negativo = cambiar_signo_constante(yystack.l_mark[0].simbolo, -1);
        printf("[SINT] Constante float negativa, lexema actualizado a: '%s' en línea %d\n", negativo->lexema, yylineno);
        }
    }
#line 1790 "y.tab.c"
break;
case 114:
#line 340 "src/gramatica.y"
	{ printf("[SINT] Estructura IF, en línea %d\n", yylineno); }
#line 1795 "y.tab.c"
break;
case 115:
#line 342 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
#line 1800 "y.tab.c"
break;
case 116:
#line 344 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
#line 1805 "y.tab.c"
break;
case 117:
#line 346 "src/gramatica.y"
	{ yyerror("Error: Estructura IF mal cerrada (posiblemente falta END_IF o el delimitador ';')."); yyerrok; }
#line 1810 "y.tab.c"
break;
case 118:
#line 351 "src/gramatica.y"
	{ printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); }
#line 1815 "y.tab.c"
break;
case 122:
#line 362 "src/gramatica.y"
	{ printf("[SINT] Estructura ITERACION, en línea %d\n", yylineno); }
#line 1820 "y.tab.c"
break;
case 125:
#line 369 "src/gramatica.y"
	{ yyerror("Error: Falta identificador (ID) en el encabezado."); yyerrok; }
#line 1825 "y.tab.c"
break;
case 126:
#line 371 "src/gramatica.y"
	{ yyerror("Error: Falta 'TO' en el encabezado de la iteración."); yyerrok; }
#line 1830 "y.tab.c"
break;
case 127:
#line 373 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
#line 1835 "y.tab.c"
break;
case 128:
#line 375 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
#line 1840 "y.tab.c"
break;
case 129:
#line 377 "src/gramatica.y"
	{ yyerror("Error: Falta CTE en el encabezado."); yyerrok; }
#line 1845 "y.tab.c"
break;
#line 1847 "y.tab.c"
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
