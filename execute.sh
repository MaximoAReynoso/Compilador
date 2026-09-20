byacc -v -d src/gramatica.y && mv y.tab.c src/ && mv y.tab.h include/
gcc -Wall -Wextra src/main.c src/lex/yylex.c src/lex/acciones_semanticas.c src/tabla_simbolos.c -Iinclude -o compilador