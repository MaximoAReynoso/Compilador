#ifndef actions_semanticas_h
#define actions_semanticas_h

#include <stdio.h>

void as_count_line(int c, char *buffer, int *len);   // cuenta lineas

void as_consume(int c, char *buffer, int *len);

void as_consume_comment(int c, char *buffer, int *len);

void as_add_to_buffer(int c, char *buffer, int *len);

void as_emit_token_string(int c, char *buffer, int *len);

void as_emit_token_NEQ(int c, char *buffer, int *len);

void as_emit_token_comp(int c, char *buffer, int *len);

void as_emit_token_ASIG(int c, char *buffer, int *len);

void as_retract_and_emit(int c, char *buffer, int *len);

void as_PR_IDENT(int c, char *buffer, int *len);

void as_classify_and_emit(int c, char *buffer, int *len);

void as_emit_token_FLOAT(int c, char *buffer, int *len);

void as_emit_token_INT(int c, char *buffer, int *len);