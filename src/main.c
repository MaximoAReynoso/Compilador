#include <stdio.h>

#include "tokens.h"
#include "yylex.h"
#include "tabla_simbolos.h"
#include "acciones_semanticas.h"

Simbolo *yylval = NULL;

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

    TablaSimbolos tabla;
    inicializar_tabla(&tabla);

    establecer_tabla_simbolos(&tabla);

    init_lexer();
    set_lexer_file(file);

    //yyparse();
    int token;
    while ((token = yylex()) != 0) {
        printf("Token reconocido: %d en linea %d\n", token, numero_linea);
    }

    fclose(file);
    destruir_tabla(&tabla);
    return 0;
}