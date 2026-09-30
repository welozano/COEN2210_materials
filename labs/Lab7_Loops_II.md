# Lab 7 — Loops II: `for`, Counters y Accumulators
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano<br>
**Basado en:** Semana 6 — Repetition Structures; Gaddis, Capítulo 5 (secciones 5.4, 5.6 y 5.7)<br>
**Duración:** 110 min<br>
**Requisitos:** Labs 1–3, Lab 5 y Lab 6 completados; `cin`, `cout`, `fixed`, `setprecision`, operadores aritméticos, relacionales y lógicos, `if`/`else`, `switch`, `while`, `do while` y `for`

---

## Objetivos

Al finalizar este laboratorio, el estudiante podrá:

1. Usar un `for` loop cuando la cantidad de iterations se conoce antes de comenzar.
2. Identificar la inicialización, condition y update de un `for` loop.
3. Usar un **counter** para contar resultados que cumplen una condición.
4. Usar un **accumulator** para conservar un total que cambia en cada iteration.
5. Integrar `for`, `while`, `if`/`else`, `switch`, operadores y salida formateada en programas con un contexto definido.
6. Diseñar y ejecutar `test cases` que comprueben límites, resultados válidos e intentos inválidos.

---

## Parte 0 — Preparar la carpeta y el repositorio (5 min)

En los labs anteriores creaste un repositorio separado para cada entrega. En este lab continuarás ese flujo: los tres programas pertenecen a la misma práctica y deben vivir en una sola carpeta de Lab 7, pero esa carpeta no debe mezclarse con los repositorios de los labs anteriores.

> 🖱️ **Vas a usar VS Code.**

1. Dentro de tu carpeta padre de COEN 2210, crea una carpeta nueva llamada `lab7-for-loops`.
2. Ábrela como la carpeta raíz en VS Code con `File → Open Folder...`.
3. Abre Source Control con `Ctrl+Shift+G` (Windows) o `Cmd+Shift+G` (Mac) y selecciona **Initialize Repository**.

**¿Qué hace esto?** Crea un historial Git independiente para los archivos de este lab.

**Qué deberías ver:** el Explorer muestra `LAB7-FOR-LOOPS` como carpeta raíz y Source Control muestra un repositorio vacío.

> ⚠️ No inicialices Git en la carpeta padre que contiene todos los labs. Si lo haces, los archivos e historiales de prácticas distintas quedarán mezclados.

---

## Parte 1 — Crear los archivos y actualizar el header (5 min)

> 🖱️ **Vas a usar VS Code.**

Crea estos tres archivos dentro de `lab7-for-loops`:

1. `calibration_summary.cpp`
2. `inspection_report.cpp`
3. `parts_order.cpp`

Copia este header al inicio de **cada** archivo y completa los campos entre corchetes. La `Description` debe describir el propósito particular de ese archivo, no una descripción genérica del lab.

```cpp
/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Your Full Name]
 * Lab: 7 - Loops II
 * Description: [What this specific program does]
 * Due Date: [Date]
 */
```

**¿Qué hace esto?** El header documenta la autoría, el propósito y la fecha de cada programa.

**Qué deberías ver:** los tres archivos aparecen en el Explorer y cada uno comienza con un header completo en inglés.

Ahora crea un archivo llamado `.gitignore` y agrega estas líneas:

```gitignore
# Compiled programs
calibration_summary
calibration_summary.exe
inspection_report
inspection_report.exe
parts_order
parts_order.exe
```

**¿Qué hace esto?** Evita que Git incluya los ejecutables creados por el compilador.

**Qué deberías ver:** después de compilar, Source Control debe mostrar los archivos `.cpp` y `.gitignore`, pero no los ejecutables.

---

## Parte 2 — `calibration_summary.cpp`: guía resuelta de `for`, counter y accumulator (15 min)

Un banco de calibración debe registrar un número conocido de lecturas de voltaje antes de decidir cuántas cumplen el rango esperado. La persona técnica indica cuántas lecturas se tomarán; por eso el programa sabe la cantidad de iterations antes de iniciar y un `for` es apropiado. Cada lectura debe agregarse a un total para calcular el promedio final, y cada lectura entre **4.75 V y 5.25 V**, inclusive, debe aumentar un contador de lecturas aceptadas.

En este problema:

- La entrada es una cantidad de 1 a 5 lecturas y después un voltaje por cada lectura.
- `totalVoltage` es el **accumulator**: comienza en `0.0` y recibe cada voltaje.
- `acceptedReadingCount` es el **counter**: comienza en `0` y aumenta solo cuando una lectura está dentro del rango.
- La salida es el total, el promedio y la cantidad de lecturas aceptadas.

Primero observa el diseño antes de escribir C++:

| Pregunta de diseño | Decisión |
|---|---|
| ¿Cuántas veces se repite la lectura? | La cantidad indicada en `readingCount`. |
| ¿Qué estructura repite una cantidad conocida? | `for`. |
| ¿Qué variable guarda una suma que crece? | `totalVoltage`, inicializada en `0.0`. |
| ¿Qué variable cuenta solo lecturas aceptadas? | `acceptedReadingCount`, inicializada en `0`. |
| ¿Cuándo una lectura es aceptada? | Cuando es mayor o igual que 4.75 **y** menor o igual que 5.25. |

### Paso 1 — Leer y validar la cantidad de lecturas

**Objetivo:** antes de repetir, el programa necesita una cantidad válida. Aquí `while` se usa antes del `for`: no sabemos cuántos intentos serán necesarios para obtener una cantidad entre 1 y 5.

En `calibration_summary.cpp`, debajo del header, escribe este programa completo. Puedes compilarlo ya; por ahora valida la cantidad y prepara las variables que usarán los próximos pasos.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
#include <iomanip>                                       // Provides fixed and setprecision
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    const double MIN_VOLTAGE = 4.75;                      // Stores the lower accepted voltage limit
    const double MAX_VOLTAGE = 5.25;                      // Stores the upper accepted voltage limit
    int readingCount;                                     // Stores the known number of readings
    int acceptedReadingCount = 0;                         // Counts readings inside the accepted range
    double voltage;                                       // Stores one voltage reading per iteration
    double totalVoltage = 0.0;                            // Accumulates every voltage reading

    cout << "Enter number of readings from 1 to 5: ";   // Prompts for the iteration count
    cin >> readingCount;                                  // Reads the first count candidate

    while (readingCount < 1 || readingCount > 5) {        // Repeats while the count is outside the allowed range
        cout << "Invalid count. Try again: ";           // Explains why another count is required
        cin >> readingCount;                              // Reads a replacement count
    }                                                     // Ends after a valid count is entered

    // TODO: Replace this line with the for loop from Step 2.
    // TODO: Replace this line with the summary from Step 3.

    return 0;                                            // Ends the program successfully
}                                                         // Ends the main function
```

### Paso 2 — Procesar cada lectura con `for`

**Objetivo:** ahora que `readingCount` es válido, el programa debe pedir exactamente esa cantidad de voltajes. Reemplaza **solo** el primer `TODO` por el bloque siguiente. No borres el segundo `TODO`, `return 0;` ni la llave final.

El header del `for` tiene tres piezas: `reading = 1` inicializa el counter de iterations; `reading <= readingCount` decide si falta una lectura; y `reading++` prepara el número de la próxima lectura. Dentro del body, el accumulator se actualiza sin importar si el voltaje se acepta; el otro counter cambia solo dentro del `if`.

```cpp
    for (int reading = 1; reading <= readingCount; reading++) { // Repeats once for each requested reading
        cout << "Enter voltage for reading " << reading << ": "; // Identifies the current reading in the prompt
        cin >> voltage;                                   // Reads one voltage for this iteration
        totalVoltage += voltage;                          // Adds this voltage to the running total

        if (voltage >= MIN_VOLTAGE && voltage <= MAX_VOLTAGE) { // Checks whether the reading is within both limits
            acceptedReadingCount++;                       // Counts one accepted reading
            cout << "Reading accepted." << endl;         // Reports the accepted result
        } else {                                          // Handles a reading outside the accepted range
            cout << "Reading requires review." << endl;  // Reports the out-of-range result
        }                                                 // Ends the selection structure
    }                                                     // Ends the count-controlled loop
```

### Paso 3 — Mostrar el resumen acumulado

**Objetivo:** después del `for`, todas las readings ya fueron procesadas. Reemplaza **solo** el segundo `TODO` por este bloque. El promedio se calcula después del loop porque `totalVoltage` ya contiene todas las lecturas y `readingCount` fue validado como mayor que cero.

```cpp
    double averageVoltage = totalVoltage / readingCount; // Calculates the average after all readings are accumulated

    cout << fixed << setprecision(2);                    // Formats displayed decimal values with two places
    cout << "Total voltage: " << totalVoltage << endl;   // Displays the accumulated voltage total
    cout << "Average voltage: " << averageVoltage << endl; // Displays the calculated average
    cout << "Accepted readings: " << acceptedReadingCount << endl; // Displays the conditional counter
```

Prueba `3` lecturas con `4.80`, `5.30` y `5.00`. El total debe ser `15.10`, el promedio `5.03` y el counter de lecturas aceptadas debe ser `2`.

**Esto es lo que debes entregar (obligatorio):** `calibration_summary.cpp` completo, con el header actualizado, la validación de `readingCount`, el `for`, el counter, el accumulator y el resumen formateado.

**Para practicar por tu cuenta (opcional, no se entrega):** cambia temporalmente el rango aceptado a 4.90–5.10. Antes de ejecutarlo, predice cómo cambiaría el counter con las mismas tres lecturas; después restaura el rango original.

---

## Parte 3 — `inspection_report.cpp`: resumen de inspecciones (30 min)

Un coordinador de control de calidad debe revisar varios dispositivos antes de enviarlos al laboratorio de pruebas. El coordinador conoce cuántos dispositivos llegaron en el lote; para cada uno, una persona registra un **quality score** de 0 a 100. Un dispositivo con score de 70 o más pasa la inspección. Al final, el coordinador necesita saber el promedio de scores y cuántos dispositivos pasaron.

El programa no debe conservar todos los scores individuales: solo necesita procesar uno, actualizar el total y decidir si aumenta el counter. Este es exactamente el caso para un accumulator y un counter.

Antes de escribir código, completa mentalmente estas preguntas de diseño:

| Pregunta de diseño | Decisión esperada |
|---|---|
| ¿Qué valor controla cuántas veces corre el `for`? | `deviceCount`. |
| ¿Qué variable debe comenzar en `0.0`? | El accumulator `totalScore`. |
| ¿Qué variable debe comenzar en `0`? | El counter `passingDeviceCount`. |
| ¿Qué score cuenta como aprobado? | Uno mayor o igual que 70. |
| ¿Cuándo se calcula el promedio? | Después del `for`, usando el total y el número de dispositivos. |

En `inspection_report.cpp`, escribe este starter code debajo del header. La validación de `deviceCount` ya está resuelta porque aplica un patrón del Lab 6. Completa los `TODO` según las preguntas de diseño.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
#include <iomanip>                                       // Provides fixed and setprecision
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    int deviceCount;                                     // Stores the known number of devices in the batch
    int passingDeviceCount = 0;                          // Counts devices with a passing quality score
    double qualityScore;                                 // Stores one device score per iteration
    double totalScore = 0.0;                             // Accumulates all quality scores

    cout << "Enter number of devices from 1 to 10: ";  // Prompts for the batch size
    cin >> deviceCount;                                  // Reads the first batch-size candidate

    while (deviceCount < 1 || deviceCount > 10) {        // Repeats while the batch size is outside the allowed range
        cout << "Invalid device count. Try again: ";    // Explains why another batch size is required
        cin >> deviceCount;                              // Reads a replacement batch size
    }                                                     // Ends after a valid batch size is entered

    // TODO: Process each device with a for loop and update the total and counter.
    // TODO: Use if/else to report whether each device passes inspection.
    // TODO: Calculate and display the formatted final report after the loop.

    return 0;                                            // Ends the program successfully
}                                                         // Ends the main function
```

### Pasos para completar el programa

1. Escribe un `for` que empiece con `device = 1`, continúe mientras `device <= deviceCount` y aumente `device` de uno en uno.
2. Dentro del loop, muestra un prompt que identifique el número del dispositivo, lee `qualityScore` y actualiza `totalScore` con `+=`.
3. Usa `if (qualityScore >= 70)` para aumentar `passingDeviceCount` y mostrar `Device passed inspection.`. En `else`, muestra `Device requires review.`.
4. Después del loop, calcula `averageScore` dividiendo `totalScore` entre `deviceCount` y muestra el reporte con `fixed << setprecision(2)`.

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila y ejecuta el programa desde la carpeta `lab7-for-loops`.

**Windows:**

```powershell
g++ inspection_report.cpp -o inspection_report
.\inspection_report.exe
```

**Mac:**

```bash
clang++ inspection_report.cpp -o inspection_report
./inspection_report
```

**¿Qué hace esto?** El primer comando compila el archivo y crea un ejecutable; el segundo ejecuta el programa.

**Qué deberías ver:** el programa pide exactamente un score por cada dispositivo válido, muestra una decisión para cada uno y termina con un resumen formateado.

Prueba estos `test cases`:

| Caso | Entradas, en orden | Resultado esperado |
|---|---|---|
| 1 | `3`, `80`, `70`, `50` | Total `200.00`, promedio `66.67` y 2 dispositivos aprobados. |
| 2 | `1`, `69` | Total y promedio `69.00`; 0 dispositivos aprobados. |
| 3 | `0`, `2`, `100`, `70` | Rechaza el primer conteo, luego procesa 2 dispositivos aprobados. |

Al final de `inspection_report.cpp`, después de `main`, agrega este comentario de bloque en inglés y reemplaza cada respuesta entre corchetes:

```cpp
/*
 * Analysis:
 * 1. [Explain why totalScore starts at 0.0.]
 * 2. [Explain why passingDeviceCount changes for 70 but not for 69.]
 * 3. [Explain why averageScore is calculated after the for loop.]
 */
```

**Esto es lo que debes entregar (obligatorio):** `inspection_report.cpp` con el header, todos los `TODO` completados, los tres test cases ejecutados y el bloque `Analysis` respondido en inglés.

**Para practicar por tu cuenta (opcional, no se entrega):** añade un segundo counter para scores de 90 o más y muestra ese resultado al final. No cambies la definición de dispositivo aprobado, que sigue siendo 70 o más.

---

## Parte 4 — `parts_order.cpp`: líneas de pedido con `for` y `switch` (35 min)

Un técnico prepara una orden de piezas para una práctica de electrónica. Antes de comenzar sabe cuántas solicitudes de piezas debe procesar. Para cada solicitud, el programa muestra un menú, recibe una opción y una cantidad, calcula el costo de una solicitud válida y lo añade al costo total de la orden.

El contexto tiene tres decisiones distintas:

1. Un `while` valida que la opción de menú esté entre 1 y 3 antes de procesarla.
2. El `switch` asigna el precio unitario y el nombre de la pieza para una opción válida.
3. El `if` decide si la cantidad está entre 1 y 5. Una cantidad inválida no se añade al total.

El `for` controla cuántas solicitudes se procesan, `validLineCount` cuenta solo las líneas que llegaron a calcularse y `orderTotal` acumula los costos válidos. Si la opción de pieza no está en el menú, el programa debe pedir otra opción para esa misma solicitud; una cantidad inválida, en cambio, registra el problema y deja esa solicitud fuera del total.

| Opción | Pieza | Precio unitario |
|---:|---|---:|
| `1` | Cable set | `$3.25` |
| `2` | Fuse pack | `$4.50` |
| `3` | Connector kit | `$1.75` |

En `parts_order.cpp`, escribe este starter code debajo del header. El propósito es preparar las variables y la primera entrada; los dos loops y la lógica de cada solicitud los construirás tú a partir de los pasos que siguen. No copies un loop resuelto: decide qué debe contener su header, su body y el código que va después de terminar.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
#include <iomanip>                                       // Provides fixed and setprecision
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    int requestCount;                                    // Stores the known number of part requests
    int partChoice;                                      // Stores one menu selection
    int quantity;                                        // Stores the requested quantity for one part
    int validLineCount = 0;                              // Counts requests that have a valid part and quantity
    double unitPrice;                                    // Stores the price selected by the switch
    double lineCost;                                     // Stores the cost of one valid request
    double orderTotal = 0.0;                             // Accumulates all valid line costs
    bool isValidPartChoice;                              // Tracks whether the switch selected a real part

    cout << "Enter number of part requests from 1 to 5: "; // Prompts for the iteration count
    cin >> requestCount;                                 // Reads the first request-count candidate

    // TODO: Validate requestCount with a while loop before processing requests.
    // Keep asking while the count is below 1 or above 5.

    // TODO: Write the for loop header that processes request 1 through requestCount.
    {
        // TODO: Reset isValidPartChoice to true.

        // TODO: Display the three menu options, prompt for partChoice, and read the selection.

        // TODO: Use a while loop to ask again while partChoice is below 1 or above 3.

        // TODO: Use switch to assign unitPrice and display the selected part.
        // Include case 1, case 2, case 3, and a defensive default case.

        // TODO: For a valid part choice, prompt for quantity and use if/else.
        // Accept quantities from 1 to 5 and update lineCost, orderTotal, and validLineCount.
        // Otherwise, report that the request was skipped.
    }

    // TODO: After the for loop, format and display validLineCount and orderTotal.

    return 0;                                            // Ends the program successfully
}                                                         // Ends the main function
```

### Pasos para completar el programa

1. Después de leer `requestCount`, escribe un `while` que repita la lectura mientras el valor sea menor que 1 o mayor que 5. Dentro del loop, muestra `Invalid request count. Try again:` y vuelve a leer el valor. Este loop debe terminar antes de iniciar el procesamiento de solicitudes.
2. Escribe un `for` que comience con `request = 1`, continúe mientras `request <= requestCount` y aumente `request` de uno en uno. Usa la estructura indentada del starter code para organizar las operaciones de cada solicitud.
3. Al inicio de cada iteration, asigna `true` a `isValidPartChoice`. Muestra el menú de la tabla y lee `partChoice`. Antes de usar `switch`, escribe un `while` que muestre `Invalid part choice. Try again:` y vuelva a leer mientras la opción sea menor que 1 o mayor que 3. Ese loop valida la opción de **la misma** solicitud; no debe avanzar al próximo valor de `request`.
4. Después de que `partChoice` sea válida, escribe un `switch` con `case 1`, `case 2`, `case 3` y `default`. Cada caso válido asigna `unitPrice`, muestra el nombre de la pieza y usa `break`; conserva `default` como protección y cambia el flag a `false` si llegara a ejecutarse.
5. Solo si el flag sigue en `true`, pide `quantity`. Usa `if`/`else` y una condition con `&&` para aceptar cantidades de 1 a 5, inclusive. Para una cantidad válida, calcula `lineCost = unitPrice * quantity`, añade el costo a `orderTotal`, aumenta `validLineCount` y muestra el costo de la línea. Para una cantidad inválida, muestra `Invalid quantity. Request skipped.` sin cambiar el total ni el counter.
6. Después del `for`, activa `fixed << setprecision(2)` y muestra cuántas líneas válidas procesaste junto con el costo total de la orden.

> ⚠️ `isValidPartChoice` debe reiniciarse a `true` al comienzo de cada iteration. Si una opción inválida deja el flag en `false` y no se reinicia, una opción válida posterior también sería descartada incorrectamente.

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila después de completar un `case` o un bloque de lógica, no solamente al final.

**Windows:**

```powershell
g++ parts_order.cpp -o parts_order
.\parts_order.exe
```

**Mac:**

```bash
clang++ parts_order.cpp -o parts_order
./parts_order
```

**¿Qué hace esto?** Compilar en incrementos pequeños permite localizar el cambio que causó un error de sintaxis o de lógica.

**Qué deberías ver:** el menú aparece exactamente una vez por cada solicitud, las líneas válidas suman al total y una opción o cantidad inválida no modifica el accumulator.

Prueba estos `test cases`:

| Caso | Entradas, en orden | Resultado esperado |
|---|---|---|
| 1 | `2`, `1`, `2`, `3`, `1` | 2 líneas válidas y total de `$8.25`. |
| 2 | `1`, `2`, `0` | Muestra error de cantidad, 0 líneas válidas y total `$0.00`. |
| 3 | `1`, `9`, `1`, `5` | Rechaza `9`, pide otra opción para la única solicitud; luego acepta Cable set por 5 y muestra total `$16.25`. |
| 4 | `0`, `1`, `3`, `5` | Rechaza el primer request count; luego acepta una línea de `$8.75`. |

Al final de `parts_order.cpp`, después de `main`, agrega este comentario de bloque en inglés y responde después de ejecutar los test cases:

```cpp
/*
 * Test analysis:
 * 1. [Explain why orderTotal starts at 0.0.]
 * 2. [Explain why an invalid part choice asks for another menu selection.]
 * 3. [Explain why isValidPartChoice is reset during every for iteration.]
 * 4. [Explain why an invalid quantity does not change validLineCount.]
 */
```

**Esto es lo que debes entregar (obligatorio):** `parts_order.cpp` con el header, todos los `TODO` completados, los cuatro test cases ejecutados y el bloque `Test analysis` respondido en inglés.

**Para practicar por tu cuenta (opcional, no se entrega):** agrega una cuarta pieza al menú y al `switch`. Elige un precio nuevo, actualiza los test cases y comprueba que también se acumula correctamente.

---

## Parte 5 — Revisar test cases y hacer trace (10 min)

Un **test case** no es solamente ejecutar el programa: es una combinación planificada de entradas y un resultado que esperas observar. En este lab, los resultados deben confirmar dos ideas diferentes: el `for` repite exactamente el número conocido de veces y los counters/accumulators cambian solo cuando corresponde.

Antes de entregar, escoge un caso de `inspection_report.cpp` y uno de `parts_order.cpp`. Para cada uno, escribe en papel o en un comentario temporal:

1. El valor inicial del accumulator.
2. El valor del accumulator después de cada iteration.
3. Cuándo cambia el counter y cuándo no debe cambiar.
4. El valor final que esperas antes de ejecutar el programa.

Como ejemplo, en el Caso 1 de `parts_order.cpp`, `orderTotal` inicia en `0.00`, cambia a `6.50` después de dos Cable sets y termina en `8.25` después de un Connector kit. `validLineCount` cambia de 0 a 1 y luego a 2.

**Esto es lo que debes entregar (obligatorio):** evidencia de haber ejecutado todos los test cases indicados en las Partes 3 y 4, y los bloques de análisis completos en los dos archivos.

**Para practicar por tu cuenta (opcional, no se entrega):** cambia temporalmente el update del `for` de `request++` a `request += 2`. Predice qué solicitudes se procesarían con `requestCount = 5`; no entregues ese cambio y restáuralo después de observarlo.

---

## Cierre — Revisar el trabajo y hacer commit/push (10 min)

Antes de entregar, revisa esta lista:

- Los tres archivos tienen un header completo y una `Description` distinta.
- Todos los prompts, mensajes y comentarios dentro de C++ están en inglés.
- `calibration_summary.cpp` usa un `for`, `totalVoltage` como accumulator y `acceptedReadingCount` como counter.
- `inspection_report.cpp` procesa exactamente `deviceCount` scores y calcula el promedio después del loop.
- `parts_order.cpp` procesa exactamente `requestCount` solicitudes, usa `switch` y no suma líneas inválidas.
- Los counters comienzan en `0`, los accumulators monetarios o de mediciones comienzan en `0.0` y los valores se actualizan en el lugar correcto.
- `.gitignore` evita que los ejecutables aparezcan en Source Control.

> 🖱️ **Vas a usar el panel de Source Control de VS Code.**

1. Guarda los tres archivos `.cpp` y `.gitignore`.
2. En Source Control, verifica que aparecen esos cuatro archivos y no los ejecutables.
3. Haz stage de todos los cambios con el botón `+` junto a **Changes**.
4. Escribe un mensaje como `Lab 7: for loops, counters, and accumulators` y haz clic en **Commit**.
5. Selecciona **Publish Branch** si este es el primer push del repositorio, o **Sync Changes** si ya lo publicaste.

**¿Qué hace esto?** Stage prepara los archivos para el commit; el commit guarda una versión en el historial local; Publish Branch o Sync Changes sube ese historial a GitHub.

**Qué deberías ver:** Source Control deja de mostrar cambios pendientes y el repositorio remoto contiene los tres archivos `.cpp` y `.gitignore`.

---

## Próxima sesión

**Semana 8 — Functions.** Usarás funciones para dividir un programa en tareas con nombres, parámetros y valores de retorno.
