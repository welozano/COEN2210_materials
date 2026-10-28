# Lab 11 — Arrays, Structs and Project Setup
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Semana 11 — Arrays, structs y matrices; Gaddis, Capítulos 7 y 11; CoRe Data Analyzer y Basic Integer Calculator

**Duración:** 110 min
**Requisitos:** Labs 1–3 y 5–9; functions, parameters, arrays, structs, loops, `switch`, input validation y formato de salida

---

## Objetivos

Al finalizar este laboratorio, el estudiante podrá:

1. Compilar varios archivos `.cpp` y explicar la función de los headers y del linker.
2. Representar una observation mediante un struct y almacenarla en un array de capacidad fija.
3. Diferenciar capacidad, cantidad registrada, índice, ID y disponibilidad de un slot.
4. Organizar la entrada y presentación de registros en archivos con responsabilidades distintas.
5. Mostrar solamente observations ocupadas y documentar pruebas del prototipo.

---

## Parte 0 — Preparar la carpeta y el repositorio (5 min)

Este lab tiene dos momentos: explorar la calculadora que sirve de referencia y construir el primer prototipo de CoRe Data Analyzer. Crea la carpeta `lab11-arrays-structs`, ábrela como carpeta raíz en VS Code e inicializa su repositorio desde Source Control. Dentro, crea estas subcarpetas:

```text
lab11-arrays-structs/
├── calculator/
├── dispatch_demo/
├── analyzer/
└── .gitignore
```

Copia en `calculator/` los cinco archivos `.cpp`/`.h` de [Basic Integer Calculator](../final_project/BasicCalculator/README.md). No inicialices repositorios adicionales dentro de las subcarpetas.

**¿Qué hace esto?** Conserva el ejemplo de referencia y tus programas separados, dentro del mismo historial de Lab 11.

**Qué deberías ver:** un solo repositorio, con los archivos de la calculadora dentro de `calculator/`.

En el `.gitignore` de la carpeta raíz agrega:

```gitignore
# Compiled programs for Windows and Mac
/calculator/BasicCalculator
/calculator/BasicCalculator.exe
/dispatch_demo/dispatch_demo
/dispatch_demo/dispatch_demo.exe
/analyzer/CoReDataAnalyzer
/analyzer/CoReDataAnalyzer.exe
*.o
*.obj
*.pdb
*.dSYM/
```

Cada archivo fuente que crees debe comenzar con el header estándar en inglés. Usa una `Description` que explique la responsabilidad de ese archivo; no repitas la misma descripción en todos los `.cpp` y `.h`. Conserva la calculadora como código de apoyo proporcionado.

```cpp
/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Your Full Name]
 * Lab: 11 - Arrays and Structs
 * Description: [What this specific file does]
 * Due Date: [Date]
 */
```

---

## Parte 1 — Calculadora: de varios archivos a un executable (20 min)

### 1.1 — Seguir una operación entre archivos

Hasta ahora, muchos ejemplos de clase reunían prototypes, `main` y function definitions en un solo archivo. La calculadora realiza las mismas tareas con otra organización: `main.cpp` coordina el menú, `mathOps.cpp` implementa operaciones y `utils.cpp` implementa funciones de apoyo. Al seleccionar Addition, la ejecución comienza en `main`, pasa por functions definidas en otros archivos y regresa al menú.

Antes de compilar, abre los cinco archivos e identifica ese recorrido:

| Archivo | Qué debes localizar |
|---|---|
| `main.cpp` | El loop, el `switch` y la function call a `computeAdd`. |
| `mathOps.h` | El prototype de `computeAdd`. |
| `mathOps.cpp` | La definition de `computeAdd` y sus function calls de apoyo. |
| `utils.h` | Los prototypes de `getValues`, `displayResult` y `pressAnyKey`. |
| `utils.cpp` | Sus definitions y el manejo de la pausa con Enter. |

Un **header** (`.h`) reúne declaraciones que otros archivos necesitan conocer. Un `.cpp` contiene las definitions que realizan el trabajo. `#include "mathOps.h"` hace visible el prototype en el archivo que lo incluye; no incorpora automáticamente la implementación de `mathOps.cpp` al executable.

El **linker** reúne el código compilado de los `.cpp` y conecta las function calls con sus definitions. Por eso debemos nombrar todos los archivos fuente que forman el programa al compilar.

Un `#include` hace que el preprocessor incorpore el contenido del header al archivo que se está compilando. Un mismo header puede llegar más de una vez: por ejemplo, `main.cpp` podría incluir `observation.h` directamente y también incluir `display.h`, que a su vez incluye `observation.h`. Sin protección, la definición del mismo struct aparecería dos veces en ese archivo y causaría un error de redefinición.

Los **include guards** evitan esa repetición. Observa este fragmento de `utils.h` de la calculadora; los prototypes quedan dentro de la protección:

```cpp
#ifndef UTILS_H // Continues only if this guard name has not been defined
#define UTILS_H // Records that this header has already been included

// Function declarations belong here. // Represents the protected header contents

#endif // Ends the conditional inclusion block
```

La primera vez que se incluye el header, `UTILS_H` todavía no está definido. `#ifndef` significa *if not defined*, por lo que el preprocessor entra al bloque; `#define` registra ese nombre y se incorpora el contenido que sigue. Si el header vuelve a incluirse durante la compilación del mismo `.cpp`, el nombre ya existe y se omite el bloque hasta `#endif`.

`UTILS_H` es un nombre de protección, no una variable de C++ ni una function. Cada header debe tener su propio nombre: por ejemplo, `MATHOPS_H` para `mathOps.h` y `OBSERVATION_H` para `observation.h`. Reutilizar el mismo nombre en headers distintos podría hacer que uno se omita por error.

La protección se aplica por cada `.cpp` que se compila junto con sus headers; a ese conjunto lo llamamos **unidad de compilación**. No impide que tanto `main.cpp` como `utils.cpp` conozcan las declaraciones de `utils.h`: cada uno las recibe durante su propia compilación. Tampoco sustituye al linker ni agrega las definitions de otros `.cpp` al executable. Conservaremos estos guards en los headers del analyzer y seguiremos incluyendo solo headers, no archivos `.cpp`.

### 1.2 — Compilar todos los archivos y ejecutar uno solo

> 💻 **Vas a usar la terminal integrada de VS Code.** Abre una terminal en la subcarpeta `calculator/`. Los siguientes comandos asumen que los cinco archivos de la calculadora están en esa carpeta.

**Windows — compilar:**

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp utils.cpp mathOps.cpp -o BasicCalculator.exe
```

**Mac — compilar:**

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp utils.cpp mathOps.cpp -o BasicCalculator
```

**¿Qué hace esto?** Compila los tres `.cpp` y los enlaza en un executable. Los `.h` se incorporan mediante `#include`; no se agregan como programas separados al comando.

Para entender el comando, separa el nombre del compilador, las opciones, los archivos de entrada y el archivo de salida. Las opciones también se llaman **flags**: modifican cómo se construye o revisa el programa.

| Parte del comando | Qué hace | Por qué se usa aquí |
|---|---|---|
| `g++` / `clang++` | Invoca el compilador de C++ y coordina la compilación y el linking. | Usamos el compilador instalado en Windows o Mac durante el curso. |
| `-std=c++17` | Selecciona la versión C++17 del lenguaje. | Hace explícito el estándar esperado, en lugar de depender del predeterminado del compilador. No significa que todas las instrucciones del programa sean características nuevas de C++17. |
| `-Wall` | Activa un grupo amplio de warnings comunes, por ejemplo sobre variables locales no utilizadas. | Ayuda a detectar código sospechoso. A pesar de su nombre, no activa todos los warnings posibles. |
| `-Wextra` | Añade otros warnings que no están incluidos en `-Wall`. | Complementa la revisión, por ejemplo al advertir sobre ciertos parameters no utilizados. |
| `-pedantic` | Solicita diagnósticos por ciertos usos que no cumplen el estándar seleccionado, incluidos usos de extensiones del compilador. | Ayuda a identificar dependencias de extensiones; no garantiza por sí solo portabilidad ni ausencia de errores. |
| `main.cpp utils.cpp mathOps.cpp` | Indica los archivos fuente que se compilarán y enlazarán. | Cada uno contiene parte de la implementación de esta calculadora. |
| `-o` | Indica que lo siguiente es el nombre del archivo de salida. | Permite elegir cómo se llamará el executable. Es una letra `o` minúscula, no el número cero. |
| `BasicCalculator.exe` / `BasicCalculator` | Es el nombre del executable resultante. | Ese es el archivo que ejecutarás después; no es otro archivo fuente. |

Un **error** de compilación o linking impide completar la construcción del programa. Un **warning** señala algo que debe revisarse, aunque en muchos casos todavía se genere el executable. La meta del lab es compilar sin errores ni warnings; tampoco debe suponerse que eso garantiza resultados correctos: todavía hay que ejecutar test cases.

**¿Por qué se repiten los flags en los demás ejercicios?** `-std=c++17`, `-Wall`, `-Wextra` y `-pedantic` seleccionan reglas del lenguaje y diagnósticos, independientemente de cuántos `.cpp` tenga el programa. Por eso son útiles también para `dispatch_demo.cpp`, que contiene toda su implementación en un archivo. No son opciones especiales de múltiples archivos. La diferencia de la calculadora es que el comando nombra tres `.cpp`; el analyzer nombrará dos. `-o` se usa en los tres casos para elegir el executable correspondiente.

Referencias de las opciones: [GCC — Warning Options](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html) y [GCC — Overall Options](https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html).

**Qué deberías ver:** el comando termina sin errores y aparece un executable, ignorado por Git. No aparece un programa distinto por cada `.cpp`.

**Windows — ejecutar:**

```powershell
.\BasicCalculator.exe
```

**Mac — ejecutar:**

```bash
./BasicCalculator
```

**¿Qué hace esto?** Inicia el executable que comienza en `main` y permite navegar por las opciones.

**Qué deberías ver:** el menú de la calculadora. Prueba Addition con `8` y `5`, luego Division con `7` y `0`, y termina con la opción `5`.

Si se compilara únicamente `main.cpp`, el compiler podría reconocer los prototypes de los headers, pero el linker no encontraría las definitions que quedaron en los otros `.cpp`. Compilar no significa ejecutar cada archivo por separado: se construye un solo programa y luego se ejecuta ese programa.

### 1.3 — Explicar lo observado

Crea un archivo de texto plano llamado `calculator/analysis.txt` y responde en inglés. Escribe el número de cada pregunta seguido de tu respuesta; no necesitas ningún formato especial.

1. Which files contain the declaration and definition of `computeAdd`?
2. After selecting Addition, which function calls read the operands, perform the operation, display the result, and pause?
3. Why must the build command include three `.cpp` files instead of only `main.cpp`?
4. What does the include guard in `utils.h` prevent?
5. What do `-std=c++17`, `-Wall`, `-Wextra`, `-pedantic`, and `-o` control? Which part of the command changes when the program has only one `.cpp` file?

**Esto es lo que debes entregar (obligatorio):** los cinco archivos proporcionados en `calculator/` y `analysis.txt` con tus respuestas. No entregues el executable.

**Para practicar por tu cuenta (opcional, no se entrega):** sigue el camino de Subtraction y compara qué functions se reutilizan respecto a Addition.

---

## Parte 2 — `dispatch_demo.cpp`: ejemplo integrado y progresivo (15 min)

Antes del analyzer, veremos un programa corto resuelto con un contexto distinto al de la lecture. Un almacén prepara una hoja de despacho: la persona entra el destino de un envío y cuántas cajas contiene. Esos datos pertenecen a un solo despacho y deben presentarse juntos. `main` recibirá el registro; otra function mostrará su resumen.

Este ejemplo no es una entrega del proyecto: es una guía para practicar la relación entre tipo, variable, prototype, function call y definition. Guarda el programa en `dispatch_demo/dispatch_demo.cpp`, debajo de tu header.

### Paso 1 — Recibir un registro

Escribe todo el programa siguiente, dejando los tres bloques `Step 2` comentados. Cada bloque comienza con una línea `/* Step 2 ...` y termina con `*/`. La primera versión compila, recibe los datos y confirma el destino; todavía no llama la function que presenta el resumen.

```cpp
#include <iostream> // Provides console input and output
#include <string> // Provides string and getline
using namespace std;

struct DispatchRecord {
    string destination; // Stores the shipment destination
    int boxCount = 0; // Initializes the number of boxes
};

/* Step 2: Activate this prototype.
void displayDispatch(DispatchRecord record); // Declares a function that receives one record
*/

int main() {
    DispatchRecord shipment = {}; // Creates one initialized record
    cout << "Enter shipment destination: ";
    getline(cin, shipment.destination); // Reads a destination that may include spaces
    cout << "Enter number of boxes: ";
    cin >> shipment.boxCount;
    while (shipment.boxCount < 1) {
        cout << "Enter a positive number of boxes: ";
        cin >> shipment.boxCount; // Validates the count before displaying the record
    }
    cout << "Destination recorded: " << shipment.destination << endl;

    /* Step 2: Activate the function call.
    displayDispatch(shipment); // Sends a copy of the complete record to the function
    */

    return 0;
}

/* Step 2: Activate this function definition.
void displayDispatch(DispatchRecord record) {
    cout << "Dispatch summary" << endl;
    cout << "Destination: " << record.destination << endl;
    cout << "Boxes: " << record.boxCount << endl; // Displays a member from the local record copy
}
*/
```

### Paso 2 — Activar y analizar la function call

Quita la línea de apertura y la de cierre de cada uno de los tres block comments marcados `Step 2`; conserva los inline comments `//`. Así quedan activos el prototype, la function call y la definition. Compila de nuevo y verifica que se muestra el resumen completo.

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila desde `dispatch_demo/`, primero con los bloques comentados y después con los tres bloques activos.

**Windows — compilar:**

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic dispatch_demo.cpp -o dispatch_demo.exe
```

**Mac — compilar:**

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic dispatch_demo.cpp -o dispatch_demo
```

**¿Qué hace esto?** Construye un programa cuyas definitions están todas en un `.cpp` y permite comparar su organización con la calculadora. Conserva los flags explicados en 1.2 para seleccionar el mismo estándar y los mismos grupos de diagnósticos; solo necesita un archivo fuente.

**Qué deberías ver:** la compilación termina sin errores ni warnings en ambos pasos; no necesita varios `.cpp` porque toda su implementación está en un solo archivo.

**Windows — ejecutar:**

```powershell
.\dispatch_demo.exe
```

**Mac — ejecutar:**

```bash
./dispatch_demo
```

**¿Qué hace esto?** Ejecuta la versión que acabas de compilar para observar el efecto de activar la function call.

**Qué deberías ver:** en el Paso 1 se confirma el destino. En el Paso 2, con destino `North service desk` y `4` cajas, aparece además el resumen con ese destino y `Boxes: 4`.

Después de la última llave del archivo, agrega y responde en inglés:

```cpp
/*
 * Analysis:
 * 1. What is the difference between DispatchRecord and shipment?
 * 2. Which members are copied when displayDispatch(shipment) is called?
 * 3. Why would changing record.boxCount inside the function leave shipment.boxCount unchanged?
 */
```

**Esto es lo que debes entregar (obligatorio):** `dispatch_demo.cpp` con los bloques activados y `Analysis` respondido.

**Para practicar por tu cuenta (opcional, no se entrega):** cambia el destino y la cantidad de cajas y comprueba que no fue necesario modificar la definition de la function.

---

## Parte 3 — Analyzer: preparar los headers del programa (20 min)

### 3.1 — Qué construiremos hoy

Hasta aquí compilaste la calculadora y analizaste un ejemplo de un solo registro. Ahora comenzarás **otro programa**, CoRe Data Analyzer, dentro de la subcarpeta `analyzer/` creada en la Parte 0. Las Partes 3 y 4 trabajan sobre ese mismo programa: primero prepararás los headers y después implementarás la entrada de datos, el menú y la presentación.

CoRe Data Analyzer debe administrar resultados electorales por county. Antes de cargar el CSV o buscar por ID, necesitamos definir qué datos forman una observation. En esta parte escribirás su definición en `observation.h` y declararás una function de presentación en `display.h`. En la Parte 4 crearás el array que almacena las observations y completarás las definitions que permiten ejecutar el programa.

En este primer prototipo, entrarás entre una y tres observations manualmente al iniciar el programa. El array mantendrá la capacidad de **100** exigida por el proyecto. Después, un menú permitirá mostrar el dataset actual o terminar. La entrada inicial es un mecanismo temporal de prueba, no la implementación completa de Add: no incluye aún búsqueda de IDs duplicados. Utiliza IDs diferentes en las pruebas de hoy.

Load/Save del CSV, Add completo, Delete, búsquedas y estadísticas se incorporarán en etapas posteriores. El prototipo de hoy sí puede conservarse como punto de partida del proyecto.

### 3.2 — Separar responsabilidades antes de escribir código

Crea estos cuatro archivos directamente dentro de `lab11-arrays-structs/analyzer/`, todos al mismo nivel. No los guardes en `calculator/` ni en `dispatch_demo/`. Completarás los dos `.h` en esta parte; los dos `.cpp` se desarrollan en la Parte 4.

| Archivo | Responsabilidad |
|---|---|
| `observation.h` | Define el tipo `Observation` y sus campos. |
| `display.h` | Declara la function que muestra una observation. |
| `display.cpp` | Define esa function y su formato de salida. |
| `main.cpp` | Conserva el array, recibe los datos iniciales y coordina el menú. |

**¿Qué hace esto?** Establece la organización del nuevo programa: los headers describen el tipo de registro y la function disponible; los `.cpp` contendrán las acciones que se ejecutan.

**Qué deberías ver:** los cuatro archivos bajo `analyzer/` en el Explorer de VS Code. Agrega a cada uno su header personal antes de comenzar su contenido.

Una **dependencia** significa aquí que un archivo necesita conocer una declaración de otro. `display.h` necesita conocer `Observation` para usarlo como parameter; por eso incluye `observation.h`. `main.cpp` y `display.cpp` incluirán `display.h`. Los include guards evitan repetir la definición del struct cuando un header llega por más de un camino.

Antes de programar, responde estas preguntas de diseño:

| Pregunta | Decisión que debes justificar |
|---|---|
| ¿Qué datos pertenecen a una observation? | Separa los siete campos del CSV del estado interno de disponibilidad. |
| ¿Cuántos registros pueden existir físicamente? | Distingue la capacidad de 100 de los datos que entrarás hoy. |
| ¿Qué significa `isEmpty == true`? | Decide si el slot se muestra o se ignora. |
| ¿El ID es el índice? | Un ID como 151 debe caber como dato en un registro, sin seleccionar la posición 151. |

### 3.3 — Completar `observation.h`

Abre **`analyzer/observation.h`**. Este archivo definirá el struct `Observation`: la forma de un registro electoral. No recibe datos, no contiene `main` y todavía no crea el array. Su definición permitirá que los otros archivos declaren variables de ese tipo y accedan a los mismos campos.

Usa estos nombres para mantener consistencia entre archivos. ID y vote counts son `int`; state y county son `string`; democratic share es `double`; disponibilidad es `bool`. Los nombres de campos en C++ pueden diferir de los labels del CSV, pero deben conservar su significado.

| Campo C++ | Significado |
|---|---|
| `id` | Identificador de la observation. |
| `state` | Abreviación del estado. |
| `county` | Nombre completo del county. |
| `totalVotes` | Total votes. |
| `democraticVotes` | Democratic votes. |
| `republicanVotes` | Republican votes. |
| `democraticShare` | Democratic share, entre 0 y 100. |
| `isEmpty` | Flag interno; no es un campo del CSV. |

Copia el siguiente starter **dentro de `analyzer/observation.h`, debajo de tu header personal**. El bloque corresponde al contenido de ese archivo, no a un programa independiente. El primer campo numérico y el flag están resueltos; reemplaza los TODOs con las declaraciones de los members que faltan, usando la tabla anterior. Inicializa los campos numéricos en cero; los `string` comienzan vacíos.

```cpp
#ifndef OBSERVATION_H
#define OBSERVATION_H

#include <string> // Provides the string fields used by each observation

struct Observation {
    int id = 0; // Initializes the identifier before data is entered

    // TODO: Declare the state and county string members.

    // TODO: Declare the remaining vote-count and share members with initial values.

    bool isEmpty = true; // Marks each newly created slot as available
};

#endif
```

Al terminar, guarda `observation.h`. Los include guards protegen la definición del tipo cuando otros archivos la incluyen. El struct completo debe contener los siete campos electorales y el flag de disponibilidad; no agregues aquí prompts ni loops.

### 3.4 — Declarar la presentación en `display.h`

Ahora abre **`analyzer/display.h`** y coloca el bloque siguiente debajo de su header personal. Este es otro archivo: conserva el código anterior en `observation.h`.

Aquí anunciaremos una function que recibe una observation y muestra sus campos. Para declarar ese parameter, el compiler debe conocer el tipo `Observation`; por eso este header incluye `observation.h`. El prototype deja visible el nombre y el tipo del parameter, pero no contiene todavía las instrucciones de salida. Su definition se escribirá en `display.cpp` durante la Parte 4.

```cpp
#ifndef DISPLAY_H
#define DISPLAY_H

#include "observation.h" // Makes Observation available as a parameter type

void displayObservation(Observation observation); // Declares output for one record passed by value

#endif
```

Guarda `display.h`. **Al finalizar esta parte debes tener los dos headers completos; todavía no hay un executable del analyzer.** Los headers no se ejecutan por sí solos y aún faltan `main` y la definition de `displayObservation`. Compilarás el programa completo después de desarrollarlos en la Parte 4.

En esa próxima parte escribirás `analyzer/main.cpp`. Allí declararás un array de `Observation` con capacidad de 100 e initialization con `{}`. El struct define la forma de cada elemento; el array reserva la colección de registros. No declares 100 variables independientes ni uses un array distinto por cada campo.

**Esto es lo que debes entregar (obligatorio):** `observation.h` completo y `display.h`, con sus headers personales y sus include guards. La declaración del array quedará en `main.cpp` en la Parte 4.

**Para practicar por tu cuenta (opcional, no se entrega):** explica qué cambiaría en los flags iniciales si se eliminara el default member initializer de `isEmpty` y se mantuviera `{}` al crear el array.

---

## Parte 4 — Analyzer: recibir registros y construir Display Data Frame (30 min)

Esta parte **continúa el mismo prototipo** de la Parte 3, dentro de `lab11-arrays-structs/analyzer/`. Los headers `observation.h` y `display.h` ya deben estar completos y guardados. Ahora escribirás el contenido de los dos `.cpp` que creaste: primero `main.cpp`, que coordina el programa, y después `display.cpp`, que muestra cada registro.

Conserva los cuatro archivos separados y al mismo nivel. Cada bloque de código siguiente corresponde a uno de esos archivos; no unas ambos bloques en un solo `.cpp`. El comando de 4.3 los compilará y enlazará como un único programa.

La persona que revisa el dataset necesita ver una tabla con una fila por observation, sin 97 o 99 filas inicializadas que todavía no contienen datos reales. La disponibilidad de cada slot determina si participa en la salida. El menú debe poder mostrar la misma colección varias veces sin volver a pedir los campos ni modificarla.

### 4.1 — Completar `analyzer/main.cpp`: entrada, colección y menú

Abre **`analyzer/main.cpp`**. En este archivo vivirá el array durante la ejecución. Su function `main` pedirá los datos iniciales y después repetirá el menú, utilizando los headers de la Parte 3 para conocer el tipo `Observation` y el prototype de `displayObservation`.

Construye la solución en este orden:

1. Declara dentro de `main` el array `observations`, con capacidad `CAPACITY` e initialization `{}`.
2. Pide `requestedObservations` entre 1 y 3. Este límite hace corta la prueba manual; no cambia la capacidad de 100 del proyecto.
3. Usa un loop para llenar las posiciones consecutivas necesarias. Para cada observation pide los siete campos de la tabla anterior. El ID lo entra la persona; no lo generes a partir del índice.
4. Lee county como una línea completa. Valida vote counts no negativos y democratic share entre 0 y 100. Mantén state y county con texto. Reutiliza las técnicas de input validation ya trabajadas para recuperarte si una extraction numérica falla.
5. Marca un registro ocupado solo después de completar sus datos. No cambies los flags de las posiciones que no llenaste.
6. Al terminar la entrada inicial, muestra un menú con `1. Display Data Frame` y `11. Exit application`. Es un menú parcial del proyecto: se conserva la numeración original de esas dos opciones.
7. En la opción 1, recorre la capacidad y selecciona únicamente los slots ocupados. Muestra una cabecera de tabla una vez; por cada registro activo, llama la function declarada en `display.h`. Cuenta las filas mostradas y reporta esa cantidad. Si no hay filas, informa que el dataset está vacío.
8. La opción 11 termina el loop; otra opción informa que no es válida y vuelve a mostrar el menú.

Copia el siguiente starter **en `analyzer/main.cpp`, debajo de tu header personal**. Contiene la estructura completa de `main`, incluido `return 0;` y su llave final. El loop del menú está resuelto porque ya se practicó en labs anteriores; completa los TODOs para construir el almacenamiento, la entrada y el recorrido de presentación. Sustituye cada TODO por el código correspondiente a ese lugar.

```cpp
#include <iostream> // Provides console input and output
#include <iomanip> // Provides table formatting
#include <limits> // Supports discarding invalid numeric input
#include "observation.h" // Provides the record type and initial member values
#include "display.h" // Provides the single-observation display prototype
using namespace std;

int main() {
    const int CAPACITY = 100; // Preserves the capacity required by the final project
    int requestedObservations = 0;
    int menuChoice = 0;

    // TODO: Declare and initialize the observations array using CAPACITY.

    // TODO: Prompt for and validate a requested observation count from 1 to 3.

    // TODO: Use a loop to read complete observations and mark only those slots as occupied.

    do { // Repeats the prototype menu without repeating the initial data entry
        cout << "\nCoRe Data Analyzer - Lab 11 prototype\n";
        cout << "1. Display Data Frame\n11. Exit application\n";
        cout << "Enter option number: ";

        // TODO: Read menuChoice and recover from a failed numeric extraction.

        switch (menuChoice) {
            case 1: {
                // TODO: Print column headings, then traverse occupied slots and display their records.

                // TODO: Report the number of displayed observations or an empty-dataset message.

                break;
            }
            case 11:
                cout << "Session ended." << endl; // Confirms the selected exit action
                break;
            default:
                cout << "Invalid option." << endl; // Handles a numeric option outside the prototype menu
                break;
        }
    } while (menuChoice != 11);

    return 0;
}
```

### 4.2 — Completar la presentación de un registro en `display.cpp`

Guarda `main.cpp` y abre **`analyzer/display.cpp`**. Este segundo archivo contendrá la definition de `displayObservation`, cuyo prototype escribiste en `display.h`. Copia el bloque siguiente debajo de su header personal y completa el TODO dentro de la function. No agregues otra function `main`: el punto de entrada del programa ya está en `main.cpp`.

La function recibe **una observation**, no el array completo. El recorrido de `main` selecciona qué registro enviar; la function se limita a mostrar una fila. Ese reparto evita introducir hoy nuevos parameters de array y permite reutilizar el mismo formato para cada registro.

Completa el body para mostrar los siete campos del registro en el orden de la tabla. Usa `left`, `setw`, `fixed` y `setprecision(2)`. Los anchos se aplican a cada campo por separado; el ancho de county debe permitir al menos 22 caracteres.

```cpp
#include <iostream> // Provides cout and endl
#include <iomanip> // Provides aligned fields and decimal formatting
#include "display.h" // Checks the definition against its declared prototype
using namespace std;

void displayObservation(Observation observation) {
    // TODO: Display one aligned row containing the seven data fields; omit the availability flag.

    cout << endl; // Ends the row after all its fields have been displayed
}
```

La cabecera de columnas se imprime una sola vez en `main`, antes del recorrido. El contenido de cada fila se imprime en `display.cpp` mediante los members del parameter `observation`. Usa los mismos anchos de columna en ambos archivos para alinear labels y valores.

Al seleccionar Display, no muestres `isEmpty` como una columna de los datos electorales: el flag controla el recorrido, pero no pertenece al report. Si hay tres observations ocupadas, debe haber tres function calls, aunque el array tenga cien posiciones.

### 4.3 — Compilar el prototipo completo

Guarda los cuatro archivos de `analyzer/` y verifica que completaste los members de `observation.h`, los TODOs de `main.cpp` y el body de `displayObservation` en `display.cpp`. Esta es la primera compilación del conjunto completo. Compilar solo un `.cpp` no reúne toda su implementación.

> 💻 **Vas a usar la terminal integrada de VS Code.** Ejecuta los comandos siguientes desde `analyzer/`, donde están sus cuatro archivos.

**Windows — compilar:**

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp display.cpp -o CoReDataAnalyzer.exe
```

**Mac — compilar:**

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp display.cpp -o CoReDataAnalyzer
```

**¿Qué hace esto?** Reúne `main.cpp` y `display.cpp` en el mismo executable. Los dos headers se procesan desde sus `#include`.

**Qué deberías ver:** la compilación termina sin errores ni warnings después de completar los TODOs. Si faltan campos o la definition de la function, corrige el archivo responsable antes de ejecutar.

**Windows — ejecutar:**

```powershell
.\CoReDataAnalyzer.exe
```

**Mac — ejecutar:**

```bash
./CoReDataAnalyzer
```

**¿Qué hace esto?** Inicia la entrada de los registros de prueba y luego el menú del prototipo.

**Qué deberías ver:** al seleccionar 1 aparecen solamente las observations entradas. Mostrar la tabla dos veces conserva los mismos datos. La opción 11 termina el programa.

**Esto es lo que debes entregar (obligatorio):** los cuatro archivos completos de `analyzer/`, con entrada validada, array de capacidad 100, flags correctos, menú parcial, function de presentación y output alineado.

**Para practicar por tu cuenta (opcional, no se entrega):** después de llenar el array y antes del menú, marca temporalmente vacío uno de los slots registrados. Comprueba que Display lo omite y que su ID no cambia en los registros restantes; retira esa modificación de prueba antes de entregar. Esto no implementa Delete, solo comprueba el uso del flag.

---

## Parte 5 — Test cases y análisis del prototipo (15 min)

Usa estos dos registros del dataset proporcionado como datos de entrada manual. No abras ni sobrescribas el CSV desde este prototipo.

| ID | State | County | Total votes | Dem votes | Rep votes | Dem share |
|---:|---|---|---:|---:|---:|---:|
| 151 | FL | Gadsden County | 22510 | 15582 | 6811 | 69.58 |
| 46 | PA | Montour County | 8023 | 3364 | 4574 | 42.38 |

Al pedir dos observations, estas se guardan en índices `0` y `1`, independientemente de sus IDs. Display debe mostrar dos filas y `Observations displayed: 2`; no debe intentar acceder a los índices 151 o 46 para localizarlas.

Registra las pruebas en el archivo de texto plano `analyzer/test_cases.txt`. Para cada prueba, escribe sus inputs, el resultado esperado y el resultado observado, en líneas separadas. No necesitas crear una tabla ni usar formato Markdown.

| Prueba | Resultado esperado |
|---|---|
| Count solicitado `0` y luego `2` | Rechaza cero y permite entrar los dos registros. |
| Display después de entrar los registros de la tabla | Dos filas alineadas, IDs preservados y share con dos decimales. |
| Display una segunda vez | Misma tabla y misma cantidad; no vuelve a solicitar los campos. |
| Un vote count negativo antes del válido | Solicita nuevamente ese campo. |
| Share `101` antes del valor válido | Rechaza el porcentaje fuera de rango. |
| Texto en un prompt numérico, luego un número válido | Recupera el input stream y continúa sin quedar en un loop de errores. |
| Opción de menú `9` | Informa opción inválida en este prototipo parcial y conserva los registros. |
| Opción `11` | Termina el programa. |

El menú parcial solo ofrece 1 y 11; no tiene todavía todas las opciones del enunciado final. En una ejecución adicional, prueba un solo registro y verifica que se muestra una fila, no cien.

Al final de `analyzer/main.cpp`, después de su última llave, agrega y responde en inglés:

```cpp
/*
 * Analysis:
 * 1. Why can observation ID 151 be stored at array index 0?
 * 2. What initializes unused slots as empty, and when does a slot become occupied?
 * 3. Why does Display examine the capacity but print only occupied observations?
 * 4. What record is passed to displayObservation on each function call, and is it a copy?
 * 5. Why does the build command include main.cpp and display.cpp but not the headers?
 */
```

**Esto es lo que debes entregar (obligatorio):** `test_cases.txt` y el bloque `Analysis` respondido en `main.cpp`, además del programa completo.

**Para practicar por tu cuenta (opcional, no se entrega):** dibuja el array de 100 slots y marca cuáles están ocupados después de cada prueba. Relaciona el dibujo con la cantidad de filas mostradas.

---

## Parte 6 — Cierre y commit/push (5 min)

Antes de entregar, verifica que:

- Los programas de las tres subcarpetas se compilan desde su propia carpeta, con los `.cpp` correspondientes.
- La calculadora conserva sus archivos proporcionados; tus respuestas están en `calculator/analysis.txt`.
- El ejemplo resuelto tiene los bloques activados y sus respuestas al final.
- El analyzer guarda registros en un array de structs y no confunde ID con índice.
- Los slots no utilizados comienzan vacíos; Display no los muestra.
- Los headers, prompts, identifiers y comments de los programas están en inglés.
- Incluiste el análisis y las pruebas, pero no los ejecutables.

Haz stage de `.gitignore`, las fuentes y los documentos de análisis/pruebas; crea un commit como `Lab 11: arrays structs and analyzer display` y publica/sincroniza el repositorio.

**¿Qué hace esto?** Guarda un punto de partida verificable para continuar CoRe Data Analyzer en las próximas sesiones.

**Qué deberías ver:** el remoto contiene las tres subcarpetas con fuentes y documentación; no contiene executables ni cambios pendientes de tu entrega.

## Próxima sesión

Semana 12 desarrollará search y sorting, y su aplicación a mean, median y mode. Este prototipo conserva la representación de datos y el display que necesitaremos para integrar las siguientes operaciones del proyecto.
