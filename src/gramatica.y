%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla_simbolos.h"

extern int yylex(void);
extern int yylineno;
int cant_errores = 0;
void yyerror(const char *s);
%}

%union {
    struct Simbolo *simbolo;
    int val_int;
}

%token <simbolo> ID CTE CTE_FLOAT PES_I MULT_STRING

%token ASSIGN GE LE EQ NE

%token IF ELSE END_IF BEGIN END POUT RET CLASS FUNCTION SINGLEF
%token FROM TO BY REPEAT COMPTIME TOSF EXTENDS

%%

programa:
    ID bloque_declarativo bloque_ejecutable ';'
    {
        if (cant_errores == 0) {
            printf("[SINT] Estructura Programa, en línea %d\n", yylineno);
            printf("Sintaxis correcta: Programa reconocido con éxito.\n"); 
        } else {
            printf("Sintaxis incorrecta: finalizado con %d error(es).\n", cant_errores);
        }
    }
  | ID bloque_declarativo BEGIN lista_ejecutables
    { yyerror("Error: Falta el delimitador END al final del bloque ejecutable."); yyerrok; }
  | bloque_declarativo bloque_ejecutable ';'
    { yyerror("Error: Falta el nombre del programa al inicio."); yyerrok; }
;

bloque_declarativo:
    lista_declaraciones
  |
;

lista_declaraciones:
    lista_declaraciones declaracion
  | declaracion
;

declaracion:
    declaracion_variable ';'
  | declaracion_funcion ';'
  | declaracion_clase ';'
  | declaracion_objeto ';'
  | declaracion_comptime ';'
;

declaracion_comptime:
    COMPTIME declaracion_variable
  | COMPTIME lista_variables
    { yyerror("Error: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
;

tipo_dato:
    PES_I
  | SINGLEF
;

declaracion_variable:
    tipo_dato lista_variables
    { printf("[SINT] Estructura Variable, en línea %d\n", yylineno); }
;

lista_variables:
    lista_variables ',' ID
  | ID
;

declaracion_objeto:
    ID lista_variables
    { printf("[SINT] Estructura Objeto, en línea %d\n", yylineno); }
;

declaracion_funcion:
    tipo_dato FUNCTION ID '(' lista_parametros ')' bloque_declarativo bloque_ejecutable
    { printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
  | tipo_dato ID '(' lista_parametros ')' bloque_ejecutable
    { printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); }
  | tipo_dato FUNCTION error '(' lista_parametros ')' bloque_declarativo bloque_ejecutable
    { yyerror("Error: Falta el nombre (identificador) de la función."); yyerrok; }
;

lista_parametros:
    lista_parametros ',' parametro
  | lista_parametros parametro
    { yyerror("Error: Falta de ',' en declaración de parámetros."); yyerrok; }
  | parametro
;

parametro:
    tipo_dato ID
  | tipo_dato
    { yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
;

declaracion_clase:
    CLASS ID codigo_clase encabezado_clase miembros_clase END
    { printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); }
;

codigo_clase:
    ID
  | { yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
;

lista_clase:
    lista_clase ',' ID
  | ID
;

encabezado_clase:
    BEGIN
  | EXTENDS lista_clase BEGIN
  | EXTENDS BEGIN
    { yyerror("Error: Ausencia de nombre o lista de clases después de extends."); yyerrok; }
;

miembros_clase:
    miembros_clase miembro
  | miembro
;

miembro:
    declaracion_variable ';'
  | declaracion_funcion ';'
;

bloque_ejecutable:
    BEGIN lista_ejecutables END
  | error lista_ejecutables END 
    { yyerror("Error: Falta de delimitador de sentencias ejecutables BEGIN."); yyerrok; }
;

lista_ejecutables:
    lista_ejecutables sentencia ';'
  | sentencia ';'
  | lista_ejecutables error ';'
    { yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
  | error ';'
    { yyerror("Error: Sentencia mal formada. Se omitió hasta el ';'."); yyerrok; }
;

sentencia:
    asignacion
  | if_sentencia
  | iteracion
  | impresion
  | sentencia_retorno
;

sentencia_retorno:
    RET '(' expresion_aritmetica ')'
    { printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
  | RET '(' ')'
    { printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
;

asignacion:
    destino ASSIGN expresion_aritmetica
    { printf("[SINT] Estructura ASSIGN, en línea %d\n", yylineno); }
  | destino '=' expresion_aritmetica
    { yyerror("Error: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
;

destino:
    ID
  | ID '.' ID
  | ID '[' expresion_aritmetica ']'
;

impresion:
    POUT '(' expresion_aritmetica ')'
    { printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
  | POUT '(' MULT_STRING ')'
    { printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
  | POUT '(' ')'
    { yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
  | POUT error
    { yyerror("Error: Falta argumento en sentencia pout."); yyerrok; }
;

expresion_aritmetica:
    expresion_aritmetica '+' termino
  | expresion_aritmetica '-' termino
  | expresion_aritmetica '+' error 
    { yyerror("Error: Falta operando en la expresión después de '+'."); yyerrok; }
  | expresion_aritmetica '-' error 
    { yyerror("Error: Falta operando en la expresión después de '-'."); yyerrok; }
  | termino
;

termino:
    termino '*' operando
  | termino '/' operando
  | termino '*' error 
    { yyerror("Error: Falta operando en la expresión después de '*'."); yyerrok; }
  | termino '/' error 
    { yyerror("Error: Falta operando en la expresión después de '/'."); yyerrok; }
  | operando
;

operando:
    ID
  | ID '.' ID
  | ID '[' expresion_aritmetica ']'
  | ID '(' parametros_reales ')' orden_evaluacion
  | ID '.' ID '(' parametros_reales ')' orden_evaluacion
  | TOSF '(' expresion_aritmetica ')'
  | constante_con_signo
;

orden_evaluacion:
    '[' lista_enteros ']'
  | '[' error ']'
    { yyerror("Error: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
  |
;

lista_enteros:
    lista_enteros ',' CTE
  | CTE
;

parametros_reales:
    lista_parametros_reales
  |
;

lista_parametros_reales:
    lista_parametros_reales ',' parametro_real
  | parametro_real
;

parametro_real:
    expresion_aritmetica
  | ID '=' expresion_aritmetica
;

constante_con_signo:
    CTE
    {
        if ($1 != NULL) {
            long valor = strtol($1->lexema, NULL, 10);
            if (valor > 32767) {
                printf("\nLínea %d: Error: La constante entera positiva '%s' excede el rango máximo permitido [32767]\n\n", yylineno, $1->lexema);
            }
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "+%s", $1->lexema);
            modificar_lexema($1, nuevo);
            printf("[SINT] Constante entera positiva, lexema actualizado a: '%s' en línea %d\n", $1->lexema, yylineno);
        }
    }
  | CTE_FLOAT
    {
        if ($1 != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "+%s", $1->lexema);
            modificar_lexema($1, nuevo);
            printf("[SINT] Constante float positiva, lexema actualizado a: '%s' en línea %d\n", $1->lexema, yylineno);
        }
    }
  | '+' CTE
    {
        if ($2 != NULL) {
            long valor = strtol($2->lexema, NULL, 10);
            if (valor > 32767) {
                printf("\nLínea %d: Error: La constante entera positiva '+%s' excede el rango máximo permitido [32767]\n\n", yylineno, $2->lexema);
            }
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "+%s", $2->lexema);
            modificar_lexema($2, nuevo);
            printf("[SINT] Constante entera positiva (+), lexema actualizado a: '%s' en línea %d\n", $2->lexema, yylineno);
        }
    }
  | '+' CTE_FLOAT
    {
        if ($2 != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "+%s", $2->lexema);
            modificar_lexema($2, nuevo);
            printf("[SINT] Constante float positiva (+), lexema actualizado a: '%s' en línea %d\n", $2->lexema, yylineno);
        }
    }
  | '-' CTE
    {
        if ($2 != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "-%s", $2->lexema);
            modificar_lexema($2, nuevo);
            printf("[SINT] Constante entera negativa, lexema actualizado a: '%s' en línea %d\n", $2->lexema, yylineno);
        }
    }
  | '-' CTE_FLOAT
    {
        if ($2 != NULL) {
            char nuevo[1024];
            snprintf(nuevo, sizeof(nuevo), "-%s", $2->lexema);
            modificar_lexema($2, nuevo);
            printf("[SINT] Constante float negativa, lexema actualizado a: '%s' en línea %d\n", $2->lexema, yylineno);
        }
    }
;

if_sentencia:
    IF '(' condicion ')' bloque_o_sentencia fin_if
    { printf("[SINT] Estructura IF, en línea %d\n", yylineno); }
  | IF condicion ')' bloque_o_sentencia fin_if
    { yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
  | IF '(' condicion bloque_o_sentencia fin_if
    { yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
  | IF '(' condicion ')' bloque_o_sentencia error
    { yyerror("Error: Estructura IF mal cerrada (posiblemente falta END_IF o el delimitador ';')."); yyerrok; }
;

fin_if:
    ELSE bloque_o_sentencia END_IF
    { printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); }
  | END_IF
;

iteracion:
    encabezado_iteracion cuerpo_iteracion REPEAT
    { printf("[SINT] Estructura ITERACION, en línea %d\n", yylineno); }
  | encabezado_iteracion error REPEAT
    { yyerror("Error: Falta o hay un error en el cuerpo de la iteración."); yyerrok; }
;

encabezado_iteracion:
    FROM ID '=' constante_con_signo TO constante_con_signo BY constante_con_signo
  | FROM '(' condicion ')'
  | FROM '=' constante_con_signo TO constante_con_signo BY constante_con_signo
    { yyerror("Error: Falta identificador (ID) en el encabezado."); yyerrok; }
  | FROM ID '=' constante_con_signo constante_con_signo
    { yyerror("Error: Falta 'TO' en el encabezado de la iteración."); yyerrok; }
  | FROM condicion ')'
    { yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
  | FROM '(' condicion
    { yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
  | FROM ID '=' TO
    { yyerror("Error: Falta CTE en el encabezado."); yyerrok; }
;

cuerpo_iteracion:
    bloque_o_sentencia
;

bloque_o_sentencia:
    bloque_ejecutable
  | sentencia
;

condicion:
    expresion_aritmetica operador_relacional expresion_aritmetica
;

operador_relacional:
    '<'
  | '>'
  | GE
  | LE
  | EQ
  | NE
;

%%

void yyerror(const char *s) {
    const char *COLOR_ROJO = "\033[1;31m";
    const char *COLOR_AMARILLO = "\033[1;33m";
    const char *COLOR_RESET = "\033[0m";

    if (strncmp(s, "syntax error", 12) == 0) {
        return; 
    }

    if (strstr(s, "Sentencia mal formada") != NULL) {
        cant_errores++; 
        fprintf(stderr, "%s[ERROR DE SINTAXIS]%s %sLínea %d:%s Sentencia inválida. Es posible que falte un delimitador estructural (como 'END_IF' o ';') o un operador.\n", 
                COLOR_ROJO, COLOR_RESET, COLOR_AMARILLO, yylineno, COLOR_RESET);
        return;
    }

    cant_errores++;
    const char *mensaje = (strncmp(s, "Error: ", 7) == 0) ? s + 7 : s;
    
    fprintf(stderr, "%s[ERROR DE SINTAXIS]%s %sLínea %d:%s %s\n", 
            COLOR_ROJO, COLOR_RESET, COLOR_AMARILLO, yylineno, COLOR_RESET, mensaje);
}