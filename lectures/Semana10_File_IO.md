# Semana 10 — File Input/Output Management
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Gaddis, *Starting Out with C++: From Control Structures through Objects* — Capítulo 5, sección 5.11; extensión de curso sobre positions y `fstream`

**Duración:** 170 min (lectura)
**Precede a:** Lab 10 — File I/O continuation / buffer

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:

1. Distinguir entre sobrescribir un text file, añadir data al final y actualizar data existente.
2. Abrir un output file con `ios::app` para conservar su contenido anterior.
3. Permitir que la persona indique el filename que un program debe abrir y validar esa apertura.
4. Explicar qué representa una read position y una write position.
5. Usar `tellg`, `tellp`, `seekg` y `seekp` para observar o mover una position de file.
6. Usar un `fstream` con `ios::in | ios::out` para actualizar un fixed-width record.
7. Explicar por qué un text record de longitud variable se modifica reescribiendo un temporary file, no con una escritura in-place.

---

## Cómo probar los programas de esta lecture

Cada bloque es un programa completo e independiente, excepto cuando se indique que un file debe existir antes de ejecutar. Crea una carpeta de práctica distinta para esta lecture. Antes de ejecutar, identifica el file que el program espera encontrar o creará, el stream que usa y el efecto esperado sobre el contenido existente.

Después de cada ejecución, abre el file desde el Explorer de VS Code. El output en la terminal muestra lo que el program decidió; el contenido del file confirma qué data persistió.

---

## Parte 1 — Recordatorio: el flujo secuencial ya conocido (15 min)

En Semana 9 y Lab 9 ya construimos programas que crean un text file con `ofstream`, validan la apertura, escriben data, cierran el stream y luego abren el file con `ifstream`. También recorrimos lines con `getline` y values numéricos con `while (inputFile >> value)`.

No repetiremos esos programas completos. Esta tabla será el punto de partida para el material nuevo de hoy.

| Patrón ya trabajado | Idea que debe recordarse | Dónde se practicó |
|---|---|---|
| `ofstream` + validation + `close()` | Un output stream puede crear un file, pero debe verificarse antes de escribir y cerrarse al terminar. | Semana 9, sección 5.1; Lab 9, Parte 2. |
| `ifstream` + `getline` dentro de `while` | Cada iteration lee una line; al no quedar otra line, el loop termina. | Semana 9, sección 5.2; Lab 9, Parte 3. |
| `while (inputFile >> value)` | La extraction intenta leer y produce `true` solo si obtuvo un numeric value. | Lab 9, Parte 4. |
| Counter y accumulator | El program cuenta y procesa los values que realmente pudo leer. | Lab 9, Parte 4. |
| `ofstream` sin mode adicional | Si el file ya existe, su contenido se reemplaza. | Semana 9, sección 5.1. |

El nuevo problema no es volver a crear un report ni volver a calcular un average. Es decidir qué operación corresponde cuando el file ya contiene data: añadir una new line, regresar a una position conocida o cambiar un record sin dañar los demás.

**Para practicar por tu cuenta:** ¿por qué `while (!inputFile.eof())` no sustituye correctamente a `while (inputFile >> value)`?

<details>
<summary>Ver respuesta</summary>

`eof()` solo se activa después de que una lectura intenta ir más allá del final. La extraction dentro de la condition controla el loop con el éxito real de cada lectura y evita procesar un value inexistente o repetido.

</details>

---

## Parte 2 — Conservar un historial: append y filenames elegidos en ejecución (30 min)

### 2.1 — Añadir una observación no es crear un report nuevo

**Problema:** un laboratory mantiene una bitácora de observaciones durante el día. Antes de ejecutar el program, el file `daily_notes.txt` ya puede contener notes de otras personas. La persona técnica debe poder entrar una observation nueva y guardarla sin borrar las anteriores.

Un `ofstream` por defecto reemplazaría el file. Para expresar la intención de conservar lo existente y escribir al final, se usa el open mode `ios::app` (*append*).

```cpp
#include <fstream>                                       // Provides ofstream for file output
#include <iostream>                                      // Provides cin, cout, and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    string note;                                         // Stores the note entered by the user

    cout << "Enter a daily note: ";                      // Prompts for one complete note
    getline(cin, note);                                  // Reads the complete note including spaces

    ofstream outputFile("daily_notes.txt", ios::app);   // Opens the file in append mode
    if (!outputFile) {                                  // Tests whether the output file opened successfully
        cout << "Error: Could not open daily_notes.txt" << endl; // Reports the opening failure
        return 1;                                       // Ends the program with an error status
    }                                                    // Ends the output-file validation

    outputFile << note << endl;                          // Adds the note after existing file contents
    outputFile.close();                                  // Flushes and closes the output stream
    cout << "Note added to daily_notes.txt" << endl;    // Confirms that the note was appended

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function
```

Si se ejecuta primero con `Battery shelf checked.` y luego con `Tool cart returned.`, el file debe contener ambas lines, en ese orden. Contrasta ese resultado con `ofstream outputFile("daily_notes.txt");`, que reemplazaría el historial.

### 2.2 — Elegir qué file se abrirá

Un program tampoco tiene que hardcodear siempre un filename. La persona puede indicar qué log desea consultar. El programa completo siguiente recibe el filename, intenta abrirlo, valida la apertura y muestra sus lines. La lectura con `getline` es un pattern ya conocido; el elemento nuevo es que el file no se decide hasta que la persona entra su name.

```cpp
#include <fstream>                                       // Provides ifstream for file input
#include <iostream>                                      // Provides cin, cout, and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    string fileName;                                    // Stores the filename entered by the user
    ifstream inputFile;                                 // Declares an input stream before opening a specific file
    string line;                                        // Stores one complete line read from the file

    cout << "Enter input filename: ";                   // Prompts for the name of an existing file
    getline(cin, fileName);                             // Reads the filename including any spaces
    inputFile.open(fileName);                           // Attempts to connect the stream to that file

    if (!inputFile) {                                   // Tests whether the requested file opened successfully
        cout << "Error: Could not open the requested file." << endl; // Reports the opening failure
        return 1;                                       // Ends the program with an error status
    }                                                    // Ends the input-file validation

    cout << "File contents:" << endl;                   // Labels the lines that will be displayed
    while (getline(inputFile, line)) {                   // Repeats while one complete line is read successfully
        cout << line << endl;                            // Displays the line that was read
    }                                                    // Ends the line-reading loop

    inputFile.close();                                   // Closes the input stream after reading
    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function
```

El `open` no garantiza que el file exista ni que el program tenga permission para leerlo. Por eso el `if (!inputFile)` aparece antes del `while`. Prueba primero con `daily_notes.txt` y luego con un filename que no exista para comparar ambos caminos.

**Para practicar por tu cuenta:** si `daily_notes.txt` tiene tres lines y ejecutas el programa de append dos veces, ¿cuántas lines esperas encontrar? ¿Qué cambiaría si se eliminara `ios::app`?

<details>
<summary>Ver respuesta</summary>

Habría cinco lines. Sin `ios::app`, la primera ejecución reemplazaría las tres existentes y la segunda reemplazaría la line creada por la primera; al final quedaría solamente la última note.

</details>

---

## Parte 3 — Positions: volver a un punto conocido y actualizar un fixed-width record (55 min)

### 3.1 — La position de la próxima operación

En los programs anteriores, un sequential loop comienza al inicio del file y avanza hasta el final. Ese recorrido es suficiente para leer un report completo o calcular un average, pero no resuelve una necesidad distinta: regresar a un record específico para examinarlo o actualizarlo.

**Problema:** un file de status contiene records de ancho fijo, uno por line. El program debe leer el primer status, regresar al inicio y actualizar solamente ese status, sin tocar el segundo. Para resolverlo, el program necesita saber dónde quedó después de leer y necesita indicar desde qué punto escribirá.

Esa ubicación interna se llama **position**. La **read position** marca desde dónde ocurrirá la próxima lectura; la **write position** marca desde dónde ocurrirá la próxima escritura. Las cuatro member functions siguientes existen precisamente para observar o cambiar esas positions.

| Member function | Opera sobre | Resultado o efecto |
|---|---|---|
| `tellg()` | Read position | Devuelve la position de la próxima lectura. |
| `tellp()` | Write position | Devuelve la position de la próxima escritura. |
| `seekg(position)` | Read position | Mueve la próxima lectura a una position indicada. |
| `seekp(position)` | Write position | Mueve la próxima escritura a una position indicada. |

Los suffixes ayudan a recordar el propósito: `g` significa *get* (obtener data del file) y `p` significa *put* (colocar data en el file).

Antes de ejecutar el programa, crea manualmente `device_status.txt` en la misma carpeta con este contenido exacto:

```text
READY
NEXT
```

El first record tiene cinco characters: `READY`. El program lo reemplazará por `PAUSE`, que también tiene cinco. El line break que sigue a `READY` no se modifica.

### 3.2 — `fstream`, `tell*` y `seek*` en un mismo programa

El program necesita leer y escribir el mismo file, por lo que usa `fstream`. Los open modes `ios::in | ios::out` indican ambas operaciones. Antes de mirar el code, sigue la secuencia que el program debe realizar:

1. Guardar la read position inicial y leer `READY`.
2. Observar que la read position avanzó después de esa line.
3. Usar `seekg` para volver al inicio y comprobar que se puede leer `READY` otra vez.
4. Usar `seekp` para colocar la write position al inicio y reemplazar solo los cinco characters del primer record.

En un `fstream` que alterna input y output, no se debe asumir que las positions se comportan como dos cursores totalmente independientes. Antes de cambiar de leer a escribir, o viceversa, el program debe usar explícitamente `seekg`, `seekp`, `flush` o `close` según la operación que necesite.

`tellg` y `tellp` devuelven un value de type `streampos`, que representa una position en el file. Para mostrar ese value como un offset en la terminal, el ejemplo lo convierte temporalmente a `streamoff` mediante `static_cast<streamoff>(...)`. Esa conversión es solo para observar el movimiento; no se usa para hacer cálculos.

```cpp
#include <fstream>                                       // Provides fstream for file input and output
#include <iostream>                                      // Provides cout and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    fstream statusFile("device_status.txt", ios::in | ios::out); // Opens one file for both input and output
    string firstStatus;                                  // Stores the first status read from the file
    streampos initialReadPosition;                       // Stores the read position before the first read
    streampos afterReadPosition;                         // Stores the read position after the first read
    streampos writePositionBeforeUpdate;                 // Stores the write position before the update

    if (!statusFile) {                                  // Tests whether the file opened for both operations
        cout << "Error: Could not open device_status.txt" << endl; // Reports the opening failure
        return 1;                                       // Ends the program with an error status
    }                                                    // Ends the file-opening validation

    initialReadPosition = statusFile.tellg();            // Records the initial read position
    getline(statusFile, firstStatus);                    // Reads the first fixed-width status line
    afterReadPosition = statusFile.tellg();              // Records the read position after that line
    cout << "First status: " << firstStatus << endl;     // Displays the status that was read
    cout << "Read position moved from " << static_cast<streamoff>(initialReadPosition) // Starts the position report
         << " to " << static_cast<streamoff>(afterReadPosition) << endl; // Displays the observed read positions

    statusFile.seekg(0, ios::beg);                       // Moves the read position back to the beginning
    writePositionBeforeUpdate = statusFile.tellp();      // Records the write position after returning to the beginning
    cout << "Write position before update: " << static_cast<streamoff>(writePositionBeforeUpdate) << endl; // Displays the write position
    getline(statusFile, firstStatus);                    // Reads the first status again from the new read position
    cout << "Status after seekg: " << firstStatus << endl; // Confirms that seekg returned to the first record

    statusFile.seekp(0, ios::beg);                       // Moves the write position to the beginning
    statusFile << "PAUSE";                              // Replaces READY with another five-character status
    statusFile.flush();                                  // Forces the updated characters to the file
    statusFile.close();                                  // Closes the combined input/output stream

    cout << "Status updated from READY to PAUSE." << endl; // Confirms the fixed-width update

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function
```

Después de ejecutar, abre `device_status.txt`. Debe quedar así:

```text
PAUSE
NEXT
```

### 3.3 — La regla crítica de una actualización in-place

El programa anterior demuestra un update que funciona. Ahora debemos evaluar cuándo esa misma técnica deja de ser segura. El ejemplo funciona porque `READY` y `PAUSE` tienen cinco characters. Si el program escribiera `OFFLINE` en la misma position, los dos characters adicionales ocuparían el line break y el inicio del segundo record. Si escribiera `OK`, sobrarían characters de `READY`. En los dos casos, el file deja de tener la estructura esperada.

| Cambio solicitado | ¿Es seguro con `seekp(0, ios::beg)`? | Razón |
|---|---|---|
| `READY` → `PAUSE` | Sí | Ambos statuses ocupan cinco characters. |
| `READY` → `OFFLINE` | No | El nuevo status es más largo y sobrescribe data posterior. |
| `READY` → `OK` | No sin otra estrategia | Sobran characters del status anterior. |

> ⚠️ **Advertencia:** `seekg` y `seekp` no convierten un text file ordinario en una base de datos. Úsalos para positions conocidas y updates de ancho fijo; no para insertar o borrar text de longitud variable.

**Para practicar por tu cuenta:** cambia manualmente el primer status a `ERROR` y vuelve a ejecutar. ¿Por qué el program sigue siendo seguro? Luego cambia el status a `WAIT` y explica por qué ya no conviene usar este mismo update.

<details>
<summary>Ver respuesta</summary>

`ERROR` tiene cinco characters, igual que `PAUSE`, por lo que el replacement conserva el ancho. `WAIT` tiene cuatro; escribir cinco characters sobre ese record modifica el line break o la data siguiente.

</details>

### Conclusión de la Parte 3 — Takeaway y best practice

`tellg`, `tellp`, `seekg` y `seekp` sirven para trabajar con una **position conocida** dentro de un file; no son una solución general para editar cualquier text. La best practice es decidir primero qué clase de cambio necesita el program:

- Usa positioning con `fstream` solamente cuando conoces la position y el replacement conserva exactamente el ancho del record.
- Antes de cambiar entre reading y writing, mueve la position explícitamente con `seekg` o `seekp` y verifica qué operación ocurrirá después.
- Si el replacement puede ser más largo o más corto, no escribas directamente sobre el original. Usa el workflow de temporary file que sigue en la Parte 4.

---

## Parte 4 — Editar un record de longitud variable (35 min)

La Parte 3 resolvió un cambio de longitud fija. Esta parte responde al caso que esa solución no puede manejar.

**Problema:** ahora el file contiene lines como `Device: Board-14` y una persona necesita cambiarla a `Device: Board-1407`. El new text no tiene la misma longitud. Escribirlo con `seekp` directamente movería o sobrescribiría characters que pertenecen a las lines posteriores.

Para este tipo de edición, el program no modifica el original character por character. Produce un temporary file nuevo siguiendo este workflow:

1. Abre el original con `ifstream` y valida la apertura.
2. Abre un temporary file con `ofstream` y valida la apertura.
3. Recorre el original line por line con `getline`.
4. Si una line es la que debe cambiarse, escribe la new version en el temporary file; si no, copia la line original.
5. Cierra ambos streams antes de reemplazar el original con el temporary file.

Este approach conserva todas las lines posteriores aunque la replacement line sea más larga o más corta. Es el pattern apropiado para text records de longitud variable.

Antes de ejecutar, crea `inspection_notes.txt` con este contenido:

```text
Inspection Notes
Device: Board-14
Status: Pending
```

El programa siguiente no modifica ese file directamente. Lee cada line del original y construye `inspection_notes_updated.txt`. Cuando encuentra exactamente `Device: Board-14`, escribe la replacement line; para las demás lines, copia el contenido original.

```cpp
#include <fstream>                                       // Provides ifstream and ofstream for file access
#include <iostream>                                      // Provides cout and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    ifstream inputFile("inspection_notes.txt");         // Opens the original notes file for input
    ofstream temporaryFile("inspection_notes_updated.txt"); // Creates the updated temporary file
    string line;                                         // Stores one line read from the original file
    string targetLine = "Device: Board-14";             // Identifies the line that must be replaced
    string replacementLine = "Device: Board-1407";      // Stores the longer replacement line

    if (!inputFile) {                                   // Tests whether the original file opened successfully
        cout << "Error: Could not open inspection_notes.txt" << endl; // Reports the input-file failure
        return 1;                                       // Ends the program with an error status
    }                                                    // Ends the input-file validation

    if (!temporaryFile) {                               // Tests whether the temporary file opened successfully
        cout << "Error: Could not create the updated notes file." << endl; // Reports the output-file failure
        inputFile.close();                               // Closes the original file before ending
        return 1;                                       // Ends the program with an error status
    }                                                    // Ends the output-file validation

    while (getline(inputFile, line)) {                   // Repeats while one original line is read successfully
        if (line == targetLine) {                        // Tests whether the current line needs replacement
            temporaryFile << replacementLine << endl;    // Writes the longer replacement line
        } else {                                         // Handles every line that does not need replacement
            temporaryFile << line << endl;               // Copies the original line unchanged
        }                                                // Ends the line-selection structure
    }                                                    // Ends the original-file traversal

    inputFile.close();                                   // Closes the original input stream
    temporaryFile.close();                               // Closes the updated output stream
    cout << "Updated notes saved to inspection_notes_updated.txt" << endl; // Confirms the completed rewrite

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function
```

Al abrir `inspection_notes_updated.txt`, debe verse lo siguiente:

```text
Inspection Notes
Device: Board-1407
Status: Pending
```

El original continúa intacto. Reemplazarlo de forma física por el temporary file depende de operaciones del file system que no son el objetivo de esta sesión; aquí nos concentramos en la decisión y en la reescritura segura del contenido.

La siguiente tabla conecta los tres problemas de la sesión con su estrategia correcta.

| Tipo de cambio | Estrategia correcta |
|---|---|
| Reemplazar cinco characters por cinco characters en una position conocida | `fstream` y `seekp`. |
| Añadir una new line al final | `ofstream` con `ios::app`. |
| Cambiar una line por text de otra longitud | Recorrer el original y reescribirlo en un temporary file. |

No implementaremos todavía el reemplazo físico del original por el temporary file: esa operación depende del file system y añade detalles que no ayudan a entender la decisión principal. Lo importante hoy es elegir la estrategia correcta antes de escribir code.

**Para practicar por tu cuenta:** un file tiene 50 lines y se necesita cambiar la line 27 por un mensaje más largo. ¿Qué strategy usarías y por qué?

<details>
<summary>Ver respuesta</summary>

Usaría un temporary file: leería cada line del original y escribiría la replacement solamente al llegar a la line 27. Un `seekp` directo no es seguro porque la new line cambia la longitud del contenido posterior.

</details>

---

## Práctica guiada — Analizar una actualización mediante temporary file (35 min)

Esta práctica es de **lecture**, no un nuevo ejercicio de lab. Trabajaremos un programa completo en pantalla: primero se describe el file inicial, luego se hace trace de cada iteration y finalmente se responden preguntas sobre las decisiones del code.

**Problema:** `service_notes.txt` contiene information sobre un device. La prioridad actual dice `Priority: Normal`, pero debe convertirse en `Priority: Requires supervisor review`. Como la replacement line es más larga, el program debe crear `service_notes_updated.txt` sin alterar el original.

Antes de ejecutar, crea `service_notes.txt` con estas lines:

```text
Device: Panel-7
Priority: Normal
Technician: Alex
```

Lee el programa por bloques: apertura y validation, recorrido y selection, luego cierre. No lo copies todavía; primero predice qué escribirá cada branch del `if` en cada vuelta del `while`.

```cpp
#include <fstream>                                       // Provides ifstream and ofstream for file access
#include <iostream>                                      // Provides cout and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    ifstream inputFile("service_notes.txt");            // Opens the original notes file for input
    ofstream temporaryFile("service_notes_updated.txt"); // Creates the updated temporary file
    string line;                                         // Stores one line read from the original file
    string targetLine = "Priority: Normal";             // Identifies the line that must be replaced
    string replacementLine = "Priority: Requires supervisor review"; // Stores the longer replacement line

    if (!inputFile || !temporaryFile) {                  // Tests whether both files opened successfully
        cout << "Error: Could not open the required files." << endl; // Reports an opening failure
        return 1;                                       // Ends the program with an error status
    }                                                    // Ends the file-opening validation

    while (getline(inputFile, line)) {                   // Repeats while one original line is read successfully
        if (line == targetLine) {                        // Tests whether the current line needs replacement
            temporaryFile << replacementLine << endl;    // Writes the replacement instead of the original line
        } else {                                         // Handles every line that does not need replacement
            temporaryFile << line << endl;               // Copies the original line unchanged
        }                                                // Ends the line-selection structure
    }                                                    // Ends the original-file traversal

    inputFile.close();                                   // Closes the original input stream
    temporaryFile.close();                               // Closes the updated output stream
    cout << "Updated service notes created." << endl;   // Confirms the completed rewrite

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function
```

Después del trace, ejecuta el program y compara `service_notes_updated.txt` con la predicción. Debe conservar la primera y tercera lines, pero contener la replacement line en el medio.

Discute y responde estas preguntas antes de modificar el program:

1. ¿Cuántas veces se ejecuta el `while` con el file inicial y qué escribe `temporaryFile` en cada iteration?
2. Si `targetLine` no aparece en el original, ¿qué contenido tendrá `service_notes_updated.txt`?
3. ¿Por qué `temporaryFile << line << endl;` sigue siendo necesario en el `else`?
4. ¿Por qué este program no usa `seekp`, aunque la line que cambia es conocida?
5. Después de terminar, ¿cuál file contiene el original y cuál contiene la versión actualizada?

<details>
<summary>Ver respuestas</summary>

1. Se ejecuta tres veces: copia `Device: Panel-7`, reemplaza `Priority: Normal` y copia `Technician: Alex`.
2. El updated file será una copia del original, porque ninguna line activa el primer branch.
3. Sin ese `else`, las lines que no coinciden con el target desaparecerían del updated file.
4. La replacement tiene una longitud distinta y podría sobrescribir data posterior si se escribiera directamente sobre el original.
5. `service_notes.txt` conserva el original; `service_notes_updated.txt` contiene la versión actualizada.

</details>

**Resultado esperado:** el estudiante puede hacer trace de un workflow de reescritura y justificar por qué es preferible a una edición in-place cuando la longitud de la line cambia.

---

## Resumen de la sesión

- La creación, lectura secuencial y validación de streams son patterns ya practicados; se usan como base, no se repiten como ejercicios completos.
- `ios::app` conserva el contenido existente y añade output al final del file.
- `tellg` y `tellp` observan positions; `seekg` y `seekp` las mueven antes de la próxima operación.
- `fstream` con `ios::in | ios::out` permite leer y escribir el mismo file, pero exige controlar el cambio de operación y de position.
- Una actualización in-place de text es segura solo cuando se conserva el ancho del record.
- Para text de longitud variable, la solución segura es reescribir el file mediante un temporary file.

## Próxima sesión

El Lab 10 se mantiene como buffer para consolidar File I/O si hace falta. Si el grupo domina estos patterns, el próximo contenido nuevo será Arrays and Matrices.
