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
#define PES_I 260
#define MULT_STRING 261
#define ASSIGN 262
#define GE 263
#define LE 264
#define EQ 265
#define NE 266
#define IF 267
#define ELSE 268
#define END_IF 269
#define BEGIN 270
#define END 271
#define POUT 272
#define RET 273
#define CLASS 274
#define FUNCTION 275
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
    0,    0,    1,    1,    3,    3,    4,    4,    4,    4,
    4,    9,    9,   11,   11,    5,   10,   10,    8,    6,
    6,    6,   12,   12,   12,   13,   13,    7,    7,   14,
   14,   17,   17,   15,   15,   15,   16,   16,   18,   18,
    2,    2,   19,   19,   19,   19,   20,   20,   20,   20,
   20,   25,   25,   21,   21,   27,   27,   27,   24,   24,
   24,   24,   26,   26,   26,   26,   26,   28,   28,   28,
   28,   28,   29,   29,   29,   29,   29,   29,   29,   31,
   31,   31,   33,   33,   30,   30,   34,   34,   35,   35,
   32,   32,   32,   32,   32,   32,   22,   22,   22,   22,
   38,   38,   23,   23,   39,   39,   39,   39,   39,   39,
   40,   37,   37,   36,   41,   41,   41,   41,   41,   41,
};
static const YYINT yylen[] = {                            2,
    4,    4,    1,    0,    2,    1,    2,    2,    2,    2,
    2,    2,    2,    1,    1,    2,    3,    1,    2,    8,
    6,    8,    3,    2,    1,    2,    1,    6,    6,    1,
    0,    3,    1,    1,    3,    2,    2,    1,    2,    2,
    3,    3,    3,    2,    3,    2,    1,    1,    1,    1,
    1,    4,    3,    3,    3,    1,    3,    4,    4,    4,
    3,    2,    3,    3,    3,    3,    1,    3,    3,    3,
    3,    1,    1,    3,    4,    5,    7,    4,    1,    3,
    3,    0,    3,    1,    1,    0,    3,    1,    1,    3,
    1,    1,    2,    2,    2,    2,    6,    5,    5,    6,
    3,    1,    3,    3,    8,    4,    7,    7,    3,    3,
    1,    1,    1,    3,    1,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,   14,    0,   15,    0,    0,    0,
    6,    0,    0,    0,    0,    0,    0,    0,   18,    0,
    0,   12,    0,    0,    0,    0,    0,    5,    7,    8,
    9,   10,   11,    0,    0,    0,    0,    0,    0,   30,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   47,
   48,   49,   50,   51,    0,    0,    0,    2,    0,    0,
    0,    1,   17,   34,    0,    0,    0,   46,    0,    0,
    0,   91,   92,    0,    0,    0,    0,    0,    0,   72,
   79,    0,   62,    0,    0,    0,    0,    0,    0,    0,
   42,    0,   44,    0,    0,    0,  112,  113,  111,    0,
   41,    0,    0,   25,    0,    0,   33,   36,    0,    0,
    0,    0,   38,    0,   57,    0,    0,    0,    0,    0,
    0,   93,   94,   95,   96,  117,  118,  119,  120,    0,
    0,  115,  116,    0,    0,    0,    0,    0,   61,    0,
   53,    0,    0,    0,    0,  109,   45,   43,    0,    0,
  104,  103,   26,    0,    0,   24,    0,    0,   35,    0,
   39,   40,   29,   37,   28,   58,    0,    0,    0,    0,
   88,    0,    0,    0,    0,    0,   65,    0,   66,    0,
    0,   70,   68,   71,   69,    0,   60,   59,   52,    0,
  106,    0,   23,   21,    0,    0,   32,    0,    0,    0,
    0,   75,   78,    0,    0,  102,   99,   98,    0,    0,
    0,    0,    0,    0,    0,   76,   87,    0,  100,   97,
    0,    0,    0,    0,   22,   20,    0,   84,    0,    0,
  101,    0,  108,  107,   81,    0,   80,   77,  105,   83,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  256,  257,  285,  257,  260,  274,  276,  281,  286,  288,
  289,  290,  291,  292,  293,  294,  296,  286,  257,  295,
  257,  290,  295,  296,  256,  270,  287,  289,   59,   59,
   59,   59,   59,  257,  275,  295,  287,   44,  256,  257,
  299,  256,  257,  267,  272,  273,  277,  304,  305,  306,
  307,  308,  309,  310,  312,  324,  304,   59,   40,  256,
  257,   59,  257,  270,  283,  300,  300,   59,   46,   91,
  257,  258,  259,  282,   40,   43,   45,  311,  313,  314,
  317,  321,  256,   40,   40,  257,   40,   61,  321,  256,
  271,  305,   59,  262,   61,  256,  287,  305,  322,  325,
  271,  296,  297,  298,   40,   40,  257,  270,  302,  290,
  291,  301,  303,  301,  257,  311,   40,   46,   91,   40,
  321,  258,  259,  258,  259,  263,  264,  265,  266,   43,
   45,   60,   62,  326,   42,   47,   41,  261,   41,  311,
   41,  311,   61,  321,  317,   41,   59,   59,  311,  311,
  280,  280,  257,   44,   41,  298,  297,  297,  270,   44,
   59,   59,  271,  303,  271,   93,  257,  311,  315,  319,
  320,  257,  311,  311,   41,  322,  256,  313,  256,  313,
  311,  256,  314,  256,  314,  322,   41,   41,   41,  317,
   41,  278,  298,  287,   41,   41,  257,   61,   41,   44,
   40,   93,   41,  322,  268,  269,  323,  323,  278,  317,
  317,  286,  286,  311,   91,  316,  320,  315,  256,  323,
  322,  317,  279,  279,  287,  287,  256,  258,  318,   41,
  269,  279,  317,  317,   93,   44,   93,  316,  317,  258,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          3,
    9,   97,   10,   11,   12,   13,   14,   15,   16,   36,
   17,  103,  104,   41,   66,  112,  109,  113,   48,   98,
   50,   51,   52,   53,   54,   78,   55,   79,   80,  169,
  216,   81,  229,  170,  171,   82,   99,  207,   56,  100,
  134,
};
static const YYINT yysindex[] = {                       -57,
 -103, -103,    0, -231,    0, -223,    0, -205, -141, -103,
    0,   10,   40,   62,  111,  123, -243, -141,    0,  144,
   19,    0,  144, -231,  307,  307,  156,    0,    0,    0,
    0,    0,    0,   50,   34,  144,  181,  -37, -140,    0,
 -140,  188,  -23,  -36,  -24,  212,  -40,  244,  197,    0,
    0,    0,    0,    0,  -59,  252,  274,    0, -227,  225,
  230,    0,    0,    0,  -90, -227, -227,    0,   20,  -14,
   27,    0,    0,  269,  -14,   39,   54,  399,   86,    0,
    0,  251,    0,  -33,  -28,    5,  -14,  -21,  273,  272,
    0,  277,    0,  -14,  -14,  218,    0,    0,    0,   61,
    0,   85,  150,    0, -227, -227,    0,    0,  -43,  284,
  285, -125,    0,  -70,    0,   63,  141,   96,  -14,  -14,
  152,    0,    0,    0,    0,    0,    0,    0,    0,  107,
  129,    0,    0,  -14,  134,  138,  282,  315,    0,  169,
    0,  337,  -21,  316,   97,    0,    0,    0,  -18,  -18,
    0,    0,    0, -227, -141,    0,  154,  167,    0,  122,
    0,    0,    0,    0,    0,    0,   46,  -18,  342,  362,
    0,  372,   67,  406,  282,   51,    0,   86,    0,   86,
  -18,    0,    0,    0,    0,   51,    0,    0,    0,  -25,
    0,  -21,    0,    0, -103, -103,    0,  -14,  330,  141,
  141,    0,    0,   31,  282,    0,    0,    0,  -21,  171,
  174, -141, -141,  -18,  -97,    0,    0,  405,    0,    0,
  166,  176,  -21,  -21,    0,    0,  347,    0,  -16,  330,
    0,  -21,    0,    0,    0,  208,    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
 -132, -132,    0,    0,    0,    0,    0,    0,    0,  -94,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  408,
  -74,    0,  409,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    3,    0,  411,    0,    0,    0,    0,
    0,    0,  -55,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   -6,    0,    0,    0,    0,    0,    0,    0,   60,    0,
    0,    0,    0,    0,    0,  394,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  172,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  430,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  300,    0,    0,    0,    0,  189,  196,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  360,  114,    0,  439,
    0,   16,    0,    0,    0,    0,    0,   82,    0,  104,
  161,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -132, -132,    0,    0,   38,    0,
  430,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  148,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   38,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
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
};
#endif
static const YYINT yygindex[] = {                         0,
    9,  260,    0,  471,   22,   73,    0,    0,    0,   42,
   11,  130,  -63,    0,  441,  416,    0,  127,  458,   17,
    0,    0,    0,    0,    0,  393,    0,  191,  199,  288,
  256,  270,    0,    0,  292,   -3,  -73,  -93,    0,    0,
    0,
};
#define YYTABLESIZE 665
static const YYINT yytable[] = {                         87,
  160,   95,   76,   75,   77,   56,   76,  139,   77,   76,
   18,   77,  141,   34,   76,   84,   77,   76,   24,   77,
   88,   76,   69,   77,  130,   19,  131,  236,   76,   22,
   77,   35,    5,   21,   73,   73,   73,   73,   73,  156,
   73,   49,   49,   89,  117,   20,   18,  176,    7,   23,
  118,   19,   73,   73,    5,   73,   74,   74,   74,   74,
   74,   18,   74,  186,   92,  143,  117,   70,   29,  102,
    7,  121,  118,   92,   74,   74,  237,   74,   82,   82,
   82,   82,   82,  144,   82,  117,   73,  110,  110,   59,
  193,  118,  208,  156,  156,  119,   82,   82,   30,   82,
   67,  204,   67,   67,   67,  130,  198,  131,   74,  130,
  220,  131,   49,  102,   25,  102,  102,  119,   67,   67,
   31,   67,   63,    4,   63,   63,   63,  135,   26,   64,
   82,  221,  136,  110,    5,  110,  119,    4,  111,  111,
   63,   63,   65,   63,   64,  163,   64,   64,   64,   76,
    7,   77,   67,    4,   89,  166,    5,   89,  227,  202,
  228,    3,   64,   64,  102,   64,  107,  102,  102,   32,
    6,   76,    7,   77,   63,    3,   76,    8,   77,  108,
   76,   33,   77,   76,  111,   77,  111,   38,   90,    5,
  155,   90,  175,  154,  195,   31,   64,  154,    1,    2,
  165,  114,   94,  212,  213,    7,   56,  196,   31,  188,
  154,  130,   27,  131,   58,   27,   86,   72,   73,   63,
   71,   72,   73,   71,   72,   73,  159,  138,   71,   72,
   73,   83,   72,   73,  157,  158,   72,   73,  164,   62,
  164,   74,   71,   72,   73,   74,   68,   54,   74,   73,
   73,   85,  209,   74,   55,   93,   73,   73,   73,   73,
   73,   73,   73,   73,  105,   73,   73,   74,   27,  106,
   73,   74,   74,   73,   39,   40,  115,   37,   74,   74,
   74,   74,   74,   74,   74,   74,  219,   74,   74,   60,
   61,  137,   74,   82,   82,   74,  122,  123,  205,  206,
   82,   82,   82,   82,   82,   82,   82,   82,  120,   82,
   82,  124,  125,  146,   82,   67,   67,   82,  205,  206,
  178,  180,   67,   67,   67,   67,   67,   67,   67,   67,
  147,   67,   67,  183,  185,  148,   67,   63,   63,   67,
  152,  153,  161,  162,   63,   63,   63,   63,   63,   63,
   63,   63,  172,   63,   63,  187,  191,  145,   63,   64,
   64,   63,  177,   71,   72,   73,   64,   64,   64,   64,
   64,   64,   64,   64,  192,   64,   64,  189,  197,  130,
   64,  131,  199,   64,  179,   71,   72,   73,   74,  182,
   71,   72,   73,  184,   71,   72,   73,  167,   72,   73,
   73,   73,   73,   73,   73,  200,   73,   25,   43,    5,
   74,  201,  190,    5,  194,   74,  114,  114,   44,   74,
  215,   26,   74,   45,   46,    7,    5,  114,   47,    7,
  114,   27,  114,  114,  231,   73,   73,  114,   73,  235,
   73,  130,    7,  131,   54,  230,  203,   27,  130,  223,
  131,   55,  224,   73,  232,   73,   54,   54,  132,  210,
  133,  211,  116,   55,   55,  240,   19,   13,   54,   16,
   86,  225,  226,   42,   43,   55,  140,  142,  222,   85,
   28,   67,  114,   57,   44,  238,  149,  150,  218,   45,
   46,  217,  233,  234,   47,    0,    0,  151,    0,   90,
   43,  239,    0,    0,    0,    0,    0,   96,   43,  168,
   44,  173,  174,    0,   91,   45,   46,    0,   44,    0,
   47,   26,    0,   45,   46,    0,  181,    0,   47,   90,
   43,    0,    0,    0,    0,    0,    0,   25,   43,    0,
   44,    0,    0,    0,  101,   45,   46,    0,   44,    0,
   47,   26,    0,   45,   46,  110,  110,    0,   47,    0,
    0,    0,   42,   43,    0,    0,  110,    0,    0,  110,
    0,  110,  110,   44,    0,    0,  110,    0,   45,   46,
    0,    0,    0,   47,    0,    0,    0,    0,    0,    0,
  214,    0,  168,  168,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   73,   73,   73,   73,
    0,  126,  127,  128,  129,
};
static const YYINT yycheck[] = {                         40,
   44,   61,   43,   40,   45,   61,   43,   41,   45,   43,
    2,   45,   41,  257,   43,   40,   45,   43,    8,   45,
   61,   43,   46,   45,   43,  257,   45,   44,   43,    8,
   45,  275,  260,  257,   41,   42,   43,   44,   45,  103,
   47,   25,   26,   47,   40,    4,   44,  121,  276,    8,
   46,  257,   59,   60,  260,   62,   41,   42,   43,   44,
   45,   59,   47,  137,   48,   61,   40,   91,   59,   59,
  276,   75,   46,   57,   59,   60,   93,   62,   41,   42,
   43,   44,   45,   87,   47,   40,   93,   66,   67,   40,
  154,   46,  186,  157,  158,   91,   59,   60,   59,   62,
   41,  175,   43,   44,   45,   43,   61,   45,   93,   43,
  204,   45,   96,  103,  256,  105,  106,   91,   59,   60,
   59,   62,   41,  256,   43,   44,   45,   42,  270,  270,
   93,  205,   47,  112,  260,  114,   91,  270,   66,   67,
   59,   60,  283,   62,   41,  271,   43,   44,   45,   43,
  276,   45,   93,  257,   41,   93,  260,   44,  256,   93,
  258,  256,   59,   60,  154,   62,  257,  157,  158,   59,
  274,   43,  276,   45,   93,  270,   43,  281,   45,  270,
   43,   59,   45,   43,  112,   45,  114,   44,   41,  260,
   41,   44,   41,   44,   41,  270,   93,   44,  256,  257,
  271,   41,  262,  195,  196,  276,  262,   41,  283,   41,
   44,   43,   41,   45,   59,   44,  257,  258,  259,  257,
  257,  258,  259,  257,  258,  259,  270,  261,  257,  258,
  259,  256,  258,  259,  105,  106,  258,  259,  112,   59,
  114,  282,  257,  258,  259,  282,   59,   59,  282,  256,
  257,   40,  278,  282,   59,   59,  263,  264,  265,  266,
  267,  268,  269,  270,   40,  272,  273,  282,    9,   40,
  277,  256,  257,  280,  256,  257,  257,   18,  263,  264,
  265,  266,  267,  268,  269,  270,  256,  272,  273,  256,
  257,   41,  277,  256,  257,  280,  258,  259,  268,  269,
  263,  264,  265,  266,  267,  268,  269,  270,   40,  272,
  273,  258,  259,   41,  277,  256,  257,  280,  268,  269,
  130,  131,  263,  264,  265,  266,  267,  268,  269,  270,
   59,  272,  273,  135,  136,   59,  277,  256,  257,  280,
  280,  257,   59,   59,  263,  264,  265,  266,  267,  268,
  269,  270,  257,  272,  273,   41,   41,   88,  277,  256,
  257,  280,  256,  257,  258,  259,  263,  264,  265,  266,
  267,  268,  269,  270,  278,  272,  273,   41,  257,   43,
  277,   45,   41,  280,  256,  257,  258,  259,  282,  256,
  257,  258,  259,  256,  257,  258,  259,  257,  258,  259,
   41,   42,   43,   44,   45,   44,   47,  256,  257,  260,
  282,   40,  143,  260,  155,  282,  256,  257,  267,  282,
   91,  270,  282,  272,  273,  276,  260,  267,  277,  276,
  270,  260,  272,  273,  269,   42,   43,  277,   45,   93,
   47,   43,  276,   45,  256,   41,   41,  276,   43,  279,
   45,  256,  279,   60,  279,   62,  268,  269,   60,  190,
   62,  192,   70,  268,  269,  258,   59,   59,  280,   59,
   41,  212,  213,  256,  257,  280,   84,   85,  209,   41,
   10,   41,   67,   26,  267,  230,   94,   95,  201,  272,
  273,  200,  223,  224,  277,   -1,   -1,  280,   -1,  256,
  257,  232,   -1,   -1,   -1,   -1,   -1,  256,  257,  117,
  267,  119,  120,   -1,  271,  272,  273,   -1,  267,   -1,
  277,  270,   -1,  272,  273,   -1,  134,   -1,  277,  256,
  257,   -1,   -1,   -1,   -1,   -1,   -1,  256,  257,   -1,
  267,   -1,   -1,   -1,  271,  272,  273,   -1,  267,   -1,
  277,  270,   -1,  272,  273,  256,  257,   -1,  277,   -1,
   -1,   -1,  256,  257,   -1,   -1,  267,   -1,   -1,  270,
   -1,  272,  273,  267,   -1,   -1,  277,   -1,  272,  273,
   -1,   -1,   -1,  277,   -1,   -1,   -1,   -1,   -1,   -1,
  198,   -1,  200,  201,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  263,  264,  265,  266,
   -1,  263,  264,  265,  266,
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
   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 283
#define YYUNDFTOKEN 327
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
0,0,0,0,0,0,0,0,0,"error","ID","CTE","CTE_FLOAT","PES_I","MULT_STRING","ASSIGN",
"GE","LE","EQ","NE","IF","ELSE","END_IF","BEGIN","END","POUT","RET","CLASS",
"FUNCTION","SINGLEF","FROM","TO","BY","REPEAT","COMPTIME","TOSF","EXTENDS",
"$accept","programa","bloque_declarativo","bloque_ejecutable",
"lista_declaraciones","declaracion","declaracion_variable",
"declaracion_funcion","declaracion_clase","declaracion_objeto",
"declaracion_comptime","lista_variables","tipo_dato","lista_parametros",
"parametro","codigo_clase","encabezado_clase","miembros_clase","lista_clase",
"miembro","lista_ejecutables","sentencia","asignacion","if_sentencia",
"iteracion","impresion","sentencia_retorno","expresion_aritmetica","destino",
"termino","operando","parametros_reales","orden_evaluacion",
"constante_con_signo","lista_enteros","lista_parametros_reales",
"parametro_real","condicion","bloque_o_sentencia","fin_if",
"encabezado_iteracion","cuerpo_iteracion","operador_relacional",
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : programa",
"programa : ID bloque_declarativo bloque_ejecutable ';'",
"programa : error bloque_declarativo bloque_ejecutable ';'",
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
"tipo_dato : PES_I",
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
"declaracion_clase : CLASS ID error encabezado_clase miembros_clase END",
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
"encabezado_iteracion : FROM ID '=' constante_con_signo constante_con_signo BY constante_con_signo",
"encabezado_iteracion : FROM condicion ')'",
"encabezado_iteracion : FROM '(' condicion",
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
#line 379 "src/gramatica.y"

void yyerror(const char *s) {
    const char *COLOR_ROJO = "\033[1;31m";
    const char *COLOR_AMARILLO = "\033[1;33m";
    const char *COLOR_RESET = "\033[0m";

    if (strncmp(s, "syntax error", 12) == 0) {
        return; 
    }

    if (strstr(s, "Sentencia mal formada") != NULL) {
        cant_errores++; /* Sumamos error */
        fprintf(stderr, "%s[ERROR DE SINTAXIS]%s %sLínea %d:%s Sentencia inválida. Es posible que falte un delimitador estructural (como 'END_IF' o ';') o un operador.\n", 
                COLOR_ROJO, COLOR_RESET, COLOR_AMARILLO, yylineno, COLOR_RESET);
        return;
    }

    cant_errores++; /* Sumamos error para cualquier regla de error personalizada */
    const char *mensaje = (strncmp(s, "Error: ", 7) == 0) ? s + 7 : s;
    
    fprintf(stderr, "%s[ERROR DE SINTAXIS]%s %sLínea %d:%s %s\n", 
            COLOR_ROJO, COLOR_RESET, COLOR_AMARILLO, yylineno, COLOR_RESET, mensaje);
}
#line 808 "y.tab.c"

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
#line 29 "src/gramatica.y"
	{ 
        if (cant_errores == 0) {
            printf("[SINT] Estructura Programa, en línea %d\n", yylineno);
            printf("Sintaxis correcta: Programa reconocido con éxito.\n"); 
        } else {
            printf("Sintaxis incorrecta: finalizado con %d error(es).\n", cant_errores);
        }
    }
#line 1488 "y.tab.c"
break;
case 2:
#line 38 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
#line 1493 "y.tab.c"
break;
case 13:
#line 62 "src/gramatica.y"
	{ yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
#line 1498 "y.tab.c"
break;
case 16:
#line 72 "src/gramatica.y"
	{ printf("[SINT] Estructura Variable, en línea %d\n", yylineno); }
#line 1503 "y.tab.c"
break;
case 19:
#line 82 "src/gramatica.y"
	{ printf("[SINT] Estructura Objeto, en línea %d\n", yylineno); }
#line 1508 "y.tab.c"
break;
case 20:
#line 87 "src/gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1513 "y.tab.c"
break;
case 21:
#line 89 "src/gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1518 "y.tab.c"
break;
case 22:
#line 91 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
#line 1523 "y.tab.c"
break;
case 24:
#line 97 "src/gramatica.y"
	{ yyerror("Error: Falta de ',' en declaración de parámetros."); yyerrok; }
#line 1528 "y.tab.c"
break;
case 27:
#line 104 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
#line 1533 "y.tab.c"
break;
case 28:
#line 110 "src/gramatica.y"
	{ printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); }
#line 1538 "y.tab.c"
break;
case 29:
#line 112 "src/gramatica.y"
	{ yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
#line 1543 "y.tab.c"
break;
case 36:
#line 129 "src/gramatica.y"
	{ yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
#line 1548 "y.tab.c"
break;
case 42:
#line 145 "src/gramatica.y"
	{ yyerror("Error: Falta de delimitador de sentencias ejecutables BEGIN."); yyerrok; }
#line 1553 "y.tab.c"
break;
case 45:
#line 152 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 1558 "y.tab.c"
break;
case 46:
#line 154 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 1563 "y.tab.c"
break;
case 52:
#line 167 "src/gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1568 "y.tab.c"
break;
case 53:
#line 169 "src/gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1573 "y.tab.c"
break;
case 54:
#line 174 "src/gramatica.y"
	{ printf("[SINT] Estructura ASSIGN, en línea %d\n", yylineno); }
#line 1578 "y.tab.c"
break;
case 55:
#line 176 "src/gramatica.y"
	{ yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
#line 1583 "y.tab.c"
break;
case 59:
#line 187 "src/gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1588 "y.tab.c"
break;
case 60:
#line 189 "src/gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1593 "y.tab.c"
break;
case 61:
#line 191 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1598 "y.tab.c"
break;
case 62:
#line 193 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1603 "y.tab.c"
break;
case 65:
#line 200 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '+'."); yyerrok; }
#line 1608 "y.tab.c"
break;
case 66:
#line 202 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '-'."); yyerrok; }
#line 1613 "y.tab.c"
break;
case 70:
#line 210 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '*'."); yyerrok; }
#line 1618 "y.tab.c"
break;
case 71:
#line 212 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '/'."); yyerrok; }
#line 1623 "y.tab.c"
break;
case 81:
#line 229 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 1628 "y.tab.c"
break;
case 91:
#line 255 "src/gramatica.y"
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
#line 1644 "y.tab.c"
break;
case 92:
#line 268 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "+%s", yystack.l_mark[0].simbolo->lexema);
            modificar_lexema(yystack.l_mark[0].simbolo, nuevo);
            printf("[SINT] Constante float positiva, lexema actualizado a: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1656 "y.tab.c"
break;
case 93:
#line 277 "src/gramatica.y"
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
#line 1672 "y.tab.c"
break;
case 94:
#line 290 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "+%s", yystack.l_mark[0].simbolo->lexema);
            modificar_lexema(yystack.l_mark[0].simbolo, nuevo);
            printf("[SINT] Constante float positiva (+), lexema actualizado a: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1684 "y.tab.c"
break;
case 95:
#line 299 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "-%s", yystack.l_mark[0].simbolo->lexema);
            modificar_lexema(yystack.l_mark[0].simbolo, nuevo);
            printf("[SINT] Constante entera negativa, lexema actualizado a: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1696 "y.tab.c"
break;
case 96:
#line 308 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "-%s", yystack.l_mark[0].simbolo->lexema);
            modificar_lexema(yystack.l_mark[0].simbolo, nuevo);
            printf("[SINT] Constante float negativa, lexema actualizado a: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1708 "y.tab.c"
break;
case 97:
#line 320 "src/gramatica.y"
	{ printf("[SINT] Estructura IF, en línea %d\n", yylineno); }
#line 1713 "y.tab.c"
break;
case 98:
#line 322 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
#line 1718 "y.tab.c"
break;
case 99:
#line 324 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
#line 1723 "y.tab.c"
break;
case 100:
#line 326 "src/gramatica.y"
	{ yyerror("Error: Estructura IF mal cerrada (posiblemente falta END_IF o el delimitador ';')."); yyerrok; }
#line 1728 "y.tab.c"
break;
case 101:
#line 331 "src/gramatica.y"
	{ printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); }
#line 1733 "y.tab.c"
break;
case 103:
#line 337 "src/gramatica.y"
	{ printf("[SINT] Estructura ITERACION, en línea %d\n", yylineno); }
#line 1738 "y.tab.c"
break;
case 104:
#line 339 "src/gramatica.y"
	{ yyerror("Error: Falta o hay un error en el cuerpo de la iteración."); yyerrok; }
#line 1743 "y.tab.c"
break;
case 107:
#line 346 "src/gramatica.y"
	{ yyerror("Error: Falta identificador (ID) en el encabezado."); yyerrok; }
#line 1748 "y.tab.c"
break;
case 108:
#line 348 "src/gramatica.y"
	{ yyerror("Error: Falta 'TO' en el encabezado de la iteración."); yyerrok; }
#line 1753 "y.tab.c"
break;
case 109:
#line 350 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
#line 1758 "y.tab.c"
break;
case 110:
#line 352 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
#line 1763 "y.tab.c"
break;
#line 1765 "y.tab.c"
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
