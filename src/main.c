#include <stdio.h>

#include "tokens.h"
#include "yylex.h"
#include "tabla_simbolos.h"
#include "acciones_semanticas.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <archivo_a_compilar>\n", argv[0]);
        return 1;
    }

    char* file_path = argv[1];
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo '%s'.\n",file_path);
        return 1;
    }

    TablaSimbolos tabla;
    inicializar_tabla(&tabla);
    establecer_tabla_simbolos(&tabla);

    init_lexer();
    set_lexer_file(file);

    printf("--- Iniciando Analisis Lexico ---\n");

    int token;
    while ((token = yylex()) != 0) {
        if (token >= 256) {
            printf("[Línea %d] (ID: %d)\n",numero_linea, token);
        } else {
            printf("[Línea %d] Símbolo simple: '%c'(ASCII: %d)\n", numero_linea, (char)token, token);
        }
    }

    printf("--- Fin de archivo ---\n");

    fclose(file);
    destruir_tabla(&tabla);
    return 0;
}    