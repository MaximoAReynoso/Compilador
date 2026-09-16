#include <stdio.h>
#include <string.h>

#include "acciones_semanticas.h"
#include "tokens.h"
#include "tabla_simbolos.h"

#define CANT_ESTADOS 16  //rangos de la matriz de transicion y acciones semanticas
#define CANT_INPUTS 128

// DECLARACION DE VARIABLES

int numero_linea = 1;
char buffer_lexema[1024] = "";
int longitud_lexema = 0;
FILE *archivo_fuente = NULL;
Simbolo *yylval = NULL;

typedef int (*AccionSemantica)(int c, char *buffer, int *len);         // Definicion de tipo para las acciones semanticas

static int matriz_transicion[CANT_ESTADOS][CANT_INPUTS];                // Matriz de transicion de estados
static AccionSemantica matriz_acciones[CANT_ESTADOS][CANT_INPUTS];      // Matriz de acciones semanticas


// FUNCIONES

void set_lexer_file(FILE *f) {
    archivo_fuente = f;
}

void init_lexer(){
// Inicializa las matrices
    for(int i = 0; i < CANT_ESTADOS; i++){
        for(int j = 0; j < CANT_INPUTS; j++){
            matriz_transicion[i][j] = -1;
            matriz_acciones[i][j] = NULL;
        }
    }

// Llenado de la matriz de transiciones
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
        matriz_transicion[14][i] = 7;
    }
    
    matriz_transicion[0][34] = 3;      //"
    matriz_transicion[3][34] = 15;

    matriz_transicion[1][36] = 2;      //$

    matriz_transicion[0][46] = 4;      //.
    matriz_transicion[1][46] = 4;

    matriz_transicion[0][33] = 10;      //!
    matriz_transicion[0][58] = 12;      //:

    matriz_transicion[0][61] = 11;      //=
    matriz_transicion[10][61] = 15;
    matriz_transicion[11][61] = 15;
    matriz_transicion[12][61] = 15;

    matriz_transicion[0][60] = 11;       //<
    matriz_transicion[0][62] = 11;       //>

    matriz_transicion[5][115] = 6;       //s

    matriz_transicion[0][43] = 15;       //+
    matriz_transicion[6][43] = 14;       //+
    matriz_transicion[0][45] = 15;       //-
    matriz_transicion[6][45] = 14;       //-
    matriz_transicion[0][42] = 15;       //*

    matriz_transicion[0][47] = 8;        ///
    matriz_transicion[8][47] = 9;

    matriz_transicion[2][105] = 15;      //i
    matriz_transicion[13][95] = 13;      //_
    matriz_transicion[0][59] = 15;       //;
    matriz_transicion[0][40] = 15;       //(
    matriz_transicion[0][41] = 15;       //)

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
        if (matriz_transicion[5][i] == -1) matriz_transicion[5][i] = 15;
        if (matriz_transicion[7][i] == -1) matriz_transicion[7][i] = 15;
        if (matriz_transicion[8][i] == -1) matriz_transicion[8][i] = 15;
        if (matriz_transicion[9][i] == -1) matriz_transicion[9][i] = 9;
        if (matriz_transicion[11][i] == -1) matriz_transicion[11][i] = 15;
        if (matriz_transicion[13][i] == -1) matriz_transicion[13][i] = 15;
    } 

//llenado de la matriz de acciones semanticas
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
        matriz_acciones[14][i] = as_add_to_buffer;
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
    int estado = 0;
    AccionSemantica accion;

    while ((c = fgetc(archivo_fuente)) != EOF){
        accion = matriz_acciones[estado][c];
        estado = matriz_transicion[estado][c];

        if(estado == -1){ //error
            printf("Error lexico en linea %d: caracter inesperado '%c' (ascii %d)\n", numero_linea,c,c);
            estado = 0;
            longitud_lexema = 0;
            buffer_lexema[0] = '\0';
        }else if (estado == 15) { //estado Final
            estado = 0; //proximo token
            if (accion != NULL)
                return accion(c, buffer_lexema, &longitud_lexema);
        }else {
            if(accion != NULL)
                accion(c, buffer_lexema, &longitud_lexema);
        }
    }

    return 0; //EOF
}