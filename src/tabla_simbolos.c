#include "tabla_simbolos.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

Simbolo *insertar_simbolo(TablaSimbolos *tabla, const char *lexema, int token) {

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
    nuevo_simbolo->siguiente = tabla->entradas[index];
    tabla->entradas[index] = nuevo_simbolo;

    return nuevo_simbolo;
}

void modificar_lexema(Simbolo *simbolo, const char *nuevo_lexema) {
    if (simbolo == NULL || nuevo_lexema == NULL) return;
    
    char *nuevo = malloc(strlen(nuevo_lexema) + 1);
    if (nuevo == NULL) return;
    
    strcpy(nuevo, nuevo_lexema);
    free(simbolo->lexema);
    simbolo->lexema = nuevo;
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

void imprimir_tabla(TablaSimbolos *tabla){
    printf("Tabla de Simbolos:\n");
    for (int i = 0; i < TAM_TABLA; i++){
        Simbolo *actual = tabla->entradas[i];
        while (actual != NULL) {
            Simbolo *temp = actual;
            printf("Token: %i, Lexema: %s\n",temp->token, temp->lexema);
            actual = actual->siguiente;
        }
    }
}