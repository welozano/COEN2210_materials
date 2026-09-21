# Semana 6 — Repetition Structures
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Gaddis, *Starting Out with C++: From Control Structures through Objects* — Capítulo 5, "Loops and Files" (secciones 5.1–5.6)

**Duración:** 170 min (lectura)
**Precede a:** Lab 6 — Loops I: `while` y `do while`, integrando selection structures

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:

1. Explicar qué es una `iteration` y las partes que controlan un loop.
2. Usar `++` y `--` de forma intencional.
3. Construir y trazar `while`, `do while` y `for`.
4. Usar `while` para input validation y detectar infinite loops.
5. Elegir un loop según el problema.

---

## Cómo probar los code snippets durante la lecture

Los bloques son fragmentos. Prueba **un snippet a la vez** dentro de esta plantilla; no los combines porque reutilizan variables.

```cpp
#include <iostream>                             // Provides cin, cout, and endl
using namespace std;                            // Allows standard-library names without the std:: prefix

int main() {                                    // Starts the program
    // Paste one code snippet here.              // Keeps each experiment independent
    return 0;                                   // Ends the program successfully
}                                               // Ends the main function
```

Al probar un loop, predice cuántas `iterations` ejecutará y qué valor tendrá su counter al terminar.

---

## Parte 1 — `++`, `--` y counters (20 min)

### 1.1 — Qué es un loop y para qué sirve

Hasta ahora, nuestros programas seguían una **sequence structure**: ejecutaban instrucciones una tras otra. Con `if`/`else` agregamos selection structures, que escogen entre caminos. Una **repetition structure**, o **loop**, es una estructura de control que repite una instrucción o un block de instrucciones mientras se cumpla una condition.

Los loops sirven cuando una misma tarea debe ocurrir varias veces, pero la cantidad puede cambiar. En vez de escribir cinco `cout` casi idénticos para mostrar cinco etiquetas, escribimos un block una sola vez y dejamos que el programa lo repita. Cada vuelta completa por el body se llama una **iteration**.

### 1.2 — Cambiar el estado de un problema

Para que un loop eventualmente termine, algo debe cambiar entre una iteration y la siguiente. Un **counter** es una variable que aumenta o disminuye en cada iteration. `count++` equivale a `count = count + 1`; `count--` equivale a `count = count - 1`.

**Problema:** la recepción de un laboratorio comienza el día con cierta cantidad de turnos disponibles. Cuando una persona reserva un turno, el programa debe actualizar el número almacenado y mostrar cuántos quedan. La entrada es la cantidad inicial de turnos; la salida es la cantidad después de una reserva. Este cambio de estado será la misma idea que permitirá que un loop avance y eventualmente termine.

Antes de resolver el caso general de muchas reservas, aislaremos **una sola operación**: descontar un turno. El siguiente snippet **no es la solución final ni contiene un loop**; simula exactamente una reserva para observar qué hace `--`. En la Parte 2 repetiremos este tipo de update dentro de un `while`.

```cpp
int remainingSlots;                             // Stores available appointment slots

cout << "Enter available appointment slots: "; // Prompts for the starting value
cin >> remainingSlots;                          // Reads the current slot count

remainingSlots--;                               // Decreases the stored value by one
cout << "Slots remaining: " << remainingSlots << endl; // Displays the updated value
```

Si entran `8` turnos, el snippet muestra `7`: solo resolvió una reserva. Para resolver ocho reservas, el programa tendría que repetir la misma operación y decidir cuándo detenerse; ese es precisamente el problema que resolverán los loops.

### 1.3 — Prefix y postfix

Los operadores `++` y `--` pueden escribirse **antes** o **después** de una variable. Cuando aparecen antes, se llaman **prefix**: `++count` modifica el valor primero y luego produce el nuevo valor para la expression. Cuando aparecen después, se llaman **postfix**: `count++` produce primero el valor actual y luego lo modifica.

La diferencia importa cuando el operador aparece dentro de una expression, como un `cout` o una asignación. Cuando el update está solo en su propia línea —por ejemplo, `count++;` dentro del body de un loop— ambas formas aumentan el counter una vez. En esta etapa, preferiremos esa forma separada porque hace el trace más legible y evita mezclar un update con otro cálculo.

**Para practicar por tu cuenta:** si `counter` vale 3, ¿qué muestran `cout << counter++ << endl;` y luego `cout << counter << endl;`?

<details>
<summary>Ver respuesta</summary>

Muestran `3` y luego `4`.

</details>

---

## Parte 2 — El `while` loop (30 min)

### 2.1 — Inicialización, condition y update

Un `while loop` evalúa una condition antes de ejecutar su body. Si es `true`, ejecuta el block y vuelve a evaluar; si es `false`, continúa después del loop. Cada vuelta completa es una **iteration**.

**Problema:** retomemos la recepción del laboratorio de la Parte 1. Durante un período, una persona de recepción procesa cierta cantidad de actualizaciones: una reserva elimina un turno y una cancelación devuelve un turno. La entrada es la cantidad inicial de turnos y la cantidad de actualizaciones que se procesarán. En cada iteration, el programa pide la acción (`A` para agregar o `R` para remover), actualiza `remainingSlots` y muestra el nuevo estado. Al terminar todas las actualizaciones, debe mostrar el total final.

Necesitamos dos variables que cambian por razones distintas: `processedUpdates` es el **counter** que indica cuántas actualizaciones se han procesado y permite terminar el loop; `remainingSlots` representa el estado real del inventario de turnos.

```cpp
int remainingSlots;                             // Stores the current number of available slots
int updateCount;                                // Stores how many updates will be processed
int processedUpdates = 0;                       // Starts the loop-control counter at zero
char slotAction;                                // Stores A to add a slot or R to remove a slot

cout << "Enter available appointment slots: "; // Prompts for the starting inventory
cin >> remainingSlots;                          // Reads the initial slot count
cout << "Enter the number of updates to process: "; // Prompts for the known number of updates
cin >> updateCount;                             // Reads the loop limit

while (processedUpdates < updateCount) {        // Repeats until every requested update is processed
    cout << "Enter A to add a slot or R to remove a slot: "; // Prompts for one update action
    cin >> slotAction;                          // Reads the selected action

    if (slotAction == 'A' || slotAction == 'a') { // Checks whether the action adds one available slot
        remainingSlots++;                       // Increases the slot inventory by one
    } else if ((slotAction == 'R' || slotAction == 'r') && remainingSlots > 0) { // Checks for a valid removal
        remainingSlots--;                       // Decreases the slot inventory by one
    } else {                                    // Handles an invalid action or an unavailable removal
        cout << "Slot update was not applied." << endl; // Reports that the inventory did not change
    }                                           // Ends the selection structure

    processedUpdates++;                         // Moves the counter toward a false loop condition
    cout << "Slots remaining: " << remainingSlots << endl; // Displays the state after this update
}                                               // Ends the repeated block

cout << "Final available slots: " << remainingSlots << endl; // Displays the final inventory
```

| Pieza | Ejemplo | Pregunta clave |
|---|---|---|
| Inicialización | `processedUpdates = 0` | ¿Cuántas actualizaciones se han procesado al inicio? |
| Condition | `processedUpdates < updateCount` | ¿Aún faltan actualizaciones por procesar? |
| Update | `processedUpdates++` | ¿Qué permite que el loop termine? |

### 2.2 — `while` es un pretest loop

Si `updateCount` es `0`, la condition inicial `0 < 0` es `false`; el body ejecuta cero iterations. Esto es correcto: un `while` es un **pretest loop**. Antes de usarlo, decide si cero repetitions es aceptable o si el input necesita validación.

Si se empieza con `5` turnos y se procesan tres acciones `R`, `A`, `R`, los valores de `remainingSlots` son 4, 5 y 4. Al mismo tiempo, `processedUpdates` toma los valores 1, 2 y 3, y luego termina el loop. Este trace ayuda a distinguir la variable que controla la repetición de la variable que representa el estado del problema.

**Para practicar por tu cuenta:** si `updateCount` es 1 y la única acción es `A`, ¿cuántas iterations ejecuta y qué variables cambian?

<details>
<summary>Ver respuesta</summary>

Ejecuta una iteration. `processedUpdates` cambia de 0 a 1 y termina el loop; `remainingSlots` aumenta en uno.

</details>

---

## Parte 3 — `while` para input validation (25 min)

### 3.1 — Repetir la lectura mientras el dato sea inválido

En Semana 5, `if`/`else` permitía aceptar o rechazar un dato una vez. Cuando el programa debe pedirlo otra vez, usamos `while`: leer una primera vez, repetir mientras sea inválido y usarlo solo después de validar.

**Problema:** el sistema de préstamos solo permite reservar equipo entre 1 y 4 horas. No debe aceptar una duración de 0, negativa o mayor que 4, pero tampoco debe terminar la solicitud por un error simple: debe explicar el problema y pedir otra duración. La entrada es una duración y las posibles repeticiones; la salida final debe confirmar únicamente una duración válida. Un valor es inválido si es menor que 1 **o** mayor que 4; por eso la condition usa `||`:

```cpp
int loanHours;                                  // Stores the requested loan duration

cout << "Enter loan duration from 1 to 4 hours: "; // Prompts for the allowed range
cin >> loanHours;                               // Reads the first candidate duration

while (loanHours < 1 || loanHours > 4) {        // Repeats while the duration is outside the range
    cout << "Invalid loan duration. Try again: "; // Explains why another value is required
    cin >> loanHours;                           // Reads a replacement value for the next test
}                                               // Ends after a valid duration is entered

cout << "Loan duration accepted: " << loanHours << endl; // Uses the value after validation
```

Cada lado de `||` debe ser una `relational expression` completa. `loanHours < 1 || > 4` no es C++ válido. Prueba `0`, luego `3`; después prueba `5`, luego `1`.

### 3.2 — Rango inválido vs. input de tipo incorrecto

Este patrón valida un número que `cin` pudo leer. Si se escribe texto cuando se espera `int`, el stream queda en error y se necesita una técnica distinta para limpiarlo; la veremos más adelante. Por ahora, prueba valores numéricos dentro y fuera del rango.

**Para practicar por tu cuenta:** escribe en pseudocódigo la condition para validar una temperatura de 10 a 35, inclusive.

<details>
<summary>Ver respuesta</summary>

Mientras la temperatura sea menor que 10 o mayor que 35, mostrar un error y leerla otra vez.

</details>

---

## Parte 4 — El `do while` loop (25 min)

### 4.1 — Ejecutar primero y evaluar después

Un `do while loop` ejecuta el body antes de evaluar la condition. Es un **posttest loop** y siempre ejecuta al menos una iteration. Úsalo cuando una acción debe ocurrir una vez antes de preguntar si se repetirá.

**Problema:** al iniciar una sesión de monitoreo, un técnico necesita registrar por lo menos una temperatura. Después de cada registro, el técnico decide si hay otra medición que guardar. La primera medición no puede depender de una respuesta previa porque todavía no se ha hecho ninguna pregunta de repetición. La entrada consiste en una o más temperaturas y una respuesta `Y`/`N`; el programa debe mostrar cada valor registrado y detenerse al recibir `N`.

```cpp
char recordAgain;                               // Stores whether the user wants another record
double temperature;                             // Stores one temperature measurement

do {                                            // Starts a block that executes at least once
    cout << "Enter a temperature: ";           // Prompts for one measurement
    cin >> temperature;                         // Reads the temperature from standard input
    cout << "Recorded temperature: " << temperature << endl; // Displays the recorded value

    cout << "Record another temperature? (Y/N): "; // Prompts for the repetition decision
    cin >> recordAgain;                         // Reads the repetition choice
} while (recordAgain == 'Y' || recordAgain == 'y'); // Repeats only for Y or y
```

El punto y coma después de `while (...)` es obligatorio. El `||` permite aceptar `Y` o `y`.

### 4.2 — Comparación de loops

| Pregunta | `while` | `do while` |
|---|---|---|
| ¿Cuándo evalúa la condition? | Antes del body | Después del body |
| ¿Puede ejecutar cero iterations? | Sí | No |
| Uso típico | Validación antes de continuar | Repetir una acción o menú |
| ¿Lleva punto y coma final? | No | Sí |

**Para practicar por tu cuenta:** ¿qué loop usarías para un menú que debe aparecer al menos una vez? Explica por qué.

<details>
<summary>Ver respuesta</summary>

`do while`, porque el menú debe ejecutarse antes de evaluar si se repetirá.

</details>

---

## Parte 5 — Introducción al `for` loop (20 min)

### 5.1 — Repeticiones de cantidad conocida

Un `for loop` reúne inicialización, condition y update en el header. Es apropiado cuando conocemos la cantidad de iterations. Igual que `while`, es pretest.

**Problema:** antes de una práctica, un instructor necesita etiquetas consecutivas para cada estación de trabajo. La cantidad de estaciones se conoce antes de empezar; si hay 4 estaciones, el resultado debe ser exactamente cuatro líneas, desde `Workstation 1` hasta `Workstation 4`. No estamos repitiendo hasta que la persona decida parar ni corrigiendo input: estamos repitiendo una cantidad conocida de veces.

```cpp
int stationCount;                               // Stores the number of workstations to label

cout << "Enter the number of workstations: ";  // Prompts for the known number of iterations
cin >> stationCount;                            // Reads the required label count

for (int station = 1; station <= stationCount; station++) { // Initializes, tests, and updates the counter
    cout << "Workstation " << station << endl; // Displays one label per iteration
}                                               // Ends the count-controlled loop
```

`station` solo existe dentro del `for`. En Lab 7 practicaremos esta estructura con contadores y acumuladores; se introduce aquí porque Semana 7 será repaso y Midterm 1, no contenido nuevo.

### 5.2 — Elegir la estructura

| Situación | Loop apropiado | Razón |
|---|---|---|
| Repetir input inválido | `while` | No se conoce la cantidad de intentos. |
| Registrar al menos una lectura | `do while` | El body debe ejecutarse una vez. |
| Crear 12 etiquetas | `for` | La cantidad de iterations se conoce. |

**Para practicar por tu cuenta:** identifica inicialización, condition y update de un `for` que muestra 1 a 8.

<details>
<summary>Ver una posible respuesta</summary>

Un counter inicia en 1, continúa mientras sea menor o igual que 8 y aumenta uno al final de cada iteration.

</details>

---

## Parte 6 — Debugging y test cases para loops (25 min)

### 6.1 — Infinite loops

Un **infinite loop** no tiene forma de hacer su condition `false`. Antes de ejecutar, verifica que el body modifique la variable que controla la condition.

**Problema de debugging:** un programa de inventario debe mostrar exactamente los artículos 1 hasta `itemCount` y luego terminar. Con una entrada de `3`, esperamos tres líneas y el programa debe volver al prompt. El siguiente intento contiene un error intencional: analiza primero qué variable debe cambiar y por qué el programa no podría llegar a su salida. No lo ejecutes hasta corregirlo:

```cpp
int itemCount;                                  // Stores how many items should be listed
int currentItem = 1;                            // Starts the loop-control counter at one

cout << "Enter the number of items: ";         // Prompts for the requested item count
cin >> itemCount;                               // Reads the loop limit from standard input

while (currentItem <= itemCount) {              // Tests a condition that may remain true forever
    cout << "Item " << currentItem << endl;    // Repeats the same item number without an update
    // TODO: Add the update that allows the condition to become false. // Prevents an infinite loop
}                                               // Ends only after the condition becomes false
```

La solución necesita un update dentro del body, no un límite arbitrario. Otros errores frecuentes son usar `=` en vez de `==`, dejar el update fuera de las llaves o escribir un punto y coma después de `while (condition)`.

### 6.2 — Test cases con límites

Para validar 1–4 horas, prueba límites y valores inválidos, no solo `2`:

| Entrada inicial | Entrada posterior | Resultado esperado |
|---:|---:|---|
| `1` | — | Acepta sin repetir. |
| `4` | — | Acepta sin repetir. |
| `0` | `3` | Muestra un error y luego acepta `3`. |
| `5` | `1` | Muestra un error y luego acepta `1`. |

**Para practicar por tu cuenta:** corrige mentalmente el snippet anterior y predice la salida con `itemCount = 3`.

<details>
<summary>Ver respuesta</summary>

Se agrega `currentItem++`; la salida muestra `Item 1`, `Item 2` e `Item 3`.

</details>

---

## Práctica guiada e integración de loops (25 min)

### Ejercicio guiado — Registro de inspecciones

**Problema:** un supervisor prepara una lista de inspecciones para el día. El sistema acepta solamente entre 1 y 5 inspecciones; si la cantidad no es válida, debe pedirla otra vez. Una vez validada, debe imprimir exactamente una etiqueta por inspección, desde `Inspection 1` hasta `Inspection N`. En la plantilla mínima, crea ese programa usando `while` para validar y `for` para producir la lista.

Antes de programar, decide: la condition que mantiene la validación, el counter del `for`, y qué debe ocurrir para las entradas `0`, luego `3`. Prueba también `6`, luego `5`.

---

## Resumen de la sesión

- `++` y `--` actualizan con frecuencia el counter de un loop.
- `while` y `for` son pretest loops; pueden ejecutar cero iterations.
- `while` permite repetir input validation hasta que un valor sea utilizable.
- `do while` ejecuta el body al menos una vez y termina con punto y coma.
- Un loop correcto necesita inicialización, condition y un update que permita terminar.
- Los boundary values y traces descubren errores de límite e infinite loops.

## Próxima sesión

En el Lab 6 se practicarán `while` y `do while` con input validation y selection structures. `for` se reforzará en Lab 7 con contadores y acumuladores antes de Midterm 1.
