#ifndef YYLEX_H
#define YYLEX_H

#include <stdio.h>

extern int numero_linea;
extern char buffer_lexema[1024];
extern int longitud_lexema;

void init_lexer();

int yylex();

void set_lexer_file(FILE *f);

#endif