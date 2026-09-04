#include <stdio.h>
#include <stdlib.h>

#define STRING_MULTIPLINEA 257
#define COMENTARIO 258
#define SUMA 259


int yylex(FILE *file){
    if (file == NULL){
        perror("Error archivo inexistente");
        return -1;
    }

    int c;
    while ((c = fgetc(file)) != EOF){
        
    }
    
    return 0;
}