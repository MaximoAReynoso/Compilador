%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla_simbolos.h"

extern int yylex(void);
extern int yylineno;
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
        printf("[SINT] Estructura Programa, en línea %d\n", yylineno);
        printf("Sintaxis correcta: Programa reconocido con éxito.\n"); 
    }
  | error bloque_declarativo bloque_ejecutable ';'
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
  | lista_parametros error parametro 
    { yyerror("Error: Falta de “,” en declaración de variables."); yyerrok; }
  | parametro
;

parametro:
    tipo_dato ID
  | tipo_dato error
    { yyerror("Error: Falta el nombre del parámetro formal en la función."); yyerrok; }
  | error ID
    { yyerror("Error: Falta el tipo del parámetro formal en la función."); yyerrok; }
;

declaracion_clase:
    CLASS ID codigo_clase encabezado_clase miembros_clase END
    { printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); }
  | CLASS ID error encabezado_clase miembros_clase END
    { yyerror("Error: Ausencia del código en la declaración de la clase."); yyerrok; }
;

codigo_clase:
    ID
  |
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
    { yyerror("Error: Falta ';' al final de la sentencia o error en sentencia."); yyerrok; }
  | error ';'
    { yyerror("Error: Falta ';' al final de la sentencia."); yyerrok; }
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
  | termino
;

termino:
    termino '*' operando
  | termino '/' operando
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
  | IF error condicion ')' bloque_o_sentencia fin_if
    { yyerror("Error: Falta '(' en la condición de selección."); yyerrok; }
  | IF '(' condicion error bloque_o_sentencia fin_if
    { yyerror("Error: Falta ')' en la condición de selección."); yyerrok; }
;

fin_if:
    rama_else END_IF
  | rama_else error
    { yyerror("Error: Falta 'END_IF' al cerrar la estructura IF."); yyerrok; }
;

rama_else:
    ELSE bloque_o_sentencia
    { printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); }
  |
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
  | FROM error '=' constante_con_signo TO constante_con_signo BY constante_con_signo
    { yyerror("Error: Falta identificador (ID) en el encabezado de la iteración."); yyerrok; }
  | destino '=' constante_con_signo TO constante_con_signo BY constante_con_signo
    { yyerror("Error: Falta palabra clave 'FROM' en el encabezado de la iteración."); yyerrok; }
  | FROM ID '=' constante_con_signo constante_con_signo BY constante_con_signo
    { yyerror("Error: Falta 'TO' o constante en el encabezado de la iteración."); yyerrok; }
  | FROM error condicion ')'
    { yyerror("Error: Falta '(' en la condición de la iteración."); yyerrok; }
  | FROM '(' condicion error
    { yyerror("Error: Falta ')' en la condición de la iteración."); yyerrok; }
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
  if (strcmp(s, "syntax error") == 0) {
    fprintf(stderr, "\nLínea %d: Error sintáctico en la entrada.\n", yylineno);
    return;
  }

  fprintf(stderr, "\nLínea %d: %s\n", yylineno, s);
}