# Lab 5 — Selection Structures e Input/Output Acumulativo
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Semana 4 — Basic Programming Concepts and Elements; Semana 5 — Selection Structures; Gaddis, Capítulos 3 y 4
**Duración:** 110 min
**Requisitos:** Labs 1–3 completados; `cin`, `cout`, variables, operadores, `fixed`, `setprecision`, `if`/`else` y `switch` de las lectures de Semanas 4–5

---

## Objetivos

Al finalizar este laboratorio, el estudiante podrá:

1. Crear programas con prompts claros, `cin` y salida numérica con `fixed` y `setprecision`.
2. Usar `if`/`else` para tomar una decisión y proteger un programa de un valor fuera de rango.
3. Usar `switch`, `case`, `break` y `default` para procesar una opción de menú.
4. Diseñar y ejecutar `test cases` que cubran valores válidos, boundary values e inputs inválidos.
5. Aplicar conceptos de las Semanas 3 y 4 dentro de programas de selection structures.

---

## Parte 0 — Preparar la carpeta y el repositorio (5 min)

Desde esta semana ya debes reconocer el flujo de crear una carpeta de lab, abrirla en VS Code e inicializar un repositorio. Esta vez lo harás con menos instrucciones paso a paso.

> 🖱️ **Vas a usar VS Code.**

1. Dentro de tu carpeta padre de COEN 2210, crea una carpeta nueva llamada `lab5-selection`.
2. Ábrela como la carpeta raíz en VS Code con `File → Open Folder...`.
3. Abre Source Control con `Ctrl+Shift+G` (Windows) o `Cmd+Shift+G` (Mac) y selecciona **Initialize Repository**.

**¿Qué hace esto?** Crea un repositorio Git independiente para este lab. Igual que en los labs anteriores, el historial de Lab 5 queda separado de tus otros trabajos.

**Qué deberías ver:** el Explorer muestra `LAB5-SELECTION` como carpeta raíz y Source Control muestra un repositorio vacío, sin cambios todavía.

> ⚠️ No inicialices Git en la carpeta padre que contiene todos tus labs. Si lo haces, mezclarás los archivos e historiales de todo el curso en un solo repositorio.

---

## Parte 1 — Crear los archivos y actualizar el header (5 min)

> 🖱️ **Vas a usar VS Code.**

Crea estos dos archivos dentro de `lab5-selection`:

1. `rental_fee.cpp`
2. `equipment_checkout.cpp`

Copia este header al inicio de **cada** archivo y completa los campos entre corchetes. El campo `Description` debe describir ese archivo particular, no copiarse igual en ambos.

```cpp
/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Your Full Name]
 * Lab: 5 - Selection Structures
 * Description: [What this specific program does]
 * Due Date: [Date]
 */
```

**¿Qué hace esto?** El header identifica el propósito, autoría y fecha de cada archivo. Es una práctica básica de documentación profesional.

**Qué deberías ver:** ambos archivos aparecen en el Explorer y cada uno comienza con un header completo en inglés.

Ahora crea un archivo nuevo llamado `.gitignore` en la misma carpeta `lab5-selection`. Agrega estas líneas:

```gitignore
# Compiled programs
rental_fee
rental_fee.exe
equipment_checkout
equipment_checkout.exe
```

**¿Qué hace esto?** Le indica a Git que no debe incluir los programas compilados. En Mac, los ejecutables creados por este lab no tienen extensión; en Windows terminan en `.exe`. Este mismo archivo cubre ambos casos.

**Qué deberías ver:** `.gitignore` aparece en el Explorer. Después de compilar, Source Control debe mostrar los archivos `.cpp`, pero no los ejecutables creados por el compilador.

---

## Parte 2 — `rental_fee.cpp`: `cin`, formato e `if` (25 min)

Un laboratorio presta sensores por hora. Toda solicitud comienza con una tarifa base de `$5.00`. Si el préstamo dura más de 2 horas, se añade una tarifa adicional de `$1.50`. El programa debe pedir las horas y mostrar la tarifa final con dos decimales.

Este primer programa es un modelo completo del patrón que usarás luego: leer un valor, tomar una decisión y mostrar una salida formateada. Escríbelo dentro de `rental_fee.cpp`, debajo de tu header:

```cpp
#include <iostream>                             // Provides cin, cout, and endl
#include <iomanip>                              // Provides fixed and setprecision
using namespace std;                            // Allows standard-library names without the std:: prefix

int main() {                                    // Starts the program
    const double BASE_FEE = 5.00;               // Stores the fixed base rental fee
    const double EXTRA_FEE = 1.50;              // Stores the fee for a loan over two hours
    double hoursUsed;                           // Stores the number of hours entered by the user
    double totalFee = BASE_FEE;                 // Starts the total with the base fee

    cout << "Enter the number of hours used: "; // Prompts for the value that controls the decision
    cin >> hoursUsed;                           // Reads the number of hours from standard input

    if (hoursUsed > 2.0) {                      // Checks whether the extra-fee condition is true
        totalFee = totalFee + EXTRA_FEE;        // Adds the extra fee only when the condition is true
    }                                           // Ends the block controlled by the if statement

    cout << fixed << setprecision(2);           // Formats decimal output with exactly two digits
    cout << "Rental fee: $" << totalFee << endl; // Displays the final formatted fee

    return 0;                                   // Ends the program successfully
}                                               // Ends the main function
```

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila y ejecuta primero desde la carpeta `lab5-selection`.

**Windows:**

```powershell
g++ rental_fee.cpp -o rental_fee
.\rental_fee.exe
```

**Mac:**

```bash
clang++ rental_fee.cpp -o rental_fee
./rental_fee
```

**¿Qué hace esto?** El primer comando compila el archivo y crea un programa ejecutable. El segundo ejecuta ese programa. En Windows se usa `.\` y la extensión `.exe`; en Mac se usa `./`.

**Qué deberías ver:** con una entrada de `2`, la salida termina en `Rental fee: $5.00`; con una entrada de `2.5`, termina en `Rental fee: $6.50`.

Ahora cambia solamente la entrada y prueba estos `test cases`:

| `hoursUsed` | ¿Se añade `EXTRA_FEE`? | Salida esperada |
|---:|---|---|
| `2` | No | `Rental fee: $5.00` |
| `2.01` | Sí | `Rental fee: $6.50` |
| `5` | Sí | `Rental fee: $6.50` |

El valor `2` es un **boundary value**: está exactamente en el límite y permite confirmar que `>` no significa lo mismo que `>=`.

### Análisis requerido

Antes de correr los tres test cases, escribe al final de `rental_fee.cpp` un comentario de bloque en inglés con tus predicciones. Después de ejecutar el programa, completa o corrige tus respuestas. Debe responder estas tres preguntas:

1. ¿Por qué `hoursUsed = 2` no añade `EXTRA_FEE`?
2. ¿Qué resultado tendría `hoursUsed = 2` si la condition usara `>=` en lugar de `>`?
3. ¿Por qué `fixed` y `setprecision(2)` son apropiados para mostrar una cantidad de dinero?

Usa este formato y reemplaza cada respuesta entre corchetes:

```cpp
/*
 * Analysis:
 * 1. [Explain the result for hoursUsed = 2.]
 * 2. [Explain what would happen with >=.]
 * 3. [Explain why fixed and setprecision(2) are used for money.]
 */
```

**Esto es lo que debes entregar (obligatorio):** `rental_fee.cpp` con el header completado, el programa anterior funcionando, los tres `test cases` ejecutados y el bloque `Analysis` respondido en inglés.

**Para practicar por tu cuenta (opcional, no se entrega):** cambia temporalmente `hoursUsed > 2.0` a `hoursUsed >= 2.0`, ejecuta de nuevo el test case con `2`, y explica en un comentario inglés qué cambió. Después restaura la condición original.

---

## Parte 3 — `equipment_checkout.cpp`: diseñar validación con `if`/`else` (25 min)

Ahora construirás la primera parte de un programa de préstamo de equipo. Una solicitud solo es válida si la duración está entre **1 y 4 horas, inclusive**. Si no es válida, el programa debe mostrar un mensaje y no continuar al menú que crearás en la Parte 4.

Antes de escribir C++, analiza la regla paso por paso:

| Pregunta de diseño | Respuesta que debes obtener |
|---|---|
| ¿Una duración válida puede cumplir solo uno de los dos límites? | No; debe cumplir ambos límites. |
| ¿Cómo expresas “al menos 1 hora”? | Una `relational expression` con `>=`. |
| ¿Cómo expresas “como máximo 4 horas”? | Una `relational expression` con `<=`. |
| ¿Qué `logical operator` produce `true` solo si ambas comparaciones son verdaderas? | `&&`. |
| ¿Cómo evitas que se presente el menú con una duración inválida? | El menú debe existir únicamente dentro del camino válido de `if`/`else`. |

No necesitas usar `exit` ni terminar el programa antes de tiempo. Si el menú está dentro del block válido y el mensaje de error está en `else`, el programa naturalmente no llega al menú cuando la duración es inválida.

En `equipment_checkout.cpp`, conserva tu header y escribe solamente la entrada inicial siguiente. Construye tú mismo la estructura `if`/`else` debajo de `cin` a partir del análisis anterior.

```cpp
#include <iostream>                             // Provides cin, cout, and endl
using namespace std;                            // Allows standard-library names without the std:: prefix

int main() {                                    // Starts the program
    int loanHours;                               // Stores the requested loan duration

    cout << "Enter loan duration in hours: ";  // Prompts for the value that will be validated
    cin >> loanHours;                            // Reads the loan duration from standard input

    // TODO: Write an if/else structure that validates loanHours. // Uses both range limits from the design table
    // TODO: In the valid block, display "Loan duration accepted." // Reserves this path for the menu in Part 4
    // TODO: In the invalid block, display "Invalid loan duration." // Prevents the program from reaching the menu

    return 0;                                   // Ends the program successfully
}                                               // Ends the main function
```

Completa el mensaje del camino inválido. Debe ser exactamente `Invalid loan duration.` para que los test cases sean fáciles de comparar.

Compila y corre usando el mismo patrón de la Parte 2, cambiando solo el nombre del archivo y ejecutable:

**Windows:**

```powershell
g++ equipment_checkout.cpp -o equipment_checkout
.\equipment_checkout.exe
```

**Mac:**

```bash
clang++ equipment_checkout.cpp -o equipment_checkout
./equipment_checkout
```

**¿Qué hace esto?** Compila y ejecuta el segundo programa independiente de este lab.

**Qué deberías ver:** con `0` o `5`, el programa muestra `Invalid loan duration.`; con `1` o `4`, muestra `Loan duration accepted.`

**Esto es lo que debes entregar (obligatorio):** `equipment_checkout.cpp` con su header completado, el `if`/`else` funcional y los cuatro test cases `0`, `1`, `4` y `5` verificados.

**Para practicar por tu cuenta (opcional, no se entrega):** agrega un mensaje adicional para cada uno de los valores válidos: `Short loan.` si dura 1 o 2 horas, y `Extended loan.` si dura 3 o 4. Piensa primero si necesitas un nested `if` o una cadena `if`/`else if`.

---

## Parte 4 — `equipment_checkout.cpp`: menú, cálculo y `switch` (35 min)

Esta parte es una **continuación y mejora** del mismo programa `equipment_checkout.cpp` de la Parte 3; no crees otro archivo ni borres la validación que ya construiste. Una vez que la duración sea válida, el programa debe permitir escoger el equipo. Agrega el siguiente menú **dentro del block válido** del `if` de la Parte 3, en el lugar del `TODO`.

### Pasos para extender `equipment_checkout.cpp`

1. Continúa en el mismo archivo y conserva intacta la estructura `if`/`else` construida en la Parte 3.
2. Antes del `if` principal, agrega `#include <iomanip>` y declara/inicializa las variables para la opción del menú, la tarifa por hora, el total y el `bool flag` `isValidEquipmentChoice`.
3. Dentro del block válido del `if`, sustituye el `TODO` por el menú, su prompt, `cin` y el `switch`.
4. No coloques el menú dentro de `else`: una duración inválida debe mostrar su mensaje y terminar sin pedir una opción de equipo.
5. Después del `switch`, pero todavía dentro del block válido, usa `isValidEquipmentChoice` para decidir si se calcula y muestra el total formateado.

| Opción | Equipo | Tarifa por hora |
|---:|---|---:|
| `1` | Sensor kit | `$4.50` |
| `2` | Multimeter | `$6.00` |
| `3` | Power supply | `$8.25` |

Agrega primero, antes del `if`, las variables necesarias para guardar la opción, la tarifa por hora y el total. La opción debe ser `int`; ambas tarifas deben ser `double`. Declara también un `bool flag` llamado `isValidEquipmentChoice` e inicialízalo en `true`. También agrega `#include <iomanip>` al inicio porque mostrarás dinero con dos decimales.

Dentro del block válido, muestra un menú claro, lee la opción y usa un `switch`. Solo la primera opción y el primer `case` están resueltos como modelo. Completa las otras dos opciones de menú y los `case` necesarios usando la tabla anterior. Cada `case` válido necesita `break`; incluye `default` para una opción inválida.

```cpp
        cout << "Equipment menu\n";             // Introduces the available equipment choices
        cout << "1. Sensor kit\n";              // Displays the first menu option
        // TODO: Display menu option 2.          // Adds the multimeter option from the table
        // TODO: Display menu option 3.          // Adds the power-supply option from the table
        cout << "Enter equipment choice: ";     // Prompts for one menu selection
        cin >> equipmentChoice;                  // Reads the selected menu option

        switch (equipmentChoice) {                // Compares the selected option with each case
            case 1:                               // Handles the sensor-kit option
                hourlyRate = 4.50;                // Assigns the hourly rate for option 1
                cout << "Equipment selected: Sensor kit" << endl; // Displays the selected equipment
                break;                            // Leaves the switch after handling option 1
            // TODO: Add case 2 for the multimeter. // Assigns its hourly rate, displays its name, and uses break
            // TODO: Add case 3 for the power supply. // Assigns its hourly rate, displays its name, and uses break
            // TODO: Add default for an invalid choice. // Sets the flag to false and displays an English error message
        }                                        // Ends the switch statement
```

Después del `switch`, no debes calcular ni mostrar un total si la opción fue inválida. Usa `isValidEquipmentChoice` en una nueva `if statement`, todavía dentro del block válido de duración. En ese camino, calcula el total con esta fórmula antes de mostrarlo:

\[
\text{total fee} = \text{hourly rate} \times \text{loan hours}
\]

Muestra el resultado con el prompt `Total equipment fee: $` y con `fixed` junto a `setprecision(2)`. Este cálculo debe usar el operador aritmético `*`; no escribas manualmente un total para cada equipo.

⚠️ El `bool flag` debe estar disponible donde se usa. Si lo declaras dentro del `switch` o dentro de un `case`, no podrás consultarlo después. Decláralo antes del `if` principal, junto a `loanHours`, `equipmentChoice`, `hourlyRate` y `totalFee`.

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila y ejecuta `equipment_checkout.cpp` cada vez que completes un `case`; no esperes a terminar todo el programa para descubrir un error de sintaxis.

**¿Qué hace esto?** Compilar en incrementos pequeños permite aislar el cambio que introdujo un error y hace el debugging más rápido.

**Qué deberías ver:** el menú solo aparece para una duración válida. Para las opciones `1`, `2` o `3`, se muestra el nombre correcto y el total calculado con dos decimales. Para otra opción, se muestra `Invalid equipment choice.` y no se muestra un total.

Ejecuta y registra mentalmente estos `test cases` antes de continuar:

| Horas | Opción | Resultado esperado |
|---:|---:|---|
| `0` | — | `Invalid loan duration.`; no aparece el menú. |
| `1` | `1` | Muestra `Sensor kit` y `Total equipment fee: $4.50`. |
| `4` | `3` | Muestra `Power supply` y `Total equipment fee: $33.00`. |
| `2` | `9` | Muestra `Invalid equipment choice.`; no muestra total. |
| `5` | — | `Invalid loan duration.`; no aparece el menú. |

**Esto es lo que debes entregar (obligatorio):** `equipment_checkout.cpp` funcional con validación de 1–4 horas, menú de tres opciones, los tres `case` completos con `break`, `default`, `bool flag`, cálculo con `hourlyRate * loanHours`, total formateado únicamente para opciones válidas y los cinco test cases anteriores verificados.

**Para practicar por tu cuenta (opcional, no se entrega):** agrega una cuarta opción, `4. Calculator`, con una tarifa que tú decidas. Actualiza el menú, el `switch` y crea un test case para esa opción.

---

## Parte 5 — Revisar el trabajo y hacer commit/push (15 min)

Antes de entregar, revisa esta lista:

- Los dos archivos tienen un header completo y una `Description` distinta.
- Todos los prompts y mensajes que imprime C++ están en inglés.
- `rental_fee.cpp` muestra dinero con dos decimales.
- `equipment_checkout.cpp` no muestra el menú si las horas son inválidas.
- Cada `case` válido termina con `break`.
- Una opción inválida llega a `default` y no muestra tarifa.

> 🖱️ **Vas a usar el panel de Source Control de VS Code.**

1. Guarda ambos archivos.
2. En Source Control, verifica que solo aparecen `rental_fee.cpp` y `equipment_checkout.cpp` como cambios del lab.
3. Haz stage de ambos archivos con el botón `+`.
4. Escribe un mensaje como `Lab 5: selection structures and formatted output` y haz clic en **Commit**.
5. Selecciona **Publish Branch** si este es el primer push del repositorio, o **Sync Changes** si ya lo publicaste.

**¿Qué hace esto?** Stage prepara los archivos para el commit; el commit guarda una versión en el historial local; Publish Branch o Sync Changes sube ese historial a GitHub.

**Qué deberías ver:** Source Control deja de mostrar cambios pendientes y tu repositorio de GitHub contiene ambos archivos `.cpp` con sus headers y programas completos.

**Ejercicio adicional para practicar por tu cuenta (opcional, no se entrega):** elimina temporalmente un `break` de `case 1` y ejecuta el programa con opción `1`. Describe en un comentario en inglés qué mensajes aparecen y por qué. Después restaura el `break`.

---

## Próxima sesión

**Semana 6 — Repetition Structures.** Comenzaremos con `while` y `do while`. Las conditions, validación y selection structures de este lab seguirán siendo herramientas disponibles dentro de los próximos loops.
