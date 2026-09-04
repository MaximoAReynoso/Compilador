#include <stdio.h>
#include <stdlib.h>

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

#endif

int yylex(FILE *file){
    if (file == NULL){
        perror("Error archivo inexistente");
        return -1;
    }

    int c;
    while ((c = fgetc(file)) != EOF){
        
    }
    
    return 0;
}