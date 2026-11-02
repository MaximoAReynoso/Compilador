#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include <stdbool.h>

#define TAM_TABLA 101

/* Tipos de datos soportados por el compilador */
typedef enum {
    TIPO_NO_ASIGNADO = 0,
    TIPO_INTEGER,
    TIPO_SINGLEF,
    TIPO_CLASE,
    TIPO_VOID,
    TIPO_CADENA
} TipoDato;

/* Usos posibles de las entradas en la Tabla de Símbolos */
typedef enum {
    USO_NO_ASIGNADO = 0,
    USO_VARIABLE,
    USO_PARAMETRO,
    USO_FUNCION,
    USO_CLASE,
    USO_OBJETO,
    USO_CONSTANTE,
    USO_VARIABLE_COMPTIME
} UsoSimbolo;

/* Parámetros formales para funciones */
typedef struct ParametroFormal {
    char *nombre;
    TipoDato tipo;
    struct ParametroFormal *siguiente;
} ParametroFormal;

/* Entrada de la Tabla de Símbolos */
typedef struct Simbolo {
    char *lexema;              // Clave en la TS (mangled si es identificador con ámbito)
    char *nombre_original;     // Nombre sin ámbito (ej: "x")
    char *ambito;              // Ámbito donde fue declarado (ej: "main:aa")
    int token;
    unsigned cantidad;

    TipoDato tipo;
    UsoSimbolo uso;

    // Metadatos para variables comptime (Tema 22)
    bool valor_comptime_valido;
    long valor_int;
    double valor_float;

    // Metadatos para funciones
    TipoDato tipo_retorno;
    int cant_parametros;
    ParametroFormal *parametros;

    // Metadatos para clases y herencia (Temas 24 y 32)
    char *codigo_clase;        // Tema 24: Identificador de código de la clase
    char **clases_padre;       // Tema 32: Nombres de las clases base de las que hereda
    int cant_padres;
    char *tipo_clase;          // Para objetos: nombre de la clase a la que pertenece

    struct Simbolo *siguiente;
} Simbolo;

typedef struct {
    Simbolo *entradas[TAM_TABLA];
} TablaSimbolos;

/* Funciones básicas de la tabla de símbolos (compatibles con TP1 / TP2) */
void inicializar_tabla(TablaSimbolos *tabla);
Simbolo *buscar_simbolo(TablaSimbolos *tabla, const char *lexema);
Simbolo *insertar_simbolo(TablaSimbolos *tabla, const char *lexema, int token);
void imprimir_tabla(TablaSimbolos *tabla);
void modificar_lexema(Simbolo *simbolo, const char *nuevo_lexema);
Simbolo *mover_ocurrencia(TablaSimbolos *tabla, Simbolo *simbolo, const char *nuevo_lexema);
void destruir_tabla(TablaSimbolos *tabla);

/* Conversiones a texto legible para la visualización */
const char *tipo_dato_a_string(TipoDato tipo);
const char *uso_simbolo_a_string(UsoSimbolo uso);

/* 
 * Gestión de Ámbitos (Scope Stack) y Name Mangling (Paso 1)
 */
void inicializar_gestor_ambitos(void);
void destruir_gestor_ambitos(void);

void entrar_ambito(const char *subambito);
void salir_ambito(void);
const char *obtener_ambito_actual(void);

/* Construir clave con mangling: "nombre:ambito" */
char *construir_mangled_name(const char *nombre, const char *ambito);

/* Búsqueda semántica con reglas de alcance (busca en ámbito actual y sube hacia los padres) */
Simbolo *buscar_identificador_semantico(TablaSimbolos *tabla, const char *nombre);

/* Búsqueda exclusiva en el ámbito actual (para detectar redeclaración) */
Simbolo *buscar_en_ambito_actual(TablaSimbolos *tabla, const char *nombre);

/* Declaración de un identificador en el ámbito actual con verificación de redeclaración */
Simbolo *declarar_identificador(
    TablaSimbolos *tabla,
    const char *nombre,
    int token,
    TipoDato tipo,
    UsoSimbolo uso,
    int linea
);

#endif