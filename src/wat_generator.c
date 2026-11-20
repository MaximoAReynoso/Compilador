#include "wat_generator.h"
#include "errores.h"
#include "polaca.h"
#include "tabla_simbolos.h"
#include "y.tab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_OPERANDOS 256
#define MAX_STRINGS 128
#define BUFFER_SIZE 65536
#define MAX_CELDAS 2048

typedef struct {
    TipoDato tipo;
    char lexema[256];
    bool es_constante;
    long val_int;
    double val_float;
    bool es_auxiliar;
} OperandoWAT;

typedef struct {
    char *texto;
    int offset;
    int longitud;
} StringLiteral;

static StringLiteral strings_tabla[MAX_STRINGS];
static int cant_strings = 0;
static int offset_memoria_actual = 512;

static int off_err_div_zero = 0;
static int len_err_div_zero = 0;
static int off_err_overflow_float = 0;
static int len_err_overflow_float = 0;
static int off_err_overflow_int = 0;
static int len_err_overflow_int = 0;
static int off_err_recursion = 0;
static int len_err_recursion = 0;

static const char *MSG_ERR_DIV_ZERO = "Error en tiempo de ejecucion: Division por cero.\n";
static const char *MSG_ERR_OVERFLOW_FLOAT = "Error en tiempo de ejecucion: Overflow en suma de punto flotante.\n";
static const char *MSG_ERR_OVERFLOW_INT = "Error en tiempo de ejecucion: Overflow en producto de enteros.\n";
static const char *MSG_ERR_RECURSION = "Error en tiempo de ejecucion: Recursion detectada en la funcion.\n";

static int registrar_string_literal(const char *cadena);

static void inicializar_strings(void) {
    cant_strings = 0;
    offset_memoria_actual = 512;

    off_err_div_zero = registrar_string_literal(MSG_ERR_DIV_ZERO);
    len_err_div_zero = strlen(MSG_ERR_DIV_ZERO);

    off_err_overflow_float = registrar_string_literal(MSG_ERR_OVERFLOW_FLOAT);
    len_err_overflow_float = strlen(MSG_ERR_OVERFLOW_FLOAT);

    off_err_overflow_int = registrar_string_literal(MSG_ERR_OVERFLOW_INT);
    len_err_overflow_int = strlen(MSG_ERR_OVERFLOW_INT);

    off_err_recursion = registrar_string_literal(MSG_ERR_RECURSION);
    len_err_recursion = strlen(MSG_ERR_RECURSION);
}

static int registrar_string_literal(const char *cadena) {
    if (!cadena) return -1;
    for (int i = 0; i < cant_strings; i++) {
        if (strcmp(strings_tabla[i].texto, cadena) == 0) {
            return strings_tabla[i].offset;
        }
    }
    if (cant_strings >= MAX_STRINGS) return -1;

    int len = strlen(cadena);
    if (cadena[0] == '"' && cadena[len - 1] == '"') {
        len -= 2;
    }

    strings_tabla[cant_strings].texto = strdup(cadena);
    strings_tabla[cant_strings].offset = offset_memoria_actual;
    strings_tabla[cant_strings].longitud = len;

    int off = offset_memoria_actual;
    offset_memoria_actual += len + 1;
    if (offset_memoria_actual % 4 != 0) {
        offset_memoria_actual += (4 - (offset_memoria_actual % 4));
    }

    cant_strings++;
    return off;
}

static int obtener_longitud_string(const char *cadena) {
    if (!cadena) return 0;
    for (int i = 0; i < cant_strings; i++) {
        if (strcmp(strings_tabla[i].texto, cadena) == 0) {
            return strings_tabla[i].longitud;
        }
    }
    int len = strlen(cadena);
    if (cadena[0] == '"' && cadena[len - 1] == '"') {
        len -= 2;
    }
    return len;
}

/* Sanitiza identificadores para WebAssembly reemplazando ':' por '_' */
static void sanitizar_identificador(const char *orig, char *dest, size_t dest_size) {
    if (!orig || !dest || dest_size == 0) return;
    size_t d = 0;
    if (orig[0] != '$' && d + 1 < dest_size) {
        dest[d++] = '$';
    }
    if (d + 1 < dest_size) {
        dest[d++] = '_';
    }

    for (size_t i = 0; orig[i] != '\0' && d + 1 < dest_size; i++) {
        char c = orig[i];
        if (c == ':') {
            dest[d++] = '_';
        } else if (isalnum((unsigned char)c) || c == '_' || c == '.') {
            dest[d++] = c;
        } else if (c == '$' && i > 0) {
            dest[d++] = '_';
        }
    }
    dest[d] = '\0';
}

static long parsear_entero_wat(const char *lexema) {
    if (!lexema) return 0;
    char buf[64];
    strncpy(buf, lexema, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    char *p = strchr(buf, '$');
    if (p) *p = '\0';
    return atol(buf);
}

static void emitir_carga_operando(FILE *f, const OperandoWAT *op, const char *nombre_ambito) {
    (void)nombre_ambito;
    if (op->es_constante) {
        if (op->tipo == TIPO_SINGLEF) {
            fprintf(f, "    f32.const %g\n", op->val_float);
        } else {
            fprintf(f, "    i32.const %ld\n", op->val_int);
        }
        return;
    }

    if (op->es_auxiliar || strstr(op->lexema, "_aux_") != NULL) {
        fprintf(f, "    local.get %s\n", op->lexema);
        return;
    }

    char id_sanitizado[128];
    sanitizar_identificador(op->lexema, id_sanitizado, sizeof(id_sanitizado));
    fprintf(f, "    global.get %s\n", id_sanitizado);
}

static void emitir_guardado_operando(FILE *f, const char *lexema, const char *nombre_ambito) {
    (void)nombre_ambito;
    char id_sanitizado[128];
    sanitizar_identificador(lexema, id_sanitizado, sizeof(id_sanitizado));

    if (strstr(lexema, "_aux_") != NULL) {
        fprintf(f, "    local.set %s\n", id_sanitizado);
    } else {
        fprintf(f, "    global.set %s\n", id_sanitizado);
    }
}

static void recolectar_atributos_clase(TablaSimbolos *ts, Simbolo *cls, AtributoClase **lista_attrs, int *cant) {
    if (!cls || !lista_attrs || !cant) return;
    for (int p = 0; p < cls->cant_padres; p++) {
        Simbolo *padre = buscar_identificador_semantico(ts, cls->clases_padre[p]);
        if (padre) recolectar_atributos_clase(ts, padre, lista_attrs, cant);
    }
    for (AtributoClase *at = cls->atributos; at != NULL; at = at->siguiente) {
        if (*cant < 64) {
            lista_attrs[(*cant)++] = at;
        }
    }
}

typedef struct {
    int celda_origen;
    int celda_destino;
    bool es_backward;
    bool es_bf;
} InfoSalto;

static bool traducir_polaca_a_wat(
    Polaca *p,
    TablaSimbolos *tabla,
    FILE *f_out,
    bool es_main,
    int *contador_aux_global
) {
    if (!p || !f_out) return true;

    char *cuerpo_buffer = malloc(BUFFER_SIZE);
    if (!cuerpo_buffer) return false;
    cuerpo_buffer[0] = '\0';
    size_t cuerpo_len = 0;

    FILE *f_cuerpo = open_memstream(&cuerpo_buffer, &cuerpo_len);
    if (!f_cuerpo) {
        free(cuerpo_buffer);
        return false;
    }

    OperandoWAT pila_operandos[MAX_OPERANDOS];
    int tope_pila = 0;

    int cant_aux_int = 0;
    int cant_aux_float = 0;
    bool hubo_error_tipos = false;

    char func_id[128];
    Simbolo *s_func = NULL;
    if (!es_main) {
        s_func = buscar_simbolo(tabla, p->nombre);
        if (!s_func) s_func = buscar_identificador_semantico(tabla, p->nombre);
        if (!s_func) {
            for (int ti = 0; ti < TAM_TABLA && !s_func; ti++) {
                for (Simbolo *cur = tabla->entradas[ti]; cur != NULL; cur = cur->siguiente) {
                    if (cur->uso == USO_FUNCION && strncmp(p->nombre, cur->lexema, strlen(cur->lexema)) == 0) {
                        s_func = cur;
                        break;
                    }
                }
            }
        }
        if (s_func) {
            sanitizar_identificador(s_func->lexema, func_id, sizeof(func_id));
        } else {
            sanitizar_identificador(p->nombre, func_id, sizeof(func_id));
        }
    } else {
        strncpy(func_id, "$main", sizeof(func_id) - 1);
    }

    /* Mapeo de saltos estructurados (block / loop) */
    InfoSalto saltos[128];
    int cant_saltos = 0;

    for (int i = 0; i < p->tam; i++) {
        ElementoPolaca *elem = &p->elementos[i];
        if (elem->tipo == POLACA_TIPO_OPERADOR && elem->operador) {
            if (strcmp(elem->operador, "BF") == 0 || strcmp(elem->operador, "BI") == 0) {
                if (i > 0 && p->elementos[i - 1].tipo == POLACA_TIPO_DESTINO) {
                    int dest = p->elementos[i - 1].celda_destino;
                    if (cant_saltos < 128) {
                        saltos[cant_saltos].celda_origen = i;
                        saltos[cant_saltos].celda_destino = dest;
                        saltos[cant_saltos].es_backward = (dest <= i);
                        saltos[cant_saltos].es_bf = (strcmp(elem->operador, "BF") == 0);
                        cant_saltos++;
                    }
                }
            }
        }
    }

    int block_open_at[MAX_CELDAS][8];
    int count_block_open[MAX_CELDAS];
    int count_block_close[MAX_CELDAS];

    int loop_open_at[MAX_CELDAS][8];
    int count_loop_open[MAX_CELDAS];
    int count_loop_close[MAX_CELDAS];

    memset(count_block_open, 0, sizeof(count_block_open));
    memset(count_block_close, 0, sizeof(count_block_close));
    memset(count_loop_open, 0, sizeof(count_loop_open));
    memset(count_loop_close, 0, sizeof(count_loop_close));

    for (int s = 0; s < cant_saltos; s++) {
        if (saltos[s].es_backward) {
            int d = saltos[s].celda_destino;
            int orig = saltos[s].celda_origen;
            if (d >= 0 && d < MAX_CELDAS && orig >= 0 && orig < MAX_CELDAS) {
                if (count_loop_open[d] < 8) {
                    loop_open_at[d][count_loop_open[d]++] = d;
                }
                if (count_loop_close[orig] < 8) {
                    count_loop_close[orig]++;
                }
            }
        }
    }

    for (int s = 0; s < cant_saltos; s++) {
        if (!saltos[s].es_backward) {
            int dest = saltos[s].celda_destino;
            int orig = saltos[s].celda_origen;

            int start_b = orig;
            for (int l = 0; l < cant_saltos; l++) {
                if (saltos[l].es_backward) {
                    int l_start = saltos[l].celda_destino;
                    int l_end = saltos[l].celda_origen;
                    if (orig >= l_start && orig <= l_end && dest > l_end) {
                        if (l_start < start_b) {
                            start_b = l_start;
                        }
                    }
                }
            }

            if (start_b >= 0 && start_b < MAX_CELDAS && dest >= 0 && dest < MAX_CELDAS) {
                if (count_block_open[start_b] < 8) {
                    block_open_at[start_b][count_block_open[start_b]++] = dest;
                }
                if (count_block_close[dest] < 8) {
                    count_block_close[dest]++;
                }
            }
        }
    }

    /* Control de recursión */
    if (!es_main) {
        fprintf(f_cuerpo, "    global.get $__en_ejecucion%s\n", func_id);
        fprintf(f_cuerpo, "    if\n");
        fprintf(f_cuerpo, "      i32.const %d\n", off_err_recursion);
        fprintf(f_cuerpo, "      i32.const %d\n", len_err_recursion);
        fprintf(f_cuerpo, "      call $pout_str\n");
        fprintf(f_cuerpo, "      i32.const 1\n");
        fprintf(f_cuerpo, "      call $error_exit\n");
        fprintf(f_cuerpo, "      unreachable\n");
        fprintf(f_cuerpo, "    end\n");
        fprintf(f_cuerpo, "    i32.const 1\n");
        fprintf(f_cuerpo, "    global.set $__en_ejecucion%s\n\n", func_id);
    }

    for (int i = 0; i < p->tam; i++) {
        ElementoPolaca *elem = &p->elementos[i];

        if (i < MAX_CELDAS) {
            for (int b = 0; b < count_block_close[i]; b++) {
                fprintf(f_cuerpo, "    )\n");
            }
        }

        if (i < MAX_CELDAS) {
            for (int b = 0; b < count_block_open[i]; b++) {
                int dest = block_open_at[i][b];
                fprintf(f_cuerpo, "    (block $b_%d\n", dest);
            }
        }

        if (i < MAX_CELDAS) {
            for (int l = 0; l < count_loop_open[i]; l++) {
                int l_id = loop_open_at[i][l];
                fprintf(f_cuerpo, "    (loop $l_%d\n", l_id);
            }
        }

        switch (elem->tipo) {
            case POLACA_TIPO_SIMBOLO: {
                Simbolo *s = elem->simbolo;
                if (!s) break;

                OperandoWAT op;
                memset(&op, 0, sizeof(op));
                strncpy(op.lexema, s->lexema ? s->lexema : "", sizeof(op.lexema) - 1);
                op.tipo = s->tipo;
                op.es_auxiliar = false;

                if (s->token == CTE || s->token == CTE_FLOAT) {
                    op.es_constante = true;
                    if (s->tipo == TIPO_SINGLEF) {
                        char buf_float[64];
                        strncpy(buf_float, s->lexema, sizeof(buf_float) - 1);
                        buf_float[sizeof(buf_float) - 1] = '\0';
                        for (int ci = 0; buf_float[ci] != '\0'; ci++) {
                            if (buf_float[ci] == 's' || buf_float[ci] == 'S') {
                                buf_float[ci] = 'e';
                            }
                        }
                        op.val_float = atof(buf_float);
                        op.val_int = (long)op.val_float;
                    } else {
                        op.val_int = parsear_entero_wat(s->lexema);
                        op.val_float = (double)op.val_int;
                    }
                } else if (s->token == MULT_STRING) {
                    op.es_constante = true;
                    op.tipo = TIPO_CADENA;
                    registrar_string_literal(s->lexema);
                } else if (s->uso == USO_VARIABLE_COMPTIME && s->valor_comptime_valido) {
                    op.es_constante = true;
                    op.val_int = s->valor_int;
                    op.val_float = s->valor_float;
                } else {
                    op.es_constante = false;
                }

                if (tope_pila < MAX_OPERANDOS) {
                    pila_operandos[tope_pila++] = op;
                }
                break;
            }

            case POLACA_TIPO_DESTINO: {
                OperandoWAT op;
                memset(&op, 0, sizeof(op));
                op.tipo = TIPO_INTEGER;
                op.es_constante = true;
                op.val_int = elem->celda_destino;
                snprintf(op.lexema, sizeof(op.lexema), "[%d]", elem->celda_destino);
                if (tope_pila < MAX_OPERANDOS) {
                    pila_operandos[tope_pila++] = op;
                }
                break;
            }

            case POLACA_TIPO_OPERADOR: {
                const char *op_str = elem->operador;
                if (!op_str) break;

                /* Asignación */
                if (strcmp(op_str, ":=") == 0) {
                    if (tope_pila >= 2) {
                        OperandoWAT fuente = pila_operandos[--tope_pila];
                        OperandoWAT destino = pila_operandos[--tope_pila];

                        if (destino.tipo == TIPO_CLASE && fuente.tipo == TIPO_CLASE) {
                            Simbolo *s_dest = buscar_identificador_semantico(tabla, destino.lexema);
                            Simbolo *s_src = buscar_identificador_semantico(tabla, fuente.lexema);
                            if (s_dest && s_src && s_dest->tipo_clase && s_src->tipo_clase) {
                                Simbolo *cls_dest = buscar_identificador_semantico(tabla, s_dest->tipo_clase);
                                Simbolo *cls_src = buscar_identificador_semantico(tabla, s_src->tipo_clase);
                                AtributoClase *attrs_d[64];
                                AtributoClase *attrs_s[64];
                                int nd = 0, ns = 0;
                                recolectar_atributos_clase(tabla, cls_dest, attrs_d, &nd);
                                recolectar_atributos_clase(tabla, cls_src, attrs_s, &ns);
                                int n_copy = (nd < ns) ? nd : ns;
                                for (int k = 0; k < n_copy; k++) {
                                    char id_d[256], id_s[256];
                                    char san_d[256], san_s[256];
                                    snprintf(id_d, sizeof(id_d), "%.120s:%.120s", destino.lexema, attrs_d[k]->nombre);
                                    snprintf(id_s, sizeof(id_s), "%.120s:%.120s", fuente.lexema, attrs_s[k]->nombre);
                                    sanitizar_identificador(id_d, san_d, sizeof(san_d));
                                    sanitizar_identificador(id_s, san_s, sizeof(san_s));
                                    fprintf(f_cuerpo, "    global.get %s\n", san_s);
                                    fprintf(f_cuerpo, "    global.set %s\n", san_d);
                                }
                            }
                        } else {
                            if (destino.tipo != TIPO_NO_ASIGNADO && fuente.tipo != TIPO_NO_ASIGNADO && destino.tipo != fuente.tipo) {
                                registrar_error(
                                    ETAPA_CODIGO_INTERMEDIO,
                                    elem->linea,
                                    "Incompatibilidad de tipos en asignacion: no se puede asignar '%s' a '%s'.",
                                    tipo_dato_a_string(fuente.tipo),
                                    tipo_dato_a_string(destino.tipo)
                                );
                                hubo_error_tipos = true;
                            }

                            emitir_carga_operando(f_cuerpo, &fuente, p->nombre);
                            emitir_guardado_operando(f_cuerpo, destino.lexema, p->nombre);
                        }
                    }
                }
                /* Conversión TOSF */
                else if (strcmp(op_str, "TOSF") == 0) {
                    if (tope_pila >= 1) {
                        OperandoWAT operando = pila_operandos[--tope_pila];

                        if (operando.tipo != TIPO_INTEGER && operando.tipo != TIPO_NO_ASIGNADO) {
                            registrar_error(
                                ETAPA_CODIGO_INTERMEDIO,
                                elem->linea,
                                "Incompatibilidad de tipos en conversion TOSF: se esperaba INTEGER pero se recibio '%s'.",
                                tipo_dato_a_string(operando.tipo)
                            );
                            hubo_error_tipos = true;
                        }

                        cant_aux_float++;
                        char aux_nombre[64];
                        snprintf(aux_nombre, sizeof(aux_nombre), "$_aux_float_%d", cant_aux_float);

                        emitir_carga_operando(f_cuerpo, &operando, p->nombre);
                        fprintf(f_cuerpo, "    f32.convert_i32_s\n");
                        fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);

                        OperandoWAT res;
                        memset(&res, 0, sizeof(res));
                        res.tipo = TIPO_SINGLEF;
                        res.es_auxiliar = true;
                        res.es_constante = false;
                        strncpy(res.lexema, aux_nombre, sizeof(res.lexema) - 1);
                        pila_operandos[tope_pila++] = res;
                    }
                }
                /* Operaciones aritméticas */
                else if (strcmp(op_str, "+") == 0 || strcmp(op_str, "-") == 0 ||
                         strcmp(op_str, "*") == 0 || strcmp(op_str, "/") == 0) {
                    if (tope_pila >= 2) {
                        OperandoWAT op2 = pila_operandos[--tope_pila];
                        OperandoWAT op1 = pila_operandos[--tope_pila];

                        if (op1.tipo != TIPO_NO_ASIGNADO && op2.tipo != TIPO_NO_ASIGNADO && op1.tipo != op2.tipo) {
                            registrar_error(
                                ETAPA_CODIGO_INTERMEDIO,
                                elem->linea,
                                "Incompatibilidad de tipos en operador '%s': operandos de tipos '%s' y '%s'.",
                                op_str,
                                tipo_dato_a_string(op1.tipo),
                                tipo_dato_a_string(op2.tipo)
                            );
                            hubo_error_tipos = true;
                        }

                        TipoDato tipo_res = (op1.tipo == TIPO_SINGLEF || op2.tipo == TIPO_SINGLEF) ? TIPO_SINGLEF : TIPO_INTEGER;

                        char aux_nombre[64];
                        if (tipo_res == TIPO_SINGLEF) {
                            cant_aux_float++;
                            snprintf(aux_nombre, sizeof(aux_nombre), "$_aux_float_%d", cant_aux_float);
                        } else {
                            cant_aux_int++;
                            snprintf(aux_nombre, sizeof(aux_nombre), "$_aux_int_%d", cant_aux_int);
                        }

                        /* Control de división por cero */
                        if (strcmp(op_str, "/") == 0) {
                            if (tipo_res == TIPO_SINGLEF) {
                                emitir_carga_operando(f_cuerpo, &op2, p->nombre);
                                fprintf(f_cuerpo, "    f32.const 0.0\n");
                                fprintf(f_cuerpo, "    f32.eq\n");
                                fprintf(f_cuerpo, "    if\n");
                                fprintf(f_cuerpo, "      i32.const %d\n", off_err_div_zero);
                                fprintf(f_cuerpo, "      i32.const %d\n", len_err_div_zero);
                                fprintf(f_cuerpo, "      call $pout_str\n");
                                fprintf(f_cuerpo, "      i32.const 1\n");
                                fprintf(f_cuerpo, "      call $error_exit\n");
                                fprintf(f_cuerpo, "      unreachable\n");
                                fprintf(f_cuerpo, "    end\n");
                            } else {
                                emitir_carga_operando(f_cuerpo, &op2, p->nombre);
                                fprintf(f_cuerpo, "    i32.eqz\n");
                                fprintf(f_cuerpo, "    if\n");
                                fprintf(f_cuerpo, "      i32.const %d\n", off_err_div_zero);
                                fprintf(f_cuerpo, "      i32.const %d\n", len_err_div_zero);
                                fprintf(f_cuerpo, "      call $pout_str\n");
                                fprintf(f_cuerpo, "      i32.const 1\n");
                                fprintf(f_cuerpo, "      call $error_exit\n");
                                fprintf(f_cuerpo, "      unreachable\n");
                                fprintf(f_cuerpo, "    end\n");
                            }
                        }

                        emitir_carga_operando(f_cuerpo, &op1, p->nombre);
                        emitir_carga_operando(f_cuerpo, &op2, p->nombre);

                        if (tipo_res == TIPO_SINGLEF) {
                            if (strcmp(op_str, "+") == 0) {
                                fprintf(f_cuerpo, "    f32.add\n");
                                fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);

                                /* Control de overflow en suma float */
                                fprintf(f_cuerpo, "    local.get %s\n", aux_nombre);
                                fprintf(f_cuerpo, "    i32.reinterpret_f32\n");
                                fprintf(f_cuerpo, "    i32.const 0x7f800000\n");
                                fprintf(f_cuerpo, "    i32.and\n");
                                fprintf(f_cuerpo, "    i32.const 0x7f800000\n");
                                fprintf(f_cuerpo, "    i32.eq\n");
                                fprintf(f_cuerpo, "    if\n");
                                fprintf(f_cuerpo, "      i32.const %d\n", off_err_overflow_float);
                                fprintf(f_cuerpo, "      i32.const %d\n", len_err_overflow_float);
                                fprintf(f_cuerpo, "      call $pout_str\n");
                                fprintf(f_cuerpo, "      i32.const 1\n");
                                fprintf(f_cuerpo, "      call $error_exit\n");
                                fprintf(f_cuerpo, "      unreachable\n");
                                fprintf(f_cuerpo, "    end\n");
                            } else if (strcmp(op_str, "-") == 0) {
                                fprintf(f_cuerpo, "    f32.sub\n");
                                fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);
                            } else if (strcmp(op_str, "*") == 0) {
                                fprintf(f_cuerpo, "    f32.mul\n");
                                fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);
                            } else if (strcmp(op_str, "/") == 0) {
                                fprintf(f_cuerpo, "    f32.div\n");
                                fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);
                            }
                        } else {
                            if (strcmp(op_str, "+") == 0) {
                                fprintf(f_cuerpo, "    i32.add\n");
                                fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);
                            } else if (strcmp(op_str, "-") == 0) {
                                fprintf(f_cuerpo, "    i32.sub\n");
                                fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);
                            } else if (strcmp(op_str, "*") == 0) {
                                fprintf(f_cuerpo, "    i32.mul\n");
                                fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);

                                /* Control de overflow en producto int (16 bits) */
                                fprintf(f_cuerpo, "    local.get %s\n", aux_nombre);
                                fprintf(f_cuerpo, "    i32.const 32767\n");
                                fprintf(f_cuerpo, "    i32.gt_s\n");
                                fprintf(f_cuerpo, "    local.get %s\n", aux_nombre);
                                fprintf(f_cuerpo, "    i32.const -32768\n");
                                fprintf(f_cuerpo, "    i32.lt_s\n");
                                fprintf(f_cuerpo, "    i32.or\n");
                                fprintf(f_cuerpo, "    if\n");
                                fprintf(f_cuerpo, "      i32.const %d\n", off_err_overflow_int);
                                fprintf(f_cuerpo, "      i32.const %d\n", len_err_overflow_int);
                                fprintf(f_cuerpo, "      call $pout_str\n");
                                fprintf(f_cuerpo, "      i32.const 1\n");
                                fprintf(f_cuerpo, "      call $error_exit\n");
                                fprintf(f_cuerpo, "      unreachable\n");
                                fprintf(f_cuerpo, "    end\n");
                            } else if (strcmp(op_str, "/") == 0) {
                                fprintf(f_cuerpo, "    i32.div_s\n");
                                fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);
                            }
                        }

                        OperandoWAT res;
                        memset(&res, 0, sizeof(res));
                        res.tipo = tipo_res;
                        res.es_auxiliar = true;
                        res.es_constante = false;
                        strncpy(res.lexema, aux_nombre, sizeof(res.lexema) - 1);
                        pila_operandos[tope_pila++] = res;
                    }
                }
                /* Comparaciones */
                else if (strcmp(op_str, "<") == 0 || strcmp(op_str, ">") == 0 ||
                         strcmp(op_str, "<=") == 0 || strcmp(op_str, ">=") == 0 ||
                         strcmp(op_str, "==") == 0 || strcmp(op_str, "!=") == 0) {
                    if (tope_pila >= 2) {
                        OperandoWAT op2 = pila_operandos[--tope_pila];
                        OperandoWAT op1 = pila_operandos[--tope_pila];

                        if (op1.tipo != TIPO_NO_ASIGNADO && op2.tipo != TIPO_NO_ASIGNADO && op1.tipo != op2.tipo) {
                            registrar_error(
                                ETAPA_CODIGO_INTERMEDIO,
                                elem->linea,
                                "Incompatibilidad de tipos en comparacion '%s': operandos de tipos '%s' y '%s'.",
                                op_str,
                                tipo_dato_a_string(op1.tipo),
                                tipo_dato_a_string(op2.tipo)
                            );
                            hubo_error_tipos = true;
                        }

                        cant_aux_int++;
                        char aux_nombre[64];
                        snprintf(aux_nombre, sizeof(aux_nombre), "$_aux_int_%d", cant_aux_int);

                        emitir_carga_operando(f_cuerpo, &op1, p->nombre);
                        emitir_carga_operando(f_cuerpo, &op2, p->nombre);

                        if (op1.tipo == TIPO_SINGLEF || op2.tipo == TIPO_SINGLEF) {
                            if (strcmp(op_str, "<") == 0) fprintf(f_cuerpo, "    f32.lt\n");
                            else if (strcmp(op_str, ">") == 0) fprintf(f_cuerpo, "    f32.gt\n");
                            else if (strcmp(op_str, "<=") == 0) fprintf(f_cuerpo, "    f32.le\n");
                            else if (strcmp(op_str, ">=") == 0) fprintf(f_cuerpo, "    f32.ge\n");
                            else if (strcmp(op_str, "==") == 0) fprintf(f_cuerpo, "    f32.eq\n");
                            else if (strcmp(op_str, "!=") == 0) fprintf(f_cuerpo, "    f32.ne\n");
                        } else {
                            if (strcmp(op_str, "<") == 0) fprintf(f_cuerpo, "    i32.lt_s\n");
                            else if (strcmp(op_str, ">") == 0) fprintf(f_cuerpo, "    i32.gt_s\n");
                            else if (strcmp(op_str, "<=") == 0) fprintf(f_cuerpo, "    i32.le_s\n");
                            else if (strcmp(op_str, ">=") == 0) fprintf(f_cuerpo, "    i32.ge_s\n");
                            else if (strcmp(op_str, "==") == 0) fprintf(f_cuerpo, "    i32.eq\n");
                            else if (strcmp(op_str, "!=") == 0) fprintf(f_cuerpo, "    i32.ne\n");
                        }
                        fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);

                        OperandoWAT res;
                        memset(&res, 0, sizeof(res));
                        res.tipo = TIPO_INTEGER;
                        res.es_auxiliar = true;
                        res.es_constante = false;
                        strncpy(res.lexema, aux_nombre, sizeof(res.lexema) - 1);
                        pila_operandos[tope_pila++] = res;
                    }
                }
                /* POUT */
                else if (strcmp(op_str, "POUT") == 0) {
                    if (tope_pila >= 1) {
                        OperandoWAT operando = pila_operandos[--tope_pila];
                        if (operando.tipo == TIPO_CADENA) {
                            int off = registrar_string_literal(operando.lexema);
                            int len = obtener_longitud_string(operando.lexema);
                            fprintf(f_cuerpo, "    i32.const %d\n", off);
                            fprintf(f_cuerpo, "    i32.const %d\n", len);
                            fprintf(f_cuerpo, "    call $pout_str\n");
                        } else if (operando.tipo == TIPO_SINGLEF) {
                            emitir_carga_operando(f_cuerpo, &operando, p->nombre);
                            fprintf(f_cuerpo, "    call $pout_float\n");
                        } else {
                            emitir_carga_operando(f_cuerpo, &operando, p->nombre);
                            fprintf(f_cuerpo, "    call $pout_int\n");
                        }
                    }
                }
                /* RET */
                else if (strcmp(op_str, "RET") == 0) {
                    if (!es_main) {
                        fprintf(f_cuerpo, "    i32.const 0\n");
                        fprintf(f_cuerpo, "    global.set $__en_ejecucion%s\n", func_id);
                    }
                    if (tope_pila >= 1) {
                        OperandoWAT ret_val = pila_operandos[--tope_pila];
                        emitir_carga_operando(f_cuerpo, &ret_val, p->nombre);
                    }
                    fprintf(f_cuerpo, "    return\n");
                }
                /* CALL */
                else if (strcmp(op_str, "CALL") == 0) {
                    if (tope_pila >= 1) {
                        OperandoWAT func_sym = pila_operandos[--tope_pila];
                        char id_func_sanitizado[128];
                        sanitizar_identificador(func_sym.lexema, id_func_sanitizado, sizeof(id_func_sanitizado));

                        fprintf(f_cuerpo, "    call %s\n", id_func_sanitizado);

                        Simbolo *s = buscar_simbolo(tabla, func_sym.lexema);
                        if (!s) s = buscar_identificador_semantico(tabla, func_sym.lexema);

                        TipoDato ret_tipo = (s && s->tipo_retorno != TIPO_NO_ASIGNADO) ? s->tipo_retorno : (s ? s->tipo : TIPO_INTEGER);
                        if (ret_tipo != TIPO_VOID && ret_tipo != TIPO_NO_ASIGNADO) {
                            char aux_nombre[64];
                            if (ret_tipo == TIPO_SINGLEF) {
                                cant_aux_float++;
                                snprintf(aux_nombre, sizeof(aux_nombre), "$_aux_float_%d", cant_aux_float);
                            } else {
                                cant_aux_int++;
                                snprintf(aux_nombre, sizeof(aux_nombre), "$_aux_int_%d", cant_aux_int);
                            }
                            fprintf(f_cuerpo, "    local.set %s\n", aux_nombre);

                            OperandoWAT res;
                            memset(&res, 0, sizeof(res));
                            res.tipo = ret_tipo;
                            res.es_auxiliar = true;
                            strncpy(res.lexema, aux_nombre, sizeof(res.lexema) - 1);
                            pila_operandos[tope_pila++] = res;
                        }
                    }
                }
                /* Saltos condicionales e incondicionales */
                else if (strcmp(op_str, "BF") == 0) {
                    if (tope_pila >= 2) {
                        OperandoWAT dest = pila_operandos[--tope_pila];
                        OperandoWAT cond = pila_operandos[--tope_pila];
                        int d = dest.val_int;

                        emitir_carga_operando(f_cuerpo, &cond, p->nombre);
                        fprintf(f_cuerpo, "    i32.eqz\n");
                        fprintf(f_cuerpo, "    br_if $b_%d\n", d);
                    }
                } else if (strcmp(op_str, "BI") == 0) {
                    if (tope_pila >= 1) {
                        OperandoWAT dest = pila_operandos[--tope_pila];
                        int d = dest.val_int;
                        if (d <= i) {
                            fprintf(f_cuerpo, "    br $l_%d\n", d);
                        } else {
                            fprintf(f_cuerpo, "    br $b_%d\n", d);
                        }
                    }
                }
                /* Acceso a atributo por nombre y posición */
                else if (strcmp(op_str, ".") == 0) {
                    if (tope_pila >= 1) {
                        OperandoWAT obj = pila_operandos[--tope_pila];
                        const char *attr_name = (i > 0 && p->elementos[i - 1].tipo == POLACA_TIPO_OPERADOR) ? p->elementos[i - 1].operador : "";
                        Simbolo *s_obj = buscar_identificador_semantico(tabla, obj.lexema);
                        TipoDato tipo_attr = TIPO_INTEGER;
                        if (s_obj && s_obj->tipo_clase) {
                            Simbolo *cls = buscar_identificador_semantico(tabla, s_obj->tipo_clase);
                            ResultadoBusquedaMiembro res_m;
                            if (resolver_miembro_herencia(tabla, cls, attr_name, elem->linea, &res_m)) {
                                tipo_attr = res_m.tipo;
                            }
                        }
                        OperandoWAT res;
                        memset(&res, 0, sizeof(res));
                        res.tipo = tipo_attr;
                        snprintf(res.lexema, sizeof(res.lexema), "%.120s:%.120s", obj.lexema, attr_name);
                        res.es_constante = false;
                        res.es_auxiliar = false;
                        if (tope_pila < MAX_OPERANDOS) {
                            pila_operandos[tope_pila++] = res;
                        }
                    }
                }
                else if (strcmp(op_str, "[]") == 0) {
                    if (tope_pila >= 2) {
                        OperandoWAT obj = pila_operandos[--tope_pila];
                        OperandoWAT idx_op = pila_operandos[--tope_pila];
                        int idx = (int)idx_op.val_int;
                        Simbolo *s_obj = buscar_identificador_semantico(tabla, obj.lexema);
                        TipoDato tipo_attr = TIPO_INTEGER;
                        const char *attr_name = "attr";
                        if (s_obj && s_obj->tipo_clase) {
                            Simbolo *cls = buscar_identificador_semantico(tabla, s_obj->tipo_clase);
                            AtributoClase *attrs[64];
                            int n_attrs = 0;
                            recolectar_atributos_clase(tabla, cls, attrs, &n_attrs);
                            if (idx >= 0 && idx < n_attrs) {
                                tipo_attr = attrs[idx]->tipo;
                                attr_name = attrs[idx]->nombre;
                            }
                        }
                        OperandoWAT res;
                        memset(&res, 0, sizeof(res));
                        res.tipo = tipo_attr;
                        snprintf(res.lexema, sizeof(res.lexema), "%.120s:%.120s", obj.lexema, attr_name);
                        res.es_constante = false;
                        res.es_auxiliar = false;
                        if (tope_pila < MAX_OPERANDOS) {
                            pila_operandos[tope_pila++] = res;
                        }
                    }
                }
                break;
            }
        }

        if (i < MAX_CELDAS) {
            for (int l = 0; l < count_loop_close[i]; l++) {
                fprintf(f_cuerpo, "    )\n");
            }
        }
    }

    if (!es_main) {
        fprintf(f_cuerpo, "\n    i32.const 0\n");
        fprintf(f_cuerpo, "    global.set $__en_ejecucion%s\n", func_id);
    }

    fclose(f_cuerpo);

    if (es_main) {
        fprintf(f_out, "\n  (func $main (export \"main\")\n");
    } else {
        fprintf(f_out, "\n  (func %s", func_id);

        TipoDato ret_tipo = (s_func && s_func->tipo_retorno != TIPO_NO_ASIGNADO) ? s_func->tipo_retorno : (s_func ? s_func->tipo : TIPO_INTEGER);
        if (ret_tipo != TIPO_VOID && ret_tipo != TIPO_NO_ASIGNADO) {
            const char *wtype = (ret_tipo == TIPO_SINGLEF) ? "f32" : "i32";
            fprintf(f_out, " (result %s)", wtype);
        }
        fprintf(f_out, "\n");
    }

    for (int a = 1; a <= cant_aux_int; a++) {
        fprintf(f_out, "    (local $_aux_int_%d i32)\n", a);
    }
    for (int a = 1; a <= cant_aux_float; a++) {
        fprintf(f_out, "    (local $_aux_float_%d f32)\n", a);
    }

    fprintf(f_out, "%s", cuerpo_buffer);
    fprintf(f_out, "  )\n");

    free(cuerpo_buffer);

    if (contador_aux_global) {
        *contador_aux_global += (cant_aux_int + cant_aux_float);
    }

    return !hubo_error_tipos;
}

bool generar_codigo_wat(TablaSimbolos *tabla, const char *archivo_salida) {
    if (!tabla || !archivo_salida) return false;

    inicializar_strings();

    registrar_string_literal(MSG_ERR_DIV_ZERO);
    registrar_string_literal(MSG_ERR_OVERFLOW_FLOAT);
    registrar_string_literal(MSG_ERR_OVERFLOW_INT);
    registrar_string_literal(MSG_ERR_RECURSION);

    FILE *f = fopen(archivo_salida, "w");
    if (!f) {
        fprintf(stderr, "Error: No se pudo crear el archivo '%s'.\n", archivo_salida);
        return false;
    }

    fprintf(f, "(module\n");
    fprintf(f, "  (import \"env\" \"pout_int\" (func $pout_int (param i32)))\n");
    fprintf(f, "  (import \"env\" \"pout_float\" (func $pout_float (param f32)))\n");
    fprintf(f, "  (import \"env\" \"pout_str\" (func $pout_str (param i32 i32)))\n");
    fprintf(f, "  (import \"env\" \"error_exit\" (func $error_exit (param i32)))\n\n");

    fprintf(f, "  (memory 1)\n");
    fprintf(f, "  (export \"memory\" (memory 0))\n\n");

    for (int i = 0; i < TAM_TABLA; i++) {
        Simbolo *s = tabla->entradas[i];
        while (s != NULL) {
            if ((s->uso == USO_VARIABLE || s->uso == USO_VARIABLE_COMPTIME || s->uso == USO_PARAMETRO || s->uso == USO_OBJETO)) {
                char id_sanitizado[128];
                sanitizar_identificador(s->lexema, id_sanitizado, sizeof(id_sanitizado));

                if (s->tipo == TIPO_SINGLEF) {
                    double val = s->valor_comptime_valido ? s->valor_float : 0.0;
                    fprintf(f, "  (global %s (mut f32) (f32.const %g))\n", id_sanitizado, val);
                } else {
                    long val = s->valor_comptime_valido ? s->valor_int : 0;
                    fprintf(f, "  (global %s (mut i32) (i32.const %ld))\n", id_sanitizado, val);
                }

                if (s->uso == USO_OBJETO && s->tipo_clase != NULL) {
                    Simbolo *cls = buscar_identificador_semantico(tabla, s->tipo_clase);
                    if (cls != NULL) {
                        AtributoClase *attrs[64];
                        int n_attrs = 0;
                        recolectar_atributos_clase(tabla, cls, attrs, &n_attrs);
                        for (int a = 0; a < n_attrs; a++) {
                            char attr_id[128];
                            char attr_san[128];
                            snprintf(attr_id, sizeof(attr_id), "%s:%s", s->lexema, attrs[a]->nombre);
                            sanitizar_identificador(attr_id, attr_san, sizeof(attr_san));
                            if (attrs[a]->tipo == TIPO_SINGLEF) {
                                fprintf(f, "  (global %s (mut f32) (f32.const 0.0))\n", attr_san);
                            } else {
                                fprintf(f, "  (global %s (mut i32) (i32.const 0))\n", attr_san);
                            }
                        }
                    }
                }
            } else if (s->uso == USO_FUNCION) {
                char func_id[128];
                sanitizar_identificador(s->lexema, func_id, sizeof(func_id));
                fprintf(f, "  (global $__en_ejecucion%s (mut i32) (i32.const 0))\n", func_id);
            }
            s = s->siguiente;
        }
    }

    fprintf(f, "\n");

    int total_auxiliares = 0;
    bool exito_tipos = true;

    for (Polaca *curr = obtener_lista_polacas(); curr != NULL; curr = curr->siguiente) {
        if (!curr->nombre || strcmp(curr->nombre, "main") == 0 || strncmp(curr->nombre, "param_", 6) == 0) {
            continue;
        }
        if (!traducir_polaca_a_wat(curr, tabla, f, false, &total_auxiliares)) {
            exito_tipos = false;
        }
    }

    Polaca *p_main = obtener_polaca_por_nombre("main");
    if (p_main != NULL) {
        if (!traducir_polaca_a_wat(p_main, tabla, f, true, &total_auxiliares)) {
            exito_tipos = false;
        }
    }

    for (int i = 0; i < cant_strings; i++) {
        const char *t = strings_tabla[i].texto;
        int off = strings_tabla[i].offset;

        fprintf(f, "  (data (i32.const %d) \"", off);
        for (size_t c = 0; t[c] != '\0'; c++) {
            if (t[c] == '"' && (c == 0 || t[c+1] == '\0')) {
                continue;
            }
            if (t[c] == '\\') {
                fprintf(f, "\\\\");
            } else if (t[c] == '"') {
                fprintf(f, "\\\"");
            } else if (t[c] == '\n') {
                fprintf(f, "\\n");
            } else if (t[c] == '\t') {
                fprintf(f, "\\t");
            } else if ((unsigned char)t[c] < 32 || (unsigned char)t[c] > 126) {
                fprintf(f, "\\%02x", (unsigned char)t[c]);
            } else {
                fputc(t[c], f);
            }
        }
        fprintf(f, "\\00\")\n");
    }

    fprintf(f, ")\n");
    fclose(f);

    if (!exito_tipos) {
        remove(archivo_salida);
        return false;
    }

    return true;
}
