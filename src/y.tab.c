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

#line 2 "gramatica.y"
#include <stdio.h>
#include <stdlib.h>
#include "tabla_simbolos.h"

extern int yylex(void);
extern int yylineno;
void yyerror(const char *s);
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 11 "gramatica.y"
typedef union YYSTYPE {
    struct Simbolo *simbolo;
    int val_int;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 44 "y.tab.c"

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
#define LOWER_THAN_ELSE 284
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    2,    0,    0,    1,    1,    4,    4,    5,    5,    5,
    5,    5,   10,   10,   12,   12,    6,   11,   11,   13,
    9,   15,    7,   16,    7,    7,   14,   14,   14,   17,
   17,   17,   19,    8,    8,   18,   18,   22,   22,   20,
   20,   20,   21,   21,   23,   23,    3,    3,   24,   24,
   24,   24,   25,   25,   25,   25,   25,   30,   30,   33,
   26,   26,   32,   32,   32,   31,   31,   31,   31,   31,
   31,   34,   34,   34,   34,   34,   35,   35,   35,   35,
   35,   35,   35,   37,   37,   37,   39,   39,   36,   36,
   40,   40,   41,   41,   38,   38,   44,   27,   27,   27,
   45,   45,   45,   47,   46,   28,   28,   48,   48,   48,
   48,   48,   48,   48,   49,   43,   43,   42,   50,   50,
   50,   50,   50,   50,   29,   29,   29,   29,
};
static const YYINT yylen[] = {                            2,
    0,    7,    6,    1,    0,    2,    1,    2,    2,    2,
    2,    2,    2,    2,    1,    1,    2,    3,    1,    0,
    3,    0,   11,    0,    9,   10,    3,    3,    1,    2,
    2,    2,    0,    7,    6,    1,    0,    3,    1,    1,
    3,    2,    2,    1,    2,    2,    1,    0,    3,    2,
    3,    2,    1,    1,    1,    1,    1,    4,    3,    0,
    4,    3,    1,    3,    4,    3,    3,    1,    3,    3,
    2,    3,    3,    1,    3,    3,    1,    3,    4,    5,
    7,    4,    1,    3,    3,    0,    3,    1,    1,    0,
    3,    1,    1,    3,    1,    1,    0,    7,    6,    6,
    2,    2,    1,    0,    3,    3,    3,    8,    8,    7,
    7,    4,    4,    4,    1,    3,    1,    3,    1,    1,
    1,    1,    1,    1,    4,    4,    3,    2,
};
static const YYINT yydefred[] = {                         0,
    0,    1,    0,   20,   15,    0,   16,    0,    0,    0,
    7,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   19,   13,    0,    0,    0,    6,    8,    9,   10,   11,
   12,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   53,   54,
   55,   56,   57,    0,    0,    0,    0,    0,    0,   40,
    0,    0,   36,    0,   18,   52,    0,    0,    0,    0,
  128,    0,    0,    0,    0,    0,    0,    0,    0,   50,
   60,    0,    0,    0,  117,  115,    0,    0,    0,    0,
   29,    0,    0,    0,   39,   42,    0,    0,    0,    0,
   44,    0,   64,    0,   95,   96,    0,    0,    0,   74,
   83,    0,    0,    0,    0,  127,    0,   59,    0,    0,
    0,    0,    0,    3,   51,   49,    0,    0,    0,  107,
    0,  106,   32,   31,   30,    0,    0,   24,    0,    0,
    0,   41,    0,   45,   46,   35,   43,    0,    0,    0,
    0,    0,   65,    0,    0,    0,    0,    0,  121,  122,
  123,  124,  119,  120,    0,    0,    0,   97,  126,  125,
   58,    0,  113,    0,  114,  112,    0,    0,  116,   28,
   27,    0,    0,   22,    2,   38,   34,    0,    0,    0,
    0,   92,    0,    0,    0,   69,    0,   70,    0,   75,
   72,   76,   73,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   79,   82,
  103,  104,   99,    0,  100,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   80,   91,    0,    0,  102,
  101,   98,    0,    0,  111,  110,   25,    0,    0,    0,
   88,    0,    0,  105,  109,  108,   26,    0,   85,    0,
   84,   81,   23,   87,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  256,  257,  286,  257,  260,  274,  276,  281,  287,  290,
  291,  292,  293,  294,  295,  296,  298,  288,  299,  257,
  257,  292,  297,  298,  270,  291,   59,   59,   59,   59,
   59,  257,  275,  297,  287,  297,  256,  305,   44,  256,
  257,  267,  272,  273,  277,  289,  310,  311,  312,  313,
  314,  315,  316,  318,  334,   40,  256,  257,  270,  270,
  283,  306,  257,  304,  257,   59,   46,   91,  256,   40,
  256,   40,   40,  256,  257,   40,  271,  256,  311,   59,
  262,   61,  256,  270,  311,  329,  335,  256,  298,  300,
  303,   40,   40,  289,  257,  270,  308,  292,  293,  307,
  309,  306,  257,  257,  258,  259,  282,  317,  320,  321,
  324,  317,  328,  328,  261,   41,  317,   41,  317,   61,
  328,   61,  328,   59,   59,   59,  319,  317,  324,  280,
  289,  280,  257,  256,  257,  256,   44,   41,  300,  300,
  271,  270,   44,   59,   59,  271,  309,  307,   40,   46,
   91,   40,   93,   43,   45,  320,   42,   47,  263,  264,
  265,  266,   60,   62,  336,   41,  256,   41,   41,   41,
   41,  324,   41,  324,  256,   41,  317,  278,  271,  303,
  303,  302,   41,   41,   59,  257,  271,  257,  317,  322,
  326,  327,  257,  317,  317,  256,  320,  256,  320,  256,
  321,  256,  321,  317,  329,  329,  330,  278,  278,  324,
  324,  270,  287,  301,   61,   41,   44,   40,   93,   41,
  256,  268,  331,  332,  331,  329,  324,  324,  279,  279,
  289,  270,  287,  317,   91,  323,  327,  322,  333,  256,
  269,  331,  279,  279,  324,  324,  271,  289,  270,  256,
  258,  325,   41,  329,  324,  324,  271,  289,   93,   44,
   93,  323,  271,  258,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          3,
    9,   18,   46,   10,   11,   12,   13,   14,   15,   16,
   34,   17,   19,   90,  214,  182,   91,   64,   38,   62,
  100,   97,  101,   47,   48,   49,   50,   51,   52,   53,
  112,   54,  127,  109,  110,  190,  236,  111,  252,  191,
  192,  113,   86,  207,  223,  224,  239,   55,   87,  165,
};
static const YYINT yysindex[] = {                        30,
  195,    0,    0,    0,    0, -240,    0,  -63, -206,  195,
    0,    7,   21,   68,   82,   88, -101,  195,  -99,  -79,
    0,    0,  138,  -99,  257,    0,    0,    0,    0,    0,
    0,  149,   50,  138,  -83,  138, -200,  -65,  -46,  188,
  -10,   -8,   -3,  222,  -27,  -11,  265,  214,    0,    0,
    0,    0,    0,  -54,  234,  -76,  280,  300,  257,    0,
  -51, -250,    0, -200,    0,    0,   37, -219, -219, -219,
    0,  -26,   46,  -56,  253, -219,  288,  295,  301,    0,
    0, -219,   96,  257,    0,    0,  100,  132,   70,   18,
    0,  -76,  -76,  122,    0,    0,  -36,  341,  344,  -62,
    0, -250,    0,   -5,    0,    0,  367,   66,   61,    0,
    0,  133,  377,  -16,  383,    0,  -21,    0,    6,  -38,
  391,  -38,    1,    0,    0,    0, -219,  106,  156,    0,
  162,    0,    0,    0,    0,  -76,  -76,    0,   24,   44,
  382,    0,  186,    0,    0,    0,    0,  196, -134,  187,
 -219, -219,    0, -137,  164,   61,  180,  191,    0,    0,
    0,    0,    0,    0, -219,  274,  274,    0,    0,    0,
    0,  167,    0, -168,    0,    0,  106,  -38,    0,    0,
    0,  183,  195,    0,    0,    0,    0,  114,  106,  413,
  414,    0,  417,   86,   26,    0,   61,    0,   61,    0,
    0,    0,    0,  106, -245, -245,  274,  -38,  -38,  184,
  189,  257,  200,  195, -219,  384, -134, -134,    0,    0,
    0,    0,    0, -167,    0, -245,  201,  205,  -38,  -38,
  203,  257,  217,  106, -151,    0,    0,  451,  274,    0,
    0,    0,  -38,  -38,    0,    0,    0,  223,  257,  400,
    0,  -32,  384,    0,    0,    0,    0,  226,    0,  240,
    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
  233,    0,    0,    0,    0,    0,    0,    0,    0,  235,
    0,    0,    0,    0,    0,    0,    0,  233,    0, -100,
    0,    0,  449,    0,  244,    0,    0,    0,    0,    0,
    0,   84,    0,  457,    0,  461,    0,  -24,    0,    0,
  -52,    0,    0,    0,    0,    0,  255,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  244,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  244,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -41,    0,    0,    0,    0,   33,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  145,  126,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  482,    0,
    0,    0,    0,    0,    0,   53,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  148,    0,    0,    0,
    0,    0,  233,    0,    0,    0,    0,  120,  147,    0,
  484,    0,  -14,    0,    0,    0,   73,    0,   93,    0,
    0,    0,    0,    2,    0,    0,    0,    0,    0,    0,
    0,  244,    0,  233,    0,   13,    0,  482,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  244,    0,  155,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  244,    0,
    0,    0,   13,    0,    0,    0,    0,    0,    0,    0,
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
   -2,    0,  287,    0,  518,   42,  -18,    0,    0,    0,
  131,  373,    0,  277,    0,    0,  230,    0,    0,  469,
  433,    0,  -47,    0,  220,    0,    0,    0,    0,    0,
  337,    0,    0,  323,  254,  321,  290,  252,    0,    0,
  328,  409,  -67,    0, -192,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 557
static const YYINT yytable[] = {                         77,
   77,   77,   77,   77,  120,   77,   82,  143,   63,    5,
  221,  260,   76,  225,  116,   35,   20,   77,   77,  170,
   77,  154,  222,  155,  168,    7,   78,   78,   78,   78,
   78,   70,   78,  242,  149,   67,   72,  104,  105,  106,
  150,  176,  118,   99,   78,   78,  171,   78,  154,   22,
  155,   77,  147,   86,   86,   86,   86,   86,  138,   86,
  261,  137,  107,   25,  183,   27,  220,  137,  154,   60,
  155,   86,   86,   68,   86,   68,   68,   68,   78,   28,
   68,   99,   61,   99,  184,  151,  118,  137,  240,  105,
  106,   68,   68,   71,   68,   71,   71,   71,  205,  206,
  147,  241,  157,   98,  250,   86,  251,  158,  154,  209,
  155,   71,   71,   66,   71,   66,   66,   66,  196,  104,
  105,  106,  188,  105,  106,   68,   29,   19,  154,   99,
  155,   66,   66,   67,   66,   67,   67,   67,   23,  226,
   30,   98,   19,   98,  107,   71,   31,  107,  154,   36,
  155,   67,   67,  149,   67,   32,   33,   21,  153,  150,
   77,   77,   77,   77,   77,   66,   77,   83,   83,   33,
   83,  254,   83,   33,  215,  154,   37,  155,  219,   88,
  213,   39,   33,    5,   83,   67,   59,   93,   56,   98,
   93,   63,  163,   21,  164,   94,    5,    5,   94,    7,
  104,  105,  106,   62,  151,   95,   61,   81,  146,   63,
   65,  233,    7,    7,   77,   77,   77,   77,   96,  105,
  106,   77,   77,   77,   77,  107,   77,   77,   74,   75,
  104,  105,  106,  142,  115,  104,  105,  106,   77,  167,
   77,   78,   78,   78,   78,   37,   66,   69,   78,   78,
   78,   78,   71,   78,   78,  107,  175,  118,   37,   77,
  107,   73,  104,  105,  106,   78,   79,   78,   86,   86,
   86,   86,   80,  136,   85,   86,   86,   86,   86,  136,
   86,   86,  104,  105,  106,    1,    2,  107,   68,   68,
   68,   68,   86,  103,   86,   68,   68,   68,   68,  136,
   68,   68,  104,  105,  106,   57,   58,  107,   71,   71,
   71,   71,   68,  122,   68,   71,   71,   71,   71,   92,
   71,   71,  104,  105,  106,  134,  135,  107,   66,   66,
   66,   66,   71,  129,   71,   66,   66,   66,   66,   93,
   66,   66,  104,  105,  106,   94,  124,  107,   67,   67,
   67,   67,   66,  125,   66,   67,   67,   67,   67,  126,
   67,   67,  104,  105,  106,  180,  181,  107,  139,  140,
  131,  172,   67,  174,   67,  130,   77,   77,   77,  132,
   24,   83,   83,   83,   83,   85,   85,  107,  133,  104,
  105,  106,  141,   83,   83,  159,  160,  161,  162,  144,
   62,   77,  145,   61,  108,   83,  152,   83,  117,  119,
  201,  203,   62,   62,  107,   61,   61,  166,  128,  198,
  104,  105,  106,  169,   62,  210,   85,   61,   89,  211,
  156,  173,  179,  178,  156,  200,  104,  105,  106,  156,
  185,  156,  186,  193,  208,  107,  202,  104,  105,  106,
  156,    4,  212,  216,    5,    5,  218,  217,   85,  227,
  228,  107,  229,  177,   89,   89,  187,  230,    6,  232,
    7,    7,  107,  247,  235,    8,  197,  199,  114,  243,
  245,  246,  121,  244,  123,  189,  249,  194,  195,   83,
   41,  253,  259,  257,  255,  256,  263,  264,  231,  156,
   42,  204,    5,   84,    4,   43,   44,   14,   89,   89,
   45,  156,   40,   41,   48,   17,  156,  156,  248,   21,
   78,   41,   90,   42,   89,   47,  156,   26,   43,   44,
   41,   42,  102,   45,  148,  258,   43,   44,  238,    0,
   42,   45,  262,   84,  237,   43,   44,    0,    0,    0,
   45,  234,    0,  189,  189,    0,  156,
};
static const YYINT yycheck[] = {                         41,
   42,   43,   44,   45,   61,   47,   61,   44,   61,  260,
  256,   44,   40,  206,   41,   18,  257,   59,   60,   41,
   62,   43,  268,   45,   41,  276,   41,   42,   43,   44,
   45,   40,   47,  226,   40,   46,   40,  257,  258,  259,
   46,   41,   41,   62,   59,   60,   41,   62,   43,    8,
   45,   93,  100,   41,   42,   43,   44,   45,   41,   47,
   93,   44,  282,  270,   41,   59,   41,   44,   43,  270,
   45,   59,   60,   41,   62,   43,   44,   45,   93,   59,
   91,  100,  283,  102,   41,   91,   41,   44,  256,  258,
  259,   59,   60,   41,   62,   43,   44,   45,  166,  167,
  148,  269,   42,   62,  256,   93,  258,   47,   43,  278,
   45,   59,   60,   41,   62,   43,   44,   45,  256,  257,
  258,  259,  257,  258,  259,   93,   59,   44,   43,  148,
   45,   59,   60,   41,   62,   43,   44,   45,    8,  207,
   59,  100,   59,  102,  282,   93,   59,  282,   43,   19,
   45,   59,   60,   40,   62,  257,  257,  257,   93,   46,
   41,   42,   43,   44,   45,   93,   47,   42,   43,  270,
   45,  239,   47,  275,   61,   43,  256,   45,   93,  256,
  183,   44,  283,  260,   59,   93,  270,   41,   40,  148,
   44,  257,   60,  257,   62,   41,  260,  260,   44,  276,
  257,  258,  259,   59,   91,  257,   59,  262,  271,  262,
  257,  214,  276,  276,  256,  257,  258,  259,  270,  258,
  259,  263,  264,  265,  266,  282,  268,  269,  256,  257,
  257,  258,  259,  270,  261,  257,  258,  259,  280,  256,
  282,  256,  257,  258,  259,  270,   59,  256,  263,  264,
  265,  266,  256,  268,  269,  282,  256,  256,  283,  271,
  282,   40,  257,  258,  259,  280,   47,  282,  256,  257,
  258,  259,   59,  256,   55,  263,  264,  265,  266,  256,
  268,  269,  257,  258,  259,  256,  257,  282,  256,  257,
  258,  259,  280,  257,  282,  263,  264,  265,  266,  256,
  268,  269,  257,  258,  259,  256,  257,  282,  256,  257,
  258,  259,  280,   61,  282,  263,  264,  265,  266,   40,
  268,  269,  257,  258,  259,  256,  257,  282,  256,  257,
  258,  259,  280,   82,  282,  263,  264,  265,  266,   40,
  268,  269,  257,  258,  259,   59,   59,  282,  256,  257,
  258,  259,  280,   59,  282,  263,  264,  265,  266,   59,
  268,  269,  257,  258,  259,  136,  137,  282,   92,   93,
   84,  120,  280,  122,  282,  280,  257,  258,  259,  280,
    8,  256,  257,  258,  259,  166,  167,  282,  257,  257,
  258,  259,  271,  268,  269,  263,  264,  265,  266,   59,
  256,  282,   59,  256,   68,  280,   40,  282,   72,   73,
  157,  158,  268,  269,  282,  268,  269,   41,   82,  256,
  257,  258,  259,   41,  280,  174,  207,  280,   56,  178,
  108,   41,  271,  278,  112,  256,  257,  258,  259,  117,
   59,  119,  257,  257,  278,  282,  256,  257,  258,  259,
  128,  257,  270,   41,  260,  260,   40,   44,  239,  208,
  209,  282,  279,  127,   92,   93,  271,  279,  274,  270,
  276,  276,  282,  271,   91,  281,  154,  155,   70,  279,
  229,  230,   74,  279,   76,  149,  270,  151,  152,  256,
  257,   41,   93,  271,  243,  244,  271,  258,  212,  177,
  267,  165,  270,  270,  270,  272,  273,   59,  136,  137,
  277,  189,  256,  257,  271,   59,  194,  195,  232,   59,
  256,  257,   41,  267,   41,  271,  204,   10,  272,  273,
  257,  267,   64,  277,  102,  249,  272,  273,  218,   -1,
  267,  277,  253,  270,  217,  272,  273,   -1,   -1,   -1,
  277,  215,   -1,  217,  218,   -1,  234,
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
   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 284
#define YYUNDFTOKEN 337
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
"LOWER_THAN_ELSE","$accept","programa","bloque_declarativo","$$1",
"bloque_ejecutable","lista_declaraciones","declaracion","declaracion_variable",
"declaracion_funcion","declaracion_clase","declaracion_objeto",
"declaracion_comptime","lista_variables","tipo_dato","$$2","lista_parametros",
"$$3","$$4","parametro","codigo_clase","$$5","encabezado_clase",
"miembros_clase","lista_clase","miembro","lista_ejecutables","sentencia",
"asignacion","if_sentencia","iteracion","impresion","sentencia_retorno",
"expresion_aritmetica","destino","$$6","termino","operando","parametros_reales",
"orden_evaluacion","constante","lista_enteros","lista_parametros_reales",
"parametro_real","condicion","bloque_o_sentencia","$$7","fin_if","rama_else",
"$$8","encabezado_iteracion","cuerpo_iteracion","operador_relacional",
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : programa",
"$$1 :",
"programa : ID $$1 bloque_declarativo BEGIN bloque_ejecutable END ';'",
"programa : error bloque_declarativo BEGIN bloque_ejecutable END ';'",
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
"$$2 :",
"declaracion_objeto : ID $$2 lista_variables",
"$$3 :",
"declaracion_funcion : tipo_dato FUNCTION ID '(' lista_parametros ')' $$3 bloque_declarativo BEGIN bloque_ejecutable END",
"$$4 :",
"declaracion_funcion : tipo_dato ID '(' lista_parametros ')' $$4 BEGIN bloque_ejecutable END",
"declaracion_funcion : tipo_dato FUNCTION error '(' lista_parametros ')' bloque_declarativo BEGIN bloque_ejecutable END",
"lista_parametros : lista_parametros ',' parametro",
"lista_parametros : lista_parametros error parametro",
"lista_parametros : parametro",
"parametro : tipo_dato ID",
"parametro : tipo_dato error",
"parametro : error ID",
"$$5 :",
"declaracion_clase : CLASS ID $$5 codigo_clase encabezado_clase miembros_clase END",
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
"bloque_ejecutable : lista_ejecutables",
"bloque_ejecutable :",
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
"$$6 :",
"asignacion : destino ASSIGN $$6 expresion_aritmetica",
"asignacion : destino '=' expresion_aritmetica",
"destino : ID",
"destino : ID '.' ID",
"destino : ID '[' expresion_aritmetica ']'",
"expresion_aritmetica : expresion_aritmetica '+' termino",
"expresion_aritmetica : expresion_aritmetica '-' termino",
"expresion_aritmetica : termino",
"expresion_aritmetica : expresion_aritmetica '+' error",
"expresion_aritmetica : expresion_aritmetica '-' error",
"expresion_aritmetica : expresion_aritmetica termino",
"termino : termino '*' operando",
"termino : termino '/' operando",
"termino : operando",
"termino : termino '*' error",
"termino : termino '/' error",
"operando : ID",
"operando : ID '.' ID",
"operando : ID '[' expresion_aritmetica ']'",
"operando : ID '(' parametros_reales ')' orden_evaluacion",
"operando : ID '.' ID '(' parametros_reales ')' orden_evaluacion",
"operando : TOSF '(' expresion_aritmetica ')'",
"operando : constante",
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
"constante : CTE",
"constante : CTE_FLOAT",
"$$7 :",
"if_sentencia : IF '(' condicion ')' $$7 bloque_o_sentencia fin_if",
"if_sentencia : IF error condicion ')' bloque_o_sentencia fin_if",
"if_sentencia : IF '(' condicion error bloque_o_sentencia fin_if",
"fin_if : rama_else END_IF",
"fin_if : rama_else error",
"fin_if : error",
"$$8 :",
"rama_else : ELSE $$8 bloque_o_sentencia",
"iteracion : encabezado_iteracion cuerpo_iteracion REPEAT",
"iteracion : encabezado_iteracion error REPEAT",
"encabezado_iteracion : FROM ID '=' constante TO constante BY constante",
"encabezado_iteracion : FROM error '=' constante TO constante BY constante",
"encabezado_iteracion : destino '=' constante TO constante BY constante",
"encabezado_iteracion : FROM ID '=' constante constante BY constante",
"encabezado_iteracion : FROM '(' condicion ')'",
"encabezado_iteracion : FROM error condicion ')'",
"encabezado_iteracion : FROM '(' condicion error",
"cuerpo_iteracion : bloque_o_sentencia",
"bloque_o_sentencia : BEGIN bloque_ejecutable END",
"bloque_o_sentencia : sentencia",
"condicion : expresion_aritmetica operador_relacional expresion_aritmetica",
"operador_relacional : '<'",
"operador_relacional : '>'",
"operador_relacional : GE",
"operador_relacional : LE",
"operador_relacional : EQ",
"operador_relacional : NE",
"impresion : POUT '(' expresion_aritmetica ')'",
"impresion : POUT '(' MULT_STRING ')'",
"impresion : POUT '(' ')'",
"impresion : POUT error",

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
#line 29 "gramatica.y"
	{ printf("[SINT] Estructura Programa, en línea %d\n", yylineno); }
#line 1447 "y.tab.c"
break;
case 2:
#line 30 "gramatica.y"
	{ printf("Sintaxis correcta: Programa reconocido con éxito.\n"); }
#line 1452 "y.tab.c"
break;
case 3:
#line 32 "gramatica.y"
	{ yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
#line 1457 "y.tab.c"
break;
case 14:
#line 56 "gramatica.y"
	{ yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
#line 1462 "y.tab.c"
break;
case 19:
#line 70 "gramatica.y"
	{ printf("[SINT] Estructura Variable, en línea %d\n", yylineno); }
#line 1467 "y.tab.c"
break;
case 20:
#line 74 "gramatica.y"
	{ printf("[SINT] Estructura Objeto, en línea %d\n", yylineno); }
#line 1472 "y.tab.c"
break;
case 22:
#line 78 "gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1477 "y.tab.c"
break;
case 24:
#line 79 "gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1482 "y.tab.c"
break;
case 26:
#line 81 "gramatica.y"
	{ yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
#line 1487 "y.tab.c"
break;
case 28:
#line 86 "gramatica.y"
	{ yyerror("Error: Falta de “,” en declaración de variables."); yyerrok; }
#line 1492 "y.tab.c"
break;
case 31:
#line 93 "gramatica.y"
	{ yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
#line 1497 "y.tab.c"
break;
case 32:
#line 95 "gramatica.y"
	{ yyerror("Error: Falta el tipo del parámetro formal en la función."); yyerrok; }
#line 1502 "y.tab.c"
break;
case 33:
#line 99 "gramatica.y"
	{ printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); }
#line 1507 "y.tab.c"
break;
case 35:
#line 101 "gramatica.y"
	{ yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
#line 1512 "y.tab.c"
break;
case 42:
#line 118 "gramatica.y"
	{ yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
#line 1517 "y.tab.c"
break;
case 51:
#line 140 "gramatica.y"
	{ yyerror("Error: Falta ';' al final de la sentencia o error en sentencia."); yyerrok; }
#line 1522 "y.tab.c"
break;
case 52:
#line 142 "gramatica.y"
	{ yyerror("Error: Falta ';' al final de la sentencia."); yyerrok; }
#line 1527 "y.tab.c"
break;
case 58:
#line 155 "gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1532 "y.tab.c"
break;
case 59:
#line 157 "gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1537 "y.tab.c"
break;
case 60:
#line 161 "gramatica.y"
	{ printf("[SINT] Estructura ASSIGN, en línea %d\n", yylineno); }
#line 1542 "y.tab.c"
break;
case 62:
#line 163 "gramatica.y"
	{ yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
#line 1547 "y.tab.c"
break;
case 69:
#line 177 "gramatica.y"
	{ yyerror("Error: Falta operando en la expresión aritmética."); yyerrok; }
#line 1552 "y.tab.c"
break;
case 70:
#line 179 "gramatica.y"
	{ yyerror("Error: Falta operando en la expresión aritmética."); yyerrok; }
#line 1557 "y.tab.c"
break;
case 71:
#line 181 "gramatica.y"
	{ yyerror("Error: Falta operador en la expresión aritmética."); yyerrok; }
#line 1562 "y.tab.c"
break;
case 75:
#line 189 "gramatica.y"
	{ yyerror("Error: Falta operando en el término de la expresión."); yyerrok; }
#line 1567 "y.tab.c"
break;
case 76:
#line 191 "gramatica.y"
	{ yyerror("Error: Falta operando en el término de la expresión."); yyerrok; }
#line 1572 "y.tab.c"
break;
case 85:
#line 207 "gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 1577 "y.tab.c"
break;
case 97:
#line 237 "gramatica.y"
	{ printf("[SINT] Estructura IF, en línea %d\n", yylineno); }
#line 1582 "y.tab.c"
break;
case 99:
#line 239 "gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
#line 1587 "y.tab.c"
break;
case 100:
#line 241 "gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
#line 1592 "y.tab.c"
break;
case 102:
#line 246 "gramatica.y"
	{ yyerror("Error: Falta de end_if."); yyerrok; }
#line 1597 "y.tab.c"
break;
case 103:
#line 247 "gramatica.y"
	{ yyerror("Error: Falta de end_if."); yyerrok; }
#line 1602 "y.tab.c"
break;
case 104:
#line 251 "gramatica.y"
	{ printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); }
#line 1607 "y.tab.c"
break;
case 107:
#line 257 "gramatica.y"
	{ yyerror("Error: Falta el cuerpo en la iteración."); yyerrok; }
#line 1612 "y.tab.c"
break;
case 109:
#line 263 "gramatica.y"
	{ yyerror("Error: Falta identificador (ID) en el encabezado de la iteración."); yyerrok; }
#line 1617 "y.tab.c"
break;
case 110:
#line 265 "gramatica.y"
	{ yyerror("Error: Falta palabra clave 'FROM' en el encabezado de la iteración."); yyerrok; }
#line 1622 "y.tab.c"
break;
case 111:
#line 267 "gramatica.y"
	{ yyerror("Error: Falta 'TO' o constante en el encabezado de la iteración."); yyerrok; }
#line 1627 "y.tab.c"
break;
case 113:
#line 270 "gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
#line 1632 "y.tab.c"
break;
case 114:
#line 272 "gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
#line 1637 "y.tab.c"
break;
case 125:
#line 299 "gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1642 "y.tab.c"
break;
case 126:
#line 301 "gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1647 "y.tab.c"
break;
case 127:
#line 303 "gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1652 "y.tab.c"
break;
case 128:
#line 305 "gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1657 "y.tab.c"
break;
#line 1659 "y.tab.c"
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
