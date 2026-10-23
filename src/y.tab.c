/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20240109

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
   28,   28,   28,   28,   29,   29,   29,   29,   29,   29,
   29,   31,   31,   31,   33,   33,   33,   33,   30,   35,
   35,   36,   36,   34,   34,   32,   32,   32,   32,   32,
   32,   32,   32,   32,   22,   22,   22,   22,   39,   39,
   23,   40,   40,   40,   40,   40,   40,   40,   41,   38,
   38,   37,   42,   42,   42,   42,   42,   42,
};
static const YYINT yylen[] = {                            2,
    4,    3,    4,    3,    1,    0,    2,    1,    2,    2,
    2,    2,    2,    2,    2,    1,    1,    2,    3,    1,
    2,    8,    6,    8,    7,    3,    2,    1,    2,    1,
    6,    1,    0,    3,    1,    1,    3,    2,    2,    1,
    2,    2,    3,    3,    3,    2,    3,    2,    1,    1,
    1,    1,    1,    4,    3,    3,    3,    1,    3,    4,
    4,    4,    3,    2,    3,    3,    3,    3,    1,    3,
    3,    3,    3,    1,    1,    3,    4,    5,    7,    4,
    1,    3,    3,    0,    3,    3,    1,    1,    1,    3,
    1,    1,    3,    1,    1,    1,    1,    2,    2,    2,
    2,    1,    2,    2,    6,    5,    5,    6,    3,    1,
    3,    8,    4,    7,    5,    3,    3,    4,    1,    1,
    1,    3,    1,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,   16,   17,    0,    0,    0,    0,    8,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   20,
   14,    0,    0,    0,    0,    0,    0,    7,    9,   10,
   11,   12,   13,    0,    0,    0,    0,    0,    0,   32,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   49,
   50,   51,   52,   53,    0,    0,    0,    4,    0,    0,
    0,    0,    1,   19,   36,    0,    0,   48,    0,    0,
    0,   96,   97,   94,   95,    0,    0,    0,    0,    0,
    0,   74,   81,  102,    0,   64,    0,    0,    0,    0,
    0,    0,    0,   44,    0,   46,    0,    0,    0,   43,
    0,    0,   28,    0,    0,   35,   38,    0,    0,    0,
    0,   40,   59,    0,    0,    0,    0,    0,    0,   98,
   99,  103,  100,  101,  104,  125,  126,  127,  128,    0,
    0,  123,  124,    0,    0,    0,    0,    0,   63,    0,
   55,    0,    0,    0,    0,  116,   47,   45,    0,    0,
  120,  121,  119,  111,   29,    0,    0,   27,    0,    0,
    0,   37,    0,   41,   42,   31,   39,   60,    0,    0,
    0,    0,   91,    0,    0,    0,    0,    0,   67,    0,
   68,    0,    0,   72,   70,   73,   71,    0,   62,   61,
   54,  118,    0,  113,    0,   26,   23,    0,    0,    0,
   34,    0,    0,    0,    0,   77,   80,    0,    0,  110,
  107,  106,    0,  115,    0,    0,   25,    0,    0,    0,
   78,   90,    0,  108,  105,    0,    0,    0,   24,   22,
    0,   87,    0,   88,    0,  109,    0,  114,   83,    0,
   82,   79,  112,   85,   86,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  257,  275,  277,  278,  283,  287,  288,  291,  292,  293,
  294,  295,  296,  297,  299,  257,  288,  298,  257,  257,
  293,  298,  299,  256,  271,  289,  257,  292,   59,   59,
   59,   59,   59,  257,  276,  298,  271,  289,   44,  257,
  302,  256,  257,  268,  273,  274,  279,  290,  307,  308,
  309,  310,  311,  312,  314,  327,  290,   59,   40,  256,
  257,  290,   59,  257,  271,  285,  303,   59,   46,   91,
  257,  258,  259,  266,  267,  284,   40,   43,   45,  313,
  315,  316,  319,  321,  324,  256,   40,   40,  257,   40,
   61,  324,  256,  272,  307,   59,  261,   61,  282,  272,
  299,  300,  301,   40,   40,  257,  271,  305,  293,  294,
  304,  306,  257,  313,   40,   46,   91,   40,  324,  258,
  259,  321,  258,  259,  321,  262,  263,  264,  265,   43,
   45,   60,   62,  329,   42,   47,   41,  260,   41,  313,
   41,  313,   61,  324,  319,   41,   59,   59,  313,  313,
  289,  307,  325,  328,  257,   44,   41,  301,  300,   41,
  300,  271,   44,   59,   59,  272,  306,   93,  257,  313,
  317,  322,  323,  257,  313,  313,   41,  325,  256,  315,
  256,  315,  313,  256,  316,  256,  316,  325,   41,   41,
   41,  280,  319,   41,  280,  301,  289,   41,  288,   41,
  257,   61,   41,   44,   40,   93,   41,  325,  269,  270,
  326,  326,  280,  319,  319,  288,  289,  288,  313,   91,
  318,  323,  317,  256,  326,  325,  319,  281,  289,  289,
  256,  258,  320,  321,   41,  270,  281,  319,   93,   44,
   93,  318,  319,  258,  321,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          6,
    7,  151,   48,    8,    9,   10,   11,   12,   13,   14,
   18,   15,  102,  103,   41,   67,  111,  108,  112,  152,
   50,   51,   52,   53,   54,   80,   55,   81,   82,  171,
  221,   83,  233,   84,  172,  173,   85,  153,  211,   56,
  154,  134,
};
static const YYINT yysindex[] = {                      -143,
  279, -217,    0,    0, -234,    0, -237,  286,    0,   20,
   57,   74,   79,   87, -251,  -99, -160,  118,  -91,    0,
    0,  118,  -99,  319,  319,  119,  -99,    0,    0,    0,
    0,    0,    0,  149, -148,  118,  319,  141,  -53,    0,
  -97,  161,  -22,  -36,  -32,  185,  -40,  309,  184,    0,
    0,    0,    0,    0,  -50,  -18,  317,    0,  -87,  210,
  226,  317,    0,    0,    0, -220,  -87,    0,    3,   23,
   15,    0,    0,    0,    0,  231,   23,  313,  341,  122,
   16,    0,    0,    0,  236,    0,  -25,  -12,   -4,   23,
  267,  247,  246,    0,  250,    0,   23,   23,  171,    0,
   44,   18,    0,  -87,   90,    0,    0,  -43,  254,  271,
  -63,    0,    0,   11,   76,   97,   23,   23,  242,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  163,
  167,    0,    0,   23,  206,  220,  171,  295,    0,  162,
    0,  195,  194,  321,   83,    0,    0,    0,  114,  114,
    0,    0,    0,    0,    0,  -87, -237,    0,   39,  286,
   41,    0,  113,    0,    0,    0,    0,    0,   -1,  114,
  334,  332,    0,  350,   50,  371,  171,  -17,    0,   16,
    0,   16,  114,    0,    0,    0,    0,  -17,    0,    0,
    0,    0,  261,    0,  267,    0,    0,  286, -237,  286,
    0,   23,  290,   76,   76,    0,    0,  -83,  171,    0,
    0,    0,  267,    0,  115, -237,    0, -237,  114,  200,
    0,    0,  353,    0,    0,  127,  130,  267,    0,    0,
  315,    0,  -16,    0,  290,    0,  267,    0,    0,  -73,
    0,    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                      -111,
 -111,    0,    0,    0,    0,    0,    0, -107,    0,    0,
    0,    0,    0,    0,    0,  111,    0,  354,  -88,    0,
    0,  358,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  111,    0,  376,    0,  436,    0,    0,
    0,    0,  -48,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  437,    0,    0,    0,    0,    0,    0,    0,    0,
    5,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   82,    0,    0,    0,    0,    0,    0,    0,  446,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   71,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  177,    0,    0,    0,    0,  133,  199,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -111,
    0,    0,    0,    0,    0,    0,    0,    0,  568,   -3,
    0,  429,    0,   29,    0,    0,    0,    0,    0,  109,
    0,  136,  175,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -111,    0, -111,
    0,    0,   58,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   69,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   58,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
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
    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
    1,  352,  -15,    0,  463,   25,  -14,    0,    0,    0,
  124,  336,  152,  -75,    0,    0,    0,    0,  364,  498,
    0,    0,    0,    0,    0,  414,    0,  227,  189,  275,
  248,  -65,    0,  -64,    0,  277,   47, -102, -176,    0,
    0,    0,
};
#define YYTABLESIZE 711
static const YYINT yytable[] = {                         90,
  163,   17,   78,   77,   79,   34,   78,   87,   79,   57,
   98,  212,   58,  122,  125,  139,  178,   78,   24,   79,
   91,   62,   20,   69,   35,  145,  158,  240,  141,   21,
   78,  225,   79,   25,  188,  115,  106,   92,  115,   19,
   92,  116,    3,    4,  116,   75,   75,   75,   75,   75,
  107,   75,  110,  130,  115,  131,  143,  135,  157,  202,
  116,  156,  136,   75,   75,   78,   75,   79,   70,   76,
   76,   76,   76,   76,  208,   76,  241,  193,   29,  198,
  196,  200,  156,  158,  156,  158,  117,   76,   76,  117,
   76,  109,  130,   92,  131,   24,  110,   75,   84,   84,
   84,   84,   84,  168,   84,  117,  226,   60,   61,   93,
   37,   30,   93,    1,   30,   30,   84,   84,   78,   84,
   79,   76,   69,  119,   69,   69,   69,  214,   22,  215,
  160,    2,   31,    3,    4,  109,  144,   32,   36,    5,
   69,   69,  206,   69,    6,   33,   36,  227,    5,   65,
   84,   65,   65,   65,   20,  234,  130,   20,  131,    6,
  199,   39,  238,    5,  130,   40,  131,   65,   65,   20,
   65,  243,  224,   65,   69,  245,   66,   58,   66,   66,
   66,  132,   33,  133,  244,  209,  210,   66,   59,    3,
    4,   56,   74,   75,   66,   66,   33,   66,  216,   63,
  218,   65,  190,   64,  130,   78,  131,   79,  166,   78,
   97,   79,   58,    3,    4,  122,   89,   72,   73,   68,
   71,   72,   73,   86,   88,   74,   75,  162,   66,   74,
   75,   71,   72,   73,  138,  191,   78,  130,   79,  131,
   74,   75,   96,   76,   71,   72,   73,   76,   78,  104,
   79,  209,  210,   74,   75,  159,  161,   57,   76,  113,
   75,   75,   78,   99,   79,  105,   75,   75,   75,   75,
  118,   76,   75,   75,   75,   75,  137,   75,   75,   71,
   72,   73,  177,   75,   76,   76,   75,  146,   74,   75,
   76,   76,   76,   76,    3,    4,   76,   76,   76,   76,
  155,   76,   76,   78,  147,   79,   76,   76,  148,   78,
   76,   79,  164,   84,   84,    3,    4,    3,    4,   84,
   84,   84,   84,  185,  187,   84,   84,   84,   84,  165,
   84,   84,  169,   72,   73,  189,   84,   69,   69,   84,
   23,   74,   75,   69,   69,   69,   69,   30,   30,   69,
   69,   69,   69,  174,   69,   69,  180,  182,   26,   76,
   69,  194,  195,   69,   65,   65,    3,    4,   38,  201,
   65,   65,   65,   65,  203,  204,   65,   65,   65,   65,
  220,   65,   65,  126,  127,  128,  129,   65,   56,  205,
   65,   66,   66,  235,  101,  228,  236,   66,   66,   66,
   66,   56,   56,   66,   66,   66,   66,  239,   66,   66,
  237,  207,   21,  130,   66,  131,   15,   66,  179,   71,
   72,   73,  181,   71,   72,   73,   24,   43,   74,   75,
  122,  122,   74,   75,   18,    2,    3,  101,   44,  101,
  101,   25,  122,   45,   46,  122,   76,  122,  122,   47,
   76,   72,   73,  122,   57,  231,  122,  232,  117,   74,
   75,  184,   71,   72,   73,   74,   75,   57,   57,   89,
   28,   74,   75,  192,  167,  186,   71,   72,   73,  223,
  222,    0,  242,  114,    0,   74,   75,   75,   75,   76,
   75,  101,   75,    0,  101,    0,  101,   24,   43,    0,
  140,  142,    0,   76,    0,   75,    0,   75,  197,   44,
  149,  150,   25,    0,   45,   46,    0,    0,   72,   73,
   47,   49,   49,    0,   72,   73,   74,   75,  170,    0,
  175,  176,   74,   75,   49,   16,    0,    0,    0,    0,
  213,    0,   27,    0,    0,   95,    0,  183,    0,    0,
  217,    0,    0,    2,   95,    3,    4,    0,    0,   95,
    2,    5,    3,    4,   93,   43,    0,  229,    5,  230,
  120,  121,   93,   43,   42,   43,   44,    0,   74,   75,
   94,   45,   46,    0,   44,    0,   44,   47,  100,   45,
   46,   45,   46,    0,    0,   47,    0,   47,  123,  124,
    0,    0,    0,    0,    0,    0,   74,   75,   75,   75,
   75,   75,   75,    0,   75,  219,    0,  170,  170,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   75,   75,   75,
   75,
};
static const YYINT yycheck[] = {                         40,
   44,    1,   43,   40,   45,  257,   43,   40,   45,   25,
   61,  188,   61,   78,   79,   41,  119,   43,  256,   45,
   61,   37,  257,   46,  276,   91,  102,   44,   41,    5,
   43,  208,   45,  271,  137,   40,  257,   41,   40,  257,
   44,   46,  277,  278,   46,   41,   42,   43,   44,   45,
  271,   47,   67,   43,   40,   45,   61,   42,   41,   61,
   46,   44,   47,   59,   60,   43,   62,   45,   91,   41,
   42,   43,   44,   45,  177,   47,   93,  143,   59,   41,
  156,   41,   44,  159,   44,  161,   91,   59,   60,   91,
   62,   67,   43,   47,   45,  256,  111,   93,   41,   42,
   43,   44,   45,   93,   47,   91,  209,  256,  257,   41,
  271,   41,   44,  257,   44,   59,   59,   60,   43,   62,
   45,   93,   41,   77,   43,   44,   45,  193,    5,  195,
   41,  275,   59,  277,  278,  111,   90,   59,   15,  283,
   59,   60,   93,   62,  256,   59,   23,  213,  256,   41,
   93,   43,   44,   45,   44,  220,   43,  257,   45,  271,
  160,   44,  228,  271,   43,  257,   45,   59,   60,   59,
   62,  237,  256,  271,   93,  240,   41,   59,   43,   44,
   45,   60,  271,   62,  258,  269,  270,  285,   40,  277,
  278,   59,  266,  267,   59,   60,  285,   62,  198,   59,
  200,   93,   41,  257,   43,   43,   45,   45,  272,   43,
  261,   45,  261,  277,  278,   41,  257,  258,  259,   59,
  257,  258,  259,  256,   40,  266,  267,  271,   93,  266,
  267,  257,  258,  259,  260,   41,   43,   43,   45,   45,
  266,  267,   59,  284,  257,  258,  259,  284,   43,   40,
   45,  269,  270,  266,  267,  104,  105,   59,  284,  257,
  256,  257,   43,  282,   45,   40,  262,  263,  264,  265,
   40,  284,  268,  269,  270,  271,   41,  273,  274,  257,
  258,  259,   41,  279,  256,  257,  282,   41,  266,  267,
  262,  263,  264,  265,  277,  278,  268,  269,  270,  271,
  257,  273,  274,   43,   59,   45,  284,  279,   59,   43,
  282,   45,   59,  256,  257,  277,  278,  277,  278,  262,
  263,  264,  265,  135,  136,  268,  269,  270,  271,   59,
  273,  274,  257,  258,  259,   41,  279,  256,  257,  282,
    5,  266,  267,  262,  263,  264,  265,  277,  278,  268,
  269,  270,  271,  257,  273,  274,  130,  131,    7,  284,
  279,   41,  280,  282,  256,  257,  277,  278,   17,  257,
  262,  263,  264,  265,   41,   44,  268,  269,  270,  271,
   91,  273,  274,  262,  263,  264,  265,  279,  256,   40,
  282,  256,  257,   41,   59,  281,  270,  262,  263,  264,
  265,  269,  270,  268,  269,  270,  271,   93,  273,  274,
  281,   41,   59,   43,  279,   45,   59,  282,  256,  257,
  258,  259,  256,  257,  258,  259,  256,  257,  266,  267,
  256,  257,  266,  267,   59,    0,    0,  102,  268,  104,
  105,  271,  268,  273,  274,  271,  284,  273,  274,  279,
  284,  258,  259,  279,  256,  256,  282,  258,  282,  266,
  267,  256,  257,  258,  259,  266,  267,  269,  270,   41,
    8,  266,  267,  280,  111,  256,  257,  258,  259,  205,
  204,   -1,  235,   70,   -1,  266,  267,   42,   43,  284,
   45,  156,   47,   -1,  159,   -1,  161,  256,  257,   -1,
   87,   88,   -1,  284,   -1,   60,   -1,   62,  157,  268,
   97,   98,  271,   -1,  273,  274,   -1,   -1,  258,  259,
  279,   24,   25,   -1,  258,  259,  266,  267,  115,   -1,
  117,  118,  266,  267,   37,  257,   -1,   -1,   -1,   -1,
  280,   -1,  257,   -1,   -1,   48,   -1,  134,   -1,   -1,
  199,   -1,   -1,  275,   57,  277,  278,   -1,   -1,   62,
  275,  283,  277,  278,  256,  257,   -1,  216,  283,  218,
  258,  259,  256,  257,  256,  257,  268,   -1,  266,  267,
  272,  273,  274,   -1,  268,   -1,  268,  279,  272,  273,
  274,  273,  274,   -1,   -1,  279,   -1,  279,  258,  259,
   -1,   -1,   -1,   -1,   -1,   -1,  266,  267,   41,   42,
   43,   44,   45,   -1,   47,  202,   -1,  204,  205,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,
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
};
#endif
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 285
#define YYUNDFTOKEN 330
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
"COMPTIME","TOSF","EXTENDS","$accept","programa","bloque_declarativo",
"bloque_ejecutable","lista_ejecutables","lista_declaraciones","declaracion",
"declaracion_variable","declaracion_funcion","declaracion_clase",
"declaracion_objeto","declaracion_comptime","lista_variables","tipo_dato",
"lista_parametros","parametro","codigo_clase","encabezado_clase",
"miembros_clase","lista_clase","miembro","sentencia","asignacion",
"if_sentencia","iteracion","impresion","sentencia_retorno",
"expresion_aritmetica","destino","termino","operando","parametros_reales",
"orden_evaluacion","constante_con_signo","lista_enteros","constante_invalida",
"lista_parametros_reales","parametro_real","condicion","bloque_o_sentencia",
"fin_if","encabezado_iteracion","cuerpo_iteracion","operador_relacional",
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
"if_sentencia : IF '(' condicion ')' bloque_o_sentencia fin_if",
"if_sentencia : IF condicion ')' bloque_o_sentencia fin_if",
"if_sentencia : IF '(' condicion bloque_o_sentencia fin_if",
"if_sentencia : IF '(' condicion ')' bloque_o_sentencia error",
"fin_if : ELSE bloque_o_sentencia END_IF",
"fin_if : END_IF",
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
#line 378 "src/gramatica.y"

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
#line 840 "y.tab.c"

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
#line 31 "src/gramatica.y"
	{
        if (cant_errores == 0) {
            printf("[SINT] Estructura Programa, en línea %d\n", yylineno);
            printf("Sintaxis correcta: Programa reconocido con éxito.\n"); 
        } else {
            printf("Sintaxis incorrecta: finalizado con %d error(es).\n", cant_errores);
        }
    }
#line 1520 "y.tab.c"
break;
case 2:
#line 40 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador ; al final del bloque ejecutable."); yyerrok; }
#line 1525 "y.tab.c"
break;
case 3:
#line 42 "src/gramatica.y"
	{ yyerror("Error: Falta el delimitador END al final del bloque ejecutable."); yyerrok; }
#line 1530 "y.tab.c"
break;
case 4:
#line 44 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
#line 1535 "y.tab.c"
break;
case 15:
#line 68 "src/gramatica.y"
	{ yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
#line 1540 "y.tab.c"
break;
case 18:
#line 78 "src/gramatica.y"
	{ printf("[SINT] Estructura Variable, en línea %d\n", yylineno); }
#line 1545 "y.tab.c"
break;
case 21:
#line 88 "src/gramatica.y"
	{ printf("[SINT] Estructura Objeto, en línea %d\n", yylineno); }
#line 1550 "y.tab.c"
break;
case 22:
#line 93 "src/gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1555 "y.tab.c"
break;
case 23:
#line 95 "src/gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1560 "y.tab.c"
break;
case 24:
#line 97 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
#line 1565 "y.tab.c"
break;
case 25:
#line 99 "src/gramatica.y"
	{ yyerror("Error: Faltan los parametros de la función."); yyerrok; }
#line 1570 "y.tab.c"
break;
case 27:
#line 105 "src/gramatica.y"
	{ yyerror("Error: Falta de ',' en declaración de parámetros."); yyerrok; }
#line 1575 "y.tab.c"
break;
case 30:
#line 112 "src/gramatica.y"
	{ yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
#line 1580 "y.tab.c"
break;
case 31:
#line 117 "src/gramatica.y"
	{ printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); }
#line 1585 "y.tab.c"
break;
case 33:
#line 122 "src/gramatica.y"
	{ yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
#line 1590 "y.tab.c"
break;
case 38:
#line 134 "src/gramatica.y"
	{ yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
#line 1595 "y.tab.c"
break;
case 44:
#line 150 "src/gramatica.y"
	{ yyerror("Error: Falta de delimitador de sentencias ejecutables BEGIN."); yyerrok; }
#line 1600 "y.tab.c"
break;
case 47:
#line 157 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 1605 "y.tab.c"
break;
case 48:
#line 159 "src/gramatica.y"
	{ yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
#line 1610 "y.tab.c"
break;
case 54:
#line 172 "src/gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1615 "y.tab.c"
break;
case 55:
#line 174 "src/gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1620 "y.tab.c"
break;
case 56:
#line 179 "src/gramatica.y"
	{ printf("[SINT] Estructura ASSIGN, en línea %d\n", yylineno); }
#line 1625 "y.tab.c"
break;
case 57:
#line 181 "src/gramatica.y"
	{ yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
#line 1630 "y.tab.c"
break;
case 61:
#line 192 "src/gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1635 "y.tab.c"
break;
case 62:
#line 194 "src/gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1640 "y.tab.c"
break;
case 63:
#line 196 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1645 "y.tab.c"
break;
case 64:
#line 198 "src/gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1650 "y.tab.c"
break;
case 67:
#line 205 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '+'."); yyerrok; }
#line 1655 "y.tab.c"
break;
case 68:
#line 207 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '-'."); yyerrok; }
#line 1660 "y.tab.c"
break;
case 72:
#line 215 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '*'."); yyerrok; }
#line 1665 "y.tab.c"
break;
case 73:
#line 217 "src/gramatica.y"
	{ yyerror("Error: Falta operando en la expresión después de '/'."); yyerrok; }
#line 1670 "y.tab.c"
break;
case 83:
#line 234 "src/gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 1675 "y.tab.c"
break;
case 94:
#line 261 "src/gramatica.y"
	{ cant_errores++; }
#line 1680 "y.tab.c"
break;
case 95:
#line 263 "src/gramatica.y"
	{ cant_errores++; }
#line 1685 "y.tab.c"
break;
case 96:
#line 268 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            long valor = strtol(yystack.l_mark[0].simbolo->lexema, NULL, 10);
            if (valor > 32767) {
                printf("\nLínea %d: Error: La constante entera positiva '%s' excede el rango máximo permitido [32767]\n\n", yylineno, yystack.l_mark[0].simbolo->lexema);
            }
            printf("[SINT] Constante entera positiva, lexema: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1698 "y.tab.c"
break;
case 97:
#line 278 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            printf("[SINT] Constante float positiva, lexema: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1707 "y.tab.c"
break;
case 98:
#line 284 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            long valor = strtol(yystack.l_mark[0].simbolo->lexema, NULL, 10);
            if (valor > 32767) {
                printf("\nLínea %d: Error: La constante entera positiva '+%s' excede el rango máximo permitido [32767]\n\n", yylineno, yystack.l_mark[0].simbolo->lexema);
            }
            printf("[SINT] Constante entera positiva (+), lexema: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1720 "y.tab.c"
break;
case 99:
#line 294 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
            printf("[SINT] Constante float positiva (+), lexema: '%s' en línea %d\n", yystack.l_mark[0].simbolo->lexema, yylineno);
        }
    }
#line 1729 "y.tab.c"
break;
case 100:
#line 300 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
        Simbolo *negativo = cambiar_signo_constante(yystack.l_mark[0].simbolo, -1);
        printf("[SINT] Constante entera negativa, lexema actualizado a: '%s' en línea %d\n", negativo->lexema, yylineno);
        }
    }
#line 1739 "y.tab.c"
break;
case 101:
#line 307 "src/gramatica.y"
	{
        if (yystack.l_mark[0].simbolo != NULL) {
        Simbolo *negativo = cambiar_signo_constante(yystack.l_mark[0].simbolo, -1);
        printf("[SINT] Constante float negativa, lexema actualizado a: '%s' en línea %d\n", negativo->lexema, yylineno);
        }
    }
#line 1749 "y.tab.c"
break;
case 105:
#line 320 "src/gramatica.y"
	{ printf("[SINT] Estructura IF, en línea %d\n", yylineno); }
#line 1754 "y.tab.c"
break;
case 106:
#line 322 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
#line 1759 "y.tab.c"
break;
case 107:
#line 324 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
#line 1764 "y.tab.c"
break;
case 108:
#line 326 "src/gramatica.y"
	{ yyerror("Error: Estructura IF mal cerrada (posiblemente falta END_IF o el delimitador ';')."); yyerrok; }
#line 1769 "y.tab.c"
break;
case 109:
#line 331 "src/gramatica.y"
	{ printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); }
#line 1774 "y.tab.c"
break;
case 111:
#line 337 "src/gramatica.y"
	{ printf("[SINT] Estructura ITERACION, en línea %d\n", yylineno); }
#line 1779 "y.tab.c"
break;
case 114:
#line 344 "src/gramatica.y"
	{ yyerror("Error: Falta identificador (ID) en el encabezado."); yyerrok; }
#line 1784 "y.tab.c"
break;
case 115:
#line 346 "src/gramatica.y"
	{ yyerror("Error: Falta 'TO' en el encabezado de la iteración."); yyerrok; }
#line 1789 "y.tab.c"
break;
case 116:
#line 348 "src/gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
#line 1794 "y.tab.c"
break;
case 117:
#line 350 "src/gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
#line 1799 "y.tab.c"
break;
case 118:
#line 352 "src/gramatica.y"
	{ yyerror("Error: Falta CTE en el encabezado."); yyerrok; }
#line 1804 "y.tab.c"
break;
#line 1806 "y.tab.c"
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
