#include "errores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static ErrorCompilador *lista_errores = NULL;
static ErrorCompilador *ultimo_error = NULL;
static int total_errores = 0;

void inicializar_errores(void) {
    destruir_errores();
    lista_errores = NULL;
    ultimo_error = NULL;
    total_errores = 0;
}

static const char *nombre_etapa(EtapaError etapa) {
    switch (etapa) {
        case ETAPA_LEXICO:
            return "LÉXICO";
        case ETAPA_SINTACTICO:
            return "SINTÁCTICO";
        case ETAPA_SEMANTICO:
            return "SEMÁNTICO";
        case ETAPA_CODIGO_INTERMEDIO:
            return "CÓDIGO INTERMEDIO";
        default:
            return "GENERAL";
    }
}

void registrar_error(EtapaError etapa, int linea, const char *formato, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, formato);
    vsnprintf(buffer, sizeof(buffer), formato, args);
    va_end(args);

    // Evitar registrar duplicados idénticos en la misma línea
    for (ErrorCompilador *curr = lista_errores; curr != NULL; curr = curr->siguiente) {
        if (curr->etapa == etapa && curr->linea == linea && strcmp(curr->descripcion, buffer) == 0) {
            return;
        }
    }

    ErrorCompilador *nuevo = malloc(sizeof(ErrorCompilador));
    if (!nuevo) return;

    nuevo->etapa = etapa;
    nuevo->linea = linea;
    nuevo->descripcion = strdup(buffer);
    nuevo->siguiente = NULL;

    if (ultimo_error == NULL) {
        lista_errores = nuevo;
    } else {
        ultimo_error->siguiente = nuevo;
    }
    ultimo_error = nuevo;
    total_errores++;
}

int cantidad_errores(void) {
    return total_errores;
}

int cantidad_errores_etapa(EtapaError etapa) {
    int c = 0;
    for (ErrorCompilador *curr = lista_errores; curr != NULL; curr = curr->siguiente) {
        if (curr->etapa == etapa) {
            c++;
        }
    }
    return c;
}

void imprimir_errores(void) {
    printf("\n============================================================\n");
    printf("                  INFORME DE ERRORES                        \n");
    printf("============================================================\n");
    if (total_errores == 0) {
        printf("No se detectaron errores durante la compilación.\n");
        printf("============================================================\n\n");
        return;
    }

    printf("Total de errores detectados: %d\n\n", total_errores);
    for (ErrorCompilador *curr = lista_errores; curr != NULL; curr = curr->siguiente) {
        printf("[ERROR %s] Línea %d: %s\n",
               nombre_etapa(curr->etapa),
               curr->linea,
               curr->descripcion);
    }
    printf("============================================================\n\n");
}

void destruir_errores(void) {
    ErrorCompilador *curr = lista_errores;
    while (curr != NULL) {
        ErrorCompilador *temp = curr;
        curr = curr->siguiente;
        free(temp->descripcion);
        free(temp);
    }
    lista_errores = NULL;
    ultimo_error = NULL;
    total_errores = 0;
}
