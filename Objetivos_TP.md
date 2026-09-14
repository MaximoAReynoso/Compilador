# Temas Asignados

**Temas que nos tocaron:**  
`3` `7` `10` `14` `15` `17` `19` `22` `24` `29` `32` `33`

---

## Temas Asignados (Extracto)

### 3. Enteros (16 bits)
Constantes enteras con valores entre $-2^{15}$ y $2^{15} - 1$ que se escriben como una secuencia de dígitos seguidos del sufijo `$i`.

### 7. Punto Flotante de 32 bits
Números reales con signo y parte exponencial. La parte exponencial puede estar ausente. Si está presente, el exponente comienza con la letra `s` y el signo del exponente puede estar ausente (su ausencia se asume como exponente positivo).

* Puede estar ausente la parte entera pero el `.` y la parte decimal son obligatorias.
* **Ejemplos válidos:** `1.0`, `.6`, `-1.2`, `3.0s-5`, `.2s34`, `2.5s-1`, `15.2`, `0.0`, `1.2s+10`
* **Considerar el rango:**
  * $1.17549435s{-}38 < x < 3.40282347s{+}38 \cup -3.40282347s{+}38 < x < -1.17549435s{-}38 \cup \{0.0\}$
* Se debe incorporar a la lista de palabras reservadas la palabra **`SINGLEF`**.

### 10. Cadenas multilínea
Cadenas de caracteres delimitadas por `"`. Estas cadenas pueden ocupar más de una línea. *(En la Tabla de símbolos se guardará la cadena sin los saltos de línea)*.

* **Ejemplo:**
  ```text
  "¡Hola
           mundo!"
  ```

### 15. Comentarios de 1 línea
Comentarios que comiencen con `//` y terminen con el fin de línea.

---

## Objetivo del Trabajo Práctico

Desarrollar un **Analizador Léxico** que reconozca los siguientes tokens:

* **Identificadores:** Cuyos nombres pueden tener hasta 22 caracteres de longitud. El primer carácter sólo puede ser una letra, y el resto pueden ser letras, dígitos y `_`. Los identificadores con longitud mayor serán truncados y esto se informará como *Warning*. Las letras utilizadas en los nombres de identificador sólo pueden ser minúsculas.
* **Constantes:** Correspondientes al tema particular asignado a cada grupo.
  > **Nota:** Para aquellas constantes que pueden llevar signo, la distinción del uso del símbolo `-` como operador aritmético o signo de una constante se postergará hasta el trabajo práctico Nro. 2.
* **Operadores aritméticos:** `+`, `-`, `*`, `/`
* **Operadores de asignación:** `:=`, `=`
* **Comparadores:** `>=`, `<=`, `>`, `<`, `==`, `!=`
* **Otros símbolos:** `(`, `)`, `;`, `:`
* **Cadenas de caracteres:** Correspondientes al tema particular de cada grupo.
* **Palabras reservadas:** Pueden escribirse con mayúsculas o minúsculas:
  `IF`, `else`, `END_if`, `begin`, `END`, `POUT`, `RET`, `class`, `function`
* Y demás símbolos / tokens indicados en los temas particulares asignados a cada grupo.

---

### Elementos a descartar por el Analizador Léxico

El Analizador Léxico debe eliminar de la entrada (reconocer, pero no informar como tokens al Analizador Sintáctico), los siguientes elementos:

* Comentarios correspondientes al tema particular de cada grupo.
* Caracteres en blanco, tabulaciones y saltos de línea, que pueden aparecer en cualquier lugar de una sentencia.
