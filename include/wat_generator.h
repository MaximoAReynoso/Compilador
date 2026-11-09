#ifndef WAT_GENERATOR_H
#define WAT_GENERATOR_H

#include <stdbool.h>
#include "tabla_simbolos.h"
#include "polaca.h"

/* Genera código WebAssembly (WAT) con variables auxiliares */
bool generar_codigo_wat(TablaSimbolos *tabla, const char *archivo_salida);

#endif
