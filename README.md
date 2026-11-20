# Compilador
---

## Como compilar el proyecto para obtener el ejecutable
```bash
./execute.sh
```

Para ejecutar el código WebAssembly generado (`.wat`), asegurarse de tener Node.js e instaladas las dependencias (`wabt`):
```bash
npm install
```

## Como probar el compilador y ejecutar los tests
Una vez compilado el proyecto, se puede compilar cualquier archivo fuente indicando su ruta:

```bash
./compilador tests/01_programas_completos/test_completo_valido.txt
```
o bien:
```bash
./compilador ruta_archivo_a_probar
```

Si el archivo no posee errores léxicos, sintácticos ni semánticos, el compilador generará el archivo `final.wat`.

### Ejecución del módulo WebAssembly (`final.wat`)
El compilador únicamente traduce el programa a WebAssembly Text (`final.wat`); para ver la salida en tiempo de ejecución o comprobar los errores de *runtime* (como división por cero, *overflow* o recursión en `tests/12_errores_runtime_tp4/`), se debe ejecutar el archivo generado con:

```bash
node runner_wasm.js final.wat
```
