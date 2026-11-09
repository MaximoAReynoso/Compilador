#ifndef POLACA_H
#define POLACA_H

#include "tabla_simbolos.h"
#include <stdbool.h>

typedef enum {
    POLACA_TIPO_SIMBOLO,
    POLACA_TIPO_OPERADOR,
    POLACA_TIPO_DESTINO
} TipoElementoPolaca;

typedef struct ElementoPolaca {
    TipoElementoPolaca tipo;
    Simbolo *simbolo;
    char *operador;
    int celda_destino;
    int linea;
} ElementoPolaca;

typedef struct Polaca {
    char *nombre;
    ElementoPolaca *elementos;
    int tam;
    int capacidad;
    struct Polaca *siguiente;
} Polaca;

/* Gestión de polacas */
void inicializar_gestor_polaca(void);
void destruir_gestor_polaca(void);
Polaca *crear_polaca(const char *nombre);
Polaca *obtener_lista_polacas(void);
void establecer_polaca_actual(Polaca *p);
Polaca *obtener_polaca_actual(void);
Polaca *obtener_polaca_por_nombre(const char *nombre);
void polaca_apilar_actual(Polaca *p);
void polaca_desapilar_actual(void);

/* Emisión */
int polaca_emitir_simbolo(Simbolo *s, int linea);
int polaca_emitir_operador(const char *op, int linea);
int polaca_emitir_celda_vacia(int linea);
void polaca_poner_destino(int celda_a_rellenar, int celda_destino);
int polaca_posicion_actual(void);

/* Pila de saltos para backpatching */
void polaca_apilar_salto(int celda);
int polaca_desapilar_salto(void);
int polaca_tope_salto(void);
bool polaca_pila_saltos_vacia(void);

/* Impresión */
void imprimir_polaca(Polaca *p);
void imprimir_todas_las_polacas(void);

#endif
