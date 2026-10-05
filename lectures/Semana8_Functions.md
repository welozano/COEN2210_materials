# Semana 8 — Functions: modularidad, parameters y passing by reference
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Gaddis, *Starting Out with C++: From Control Structures through Objects* — Capítulo 6, secciones 6.1–6.6 y 6.13

**Duración:** 170 min (lectura)
**Precede a:** Lab 8 — Functions: call-by-value y call-by-reference

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:

1. Explicar cómo las `functions` dividen un programa en tareas con una responsabilidad definida.
2. Distinguir `function definition`, `function header`, `function call` y `function prototype`.
3. Crear y llamar `void functions` con y sin parameters.
4. Diferenciar `arguments` de `parameters` y predecir el efecto de pass-by-value.
5. Usar pass-by-reference cuando una function debe cambiar intencionalmente una variable de `main`.

---

## Cómo probar los programas de esta lecture

Cada bloque es un **programa completo e independiente**. A diferencia de las lectures previas, no debes pegar estos ejemplos dentro de un `main` vacío: una function puede requerir un prototype antes de `main` y su definition puede aparecer después.

Antes de ejecutar un programa, predice qué function comienza primero, qué call ocurre después y a qué línea regresará el control al terminar la function llamada. Compila un ejemplo a la vez y cambia únicamente las entradas solicitadas.

---

## Parte 1 — Modular programming y responsabilidad de una function (15 min)

Hasta ahora, la mayor parte de nuestros programas vive dentro de `main`. Eso funciona para ejercicios pequeños, pero un programa que debe mostrar un menú, validar datos, actualizar un inventario y producir un reporte se vuelve difícil de leer si toda su lógica está mezclada en un solo block.

Una **function** es un conjunto de statements que realiza una tarea específica. Dividir un problema en tareas pequeñas y manejables se llama **modular programming**. `main` sigue siendo el punto donde comienza el programa, pero ahora coordina funciones con responsabilidades claras.

**Problema:** el laboratorio de electrónica tiene una cantidad limitada de turnos para usar una estación de osciloscopio. Al comenzar una sesión, el programa conoce cuántos turnos quedan disponibles. Una persona puede seleccionar la opción de reservar un turno o terminar la sesión. El programa debe proteger ese inventario: no puede aceptar una reserva si `remainingSlots` ya vale `0`.

Después de una selección, son posibles estos estados:

| Situación | Estado de `remainingSlots` | Mensaje esperado |
|---|---|---|
| Se solicita una reserva y queda al menos un turno | Disminuye en uno | `Reservation accepted.` |
| Se solicita una reserva y no quedan turnos | Permanece en `0` | `No slots available.` |
| Se selecciona terminar la sesión | No cambia | `No reservation requested.` |

El programa necesita mostrar el menú, aplicar una reserva cuando corresponde y presentar el estado final. Antes de escribir C++, podemos separar esas responsabilidades:

| Tarea | Posible function | Responsabilidad |
|---|---|---|
| Mostrar las opciones | `displayMenu` | Imprimir las opciones disponibles. |
| Aplicar una reserva | `reserveSlot` | Cambiar turnos solo si queda disponibilidad. |
| Mostrar el resultado | `displayReport` | Comunicar el estado final. |

Ya has usado functions de bibliotecas: `sqrt`, `pow`, `fixed` y `setprecision`. Cada una resuelve una tarea con un nombre y comportamiento definidos. Ahora aprenderemos a crear functions propias.

**Para practicar por tu cuenta:** propone nombres para cuatro functions de un programa que debe mostrar instrucciones, validar horas, calcular un costo y mostrar un recibo.

<details>
<summary>Ver una posible respuesta</summary>

`displayInstructions`, `readValidHours`, `calculateCost` y `displayReceipt` son nombres posibles. Las functions que retornan valores, como las dos del medio, se estudiarán en Semana 9.

</details>

---

## Parte 2 — Definir y llamar `void functions` (30 min)

### 2.1 — Una tarea que no devuelve un valor

En el laboratorio de electrónica, un asistente inicia una sesión de calibración cada vez que un estudiante llega a medir un circuito. Antes de permitir que se registre el primer voltaje, el programa debe mostrar el mismo título y la misma instrucción de seguridad. Durante un día pueden comenzar muchas sesiones, pero el texto no depende del estudiante, del circuito ni de una lectura: siempre es idéntico.

La entrada de esta tarea es ninguna; su única salida son dos líneas en pantalla. No hay una variable de estado que deba cambiar. Copiar esos dos `cout` en cada punto donde inicia una sesión produciría repetición y el riesgo de que una copia quede distinta.

Aquí aparece la necesidad de una **function**: escribimos ese grupo de statements una vez, le damos un nombre que describe su tarea y lo ejecutamos cada vez que haga falta. Una **function definition** es el código que declara ese nombre y especifica qué hará la function cuando sea llamada. La forma canónica de una `void function` sin datos de entrada es esta:

```cpp
void functionName() {                                  // Defines a function that does not return a value
    // Statements that perform one specific task.        // Contains the work of the function
}                                                        // Ends the function definition
```

Este patrón todavía no es un programa completo ni se ejecuta por sí solo. Es una plantilla para reconocer las partes que C++ necesita antes de ver un ejemplo real: `void` comunica que la function no devuelve un value, `functionName` se reemplaza por un nombre descriptivo y los paréntesis vacíos indican que no recibe datos. Los statements entre llaves son el **body**.

Ahora podemos nombrar las piezas de una function definition:

| Pieza | Ejemplo | Propósito |
|---|---|---|
| Return type | `void` | No devuelve un value. |
| Name | `displaySessionHeading` | Describe la tarea. |
| Parameter list | `()` | Esta versión no recibe datos. |
| Body | `{ ... }` | Ejecuta la tarea. |

Para convertir la plantilla en la tarea del banco de calibración, elegimos el nombre `displaySessionHeading` y colocamos los dos `cout` dentro del body. El programa completo necesita además `main`, porque `main` será quien decida cuándo ejecutar esa tarea.

```cpp
#include <iostream>                                      // Provides cout and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

void displaySessionHeading() {                           // Defines a function that displays a fixed heading
    cout << "Calibration session" << endl;              // Displays the session title
    cout << "Record measurements carefully." << endl;   // Displays a safety reminder
}                                                        // Ends the function definition

int main() {                                             // Starts the program
    cout << "Starting program." << endl;                // Displays the first statement in main
    displaySessionHeading();                              // Calls the heading function
    cout << "Ready for the first measurement." << endl; // Runs after the called function finishes

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function
```

El `function header` es `void displaySessionHeading()`. La call es `displaySessionHeading();`. El header no lleva punto y coma porque su body aparece después; la call sí es un statement y por eso termina con punto y coma.

### 2.2 — Trace del control de ejecución

El código anterior contiene dos functions, pero el programa no empieza ejecutando la primera que aparece en el archivo. Siempre comienza en `main`. La definition de `displaySessionHeading` solo deja preparada la tarea; el control llega a ella únicamente cuando `main` encuentra su call. Haz el trace siguiendo esa call, no el orden visual de las definitions.

| Paso | Lugar | Acción |
|---:|---|---|
| 1 | `main` | Muestra `Starting program.` |
| 2 | `main` | Encuentra la call a `displaySessionHeading`. |
| 3 | `displaySessionHeading` | Ejecuta sus dos `cout`. |
| 4 | `main` | Regresa a la línea posterior a la call. |

Una function no se ejecuta solo porque exista su definition. Si eliminas la call, el programa compila pero el encabezado no aparece.

**Para practicar por tu cuenta:** agrega una segunda call a `displaySessionHeading();` antes de `return 0;`. ¿Cuántas veces aparece el título?

<details>
<summary>Ver respuesta</summary>

Dos veces. Cada function call vuelve a ejecutar el body.

</details>

---

## Parte 3 — Function prototypes y organización del archivo (25 min)

Retomemos la estación de calibración. Al comenzar, el asistente debe ver el flujo principal sin recorrer detalles de impresión: mostrar las opciones, leer qué desea hacer y registrar la selección. El menú tiene solo dos estados posibles: `1` para comenzar una medición y `2` para terminar la sesión. En esta demostración, `main` todavía no procesa la opción; su propósito es mostrar que el menú aparece antes de leerla.

Podemos definir una function antes de `main`, como en la Parte 2. Sin embargo, en un programa donde `main` coordina varias tareas, conviene dejar las definitions debajo para que el flujo principal sea visible primero. Para ello usamos un **function prototype**: declara al compiler el return type, nombre y tipos de parameters antes de una call.

Antes de ver un programa completo, observa la relación canónica. El prototype anuncia una tarea; la call la usa más tarde. Este bloque sirve para leer la sintaxis, no es un programa ejecutable:

```cpp
void functionName();                                    // Declares a function before it is called

functionName();                                         // Calls that function from another function
```

El punto y coma separa las dos ideas: el prototype termina porque no tiene body; la call termina porque es un statement. La definition usa el mismo header pero agrega un body y por eso no lleva punto y coma tras los paréntesis.

| Elemento | Forma | ¿Tiene body? | ¿Lleva punto y coma? |
|---|---|---|---|
| Prototype | `void displayMenu();` | No | Sí |
| Header | `void displayMenu()` | Sí, inmediatamente después | No |
| Call | `displayMenu();` | No | Sí |

**Problema:** al organizar el archivo de la estación de calibración, queremos que quien lo lea encuentre `main` cerca del inicio y pueda ver rápidamente la secuencia principal: mostrar el menú, leer una selección y continuar. Por eso colocaremos la definition de `displayMenu` debajo de `main`.

Sin embargo, el compiler lee el archivo de arriba hacia abajo. Cuando llegue a `displayMenu();` dentro de `main`, todavía no habrá visto la definition que está más abajo. El prototype, escrito antes de `main`, resuelve exactamente ese problema: le informa al compiler que existe una `void function` llamada `displayMenu` que no recibe parameters. La function solo imprime las opciones; `main` lee y guarda la selección en `menuChoice`.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

void displayMenu();                                      // Declares the function before main calls it

int main() {                                             // Starts the program
    int menuChoice;                                      // Stores one menu selection

    displayMenu();                                       // Calls the function declared by the prototype
    cout << "Enter menu choice: ";                       // Prompts for one option
    cin >> menuChoice;                                   // Reads the selected option
    cout << "Choice entered: " << menuChoice << endl;   // Confirms the value read by main

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

void displayMenu() {                                    // Defines the function declared near the top
    cout << "1. Start measurement" << endl;             // Displays the first menu option
    cout << "2. End session" << endl;                   // Displays the second menu option
}                                                        // Ends the function definition
```

Un prototype y su header deben coincidir. Si uno declara `void displayMenu();` y el otro usa `void displayMenu(int choice)`, el compiler interpreta funciones distintas.

> ⚠️ Un prototype o una definition completa debe aparecer antes de cualquier call. De otro modo, el compiler no conoce los datos que la function espera.

**Para practicar por tu cuenta:** si una function se define después de `main`, ¿qué debe ir antes de `main`?

<details>
<summary>Ver respuesta</summary>

Un function prototype que coincida con la definition.

</details>

---

## Parte 4 — Parameters, arguments y pass-by-value (30 min)

La estación de calibración ahora recibe una lectura distinta para cada sensor. Una function sin parameters siempre hace exactamente la misma tarea; para procesar datos que cambian necesita recibir información. Primero observa la forma canónica de una function que recibe un dato:

```cpp
void functionName(type parameterName) {                 // Defines a function that receives one parameter
    // Statements use parameterName inside the function. // Uses the received local value
}                                                        // Ends the function definition

functionName(argument);                                 // Calls the function with one argument
```

Esta es una guía de sintaxis, no un programa completo: la call debe ir dentro de una function como `main`. El `parameterName` existe dentro de la function; el `argument` existe en la function que hace la call. Un **argument** aparece en la call; un **parameter** es la variable del header que recibe ese dato.

| Lugar | Código | Rol |
|---|---|---|
| Call | `showAdjustedReading(voltage);` | `voltage` es el argument. |
| Prototype | `void showAdjustedReading(double);` | Declara el tipo esperado. |
| Header | `void showAdjustedReading(double reading)` | `reading` es el parameter. |

**Problema:** un técnico registra el voltaje medido de un sensor en `main`. Para comparar esa medición contra un escenario de prueba, el programa debe mostrar una lectura temporalmente ajustada por `0.10 V`. Esa comparación no es una calibración real: el registro original debe permanecer intacto para que el técnico pueda contrastar ambos valores después. La entrada es un voltaje; la salida muestra primero el valor ajustado y luego el valor original almacenado. Pass-by-value entrega una copia del argument a la function, por lo que cumple esa regla.

Ahora aplica la tabla anterior a este problema: `voltage` será la variable que pertenece a `main`, `reading` será el parameter local y la call enviará el value de `voltage` a `reading`. Antes de ejecutar el programa, responde: si la function modifica `reading`, ¿debe cambiar también `voltage` después de que termine la call?

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
#include <iomanip>                                       // Provides fixed and setprecision
using namespace std;                                     // Allows standard-library names without the std:: prefix

void showAdjustedReading(double reading);                // Declares a function that receives a copied value

int main() {                                             // Starts the program
    double voltage;                                      // Stores the original sensor measurement

    cout << "Enter sensor voltage: ";                   // Prompts for one voltage measurement
    cin >> voltage;                                      // Reads the original value into main
    cout << fixed << setprecision(2);                    // Formats decimal output with two places
    showAdjustedReading(voltage);                        // Sends the current value as an argument
    cout << "Voltage stored in main: " << voltage << endl; // Shows that main keeps its original value

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

void showAdjustedReading(double reading) {               // Defines a function with a value parameter
    reading = reading + 0.10;                            // Changes only the local parameter copy
    cout << "Adjusted voltage: " << reading << endl;    // Displays the temporary adjusted value
}                                                        // Ends the function definition
```

Con entrada `5.00`, la function muestra `5.10`, pero `main` muestra `5.00`. En pass-by-value, modificar el parameter no modifica la variable original.

Los arguments deben coincidir con los parameters en número, tipo y orden. Para dos parameters, el primer argument inicializa el primero y el segundo inicializa el segundo.

**Para practicar por tu cuenta:** con `double voltage = 4.80;`, ¿qué muestra `main` después de llamar `showAdjustedReading(voltage);`? ¿Qué variable cambió?

<details>
<summary>Ver respuesta</summary>

`main` muestra `4.80`. El parameter local `reading` cambia a `4.90`, pero `voltage` no cambia.

</details>

---

## Parte 5 — Pass-by-reference: cambiar el estado original (30 min)

No toda corrección es temporal. Después de verificar un sensor con un patrón certificado, el técnico puede aprobar una corrección de `0.10 V`. En ese caso el registro que conservará el programa para la sesión debe cambiar: el valor corregido será el que aparezca en el reporte posterior. La entrada es el voltaje original almacenado por `main`; el resultado esperado es que esa misma variable contenga el valor corregido después de la call.

Para permitir ese cambio intencional usamos un **reference parameter**, escrito con `&` en el prototype y header. No es una forma de hacer código más corto: comunica que la function puede modificar el estado de quien la llama.

La forma canónica cambia en un solo lugar, pero ese cambio altera el significado del parameter. Las dos definitions siguientes son **alternativas** para comparar; no deben copiarse juntas con el mismo nombre en un programa:

```cpp
void functionName(double parameterName) {                // Receives a copied value parameter
    // Changes affect only the local parameter copy.     // Keeps the caller variable unchanged
}                                                        // Ends the value-parameter function

void functionName(double &parameterName) {               // Receives a reference to the caller variable
    // Changes affect the original caller variable.      // Updates the caller state intentionally
}                                                        // Ends the reference-parameter function
```

En ambos casos la call se escribe sin `&`: `functionName(voltage);`. La diferencia se declara donde la function recibe el parameter, no donde `main` la llama. El segundo header crea un alias de la variable original; por eso necesita un argument que sea una variable, no un literal.

**Problema:** a diferencia de la Parte 4, ahora `main` debe guardar el voltaje corregido, no solo verlo temporalmente.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
#include <iomanip>                                       // Provides fixed and setprecision
using namespace std;                                     // Allows standard-library names without the std:: prefix

void applyApprovedCorrection(double &reading);           // Declares a function with a reference parameter

int main() {                                             // Starts the program
    double voltage;                                      // Stores the sensor measurement used by main

    cout << "Enter sensor voltage: ";                   // Prompts for one voltage measurement
    cin >> voltage;                                      // Reads the value that will be changed by reference
    cout << fixed << setprecision(2);                    // Formats decimal output with two places
    applyApprovedCorrection(voltage);                    // Sends the variable to the reference parameter
    cout << "Corrected voltage in main: " << voltage << endl; // Displays the modified original value

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

void applyApprovedCorrection(double &reading) {          // Defines a function that accesses the original argument
    reading = reading + 0.10;                            // Changes the variable referred to by reading
    cout << "Correction applied." << endl;              // Confirms the state change
}                                                        // Ends the function definition
```

Con entrada `5.00`, `main` muestra `5.10`. El `&` no aparece en la call: se escribe `applyApprovedCorrection(voltage);`, no `applyApprovedCorrection(&voltage);`.

| Pregunta | Pass-by-value | Pass-by-reference |
|---|---|---|
| ¿Qué recibe el parameter? | Una copia. | Acceso a la variable original. |
| ¿Cambiar el parameter modifica `main`? | No. | Sí. |
| ¿Lleva `&` en prototype y header? | No. | Sí. |
| ¿Acepta un literal como argument? | Sí. | No; necesita una variable. |
| Uso apropiado | Observar o calcular sin cambiar el dato original. | Actualizar intencionalmente el estado de quien llama. |

Un reference parameter es poderoso y debe usarse con intención. El nombre de la function debe comunicar que puede cambiar algo, como `applyApprovedCorrection`.

**Para practicar por tu cuenta:** ¿por qué `applyApprovedCorrection(5.00);` no es válida?

<details>
<summary>Ver respuesta</summary>

Un reference parameter necesita una variable existente a la que pueda referirse. `5.00` es un literal, no una variable modificable.

</details>

---

## Parte 6 — Integrar functions con selection structures (20 min)

Volvamos al laboratorio que reserva turnos para la estación de osciloscopio. Al iniciar la sesión, la persona encargada entra cuántos turnos quedan disponibles. El menú ofrece `1` para reservar uno y `2` para terminar. Si se selecciona reserva y el inventario es mayor que cero, el resultado esperado es disminuir `remainingSlots` en uno; si vale cero, debe quedar en cero e informar que no hay disponibilidad. Seleccionar terminar no cambia el inventario.

El programa de esta parte procesa una sola selección para concentrarse en la distribución de responsabilidades. Antes de mirar código, identifica qué information posee cada function:

| Function | Información que usa | Resultado que produce |
|---|---|---|
| `main` | Entrada inicial, selección y `remainingSlots` | Decide si se solicita una reserva y muestra el estado final. |
| `displayMenu` | Ninguna | Muestra las dos opciones. |
| `reserveSlot` | Reference a `remainingSlots` | Disminuye el inventario o explica por qué no puede hacerlo. |

Así `main` coordina la entrada y la decisión; `displayMenu` solo produce output; `reserveSlot` protege y actualiza el estado por reference. En Lab 8 podrás extender este patrón a un menú que se repite.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

void displayMenu();                                      // Declares the function that prints the menu
void reserveSlot(int &remainingSlots);                   // Declares the function that can update available slots

int main() {                                             // Starts the program
    int remainingSlots;                                  // Stores the current number of available slots
    int menuChoice;                                      // Stores one menu selection

    cout << "Enter available slots: ";                  // Prompts for the initial inventory
    cin >> remainingSlots;                               // Reads the current slot count
    displayMenu();                                       // Calls the function responsible for the menu
    cout << "Enter menu choice: ";                      // Prompts for one action
    cin >> menuChoice;                                   // Reads the selected action

    if (menuChoice == 1) {                               // Checks whether reservation was selected
        reserveSlot(remainingSlots);                     // Calls the function that may change the inventory
    } else {                                             // Handles every option other than reservation
        cout << "No reservation requested." << endl;    // Reports that inventory remains unchanged
    }                                                    // Ends the selection structure

    cout << "Slots remaining: " << remainingSlots << endl; // Displays the state after the function call
    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

void displayMenu() {                                    // Defines the menu-display function
    cout << "1. Reserve a slot" << endl;                // Displays the reservation option
    cout << "2. End session" << endl;                   // Displays the exit option
}                                                        // Ends the function definition

void reserveSlot(int &remainingSlots) {                 // Defines the function that accesses original inventory
    if (remainingSlots > 0) {                            // Checks whether a slot is available
        remainingSlots--;                                // Updates the original slot count by reference
        cout << "Reservation accepted." << endl;        // Confirms the state change
    } else {                                            // Handles a reservation when no slots remain
        cout << "No slots available." << endl;          // Explains why the state did not change
    }                                                    // Ends the validation structure
}                                                        // Ends the reservation function
```

Prueba `remainingSlots = 1` con opción `1`, luego `remainingSlots = 0` con opción `1`, y finalmente opción `2`. Identifica qué function es responsable de cada resultado.

---

## Práctica guiada — Diseñar antes de programar (20 min)

**Problema:** antes de encender una cámara ambiental, un técnico registra la temperatura medida por su sensor. El laboratorio puede aprobar una corrección fija de `2.0` grados si el técnico confirma que el sensor fue comparado con un patrón. El programa debe mostrar un encabezado, leer la temperatura medida, preguntar `Y/N` y reportar la temperatura que se usará durante la prueba. Con `Y` o `y`, el valor almacenado debe aumentar en `2.0`; con `N`, debe conservar exactamente la medición inicial.

En parejas, diseña un programa con estas functions:

1. `displayStationHeading()` — `void`, sin parameters; muestra `Temperature test station`.
2. `applyTemperatureCorrection(...)` — `void`, recibe la temperatura por reference y le suma `2.0`.

| Pregunta de diseño | Decisión esperada |
|---|---|
| ¿Qué function no necesita parameters? | La que muestra el encabezado. |
| ¿Qué variable debe cambiar fuera de la function? | La temperatura de `main`. |
| ¿Qué parameter necesita la corrección? | Un reference parameter `double &...`. |
| ¿Qué estructura decide si se llama? | `if`/`else` en `main`. |

Antes de programar, escribe el trace esperado para cada respuesta: con `Y` o `y`, `main` llama la function de corrección y luego muestra el valor aumentado; con `N`, no hace esa call y muestra el valor original. Esa predicción determina dónde debe estar el `if` y por qué la temperatura debe ser una variable de `main`.

Prueba `20.0` con `Y`, `y` y `N`. Si terminas temprano, cambia temporalmente el reference parameter a pass-by-value y explica por qué el valor final deja de cambiar.

---

## Resumen de la sesión

- Modular programming divide un problema grande en functions con responsabilidades claras.
- Una `void function` realiza una tarea sin devolver un value a quien la llama.
- Un call transfiere temporalmente el control y luego continúa en la línea siguiente.
- Un prototype permite colocar definitions después de `main` y debe coincidir con el header.
- Pass-by-value usa una copia; pass-by-reference usa `&` para actualizar la variable original.
- Reference se usa solo cuando cambiar el estado de quien llama es parte intencional de la tarea.

## Próxima sesión

En el **Lab 8** practicarás `void functions`, prototypes, parameters, call-by-value y call-by-reference. En la Semana 9 continuaremos con functions que retornan valores y scope.
