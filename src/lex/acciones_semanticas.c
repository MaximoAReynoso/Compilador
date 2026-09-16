#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

#include "yylex.h"
#include "tokens.h"
#include "acciones_semanticas.h"
#include "tabla_simbolos.h"

static TablaSimbolos *tabla_actual;
#define MAX_LONG_ID 22
#define MAX_INT_CTE 32768


void establecer_tabla_simbolos(TablaSimbolos *tabla) {
    tabla_actual = tabla;
}

int as_count_line(int c, char *buffer, int *len){
    numero_linea++;
    *len = 0;
    buffer[0] = '\0';
    return 0;
};

int as_consume(int c, char *buffer, int *len){
    return 0;
};

int as_consume_comment(int c, char *buffer, int *len){
    *len = 0;
    buffer[0] = '\0';
    numero_linea++;
    printf("\n");
    return 0;
};

int as_add_to_buffer(int c, char *buffer, int *len){
    if( c == '\n')
    numero_linea++;
    if (*len < 1023){
        buffer[*len] = c;
        (*len)++;
        buffer[*len] = '\0';
    }
    printf("Se retorna as_add_to_buffer:%c \n", c);
    return 0;
}


int as_retract_and_emit(int c, char *buffer, int *len) {
    yylval = NULL;
    if (c != EOF) {
        ungetc(c, archivo_fuente);
    }

    int caracter = buffer[*len -1]; //buffer[0]

    *len = 0;
    buffer[0] = '\0';
    if (c != EOF) {
        printf("Se retorna as_retract_and_emit:%c \n", c);
    } else {
        printf("Se retorna as_retract_and_emit: EOF\n");
    }
    return caracter;
}

int as_classify_and_emit(int c, char *buffer, int *len){
    yylval = NULL;
    printf("Se retorna as_classify_and_emit:%c \n", c);
    return c;
}

int as_emit_token_FLOAT(int c, char *buffer, int *len){
    ungetc(c, archivo_fuente);

    char buffer_aux[1024];
    strncpy(buffer_aux, buffer, sizeof(buffer_aux) - 1);
    buffer_aux[sizeof(buffer_aux) - 1] = '\0';

    for (int i = 0; buffer_aux[i] != '\0'; i++) { //se cambia s por e, debido a que strtof tiene de estandar un e en vez de s
        if (buffer_aux[i] == 's' || buffer_aux[i] == 'S') {
            buffer_aux[i] = 'e';
        }
    }

    char *ptr;
    errno=0;
    float valor = strtof(buffer_aux, &ptr);

    if (valor != 0.0f) {
            if (errno == ERANGE || valor < FLT_MIN) {
                printf("Error lexico [Línea %d]: Underflow en constante float '%s' (menor a %e)\n", numero_linea, buffer, FLT_MIN);
                *len = 0;
                buffer[0] = '\0';
                return -1;
            }

            if (valor > FLT_MAX) {
                printf("Error lexico [Línea %d]: Overflow en constante float '%s' (mayor a %e)\n",
                       numero_linea, buffer, FLT_MAX);
                *len = 0;
                buffer[0] = '\0';
                return -1;
            }
    }

    if (c != EOF) {
        ungetc(c, archivo_fuente);
    }
    yylval = insertar_simbolo(tabla_actual, buffer, CTE_FLOAT, numero_linea);
    
    *len = 0;
    buffer[0] = '\0';
    if (c != EOF) {
        printf("Se retorna as_emit_token_FLOAT:%c \n", c);
    } else {
        printf("Se retorna as_emit_token_FLOAT: EOF\n");
    }
    return CTE_FLOAT;
};

int as_emit_token_INT(int c, char *buffer, int *len){

    errno = 0;

    char *ptr;
    
    long valor = strtoll(buffer,&ptr, 10);

    if (errno == ERANGE) {// captura del error causado por C
        char *mensaje_error_c = strerror(errno); 
        printf("Error lexico [Línea %d]: Fallo en '%s' -> C reporta: \"%s\"\n", numero_linea, buffer, mensaje_error_c);
        *len = 0;
        buffer[0] = '\0';
        return -1;
    }

    // asumo que todos los valores son positivos
    if(valor > MAX_INT_CTE){ // c== 32768, asumo que es negativo
        printf("Error lexico [Línea %d]: El valor '%ld'excede el rango de 16 bits [%d]\n", numero_linea, valor,MAX_INT_CTE);
        *len = 0;
        buffer[0] = '\0';
        return -1;
    }
    
    buffer[*len] = 'i';
    (*len)++;
    buffer[*len] = '\0';
    yylval = insertar_simbolo(tabla_actual, buffer, PES_I, numero_linea);
    *len = 0;
    buffer[0] = '\0';
    printf("Se retorna as_emit_token_INT:%c \n", c);
    return PES_I;
}

int as_emit_token_ASIG(int c, char *buffer, int *len){
    yylval = NULL;
    *len = 0;
    buffer[0] = '\0';
    printf("Se retorna as_emit_token_ASIG:%c \n", c);
    return ASSIGN;
}

int as_emit_token_NEQ(int c, char *buffer, int *len){
    yylval = NULL;
    *len = 0;
    buffer[0] = '\0';
    printf("Se retorna as_emit_token_NEQ:%c \n", c);
    return NE;
}

int as_emit_token_comp(int c, char *buffer, int *len){
    yylval = NULL;
    int value = 0;
    if (buffer[0] == '=') {
        value = EQ;
    } else if (buffer[0] == '<') {
        value = LE;
    } else if (buffer[0] == '>') {
        value = GE;
    }
    *len = 0;
    buffer[0] = '\0';
    printf("Se retorna as_emit_token_comp:%c \n", c);
    return value;
}

int as_emit_token_string(int c, char *buffer, int *len){
    int j = 0; 
    for (int i = 0; buffer[i] != '\0'; i++) { // elimino los saltos de limnea 
        if (buffer[i] != '\n' && buffer[i] != '\r') {
            buffer[j++] = buffer[i];
        }
    }
    buffer[j++] = '"';// comilla de cierre
    buffer[j] = '\0';
    *len = j;

    yylval = insertar_simbolo(tabla_actual, buffer, MULT_STRING, numero_linea);
    *len = 0;
    buffer[0] = '\0';
    printf("Se retorna :%c \n", c);
    return MULT_STRING;
}

bool id_valido(char *buffer) {
    // Verificar que el primer carácter sea una letra o un guion bajo
    if (!(buffer[0] >= 'a' && buffer[0] <= 'z')) {
        return false;
    }

    // Verificar que los caracteres restantes sean letras, dígitos o guiones bajos
    for (int i = 1; buffer[i] != '\0'; i++) {
        if (!((buffer[i] >= 'a' && buffer[i] <= 'z') ||
              (buffer[i] >= '0' && buffer[i] <= '9') ||
              buffer[i] == '_')) {
            return false;
        }
    }

    return true;
}

int as_PR_IDENT(int c, char *buffer, int *len){
    if (c != EOF) {
        ungetc(c, archivo_fuente);    //retraer caracter que trajo a este estado
    }

    char *cadena = buffer;

    for (int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] = (char)tolower((unsigned char)cadena[i]);
    }
    printf(" \n as_PR_IDENT");
    yylval = NULL;
    if (strcmp(cadena, "if") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return IF;
    } else if (strcmp(cadena, "else") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return ELSE;
    } else if (strcmp(cadena, "end_if") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return END_IF;
    } else if (strcmp(cadena, "begin") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return BEGIN;
    } else if (strcmp(cadena, "end") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return END;
    } else if (strcmp(cadena, "pout") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return POUT;
    } else if (strcmp(cadena, "ret") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return RET;
    } else if (strcmp(cadena, "class") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return CLASS;
    } else if (strcmp(cadena, "function") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return FUNCTION;
    } else if (strcmp(cadena, "from") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return FROM;
    } else if (strcmp(cadena, "to") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return TO;
    } else if (strcmp(cadena, "by") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return BY;
    } else if (strcmp(cadena, "repeat") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return REPEAT;
    } else if (strcmp(cadena, "comptime") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return COMPTIME;
    } else if (strcmp(cadena, "tosf") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return TOSF;
    } else if(strcmp(cadena,"singlef") == 0){
        *len = 0;
        buffer[0] = '\0';
        return SINGLEF; 
    }else {
        if (id_valido(buffer)) {
            if(strlen(buffer) > MAX_LONG_ID){
                printf("WARNING (linea %d): El identificador (%s) supera los %d caracteres. Se trunco a '%.*s'. \n", 
                                numero_linea, buffer, MAX_LONG_ID,MAX_LONG_ID,buffer);
                buffer[MAX_LONG_ID] = '\0'; //trunca
                *len = MAX_LONG_ID;
            }
            yylval = insertar_simbolo(tabla_actual, buffer, ID, numero_linea);
            *len = 0;
            buffer[0] = '\0';
            return ID;
        }
    }
    //limpio el buffer
    *len = 0;
    buffer[0] = '\0';
    return ID;
}