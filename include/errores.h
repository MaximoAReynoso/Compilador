#ifndef ERRORES_H
#define ERRORES_H

typedef enum {
    ETAPA_LEXICO,
    ETAPA_SINTACTICO,
    ETAPA_SEMANTICO,
    ETAPA_CODIGO_INTERMEDIO
} EtapaError;

typedef struct ErrorCompilador {
    EtapaError etapa;
    int linea;
    char *descripcion;
    struct ErrorCompilador *siguiente;
} ErrorCompilador;

void inicializar_errores(void);
void registrar_error(EtapaError etapa, int linea, const char *formato, ...);
int cantidad_errores(void);
int cantidad_errores_etapa(EtapaError etapa);
void imprimir_errores(void);
void destruir_errores(void);

#endif
