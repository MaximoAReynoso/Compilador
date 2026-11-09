#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include <stdbool.h>

#define TAM_TABLA 101

typedef enum {
    TIPO_NO_ASIGNADO = 0,
    TIPO_INTEGER,
    TIPO_SINGLEF,
    TIPO_CLASE,
    TIPO_VOID,
    TIPO_CADENA
} TipoDato;

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

typedef struct ParametroFormal {
    char *nombre;
    TipoDato tipo;
    bool es_comptime;
    struct ParametroFormal *siguiente;
} ParametroFormal;

typedef struct AtributoClase {
    char *nombre;
    TipoDato tipo;
    struct AtributoClase *siguiente;
} AtributoClase;

typedef struct Simbolo {
    char *lexema;
    char *nombre_original;
    char *ambito;
    int token;
    unsigned cantidad;

    TipoDato tipo;
    UsoSimbolo uso;

    /* COMPTIME */
    bool valor_comptime_valido;
    long valor_int;
    double valor_float;

    /* Funciones */
    TipoDato tipo_retorno;
    int cant_parametros;
    ParametroFormal *parametros;

    /* Clases y herencia */
    char *codigo_clase;
    char **clases_padre;
    int cant_padres;
    char *tipo_clase;
    AtributoClase *atributos;
    int cant_atributos;

    struct Simbolo *siguiente;
} Simbolo;

typedef struct InfoExpr {
    bool es_comptime;
    long val_int;
    double val_float;
    TipoDato tipo;
    Simbolo *simbolo_ref;
} InfoExpr;

typedef struct {
    Simbolo *entradas[TAM_TABLA];
} TablaSimbolos;

/* Gestión de tabla */
void inicializar_tabla(TablaSimbolos *tabla);
Simbolo *buscar_simbolo(TablaSimbolos *tabla, const char *lexema);
Simbolo *insertar_simbolo(TablaSimbolos *tabla, const char *lexema, int token);
void imprimir_tabla(TablaSimbolos *tabla);
void modificar_lexema(Simbolo *simbolo, const char *nuevo_lexema);
Simbolo *mover_ocurrencia(TablaSimbolos *tabla, Simbolo *simbolo, const char *nuevo_lexema);
void destruir_tabla(TablaSimbolos *tabla);

const char *tipo_dato_a_string(TipoDato tipo);
const char *uso_simbolo_a_string(UsoSimbolo uso);

/* Ámbitos y name mangling */
void inicializar_gestor_ambitos(void);
void destruir_gestor_ambitos(void);
void entrar_ambito(const char *subambito);
void salir_ambito(void);
const char *obtener_ambito_actual(void);
char *construir_mangled_name(const char *nombre, const char *ambito);

/* Búsqueda y declaración */
Simbolo *buscar_identificador_semantico(TablaSimbolos *tabla, const char *nombre);
Simbolo *buscar_en_ambito_actual(TablaSimbolos *tabla, const char *nombre);
Simbolo *declarar_identificador(
    TablaSimbolos *tabla,
    const char *nombre,
    int token,
    TipoDato tipo,
    UsoSimbolo uso,
    int linea
);

/* Clases y herencia */
bool clases_tienen_misma_estructura(Simbolo *c1, Simbolo *c2);

typedef struct {
    char *nombre_clase_origen;
    TipoDato tipo;
    UsoSimbolo uso;
    Simbolo *simbolo_metodo;
} ResultadoBusquedaMiembro;

bool resolver_miembro_herencia(TablaSimbolos *ts, Simbolo *cls, const char *nombre, int linea, ResultadoBusquedaMiembro *res_final);

#endif
