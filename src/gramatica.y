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

%token <simbolo> ID CTE CTE_FLOAT PES_I MULT_STRING

%token ASSIGN GE LE EQ NE

%token IF ELSE END_IF BEGIN END POUT RET CLASS FUNCTION SINGLEF
%token FROM TO BY REPEAT COMPTIME TOSF EXTENDS

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

programa:
    ID { printf("[SINT] Estructura Programa, en línea %d\n", yylineno); } bloque_declarativo BEGIN bloque_ejecutable END ';'
    { printf("Sintaxis correcta: Programa reconocido con éxito.\n"); }
  | error bloque_declarativo BEGIN bloque_ejecutable END ';'
    { yyerror("Error sintáctico: Falta el nombre del programa al inicio."); yyerrok; }
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
    { yyerror("Error sintáctico: Falta el tipo de dato en la declaración COMPTIME."); yyerrok; }
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
  | tipo_dato FUNCTION error '(' lista_parametros ')' bloque_declarativo BEGIN bloque_ejecutable END
    { yyerror("Error sintáctico: Falta el nombre (identificador) de la función."); yyerrok; }
;

lista_parametros:
    lista_parametros ',' parametro
  | parametro
;

parametro:
    tipo_dato ID
  | tipo_dato error
    { yyerror("Error sintáctico: Falta el nombre del parámetro formal en la función."); yyerrok; }
  | error ID
    { yyerror("Error sintáctico: Falta el tipo del parámetro formal en la función."); yyerrok; }
;

declaracion_clase:
    CLASS ID { printf("[SINT] Estructura CLASS, en línea %d\n", yylineno); } codigo_clase encabezado_clase miembros_clase END
  | CLASS ID error encabezado_clase miembros_clase END
    { yyerror("Error sintáctico: Ausencia del código en la declaración de la clase."); yyerrok; }
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
  | lista_ejecutables error ';'
    { yyerror("Error sintáctico: Falta ';' al final de la sentencia o error en sentencia."); yyerrok; }
  | error ';'
    { yyerror("Error sintáctico: Falta ';' al final de la sentencia."); yyerrok; }
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
  { printf("Estructura RET, en línea %d\n", yylineno); }
;

asignacion:
    destino ASSIGN { printf("[SINT] Estructura ASSIGN, en línea %d\n", yylineno); } expresion_aritmetica
  | destino '=' expresion_aritmetica
    { yyerror("Error sintáctico: Uso del símbolo '=' donde debe usarse ':='."); yyerrok; }
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
  | expresion_aritmetica '+' error
    { yyerror("Error sintáctico: Falta operando en la expresión aritmética."); yyerrok; }
  | expresion_aritmetica '-' error
    { yyerror("Error sintáctico: Falta operando en la expresión aritmética."); yyerrok; }
;

termino:
    termino '*' operando
  | termino '/' operando
  | operando
  | termino '*' error
    { yyerror("Error sintáctico: Falta operando en el término de la expresión."); yyerrok; }
  | termino '/' error
    { yyerror("Error sintáctico: Falta operando en el término de la expresión."); yyerrok; }
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
  | '[' error ']'
    { yyerror("Error sintáctico: Falta el orden de evaluación de parámetros entre '[' y ']'."); yyerrok; }
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
  | IF error condicion ')' bloque_o_sentencia rama_else END_IF
    { yyerror("Error sintáctico: Falta '(' en la condición de selección."); yyerrok; }
  | IF '(' condicion error bloque_o_sentencia rama_else END_IF
    { yyerror("Error sintáctico: Falta ')' en la condición de selección."); yyerrok; }
;

rama_else:
    ELSE { printf("[SINT] Estructura ELSE, en línea %d\n", yylineno); } bloque_o_sentencia %prec ELSE
  | %prec LOWER_THAN_ELSE
;

iteracion:
    encabezado_iteracion cuerpo_iteracion REPEAT
  | encabezado_iteracion error REPEAT
    { yyerror("Error sintáctico: Falta el cuerpo en la iteración."); yyerrok; }
;

encabezado_iteracion:
    FROM ID '=' constante TO constante BY constante
  | FROM error '=' constante TO constante BY constante
    { yyerror("Error sintáctico: Falta identificador (ID) en el encabezado de la iteración."); yyerrok; }
  | destino '=' constante TO constante BY constante
    { yyerror("Error sintáctico: Falta palabra clave 'FROM' en el encabezado de la iteración."); yyerrok; }
  | FROM ID '=' constante constante BY constante
    { yyerror("Error sintáctico: Falta 'TO' o constante en el encabezado de la iteración."); yyerrok; }
  | FROM '(' condicion ')'
  | FROM error condicion ')'
    { yyerror("Error sintáctico: Falta '(' en la condición de la iteración."); yyerrok; }
  | FROM '(' condicion error
    { yyerror("Error sintáctico: Falta ')' en la condición de la iteración."); yyerrok; }
;

cuerpo_iteracion:
    bloque_o_sentencia
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
    { printf("Estructura POUT, en línea %d\n", yylineno); }
;

%%