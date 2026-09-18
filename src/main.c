#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"
#include "yylex.h"
#include "tabla_simbolos.h"
#include "acciones_semanticas.h"

#include "y.tab.c"


extern int yyparse();
extern int yylineno;

void yyerror(const char *s) {
    if (yychar != END) {
        fprintf(stderr, "\nLínea %d: Error: Falta de delimitador de sentencias ejecutables END.\n\n", yylineno);
    }
    fprintf(stderr, "\nLínea %d: %s\n\n", yylineno, s);
}


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

    if (resultado == 0) {
        printf("\n Compilacion exitosa: No se encontraron errores sintacticos.\n");
    } else {
        printf("\n Fallo el analisis sintactico.\n");
    }

    printf("--- Fin de archivo ---\n\n");
    imprimir_tabla(&tabla);

    fclose(file);
    destruir_tabla(&tabla);

    //yylex_destroy();
    
    return 0;
}    