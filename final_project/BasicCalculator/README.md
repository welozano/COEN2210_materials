# Basic Integer Calculator — VS Code

Código de apoyo para COEN 2210. Incluye un menú de operaciones y separación en functions, con entrada/salida estándar de C++.

## Archivos y responsabilidades

| Archivo | Responsabilidad |
|---|---|
| `main.cpp` | Menu loop, `switch` y function calls. |
| `utils.h` / `utils.cpp` | Prototypes y definitions para input, validación, presentación y pausa. |
| `mathOps.h` / `mathOps.cpp` | Prototypes y definitions de las cuatro operaciones aritméticas. |

Los `.h` declaran las functions que otros archivos necesitan conocer. Los `.cpp` contienen sus definitions. Cada `.cpp` se compila y luego el linker reúne las piezas en un executable. No se incluye un `.cpp` desde otro archivo.

## Compilar y ejecutar

Abre **esta carpeta** como carpeta raíz de VS Code. Usa el compilador instalado durante el curso y abre la terminal integrada en esta carpeta.

**Windows:**

Compilar:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp utils.cpp mathOps.cpp -o BasicCalculator.exe
```

Ejecutar:

```powershell
.\BasicCalculator.exe
```

**Mac:**

Compilar:

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp utils.cpp mathOps.cpp -o BasicCalculator
```

Ejecutar:

```bash
./BasicCalculator
```

**¿Qué hace esto?** Compila los tres archivos `.cpp` y los enlaza en un solo executable; el segundo comando inicia el menú.

**Qué deberías ver:** un menú con Addition, Subtraction, Multiplication, Division y Exit application. Compilar solamente `main.cpp` no basta: las definitions de las functions están en los otros dos archivos.

## Comportamiento del ejemplo

- Cada respuesta debe contener un solo integer. El programa vuelve a pedir input si recibe letras, decimales o un value fuera del rango de `int`.
- La división es integer division: `7 / 2` produce `3`.
- Se rechaza la división entre cero.
- Los cálculos usan `long long` antes de operar para admitir resultados de mayor tamaño que los operandos `int`.
- La pausa solicita **Enter**. `pressAnyKey` conserva su nombre del ejemplo original, pero ya no usa `conio.h` ni `_getch()`.
- La terminal conserva el output anterior; se retiró `system("cls")` para permitir su uso en Windows y Mac.

## Pruebas sugeridas

| Prueba | Resultado esperado |
|---|---|
| Addition: `8`, `5` | `13` |
| Subtraction: `8`, `5` | `3` |
| Multiplication: `8`, `5` | `40` |
| Division: `7`, `2` | `3` |
| Division: `7`, `0` | Mensaje de error; regresa al menú después de Enter. |
| Menu option: `9` | Mensaje de opción inválida. |
| Input: `abc` o `2.5` | Solicita nuevamente un integer. |
| Menu option: `5` | Termina el programa. |

El menú y las functions son una referencia de organización para CoRe Data Analyzer. El proyecto requiere sus propias operaciones sobre observations.
