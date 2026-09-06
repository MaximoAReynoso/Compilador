#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>
#include "acciones_semanticas.h"

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

// DECLARACION DE VARIABLES

int numero_linea = 1;
char buffer_lexema[1024] = "";
int longitud_lexema = 0;

const int CANT_ESTADOS = 15;  //rangos de la matriz de transicion y acciones semanticas
const int CANT_INPUTS = 128;

typedef void (*AccionSemantica)(int c, char *buffer, int *len);         // Definicion de tipo para las acciones semanticas

static int matriz_transicion[CANT_ESTADOS][CANT_INPUTS];                // Matriz de transicion de estados
static AccionSemantica matriz_acciones[CANT_ESTADOS][CANT_INPUTS];      // Matriz de acciones semanticas
static FILE *archivo_fuente = NULL;

// FUNCIONES

void set_lexer_file(FILE *f) {
    archivo_fuente = f;
}

bool compareRegex(const char* string, const char* patron){
    regex_t regex;
    int res;

    if (regcomp(&regex, patron, REG_EXTENDED || REG_ICASE) != 0)
        return false;
    res = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    return res == 0; 
}

void init_lexer(){

// Inicializa las matrices internas
    for(int i = 0; i < CANT_ESTADOS; i++){
        for(int j = 0; j < CANT_INPUTS; j++){
            matriz_transicion[i][j] = -1;
            matriz_acciones[i][j] = NULL;
        }
    }

// Llena la matriz de transiciones
    matriz_transicion[0][32] = 0;      // " "
    matriz_transicion[0][9] = 0;       // tab
    matriz_transicion[0][10] = 0;      // \n
    matriz_transicion[9][10] = 0;      // fin comentario

    //Digitos 0-9
    for (int i = 48; i <= 57; i++){
        matriz_transicion[0][i] = 1;
        matriz_transicion[1][i] = 1;
        matriz_transicion[4][i] = 5;
        matriz_transicion[5][i] = 5;
        matriz_transicion[6][i] = 7;
        matriz_transicion[7][i] = 7;
        matriz_transicion[13][i] = 13;
    }
    
    matriz_transicion[0][34] = 3;      //"
    matriz_transicion[3][34] = 14;

    matriz_transicion[1][36] = 2;      //$

    matriz_transicion[0][46] = 4;      //.
    matriz_transicion[1][46] = 4;

    matriz_transicion[0][33] = 10;      //!
    matriz_transicion[0][58] = 12;      //:

    matriz_transicion[0][61] = 11;      //=
    matriz_transicion[10][61] = 14;
    matriz_transicion[11][61] = 14;
    matriz_transicion[12][61] = 14;

    matriz_transicion[0][60] = 11;       //<
    matriz_transicion[0][62] = 11;       //>

    matriz_transicion[5][115] = 6;       //s

    matriz_transicion[0][43] = 14;       //+
    matriz_transicion[6][43] = 7;        //+
    matriz_transicion[0][45] = 14;       //-
    matriz_transicion[6][45] = 7;        //-
    matriz_transicion[0][42] = 14;       //*

    matriz_transicion[0][47] = 8;        ///
    matriz_transicion[8][47] = 9;

    matriz_transicion[2][105] = 14;      //i
    matriz_transicion[13][95] = 13;      //_
    matriz_transicion[0][59] = 14;       //;
    matriz_transicion[0][40] = 14;       //(
    matriz_transicion[0][41] = 14;       //)

    //Mayusculas
    for (int i = 65; i <= 90; i++){
        matriz_transicion[0][i] = 13;
        matriz_transicion[13][i] = 13;
    }

    //Minusculas
    for (int i = 97; i <= 122; i++){
        matriz_transicion[0][i] = 13;
        matriz_transicion[13][i] = 13;
    }

    //otros
    for (int i = 0; i < CANT_INPUTS; i++){
        if (matriz_transicion[3][i] == -1) matriz_transicion[3][i] = 3;
        if (matriz_transicion[5][i] == -1) matriz_transicion[5][i] = 14;
        if (matriz_transicion[7][i] == -1) matriz_transicion[7][i] = 14;
        if (matriz_transicion[8][i] == -1) matriz_transicion[8][i] = 14;
        if (matriz_transicion[9][i] == -1) matriz_transicion[9][i] = 9;
        if (matriz_transicion[11][i] == -1) matriz_transicion[11][i] = 14;
        if (matriz_transicion[13][i] == -1) matriz_transicion[13][i] = 14;
    }

//llena la matriz de acciones semanticas
    matriz_acciones[0][32] = as_consume;                // " "
    matriz_acciones[0][9] = as_consume;                 // tab
    matriz_acciones[0][10] = as_count_line;             // \n
    matriz_acciones[9][10] = as_consume_comment;        // fin comentario

    //Digitos 0-9
    for (int i = 48; i <= 57; i++){
        matriz_acciones[0][i] = as_add_to_buffer;
        matriz_acciones[1][i] = as_add_to_buffer;
        matriz_acciones[4][i] = as_add_to_buffer;
        matriz_acciones[5][i] = as_add_to_buffer;
        matriz_acciones[6][i] = as_add_to_buffer;      // leer signo
        matriz_acciones[7][i] = as_add_to_buffer;
        matriz_acciones[13][i] = as_add_to_buffer;
    }

    matriz_acciones[0][34] = as_add_to_buffer;            //"
    matriz_acciones[3][34] = as_emit_token_string;

    matriz_acciones[1][36] = as_add_to_buffer;            //$

    matriz_acciones[0][46] = as_add_to_buffer;            //.
    matriz_acciones[1][46] = as_add_to_buffer;

    matriz_acciones[0][33] = as_add_to_buffer;;           //!
    matriz_acciones[0][58] = as_add_to_buffer;            //:

    matriz_acciones[0][61] = as_add_to_buffer;            //=
    matriz_acciones[10][61] = as_emit_token_NEQ;          //!=
    matriz_acciones[11][61] = as_emit_token_comp;         //==, <=, >=  
    matriz_acciones[12][61] = as_emit_token_ASIG;         //:=

    matriz_acciones[0][60] = as_add_to_buffer;            //<
    matriz_acciones[0][62] = as_add_to_buffer;            //>

    matriz_acciones[5][115] = as_add_to_buffer;           //s

    matriz_acciones[0][43] = as_classify_and_emit;        //+
    matriz_acciones[6][43] = as_add_to_buffer;            //+
    matriz_acciones[0][45] = as_classify_and_emit;        //-
    matriz_acciones[6][45] = as_add_to_buffer;            //-
    matriz_acciones[0][42] = as_classify_and_emit;        //*

    matriz_acciones[0][47] = as_add_to_buffer;            ///
    matriz_acciones[8][47] = as_add_to_buffer;

    matriz_acciones[2][105] = as_emit_token_INT;          //i
    matriz_acciones[13][95] = as_add_to_buffer;           //_
    matriz_acciones[0][59] = as_classify_and_emit;        //;
    matriz_acciones[0][40] = as_classify_and_emit;        //(
    matriz_acciones[0][41] = as_classify_and_emit;        //)

        //Mayusculas
    for (int i = 65; i <= 90; i++){
        matriz_acciones[0][i] = as_add_to_buffer;
        matriz_acciones[13][i] = as_add_to_buffer;
    }

    //Minusculas
    for (int i = 97; i <= 122; i++){
        matriz_acciones[0][i] = as_add_to_buffer;
        matriz_acciones[13][i] = as_add_to_buffer;
    }

        //otros
    for (int i = 0; i < CANT_INPUTS; i++){
        if (matriz_acciones[3][i] == NULL) matriz_acciones[3][i] = as_add_to_buffer;
        if (matriz_acciones[5][i] == NULL) matriz_acciones[5][i] = as_emit_token_FLOAT;
        if (matriz_acciones[7][i] == NULL) matriz_acciones[7][i] = as_emit_token_FLOAT;
        if (matriz_acciones[8][i] == NULL) matriz_acciones[8][i] = as_retract_and_emit;
        if (matriz_acciones[9][i] == NULL) matriz_acciones[9][i] = as_add_to_buffer;
        if (matriz_acciones[11][i] == NULL) matriz_acciones[11][i] = as_retract_and_emit;
        if (matriz_acciones[13][i] == NULL) matriz_acciones[13][i] = as_PR_IDENT;
    }
}

int yylex(){
    int c;
    int previous;
    char string[50] = "";
    int estado = 0;

    //ver que hacer con el .* al final
    while ((c = fgetc(archivo_fuente)) != EOF){
        estado = matriz_transicion[estado][c];
        strcat(string, c);          //error c es un entero
                                    //mantener string con nulo al final

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