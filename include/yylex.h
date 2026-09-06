#ifndef YYLEX_H
#define YYLEX_H

#include <stdio.h>

void init_lexer();

int yylex();

void set_lexer_file(FILE *f);

#endif