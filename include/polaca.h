#ifndef POLACA_H
#define POLACA_H

#include "tabla_simbolos.h"
#include <stdbool.h>

typedef enum {
    POLACA_TIPO_SIMBOLO,        // Referencia a un símbolo de la Tabla de Símbolos
    POLACA_TIPO_OPERADOR,       // Operador (+, -, :=, etc.) o comando (BF, BI, POUT, RET, CALL)
    POLACA_TIPO_DESTINO         // Celda / dirección de salto numérico
} TipoElementoPolaca;

typedef struct ElementoPolaca {
    TipoElementoPolaca tipo;
    Simbolo *simbolo;           // Si tipo == POLACA_TIPO_SIMBOLO
    char *operador;             // Si tipo == POLACA_TIPO_OPERADOR
    int celda_destino;          // Si tipo == POLACA_TIPO_DESTINO
    int linea;                  // Línea del código fuente asociada
} ElementoPolaca;

typedef struct Polaca {
    char *nombre;               // "main", o nombre de función ("calcular:mi_prog")
    ElementoPolaca *elementos;  // Arreglo dinámico de celdas
    int tam;                    // Cantidad actual de elementos
    int capacidad;              // Capacidad reservada
    struct Polaca *siguiente;   // Para encadenar polacas de distintas funciones
} Polaca;

/* Inicialización y limpieza del módulo */
void inicializar_gestor_polaca(void);
void destruir_gestor_polaca(void);

/* Creación y selección de la polaca activa (main o funciones) */
Polaca *crear_polaca(const char *nombre);
void establecer_polaca_actual(Polaca *p);
Polaca *obtener_polaca_actual(void);
Polaca *obtener_polaca_por_nombre(const char *nombre);
void polaca_apilar_actual(Polaca *p);
void polaca_desapilar_actual(void);

/* Emisión de elementos en la polaca activa */
int polaca_emitir_simbolo(Simbolo *s, int linea);
int polaca_emitir_operador(const char *op, int linea);
int polaca_emitir_celda_vacia(int linea);
void polaca_poner_destino(int celda_a_rellenar, int celda_destino);
int polaca_posicion_actual(void);

/* Pila de saltos para backpatching (IF, ELSE, FROM, etc.) */
void polaca_apilar_salto(int celda);
int polaca_desapilar_salto(void);
int polaca_tope_salto(void);
bool polaca_pila_saltos_vacia(void);

/* Visualización del código intermedio según los requisitos de entrega */
void imprimir_polaca(Polaca *p);
void imprimir_todas_las_polacas(void);

#endif
