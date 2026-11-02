#!/bin/bash
byacc -v -d src/gramatica.y && mv y.tab.c src/ && mv y.tab.h include/
gcc -Wall -Wextra src/main.c src/y.tab.c src/lex/yylex.c src/lex/acciones_semanticas.c src/tabla_simbolos.c src/polaca.c src/errores.c -Iinclude -o compilador