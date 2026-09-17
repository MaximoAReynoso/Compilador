#ifndef ACCIONES_SEMANTICAS_H
#define ACCIONES_SEMANTICAS_H

#include <stdio.h>
#include <stdbool.h> //libreria necesaria

#include "tabla_simbolos.h"

void establecer_tabla_simbolos(TablaSimbolos *tabla);

int as_count_line(int c, char *buffer, int *len);   // cuenta lineas

int as_consume(int c, char *buffer, int *len);

int as_consume_comment(int c, char *buffer, int *len);

int as_add_to_buffer(int c, char *buffer, int *len);

int as_retract_and_emit(int c, char *buffer, int *len);

int as_retract_and_emit_dot(int c, char *buffer, int *len);

int as_classify_and_emit(int c, char *buffer, int *len);

int as_emit_token_FLOAT(int c, char *buffer, int *len);

int as_emit_token_INT(int c, char *buffer, int *len);

int as_emit_token_ASIG(int c, char *buffer, int *len);

int as_emit_token_NEQ(int c, char *buffer, int *len);

int as_emit_token_comp(int c, char *buffer, int *len);

int as_emit_token_string(int c, char *buffer, int *len);

bool id_valido(char *buffer);

int as_PR_IDENT(int c, char *buffer, int *len);


#endif