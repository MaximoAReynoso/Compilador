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
    9,   15,    7,   16,    7,    7,   14,   14,   17,   17,
   17,   19,    8,    8,   18,   18,   20,   20,   21,   21,
   22,   22,    3,    3,   23,   23,   23,   23,   24,   24,
   24,   24,   24,   29,   29,   32,   25,   25,   31,   31,
   31,   30,   30,   30,   30,   30,   33,   33,   33,   33,
   33,   34,   34,   34,   34,   34,   34,   34,   36,   36,
   36,   38,   38,   35,   35,   39,   39,   40,   40,   37,
   37,   43,   26,   26,   26,   45,   44,   44,   27,   27,
   46,   46,   46,   46,   46,   46,   46,   47,   42,   42,
   41,   48,   48,   48,   48,   48,   48,   28,   28,
};
static const YYINT yylen[] = {                            2,
    0,    7,    6,    1,    0,    2,    1,    2,    2,    2,
    2,    2,    2,    2,    1,    1,    2,    3,    1,    0,
    3,    0,   11,    0,    9,   10,    3,    1,    2,    2,
    2,    0,    7,    6,    1,    0,    1,    0,    2,    1,
    2,    2,    1,    0,    3,    2,    3,    2,    1,    1,
    1,    1,    1,    4,    3,    0,    4,    3,    1,    3,
    4,    3,    3,    1,    3,    3,    3,    3,    1,    3,
    3,    1,    3,    4,    5,    7,    4,    1,    3,    3,
    0,    3,    1,    1,    0,    3,    1,    1,    3,    1,
    1,    0,    8,    7,    7,    0,    3,    0,    3,    3,
    8,    8,    7,    7,    4,    4,    4,    1,    3,    1,
    3,    1,    1,    1,    1,    1,    1,    4,    4,
};
static const YYINT yydefred[] = {                         0,
    0,    1,    0,   20,   15,    0,   16,    0,    0,    0,
    7,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   19,   13,    0,    0,    0,    6,    8,    9,   10,   11,
   12,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   49,   50,
   51,   52,   53,    0,    0,    0,    0,    0,    0,   37,
    0,   35,    0,   18,   48,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   46,   56,    0,
    0,    0,  110,  108,    0,    0,    0,    0,   28,    0,
    0,    0,    0,    0,    0,   40,    0,   60,    0,   90,
   91,    0,    0,    0,   69,   78,    0,    0,    0,    0,
    0,   55,    0,    0,    0,    0,    0,    3,   47,   45,
    0,    0,    0,  100,    0,   99,   31,   30,   29,    0,
   24,    0,    0,    0,   41,   42,   34,   39,    0,    0,
    0,    0,    0,   61,    0,    0,    0,    0,  114,  115,
  116,  117,  112,  113,    0,    0,    0,   92,  119,  118,
   54,    0,  106,    0,  107,  105,    0,    0,  109,   27,
    0,    0,   22,    2,   33,    0,    0,    0,    0,   87,
    0,    0,    0,   65,    0,   66,    0,   70,   67,   71,
   68,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   74,   77,   96,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   75,   86,    0,    0,   94,   95,    0,    0,    0,
  104,  103,   25,    0,    0,    0,   83,    0,    0,   97,
   93,  102,  101,   26,    0,   80,    0,   79,   76,   23,
   82,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  256,  257,  286,  257,  260,  274,  276,  281,  287,  290,
  291,  292,  293,  294,  295,  296,  298,  288,  299,  257,
  257,  292,  297,  298,  270,  291,   59,   59,   59,   59,
   59,  257,  275,  297,  287,  297,  256,  305,   44,  256,
  257,  267,  272,  273,  277,  289,  309,  310,  311,  312,
  313,  314,  315,  317,  332,   40,  256,  257,  270,  270,
  306,  257,  304,  257,   59,   46,   91,  256,   40,   40,
   40,  256,  257,   40,  271,  256,  310,   59,  262,   61,
  256,  270,  310,  328,  333,  256,  298,  300,  303,   40,
   40,  289,  292,  293,  307,  308,  306,  257,  257,  258,
  259,  282,  316,  319,  320,  323,  316,  327,  327,  261,
  316,   41,  316,   61,  327,   61,  327,   59,   59,   59,
  318,  316,  323,  280,  289,  280,  257,  256,  257,   44,
   41,  300,  300,  271,   59,   59,  271,  308,  307,   40,
   46,   91,   40,   93,   43,   45,   42,   47,  263,  264,
  265,  266,   60,   62,  334,   41,  256,   41,   41,   41,
   41,  323,   41,  323,  256,   41,  316,  278,  271,  303,
  302,   41,   41,   59,  271,  257,  316,  321,  325,  326,
  257,  316,  316,  256,  319,  256,  319,  256,  320,  256,
  320,  316,  328,  328,  329,  278,  278,  323,  323,  270,
  287,  301,   61,   41,   44,   40,   93,   41,  268,  330,
  330,  328,  323,  323,  279,  279,  289,  270,  287,  316,
   91,  322,  326,  321,  331,  269,  269,  330,  279,  279,
  323,  323,  271,  289,  270,  256,  258,  324,   41,  328,
  269,  323,  323,  271,  289,   93,   44,   93,  322,  271,
  258,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          3,
    9,   18,   46,   10,   11,   12,   13,   14,   15,   16,
   34,   17,   19,   88,  202,  171,   89,   63,   38,   61,
   95,   96,   47,   48,   49,   50,   51,   52,   53,  107,
   54,  121,  104,  105,  178,  222,  106,  238,  179,  180,
  108,   84,  195,  210,  225,   55,   85,  155,
};
static const YYINT yysindex[] = {                      -152,
  -77,    0,    0,    0,    0, -238,    0,  -66, -231,  -77,
    0,   36,   83,  111,  122,  127, -103,  -77, -179,  -63,
    0,    0,  158, -179,   85,    0,    0,    0,    0,    0,
    0,  168,  -17,  158,  -24,  158,   -9,   33,   61,  248,
  -29,   -8,  282,  287,  -19,   58,   87,  276,    0,    0,
    0,    0,    0,  -59,   53, -162,  300,  307,   85,    0,
 -196,    0,   -9,    0,    0,   98, -100, -100, -100,  -90,
  -41,  -52,  302, -100,  317,  325,  326,    0,    0, -100,
   81,   85,    0,    0,  107,  134,   24,   88,    0, -162,
 -162,  121,  335,  336,  -51,    0, -196,    0,   -5,    0,
    0,  356,   40,  132,    0,    0,  -42,  357,   -3,  358,
  144,    0,  170,   80,  361,   80,    1,    0,    0,    0,
 -100,  225,  119,    0,  133,    0,    0,    0,    0, -162,
    0,   99,  219,  344,    0,    0,    0,    0,    7,  -81,
  148, -100, -100,    0, -134, -122, -107,  -94,    0,    0,
    0,    0,    0,    0, -100,  116,  116,    0,    0,    0,
    0,  128,    0, -139,    0,    0,  225,   80,    0,    0,
  137,  -77,    0,    0,    0,   35,  225,  367,  365,    0,
  370,   54,  329,    0,  132,    0,  132,    0,    0,    0,
    0,  225,  143,  143,  116,   80,   80,  138,  139,   85,
  142,  -77, -100,  322,  -81,  -81,    0,    0,    0,  147,
  150,  143,  141,  145,   80,   80,  151,   85,  153,  225,
   63,    0,    0,  380,  116,    0,    0,  156,   80,   80,
    0,    0,    0,  155,   85,  334,    0,   13,  322,    0,
    0,    0,    0,    0,  157,    0,  171,    0,    0,    0,
    0,
};
static const YYINT yyrindex[] = {                         0,
  160,    0,    0,    0,    0,    0,    0,    0,    0,  161,
    0,    0,    0,    0,    0,    0,    0,  160,    0,   -1,
    0,    0,  373,    0,  162,    0,    0,    0,    0,    0,
    0,   94,    0,  375,    0,  376, -145,   19,    0,    0,
  -50,    0,    0,    0,    0,    0,  165,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  162,    0,
    0,    0, -145,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  162,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -37,    0,
    0,    0,    0,   28,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -35,   18,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  396,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -33,    0,    0,    0,
    0,  160,    0,    0,    0,  324,  241,    0,  398,    0,
  -14,    0,    0,    0,   48,    0,   68,    0,    0,    0,
    0,    2,  173,  173,    0,    0,    0,    0,    0,  162,
    0,  160,    0,    8,    0,  396,    0,    0,    0,    0,
    0,  173,    0,    0,    0,    0,    0,  162,    0,  259,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  162,    0,    0,    0,    8,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,
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
    0,
};
#endif
static const YYINT yygindex[] = {                         0,
   -6,    0,  -45,    0,  433,    5,  -21,    0,    0,    0,
   39,   26,    0,  255,    0,    0,  314,    0,    0,  382,
  349,  -36,    0,  -11,    0,    0,    0,    0,    0,  235,
    0,    0,  205,  232,  242,  208,  185,    0,    0,  244,
  126, -141,    0,   50,    0,    0,    0,    0,
};
#define YYTABLESIZE 449
static const YYINT yytable[] = {                        112,
  145,   80,  146,   72,   72,   72,   72,   72,  114,   72,
   59,   35,   22,   92,  193,  194,   66,  153,   20,  154,
   74,   72,   72,   58,   72,   57,   73,   73,   73,   73,
   73,   69,   73,   24,  140,   77,  125,  158,   25,   94,
  141,  166,  111,   83,   73,   73,   23,   73,   81,   81,
   81,   81,   81,  212,   81,   72,  247,   36,  138,   78,
   78,   67,   78,    5,   78,   93,   81,   81,   64,   81,
   64,   64,   64,   94,  140,   94,   78,   21,   73,    7,
  141,   87,  145,  240,  146,  142,   64,   64,   62,   64,
   62,   62,   62,   86,   27,  203,  145,    5,  146,   93,
   81,   93,  138,    1,    2,  248,   62,   62,   63,   62,
   63,   63,   63,    7,   38,   87,   87,   94,  100,  101,
   64,  184,   99,  100,  101,  142,   63,   63,  131,   63,
   38,  130,  144,  186,   99,  100,  101,   19,  197,  172,
   62,   28,  130,   93,   83,   83,  207,  102,  188,   99,
  100,  101,   19,   32,  217,   87,   99,  100,  101,  102,
   63,  190,   99,  100,  101,  201,   99,  100,  101,   29,
  110,   33,  234,  147,  102,  176,  100,  101,  148,    4,
   30,  102,    5,   83,  160,   31,  145,  102,  146,  245,
   21,  102,   37,    5,  109,  219,    6,  115,    7,  117,
  102,   39,   79,    8,   99,  100,  101,   56,    5,    7,
  161,   59,  145,   83,  146,   99,  100,  101,   72,  137,
  149,  150,  151,  152,    7,   72,   72,   72,   72,  102,
   72,   72,   58,   58,   57,   57,   72,   73,   57,   58,
  102,   73,   72,  211,   58,   59,   57,   68,   73,   73,
   73,   73,  157,   73,   73,   32,  165,  111,   32,  173,
   60,  228,  130,   81,  123,   73,    5,  145,   32,  146,
   81,   81,   81,   81,   32,   81,   81,  175,   36,  128,
  129,   88,    7,   64,   88,   78,   78,   81,   36,   62,
   64,   64,   64,   64,   36,   64,   64,   78,  162,   89,
  164,  103,   89,   62,  111,  113,   65,   64,   81,   41,
   62,   62,   62,   62,  122,   62,   62,   64,  236,   42,
  237,   70,   82,   63,   43,   44,   71,   62,   75,   45,
   63,   63,   63,   63,   78,   63,   63,  100,  101,   90,
   40,   41,   76,   41,  132,  133,   91,   63,  198,  185,
  187,   42,  199,   42,   98,  167,   43,   44,   43,   44,
  124,   45,  116,   45,   72,   72,   72,   72,   72,  208,
   72,  145,   41,  146,  177,  118,  182,  183,  189,  191,
  213,  214,   42,  119,  120,   82,  126,   43,   44,  192,
  127,  134,   45,  135,  136,  143,  168,  156,  159,  231,
  232,  163,  174,  169,  181,  196,  200,  204,  205,  206,
  209,  218,  221,  242,  243,  226,  215,  216,  227,  229,
  239,  233,  235,  230,  241,  244,  246,  250,  251,    5,
    4,   14,   44,   17,   21,   43,   85,  220,   84,  177,
  177,   98,   26,  170,   97,  139,  249,  224,  223,
};
static const YYINT yycheck[] = {                         41,
   43,   61,   45,   41,   42,   43,   44,   45,   61,   47,
   61,   18,    8,   59,  156,  157,   46,   60,  257,   62,
   40,   59,   60,   59,   62,   59,   41,   42,   43,   44,
   45,   40,   47,    8,   40,   47,   82,   41,  270,   61,
   46,   41,   41,   55,   59,   60,    8,   62,   41,   42,
   43,   44,   45,  195,   47,   93,   44,   19,   95,   42,
   43,   91,   45,  260,   47,   61,   59,   60,   41,   62,
   43,   44,   45,   95,   40,   97,   59,  257,   93,  276,
   46,   56,   43,  225,   45,   91,   59,   60,   41,   62,
   43,   44,   45,  256,   59,   61,   43,  260,   45,   95,
   93,   97,  139,  256,  257,   93,   59,   60,   41,   62,
   43,   44,   45,  276,  260,   90,   91,  139,  258,  259,
   93,  256,  257,  258,  259,   91,   59,   60,   41,   62,
  276,   44,   93,  256,  257,  258,  259,   44,  278,   41,
   93,   59,   44,  139,  156,  157,   93,  282,  256,  257,
  258,  259,   59,  257,  200,  130,  257,  258,  259,  282,
   93,  256,  257,  258,  259,  172,  257,  258,  259,   59,
  261,  275,  218,   42,  282,  257,  258,  259,   47,  257,
   59,  282,  260,  195,   41,   59,   43,  282,   45,  235,
  257,  282,  256,  260,   69,  202,  274,   72,  276,   74,
  282,   44,  262,  281,  257,  258,  259,   40,  260,  276,
   41,  262,   43,  225,   45,  257,  258,  259,  256,  271,
  263,  264,  265,  266,  276,  263,  264,  265,  266,  282,
  268,  269,  268,  269,  268,  269,  256,  257,  256,  257,
  282,  256,  280,  194,  280,  270,  280,  256,  263,  264,
  265,  266,  256,  268,  269,  257,  256,  256,  260,   41,
  270,  212,   44,  256,   80,  280,  260,   43,  270,   45,
  263,  264,  265,  266,  276,  268,  269,  271,  260,  256,
  257,   41,  276,  256,   44,  268,  269,  280,  270,  257,
  263,  264,  265,  266,  276,  268,  269,  280,  114,   41,
  116,   67,   44,  256,   70,   71,   59,  280,  256,  257,
  263,  264,  265,  266,   80,  268,  269,  257,  256,  267,
  258,   40,  270,  256,  272,  273,   40,  280,  271,  277,
  263,  264,  265,  266,   59,  268,  269,  258,  259,   40,
  256,  257,  256,  257,   90,   91,   40,  280,  164,  145,
  146,  267,  168,  267,  257,  121,  272,  273,  272,  273,
  280,  277,   61,  277,   41,   42,   43,   44,   45,   41,
   47,   43,  257,   45,  140,   59,  142,  143,  147,  148,
  196,  197,  267,   59,   59,  270,  280,  272,  273,  155,
  257,  271,  277,   59,   59,   40,  278,   41,   41,  215,
  216,   41,   59,  271,  257,  278,  270,   41,   44,   40,
  268,  270,   91,  229,  230,  269,  279,  279,  269,  279,
   41,  271,  270,  279,  269,  271,   93,  271,  258,  270,
  270,   59,  271,   59,   59,  271,   41,  203,   41,  205,
  206,  269,   10,  130,   63,   97,  239,  206,  205,
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
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 284
#define YYUNDFTOKEN 335
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
"miembros_clase","miembro","lista_ejecutables","sentencia","asignacion",
"if_sentencia","iteracion","impresion","sentencia_retorno",
"expresion_aritmetica","destino","$$6","termino","operando","parametros_reales",
"orden_evaluacion","constante","lista_enteros","lista_parametros_reales",
"parametro_real","condicion","bloque_o_sentencia","$$7","rama_else","$$8",
"encabezado_iteracion","cuerpo_iteracion","operador_relacional",
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
"lista_parametros : parametro",
"parametro : tipo_dato ID",
"parametro : tipo_dato error",
"parametro : error ID",
"$$5 :",
"declaracion_clase : CLASS ID $$5 codigo_clase encabezado_clase miembros_clase END",
"declaracion_clase : CLASS ID error encabezado_clase miembros_clase END",
"codigo_clase : ID",
"codigo_clase :",
"encabezado_clase : BEGIN",
"encabezado_clase :",
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
"if_sentencia : IF '(' condicion ')' $$7 bloque_o_sentencia rama_else END_IF",
"if_sentencia : IF error condicion ')' bloque_o_sentencia rama_else END_IF",
"if_sentencia : IF '(' condicion error bloque_o_sentencia rama_else END_IF",
"$$8 :",
"rama_else : ELSE $$8 bloque_o_sentencia",
"rama_else :",
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
#line 1398 "y.tab.c"
break;
case 2:
#line 30 "gramatica.y"
	{ printf("Sintaxis correcta: Programa reconocido con éxito.\n"); }
#line 1403 "y.tab.c"
break;
case 3:
#line 32 "gramatica.y"
	{ yyerror("Error sintáctico: Falta el nombre del programa al inicio."); yyerrok; }
#line 1408 "y.tab.c"
break;
case 14:
#line 56 "gramatica.y"
	{ yyerror("Error sintáctico: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
#line 1413 "y.tab.c"
break;
case 19:
#line 70 "gramatica.y"
	{ printf("[SINT] Estructura Variable, en línea %d\n", yylineno); }
#line 1418 "y.tab.c"
break;
case 20:
#line 74 "gramatica.y"
	{ printf("[SINT] Estructura Objeto, en línea %d\n", yylineno); }
#line 1423 "y.tab.c"
break;
case 22:
#line 78 "gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1428 "y.tab.c"
break;
case 24:
#line 79 "gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1433 "y.tab.c"
break;
case 26:
#line 81 "gramatica.y"
	{ yyerror("Error sintáctico: Falta el nombre (identificador) de la función."); yyerrok; }
#line 1438 "y.tab.c"
break;
case 30:
#line 92 "gramatica.y"
	{ yyerror("Error sintáctico: Falta el nombre del parámetro formal en la función."); yyerrok; }
#line 1443 "y.tab.c"
break;
case 31:
#line 94 "gramatica.y"
	{ yyerror("Error sintáctico: Falta el tipo del parámetro formal en la función."); yyerrok; }
#line 1448 "y.tab.c"
break;
case 32:
#line 98 "gramatica.y"
	{ printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); }
#line 1453 "y.tab.c"
break;
case 34:
#line 100 "gramatica.y"
	{ yyerror("Error sintáctico: Ausencia del código en la declaración de la clase."); yyerrok; }
#line 1458 "y.tab.c"
break;
case 47:
#line 132 "gramatica.y"
	{ yyerror("Error sintáctico: Falta ';' al final de la sentencia o error en sentencia."); yyerrok; }
#line 1463 "y.tab.c"
break;
case 48:
#line 134 "gramatica.y"
	{ yyerror("Error sintáctico: Falta ';' al final de la sentencia."); yyerrok; }
#line 1468 "y.tab.c"
break;
case 54:
#line 147 "gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1473 "y.tab.c"
break;
case 55:
#line 149 "gramatica.y"
	{ printf("Estructura RET, en línea %d\n", yylineno); }
#line 1478 "y.tab.c"
break;
case 56:
#line 153 "gramatica.y"
	{ printf("[SINT] Estructura ASSIGN, en línea %d\n", yylineno); }
#line 1483 "y.tab.c"
break;
case 58:
#line 155 "gramatica.y"
	{ yyerror("Error sintáctico: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
#line 1488 "y.tab.c"
break;
case 65:
#line 169 "gramatica.y"
	{ yyerror("Error sintáctico: Falta operando en la expresión aritmética."); yyerrok; }
#line 1493 "y.tab.c"
break;
case 66:
#line 171 "gramatica.y"
	{ yyerror("Error sintáctico: Falta operando en la expresión aritmética."); yyerrok; }
#line 1498 "y.tab.c"
break;
case 70:
#line 179 "gramatica.y"
	{ yyerror("Error sintáctico: Falta operando en el término de la expresión."); yyerrok; }
#line 1503 "y.tab.c"
break;
case 71:
#line 181 "gramatica.y"
	{ yyerror("Error sintáctico: Falta operando en el término de la expresión."); yyerrok; }
#line 1508 "y.tab.c"
break;
case 80:
#line 197 "gramatica.y"
	{ yyerror("Error sintáctico: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 1513 "y.tab.c"
break;
case 92:
#line 227 "gramatica.y"
	{ printf("[SINT] Estructura IF, en línea %d\n", yylineno); }
#line 1518 "y.tab.c"
break;
case 94:
#line 229 "gramatica.y"
	{ yyerror("Error sintáctico: Falta '(' en la condición de selección."); yyerrok; }
#line 1523 "y.tab.c"
break;
case 95:
#line 231 "gramatica.y"
	{ yyerror("Error sintáctico: Falta ')' en la condición de selección."); yyerrok; }
#line 1528 "y.tab.c"
break;
case 96:
#line 235 "gramatica.y"
	{ printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); }
#line 1533 "y.tab.c"
break;
case 100:
#line 242 "gramatica.y"
	{ yyerror("Error sintáctico: Falta el cuerpo en la iteración."); yyerrok; }
#line 1538 "y.tab.c"
break;
case 102:
#line 248 "gramatica.y"
	{ yyerror("Error sintáctico: Falta identificador (ID) en el encabezado de la iteración."); yyerrok; }
#line 1543 "y.tab.c"
break;
case 103:
#line 250 "gramatica.y"
	{ yyerror("Error sintáctico: Falta palabra clave 'FROM' en el encabezado de la iteración."); yyerrok; }
#line 1548 "y.tab.c"
break;
case 104:
#line 252 "gramatica.y"
	{ yyerror("Error sintáctico: Falta 'TO' o constante en el encabezado de la iteración."); yyerrok; }
#line 1553 "y.tab.c"
break;
case 106:
#line 255 "gramatica.y"
	{ yyerror("Error sintáctico: Falta '(' en la condición de la iteración."); yyerrok; }
#line 1558 "y.tab.c"
break;
case 107:
#line 257 "gramatica.y"
	{ yyerror("Error sintáctico: Falta ')' en la condición de la iteración."); yyerrok; }
#line 1563 "y.tab.c"
break;
case 118:
#line 284 "gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1568 "y.tab.c"
break;
case 119:
#line 286 "gramatica.y"
	{ printf("Estructura POUT, en línea %d\n", yylineno); }
#line 1573 "y.tab.c"
break;
#line 1575 "y.tab.c"
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
