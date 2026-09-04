#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TOKENS
#define PLUS 257
#define MINUS 258
#define MULT 259
#define DIV 260
#define ASSIGN_COLON 261
#define ASSIGN 262

#define GE 263
#define LE 264
#define GT 265
#define LT 266
#define EQ 267
#define NE 268

#define LPAREN 269
#define RPAREN 270

#define COMMA 271
#define SEMICOLON 272
#define AND 273
#define COLON 274

#define ID 275
#define CTE 276

#define IF 278
#define ELSE 279
#define END_IF 280
#define BEGIN 281
#define END 282
#define POUT 283
#define RET 284
#define CLASS 285
#define FUNCT 286

#define PES_I 287
#define SINGLEF 288
#define MULT_STRING 289

#define FROM 290
#define TO 291
#define BY 292
#define REPEAT 293

#define LBRACKET 294
#define RBRACKET 295

#define COMPTIME 296
#define TOSF 297
#endif

int yylex(FILE *file){
    if (file == NULL){
        perror("Error archivo inexistente");
        return 1;
    }

    int c;
    int previous;
    char* string;
    while ((c = fgetc(file)) != EOF){
        if (!isspace(c)){
            int len = strlen(string);
            string[len] = c;
            string[len+1] = '/0';

            if (c == '/' && previous == '/'){
                while ((c = fgetc(file)) != '/n' && c != EOF){}
                break;
            }

            previous == c;
        }
    }
    
    return 0;
}