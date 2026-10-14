# Semana 9 — Functions: return values, `bool` y scope local
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Gaddis, *Starting Out with C++: From Control Structures through Objects* — Capítulo 6, secciones 6.7–6.10; adelanto introductorio de File I/O

**Duración:** 110 min (lectura — sesión ajustada por el feriado del lunes)
**Precede a:** Lab 9 — File I/O

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:

1. Diferenciar una `void function` de una function que devuelve un value.
2. Escribir prototypes y definitions con un return type compatible con el value que se devuelve.
3. Usar una function call que devuelve un value en una assignment, una expresión o una decisión.
4. Crear functions que devuelvan `bool` y usarlas directamente en `if`/`else`.
5. Explicar el scope de variables locales y parameters, sin usar global variables.
6. Reconocer el flujo básico para crear un archivo de texto y leerlo línea por línea.

---

## Cómo probar los programas de esta lecture

Cada bloque es un **programa completo e independiente**. Compila uno a la vez y, antes de ejecutarlo, identifica qué data entra a `main`, qué data recibe cada function y qué value regresa a la línea que hizo la function call.

Para esta sesión, no basta con observar el output. Después de cada ejecución, escribe un trace corto: el value de los arguments, el value que calcula la function y el value que recibe `main` después de `return`.

---

## Parte 1 — De realizar una tarea a devolver un resultado (15 min)

En Semana 8 usamos `void functions` para realizar tareas: mostrar un menú, imprimir un encabezado o actualizar una variable por reference. Algunas tareas, sin embargo, producen un resultado que `main` necesita usar después. Mostrar el resultado con `cout` no es suficiente si `main` debe guardarlo, combinarlo con otro cálculo o tomar una decisión con él.

**Problema:** en una estación de pruebas, cada dispositivo requiere la misma cantidad de minutos para completar una verificación. La persona técnica entra el número de dispositivos y los minutos requeridos por dispositivo. El programa debe calcular el tiempo total y guardarlo en `main` para mostrarlo en el reporte final.

La tarea de calcular el total no necesita imprimir nada ni cambiar datos de `main`. Necesita recibir dos values, calcular uno nuevo y enviarlo de vuelta a la function que hizo la call. Una **value-returning function** realiza precisamente esa comunicación: su `return type` indica qué tipo de value enviará y el statement `return` envía un value compatible.

La forma canónica es la siguiente. Es una forma para reconocer la sintaxis; todavía no es un programa completo.

```cpp
returnType functionName(type parameterName) {           // Defines a function that sends one value back
    return value;                                       // Returns a value compatible with returnType
}                                                        // Ends the function definition
```

| Pieza | Ejemplo | Propósito |
|---|---|---|
| Return type | `int` | Indica el type del value que regresará la function. |
| Function name | `calculateTestMinutes` | Describe la tarea que produce el resultado. |
| Parameters | `int deviceCount, int minutesPerDevice` | Reciben los data necesarios para calcular. |
| `return` statement | `return calculatedMinutes;` | Envía un value compatible al lugar de la call y termina esa function. |

No confundas `return` con `cout`. `cout` hace visible un value en pantalla; `return` entrega un value al programa. Después de ejecutar `return`, la function termina y el control vuelve a la línea que hizo la call.

**Para practicar por tu cuenta:** si una function calcula un promedio que puede tener parte decimal, ¿cuál return type sería más apropiado: `int` o `double`?

<details>
<summary>Ver respuesta</summary>

`double`, porque conserva la parte decimal del promedio.

</details>

---

## Parte 2 — Usar un return value numérico (30 min)

### 2.1 — Del problema a la function call

Retomemos la estación de pruebas. Con `3` dispositivos y `8` minutos por dispositivo, el reporte necesita conservar `24` minutos como un `int`. `main` coordina la interacción: recibe los dos inputs, llama la function y guarda el resultado. La function se concentra solo en el cálculo.

Antes de ver el programa, identifica el flujo:

| Lugar | Data que maneja | Responsabilidad |
|---|---|---|
| `main` | Cantidad de dispositivos, minutos por dispositivo y total final | Leer, hacer la call y mostrar el reporte. |
| `calculateTestMinutes` | Dos parameters y un cálculo local | Multiplicar y devolver el total. |

El prototype y el header deben usar el mismo return type. La call aparece a la derecha de una assignment porque se comporta como un value de ese type: cuando la function termina, `calculateTestMinutes(deviceCount, minutesPerDevice)` es reemplazada por el `int` que devolvió.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

int calculateTestMinutes(int deviceCount, int minutesPerDevice); // Declares a function that returns an int

int main() {                                             // Starts the program
    int deviceCount;                                     // Stores the number of devices to test
    int minutesPerDevice;                                // Stores the time needed for one device
    int totalMinutes;                                    // Stores the value returned by the function

    cout << "Enter number of devices: ";               // Prompts for the device count
    cin >> deviceCount;                                  // Reads the device count into main
    cout << "Enter minutes per device: ";              // Prompts for the time per device
    cin >> minutesPerDevice;                             // Reads the time per device into main

    totalMinutes = calculateTestMinutes(deviceCount, minutesPerDevice); // Stores the returned int
    cout << "Total test minutes: " << totalMinutes << endl; // Displays the saved result

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

int calculateTestMinutes(int deviceCount, int minutesPerDevice) { // Defines the calculation function
    int calculatedMinutes;                               // Stores a local calculation result

    calculatedMinutes = deviceCount * minutesPerDevice; // Calculates the total test time
    return calculatedMinutes;                            // Sends the local result back to main
}                                                        // Ends the calculation function
```

### 2.2 — Trace del `return` statement

Con inputs `3` y `8`, sigue la call sin saltar directamente al output:

| Paso | Lugar | Acción y value |
|---:|---|---|
| 1 | `main` | Guarda `3` en `deviceCount` y `8` en `minutesPerDevice`. |
| 2 | Call | Envía `3` y `8` como arguments a `calculateTestMinutes`. |
| 3 | Function | Sus parameters reciben esos values y calcula `calculatedMinutes = 24`. |
| 4 | `return` | Devuelve `24`; la function termina. |
| 5 | `main` | Guarda el returned value en `totalMinutes` y muestra `24`. |

El value devuelto también puede usarse directamente en `cout` o como parte de una expresión, siempre que el contexto espere el mismo type. Para mantener el trace legible en esta etapa, preferimos primero guardarlo en una variable con un nombre que explique el resultado.

> ⚠️ El return type, el prototype y el value de `return` deben ser compatibles. Si una function puede producir un decimal pero se declara como `int`, ocurre truncation al devolver el resultado.

**Para practicar por tu cuenta:** cambia los inputs a `4` y `15`. ¿Qué value se guarda en `totalMinutes`? Luego indica qué parte del programa dejaría de funcionar si se eliminara `return calculatedMinutes;`.

<details>
<summary>Ver respuesta</summary>

Se guarda `60`. Sin el `return`, `main` no recibiría el resultado de la function; una function declarada con return type `int` debe devolver un `int` en su ejecución normal.

</details>

---

## Parte 3 — Functions que responden una pregunta con `bool` (25 min)

Un return value no siempre representa una cantidad. A veces una function debe responder una pregunta cuya respuesta solo puede ser `true` o `false`. El type para ese resultado es `bool`.

**Problema:** antes de usar la estación de soldadura, una persona debe haber obtenido al menos `80` en el safety quiz y confirmar que lleva protective glasses. `main` recoge el score y la confirmación. Otra function debe decidir si ambas condiciones se cumplen. `main` mostrará el mensaje de acceso usando esa respuesta.

Primero formula la pregunta que la function debe responder: “¿puede esta persona usar la estación?”. Esa pregunta tiene dos resultados posibles, por lo que una `bool function` es más clara que dejar toda la condición dentro de `main`.

La forma canónica conserva la idea de return value, pero el return type y los possible returned values son `bool`:

```cpp
bool functionName(type parameterName) {                 // Defines a function that answers true or false
    return condition;                                   // Returns the result of a Boolean condition
}                                                        // Ends the Boolean function definition
```

Una function call que devuelve `bool` se puede colocar directamente dentro de `if`, porque `if` necesita precisamente una condition con resultado `true` o `false`. La function no decide qué mensaje mostrar; solo responde la pregunta. `main` conserva la responsabilidad de decidir qué hacer con esa respuesta.

```cpp
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

bool canUseSolderingStation(int safetyScore, char glassesConfirmed); // Declares a Boolean decision function

int main() {                                             // Starts the program
    int safetyScore;                                     // Stores the quiz score entered by the user
    char glassesConfirmed;                               // Stores the Y or N safety confirmation

    cout << "Enter safety quiz score: ";               // Prompts for the score
    cin >> safetyScore;                                  // Reads the score into main
    cout << "Are protective glasses confirmed? (Y/N): "; // Prompts for the safety confirmation
    cin >> glassesConfirmed;                             // Reads one confirmation character

    if (canUseSolderingStation(safetyScore, glassesConfirmed)) { // Uses the returned bool as the condition
        cout << "Station access approved." << endl;    // Runs when the function returns true
    } else {                                            // Handles a false return value
        cout << "Station access denied." << endl;      // Runs when the function returns false
    }                                                    // Ends the selection structure

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

bool canUseSolderingStation(int safetyScore, char glassesConfirmed) { // Defines the access decision
    return safetyScore >= 80 &&                          // Requires a passing safety score
           (glassesConfirmed == 'Y' || glassesConfirmed == 'y'); // Accepts either capital or lowercase Y
}                                                        // Ends the Boolean function definition
```

Haz el trace de estos test cases antes de ejecutarlos:

| `safetyScore` | `glassesConfirmed` | Return value esperado | Mensaje esperado |
|---:|:---:|:---:|---|
| `85` | `Y` | `true` | `Station access approved.` |
| `85` | `N` | `false` | `Station access denied.` |
| `75` | `y` | `false` | `Station access denied.` |

El `if` no recibe el score ni la letra directamente: recibe el `bool` producido por la function call. Esto permite leer `main` como una decisión de alto nivel y concentrar la regla de acceso en un solo lugar.

**Para practicar por tu cuenta:** ¿qué return value produce `canUseSolderingStation(80, 'y')`? ¿Por qué?

<details>
<summary>Ver respuesta</summary>

Devuelve `true`: `80` cumple `safetyScore >= 80` y `'y'` cumple la segunda parte de la condition.

</details>

---

## Parte 4 — Scope local: dónde existe cada variable (15 min)

El programa de la Parte 2 funciona porque `main` no intenta usar directamente las variables internas de `calculateTestMinutes`. Una variable tiene **scope** en la parte del programa donde puede usarse. Para esta sesión usaremos **local scope**: las variables declaradas dentro de una function y sus parameters pertenecen solo a esa function.

Vuelve al programa de minutos de prueba. Aunque `main` y `calculateTestMinutes` se comunican, no comparten todas sus variables:

| Nombre | Dónde se declara | Scope | ¿Puede `main` usarlo directamente? |
|---|---|---|---|
| `deviceCount` | Dentro de `main` | Solo `main` | Sí. |
| `deviceCount` parameter | Header de `calculateTestMinutes` | Solo esa function | No. Es un parameter local distinto. |
| `calculatedMinutes` | Dentro de `calculateTestMinutes` | Solo esa function mientras se ejecuta | No. |
| `totalMinutes` | Dentro de `main` | Solo `main` | Sí. Recibe el value devuelto. |

Los nombres repetidos no convierten esas variables en la misma variable. El `deviceCount` de `main` entrega un value al parameter de la function; el cálculo local se envía de vuelta únicamente mediante `return`. Cuando la function termina, sus parameters y variables locales dejan de existir; por eso `main` necesita guardar el returned value en su propia variable.

**Problema de diseño:** si `main` necesita un resultado calculado dentro de otra function, ¿debe intentar acceder a su local variable o debe recibir un return value? La segunda opción conserva los límites de cada function y hace explícito cómo viaja el data.

No usaremos global variables en estos programas. Una global variable parece hacer el data accesible desde cualquier function, pero oculta qué functions dependen de ella y hace más difícil seguir los cambios. Por ahora, comunica data mediante parameters y return values.

**Para practicar por tu cuenta:** en el programa de la Parte 2, ¿por qué esta línea no pertenece dentro de `main`?

```cpp
cout << calculatedMinutes << endl;                       // Cannot access the local variable from calculateTestMinutes
```

<details>
<summary>Ver respuesta</summary>

`calculatedMinutes` pertenece a `calculateTestMinutes`, no a `main`; está fuera de scope. `main` debe usar su propia variable `totalMinutes`, que recibe el value mediante `return`.

</details>

---

## Parte 5 — Adelanto: crear y leer un archivo de texto (15 min)

Hasta ahora, un programa recibe data con `cin` y muestra resultados con `cout`. Cuando el programa termina, ese data no permanece disponible para una ejecución posterior. Un **text file** permite guardar information fuera del programa para que luego pueda leerse de nuevo.

**Problema:** al terminar una inspección de seguridad, un laboratorio necesita guardar tres notas breves para dejar evidencia de la sesión. Primero crearemos el archivo y lo inspeccionaremos como un archivo de texto normal. Después de modificarlo manualmente, un segundo programa lo abrirá y mostrará cada nota, una línea a la vez. El objetivo de este adelanto no es diseñar un sistema de archivos completo: es observar por separado los pasos de crear, explorar, editar y leer.

Para trabajar con archivos, C++ provee la biblioteca `<fstream>`:

| Elemento | Propósito en este programa |
|---|---|
| `ofstream` | Abre un archivo para output; permite escribir en él. |
| `ifstream` | Abre un archivo existente para input; permite leerlo. |
| `getline` | Lee una línea completa, incluyendo espacios, y la guarda en un `string`. |
| `close` | Cierra el archivo cuando se termina de usar en ese modo. |

### 5.1 — Crear y explorar el archivo (8 min)

Guarda el primer programa como `create_inspection_log.cpp`. El programa crea y guarda `inspection_log.txt` en la carpeta desde la que se ejecuta. La primera línea del archivo será un header fijo. Luego hará tres preguntas específicas en la consola y construirá las siguientes tres líneas con labels predeterminados y los values que la persona entre.

```cpp
#include <fstream>                                       // Provides ofstream for file output
#include <iostream>                                      // Provides cout and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    ofstream outputFile("inspection_log.txt");          // Creates or opens the text file for writing
    string inspectorName;                                // Stores the inspector name entered by the user
    string inspectionDate;                               // Stores the inspection date entered by the user
    string equipmentId;                                  // Stores the equipment identifier entered by the user

    if (!outputFile) {                                   // Checks whether the file opened successfully
        cout << "Unable to create inspection log." << endl; // Reports an output-file error
        return 1;                                        // Ends the program with an error status
    }                                                    // Ends the output-file validation

    cout << "Enter inspector name: ";                   // Prompts for the inspector name
    getline(cin, inspectorName);                         // Reads the complete inspector name
    cout << "Enter inspection date: ";                  // Prompts for the inspection date
    getline(cin, inspectionDate);                        // Reads the complete inspection date
    cout << "Enter equipment ID: ";                     // Prompts for the equipment identifier
    getline(cin, equipmentId);                           // Reads the complete equipment identifier

    outputFile << "Inspection Log" << endl;             // Writes a fixed header as the first line
    outputFile << "Inspector: " << inspectorName << endl; // Writes the labeled inspector line
    outputFile << "Date: " << inspectionDate << endl;   // Writes the labeled date line
    outputFile << "Equipment ID: " << equipmentId << endl; // Writes the labeled equipment line
    outputFile.close();                                  // Closes the file after writing

    cout << "Inspection log created." << endl;          // Confirms that the output task finished
    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function
```

Después de ejecutarlo, abre `inspection_log.txt` desde el Explorer de VS Code. Verifica que contiene el header y las tres líneas construidas por el programa. Luego realiza estas dos ediciones manuales y guarda el archivo:

1. Cambia uno de los values que entró el programa; por ejemplo, cambia el value después de `Equipment ID:`.
2. Agrega al final una línea con `Approved by: ` seguida de tu nombre completo en inglés.

**Qué deberías ver:** el Explorer muestra `inspection_log.txt` junto al archivo `.cpp`. Al abrirlo, ves tus cambios y la línea final, por ejemplo `Approved by: Ada Lovelace`.

> ⚠️ Abrir un archivo con `ofstream` de esta manera lo crea si no existe, pero reemplaza su contenido si ya existe. Después de hacer las ediciones manuales, no ejecutes nuevamente el primer programa: borraría esos cambios.

### 5.2 — Leer el archivo modificado línea por línea (7 min)

Guarda el segundo programa como `read_inspection_log.cpp`. Ahora que el archivo ya existe y contiene las ediciones manuales, este segundo programa no escribe nada. Su única tarea es abrir `inspection_log.txt` para input y mostrar exactamente las líneas que encuentre. La condition del `while` lee una línea y continúa mientras `getline` pueda leer otra línea.

```cpp
#include <fstream>                                       // Provides ifstream for file input
#include <iostream>                                      // Provides cout and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    ifstream inputFile("inspection_log.txt");           // Opens the existing text file for reading
    string line;                                         // Stores one line read from the file

    if (!inputFile) {                                    // Checks whether the file opened successfully
        cout << "Unable to read inspection log." << endl; // Reports an input-file error
        return 1;                                        // Ends the program with an error status
    }                                                    // Ends the input-file validation

    cout << "Inspection log:" << endl;                  // Labels the lines that will be displayed
    while (getline(inputFile, line)) {                   // Reads and processes one line while one remains
        cout << line << endl;                            // Displays the line just read from the file
    }                                                    // Ends the line-by-line reading loop

    inputFile.close();                                   // Closes the file after reading
    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function
```

**Qué deberías ver:** la terminal muestra el header, las tres líneas con labels predeterminados y la edición que hiciste, además de la línea `Approved by: ` con tu nombre.

**Para practicar por tu cuenta:** agrega una sexta línea al archivo y predice cuántas veces se ejecutará el body del `while`.

<details>
<summary>Ver respuesta</summary>

Seis veces: `getline` produce una línea en cada iteración hasta llegar al final del archivo.

</details>

---

## Práctica guiada — Diseñar un cálculo y una decisión (10 min)

**Problema:** el equipo de robótica se prepara para una práctica en la que ensamblará varios robots idénticos. Antes de comenzar, la persona encargada del almacén debe decidir si hay suficientes connector kits para completar todos los robots planificados. Cada robot requiere la misma cantidad de connector kits; por ejemplo, si se ensamblarán `3` robots y cada uno requiere `2` kits, se necesitan `6` kits en total.

El programa recibe tres datos: el número de robots planificados, los connector kits requeridos por cada robot y los connector kits que ya están disponibles en el almacén. La primera function debe devolver el número total de kits requeridos. La segunda debe recibir esa cantidad y el inventario disponible, y devolver un `bool`: `true` si el inventario alcanza o `false` si faltan kits. Finalmente, `main` usa ese returned value en `if`/`else` para mostrar el mensaje apropiado: que se puede iniciar el ensamblaje o que faltan kits.

Trabaja en una plantilla vacía de C++ con `#include <iostream>`, `using namespace std` y `main`. Construye el programa en este orden:

1. Identifica qué data entra al programa y qué value numérico debe devolver la primera function.
2. En `main`, declara las tres variables de input y una cuarta variable para guardar el total de kits requeridos. Muestra prompts en inglés y usa `cin` para leer los tres inputs.
3. Escribe un prototype y una definition para una function que calcule los kits requeridos. En `main`, haz su function call y asigna el returned value a la variable que guarda el total.
4. Escribe un prototype y una definition para una `bool function` que reciba el total requerido y los kits disponibles. En `main`, coloca esa function call como la condition de un `if`/`else`; cada branch muestra en inglés el mensaje correspondiente.

Antes de ejecutar, predice estos resultados: con `3` robots, `2` kits por robot y `8` kits disponibles, el cálculo debe producir `6` y la decisión debe ser `true`. Con los mismos primeros dos inputs y `5` kits disponibles, la decisión debe ser `false`.

Al terminar, señala una variable local de cada function y explica por qué `main` no puede usarla directamente.

---

## Resumen de la sesión

- Una value-returning function envía un value compatible con su return type mediante `return`.
- El prototype y el header deben coincidir en return type, nombre y parameter types.
- `main` puede guardar un returned value, usarlo en una expresión o usar un `bool` returned value dentro de `if`.
- Una `bool function` responde una pregunta con `true` o `false`; `main` decide qué acción tomar con esa respuesta.
- Parameters y variables declaradas dentro de una function tienen local scope; return values y parameters hacen explícito cómo viaja el data.
- Un programa puede crear un text file con `ofstream`, cerrarlo y recorrerlo línea por línea con `ifstream` y `getline`.

## Próxima sesión

El próximo laboratorio del calendario profundizará **File I/O**. Las functions de esta semana siguen siendo herramientas disponibles para organizar programas posteriores.
