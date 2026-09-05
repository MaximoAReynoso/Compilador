#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

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

bool compareRegex(const char* string, const char* patron){
    regex_t regex;
    int res;

    if (regcomp(&regex, patron, REG_EXTENDED || REG_ICASE) != 0)
        return false;
    res = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    return res == 0;
}

int yylex(FILE *file, int estados, int inputs, int matriz[estados][inputs]){
    if (file == NULL){
        perror("Error archivo inexistente");
        return 1;
    }

    int c;
    int previous;
    char string[50] = "";
    int estado = 0;

    //ver que hacer con el .* al final
    while ((c = fgetc(file)) != EOF && estado != 14){
        estado = matriz[estado][c];
        strcat(string, c);

        if (estado == 14){
            if (compareRegex(string, "^+$")) return PLUS;
            if (compareRegex(string, "^-$")) return MINUS;
            if (compareRegex(string, "^*$")) return MULT;
            if (compareRegex(string, "^/.*$")) return DIV;

            if (compareRegex(string, "^<=$")) return GE;
            if (compareRegex(string, "^>=$")) return LE;
            if (compareRegex(string, "^<.*$")) return GT;
            if (compareRegex(string, "^>.*$")) return LT;
            if (compareRegex(string, "^==$")) return EQ;
            if (compareRegex(string, "^!=$")) return NE;

            if (compareRegex(string, "^:=$")) return ASSIGN_COLON;
            if (compareRegex(string, "^=.*$")) return ASSIGN;

            if (compareRegex(string, "^($")) return LPAREN;
            if (compareRegex(string, "^)$")) return RPAREN;

            if (compareRegex(string, "^[$")) return LBRACKET;
            if (compareRegex(string, "^]$")) return RBRACKET;

            if (compareRegex(string, "^if.*$")) return IF;
            if (compareRegex(string, "^else.*$")) return ELSE;
            if (compareRegex(string, "^end_if.*$")) return END_IF;
            if (compareRegex(string, "^begin.*$")) return BEGIN;
            if (compareRegex(string, "^end.*$")) return END;
            if (compareRegex(string, "^pout.*$")) return POUT;
            if (compareRegex(string, "^ret.*$")) return RET;
            if (compareRegex(string, "^class.*$")) return CLASS;
            if (compareRegex(string, "^funct.*$")) return FUNCT;
            if (compareRegex(string, "^from.*$")) return FROM;
            if (compareRegex(string, "^to.*$")) return TO;
            if (compareRegex(string, "^by.*$")) return BY;
            if (compareRegex(string, "^repeat.*$")) return REPEAT;
            if (compareRegex(string, "^comptime.*$")) return COMPTIME;
            if (compareRegex(string, "^tosf.*$")) return COMPTIME;
            if (compareRegex(string, "^[0-9]*$")) return CTE;
            if (compareRegex(string, "^[a-z0-9_]*$")) return ID;

            if (compareRegex(string, "^\".*\"$")) return MULT_STRING;
        } 
        
        if (estado == -1){
            //esto es un error, ver si el valor retornado esta bien
            return 0;
        }
    }

    if (estado == 14){
        if (compareRegex(string, "^+$")) return PLUS;
        if (compareRegex(string, "^-$")) return MINUS;
        if (compareRegex(string, "^*$")) return MULT;
        if (compareRegex(string, "^/.*$")) return DIV;

        if (compareRegex(string, "^<=$")) return GE;
        if (compareRegex(string, "^>=$")) return LE;
        if (compareRegex(string, "^<.*$")) return GT;
        if (compareRegex(string, "^>.*$")) return LT;
        if (compareRegex(string, "^==$")) return EQ;
        if (compareRegex(string, "^!=$")) return NE;

        if (compareRegex(string, "^:=$")) return ASSIGN_COLON;
        if (compareRegex(string, "^=.*$")) return ASSIGN;

        if (compareRegex(string, "^($")) return LPAREN;
        if (compareRegex(string, "^)$")) return RPAREN;

        if (compareRegex(string, "^[$")) return LBRACKET;
        if (compareRegex(string, "^]$")) return RBRACKET;

        if (compareRegex(string, "^if.*$")) return IF;
        if (compareRegex(string, "^else.*$")) return ELSE;
        if (compareRegex(string, "^end_if.*$")) return END_IF;
        if (compareRegex(string, "^begin.*$")) return BEGIN;
        if (compareRegex(string, "^end.*$")) return END;
        if (compareRegex(string, "^pout.*$")) return POUT;
        if (compareRegex(string, "^ret.*$")) return RET;
        if (compareRegex(string, "^class.*$")) return CLASS;
        if (compareRegex(string, "^funct.*$")) return FUNCT;
        if (compareRegex(string, "^from.*$")) return FROM;
        if (compareRegex(string, "^to.*$")) return TO;
        if (compareRegex(string, "^by.*$")) return BY;
        if (compareRegex(string, "^repeat.*$")) return REPEAT;
        if (compareRegex(string, "^comptime.*$")) return COMPTIME;
        if (compareRegex(string, "^tosf.*$")) return COMPTIME;
        if (compareRegex(string, "^[0-9]*$")) return CTE;
        if (compareRegex(string, "^[a-z0-9_]*$")) return ID;

        if (compareRegex(string, "^\".*\"$")) return MULT_STRING;
    }
    
    return 0;
}