const fs = require("fs");
const wabtFactory = require("wabt");

async function runWasm(watPath) {
    const wabt = await wabtFactory();
    const wat = fs.readFileSync(watPath, "utf8");
    const parsed = wabt.parseWat(watPath, wat);
    const { buffer } = parsed.toBinary({});

    let memory;
    const importObject = {
        env: {
            pout_int: (val) => console.log("[SALIDA ENTERO]:", val),
            pout_float: (val) => console.log("[SALIDA FLOAT]:", val),
            pout_str: (offset, len) => {
                const bytes = new Uint8Array(memory.buffer, offset, len);
                const str = new TextDecoder("utf8").decode(bytes);
                process.stdout.write(str);
            },
            error_exit: (code) => {
                console.error("\n[RUNTIME ABORT] Codigo de error:", code);
                process.exit(code || 1);
            }
        }
    };

    const wasmModule = await WebAssembly.instantiate(buffer, importObject);
    memory = wasmModule.instance.exports.memory;
    try {
        wasmModule.instance.exports.main();
    } catch (e) {
        console.error("[TRAP CAPTURADO]:", e.message);
    }
}

const target = process.argv[2] || "final.wat";
runWasm(target);
