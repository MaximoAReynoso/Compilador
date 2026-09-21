#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"
#include "yylex.h"
#include "tabla_simbolos.h"
#include "acciones_semanticas.h"


extern int yyparse();
extern int yylineno;

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

    printf("--- Iniciando Analisis sintactico ---\n");

    int resultado = yyparse();
  
    /*if (resultado == 0) {
        printf("Compilación exitosa: No se encontraron errores sintácticos.\n");
    } else {
        printf("\n Fallo el analisis sintactico.\n");
    }*/

    printf("--- Fin de archivo ---\n\n");
    imprimir_tabla(&tabla);

    fclose(file);
    destruir_tabla(&tabla);

    //yylex_destroy();

    return 0;
}    