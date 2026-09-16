#include "tabla_simbolos.h"
#include <stdlib.h>
#include <string.h>

static unsigned hash(const char *lexema) {
    unsigned hash_value = 0;

    while (*lexema != '\0') {
        hash_value = (hash_value * 31) + (unsigned char)(*lexema);
        lexema++;
    }
    
    return hash_value % TAM_TABLA;
}

void inicializar_tabla(TablaSimbolos *tabla) {
    for (int i = 0; i < TAM_TABLA; i++) {
        tabla->entradas[i] = NULL;
    }
}

Simbolo *buscar_simbolo(TablaSimbolos *tabla, const char *lexema){
    unsigned index = hash(lexema);
    Simbolo *actual = tabla->entradas[index];

    while (actual != NULL) {
        if (strcmp(actual->lexema, lexema) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }

    return NULL;

}

Simbolo *insertar_simbolo(TablaSimbolos *tabla, const char *lexema, int token, int linea) {

    Simbolo *existe = buscar_simbolo(tabla, lexema);
    if (existe != NULL) {
        return existe;
    }
    
    unsigned index = hash(lexema);
    Simbolo *nuevo_simbolo = malloc(sizeof *nuevo_simbolo);
    if (nuevo_simbolo == NULL) {
        return NULL;
    }

    nuevo_simbolo->lexema = malloc(strlen(lexema) + 1);
    if (nuevo_simbolo->lexema == NULL) {
        free(nuevo_simbolo);
        return NULL;
    }

    strcpy(nuevo_simbolo->lexema, lexema);
    nuevo_simbolo->token = token;
    nuevo_simbolo->linea = linea;
    nuevo_simbolo->siguiente = tabla->entradas[index];
    tabla->entradas[index] = nuevo_simbolo;

    return nuevo_simbolo;
}

void destruir_tabla(TablaSimbolos *tabla) {
    for (int i = 0; i < TAM_TABLA; i++) {
        Simbolo *actual = tabla->entradas[i];
        while (actual != NULL) {
            Simbolo *temp = actual;
            actual = actual->siguiente;
            free(temp->lexema);
            free(temp);
        }
    }
}