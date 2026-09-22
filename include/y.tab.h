#ifndef _yy_defines_h_
#define _yy_defines_h_

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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE {
    struct Simbolo *simbolo;
    int val_int;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
