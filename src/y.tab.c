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
   20,   20,   21,   21,   23,   23,    3,    3,   25,   24,
   24,   24,   24,   26,   26,   26,   26,   26,   31,   31,
   34,   27,   27,   33,   33,   33,   32,   32,   32,   32,
   32,   32,   35,   35,   35,   35,   35,   36,   36,   36,
   36,   36,   36,   36,   38,   38,   38,   40,   40,   37,
   37,   41,   41,   42,   42,   39,   39,   45,   28,   28,
   28,   46,   46,   46,   48,   47,   29,   29,   49,   49,
   49,   49,   49,   49,   49,   50,   44,   44,   43,   51,
   51,   51,   51,   51,   51,   30,   30,   30,   30,
};
static const YYINT yylen[] = {                            2,
    0,    5,    4,    1,    0,    2,    1,    2,    2,    2,
    2,    2,    2,    2,    1,    1,    2,    3,    1,    0,
    3,    0,    9,    0,    7,    8,    3,    3,    1,    2,
    2,    2,    0,    7,    6,    1,    0,    3,    1,    1,
    3,    2,    2,    1,    2,    2,    3,    3,    1,    3,
    2,    3,    2,    1,    1,    1,    1,    1,    4,    3,
    0,    4,    3,    1,    3,    4,    3,    3,    1,    3,
    3,    2,    3,    3,    1,    3,    3,    1,    3,    4,
    5,    7,    4,    1,    3,    3,    0,    3,    1,    1,
    0,    3,    1,    1,    3,    1,    1,    0,    7,    6,
    6,    2,    2,    1,    0,    3,    3,    3,    8,    8,
    7,    7,    4,    4,    4,    1,    1,    1,    3,    1,
    1,    1,    1,    1,    1,    4,    4,    3,    2,
};
static const YYINT yydefred[] = {                         0,
    0,    1,    0,   20,   15,    0,   16,    0,    0,    0,
    7,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   19,   13,    0,    0,    0,    0,    0,    6,    8,    9,
   10,   11,   12,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   54,
   55,   56,   57,   58,    0,    0,    0,    3,    0,    0,
    0,    0,   40,    0,    0,   36,    0,   18,   53,    0,
    0,    0,    0,  129,    0,    0,    0,    0,    0,    0,
   49,   48,    0,   51,   61,    0,    0,  117,  118,  116,
    0,   47,    0,    0,    0,   29,    0,    0,    2,   39,
   42,    0,    0,    0,    0,   44,    0,   65,    0,   96,
   97,    0,    0,    0,   75,   84,    0,    0,    0,    0,
  128,    0,   60,    0,    0,    0,    0,    0,   52,   50,
    0,    0,    0,  108,  107,   32,   31,   30,    0,    0,
   24,    0,    0,   41,    0,   45,   46,   35,   43,    0,
    0,    0,    0,    0,   66,    0,    0,    0,    0,    0,
  122,  123,  124,  125,  120,  121,    0,    0,    0,   98,
  127,  126,   59,    0,  114,    0,  115,  113,    0,    0,
   28,   27,    0,    0,   22,   38,   34,    0,    0,    0,
    0,   93,    0,    0,    0,   70,    0,   71,    0,   76,
   73,   77,   74,    0,    0,    0,    0,    0,    0,    0,
    0,   25,    0,    0,    0,    0,    0,    0,   80,   83,
  104,  105,  100,    0,  101,    0,    0,    0,    0,    0,
   26,    0,    0,    0,   81,   92,    0,    0,  103,  102,
   99,    0,    0,  112,  111,   23,    0,   89,    0,    0,
  106,  110,  109,   86,    0,   85,   82,   88,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  256,  257,  286,  257,  260,  274,  276,  281,  287,  290,
  291,  292,  293,  294,  295,  296,  298,  288,  299,  257,
  257,  292,  297,  298,  256,  270,  289,  291,   59,   59,
   59,   59,   59,  257,  275,  297,  287,  297,  256,  305,
   44,  256,  257,  267,  272,  273,  277,  310,  312,  313,
  314,  315,  316,  317,  319,  335,  310,   59,   40,  256,
  257,  289,  270,  283,  306,  257,  304,  257,   59,   46,
   91,  256,   40,  256,   40,   40,  256,  257,   40,  256,
  271,  311,  312,   59,  262,   61,  256,  289,  312,  330,
  336,  311,  256,  298,  300,  303,   40,   40,   59,  257,
  270,  308,  292,  293,  307,  309,  306,  257,  257,  258,
  259,  282,  318,  321,  322,  325,  318,  329,  329,  261,
   41,  318,   41,  318,   61,  329,   61,  329,   59,   59,
  320,  318,  325,  280,  280,  257,  256,  257,  256,   44,
   41,  300,  300,  270,   44,   59,   59,  271,  309,  307,
   40,   46,   91,   40,   93,   43,   45,  321,   42,   47,
  263,  264,  265,  266,   60,   62,  337,   41,  256,   41,
   41,   41,   41,  325,   41,  325,  256,   41,  318,  278,
  303,  303,  302,   41,   41,  257,  271,  257,  318,  323,
  327,  328,  257,  318,  318,  256,  321,  256,  321,  256,
  322,  256,  322,  318,  330,  330,  331,  278,  278,  325,
  325,  289,  287,  301,   61,   41,   44,   40,   93,   41,
  256,  268,  332,  333,  332,  330,  325,  325,  279,  279,
  289,  287,  318,   91,  324,  328,  323,  334,  256,  269,
  332,  279,  279,  325,  325,  289,  256,  258,  326,   41,
  330,  325,  325,   93,   44,   93,  324,  258,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          3,
    9,   18,   88,   10,   11,   12,   13,   14,   15,   16,
   36,   17,   19,   95,  214,  183,   96,   67,   40,   65,
  105,  102,  106,   48,   82,   89,   50,   51,   52,   53,
   54,  117,   55,  131,  114,  115,  190,  235,  116,  249,
  191,  192,  118,   90,  207,  223,  224,  238,   56,   91,
  167,
};
static const YYINT yysindex[] = {                      -149,
  201,    0,    0,    0,    0, -157,    0,  -80, -206,  201,
    0,   91,   98,  123,  138,  161, -127,  201,   10, -167,
    0,    0,  216,   10,  303,  303,  235,    0,    0,    0,
    0,    0,    0,  274,  -66,  216, -206,  216,  -95,   63,
   77,  281,   -7,  -27,   -8,  314,    1,  264,  315,    0,
    0,    0,    0,    0,  -52,  272,  264,    0, -190,  346,
  353,  341,    0,  -65, -223,    0,  -95,    0,    0,  153,
 -154, -154, -154,    0,  -26,   46,  -56,  214, -154,  350,
    0,    0,  352,    0,    0, -154,  239,    0,    0,    0,
  139,    0,  163,   30,   18,    0, -190, -190,    0,    0,
    0,  -36,  362,  365,  -62,    0, -223,    0,  -30,    0,
    0,  387,   66,  152,    0,    0,  133,  388,  -16,  390,
    0,  -21,    0,    6,  -12,  391,  -12,   -3,    0,    0,
 -154,  106,  156,    0,    0,    0,    0,    0, -190, -190,
    0,   24,   44,    0,  179,    0,    0,    0,    0,  100,
 -135,  186, -154, -154,    0,  182,  190,  152,  194,  209,
    0,    0,    0,    0,    0,    0, -154,  296,  296,    0,
    0,    0,    0,  166,    0, -168,    0,    0,  106,  -12,
    0,    0, -206,  201,    0,    0,    0,   81,  106,  413,
  411,    0,  417,   86,   26,    0,  152,    0,  152,    0,
    0,    0,    0,  106, -242, -242,  296,  -12,  -12,  180,
  183,    0, -206,  201, -154,  372, -135, -135,    0,    0,
    0,    0,    0,  -48,    0, -242,  192,  195,  -12,  -12,
    0, -206,  106,  131,    0,    0,  432,  296,    0,    0,
    0,  -12,  -12,    0,    0,    0,  393,    0,  -10,  372,
    0,    0,    0,    0,  222,    0,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
 -116,    0,    0,    0,    0,    0,    0,    0,    0, -100,
    0,    0,    0,    0,    0,    0,    0, -116,    0,  -83,
    0,    0,  422,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  101,    0,  425,    0,  428,    0,  -64,
    0,    0,  -50,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -41,    0,
    0,    0,    0,   33,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  145,  126,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  449,    0,    0,    0,    0,    0,    0,   53,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  148,    0,
    0,    0,    0, -116,    0,    0,    0,  120,  326,    0,
  452,    0,  -14,    0,    0,    0,   73,    0,   93,    0,
    0,    0,    0,    3,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -116,    0,   13,    0,  449,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  328,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   13,
    0,    0,    0,    0,    0,    0,    0,    0,
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
    0,    0,    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
   -1,    0,   -2,    0,  484,   34,  -25,    0,    0,    0,
  254,    4,    0,  229,    0,    0,  167,    0,    0,  430,
  392,    0,  -69,  477,  447,  355,    0,    0,    0,    0,
    0,  347,    0,    0,  313,  187,  287,  263,  280,    0,
    0,  298,  406,  -49,    0, -183,    0,    0,    0,    0,
    0,
};
#define YYTABLESIZE 580
static const YYINT yytable[] = {                         78,
   78,   78,   78,   78,  125,   78,   27,  145,   86,  151,
   64,   24,   73,  221,  121,  152,   37,   78,   78,  172,
   78,  156,  225,  157,  170,  222,   79,   79,   79,   79,
   79,   75,   79,  255,   62,  149,    5,  178,   70,  104,
   79,   22,  241,  119,   79,   79,  173,   79,  156,   25,
  157,   78,    7,   87,   87,   87,   87,   87,  141,   87,
  153,  140,   94,   26,  184,   93,  220,  140,  156,    5,
  157,   87,   87,   69,   87,   69,   69,   69,   79,  104,
  149,  104,  256,   71,  185,    7,  123,  140,   39,  110,
  111,   69,   69,   72,   69,   72,   72,   72,  103,   20,
   94,   94,  109,  110,  111,   87,    1,    2,  156,  209,
  157,   72,   72,   67,   72,   67,   67,   67,  205,  206,
  151,  188,  110,  111,  104,   69,  152,  112,  156,   34,
  157,   67,   67,   68,   67,   68,   68,   68,  103,    5,
  103,  215,   94,   94,   19,   72,  112,   35,  156,   29,
  157,   68,   68,    5,   68,    4,   30,  226,  155,   19,
   78,   78,   78,   78,   78,   67,   78,   84,   84,    4,
   84,  153,   84,   33,   63,  156,   21,  157,  219,    5,
  212,   31,  213,  103,   84,   68,   33,   64,  251,   60,
   61,  100,  165,  159,  166,    7,   32,    5,  160,   33,
  109,  110,  111,   63,  101,   37,   62,  239,  148,   85,
  231,   64,  232,    7,   78,   78,   78,   78,   37,   33,
  240,   78,   78,   78,   78,  112,   78,   78,   72,  246,
  109,  110,  111,  144,  120,  109,  110,  111,   78,  169,
   78,   79,   79,   79,   79,  110,  111,   74,   79,   79,
   79,   79,  177,   79,   79,  112,   77,   78,  119,   41,
  112,   23,  109,  110,  111,   79,   21,   79,   87,   87,
   87,   87,   38,  139,  127,   87,   87,   87,   87,  139,
   87,   87,  109,  110,  111,  137,  138,  112,   69,   69,
   69,   69,   87,   58,   87,   69,   69,   69,   69,  139,
   69,   69,  109,  110,  111,  181,  182,  112,   72,   72,
   72,   72,   69,   59,   69,   72,   72,   72,   72,   66,
   72,   72,  109,  110,  111,  142,  143,  112,   67,   67,
   67,   67,   72,   68,   72,   67,   67,   67,   67,   69,
   67,   67,  109,  110,  111,  201,  203,  112,   68,   68,
   68,   68,   67,   76,   67,   68,   68,   68,   68,    5,
   68,   68,  109,  110,  111,  133,   94,  112,   95,   94,
  187,   95,   68,   84,   68,    7,   78,   78,   78,   49,
   49,   84,   84,   84,   84,   97,  247,  112,  248,  109,
  110,  111,   98,   84,   84,  161,  162,  163,  164,   99,
   63,   78,   83,   62,  174,   84,  176,   84,  129,  108,
  130,   83,   63,   63,  112,   62,   62,  113,  135,  136,
  146,  122,  124,  147,   63,  158,  154,   62,  168,  158,
  171,  175,  132,  180,  158,  186,  158,  196,  109,  110,
  111,   49,  193,  208,  158,  198,  109,  110,  111,  200,
  109,  110,  111,  216,  217,  210,  218,    4,  229,  211,
    5,  230,  234,  112,  202,  109,  110,  111,  197,  199,
  242,  112,  250,  243,    6,  112,    7,  179,  119,  258,
   14,    8,  126,   17,  128,  254,   21,  227,  228,   91,
  112,  158,   90,   28,   42,   43,  107,  189,  150,  194,
  195,  158,   57,   92,  237,   44,  158,  158,  244,  245,
   45,   46,  257,  204,  236,   47,  158,    0,  134,   80,
   43,  252,  253,    0,    0,    0,    0,   87,   43,    0,
   44,    0,    0,    0,   81,   45,   46,    0,   44,    0,
   47,   26,    0,   45,   46,  158,    0,    0,   47,    0,
    0,   25,   43,    0,    0,    0,    0,    0,   42,   43,
    0,  233,   44,  189,  189,   26,    0,   45,   46,   44,
    0,    0,   47,    0,   45,   46,    0,    0,    0,   47,
};
static const YYINT yycheck[] = {                         41,
   42,   43,   44,   45,   61,   47,    9,   44,   61,   40,
   61,    8,   40,  256,   41,   46,   18,   59,   60,   41,
   62,   43,  206,   45,   41,  268,   41,   42,   43,   44,
   45,   40,   47,   44,   37,  105,  260,   41,   46,   65,
   40,    8,  226,   41,   59,   60,   41,   62,   43,  256,
   45,   93,  276,   41,   42,   43,   44,   45,   41,   47,
   91,   44,   59,  270,   41,  256,   41,   44,   43,  260,
   45,   59,   60,   41,   62,   43,   44,   45,   93,  105,
  150,  107,   93,   91,   41,  276,   41,   44,  256,  258,
  259,   59,   60,   41,   62,   43,   44,   45,   65,  257,
   97,   98,  257,  258,  259,   93,  256,  257,   43,  278,
   45,   59,   60,   41,   62,   43,   44,   45,  168,  169,
   40,  257,  258,  259,  150,   93,   46,  282,   43,  257,
   45,   59,   60,   41,   62,   43,   44,   45,  105,  256,
  107,   61,  139,  140,   44,   93,  282,  275,   43,   59,
   45,   59,   60,  270,   62,  256,   59,  207,   93,   59,
   41,   42,   43,   44,   45,   93,   47,   42,   43,  270,
   45,   91,   47,  257,  270,   43,  257,   45,   93,  260,
  183,   59,  184,  150,   59,   93,  270,  283,  238,  256,
  257,  257,   60,   42,   62,  276,   59,  260,   47,  283,
  257,  258,  259,   59,  270,  270,   59,  256,  271,  262,
  213,  262,  214,  276,  256,  257,  258,  259,  283,   59,
  269,  263,  264,  265,  266,  282,  268,  269,  256,  232,
  257,  258,  259,  270,  261,  257,  258,  259,  280,  256,
  282,  256,  257,  258,  259,  258,  259,  256,  263,  264,
  265,  266,  256,  268,  269,  282,  256,  257,  256,   44,
  282,    8,  257,  258,  259,  280,  257,  282,  256,  257,
  258,  259,   19,  256,   61,  263,  264,  265,  266,  256,
  268,  269,  257,  258,  259,  256,  257,  282,  256,  257,
  258,  259,  280,   59,  282,  263,  264,  265,  266,  256,
  268,  269,  257,  258,  259,  139,  140,  282,  256,  257,
  258,  259,  280,   40,  282,  263,  264,  265,  266,  257,
  268,  269,  257,  258,  259,   97,   98,  282,  256,  257,
  258,  259,  280,  257,  282,  263,  264,  265,  266,   59,
  268,  269,  257,  258,  259,  159,  160,  282,  256,  257,
  258,  259,  280,   40,  282,  263,  264,  265,  266,  260,
  268,  269,  257,  258,  259,   86,   41,  282,   41,   44,
  271,   44,  280,   59,  282,  276,  257,  258,  259,   25,
   26,  256,  257,  258,  259,   40,  256,  282,  258,  257,
  258,  259,   40,  268,  269,  263,  264,  265,  266,   59,
  256,  282,   48,  256,  125,  280,  127,  282,   59,  257,
   59,   57,  268,  269,  282,  268,  269,   71,  280,  257,
   59,   75,   76,   59,  280,  113,   40,  280,   41,  117,
   41,   41,   86,  278,  122,  257,  124,  256,  257,  258,
  259,   87,  257,  278,  132,  256,  257,  258,  259,  256,
  257,  258,  259,   41,   44,  176,   40,  257,  279,  180,
  260,  279,   91,  282,  256,  257,  258,  259,  156,  157,
  279,  282,   41,  279,  274,  282,  276,  131,   73,  258,
   59,  281,   77,   59,   79,   93,   59,  208,  209,   41,
  282,  179,   41,   10,  256,  257,   67,  151,  107,  153,
  154,  189,   26,   57,  218,  267,  194,  195,  229,  230,
  272,  273,  250,  167,  217,  277,  204,   -1,  280,  256,
  257,  242,  243,   -1,   -1,   -1,   -1,  256,  257,   -1,
  267,   -1,   -1,   -1,  271,  272,  273,   -1,  267,   -1,
  277,  270,   -1,  272,  273,  233,   -1,   -1,  277,   -1,
   -1,  256,  257,   -1,   -1,   -1,   -1,   -1,  256,  257,
   -1,  215,  267,  217,  218,  270,   -1,  272,  273,  267,
   -1,   -1,  277,   -1,  272,  273,   -1,   -1,   -1,  277,
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
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 284
#define YYUNDFTOKEN 338
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
"miembros_clase","lista_clase","miembro","lista_ejecutables","bloque_END",
"sentencia","asignacion","if_sentencia","iteracion","impresion",
"sentencia_retorno","expresion_aritmetica","destino","$$6","termino","operando",
"parametros_reales","orden_evaluacion","constante","lista_enteros",
"lista_parametros_reales","parametro_real","condicion","bloque_o_sentencia",
"$$7","fin_if","rama_else","$$8","encabezado_iteracion","cuerpo_iteracion",
"operador_relacional","illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : programa",
"$$1 :",
"programa : ID $$1 bloque_declarativo bloque_ejecutable ';'",
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
"$$2 :",
"declaracion_objeto : ID $$2 lista_variables",
"$$3 :",
"declaracion_funcion : tipo_dato FUNCTION ID '(' lista_parametros ')' $$3 bloque_declarativo bloque_ejecutable",
"$$4 :",
"declaracion_funcion : tipo_dato ID '(' lista_parametros ')' $$4 bloque_ejecutable",
"declaracion_funcion : tipo_dato FUNCTION error '(' lista_parametros ')' bloque_declarativo bloque_ejecutable",
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
"bloque_ejecutable : BEGIN lista_ejecutables bloque_END",
"bloque_ejecutable : error lista_ejecutables bloque_END",
"bloque_END : END",
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
"bloque_o_sentencia : bloque_ejecutable",
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
#line 1451 "y.tab.c"
break;
case 2:
#line 30 "gramatica.y"
	{ printf("Sintaxis correcta: Programa reconocido con éxito.\n"); }
#line 1456 "y.tab.c"
break;
case 3:
#line 32 "gramatica.y"
	{ yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
#line 1461 "y.tab.c"
break;
case 14:
#line 56 "gramatica.y"
	{ yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
#line 1466 "y.tab.c"
break;
case 19:
#line 70 "gramatica.y"
	{ printf("[SINT] Estructura Variable, en línea %d\n", yylineno); }
#line 1471 "y.tab.c"
break;
case 20:
#line 74 "gramatica.y"
	{ printf("[SINT] Estructura Objeto, en línea %d\n", yylineno); }
#line 1476 "y.tab.c"
break;
case 22:
#line 78 "gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1481 "y.tab.c"
break;
case 24:
#line 79 "gramatica.y"
	{ printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
#line 1486 "y.tab.c"
break;
case 26:
#line 81 "gramatica.y"
	{ yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
#line 1491 "y.tab.c"
break;
case 28:
#line 86 "gramatica.y"
	{ yyerror("Error: Falta de “,” en declaración de variables."); yyerrok; }
#line 1496 "y.tab.c"
break;
case 31:
#line 93 "gramatica.y"
	{ yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
#line 1501 "y.tab.c"
break;
case 32:
#line 95 "gramatica.y"
	{ yyerror("Error: Falta el tipo del parámetro formal en la función."); yyerrok; }
#line 1506 "y.tab.c"
break;
case 33:
#line 99 "gramatica.y"
	{ printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); }
#line 1511 "y.tab.c"
break;
case 35:
#line 101 "gramatica.y"
	{ yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
#line 1516 "y.tab.c"
break;
case 42:
#line 118 "gramatica.y"
	{ yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
#line 1521 "y.tab.c"
break;
case 48:
#line 133 "gramatica.y"
	{ yyerror("Error: Falta de delimitador de sentencias ejecutables BEGIN."); yyerrok; }
#line 1526 "y.tab.c"
break;
case 52:
#line 144 "gramatica.y"
	{ yyerror("Error: Falta ';' al final de la sentencia o error en sentencia."); yyerrok; }
#line 1531 "y.tab.c"
break;
case 53:
#line 146 "gramatica.y"
	{ yyerror("Error: Falta ';' al final de la sentencia."); yyerrok; }
#line 1536 "y.tab.c"
break;
case 59:
#line 159 "gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1541 "y.tab.c"
break;
case 60:
#line 161 "gramatica.y"
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
#line 1546 "y.tab.c"
break;
case 61:
#line 165 "gramatica.y"
	{ printf("[SINT] Estructura ASSIGN, en línea %d\n", yylineno); }
#line 1551 "y.tab.c"
break;
case 63:
#line 167 "gramatica.y"
	{ yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
#line 1556 "y.tab.c"
break;
case 70:
#line 181 "gramatica.y"
	{ yyerror("Error: Falta operando en la expresión aritmética."); yyerrok; }
#line 1561 "y.tab.c"
break;
case 71:
#line 183 "gramatica.y"
	{ yyerror("Error: Falta operando en la expresión aritmética."); yyerrok; }
#line 1566 "y.tab.c"
break;
case 72:
#line 185 "gramatica.y"
	{ yyerror("Error: Falta operador en la expresión aritmética."); yyerrok; }
#line 1571 "y.tab.c"
break;
case 76:
#line 193 "gramatica.y"
	{ yyerror("Error: Falta operando en el término de la expresión."); yyerrok; }
#line 1576 "y.tab.c"
break;
case 77:
#line 195 "gramatica.y"
	{ yyerror("Error: Falta operando en el término de la expresión."); yyerrok; }
#line 1581 "y.tab.c"
break;
case 86:
#line 211 "gramatica.y"
	{ yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
#line 1586 "y.tab.c"
break;
case 98:
#line 241 "gramatica.y"
	{ printf("[SINT] Estructura IF, en línea %d\n", yylineno); }
#line 1591 "y.tab.c"
break;
case 100:
#line 243 "gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
#line 1596 "y.tab.c"
break;
case 101:
#line 245 "gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
#line 1601 "y.tab.c"
break;
case 103:
#line 250 "gramatica.y"
	{ yyerror("Error: Falta de end_if."); yyerrok; }
#line 1606 "y.tab.c"
break;
case 104:
#line 251 "gramatica.y"
	{ yyerror("Error: Falta de end_if."); yyerrok; }
#line 1611 "y.tab.c"
break;
case 105:
#line 255 "gramatica.y"
	{ printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); }
#line 1616 "y.tab.c"
break;
case 108:
#line 261 "gramatica.y"
	{ yyerror("Error: Falta el cuerpo en la iteración."); yyerrok; }
#line 1621 "y.tab.c"
break;
case 110:
#line 267 "gramatica.y"
	{ yyerror("Error: Falta identificador (ID) en el encabezado de la iteración."); yyerrok; }
#line 1626 "y.tab.c"
break;
case 111:
#line 269 "gramatica.y"
	{ yyerror("Error: Falta palabra clave 'FROM' en el encabezado de la iteración."); yyerrok; }
#line 1631 "y.tab.c"
break;
case 112:
#line 271 "gramatica.y"
	{ yyerror("Error: Falta 'TO' o constante en el encabezado de la iteración."); yyerrok; }
#line 1636 "y.tab.c"
break;
case 114:
#line 274 "gramatica.y"
	{ yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
#line 1641 "y.tab.c"
break;
case 115:
#line 276 "gramatica.y"
	{ yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
#line 1646 "y.tab.c"
break;
case 126:
#line 303 "gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1651 "y.tab.c"
break;
case 127:
#line 305 "gramatica.y"
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
#line 1656 "y.tab.c"
break;
case 128:
#line 307 "gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1661 "y.tab.c"
break;
case 129:
#line 309 "gramatica.y"
	{ yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
#line 1666 "y.tab.c"
break;
#line 1668 "y.tab.c"
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
