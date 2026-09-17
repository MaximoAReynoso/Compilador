%{
#include <stdio.h>
#include <stdlib.h>
#include "tabla_simbolos.h"

extern int yylex(void);
extern int yylineno;
void yyerror(const char *s);
%}

%union {
    Simbolo *simbolo;
    int val_int;
}

/* Tokens con puntero a la Tabla de Símbolos */
%token <simbolo> ID CTE CTE_FLOAT PES_I MULT_STRING

/* Operadores y Comparadores */
%token ASSIGN_COLON ASSIGN GE LE GT LT EQ NE

/* Palabras reservadas */
%token IF ELSE END_IF BEGIN END POUT RET CLASS FUNCTION SINGLEF

%token FROM TO BY REPEAT COMPTIME TOSF

%%

programa:
    ID bloque_declarativo BEGIN bloque_ejecutable END
    { printf("Sintaxis correcta: Programa reconocido con éxito.\n"); }
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

tipo_dato:
    SINGLEF
;

declaracion_variable:
    tipo_dato lista_variables
;

lista_variables:
    lista_variables ',' ID
  | ID
;

declaracion_objeto:
    ID lista_variables
;

declaracion_funcion:
    tipo_dato FUNCTION ID '(' lista_parametros ')' bloque_declarativo BEGIN bloque_ejecutable END
  | tipo_dato ID '(' lista_parametros ')' BEGIN bloque_ejecutable END
;

lista_parametros:
    lista_parametros ',' parametro
  | parametro
;

parametro:
    tipo_dato ID
;

declaracion_clase:
    CLASS ID encabezado_clase miembros_clase END
;

encabezado_clase:
    BEGIN
  |
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
    lista_asignaciones asignacion
;

lista_asignaciones:
    asignacion'(' lista_parametros ')'
  | 
;

asignacion:
    ID ASSIGN expresion_aritmetica
;

expresion_aritmetica:
    operando operador expresion_aritmetica
  | operando 
;

operando:
    ID                                           /* Variable */
  | ID '(' parametros_reales ')'             /* invocacion a funcion */
  | referencia
  |                                             /* falta constantes u otras expresiones aritméticas */
;

parametros_reales:
    parametros_reales parametro_real
  | parametro_real
;

parametro_real:
    ID
  | expresion_aritmetica
  |                                        /* falta constante */
;

referencia:
    ID '.' ID '=' constante
;

constante:
    /* no se que poner */
;








%%