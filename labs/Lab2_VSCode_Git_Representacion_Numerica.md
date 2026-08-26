# Lab 2 — VS Code, Git desde el IDE, y Representación Numérica
## COEN 2210 — Introduction to Programming

**Duración:** 2 horas
**Precede:** Basado en Semana 2 — Hardware & Number Representation (lecture)
**Requisitos:** Cuenta de GitHub y conocimientos básicos de Git (Lab 1). Las computadoras del laboratorio ya tienen VS Code y el compilador instalados.

---

## Objetivos

Al finalizar este laboratorio, el estudiante podrá:
1. Usar VS Code para escribir, compilar, y ejecutar programas en C++.
2. Usar el panel de Source Control de VS Code para hacer commit y push a GitHub (sin consola).
3. Escribir programas C++ que muestren un número en decimal, binario, octal, y hexadecimal.
4. Demostrar overflow de forma práctica usando tipos de datos pequeños.

---

## Parte 0 — Instalación de VS Code y el compilador (opcional — no cuenta en el tiempo del lab)

> Las computadoras del laboratorio **ya tienen esto instalado** — esta sección es solo para quien quiera configurar su laptop personal. Sáltala si estás en el laboratorio y ve directo a la Parte 1.

### Instalar VS Code

**Windows:**
```powershell
winget install --id Microsoft.VisualStudioCode -e --source winget
```

**Mac:**
```bash
brew install --cask visual-studio-code
```
*(Requiere Homebrew — ver la nota de instalación en la guía del Lab 1 si no lo tienes.)*

> **Alternativa para ambos sistemas:** descarga directa desde [code.visualstudio.com](https://code.visualstudio.com/).

### Instalar el compilador de C++

VS Code **no incluye un compilador** — es solo un editor con herramientas de ayuda (autocompletado, debugging). El compilador se instala aparte, según el sistema operativo.

**Windows — MSYS2 + MinGW-w64 (método oficial recomendado por Microsoft):**

MSYS2 es un instalador/manejador de paquetes que trae GCC (el compilador) empaquetado para Windows — es el método que la documentación oficial de VS Code recomienda en vez de instalar GCC "a mano".

1. Instala MSYS2:
   ```powershell
   winget install --id MSYS2.MSYS2 -e --source winget
   ```
   **¿Qué hace esto?** Descarga e instala MSYS2 junto con su propia terminal especializada. **Qué deberías ver:** una barra de progreso y un mensaje de instalación exitosa (puede tardar 1-2 minutos).

2. Abre **"MSYS2 UCRT64"** desde el menú de inicio (no la terminal normal de Windows — MSYS2 instala su propia terminal, y es ahí donde corren los siguientes comandos) y ejecuta:
   ```bash
   pacman -Syu
   ```
   **¿Qué hace esto?** `pacman` es el manejador de paquetes de MSYS2 (equivalente a `winget` pero dentro de MSYS2). `-Syu` actualiza la lista de paquetes disponibles y todo lo que ya esté instalado a su versión más reciente — es un paso de mantenimiento que MSYS2 requiere antes de instalar algo nuevo, para evitar conflictos de versiones.

   **Qué deberías ver:** una lista de paquetes actualizándose. En algún punto puede preguntarte `:: Proceed with installation? [Y/n]` — escribe `Y` y presiona Enter. **Es posible que te pida cerrar la ventana y volver a abrir "MSYS2 UCRT64"** para terminar la actualización — si eso pasa, hazlo y continúa con el siguiente comando.

   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```
   **¿Qué hace esto?** Instala específicamente el paquete de GCC (el compilador de C/C++) para el entorno UCRT64.

   **Qué deberías ver:** una lista de paquetes a instalar con su tamaño total, y otra vez `:: Proceed with installation? [Y/n]` — confirma con `Y`. Puede tardar varios minutos dependiendo de la red.

   Ahora instala también el depurador (necesario más adelante para que el botón de "Debug" de VS Code funcione — sin esto, VS Code no puede ofrecer la opción específica de tu compilador y solo muestra plantillas genéricas que fallan):
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gdb
   ```
   **Qué deberías ver:** mismo patrón — confirma con `Y` cuando pregunte.

3. Agrega el compilador al PATH de Windows — este paso es necesario porque Windows no sabe automáticamente dónde buscar el comando `g++` a menos que le digas explícitamente en qué carpeta está instalado:

   Busca "Variables de entorno" en el menú de inicio → **Editar las variables de entorno del sistema** → **Variables de entorno** → en "Path" (bajo "Variables del sistema") → **Editar** → **Nuevo** → agrega `C:\msys64\ucrt64\bin`.

   **Qué deberías ver:** la nueva ruta agregada a la lista del Path — dale **Aceptar** en todas las ventanas para guardar el cambio.

4. Cierra **todas** las ventanas de terminal que tengas abiertas (el cambio de PATH no aplica a terminales ya abiertas) y abre una nueva terminal normal de Windows (`cmd` o `PowerShell`, ya no necesitas la terminal especial de MSYS2). Verifica:
   ```powershell
   g++ --version
   ```
   **Qué deberías ver:** algo como `g++.exe (Rev...) 13.x.x` — si en cambio dice "comando no reconocido", revisa que la ruta del paso 3 esté escrita exactamente igual (`C:\msys64\ucrt64\bin`) y que hayas cerrado/abierto la terminal después de guardarla.

*(Guía oficial completa con capturas de pantalla: [code.visualstudio.com/docs/cpp/config-mingw](https://code.visualstudio.com/docs/cpp/config-mingw))*

**Mac — Command Line Tools (incluye Clang):**

A diferencia de Windows, macOS no requiere un paquete externo — Apple distribuye su propio compilador (Clang) como parte de las herramientas de desarrollo del sistema.

```bash
xcode-select --install
```

**¿Qué hace esto?** Le pide a macOS que instale las "Command Line Developer Tools" — un paquete de Apple que incluye Clang (el compilador), Git, y otras herramientas de desarrollo básicas.

**Qué deberías ver:** una ventana emergente del sistema preguntando si quieres instalar las herramientas — dale clic a **Install**, acepta los términos, y espera (puede tardar varios minutos dependiendo de la red, ya que descarga varios cientos de MB).

Verifica al terminar:
```bash
clang++ --version
```
**Qué deberías ver:** algo como `Apple clang version 15.x.x`. Si te aparece un error, es probable que la instalación de las Developer Tools no haya terminado todavía — espera unos minutos más e intenta de nuevo.

### Instalar la extensión de C++ en VS Code

1. Abre VS Code.
2. Panel de Extensions (`Ctrl+Shift+X` / `Cmd+Shift+X`).
3. Busca **"C/C++"** e instala la extensión publicada por **Microsoft** (ícono azul).

### Verificar que todo el entorno funciona junto

> 🖱️ **Vas a usar la terminal integrada de VS Code** — no una terminal aparte. Esto es importante: si instalaste el compilador con VS Code ya abierto, esa sesión puede no haber "notado" el cambio todavía, así que verificamos desde dentro de VS Code para confirmar que es exactamente el entorno que vas a usar en el resto del lab.

1. Abre la terminal integrada: `Terminal → New Terminal`, o `` Ctrl+` `` (Windows) / `` Cmd+` `` (Mac).
2. Escribe:

**Windows:**
```powershell
g++ --version
gdb --version
```

**Mac:**
```bash
clang++ --version
```

**Qué deberías ver:** un número de versión para cada comando (ej. `g++ (MSYS2) 13.x.x` / `GNU gdb 14.x.x`, o `Apple clang version 15.x.x` en Mac). Si en cambio ves un error tipo "comando no reconocido" o "command not found", cierra VS Code por completo y vuelve a abrirlo (esto refresca el PATH), y prueba de nuevo. Si el problema persiste, avisa al profesor/asistente.

---

## Parte 1 — Tour rápido de VS Code (10 min)

> 🖱️ **Vas a usar VS Code**, no la terminal directamente (aunque VS Code tiene una terminal integrada que vamos a usar más adelante).

1. Abre VS Code.
2. `File → Open Folder...` y navega hasta tu carpeta `COEN2210_intro_to_programming` (la misma que creaste en el Lab 1).
3. Identifica estas partes de la interfaz:
   - **Explorer** (ícono de archivos, barra izquierda) — muestra el árbol de carpetas/archivos, como el Explorador/Finder pero dentro de VS Code.
   - **Editor** (panel central) — donde vas a escribir código.
   - **Source Control** (ícono de rama/branch, barra izquierda) — el reemplazo visual de `git status`/`add`/`commit` que usaste en consola en el Lab 1. Atajo: `Ctrl+Shift+G` (Windows) / `Cmd+Shift+G` (Mac).
   - **Terminal integrada** — es la misma terminal del Lab 1, pero ahora vive dentro de VS Code en vez de una ventana aparte. Ábrela con `Terminal → New Terminal` desde el menú, o con el atajo `` Ctrl+` `` (Windows) / `` Cmd+` `` (Mac).

**Qué deberías ver:** el árbol de carpetas a la izquierda debería mostrar `lab1-git/` (o `lab1-git-clon/`) si sigues en la misma carpeta padre del Lab 1.

---

## Parte 2 — Crear y correr tu primer programa en VS Code (15 min)

Vamos a crear una carpeta nueva para este laboratorio, dentro de tu carpeta de curso.

> 🖱️ **Vas a usar la terminal integrada de VS Code.** Ábrela con `` Ctrl+` `` (Windows) / `` Cmd+` `` (Mac) y escribe (mismo comando visto en el Tutorial de Terminal / Lab 1):

```bash
mkdir lab2-numeros
cd lab2-numeros
```

**Qué deberías ver:** el `Explorer` a la izquierda ahora muestra la carpeta `lab2-numeros` — VS Code refleja automáticamente los cambios que haces desde la terminal integrada.

Ahora crea un archivo nuevo: clic derecho sobre `lab2-numeros` en el Explorer → **New File** → nómbralo `hola.cpp`.

**Escribe este código en el editor:**

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hola desde VS Code!" << endl;
    return 0;
}
```

**Compilar y correr — dos formas:**

**Opción A (recomendada para entender qué pasa por dentro): manual, desde la terminal integrada.**

```bash
g++ hola.cpp -o hola
./hola
```
*(En Windows, el ejecutable puede requerir `.\hola.exe` en vez de `./hola`, dependiendo de tu terminal.)*

**¿Qué hace cada comando?**
- `g++ hola.cpp -o hola` — compila `hola.cpp` (traduce tu código a un programa ejecutable) y lo guarda con el nombre `hola`.
- `./hola` — ejecuta ese programa.

**Qué deberías ver:** el mensaje `Hola desde VS Code!` impreso en la terminal, justo debajo del comando que escribiste.

**Opción B (más rápida una vez ya entiendes el proceso): botón de Play.** En la esquina superior derecha del editor aparece un triángulo ▷ ("Run C/C++ File") una vez tienes la extensión instalada y un archivo `.cpp` abierto. Haz clic ahí.

**Qué deberías ver:** se abre un panel de terminal abajo mostrando el mismo mensaje `Hola desde VS Code!` — el botón internamente hace exactamente los mismos dos pasos de la Opción A (compilar y luego ejecutar), solo que sin que tengas que escribir el comando.

---

## Parte 3 — Conectar esta carpeta con GitHub desde VS Code (15 min)

Vamos a crear un repositorio nuevo para este lab, usando el flujo visual de VS Code en vez de comandos de consola.

> 🖱️ **Vas a usar VS Code**, específicamente el panel de Source Control.

1. Asegúrate de estar parado dentro de `lab2-numeros` (`File → Open Folder...` si es necesario, y selecciona esa carpeta específicamente — no la carpeta padre).
2. Abre el panel de **Source Control** (ícono de rama en la barra izquierda, o `Ctrl+Shift+G` en Windows / `Cmd+Shift+G` en Mac).
3. Si la carpeta no es un repositorio Git todavía, vas a ver un botón que dice **"Initialize Repository"** — haz clic ahí.

**¿Qué hace esto?** Es el equivalente visual de `git init` que usaste en consola en el Lab 1.

4. Ahora vas a ver `hola.cpp` listado bajo "Changes" — haz clic en el ícono de `+` a la derecha del archivo para hacer **stage** (equivalente a `git add`).
5. Escribe un mensaje en el cuadro de texto arriba (ej. "Primer commit: hola.cpp") y haz clic en el ✓ **Commit**.

**Qué deberías ver:** el archivo desaparece de la lista de "Changes" — ya quedó guardado en el historial local.

6. Para subirlo a GitHub, haz clic en **"Publish Branch"** (botón que aparece después de tu primer commit, en la parte inferior del panel).

**¿Qué hace esto?** Es el equivalente visual de los tres comandos que hiciste en consola en el Lab 1 (`git remote add origin`, `git branch -M main`, `git push -u origin main`) — VS Code los combina en un solo botón, y **automáticamente crea el repositorio en tu cuenta de GitHub** por ti (no necesitas ir a github.com a crear el repo manualmente, como sí hiciste en el Lab 1).

> **Autenticación:** la primera vez, VS Code va a abrir el navegador pidiéndote iniciar sesión en GitHub y autorizar la extensión — sigue ese flujo normalmente. Después de la primera vez, no te lo vuelve a pedir en esa computadora.

7. Elige si el repositorio nuevo será público o privado cuando VS Code te lo pregunte (recomendación: público, como discutimos para material de clase).

**Qué deberías ver:** un mensaje de confirmación, y si visitas tu perfil de GitHub, un repositorio nuevo llamado `lab2-numeros` con tu archivo `hola.cpp` adentro.

---

## Parte 4 — Programa: mostrar un número en decimal, binario, octal, y hex (35 min)

Ahora vamos a escribir el programa central de este lab, conectado directamente con lo visto en el lecture de esta semana.

Crea un archivo nuevo `representacion.cpp` (clic derecho en `lab2-numeros` → New File).

**Primera versión — usando los manipuladores vistos en el lecture:**

```cpp
#include <iostream>
using namespace std;

int main() {
    int numero;

    cout << "Escribe un numero entero: ";
    cin >> numero;

    cout << "Decimal: " << dec << numero << endl;
    cout << "Hexadecimal: " << hex << numero << endl;
    cout << "Octal: " << oct << numero << endl;

    return 0;
}
```

Compílalo y corre desde la terminal integrada (`g++ representacion.cpp -o representacion` seguido de `./representacion`, o `.\representacion.exe` en Windows) — o con el botón ▷ si prefieres, como vimos en la Parte 2.

**Qué deberías ver:** el programa pide un número, y lo muestra en las tres bases. Prueba con `47` — deberías obtener los mismos resultados que calculaste a mano en el lecture (`2f` en hex, `57` en octal).

**Problema a notar:** el hexadecimal sale en minúscula (`2f`) y sin el prefijo `0x`. Vamos a mejorar el programa para que se vea más claro, usando manipuladores adicionales:

```cpp
#include <iostream>
using namespace std;

int main() {
    int numero;

    cout << "Escribe un numero entero: ";
    cin >> numero;

    cout << "Decimal: " << dec << numero << endl;
    cout << "Hexadecimal: " << hex << uppercase << showbase << numero << endl;
    cout << "Octal: " << oct << numero << endl;

    return 0;
}
```

**¿Qué hace cada manipulador nuevo?**
- `uppercase` — muestra las letras A-F en mayúscula.
- `showbase` — agrega el prefijo correspondiente (`0x` para hex, `0` para octal) automáticamente.

**Qué deberías ver ahora:** con `47`, la salida hex debería verse como `0X2F` en vez de `2f`.

**Ejercicios para practicar por tu cuenta (modifica el programa y prueba):**

1. Agrega una línea que también muestre el número en binario. *(Pista: C++ no tiene un manipulador directo para binario como `hex`/`oct` — vas a necesitar investigar `std::bitset<8>`, o escribir tu propia lógica usando lo aprendido en el lecture sobre divisiones sucesivas entre 2.)*
2. Modifica el programa para que, en vez de pedir un número, convierta automáticamente los números 10, 100, y 255 (mostrando los tres resultados uno tras otro).
3. ¿Qué pasa si el usuario escribe un número negativo? Pruébalo y observa el resultado en hexadecimal — ¿tiene sentido con lo que sabes sobre cómo se almacenan los números en memoria?

---

## Parte 5 — Programa: overflow en vivo (20 min)

Vamos a ver en código el concepto de overflow que se discutió en el lecture (Parte 6).

Crea un archivo nuevo `overflow.cpp`:

```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned char contador = 250;

    for (int i = 0; i < 10; i++) {
        cout << "Valor actual: " << (int)contador << endl;
        contador = contador + 1;
    }

    return 0;
}
```

**¿Por qué `(int)contador` en vez de solo `contador`?** `unsigned char` es un tipo de carácter — si lo imprimes directamente, `cout` intenta mostrarlo como un símbolo de texto en vez de un número. `(int)contador` le dice a C++ "trata este valor como un número entero para mostrarlo", una conversión de tipo llamada *cast*.

Compílalo y corre desde la terminal integrada (`g++ overflow.cpp -o overflow` seguido de `./overflow`, o `.\overflow.exe` en Windows) — o con el botón ▷.

**Qué deberías ver:** el contador sube normalmente — 250, 251, 252, 253, 254, 255 — y en el siguiente paso, en vez de continuar a 256, **vuelve a 0**. Este es exactamente el comportamiento que se explicó en el lecture con la analogía del odómetro — ahora lo estás viendo ejecutarse de verdad.

**Ejercicio para practicar por tu cuenta:** cambia `unsigned char` por `unsigned short` (rango 0-65,535) y ajusta el valor inicial y el número de iteraciones del `for` para poder observar ese overflow también. ¿Cuántas iteraciones necesitas como mínimo para verlo, empezando desde 65,530?

---

## Parte 6 — Guardar tu progreso en GitHub (15 min)

> 🖱️ **Vas a usar el panel de Source Control de VS Code.**

1. Abre el panel de Source Control (`Ctrl+Shift+G` en Windows / `Cmd+Shift+G` en Mac).
2. Deberías ver `representacion.cpp` y `overflow.cpp` listados bajo "Changes".
3. Haz clic en el `+` junto a **"Changes"** (arriba de la lista) en vez de archivo por archivo — esto hace stage de todos los archivos a la vez (equivalente a `git add -A` que usaste en consola).
4. Escribe un mensaje descriptivo, ej. "Agrego programas de representacion numerica y overflow".
5. Haz clic en ✓ **Commit**.
6. Haz clic en **Sync Changes** (o el ícono de flechas circulares) para hacer push.

**Qué deberías ver:** al refrescar tu repositorio en github.com, ambos archivos `.cpp` aparecen ahí, junto con `hola.cpp` de la Parte 2.

---

## Parte 7 — Repaso (10 min)

| Acción en consola (Lab 1) | Equivalente visual en VS Code (Lab 2) |
|---|---|
| `git init` | Botón "Initialize Repository" |
| `git add archivo` | Clic en `+` junto al archivo |
| `git add -A` | Clic en `+` junto a "Changes" |
| `git commit -m "mensaje"` | Escribir mensaje + clic en ✓ Commit |
| `git remote add` + `git push -u` | Botón "Publish Branch" |
| `git push` (después de la primera vez) | Botón "Sync Changes" |

---

## Apéndice — Solución de problemas: el botón ▷ pide "Select a debug configuration" (Windows)

Si seguiste la Parte 0 tal como está (incluyendo la instalación de `gdb` junto con `gcc`), no deberías toparte con esto. Si aun así te aparece una pantalla pidiendo elegir entre **"gdb launch"** y **"windows launch"**, o un `launch.json` genérico con un placeholder tipo `"Enter program name, e.g. C:\..."`, es casi siempre porque falta `gdb` — instalado por separado de `gcc` en MSYS2.

**Cómo confirmarlo:** en la terminal integrada de VS Code:
```powershell
gdb --version
```
Si da "comando no reconocido", instálalo desde la terminal **"MSYS2 UCRT64"**:
```bash
pacman -S mingw-w64-ucrt-x86_64-gdb
```
Cierra **todas** las ventanas de terminal y de VS Code por completo, vuelve a abrir, y prueba de nuevo: botón ▾ (junto al ▷) → **"Debug C/C++ File"**.

**Nota sobre lo que vas a ver al depurar (`F5`) vs. correr (▷):** una vez configurado, usar `F5` o "Debug C/C++ File" abre un panel adicional llamado **Debug Console** (distinto de la terminal integrada normal), y la salida en la terminal puede incluir líneas extra generadas por GDB (mensajes de arranque/cierre del depurador) que no aparecen cuando usas la Opción A de la Parte 2 (compilar/correr manualmente) o el botón ▷ simple sin depurar. Eso es esperado — GDB añade ese "ruido" porque está monitoreando la ejecución del programa para permitir breakpoints y ejecución paso a paso, algo que no está en el alcance de este lab. **Para las Partes 2, 4, y 5 de este documento, sigue usando la terminal integrada o el botón ▷ simple — no hace falta usar el depurador.**

---

## Entregable del laboratorio

Envía al profesor el enlace de tu repositorio `lab2-numeros` en GitHub, con al menos **3 commits** visibles y los archivos `hola.cpp`, `representacion.cpp`, y `overflow.cpp`.

---

## Próxima sesión

**Semana 3 — Introduction to C++** — seguimos con sintaxis básica, variables, y entrada/salida, ya con el entorno de VS Code + Git completamente configurado.
