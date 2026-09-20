#ifndef YYLEX_H
#define YYLEX_H

#include <stdio.h>
#include "tabla_simbolos.h"
#include "y.tab.h"

extern int yylineno;
extern char buffer_lexema[1024];
extern int longitud_lexema;
extern FILE *archivo_fuente;

void init_lexer();

int yylex(void);

void set_lexer_file(FILE *f);

#endif