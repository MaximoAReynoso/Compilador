#include <stdbool.h>

#include "yylex.h"
#include "tokens.h"
#include "acciones_semanticas.h"
#include "tabla_simbolos.h"

static TablaSimbolos *tabla_actual;

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

    return 0;
};

int as_add_to_buffer(int c, char *buffer, int *len){
    buffer[*len] = c;
    (*len)++;
    buffer[*len] = '\0';
}


int as_retract_and_emit(int c, char *buffer, int *len) {
    //yylval = NULL;
    ungetc(c, archivo_fuente);

    int caracter = buffer[*len];

    *len = 0;
    buffer[0] = '\0';

    return caracter;
}

int as_classify_and_emit(int c, char *buffer, int *len){
    //yylval = NULL;
    return c;
}

int as_emit_token_FLOAT(int c, char *buffer, int *len){
    //yylval = insertar_simbolo(tabla_actual, buffer, SINGLEF, numero_linea);
    ungetc(c, archivo_fuente);
    *len = 0;
    buffer[0] = '\0';
    return SINGLEF;
};

int as_emit_token_INT(int c, char *buffer, int *len){
    buffer[*len] = 'i';
    (*len)++;
    buffer[*len] = '\0';
    //yylval = insertar_simbolo(tabla_actual, buffer, PES_I, numero_linea);
    *len = 0;
    buffer[0] = '\0';
    return PES_I;
}

int as_emit_token_ASIG(int c, char *buffer, int *len){
    //yylval = NULL;
    *len = 0;
    buffer[0] = '\0';
    return ASSIGN;
}

int as_emit_token_NEQ(int c, char *buffer, int *len){
    //yylval = NULL;
    *len = 0;
    buffer[0] = '\0';
    return NE;
}

int as_emit_token_comp(int c, char *buffer, int *len){
    //yylval = NULL;
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
    return value;
}

int as_emit_token_string(int c, char *buffer, int *len){
    //yylval = insertar_simbolo(tabla_actual, buffer, MULT_STRING, numero_linea);
    *len = 0;
    buffer[0] = '\0';
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
    ungetc(c, archivo_fuente);    //retraer caracter que trajo a este estado

    char *cadena = buffer;

    for (int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] = (char)tolower((unsigned char)cadena[i]);
    }


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
    } else if (strcmp(cadena, "funct") == 0) {
        *len = 0;
        buffer[0] = '\0';
        return FUNCT;
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
    } else {
        if (id_valido(buffer)) {
            //yylval = insertar_simbolo(tabla_actual, buffer, ID, numero_linea);
            *len = 0;
            buffer[0] = '\0';
            return ID;
        }
    }
    return ID;
}