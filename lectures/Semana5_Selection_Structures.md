# Semana 5 — Selection Structures
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Gaddis, *Starting Out with C++: From Control Structures through Objects* — Capítulo 4, "Making Decisions" (secciones 4.1–4.11 y 4.14)

**Duración:** 170 min (lectura)
**Precede a:** Lab 5 — `if`/`else` y `switch`, integrando `cin`, operadores y formato de salida de Semana 4

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:

1. Construir y evaluar `relational expressions` que produzcan valores `bool`.
2. Usar `if`, `if`/`else` e `if`/`else if` para controlar qué instrucciones ejecuta un programa.
3. Combinar condiciones con los `logical operators` `&&`, `||` y `!`.
4. Validar rangos sencillos de entrada antes de usar un dato en un cálculo.
5. Usar `switch` con `case`, `break` y `default` cuando una sola expresión se compara con opciones discretas.
6. Seleccionar entre `if`/`else if` y `switch` según el problema.

---

## Cómo probar los code snippets durante la lecture

Los bloques de esta guía son fragmentos, no programas completos. Para probarlos, crea un archivo nuevo y pega **un snippet a la vez** dentro de la siguiente plantilla. No combines varios snippets en el mismo `main`, porque algunos declaran variables con el mismo nombre.

```cpp
#include <iostream>                             // Provides cin, cout, endl, and stream manipulators
using namespace std;                            // Allows standard-library names without the std:: prefix

int main() {                                    // Starts the program
    // Paste one code snippet here.              // Keeps each experiment independent

    return 0;                                   // Ends the program successfully
}                                               // Ends the main function
```

Cada snippet de esta lecture funciona con esa plantilla. Después de compilarlo, cambia los valores solicitados por `cin` y compara lo que ocurre con la condition que esperabas. La prueba breve forma parte de cada sección; no es una actividad separada al final.

---

## Parte 1 — Decisiones y `relational expressions` (20 min)

### 1.1 — Convertir una pregunta en un valor `bool`

Hasta ahora, las instrucciones de un programa se ejecutaban en orden: leer datos, calcular y mostrar resultados. Muchos problemas requieren una decisión. Por ejemplo, un sistema de préstamo de equipo debe determinar si la cantidad solicitada cabe dentro del inventario disponible.

Una **condition** es una pregunta cuya respuesta solo puede ser `true` o `false`. En C++, una `relational expression` construye esa pregunta mediante un `relational operator`.

| Operador | Pregunta que representa | Ejemplo |
|---|---|---|
| `>` | ¿es mayor que? | `requestedUnits > availableUnits` |
| `<` | ¿es menor que? | `temperature < 0` |
| `>=` | ¿es mayor o igual que? | `score >= 70` |
| `<=` | ¿es menor o igual que? | `speed <= limit` |
| `==` | ¿es igual a? | `section == 'A'` |
| `!=` | ¿es diferente de? | `choice != 0` |

Para observar el resultado de una condición, consideremos el inventario de un laboratorio. El inventario disponible se mantiene fijo para este ejemplo, pero la persona puede cambiar la cantidad que solicita y observar cómo cambia el resultado `bool`:

```cpp
int requestedUnits;                              // Stores the number of units requested
int availableUnits = 12;                         // Stores the number of units in stock

cout << "Enter the number of units requested: "; // Prompts for the value that will be compared
cin >> requestedUnits;                           // Reads the requested quantity from standard input

bool canLoanEquipment = requestedUnits <= availableUnits; // Stores true when stock is sufficient

cout << boolalpha;                               // Displays Boolean values as true or false
cout << "Can loan equipment: " << canLoanEquipment << endl; // Shows the decision result
```

Si se ingresa `8`, `8 <= 12` es verdadero y `canLoanEquipment` guarda `true`. Prueba también `12` y `13` para observar la diferencia entre `<=` y `<`. `boolalpha` solo cambia cómo se muestra un valor `bool`; sin él, C++ suele imprimir `1` para `true` y `0` para `false`.

⚠️ `=` y `==` no significan lo mismo. `=` es el **assignment operator**: cambia el valor de una variable. `==` es un **equality comparison**: pregunta si dos valores son iguales. Escribir `if (score = 70)` cuando se quería comparar es un error lógico muy frecuente.

También conviene evitar comparar valores `double` con `==` cuando el resultado proviene de cálculos. Por redondeo interno, dos valores que parecen iguales pueden diferir ligeramente. Para esta semana, usaremos comparaciones de `double` con rangos cuando sea necesario; más adelante veremos técnicas apropiadas para comparaciones de precisión.

**Para practicar por tu cuenta:**

Si `int completedTasks = 5;` y `int requiredTasks = 5;`, predice el valor de estas `relational expressions`: `completedTasks > requiredTasks`, `completedTasks == requiredTasks` y `completedTasks != requiredTasks`.

<details>
<summary>Ver respuesta</summary>

`completedTasks > requiredTasks` es `false`; `completedTasks == requiredTasks` es `true`; y `completedTasks != requiredTasks` es `false`.

</details>

---

## Parte 2 — `if` y `if`/`else` (25 min)

### 2.1 — Ejecutar un block solo cuando corresponde

Una `relational expression` por sí sola calcula `true` o `false`, pero no cambia el comportamiento del programa. Un **`if statement`** ejecuta una instrucción o un `block` únicamente cuando su condition es `true`.

Supón que un estacionamiento cobra una tarifa adicional si el vehículo permanece más de dos horas. Primero calculamos el total básico y luego aplicamos esa tarifa solo si se cumple la condition:

```cpp
double hoursParked;                             // Stores the time the vehicle remained parked
double fee = 5.00;                              // Starts with the base parking fee

cout << "Enter hours parked: ";                // Prompts for the value that controls the decision
cin >> hoursParked;                             // Reads the parking duration from standard input

if (hoursParked > 2.0) {                        // Checks whether the extra-fee condition is true
    fee = fee + 2.00;                           // Adds the extra fee only for stays over two hours
}                                               // Ends the block controlled by the if statement

cout << "Parking fee: $" << fee << endl;        // Displays the final fee after the possible decision
```

Las llaves `{ }` delimitan un **block**. Aunque una `if statement` puede controlar una sola instrucción sin llaves, usarlas desde ahora evita que una futura línea quede fuera de la decisión por accidente. La indentación hace visible qué instrucciones pertenecen al block, pero son las llaves las que el compilador usa para determinarlo.

### 2.2 — Elegir entre dos alternativas

Cuando el programa debe hacer una cosa si la condition es `true` y otra si es `false`, se usa `if`/`else`. Por ejemplo, antes de calcular un promedio debemos evitar dividir entre cero:

```cpp
int totalPoints = 84;                           // Stores the fixed total points for this example
int studentCount;                               // Stores how many students are in the group

cout << "Enter the number of students: ";      // Prompts for the denominator that controls the decision
cin >> studentCount;                            // Reads the student count from standard input

if (studentCount > 0) {                         // Allows division only when the denominator is positive
    double average = static_cast<double>(totalPoints) / studentCount; // Uses decimal division for the average
    cout << "Average: " << average << endl;     // Displays the valid calculated average
} else {                                        // Runs when studentCount is zero or negative
    cout << "Cannot calculate an average with zero or negative students." << endl; // Explains why no calculation occurred
}                                               // Ends the alternative paths
```

Solo se ejecuta uno de los dos blocks. Una condition bien elegida protege al programa antes de que ocurra un error, no después. En este ejemplo, la `input validation` completa llegará cuando `studentCount` se lea con `cin`; aquí el foco es reconocer que el denominador debe ser válido antes de dividir.

### 2.3 — Trazar ambos caminos

Al hacer un trace, no leas ambos blocks como si siempre ocurrieran. Marca primero si la condition es `true` o `false`, y sigue únicamente ese camino.

| `studentCount` | Resultado de `studentCount > 0` | Camino ejecutado |
|---:|---|---|
| `4` | `true` | Calcula y muestra el promedio. |
| `0` | `false` | Muestra el mensaje de error. |

**Para practicar por tu cuenta:**

Un programa aplica envío gratis cuando `orderTotal >= 50.0`; en caso contrario cobra `$6.00`. Escribe en pseudocódigo las dos alternativas antes de intentar C++.

<details>
<summary>Ver una posible respuesta</summary>

Si el total de la orden es al menos 50, asignar el costo de envío a 0. En cualquier otro caso, asignar el costo de envío a 6. Después, mostrar el costo de envío.

</details>

---

## Parte 3 — Más de dos resultados: `if`/`else if` y nested `if` (25 min)

### 3.1 — Una cadena de conditions ordenadas

Un programa puede tener más de dos resultados. Supón que un sistema traduce un porcentaje a una clasificación. Una cadena `if`/`else if` prueba las conditions de arriba hacia abajo y ejecuta **el primer block verdadero**.

```cpp
int score;                                      // Stores a score from 0 through 100

cout << "Enter a score from 0 to 100: ";       // Prompts for the score that controls the classification
cin >> score;                                   // Reads the score from standard input

if (score >= 90) {                              // Checks the highest range first
    cout << "Classification: Excellent" << endl; // Displays the result for scores 90 or higher
} else if (score >= 80) {                       // Runs only when the previous condition was false
    cout << "Classification: Good" << endl;    // Displays the result for scores from 80 through 89
} else if (score >= 70) {                       // Tests the next remaining range
    cout << "Classification: Satisfactory" << endl; // Displays the result for scores from 70 through 79
} else {                                        // Handles every value below 70
    cout << "Classification: Needs improvement" << endl; // Displays the remaining classification
}                                               // Ends the complete decision chain
```

El orden es esencial. Si la primera condition fuera `score >= 70`, un `score` de 95 entraría allí y nunca llegaría a la clasificación `Excellent`. Las condiciones se organizan de la categoría más restrictiva o alta hacia las siguientes, de forma que los rangos no se oculten unos a otros.

### 3.2 — Separar validación y clasificación

El `else` final del ejemplo anterior trataría `-10` igual que `60`, aunque `-10` no es un score válido. Una mejor solución valida primero el rango permitido y luego clasifica los valores correctos:

```cpp
int score;                                      // Stores the score entered by the user

cout << "Enter a score from 0 to 100: ";       // Tells the user the valid input range
cin >> score;                                   // Reads the score from standard input

if (score < 0 || score > 100) {                 // Rejects values outside the allowed range
    cout << "Invalid score." << endl;          // Reports invalid input without classifying it
} else if (score >= 90) {                       // Classifies only a valid high score
    cout << "Classification: Excellent" << endl; // Displays the high classification
} else if (score >= 80) {                       // Classifies the next valid range
    cout << "Classification: Good" << endl;    // Displays the middle-high classification
} else if (score >= 70) {                       // Classifies the next valid range
    cout << "Classification: Satisfactory" << endl; // Displays the middle classification
} else {                                        // Classifies all remaining valid scores from 0 through 69
    cout << "Classification: Needs improvement" << endl; // Displays the final valid classification
}                                               // Ends the validation and classification chain
```

### 3.3 — Un `if` dentro de otro `if`

Un **nested `if`** coloca una decisión dentro de un camino de otra decisión. Es útil cuando la segunda pregunta solo tiene sentido después de responder la primera. Por ejemplo, un sistema de envíos no debe clasificar un pedido como estándar o al por mayor hasta confirmar que la cantidad de paquetes no sea negativa:

```cpp
int packageCount;                               // Stores the number of packages entered by the user

cout << "Enter the number of packages: ";      // Prompts for the value used by both decisions
cin >> packageCount;                            // Reads the package count from standard input

if (packageCount >= 0) {                        // First confirms that the quantity is valid
    if (packageCount >= 100) {                  // Classifies only a valid quantity of 100 or more
        cout << "Shipping type: Bulk" << endl; // Displays the bulk-shipping classification
    } else {                                    // Handles valid quantities from 0 through 99
        cout << "Shipping type: Standard" << endl; // Displays the standard-shipping classification
    }                                           // Ends the inner classification decision
} else {                                        // Runs when the quantity fails the first validation
    cout << "Invalid package count." << endl;  // Reports the invalid input without classifying it
}                                               // Ends the outer validation decision
```

Prueba `-1`, `0`, `99` y `100`. Con `-1`, el `if` exterior es `false`, por lo que el `if` interior ni siquiera se evalúa. Con `100`, ambos `if` son `true` y el programa muestra `Bulk`. La indentación permite ver la relación entre los dos blocks, mientras que las llaves determinan esa relación para el compilador.

No todo `if` dentro de otro `if` es necesario. En este ejemplo también podríamos usar una cadena `if`/`else if`; el nesting enfatiza que la clasificación depende de una validación previa. Sin embargo, varios niveles de nesting pueden ser difíciles de leer; cuando las conditions representan rangos mutuamente excluyentes, una cadena `if`/`else if` suele ser más clara.

**Para practicar por tu cuenta:**

Ordena de manera correcta estas conditions para clasificar un número de paquetes: `packages >= 100`, `packages >= 50`, `packages >= 10` y el caso restante. Explica qué error habría si se prueban de menor a mayor.

<details>
<summary>Ver respuesta</summary>

Se deben probar de mayor a menor: 100, 50, 10 y el caso restante. Si se prueba primero `packages >= 10`, un valor de 120 cumple esa primera condition y los niveles de 50 y 100 nunca se alcanzan.

</details>

---

## Parte 4 — `logical operators`, rangos y `bool flags` (25 min)

### 4.1 — Combinar preguntas simples

Los `logical operators` permiten construir conditions más expresivas:

| Operador | Significado | Es `true` cuando… |
|---|---|---|
| `&&` | AND | ambas conditions son `true` |
| <code>&#124;&#124;</code> | OR | al menos una condition es `true` |
| `!` | NOT | invierte el valor de una condition |

Imagina que un programa concede acceso a un equipo solo a quien tenga una identificación válida **y** haya completado el entrenamiento. La identificación ya fue verificada por el sistema; cambia el estado del entrenamiento para observar que ambas condiciones deben cumplirse. Para una variable `bool`, `cin` acepta `1` para `true` y `0` para `false` por defecto:

```cpp
bool hasValidId = true;                         // Records whether the ID was accepted
bool completedTraining;                         // Records whether training was completed

cout << "Completed training? Enter 1 for yes or 0 for no: "; // Prompts for the changing Boolean value
cin >> completedTraining;                        // Reads 1 as true or 0 as false from standard input

bool canUseEquipment = hasValidId && completedTraining; // Requires both conditions to be true

cout << boolalpha;                              // Displays the Boolean result as a word
cout << "Can use equipment: " << canUseEquipment << endl; // Shows whether access is granted
```

Para representar un rango de valores válidos, piensa en los extremos. Un número está entre 1 y 12, inclusive, cuando satisface ambas preguntas: es al menos 1 **y** es como máximo 12. Un valor está fuera de ese rango cuando es menor que 1 **o** mayor que 12.

```cpp
int monthNumber;                                // Stores a month number entered by the user

cout << "Enter a month number from 1 to 12: "; // States the allowed range before reading input
cin >> monthNumber;                             // Reads the candidate month number

if (monthNumber >= 1 && monthNumber <= 12) {    // Accepts values inside the inclusive range
    cout << "Valid month number." << endl;     // Confirms a usable value
} else {                                        // Runs for every value outside the range
    cout << "Invalid month number." << endl;   // Explains that the value cannot be used
}                                               // Ends the range-validation decision
```

### 4.2 — `bool flag`

Un **`bool flag`** es una variable `bool` cuyo nombre describe un estado o una pregunta: `isValid`, `hasAccess`, `isWeekend`. Un buen nombre permite leer la condition casi como una oración. Evita nombres vagos como `flag1` porque esconden el significado de la decisión.

Por ejemplo, un sensor registra una temperatura y el programa guarda en un `bool flag` si esa temperatura está dentro del rango seguro. La variable `isTemperatureSafe` conserva el resultado de la condition para poder usarlo después, en vez de repetir toda la comparación:

```cpp
double temperature;                             // Stores the temperature entered by the user
const double MIN_SAFE_TEMPERATURE = 10.0;       // Defines the fixed lower safe limit
const double MAX_SAFE_TEMPERATURE = 35.0;       // Defines the fixed upper safe limit

cout << "Enter the temperature: ";             // Prompts for the value that will be checked
cin >> temperature;                             // Reads the temperature from standard input

bool isTemperatureSafe = temperature >= MIN_SAFE_TEMPERATURE && temperature <= MAX_SAFE_TEMPERATURE; // Stores the range-check result

if (isTemperatureSafe) {                        // Uses the descriptive flag to choose a path
    cout << "Temperature is safe." << endl;    // Reports a temperature inside the allowed range
} else {                                        // Runs when the flag is false
    cout << "Temperature is outside the safe range." << endl; // Reports a temperature outside the range
}                                               // Ends the decision controlled by the flag
```

Prueba `10`, `35`, `9.9` y `35.1`. El nombre `isTemperatureSafe` permite leer `if (isTemperatureSafe)` como una pregunta clara. Si la condición se necesitara en varias partes del programa, el `bool flag` también evita repetir una expresión larga y reduce el riesgo de escribirla de manera diferente en cada lugar.

La expresión `!isValid` se lee “not valid”. Es útil, pero no dupliques negaciones innecesarias: `if (!isNotAvailable)` obliga a descifrar el nombre antes de entender la condition.

**Para practicar por tu cuenta:**

Para cada situación, decide si corresponde `&&` u `||`:

1. Un cupón es válido si el cliente tiene membresía o escribió un código promocional.
2. Una batería puede cargarse si está conectada y su temperatura es segura.
3. Una entrada es inválida si es menor que 1 o mayor que 12.

<details>
<summary>Ver respuesta</summary>

1. `||`, porque basta una de las dos alternativas.
2. `&&`, porque se requieren ambas condiciones.
3. `||`, porque cualquiera de las dos situaciones deja el valor fuera del rango.

</details>

---

## Parte 5 — `switch`: opciones discretas (30 min)

### 5.1 — Cuándo usar un `switch statement`

Un `switch statement` compara **una expresión** con valores discretos llamados `case`. Es una buena opción cuando un menú usa opciones como `1`, `2`, `3`, o cuando un `char` representa una selección. No sustituye todos los `if`/`else if`: para rangos como `score >= 90` o conditions compuestas con `&&`, usamos `if`.

Supón que un programa de préstamo permite escoger el tipo de equipo mediante un número. Cada opción produce una tarifa distinta:

```cpp
int equipmentChoice;                            // Stores the menu option selected by the user

cout << "Equipment menu\n";                    // Introduces the available choices
cout << "1. Sensor kit\n";                     // Displays the first discrete option
cout << "2. Multimeter\n";                     // Displays the second discrete option
cout << "3. Power supply\n";                   // Displays the third discrete option
cout << "Enter your choice: ";                 // Prompts for one menu number
cin >> equipmentChoice;                         // Reads the chosen menu number

switch (equipmentChoice) {                      // Compares one expression against the listed cases
    case 1:                                      // Handles the sensor-kit option
        cout << "Fee: $4.00" << endl;           // Displays the fee for option 1
        break;                                   // Leaves the switch after handling option 1
    case 2:                                      // Handles the multimeter option
        cout << "Fee: $6.00" << endl;           // Displays the fee for option 2
        break;                                   // Leaves the switch after handling option 2
    case 3:                                      // Handles the power-supply option
        cout << "Fee: $8.00" << endl;           // Displays the fee for option 3
        break;                                   // Leaves the switch after handling option 3
    default:                                     // Handles every menu number not listed above
        cout << "Invalid equipment choice." << endl; // Reports an unsupported selection
}                                               // Ends the switch statement
```

Cada `case` representa una igualdad implícita: `case 2` se comporta como la pregunta “¿`equipmentChoice` es igual a 2?”. Los valores de los `case` deben ser constantes discretas, no rangos ni variables cuyo valor cambie durante el programa.

### 5.2 — El propósito de `break` y `default`

Sin `break`, al terminar el código de un `case`, la ejecución continúa al próximo `case`. A este comportamiento se le llama **fall-through**. A veces se usa intencionalmente en código avanzado, pero por ahora cada `case` de un menú debe terminar con `break` para impedir resultados inesperados.

Observa este ejemplo con un error intencional. Si se entra `1`, el programa muestra dos mensajes porque falta el `break` después de `case 1`:

```cpp
int shippingChoice;                             // Stores the shipping menu choice

cout << "Enter 1 for standard or 2 for express: "; // Prompts for one discrete menu choice
cin >> shippingChoice;                          // Reads the shipping choice from standard input

switch (shippingChoice) {                       // Compares the entered choice with each case
    case 1:                                     // Handles the standard-shipping option
        cout << "Standard shipping selected." << endl; // Displays the first message
    case 2:                                     // Runs next by fall-through when the first break is missing
        cout << "Express shipping selected." << endl; // Displays an unintended second message for input 1
        break;                                  // Leaves the switch after case 2
}                                               // Ends the switch statement with the intentional error
```

La versión correcta termina cada opción con `break` y usa `default` para una selección que no pertenece al menú:

```cpp
int shippingChoice;                             // Stores the shipping menu choice

cout << "Enter 1 for standard or 2 for express: "; // Prompts for one discrete menu choice
cin >> shippingChoice;                          // Reads the shipping choice from standard input

switch (shippingChoice) {                       // Compares the entered choice with each case
    case 1:                                     // Handles the standard-shipping option
        cout << "Standard shipping selected." << endl; // Displays the result for option 1
        break;                                  // Stops case 1 from continuing into case 2
    case 2:                                     // Handles the express-shipping option
        cout << "Express shipping selected." << endl; // Displays the result for option 2
        break;                                  // Stops case 2 after its own instructions
    default:                                    // Handles values other than 1 or 2
        cout << "Invalid shipping choice." << endl; // Reports a menu choice not supported by the program
}                                               // Ends the corrected switch statement
```

Prueba `1`, `2` y `9` en ambas versiones. La primera sirve únicamente para observar el error; la segunda es el patrón que debes usar para un menú.

`default` no es obligatorio para compilar, pero sí es una buena práctica para un menú: maneja cualquier valor no reconocido y evita que el programa parezca no hacer nada. Colócalo al final por legibilidad; no requiere `break` si es el último block, aunque añadirlo tampoco es un error.

### 5.3 — Elegir la estructura correcta

| Situación | Estructura apropiada | Razón |
|---|---|---|
| Calificar `score` por rangos | `if`/`else if` | Las conditions usan comparaciones como `>=`. |
| Verificar que un valor esté entre dos límites | `if` con `&&` | Se combinan dos conditions. |
| Escoger una de cuatro opciones de un menú | `switch` | Una expresión se compara con opciones discretas. |
| Ejecutar una alternativa y otra si no se cumple | `if`/`else` | Hay dos caminos complementarios. |

**Para practicar por tu cuenta:**

Un menú ofrece las opciones `A`, `B` y `C` para tres secciones de un edificio. ¿Usarías `switch` o `if`/`else if`? Escribe los `case` que necesitarías, incluido el manejo de una letra no válida.

<details>
<summary>Ver una posible respuesta</summary>

`switch` es apropiado porque una sola variable `char` se compara con opciones discretas. Se necesitan `case 'A':`, `case 'B':`, `case 'C':` y `default:` para la letra no válida; cada `case` debe terminar con `break`.

</details>

---

## Parte 6 — Diseño, trace y preparación para el Lab 5 (25 min)

### 6.1 — Del requisito a los test cases

Antes de escribir una `selection structure`, separa el problema en tres preguntas:

1. ¿Qué dato se necesita y cuál es su tipo?
2. ¿Cuál es exactamente la condition o la opción que debe decidir el camino?
3. ¿Qué debe pasar en cada camino, incluido un dato inválido?

Un **test case** es un valor de entrada que escogemos deliberadamente para comprobar un comportamiento específico del programa. Antes de ejecutarlo, debemos poder indicar qué camino esperamos que tome y cuál debe ser su salida. Por eso, cada test case incluye al menos: la entrada que se escribirá, la condition que debe resultar `true` o `false`, y el resultado esperado. No es suficiente ejecutar el programa con cualquier número y asumir que funciona porque no mostró un error.

Considera un programa que recibe una cantidad de horas de uso y clasifica una tarifa. Antes del C++, describe primero los casos: una cantidad negativa es inválida; de 0 a 2 horas usa una tarifa básica; más de 2 horas usa una tarifa extendida. Esta descripción ya revela que `if`/`else if` es más apropiado que `switch`, porque hay rangos.

El siguiente programa implementa esa decisión. Prueba `-1`, `2` y `2.5` para observar cada camino:

```cpp
double hoursUsed;                               // Stores the equipment-use duration

cout << "Enter hours used: ";                  // Prompts for the value that controls the classification
cin >> hoursUsed;                               // Reads the equipment-use duration from standard input

if (hoursUsed < 0.0) {                          // Rejects a duration that cannot exist
    cout << "Invalid duration." << endl;        // Reports invalid input
} else if (hoursUsed <= 2.0) {                  // Covers the valid basic range from 0 through 2
    cout << "Rate: Basic" << endl;              // Displays the basic-rate classification
} else {                                        // Covers every valid duration greater than 2
    cout << "Rate: Extended" << endl;           // Displays the extended-rate classification
}                                               // Ends the decision chain
```

Un buen conjunto de test cases no usa solo valores cómodos. Incluye los límites y valores justo fuera de ellos. Para este problema, `-1`, `0`, `2`, `2.0001` y `2.5` ayudan a verificar cada camino. Los **boundary values** descubren muchos errores como usar `< 2` cuando el requisito decía “hasta 2, inclusive”.

| Entrada | Camino esperado | Salida esperada |
|---:|---|---|
| `-1` | Primer `if` | `Invalid duration.` |
| `2` | `else if` | `Rate: Basic` |
| `2.5` | `else` | `Rate: Extended` |

**Para practicar por tu cuenta:**

Diseña tres test cases para un menú `switch` con opciones válidas `1`, `2` y `3`. Incluye al menos un test case que llegue a `default` e indica qué salida esperas.

<details>
<summary>Ver una posible respuesta</summary>

Por ejemplo: entrada `1` debe ejecutar `case 1`; entrada `3` debe ejecutar `case 3`; entrada `9` debe ejecutar `default` y mostrar un mensaje de opción inválida. También sería útil probar `0` o una entrada no numérica cuando estudiemos validación de `cin` con más detalle.

</details>

---

## Práctica guiada e integración de snippets (20 min)

### Ejercicio guiado — Solicitud de préstamo de equipo

En la plantilla mínima de la lecture, escribe un programa que determine si una persona puede solicitar un equipo del laboratorio y qué equipo escogió.

El programa debe pedir una cantidad de horas de préstamo. Solo se permiten préstamos de **1 a 4 horas, inclusive**. Si la cantidad está fuera de ese rango, debe mostrar `Invalid loan duration.` y terminar sin mostrar el menú.

Si la cantidad es válida, el programa debe mostrar este menú y pedir una opción:

| Opción | Equipo | Mensaje esperado |
|---:|---|---|
| `1` | Sensor kit | `Equipment selected: Sensor kit` |
| `2` | Multimeter | `Equipment selected: Multimeter` |
| `3` | Power supply | `Equipment selected: Power supply` |

Usa un `if` con `&&` para validar las horas y un `switch` con `case`, `break` y `default` para las opciones del equipo. El `default` debe mostrar `Invalid equipment choice.`

Antes de compilar, escribe estas predicciones y luego verifica cada una con el programa:

| Horas | Opción | Resultado esperado |
|---:|---:|---|
| `0` | — | Muestra `Invalid loan duration.` y no presenta el menú. |
| `1` | `2` | Acepta las horas y muestra `Equipment selected: Multimeter`. |
| `4` | `3` | Acepta las horas y muestra `Equipment selected: Power supply`. |
| `5` | — | Muestra `Invalid loan duration.` y no presenta el menú. |
| `2` | `9` | Presenta el menú y luego muestra `Invalid equipment choice.` |

Durante la discusión, identifica qué `test cases` verifican los boundary values (`1` y `4`) y cuál llega al `default`.

---

## Resumen de la sesión

- Una `relational expression` produce `true` o `false`; `if` usa ese resultado para decidir si ejecuta un block.
- `if`/`else` representa dos caminos; `if`/`else if` permite varios caminos y ejecuta el primero cuya condition sea verdadera.
- Los `logical operators` combinan conditions y permiten validar rangos.
- Un `bool flag` debe describir claramente la pregunta o el estado que representa.
- `switch` es adecuado para una expresión y opciones discretas; usa `break` para evitar fall-through y `default` para manejar opciones no reconocidas.
- Antes de programar, enumera los caminos posibles y prueba boundary values, no solo casos ordinarios.

## Próxima sesión

En el Lab 5 se practicarán `if`/`else` y `switch` mediante programas que integran la entrada con `cin`, operadores y formato de salida trabajados en Semana 4.
