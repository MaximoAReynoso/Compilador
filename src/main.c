#include <stdio.h>
#include <stdlib.h>

#include "tabla_simbolos.h"
#include "y.tab.h"
#include "yylex.h"
#include "acciones_semanticas.h"
#include "polaca.h"
#include "errores.h"

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
        printf("Error: No se pudo abrir el archivo '%s'.\n", file_path);
        return 1;
    }

    // Inicialización de subsistemas del compilador
    inicializar_errores();
    inicializar_gestor_ambitos();
    inicializar_gestor_polaca();

    // Crear polaca principal
    Polaca *polaca_main = crear_polaca("main");
    establecer_polaca_actual(polaca_main);

    TablaSimbolos tabla;
    inicializar_tabla(&tabla);
    establecer_tabla_simbolos(&tabla);

    init_lexer();
    set_lexer_file(file);

    yyparse();

    fclose(file);

    // Salida según los requerimientos de entrega (Paso 5)
    imprimir_errores();
    imprimir_todas_las_polacas();
    imprimir_tabla(&tabla);

    // Liberación de recursos
    destruir_tabla(&tabla);
    destruir_gestor_polaca();
    destruir_gestor_ambitos();
    destruir_errores();

    return 0;
}