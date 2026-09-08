#include <stdio.h>

#include "tokens.h"

extern int *yylval;

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

    init_lexer();
    set_lexer_file(file);
    //yyparse();

    fclose(file);
    return 0;
}