# Lab 6 — Loops I: `while`, `do while` y Selection Structures
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano  
**Basado en:** Semana 6 — Repetition Structures; Gaddis, Capítulo 5 (secciones 5.2, 5.3 y 5.5)  
**Duración:** 110 min  
**Requisitos:** Labs 1–3 y Lab 5 completados; `cin`, `cout`, operadores relacionales y lógicos, `if`/`else`, `switch`, `fixed` y `setprecision`

---

## Objetivos

Al finalizar este laboratorio, el estudiante podrá:

1. Usar un `while` loop para repetir una lectura hasta obtener un valor numérico dentro de un rango válido.
2. Explicar por qué un `while` puede ejecutar cero iterations y por qué su condition debe poder llegar a `false`.
3. Usar un `do while` loop para mostrar un menú al menos una vez y repetirlo según la decisión de la persona usuaria.
4. Integrar `while`, `do while`, `if`/`else`, `switch`, operadores lógicos, cálculo aritmético y salida formateada en un programa.
5. Diseñar `test cases` que comprueben límites, opciones inválidas y más de una iteration.

---

## Parte 0 — Preparar la carpeta y el repositorio (5 min)

Desde Lab 5 ya debes reconocer el flujo de crear una carpeta de lab, abrirla en VS Code e inicializar un repositorio. Esta vez lo harás con menos instrucciones paso a paso.

> 🖱️ **Vas a usar VS Code.**

1. Dentro de tu carpeta padre de COEN 2210, crea una carpeta nueva llamada `lab6-loops`.
2. Ábrela como la carpeta raíz en VS Code con `File → Open Folder...`.
3. Abre Source Control con `Ctrl+Shift+G` (Windows) o `Cmd+Shift+G` (Mac) y selecciona **Initialize Repository**.

**¿Qué hace esto?** Crea un repositorio Git independiente para este lab; su historial no se mezcla con el de los labs anteriores.

**Qué deberías ver:** el Explorer muestra `LAB6-LOOPS` como carpeta raíz y Source Control muestra un repositorio vacío.

> ⚠️ No inicialices Git en la carpeta padre que contiene todos tus labs. Eso mezclaría los archivos e historiales del curso en un solo repositorio.

---

## Parte 1 — Crear los archivos y actualizar el header (5 min)

> 🖱️ **Vas a usar VS Code.**

Crea estos tres archivos dentro de `lab6-loops`:

1. `temperature_validation.cpp`
2. `maintenance_session.cpp`
3. `slot_manager.cpp`

Copia este header al inicio de **cada** archivo y completa los campos entre corchetes. `Description` debe describir el propósito de ese archivo particular.

```cpp
/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Your Full Name]
 * Lab: 6 - Loops I
 * Description: [What this specific program does]
 * Due Date: [Date]
 */
```

**¿Qué hace esto?** El header identifica el propósito, autoría y fecha de cada archivo, como una forma básica de documentación profesional.

**Qué deberías ver:** ambos archivos aparecen en el Explorer y cada uno comienza con un header completo en inglés.

Ahora crea un archivo llamado `.gitignore` en `lab6-loops` y agrega estas líneas:

```gitignore
# Compiled programs
temperature_validation
temperature_validation.exe
maintenance_session
maintenance_session.exe
slot_manager
slot_manager.exe
```

**¿Qué hace esto?** Evita que Git incluya programas compilados: en Mac no tienen extensión y en Windows terminan en `.exe`.

**Qué deberías ver:** después de compilar, Source Control debe mostrar los archivos `.cpp` y `.gitignore`, pero no los ejecutables.

---

## Parte 2 — `slot_manager.cpp`: guía resuelta de integración (15 min)

Este es un programa corto, completamente resuelto, que sirve como ejemplo integrado antes de los ejercicios de práctica. Retoma el problema de **turnos disponibles** trabajado en clase: una recepción comienza con cierta cantidad de turnos; puede reservar uno, cancelar una reserva o cerrar el programa. Aquí verás el programa completo antes de construir los tuyos.

El programa debe cumplir estas reglas:

- Una reserva reduce los turnos disponibles en uno, pero solo si queda al menos un turno.
- Una cancelación aumenta los turnos disponibles en uno, pero solo si existe una reserva que cancelar.
- El menú debe mostrarse al menos una vez y terminar solo cuando se seleccione la opción 3.

### Paso 1 — Guardar el estado inicial

**Objetivo:** antes de mostrar un menú, el programa necesita saber cuántos turnos existen. `maxSlots` conserva la capacidad inicial y no cambia; `remainingSlots` representa los turnos disponibles y sí cambia durante el programa. `menuChoice` guardará la opción para que el `switch` y el loop puedan consultarla.

En `slot_manager.cpp`, debajo del header, escribe este primer bloque:

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    int maxSlots;                                        // Stores the fixed capacity of the appointment schedule
    int remainingSlots;                                  // Stores the current number of available appointment slots
    int menuChoice;                                      // Stores one menu selection

    cout << "Enter maximum appointment slots: ";        // Prompts for the fixed schedule capacity
    cin >> maxSlots;                                     // Reads the initial capacity
    remainingSlots = maxSlots;                           // Starts with every appointment slot available

    // TODO: Replace this line with the complete menu loop from Step 2. // Reserves the repeated menu

    return 0;                                            // Ends the program successfully
}                                                         // Ends the main function
```

Este primer bloque ya es un programa C++ completo: aunque todavía no muestra un menú, puedes compilarlo y confirmar que guarda la entrada sin errores de sintaxis. Con una entrada de `3`, `maxSlots` y `remainingSlots` valen 3. Todavía no existe ninguna reserva: el próximo paso reemplaza el `TODO` por un menú que permita elegir una acción.

### Paso 2 — Mostrar el menú y seleccionar una acción

**Objetivo:** el menú debe aparecer aunque la persona vaya a cerrarlo inmediatamente. Por eso agregamos un `do` block: primero muestra las opciones y lee una elección; la condition al final mantiene el menú activo hasta que se seleccione 3.

Reemplaza **solo** el comentario `TODO` del Paso 1 por este bloque. No borres el `return 0;` ni la llave final que ya escribiste. Este nuevo bloque también queda completo: muestra el menú y se repite hasta que se seleccione 3; por ahora, las acciones dentro del `switch` aún están pendientes.

```cpp
    do {                                                 // Starts a menu that must appear at least once
        cout << "\nSlot manager\n";                     // Displays the menu title
        cout << "1. Reserve a slot\n";                  // Displays the reservation option
        cout << "2. Cancel a reservation\n";            // Displays the cancellation option
        cout << "3. End session\n";                     // Displays the exit option
        cout << "Enter menu choice: ";                  // Prompts for one menu selection
        cin >> menuChoice;                               // Reads the selected action

        switch (menuChoice) {                            // Chooses the code for the selected action
            // TODO: Replace this line with the cases from Step 3. // Reserves the selection logic for the next step
        }                                                // Ends the switch statement
    } while (menuChoice != 3);                           // Repeats until the user selects the exit option
```

El `switch` organiza las tres opciones del menú y el `do while` ya reconoce que debe detenerse al entrar `3`. Falta definir qué hace cada opción; eso se agregará sin reemplazar el loop completo.

### Paso 3 — Proteger la reserva y terminar la sesión

**Objetivo:** una reserva no puede reducir el contador por debajo de cero, y una cancelación no puede aumentar el contador por encima de `maxSlots`. Dentro de `case 1`, `if` comprueba si quedan turnos; dentro de `case 2`, otro `if` comprueba si existe una reserva que cancelar. Los `else` muestran el resultado cuando la acción no es posible. La condition `while (menuChoice != 3)` que agregaste en el Paso 2 repite todo mientras no se elija salir.

Reemplaza **solo** el comentario `TODO` dentro de `switch` por los siguientes `case`. Conserva el `do while`, `return 0;` y las llaves que ya existen en tu archivo.

```cpp
case 1:                                                  // Handles a reservation request
    if (remainingSlots > 0) {                            // Checks whether a slot can be reserved
        remainingSlots--;                                // Removes one available slot
        cout << "Reservation accepted." << endl;        // Confirms the successful reservation
    } else {                                             // Handles a reservation when no slots remain
        cout << "No slots available." << endl;          // Explains why the reservation was not made
    }                                                     // Ends the selection that protects the counter
    break;                                               // Leaves the switch after option 1
case 2:                                                  // Handles a cancellation request
    if (remainingSlots < maxSlots) {                     // Checks whether a reservation exists to cancel
        remainingSlots++;                                // Returns one slot to the available inventory
        cout << "Reservation cancelled." << endl;       // Confirms the cancellation
    } else {                                             // Handles a cancellation when every slot is already available
        cout << "No reservation to cancel." << endl;    // Explains why the cancellation was not made
    }                                                     // Ends the selection that protects the maximum capacity
    break;                                               // Leaves the switch after option 2
case 3:                                                  // Handles the exit option
    cout << "Closing slot manager." << endl;            // Confirms the exit request
    break;                                               // Leaves the switch after option 3
default:                                                 // Handles a menu number outside the available options
    cout << "Invalid menu choice." << endl;             // Reports an invalid selection
```

Prueba esta secuencia: inicia con `1` turno, escribe `1`, luego `1`, `2`, `2` y finalmente `3`. La primera reserva debe aceptarse; la segunda debe llegar a `else`, porque el contador ya vale 0. La primera cancelación debe devolver el único turno; la segunda debe llegar a `else`, porque `remainingSlots` ya volvió a ser igual a `maxSlots`. El programa sigue mostrando el menú hasta recibir `3`.

**Esto es lo que debes entregar (obligatorio):** `slot_manager.cpp` con el header completo y el programa resuelto ejecutado con la secuencia indicada.

**Para practicar por tu cuenta (opcional, no se entrega):** agrega una opción 4 que muestre solamente el número actual de turnos, sin modificarlo. Actualiza también la condition del loop si decides convertir la opción 3 en otra acción.

---

## Parte 3 — `temperature_validation.cpp`: repetir hasta obtener una temperatura válida (25 min)

Antes de encender una cámara de pruebas, un técnico debe registrar la temperatura de operación. El procedimiento del laboratorio acepta únicamente valores entre **18 °C y 30 °C, inclusive**: una temperatura demasiado baja puede producir mediciones no representativas y una demasiado alta puede afectar el equipo. El programa no controla la cámara; solo verifica que el dato registrado cumple el procedimiento antes de confirmar el inicio de la prueba. Si alguien escribe un valor fuera del rango, debe explicar el problema y pedir otro valor, no terminar la solicitud.

Antes de escribir C++, diseña la condition:

| Pregunta de diseño | Respuesta que debes obtener |
|---|---|
| ¿Cuándo una temperatura es inválida? | Cuando es menor que 18 **o** mayor que 30. |
| ¿Qué operador lógico une esas dos comparaciones? | `\|\|` |
| ¿Qué debe ocurrir dentro del loop? | Mostrar un error, pedir un reemplazo y guardar el nuevo valor. |
| ¿Cuándo termina el loop? | Cuando ambas partes de la condición inválida son `false`. |

En `temperature_validation.cpp`, debajo del header, escribe el siguiente starter code. El primer `cin` ocurre antes del loop porque `while` necesita un valor inicial para poder evaluar su condition.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    double testTemperature;                              // Stores one requested operating temperature

    cout << "Enter operating temperature from 18 to 30 C: "; // Prompts for the first candidate temperature
    cin >> testTemperature;                              // Reads the first candidate temperature

    // TODO: Write a while loop for a temperature below 18 or above 30. // Repeats while the temperature is invalid
    // TODO: Inside the loop, display an English error message.    // Explains that another value is required
    // TODO: Inside the loop, read testTemperature again.           // Replaces the invalid value before retesting

    cout << "Temperature accepted: " << testTemperature << " C" << endl; // Displays the value only after validation

    return 0;                                            // Ends the program successfully
}                                                         // Ends the main function
```

No uses `if`/`else` para la validación principal: ese patrón solo decidiría una vez. El `while` debe contener el mensaje y el segundo `cin`, porque ambos deben repetirse cada vez que la temperatura siga inválida.

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila y ejecuta el programa desde la carpeta `lab6-loops`.

**Windows:**

```powershell
g++ temperature_validation.cpp -o temperature_validation
.\temperature_validation.exe
```

**Mac:**

```bash
clang++ temperature_validation.cpp -o temperature_validation
./temperature_validation
```

**¿Qué hace esto?** El primer comando compila el archivo y crea un ejecutable. El segundo ejecuta ese programa.

**Qué deberías ver:** una temperatura válida se acepta inmediatamente; una temperatura fuera del rango muestra un mensaje y pide otra entrada.

Prueba estos `test cases`:

| Primera entrada | Segunda entrada | Resultado esperado |
|---:|---:|---|
| `18` | — | Acepta `18` sin repetir. |
| `30` | — | Acepta `30` sin repetir. |
| `17` | `22` | Muestra un error y luego acepta `22`. |
| `31` | `29` | Muestra un error y luego acepta `29`. |

El `18` y el `30` son **boundary values**: confirman que los extremos inclusivos son válidos. Por ahora prueba solo entradas numéricas; texto como `warm` produce un tipo de error de `cin` que requiere una técnica distinta.

### Análisis requerido

Al final de `temperature_validation.cpp`, después de `main`, agrega este comentario de bloque en inglés y reemplaza cada respuesta entre corchetes después de ejecutar los test cases:

```cpp
/*
 * Analysis:
 * 1. [Explain why 17 causes another prompt.]
 * 2. [Explain why 18 does not enter the while loop.]
 * 3. [Explain what must change so the while condition eventually becomes false.]
 */
```

**Esto es lo que debes entregar (obligatorio):** `temperature_validation.cpp` con su header completo, un `while` funcional, los cuatro test cases ejecutados y el bloque `Analysis` respondido en inglés.

**Para practicar por tu cuenta (opcional, no se entrega):** cambia el rango para permitir de 20 a 28 °C. Antes de correrlo, predice qué ocurrirá con las entradas `19`, `20`, `28` y `29`; después restaura el rango original.

---

## Parte 4 — `maintenance_session.cpp`: un menú que se repite con `do while` (40 min)

El área de mantenimiento prepara solicitudes de suministros para reparar equipos. En una sola sesión, el técnico puede procesar una o varias solicitudes: para cada una escoge un tipo de suministro, indica cuántas unidades necesita y obtiene el costo de esa solicitud. El programa no guarda inventario ni suma el total de toda la sesión; su propósito es practicar el flujo completo de **una solicitud** y luego decidir si se procesa otra.

Para iniciar cada solicitud, el programa muestra un **menú de suministros** como este:

```text
Maintenance supply menu
1. Cable set
2. Battery pack
3. Connector kit
Enter supply choice:
```

El técnico escoge una opción; si es válida, indica una cantidad de 1 a 5 y el programa muestra el costo. Si la opción no existe, el programa muestra un error y no pide cantidad. Después de cualquiera de esos dos resultados, el programa pregunta `Process another request? (Y/N):`.

Ese menú debe aparecer una primera vez antes de que el técnico pueda responder si habrá otra solicitud; luego debe volver a mostrarse solo si responde `Y` o `y`. Por eso este problema necesita un `do while`: el body contiene el menú y todo el procesamiento de una solicitud, y la condition al final decide si comienza una nueva iteration.

Cada solicitud tiene dos decisiones:

1. Seleccionar un suministro con `switch`.
2. Escribir una cantidad válida de 1 a 5 unidades con el patrón `while` de la Parte 3.

Una cantidad menor que 1 no representa una solicitud real y una cantidad mayor que 5 excede el límite de una solicitud individual; ambas requieren una nueva entrada. El programa calcula el costo de cada solicitud con la fórmula:

\[
\text{request cost} = \text{unit price} \times \text{quantity}
\]

| Opción | Suministro | Precio por unidad |
|---:|---|---:|
| `1` | Cable set | `$3.25` |
| `2` | Battery pack | `$7.50` |
| `3` | Connector kit | `$4.00` |

En `maintenance_session.cpp`, coloca el siguiente starter code debajo del header. Primero completa los tres `TODO` de variables: cada comentario indica el tipo de dato y el propósito de la variable. El primer `case` es el modelo completo. Usa el mismo patrón para completar las opciones 2 y 3, sin copiar un costo final fijo: el programa debe calcularlo con `unitPrice * quantity`.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
#include <iomanip>                                       // Provides fixed and setprecision
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    int supplyChoice;                                    // Stores one menu selection
    // TODO: Declare quantity as an int.                 // Stores the quantity for one supply request
    double unitPrice;                                    // Stores the price selected by the switch
    // TODO: Declare requestCost as a double.            // Stores the calculated cost for one request
    bool isValidSupplyChoice;                            // Tracks whether the switch selected a real supply
    // TODO: Declare processAnother as a char.           // Stores whether another request should be processed

    cout << fixed << setprecision(2);                    // Formats every displayed cost with two decimal places

    do {                                                 // Starts a session that must process at least one menu
        isValidSupplyChoice = true;                      // Resets the flag for this new menu iteration
        cout << "Maintenance supply menu\n";             // Introduces the available supply choices
        cout << "1. Cable set\n";                        // Displays the first menu option
        // TODO: Display menu option 2.                  // Adds the battery-pack option from the table
        // TODO: Display menu option 3.                  // Adds the connector-kit option from the table
        cout << "Enter supply choice: ";                // Prompts for one menu selection
        cin >> supplyChoice;                             // Reads the selected option

        switch (supplyChoice) {                          // Compares the option against each available case
            case 1:                                      // Handles the cable-set option as the model
                unitPrice = 3.25;                        // Assigns the price for the selected supply
                cout << "Supply selected: Cable set" << endl; // Confirms the selected supply
                break;                                   // Leaves the switch after handling option 1
            // TODO: Add case 2 for the battery pack.    // Assign its price, display its name, and use break
            // TODO: Add case 3 for the connector kit.   // Assign its price, display its name, and use break
            // TODO: Add default for an invalid option.  // Set the flag to false and display an English error message
        }                                                // Ends the switch statement

        if (isValidSupplyChoice) {                       // Continues only when the switch selected a real supply
            cout << "Enter quantity from 1 to 5: ";     // Prompts for the first quantity candidate
            cin >> quantity;                             // Reads the first quantity candidate
            while (quantity < 1 || quantity > 5) {       // Repeats while the quantity is outside the valid range
                cout << "Invalid quantity. Try again: "; // Explains why another quantity is needed
                cin >> quantity;                         // Reads a replacement quantity for the next test
            }                                           // Ends after a valid quantity is entered
            requestCost = unitPrice * quantity;          // Calculates the cost using the selected price and quantity
            cout << "Request cost: $" << requestCost << endl; // Displays the formatted cost for this request
        }                                               // Skips the quantity and cost for an invalid supply option

        cout << "Process another request? (Y/N): ";     // Prompts for the decision to repeat the menu
        cin >> processAnother;                           // Reads the repetition decision
    } while (processAnother == 'Y' || processAnother == 'y'); // Repeats only when the user chooses Y or y

    cout << "Maintenance session ended." << endl;       // Confirms that the posttest loop has ended

    return 0;                                            // Ends the program successfully
}                                                         // Ends the main function
```

### Pasos para completar el programa

1. Completa las líneas del menú para las opciones 2 y 3 usando la tabla.
2. Completa `case 2` y `case 3`. Cada caso debe asignar su precio, confirmar el suministro y terminar con `break`.
3. Completa `default`. Debe mostrar `Invalid supply choice.` en inglés y asignar `false` a `isValidSupplyChoice`.
4. Conserva el prompt `Process another request? (Y/N):` después del `switch`. Incluso si la opción fue inválida, el técnico puede decidir si intenta mostrar el menú otra vez.
5. Observa el `if (isValidSupplyChoice)` después del `switch`: contiene la validación con `while` y el cálculo que aplican a cualquier suministro válido. No lo coloques dentro de cada `case` ni declares variables nuevas dentro de un `case`.

> ⚠️ `isValidSupplyChoice` se reinicia a `true` al principio de cada iteration. Si queda en `false` tras una opción inválida y no se reinicia, una opción válida posterior conservaría un estado incorrecto. El `if` después del `switch` usa ese flag para impedir que una opción inválida llegue a pedir una cantidad o calcular un costo.

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila después de completar un `case`, no solo al final.

**Windows:**

```powershell
g++ maintenance_session.cpp -o maintenance_session
.\maintenance_session.exe
```

**Mac:**

```bash
clang++ maintenance_session.cpp -o maintenance_session
./maintenance_session
```

**¿Qué hace esto?** Compilar en incrementos pequeños ayuda a localizar el cambio que causó un error de sintaxis o de lógica.

**Qué deberías ver:** el menú aparece una vez antes de cualquier pregunta sobre repetir. Cada opción válida muestra el suministro y un costo con dos decimales; una opción inválida no solicita una cantidad y muestra el error.

**Esto es lo que debes entregar (obligatorio):** `maintenance_session.cpp` con header completo, menú de tres opciones, `switch` con tres `case` válidos y `default`, validación de cantidad dentro de cada opción válida, cálculo de `requestCost`, salida con dos decimales y un `do while` que repite el menú para `Y` o `y`.

**Para practicar por tu cuenta (opcional, no se entrega):** cambia temporalmente la condition final para aceptar solo `Y` mayúscula. Prueba `y` y explica, en un comentario inglés, por qué el menú ya no se repite. Después restaura la condition original.

---

## Parte 5 — Test cases, trace y prevención de infinite loops (10 min)

Un `test case` es una combinación planificada de entradas y resultado esperado. Para un loop no basta con probar una sola vuelta: debes comprobar que entra, se repite y termina cuando corresponde.

Antes de ejecutar cada caso, predice el resultado. Luego ejecútalo y compara tu predicción con el comportamiento real.

| Caso | Entradas, en orden | Resultado esperado |
|---|---|---|
| 1 | `1`, `1`, `N` | Selecciona Cable set, acepta 1 unidad, muestra `$3.25` y termina la sesión. |
| 2 | `2`, `0`, `3`, `N` | Selecciona Battery pack, rechaza 0, acepta 3 y muestra `$22.50`. |
| 3 | `9`, `Y`, `3`, `4`, `N` | Muestra opción inválida, vuelve a mostrar el menú, procesa Connector kit por 4 unidades y muestra `$16.00`. |
| 4 | `1`, `5`, `y`, `2`, `1`, `N` | Procesa dos solicitudes; confirma que `y` minúscula repite el menú. |

Después de ejecutar los cuatro casos, agrega este comentario de bloque al final de `maintenance_session.cpp`, después de `main`, y responde en inglés:

```cpp
/*
 * Test analysis:
 * 1. [Explain why the menu appears before processAnother has a value.]
 * 2. [Explain what changes when the user enters Y after a request.]
 * 3. [Explain why an invalid supply choice does not ask for quantity.]
 * 4. [Explain how the do while loop reaches its false condition.]
 */
```

Un **infinite loop** ocurre si un loop no tiene una forma realista de hacer su condition `false`. En este programa, verifica estas dos condiciones de terminación antes de entregar:

- Dentro de cada `while`, `cin >> quantity` debe leer un valor nuevo; de lo contrario, un número inválido no cambiaría.
- En el `do while`, la persona debe poder entrar `N` o cualquier carácter distinto de `Y`/`y`; ese resultado hace que la condition sea `false` y termina la sesión.

**Esto es lo que debes entregar (obligatorio):** los cuatro test cases ejecutados, el bloque `Test analysis` completado en inglés y programas que terminan normalmente después de `N`.

**Para practicar por tu cuenta (opcional, no se entrega):** elimina temporalmente el `cin >> quantity` dentro de uno de los `while`, predice qué ocurre con una entrada de `0` y no ejecutes el programa hasta consultar al profesor. Después restaura la lectura.

---

## Cierre — Revisar el trabajo y hacer commit/push (10 min)

Antes de entregar, revisa esta lista:

- Los tres archivos tienen un header completo y una `Description` distinta.
- Todos los prompts, mensajes y comentarios dentro de C++ están en inglés.
- `temperature_validation.cpp` repite la entrada solo mientras la temperatura esté fuera del rango 18–30.
- `maintenance_session.cpp` muestra el menú al menos una vez y termina después de `N`.
- `slot_manager.cpp` no permite que una reserva reduzca los turnos por debajo de cero ni que una cancelación supere `maxSlots`.
- Cada `case` válido termina con `break`.
- Cada costo se calcula con `unitPrice * quantity` y se muestra con dos decimales.
- `.gitignore` evita que los ejecutables aparezcan en Source Control.

> 🖱️ **Vas a usar el panel de Source Control de VS Code.**

1. Guarda los tres archivos `.cpp` y `.gitignore`.
2. En Source Control, verifica que aparecen esos cuatro archivos y no los ejecutables.
3. Haz stage de todos los cambios con el botón `+` junto a **Changes**.
4. Escribe un mensaje como `Lab 6: while and do while loops` y haz clic en **Commit**.
5. Selecciona **Publish Branch** si este es el primer push del repositorio, o **Sync Changes** si ya lo publicaste.

**¿Qué hace esto?** Stage prepara los archivos para el commit; el commit guarda una versión en el historial local; Publish Branch o Sync Changes sube ese historial a GitHub.

**Qué deberías ver:** Source Control deja de mostrar cambios pendientes y el repositorio remoto contiene los tres archivos `.cpp` y `.gitignore`.

---

## Próxima sesión

**Semana 7 — Review + Midterm 1.** El Lab 7 reforzará el `for` loop, counters y acumuladores con los operadores y selection structures ya vistos.
