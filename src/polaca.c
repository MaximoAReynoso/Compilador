#include "polaca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDAD_INICIAL 64
#define MAX_SALTOS 256

static Polaca *lista_polacas = NULL;
static Polaca *polaca_actual = NULL;

static int pila_saltos[MAX_SALTOS];
static int tope_saltos = 0;

void inicializar_gestor_polaca(void) {
    destruir_gestor_polaca();
    lista_polacas = NULL;
    polaca_actual = NULL;
    tope_saltos = 0;
}

static void redimensionar_si_es_necesario(Polaca *p) {
    if (!p) return;
    if (p->tam >= p->capacidad) {
        int nueva_capacidad = p->capacidad * 2;
        if (nueva_capacidad < CAPACIDAD_INICIAL) {
            nueva_capacidad = CAPACIDAD_INICIAL;
        }
        ElementoPolaca *nuevos = realloc(p->elementos, nueva_capacidad * sizeof(ElementoPolaca));
        if (!nuevos) {
            fprintf(stderr, "Error interno: Memoria insuficiente para Polaca Inversa.\n");
            return;
        }
        p->elementos = nuevos;
        p->capacidad = nueva_capacidad;
    }
}

Polaca *crear_polaca(const char *nombre) {
    Polaca *p = calloc(1, sizeof(Polaca));
    if (!p) return NULL;

    p->nombre = strdup(nombre ? nombre : "desconocido");
    p->capacidad = CAPACIDAD_INICIAL;
    p->tam = 0;
    p->elementos = calloc(p->capacidad, sizeof(ElementoPolaca));
    p->siguiente = NULL;

    if (lista_polacas == NULL) {
        lista_polacas = p;
    } else {
        Polaca *curr = lista_polacas;
        while (curr->siguiente != NULL) {
            curr = curr->siguiente;
        }
        curr->siguiente = p;
    }

    return p;
}

static Polaca *pila_polacas_activas[32];
static int tope_polacas_activas = 0;

void polaca_apilar_actual(Polaca *p) {
    if (tope_polacas_activas < 32) {
        pila_polacas_activas[tope_polacas_activas++] = polaca_actual;
    }
    establecer_polaca_actual(p);
}

void polaca_desapilar_actual(void) {
    if (tope_polacas_activas > 0) {
        establecer_polaca_actual(pila_polacas_activas[--tope_polacas_activas]);
    }
}

void establecer_polaca_actual(Polaca *p) {
    polaca_actual = p;
}

Polaca *obtener_polaca_actual(void) {
    return polaca_actual;
}

Polaca *obtener_polaca_por_nombre(const char *nombre) {
    if (!nombre) return NULL;
    for (Polaca *p = lista_polacas; p != NULL; p = p->siguiente) {
        if (strcmp(p->nombre, nombre) == 0) {
            return p;
        }
    }
    return NULL;
}

int polaca_emitir_simbolo(Simbolo *s, int linea) {
    if (!polaca_actual) return -1;
    redimensionar_si_es_necesario(polaca_actual);

    int pos = polaca_actual->tam;
    ElementoPolaca *e = &polaca_actual->elementos[pos];
    e->tipo = POLACA_TIPO_SIMBOLO;
    e->simbolo = s;
    e->operador = NULL;
    e->celda_destino = -1;
    e->linea = linea;

    polaca_actual->tam++;
    return pos;
}

int polaca_emitir_operador(const char *op, int linea) {
    if (!polaca_actual || !op) return -1;
    redimensionar_si_es_necesario(polaca_actual);

    int pos = polaca_actual->tam;
    ElementoPolaca *e = &polaca_actual->elementos[pos];
    e->tipo = POLACA_TIPO_OPERADOR;
    e->simbolo = NULL;
    e->operador = strdup(op);
    e->celda_destino = -1;
    e->linea = linea;

    polaca_actual->tam++;
    return pos;
}

int polaca_emitir_celda_vacia(int linea) {
    if (!polaca_actual) return -1;
    redimensionar_si_es_necesario(polaca_actual);

    int pos = polaca_actual->tam;
    ElementoPolaca *e = &polaca_actual->elementos[pos];
    e->tipo = POLACA_TIPO_DESTINO;
    e->simbolo = NULL;
    e->operador = NULL;
    e->celda_destino = -1; // aún no resuelta
    e->linea = linea;

    polaca_actual->tam++;
    return pos;
}

void polaca_poner_destino(int celda_a_rellenar, int celda_destino) {
    if (!polaca_actual) return;
    if (celda_a_rellenar < 0 || celda_a_rellenar >= polaca_actual->tam) return;

    polaca_actual->elementos[celda_a_rellenar].tipo = POLACA_TIPO_DESTINO;
    polaca_actual->elementos[celda_a_rellenar].celda_destino = celda_destino;
}

int polaca_posicion_actual(void) {
    if (!polaca_actual) return 0;
    return polaca_actual->tam;
}

/* Pila de Saltos */
void polaca_apilar_salto(int celda) {
    if (tope_saltos >= MAX_SALTOS) {
        fprintf(stderr, "Error interno: Pila de saltos de Polaca desbordada.\n");
        return;
    }
    pila_saltos[tope_saltos++] = celda;
}

int polaca_desapilar_salto(void) {
    if (tope_saltos <= 0) {
        fprintf(stderr, "Error interno: Intento de desapilar de pila de saltos vacía.\n");
        return -1;
    }
    return pila_saltos[--tope_saltos];
}

int polaca_tope_salto(void) {
    if (tope_saltos <= 0) return -1;
    return pila_saltos[tope_saltos - 1];
}

bool polaca_pila_saltos_vacia(void) {
    return tope_saltos == 0;
}

/* Destrucción */
static void destruir_polaca(Polaca *p) {
    if (!p) return;
    free(p->nombre);
    for (int i = 0; i < p->tam; i++) {
        if (p->elementos[i].operador) {
            free(p->elementos[i].operador);
        }
    }
    free(p->elementos);
    free(p);
}

void destruir_gestor_polaca(void) {
    Polaca *curr = lista_polacas;
    while (curr != NULL) {
        Polaca *sig = curr->siguiente;
        destruir_polaca(curr);
        curr = sig;
    }
    lista_polacas = NULL;
    polaca_actual = NULL;
    tope_saltos = 0;
}

/* Visualización */
void imprimir_polaca(Polaca *p) {
    if (!p) return;
    printf("\n------------------------------------------------------------\n");
    printf(" CÓDIGO INTERMEDIO (POLACA INVERSA): [%s]\n", p->nombre);
    printf("------------------------------------------------------------\n");

    if (p->tam == 0) {
        printf(" (vacío)\n");
        printf("------------------------------------------------------------\n");
        return;
    }

    for (int i = 0; i < p->tam; i++) {
        ElementoPolaca *e = &p->elementos[i];
        switch (e->tipo) {
            case POLACA_TIPO_SIMBOLO:
                if (e->simbolo) {
                    // Si es una variable comptime (Tema 22), mostrar su valor numérico resuelto
                    if (e->simbolo->uso == USO_VARIABLE_COMPTIME && e->simbolo->valor_comptime_valido) {
                        if (e->simbolo->tipo == TIPO_INTEGER) {
                            printf("%4d:  %ld$i  (comptime: %s)\n", i, e->simbolo->valor_int, e->simbolo->lexema);
                        } else {
                            printf("%4d:  %.7g  (comptime: %s)\n", i, e->simbolo->valor_float, e->simbolo->lexema);
                        }
                    } else {
                        printf("%4d:  %s\n", i, e->simbolo->lexema ? e->simbolo->lexema : "?");
                    }
                } else {
                    printf("%4d:  (simbolo nulo)\n", i);
                }
                break;

            case POLACA_TIPO_OPERADOR:
                printf("%4d:  %s\n", i, e->operador ? e->operador : "?");
                break;

            case POLACA_TIPO_DESTINO:
                if (e->celda_destino >= 0) {
                    printf("%4d:  [%d]\n", i, e->celda_destino);
                } else {
                    printf("%4d:  [PENDIENTE]\n", i);
                }
                break;
        }
    }
    printf("------------------------------------------------------------\n");
}

void imprimir_todas_las_polacas(void) {
    printf("\n============================================================\n");
    printf("       REPRESENTACIÓN INTERMEDIA: POLACA INVERSA            \n");
    printf("============================================================\n");

    if (lista_polacas == NULL) {
        printf("No se generó código intermedio.\n");
        printf("============================================================\n\n");
        return;
    }

    for (Polaca *p = lista_polacas; p != NULL; p = p->siguiente) {
        imprimir_polaca(p);
    }
    printf("============================================================\n\n");
}
