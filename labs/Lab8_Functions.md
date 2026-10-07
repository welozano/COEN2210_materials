# Lab 8 — Functions: Value and Reference Parameters
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Semana 8 — Functions; Gaddis, Capítulo 6 (secciones 6.1–6.6 y 6.13)

**Duración:** 110 min
**Requisitos:** Labs 1–3 y 5–7; `if`/`else`, `switch`, loops, prototypes, `void functions`, parameters, pass-by-value y pass-by-reference

---

## Objetivos

Al finalizar este laboratorio, el estudiante podrá:

1. Organizar un programa con prototypes, `main` y function definitions.
2. Usar pass-by-value cuando una function solo necesita observar un dato.
3. Usar pass-by-reference cuando una function debe actualizar el estado de `main`.
4. Integrar functions con selection structures y loops ya conocidos.
5. Diseñar test cases que distingan una copia de una variable original modificable.

---

## Parte 0 — Preparar la carpeta y el repositorio (5 min)

Este lab reúne programas que separan tareas en functions. Crea una carpeta nueva llamada `lab8-functions`, ábrela como carpeta raíz en VS Code e inicializa un repositorio desde Source Control.

**¿Qué hace esto?** Mantiene el historial de Lab 8 separado de los labs anteriores.

**Qué deberías ver:** `LAB8-FUNCTIONS` aparece como carpeta raíz y Source Control muestra un repositorio vacío.

---

## Parte 1 — Crear archivos y `.gitignore` (5 min)

Crea estos archivos:

1. `value_reference_demo.cpp`
2. `fuse_inventory.cpp`
3. `workshop_registration.cpp`

Cada archivo debe comenzar con el header estándar, usando `Lab: 8 - Functions` y una `Description` distinta en inglés.

```cpp
/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Your Full Name]
 * Lab: 8 - Functions
 * Description: [What this specific program does]
 * Due Date: [Date]
 */
```

En `.gitignore`, agrega los seis ejecutables de esos tres archivos para Mac y Windows:

```gitignore
# Compiled programs
value_reference_demo
value_reference_demo.exe
fuse_inventory
fuse_inventory.exe
workshop_registration
workshop_registration.exe
```

**Qué deberías ver:** al compilar, Source Control muestra los `.cpp` y `.gitignore`, pero no los ejecutables.

---

## Parte 2 — `value_reference_demo.cpp`: guía resuelta (15 min)

Un laboratorio lleva un conteo de inspecciones de seguridad ya completadas durante el turno. Antes de registrar una inspección nueva, el asistente quiere ver cuál sería el conteo si la completa; esa proyección no debe cambiar el registro oficial. Después de confirmarla, el sistema sí debe aumentar el conteo oficial. El programa recibe el número de inspecciones ya registradas y demuestra ambas operaciones.

Antes de correrlo, predice los tres valores que se mostrarán para una entrada de `4`: el conteo proyectado, el conteo después de la proyección y el conteo después de registrar la inspección.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

void showProjectedCount(int completedInspections);       // Declares a value-parameter function
void recordCompletedInspection(int &completedInspections); // Declares a reference-parameter function

int main() {                                             // Starts the program
    int completedInspections;                            // Stores the official completed-inspection count

    cout << "Enter completed inspections: ";           // Prompts for the official count
    cin >> completedInspections;                         // Reads the value stored by main

    showProjectedCount(completedInspections);            // Sends a copied count to the first function
    cout << "After projection: " << completedInspections << endl; // Shows that main kept its count
    recordCompletedInspection(completedInspections);     // Sends the original count by reference
    cout << "After recording: " << completedInspections << endl; // Shows that main now stores the update

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

void showProjectedCount(int completedInspections) {      // Defines a function that changes only its local copy
    completedInspections++;                              // Adds one only to the copied parameter
    cout << "Projected count: " << completedInspections << endl; // Displays the possible next count
}                                                        // Ends the value-parameter function

void recordCompletedInspection(int &completedInspections) { // Defines a function that accesses the original variable
    completedInspections++;                              // Changes the official count through the reference
    cout << "Inspection recorded." << endl;             // Confirms the permanent update
}                                                        // Ends the reference-parameter function
```

**Esto es lo que debes entregar (obligatorio):** el archivo completo, ejecutado con `4`, y un comentario de bloque en inglés que explique por qué el conteo mostrado después de la function call `showProjectedCount(completedInspections)` es distinto del conteo mostrado después de la function call `recordCompletedInspection(completedInspections)`.

---

## Parte 3 — `fuse_inventory.cpp`: functions con responsabilidades distintas (30 min)

El gabinete de mantenimiento comienza con cierta cantidad de fusibles de repuesto. Una persona técnica indica si utilizó un fusible durante una reparación. El programa siempre muestra el encabezado del gabinete; una function informa la decisión recibida y otra, solo cuando la respuesta es `Y` o `y`, reduce el inventario oficial en una unidad. Al terminar, debe mostrar la cantidad que queda en el gabinete.

Antes de programar, responde:

| Pregunta | Decisión |
|---|---|
| ¿Qué function no necesita datos? | La que muestra el encabezado. |
| ¿Qué function solo observa una respuesta? | La que recibe el carácter de decisión por value. |
| ¿Qué function debe cambiar el inventario de `main`? | La que recibe `int &fuseCount`. |

### Instrucciones

1. Crea tres `void functions` con nombres descriptivos en inglés: una para el encabezado, una para informar la decisión recibida y una para actualizar el inventario cuando corresponda.
2. Declara sus prototypes antes de `main`, completa `main` para leer la cantidad inicial y la decisión de la persona técnica, y muestra el inventario final.
3. Usa una `if`/`else` para decidir si el inventario puede cambiar. El programa debe reconocer tanto letras mayúsculas como minúsculas y debe impedir un inventario negativo.
4. Define las tres functions después de `main`. Elige cuidadosamente cuál dato solo necesita una copia y cuál debe conservar un cambio cuando la function termine.

Escribe este starter code debajo del header. Los `TODO` están separados para que agregues cada parte en el lugar correspondiente.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

// TODO: Declare prototypes for the three functions described below.

int main() {                                             // Starts the program
    int fuseCount;                                       // Stores the official number of spare fuses
    char usedFuse;                                       // Stores the technician decision

    // TODO: Call the heading function, read fuseCount, and read Y or N.
    // TODO: Use if/else to decide whether to call the inventory-update function.
    // TODO: Display the final number of spare fuses.

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

// TODO: Define a void function that displays the cabinet heading.
// TODO: Define a void function that reports whether the response uses a fuse.
// TODO: Define a void function that receives fuseCount by reference and subtracts one.
```

Use a value parameter for the response-reporting function and a reference parameter only for the inventory-changing function. Before subtracting, make sure that `fuseCount` is greater than zero. Test `4` with `Y`, `y` and `N`; also test `0` with `Y`.

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila cada archivo después de completar una function, no solo al final.

**Windows:**

```powershell
g++ fuse_inventory.cpp -o fuse_inventory
.\fuse_inventory.exe
```

**Mac:**

```bash
clang++ fuse_inventory.cpp -o fuse_inventory
./fuse_inventory
```

**¿Qué hace esto?** El primer comando compila el programa; el segundo lo ejecuta. Sustituye `fuse_inventory` por el nombre de los otros archivos cuando los pruebes.

**Qué deberías ver:** `Y` o `y` reduce el inventario cuando hay fusibles; `N` lo conserva; y nunca se muestra un inventario negativo.

**Esto es lo que debes entregar (obligatorio):** prototypes, three definitions, a functional `if`/`else`, the four test cases and an English `Analysis` block explaining why only one function needs `&`.

---

## Parte 4 — `workshop_registration.cpp`: integrar functions, `switch` y loops (40 min)

El capítulo estudiantil de robótica organiza un workshop con un número máximo de asientos. La sesión inicia con `maxSeats` y `availableSeats` iguales. La persona encargada puede registrar una asistencia, cancelar un registro o terminar la sesión. Un registro no puede bajar los asientos disponibles de cero; una cancelación no puede superar `maxSeats`. El menú debe repetirse hasta que se seleccione terminar.

Antes de escribir código, identifica las responsabilidades que el programa debe separar:

| Responsabilidad | Pregunta de diseño |
|---|---|
| Mostrar las opciones | ¿Necesita recibir datos o solamente producir output? |
| Registrar una asistencia | ¿Qué variable debe conservar un cambio después de la function call? |
| Cancelar un registro | ¿Qué valor puede cambiar y cuál solamente establece el límite? |

### Instrucciones

1. Diseña tres `void functions` con nombres descriptivos en inglés: una para mostrar el menú y dos para realizar las acciones que cambian la disponibilidad.
2. Declara los prototypes antes de `main`. En `main`, solicita una capacidad máxima válida, inicializa los asientos disponibles y conserva allí el valor de la opción del menú.
3. Repite el menú hasta que la persona seleccione terminar. Usa `switch` para dirigir cada opción a la acción correspondiente; las functions deben validar que no se excedan los dos límites de capacidad.
4. Define las functions después de `main`. Decide qué variables deben recibirse por value y cuáles por reference según si la acción debe dejar un cambio permanente.

Escribe este starter code debajo del header. Los `TODO` indican el lugar donde debes completar cada componente, no una solución predeterminada.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

// TODO: Declare the three required function prototypes.

int main() {                                             // Starts the program
    int maxSeats;                                        // Stores the fixed workshop capacity
    int availableSeats;                                  // Stores the changing number of available seats
    int menuChoice;                                      // Stores one selected menu option

    // TODO: Read a valid capacity and initialize the available seats.
    // TODO: Repeat the menu and read one option on each pass.
    // TODO: Use switch to perform the selected action or end the session.

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

// TODO: Define the menu-display function.
// TODO: Define the function that registers an attendee and respects capacity.
// TODO: Define the function that cancels a registration and respects capacity.
```

Registra los resultados de estos test cases: con capacidad `1`, registra dos veces, cancela dos veces y termina; con capacidad `2`, registra una vez, cancela una vez y termina; también entra una opción de menú inválida antes de terminar. Para cada caso, escribe la disponibilidad final que esperabas y la que observaste.

**Esto es lo que debes entregar (obligatorio):** un menú repetido, `switch`, tres functions, correct use of reference parameters, validation of both capacity limits, test cases and an English analysis explaining why `maxSeats` does not need `&`.

---

## Parte 5 — Cierre, test cases y commit/push (15 min)

Antes de entregar verifica:

- Cada function tiene un prototype antes de `main` y una definition que coincide con él.
- Los parameters por value no cambian variables de `main`.
- Los parameters por reference usan `&` en prototype y header, no en la call.
- Los prompts, identifiers y comments de C++ están en inglés.
- Los tres archivos tienen headers distintos y `.gitignore` excluye ejecutables.
- Los test cases de las Partes 3 y 4 incluyen el resultado esperado y el resultado observado.

Completa un bloque `Analysis` en inglés en cada archivo: explica una decisión de pass-by-value o pass-by-reference que tomaste en ese programa. Luego haz stage de los tres `.cpp` y `.gitignore`, crea un commit como `Lab 8: functions and reference parameters` y publica/sincroniza el repositorio.

**Qué deberías ver:** Source Control sin cambios pendientes y el repositorio remoto con los tres programas.

## Próxima sesión

Semana 9 continuará con functions que retornan valores y scope.
