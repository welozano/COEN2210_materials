# Lab 9 — File I/O with Value-Returning Functions
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Semana 9 — return values, `bool` y scope local; adelanto de File I/O; Gaddis, Capítulo 5, sección 5.11

**Duración:** 110 min
**Requisitos:** Labs 1–3 y 5–8; `string`, `cin`, `cout`, `getline`, `for`, `while`, `if`/`else`, value-returning functions y formato de output

---

## Objetivos

Al finalizar este laboratorio, el estudiante podrá:

1. Usar una function que retorna un `int` o `double` para producir un resultado que `main` debe guardar.
2. Usar una `bool function` dentro de `if`/`else` para decidir qué mensaje o data guardar.
3. Crear un text file con `ofstream` y registrar data calculado por el programa.
4. Abrir un text file existente con `ifstream`, validar la apertura y leerlo línea por línea.
5. Usar loops, un counter y un accumulator para procesar data numérico desde un archivo.

---

## Parte 0 — Preparar la carpeta y el repositorio (5 min)

Este lab reúne programas C++ y text files que esos programas crean. Crea una carpeta nueva llamada `lab9-file-io`, ábrela como carpeta raíz en VS Code e inicializa un repositorio desde Source Control.

**¿Qué hace esto?** Mantiene juntos los programas y sus archivos de data, sin mezclarlos con los Labs anteriores.

**Qué deberías ver:** `LAB9-FILE-IO` aparece como carpeta raíz y Source Control muestra un repositorio vacío.

---

## Parte 1 — Crear archivos y `.gitignore` (5 min)

Crea estos archivos C++:

1. `create_lab_readiness_report.cpp`
2. `read_lab_readiness_report.cpp`
3. `motor_current_analysis.cpp`

Cada archivo debe comenzar con el header estándar. Usa `Lab: 9 - File I/O` y una `Description` distinta en inglés que explique ese programa específico.

```cpp
/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Your Full Name]
 * Lab: 9 - File I/O
 * Description: [What this specific program does]
 * Due Date: [Date]
 */
```

En `.gitignore`, agrega los seis ejecutables para Mac y Windows. **No** agregues los archivos `.txt`: son parte del resultado que se debe verificar y entregar.

```gitignore
# Compiled programs
create_lab_readiness_report
create_lab_readiness_report.exe
read_lab_readiness_report
read_lab_readiness_report.exe
motor_current_analysis
motor_current_analysis.exe
```

**Qué deberías ver:** al compilar, Source Control muestra los tres `.cpp`, `.gitignore` y los archivos `.txt` creados; no muestra los ejecutables.

---

## Parte 2 — `create_lab_readiness_report.cpp`: guía progresiva (25 min)

Antes de abrir un laboratorio de computadoras para un workshop, la persona encargada debe saber si hay suficientes estaciones de trabajo disponibles. Conoce el nombre del laboratorio, la cantidad total de estaciones, cuántas están fuera de servicio y cuántas estaciones se requieren como mínimo para el workshop.

El programa debe responder dos preguntas distintas:

1. ¿Cuántas estaciones están disponibles? Una function debe calcular y **return** ese número a `main`.
2. ¿Puede abrirse el workshop? Otra function debe **return** `true` o `false` según si las estaciones disponibles alcanzan el mínimo requerido.

Finalmente, `main` debe guardar todos esos data y el resultado de la decisión en `lab_readiness_report.txt`. Para concentrarnos en functions y File I/O, usa values válidos: total positivo, estaciones fuera de servicio entre `0` y el total, y mínimo requerido positivo.

Trabajaremos el programa por pasos. Cada paso conserva un programa que compila; no pegues un programa completo nuevo sobre el anterior.

### Paso 1 — Recibir los data de `main`

Usaremos **un solo programa completo**. Los bloques de los Pasos 2 y 3 aparecen inicialmente dentro de block comments. En cada paso quitarás solamente las marcas `/*` y `*/` que llevan el nombre de ese paso; así irás activando código que ya está colocado donde corresponde. No borres los comments de una línea (`//`): explican el propósito de cada statement.

Escribe el siguiente programa debajo de tu header. Para el Paso 1, deja comentados los bloques `Step 2` y `Step 3`, compila y ejecuta con `Engineering Lab A`, `12`, `3` y `8`. Confirma que cada value puede entrarse antes de continuar.

```cpp
#include <fstream>                                       // Provides ofstream for file output in Step 3
#include <iostream>                                      // Provides cin, cout, and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

/* Step 2: Remove these delimiters to activate the function prototypes.
int calculateAvailableWorkstations(int totalWorkstations, int unavailableWorkstations); // Declares a function that returns the available count
bool canOpenWorkshop(int availableWorkstations, int minimumRequired); // Declares a function that returns the opening decision
*/

int main() {                                             // Starts the program
    string labName;                                      // Stores the laboratory name
    int totalWorkstations;                               // Stores the total number of workstations
    int unavailableWorkstations;                         // Stores the number of unavailable workstations
    int minimumRequired;                                 // Stores the minimum number required for the workshop

    cout << "Enter laboratory name: ";                  // Prompts for the laboratory name
    getline(cin, labName);                               // Reads the complete laboratory name
    cout << "Enter total workstations: ";              // Prompts for the total number of workstations
    cin >> totalWorkstations;                            // Reads the total number into main
    cout << "Enter unavailable workstations: ";        // Prompts for the unavailable count
    cin >> unavailableWorkstations;                      // Reads the unavailable count into main
    cout << "Enter minimum workstations required: ";   // Prompts for the workshop requirement
    cin >> minimumRequired;                              // Reads the minimum requirement into main

    /* Step 2: Remove these delimiters to calculate and store both returned values.
    int availableWorkstations;                           // Stores the number returned by the availability function
    bool workshopCanOpen;                                // Stores the decision returned by the Boolean function

    availableWorkstations = calculateAvailableWorkstations(totalWorkstations, unavailableWorkstations); // Stores the calculated available count
    workshopCanOpen = canOpenWorkshop(availableWorkstations, minimumRequired); // Stores whether the workshop can open

    cout << "Available workstations: " << availableWorkstations << endl; // Displays the returned available count
    cout << boolalpha << "Workshop can open: " << workshopCanOpen << endl; // Displays the returned Boolean value
    */

    /* Step 3: Remove these delimiters to create and write the report file.
    ofstream outputFile("lab_readiness_report.txt");    // Opens the report file for output
    if (!outputFile) {                                  // Tests whether the output file opened successfully
        cout << "Error: Could not create the report file." << endl; // Reports an opening failure in English
        return 1;                                       // Ends the program with an error status
    }                                                    // Ends the output-file validation

    outputFile << "Lab Readiness Report" << endl;      // Writes a fixed report heading
    outputFile << "Laboratory: " << labName << endl;   // Writes the entered laboratory name
    outputFile << "Total workstations: " << totalWorkstations << endl; // Writes the total count
    outputFile << "Unavailable workstations: " << unavailableWorkstations << endl; // Writes the unavailable count
    outputFile << "Minimum required: " << minimumRequired << endl; // Writes the minimum requirement
    outputFile << "Available workstations: " << availableWorkstations << endl; // Writes the returned available count

    if (workshopCanOpen) {                              // Tests the Boolean value returned by the decision function
        outputFile << "Workshop can open." << endl;     // Writes the positive workshop status
    } else {                                             // Handles the case where the minimum is not met
        outputFile << "Workshop cannot open." << endl;  // Writes the negative workshop status
    }                                                    // Ends the workshop-status selection

    outputFile.close();                                 // Flushes and closes the report file
    */

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

/* Step 2: Remove these delimiters to activate the function definitions.
int calculateAvailableWorkstations(int totalWorkstations, int unavailableWorkstations) { // Defines the availability calculation
    return totalWorkstations - unavailableWorkstations;  // Returns the number of usable workstations
}                                                        // Ends the availability function

bool canOpenWorkshop(int availableWorkstations, int minimumRequired) { // Defines the opening decision
    return availableWorkstations >= minimumRequired;     // Returns true when the minimum is met
}                                                        // Ends the Boolean function
*/
```

### Paso 2 — Calcular y decidir con functions

Ahora quita los delimitadores `/*` y `*/` de los **tres** bloques marcados `Step 2`: los prototypes antes de `main`, las variables y function calls dentro de `main`, y las function definitions después de `main`. Los tres son necesarios: los prototypes permiten que `main` haga las calls, y las definitions proporcionan el trabajo que las functions ejecutan.

En este paso el programa muestra los dos returned values en la terminal, pero todavía no escribe un file.

| Function | Input | Return value |
|---|---|---|
| Cálculo de disponibilidad | Total y estaciones fuera de servicio | Un `int` con las estaciones disponibles. |
| Decisión de apertura | Estaciones disponibles y mínimo requerido | `true` si hay suficientes; `false` si no las hay. |

Antes de ejecutar, predice los results del ejemplo: `12 - 3` produce `9` estaciones disponibles. El workshop requiere `8` estaciones y hay `9`, por lo que se cumple la condition `availableWorkstations >= minimumRequired`; la `bool function` debe devolver `true`. Compila y verifica ambas predicciones.

### Paso 3 — Guardar el reporte en un archivo

Con el código del Paso 2 ya activo, quita los delimitadores `/*` y `*/` del bloque marcado `Step 3` dentro de `main`. Ese bloque crea y valida el `ofstream`, escribe el reporte y cierra el stream. No cambies los bloques del Paso 2.

El reporte debe contener labels en inglés. Una vez que completes este paso, ejecútalo con los values anteriores y abre `lab_readiness_report.txt` desde el Explorer para verificar que `Available workstations: 9` y `Workshop can open.` aparecen en el archivo.

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila y ejecuta el programa después de completar cada paso.

**Windows:**

```powershell
g++ create_lab_readiness_report.cpp -o create_lab_readiness_report
.\create_lab_readiness_report.exe
```

**Mac:**

```bash
clang++ create_lab_readiness_report.cpp -o create_lab_readiness_report
./create_lab_readiness_report
```

**¿Qué hace esto?** El primer comando compila la versión actual del programa; el segundo ejecuta sus prompts, function calls y escritura del reporte.

**Qué deberías ver:** el Explorer muestra `lab_readiness_report.txt` y ese archivo contiene los data entrados, el returned `int` y el status decidido por el returned `bool`.

Al final de `create_lab_readiness_report.cpp`, después de la última llave, agrega y responde este bloque de comentarios en inglés:

```cpp
/*
 * Analysis:
 * 1. What value does the availability function return for your test case?
 * 2. What condition makes the Boolean function return true?
 * 3. Why must the output stream be closed after writing the report?
 */
```

**Esto es lo que debes entregar (obligatorio):** `create_lab_readiness_report.cpp` con dos value-returning functions, `lab_readiness_report.txt` y el bloque `Analysis` respondido en inglés.

**Para practicar por tu cuenta (opcional, no se entrega):** ejecuta otra vez con `12` estaciones, `5` fuera de servicio y mínimo `8`. Predice y luego verifica el nuevo status del reporte.

---

## Parte 3 — `read_lab_readiness_report.cpp`: leer el reporte (20 min)

El reporte ya existe y contiene data producido por el primer programa. Este segundo programa no calcula disponibilidad ni vuelve a escribir el archivo: su única responsabilidad es abrir el reporte existente y presentar sus líneas en la terminal. Esa separación evita que un programa lector borre accidentalmente un reporte al usar un output stream.

Antes de escribir código, responde:

| Pregunta de diseño | Decisión que debes tomar |
|---|---|
| ¿El programa necesita `ofstream` o `ifstream`? | Selecciona el stream según si el programa escribe o lee. |
| ¿Qué debe ocurrir si el reporte no existe? | El programa debe informar el problema, no intentar leer data inexistente. |
| ¿Cuántas líneas debe leer? | No lo sabes de antemano; el loop debe terminar al llegar al final del archivo. |

Completa el programa con estas instrucciones:

1. Abre `lab_readiness_report.txt` para input y verifica que el archivo se abrió antes de leer.
2. Si no se puede abrir, muestra un error en inglés y termina el programa con un status distinto de cero.
3. Si se abrió, muestra un heading en la terminal y usa `getline` dentro de un `while` loop para imprimir cada línea.
4. Cierra el input stream al terminar el loop.

El starter code declara los elementos que necesitarás. Los `TODO` indican dónde construir cada parte de la solución.

```cpp
#include <fstream>                                       // Provides ifstream for file input
#include <iostream>                                      // Provides cout and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    ifstream inputFile("lab_readiness_report.txt");     // Prepares the existing report for input
    string line;                                         // Stores one complete line read from the file

    // TODO: Test whether inputFile opened successfully and handle an error in English.
    // TODO: Display a terminal heading before reading the report contents.
    // TODO: Use getline in a while loop to display each line from the report.
    // TODO: Close the input stream after all lines have been processed.

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function
```

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila el programa lector solo después de que `lab_readiness_report.txt` exista.

**Windows:**

```powershell
g++ read_lab_readiness_report.cpp -o read_lab_readiness_report
.\read_lab_readiness_report.exe
```

**Mac:**

```bash
clang++ read_lab_readiness_report.cpp -o read_lab_readiness_report
./read_lab_readiness_report
```

**¿Qué hace esto?** Compila y ejecuta el programa lector. El ejecutable abre el reporte creado en la Parte 2 y muestra las líneas que encuentre.

**Qué deberías ver:** el heading aparece una vez y luego se muestran todas las líneas de `lab_readiness_report.txt`, incluido el status del workshop.

Al final de `read_lab_readiness_report.cpp`, después de la última llave, agrega y responde este bloque de comentarios en inglés:

```cpp
/*
 * Analysis:
 * 1. Why does this program use ifstream instead of ofstream?
 * 2. What causes the while loop to stop?
 * 3. Why must the program test the input stream before reading?
 */
```

**Esto es lo que debes entregar (obligatorio):** `read_lab_readiness_report.cpp` con validación de apertura, un `while` que use `getline`, cierre del archivo y el bloque `Analysis` respondido en inglés.

**Para practicar por tu cuenta (opcional, no se entrega):** cambia temporalmente el nombre en `ifstream` a `missing_report.txt`. Ejecuta el programa, observa el mensaje de error y devuelve el nombre correcto antes de entregar.

---

## Parte 4 — `motor_current_analysis.cpp`: procesar data numérico desde un archivo (40 min)

Un banco de pruebas registra la corriente medida de varios motores pequeños. La persona técnica decide cuántas muestras tomará, entra un máximo permitido para el average y luego entra una lectura de corriente para cada muestra. El programa debe guardar cada reading en `motor_current_readings.txt`, una por línea. Después debe abrir ese archivo, procesar todos los numbers que encuentre y decidir si el average de corriente cumple el límite indicado.

Esta parte combina cuatro responsabilidades:

| Responsabilidad | Resultado esperado |
|---|---|
| Escribir las muestras | Un text file con un `double` por línea. |
| Leer las muestras | Counter y accumulator basados en data leído realmente. |
| Calcular el average | Una function que retorna un `double`. |
| Evaluar el límite | Una `bool function` que retorna si el average cumple el máximo. |

Por ejemplo, si la persona entra las tres readings `1.50`, `2.00` y `2.50`, el archivo `motor_current_readings.txt` debe quedar así. No debe incluir prompts, labels ni el average: esos elementos se muestran en la terminal, mientras que el archivo conserva los data numéricos que el programa leerá después.

```text
1.50
2.00
2.50
```

Antes de programar, responde:

| Pregunta de diseño | Razón |
|---|---|
| ¿Qué loop pide exactamente la cantidad de muestras indicada? | La cantidad se conoce antes de comenzar a escribir. |
| ¿Qué loop lee el archivo? | La cantidad de values que se logra leer se conoce solo mientras se procesa el archivo. |
| ¿Qué return type requiere la function del average? | El average puede incluir una parte decimal. |
| ¿Qué return type requiere la decisión sobre el máximo? | La respuesta solo puede ser verdadera o falsa. |

Usa esta relación matemática después de leer el archivo, solamente si se leyó al menos una muestra:

| Resultado | Relación |
|---|---|
| Average current | total de readings ÷ cantidad de readings leídos |

Completa el programa con esta secuencia:

1. Diseña y declara dos value-returning functions: una recibe total y count para retornar el average; la otra recibe average y maximum para retornar un `bool`.
2. Solicita `requestedSamples` y `maximumCurrent`. No continúes si la cantidad solicitada no es positiva.
3. Abre `motor_current_readings.txt` para output, verifica que se abrió y usa un `for` loop para solicitar y guardar una lectura por cada muestra.
4. Cierra el output stream antes de abrir el mismo archivo para input.
5. Abre el archivo para input, verifica que se abrió y usa un `while` loop cuya condition lea cada `double` exitosamente. Dentro del loop, actualiza el counter y el accumulator.
6. Cuando termine el loop, llama la function que retorna el average. Luego usa la `bool function` en `if`/`else` para mostrar si el average cumple el límite.
7. Cierra el input stream. El programa debe reportar el counter de readings realmente leídos, no asumir que siempre coincide con `requestedSamples`.

```cpp
#include <fstream>                                       // Provides ifstream and ofstream for file access
#include <iomanip>                                       // Provides fixed and setprecision
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

// TODO: Declare prototypes for a double-returning average function and a Boolean limit function.

int main() {                                             // Starts the program
    int requestedSamples;                                // Stores the number of readings requested by the user
    int samplesRead = 0;                                 // Counts readings successfully read from the file
    double maximumCurrent;                               // Stores the allowed average-current limit
    double currentReading;                               // Stores one current reading at a time
    double totalCurrent = 0.0;                           // Accumulates the readings obtained from the file
    double averageCurrent;                               // Stores the average returned by a function

    // TODO: Read and validate requestedSamples and maximumCurrent before creating the output file.
    // TODO: Open a validated output stream, use a for loop to write each reading, and close the stream.
    // TODO: Open a validated input stream, then use a while loop to update samplesRead and totalCurrent.
    // TODO: Call both functions, display the decision, and close the input stream.

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

// TODO: Define the average-returning function after main.
// TODO: Define the Boolean limit function after main.
```

Test with `3` samples, maximum current `2.25`, and readings `1.50`, `2.00` and `2.50`. Tu programa debe crear un archivo de tres líneas, reportar `3` readings leídos, mostrar un average de `2.00` y reportar que está dentro del límite. Luego prueba `0` como cantidad solicitada: el programa debe informar que la cantidad no es válida y no debe intentar calcular un average.

Al final de `motor_current_analysis.cpp`, después de la última llave, agrega y responde este bloque de comentarios en inglés:

```cpp
/*
 * Analysis:
 * 1. Why does the average function return double instead of int?
 * 2. What exact comparison makes the Boolean function return true?
 * 3. Why is samplesRead more reliable than requestedSamples for calculating the average?
 * 4. Why must the output stream close before the input stream opens the same file?
 */
```

**Esto es lo que debes entregar (obligatorio):** `motor_current_analysis.cpp`, `motor_current_readings.txt`, validación de apertura de ambos streams, dos value-returning functions, un `for` loop de escritura, un `while` loop de lectura, counter, accumulator, average con dos decimals, decisión `bool`, el bloque `Analysis` y los dos test cases.

**Para practicar por tu cuenta (opcional, no se entrega):** después de una ejecución correcta, explica por qué no debes editar `motor_current_readings.txt` y luego ejecutar el programa completo esperando conservar esa edición manual. Relaciona tu respuesta con el momento en que el programa abre el output stream.

---

## Parte 5 — Cierre, test cases y commit/push (15 min)

Antes de entregar verifica:

- Cada archivo `.cpp` tiene su propio header en inglés y una `Description` que corresponde a ese programa.
- `lab_readiness_report.txt` y `motor_current_readings.txt` están presentes y no aparecen en `.gitignore`.
- Las functions que calculan quantities retornan el type apropiado y `main` guarda esos returned values.
- Las `bool functions` responden solo la condition; `main` usa sus returned values en `if`/`else`.
- Cada output stream se cierra antes de abrir el mismo archivo para input.
- Cada input stream se valida antes de leer data.
- El reader de la Parte 3 usa `getline` en la condition del `while`.
- El programa de la Parte 4 usa el counter de readings realmente leídos para calcular el average.
- Los tres bloques `Analysis` están respondidos en inglés al final de sus respectivos archivos.
- Los prompts, identifiers y comments de C++ están en inglés.

Haz stage de los tres `.cpp`, los dos `.txt` y `.gitignore`, crea un commit como `Lab 9: files and return values` y publica/sincroniza el repositorio.

**Qué deberías ver:** Source Control sin cambios pendientes y el repositorio remoto con los tres programas y los dos archivos de data.

## Próxima sesión

La lecture de **File I/O** profundizará los conceptos usados en este lab: streams, apertura, validación, procesamiento de data y cierre de archivos.
