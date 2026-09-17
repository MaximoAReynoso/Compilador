#ifndef _yy_defines_h_
#define _yy_defines_h_

#define ID 257
#define CTE 258
#define CTE_FLOAT 259
#define PES_I 260
#define MULT_STRING 261
#define ASSIGN_COLON 262
#define ASSIGN 263
#define GE 264
#define LE 265
#define GT 266
#define LT 267
#define EQ 268
#define NE 269
#define IF 270
#define ELSE 271
#define END_IF 272
#define BEGIN 273
#define END 274
#define POUT 275
#define RET 276
#define CLASS 277
#define FUNCTION 278
#define SINGLEF 279
#define FROM 280
#define TO 281
#define BY 282
#define REPEAT 283
#define COMPTIME 284
#define TOSF 285
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
