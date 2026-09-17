%{
#include <stdio.h>
#include <stdlib.h>
#include "tabla_simbolos.h"

extern int yylex(void);
void yyerror(const char *s);
%}

%union {
    struct Simbolo *simbolo;
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
    ID bloque_declarativo BEGIN bloque_ejecutable END ';'
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
  | declaracion_comptime ';'
;

declaracion_comptime:
    COMPTIME declaracion_variable
;

tipo_dato:
  PES_I
  | SINGLEF
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
    CLASS ID codigo_clase encabezado_clase miembros_clase END
;

codigo_clase:
    ID
  | 
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
    lista_ejecutables
  | 
;

lista_ejecutables:
    lista_ejecutables sentencia ';'
  | sentencia ';'
;

sentencia:
    asignacion
  | if_sentencia
  | impresion
  | sentencia_retorno
;

sentencia_retorno:
    RET '(' expresion_aritmetica ')'
  | RET '(' ')'
;

asignacion:
    destino ASSIGN expresion_aritmetica
  | destino ASSIGN_COLON expresion_aritmetica
;

destino:
    ID
  | ID '.' ID
  | ID '[' expresion_aritmetica ']'
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
  | constante
;

orden_evaluacion:
    '[' lista_enteros ']'
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

constante:
    CTE
  | CTE_FLOAT
;

if_sentencia:
    IF '(' condicion ')' bloque_o_sentencia rama_else END_IF
;

rama_else:
    ELSE bloque_o_sentencia
  | 
;

bloque_o_sentencia:
    BEGIN bloque_ejecutable END
  | sentencia
;

condicion:
    expresion_aritmetica operador_relacional expresion_aritmetica
;

operador_relacional:
    GT
  | LT
  | GE
  | LE
  | EQ
  | NE
;

impresion:
    POUT '(' expresion_aritmetica ')'
  | POUT '(' MULT_STRING ')'
;

%%