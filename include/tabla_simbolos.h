#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#define TAM_TABLA 101

typedef struct Simbolo {
    char *lexema;
    int token;
    int linea;
    struct Simbolo *siguiente;
} Simbolo;

typedef struct {
    Simbolo *entradas[TAM_TABLA];
} TablaSimbolos;

void inicializar_tabla(TablaSimbolos *tabla);

Simbolo *buscar_simbolo(TablaSimbolos *tabla, const char *lexema);

Simbolo *insertar_simbolo(
    TablaSimbolos *tabla,
    const char *lexema,
    int token,
    int linea
);

void destruir_tabla(TablaSimbolos *tabla);

#endif