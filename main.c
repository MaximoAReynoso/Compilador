#include <stdio.h>

void yyparse();

void initialize(int estados, int inputs, int matriz[estados][inputs]){
    for(int i = 0; i < estados; i++)
        for(int j = 0; j < inputs; j++)
            matriz[i][j] = -1;
}

void fill(int estados, int inputs, int matriz[estados][inputs]){
    matriz[0][32] = 0;      // " "
    matriz[0][9] = 0;       // tab

    matriz[0][10] = 0;      // \n
    matriz[9][10] = 0;

    //Digitos 0-9
    for (int i = 48; i <= 57; i++){
        matriz[0][i] = 1;
        matriz[1][i] = 1;
        matriz[4][i] = 5;
        matriz[5][i] = 5;
        matriz[6][i] = 7;
        matriz[7][i] = 7;
        matriz[13][i] = 13;
    }
    
    matriz[0][34] = 3;      //"
    matriz[3][34] = 14;

    matriz[1][36] = 2;      //$

    matriz[0][46] = 4;      //.
    matriz[1][46] = 4;

    matriz[0][33] = 10;      //!
    matriz[0][58] = 13;      //:

    matriz[0][61] = 11;      //=
    matriz[10][61] = 14;
    matriz[11][61] = 14;
    matriz[12][61] = 14;

    matriz[0][60] = 11;       //<
    matriz[0][62] = 11;       //>

    matriz[5][115] = 6;       //s

    matriz[0][43] = 14;       //+
    matriz[6][43] = 7;        //+
    matriz[0][45] = 14;       //-
    matriz[6][45] = 7;        //-
    matriz[0][42] = 14;       //*

    matriz[0][47] = 8;        // /
    matriz[8][47] = 9;

    matriz[2][105] = 14;      //i
    matriz[13][95] = 13;      //_
    matriz[0][59] = 14;       //;
    matriz[0][40] = 14;       //(
    matriz[0][41] = 14;       //)

    //Mayusculas
    for (int i = 65; i <= 90; i++){
        matriz[0][i] = 13;
        matriz[13][i] = 13;
    }

    //Minusculas
    for (int i = 97; i <= 122; i++){
        matriz[0][i] = 13;
        matriz[13][i] = 13;
    }

    //otros
    for (int i = 0; i < inputs; i++){
        if (matriz[3][i] == -1) matriz[3][i] = 3;
        if (matriz[5][i] == -1) matriz[5][i] = 14;
        if (matriz[7][i] == -1) matriz[7][i] = 14;
        if (matriz[8][i] == -1) matriz[8][i] = 14;
        if (matriz[9][i] == -1) matriz[9][i] = 9;
        if (matriz[11][i] == -1) matriz[11][i] = 14;
        if (matriz[13][i] == -1) matriz[13][i] = 14;
    }

}

int main(int argc, char* argv[]){
    if (argc != 2){
        if (argc < 2)
            printf("Error - Necesita un archivo a compilar.");
        else
            printf("Error - Necesita un unico archivo a compilar.");
        return 1;
    }

    char* file_path = argv[1];
    FILE *file = fopen(file_path, "r");

    if (file == NULL){
        printf("Error - Archivo no encontrado.");
        return 1;
    }

    int matriz_transicion[14][128];
    initialize(14, 128, matriz_transicion);
    fill(14, 128, matriz_transicion);



    //yyparse();

    fclose(file);
    return 0;
}