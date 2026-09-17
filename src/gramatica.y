%{
#include <stdio.h>
#include <stdlib.h>
#include "tabla_simbolos.h"

extern int yylex(void);
extern int yylineno;
void yyerror(const char *s);
%}

%union {
    struct Simbolo *simbolo;
    int val_int;
}

/* Tokens con puntero a la Tabla de Símbolos */
%token <simbolo> ID CTE CTE_FLOAT PES_I MULT_STRING

/* Operadores y Comparadores */
%token ASSIGN GE LE EQ NE

/* Palabras reservadas */
%token IF ELSE END_IF BEGIN END POUT RET CLASS FUNCTION SINGLEF

%token FROM TO BY REPEAT COMPTIME TOSF

%%

programa:
    ID { printf("[SINT] Estructura Programa, en línea %d\n", yylineno);} bloque_declarativo BEGIN bloque_ejecutable END ';'
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
  | ID { printf("[SINT] Estructura Variable, en línea %d\n", yylineno); }
;

declaracion_objeto:
    ID { printf("[SINT] Estructura Objeto, en línea %d\n", yylineno); } lista_variables
;

declaracion_funcion:
    tipo_dato FUNCTION ID '(' lista_parametros ')' { printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); } bloque_declarativo BEGIN bloque_ejecutable END
  	| tipo_dato ID '(' lista_parametros ')' { printf("[SINT] Estructura FUNCTION, en línea %d\n", yylineno); } BEGIN bloque_ejecutable END
;

lista_parametros:
    lista_parametros ',' parametro
  | parametro
;

parametro:
    tipo_dato ID
;

declaracion_clase:
    CLASS ID { printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); } codigo_clase encabezado_clase miembros_clase END
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
	{ printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
  | RET '(' ')'
  { printf("[SINT] Estructura RET, en línea %d\n", yylineno); }
;

asignacion:
    destino ASSIGN { printf("[SINT] Estructura ASSIGN, en línea %d\n", yylineno); } expresion_aritmetica
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
    IF '(' condicion ')' { printf("[SINT] Estructura IF, en línea %d\n", yylineno); } bloque_o_sentencia rama_else END_IF
;

rama_else:
    ELSE { printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); } bloque_o_sentencia
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
	'<'
  | '>'
  | GE
  | LE
  | EQ
  | NE
;

impresion:
    POUT '(' expresion_aritmetica ')'
	{ printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
  | POUT '(' MULT_STRING ')'
    { printf("[SINT] Estructura POUT, en línea %d\n", yylineno); }
;

%%