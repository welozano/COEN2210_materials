# Semana 4 — Conceptos Básicos de Programación y Elementos
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Gaddis, *Starting Out with C++: From Control Structures through Objects* — Capítulo 3, "Expressions and Interactivity" (secciones 3.1–3.10)

**Duración:** 170 min (lectura)
**Precede a:** Lab 4 — trazar expresiones, detectar errores lógicos, entrada con `cin`, `sqrt`, formato de salida y explicit casts

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:

1. Usar `cin` con prompts claros para leer datos del teclado y almacenarlos en variables.
2. Construir expresiones matemáticas en C++ respetando la precedencia de operadores y los tipos de datos.
3. Explicar el efecto de la división entera, las implicit type conversions y `static_cast` en un cálculo.
4. Usar `sqrt` de `<cmath>` y manipuladores de `<iomanip>` para producir resultados numéricos correctos y legibles.
5. Trazar un programa a mano para localizar errores lógicos antes de ejecutarlo.

---

## Parte 1 — Entrada por teclado con `cin` (25 min)

Imagina un programa que calcula la circunferencia de un círculo cuyo radio siempre es 5.4. En ese caso, el valor puede estar escrito directamente en el código:

```cpp
const double RADIUS = 5.4;  // Fixed radius used by the calculation
```

Eso es útil para practicar una fórmula, pero no es interactivo. Un programa se vuelve más útil cuando una persona puede proporcionarle datos mientras corre. Para eso usamos `cin`, el objeto de **entrada estándar**.

En este curso, la entrada estándar normalmente viene del teclado. `cin` recibe datos de esa entrada y el operador `>>` los extrae hacia una variable. Más adelante, al trabajar con archivos, usaremos el mismo patrón `>>` con objetos de archivo; no será `cin` quien lea el archivo, sino un flujo de archivo diferente.

Por ejemplo, supón que queremos registrar la carga académica de un estudiante. El programa necesita pedir la cantidad de créditos y guardarla como un entero:

```cpp
int credits;  // Stores the student's number of credits

cout << "How many credits are you taking? ";  // Prompts the student for input
cin >> credits;                                // Reads an integer from standard input
```

La línea con `cout` se llama un **prompt**: un mensaje que le indica claramente a la persona qué debe escribir. No asumas que el usuario sabe qué dato espera el programa; cada `cin` debe tener un prompt útil antes.

Cuando la persona escribe, por ejemplo, `15` y presiona Enter, `cin` interpreta ese texto como un valor del tipo de la variable y lo guarda en `credits`.

| Parte | Qué ocurre en el ejemplo |
|---|---|
| `int credits;` | Se reserva una variable para un número entero. |
| `cout << ...` | Se muestra una pregunta en pantalla. |
| `cin >> credits;` | Se lee la respuesta y se guarda como `int`. |

### 1.1 — Input type y input buffer

**El tipo importa.** Supón que el programa de inventario de una tienda pide una cantidad de piezas, la cual debe ser entera:

```cpp
int pieces;  // Stores a whole number of pieces

cout << "Enter the number of pieces: ";  // Asks for a whole-number quantity
cin >> pieces;                            // Attempts to read an integer
```

Si la persona escribe `3.75`, `cin` puede leer la parte entera `3` y dejar `.75` pendiente en el **buffer de entrada**. El buffer es la secuencia de caracteres que el teclado ya entregó al programa, pero que una lectura todavía no ha consumido. No redondea a `4`, ni convierte mágicamente ese dato completo a un entero.

La parte pendiente importa mucho porque la próxima instrucción `cin` la encuentra antes de esperar una respuesta nueva. El resultado depende del tipo de la siguiente variable.

### 1.2 — La próxima extracción es hacia un `double`

```cpp
int pieces = 0;         // Stores the whole-number quantity
double measurement = 0; // Stores a decimal measurement

cout << "Enter the number of pieces: ";  // First prompt expects an integer
cin >> pieces;                            // Reads only the integer portion of 3.75
cout << "Pieces read: " << pieces << endl; // Displays the recovered value: 3

cout << "Enter a decimal measurement: "; // Second prompt appears on screen
cin >> measurement;                       // Reads the remaining .75 as 0.75
cout << "Measurement read: " << measurement << endl; // Displays the recovered value: 0.75
```

Si la persona responde `3.75` al primer prompt, ocurre esta secuencia:

| Momento | Variable | Valor | Buffer de entrada |
|---|---|---:|---|
| Después de escribir `3.75` | — | — | `3.75` |
| Después de `cin >> pieces` | `pieces` | `3` | `.75` |
| Después de `cin >> measurement` | `measurement` | `0.75` | vacío |

El segundo `cin` no espera que la persona escriba otra medida: toma automáticamente `.75` que quedó pendiente. La pantalla puede mostrar el segundo prompt, pero el programa parece "saltárselo" porque ya había texto disponible en el buffer.

### 1.3 — La próxima extracción es hacia otro `int`

```cpp
int pieces = 0;       // Stores the first whole-number quantity
int nextPieces = 0;   // Starts at zero so its value is observable after failure

cout << "Enter the number of pieces: ";      // First prompt expects an integer
cin >> pieces;                                // Leaves .75 after reading 3
cout << "Pieces read: " << pieces << endl;   // Displays the recovered value: 3

cout << "Enter another number of pieces: "; // Second prompt also expects an integer
cin >> nextPieces;                            // Fails because .75 cannot begin an integer
cout << "Next pieces read: " << nextPieces << endl; // Displays its unchanged value: 0
```

Con la entrada inicial `3.75`, el primer `cin` vuelve a guardar `3` y deja `.75`. Pero `.75` no es el inicio válido de un entero, así que el segundo `cin` falla. `nextPieces` conserva el valor que ya tenía (`0` en este ejemplo) y el flujo de entrada queda en estado de error. Las lecturas posteriores con `cin >> ...` también fallarán hasta que el programa limpie ese estado y descarte la entrada problemática, una técnica que veremos cuando estudiemos validación de datos.

Este es un error común porque el mensaje de la segunda pregunta sí aparece, pero el programa no se detiene a esperar una respuesta. Cuando un programa "ignora" una entrada, revisa primero si una lectura anterior consumió solo parte de lo escrito.

Por ejemplo, una estación meteorológica que registra una temperatura debe declarar un `double` desde el principio:

```cpp
double temperature;  // Stores a value that may include decimals

cout << "Enter the temperature in Celsius: "; // Prompts for a decimal value
cin >> temperature;                            // Reads the complete decimal input
cout << "Recorded temperature: " << temperature // Displays the stored value
     << " degrees.\n";
```

### 1.4 — Input extraction, implicit conversion y explicit cast

En C++, varios procesos relacionados con los tipos tienen nombres técnicos distintos:

| Proceso | Cuándo sucede | Ejemplo |
|---|---|---|
| **Input extraction** | `cin` interpreta texto escrito por la persona. | Los caracteres `"27"` se guardan como el `int` `27`. |
| **Implicit type conversion** | C++ adapta tipos compatibles durante una expresión. | En `3 * 2.5`, el `3` se trata temporalmente como decimal. |
| **Explicit cast** | El programador solicita un type conversion concreto en código. | `static_cast<double>(points)` |

Un **explicit cast** no cambia el tipo declarado de la variable original. Crea un valor convertido para la operación que se está realizando. Por ejemplo, si `points` es `int`, `static_cast<double>(points)` usa una versión decimal de ese valor; `points` sigue siendo `int`. Veremos el mecanismo y la razón de usarlo para evitar división entera en la Parte 3.

Considera ahora un programa para calcular el área de un salón. Necesita dos dimensiones; la persona puede escribirlas en el mismo orden, separadas por espacios o por Enter:

```cpp
double length, width;  // Store the room dimensions

cout << "Enter the room length and width: "; // Explains the required input order
cin >> length >> width;                       // Reads both decimal values in order
```

Si se escribe `8.5 6`, `length` recibe `8.5` y `width` recibe `6`. El primer valor ingresado se guarda en la primera variable y el segundo en la segunda; por eso el orden debe coincidir con el prompt.

**Para practicar por tu cuenta:**

¿Qué tipo de dato escogerías y qué prompt escribirías para pedir cada uno de estos datos?

1. La cantidad de libros prestados en una biblioteca.
2. El costo de una pieza electrónica.
3. La inicial de la sección de un estudiante.

<details>
<summary>Ver una posible respuesta</summary>

1. `int borrowedBooks;` y `cout << "How many books did you borrow? ";`
2. `double partCost;` y `cout << "Enter the part cost: $";`
3. `char section;` y `cout << "Enter your section initial: ";`

Hay otros prompts válidos si expresan con claridad el dato esperado.

</details>

---

## Parte 2 — Expresiones, precedencia y repaso aplicado (20 min)

### 2.1 — Mathematical expressions

Una **expression** es cualquier combinación de literales, variables y operadores que produce un valor. Una variable sola es una expression; `7.5` también lo es; `length * width` es una expresión matemática.

Por ejemplo, después de leer las dimensiones de una pared, un programa necesita multiplicarlas para calcular el área que se pintará:

```cpp
double area;              // Stores the wall area in square units
area = length * width;    // Multiplies the previously entered dimensions
```

La computadora no interpreta álgebra como una persona. Debes escribir explícitamente cada multiplicación y traducir con cuidado los paréntesis.

| Matemática | C++ |
|---|---|
| área = largo × ancho | `area = length * width;` |
| perímetro = 2(largo + ancho) | `perimeter = 2 * (length + width);` |
| promedio = suma / cantidad | `average = sum / count;` |
| pendiente = (y₂ − y₁) / (x₂ − x₁) | `slope = (y2 - y1) / (x2 - x1);` |

No existe un operador de exponenciación `^` para elevar números al cuadrado en C++. Ese símbolo se usa para otra operación que veremos mucho más adelante. Por ahora, un cuadrado se puede expresar multiplicando el valor por sí mismo: `side * side`. También veremos `pow` y `sqrt` más adelante en esta misma sesión.

### 2.2 — Precedence y associativity

C++ sigue un orden de operaciones parecido al de matemáticas:

1. Paréntesis interiores primero.
2. Negación unaria, como `-valor`.
3. Multiplicación, división y residuo: `*`, `/`, `%`, de izquierda a derecha.
4. Suma y resta: `+`, `-`, de izquierda a derecha.

Supón que un programa debe combinar varios costos y descuentos. Los paréntesis cambian el resultado de su expresión:

```cpp
int result1 = 2 + 2 * 2 - 2;       // Evaluates multiplication first: 4
int result2 = (2 + 2) * 2 - 2;     // Evaluates parentheses first: 6
int result3 = 2 + 2 * (2 - 2);     // Evaluates inner parentheses first: 2
```

Los paréntesis no son solo para el compilador: también ayudan a otra persona a leer tu intención. Cuando una fórmula tenga varias operaciones, es preferible usar paréntesis aunque conozcas la precedencia.

### 2.3 — Repaso aplicado: integer division

En la Semana 3 conociste los operadores aritméticos, el módulo (`%`) y la división entera. Aquí los usaremos para leer expresiones completas y anticipar errores lógicos. Supón que siete piezas se reparten por igual en dos cajas:

```cpp
int pieces = 7;  // Total number of pieces to distribute
int boxes = 2;   // Number of boxes receiving the pieces

cout << pieces / boxes << endl;  // Displays 3 because integer division truncates
```

La salida es `3`, no `3.5`. Como ambos operandos son `int`, C++ hace **división entera**: elimina la parte decimal. La variable que recibe el resultado no cambia esta decisión; lo que decide la operación son los tipos de los valores a ambos lados de `/`.

```cpp
double average;  // Intended to store a decimal average
int points = 17; // Total points earned
int students = 4; // Number of students

average = points / students;  // Stores 4.0, not 4.25, after integer division
```

En la próxima parte veremos cómo corregirlo de forma intencional con `static_cast`. La idea importante no es memorizar otra vez la definición de `/`, sino identificar el tipo de los operandos **antes** de confiar en el resultado de una fórmula.

**Para practicar por tu cuenta:**

Calcula a mano el resultado de cada expresión antes de verificarlo en C++. Estas podrían ser expresiones usadas por un programa de inventario:

```cpp
int quotient = 18 / 5;            // Integer division result
int remainder = 18 % 5;           // Remaining items after division
int totalWithoutParentheses = 4 + 3 * 5; // Multiplication has higher precedence
int totalWithParentheses = (4 + 3) * 5;  // Parentheses change the order
```

<details>
<summary>Ver respuesta</summary>

1. `quotient` vale `3` — la división es entera.
2. `remainder` vale `3` — es el residuo de 18 dividido entre 5.
3. `totalWithoutParentheses` vale `19` — primero `3 * 5`.
4. `totalWithParentheses` vale `35` — los paréntesis cambian el orden.

</details>

---

## Parte 3 — Type Conversion y `static_cast` (20 min)

### 3.1 — Implicit type conversion

En ocasiones una expression mezcla tipos. Supón que una tienda multiplica una cantidad entera de artículos por un precio decimal. C++ realiza **implicit type conversions** para poder operar, pero conviene entenderlas porque pueden cambiar un resultado.

```cpp
int units = 3;          // Number of items is a whole number
double price = 2.50;    // Unit price includes cents
double total = units * price; // C++ promotes units for decimal multiplication
```

Para multiplicar, C++ convierte temporalmente `units` a `double`. El resultado es `7.5`, que se guarda correctamente en `total`.

Una **narrowing conversion** puede ser problemática en la dirección contraria. Por ejemplo, si un sensor registra una medida decimal y el programa la guarda en una variable entera:

```cpp
double measurement = 9.8;       // Original value includes a decimal part
int wholeMeasurement = measurement; // Assignment discards the decimal part
```

`wholeMeasurement` termina con `9`. Al pasar de `double` a `int`, se descarta la parte decimal; no se redondea automáticamente.

### 3.2 — Explicit cast con `static_cast`

Para obtener el promedio decimal de los puntos de cuatro estudiantes, aplica un **explicit cast** a uno de los operands **antes** de dividir:

```cpp
int points = 17;        // Total points to average
int students = 4;       // Number of students
double average;         // Stores the decimal average

average = static_cast<double>(points) / students; // Converts before division
cout << average << endl;                           // Displays 4.25
```

`static_cast<double>(points)` crea una versión temporal de `points` como `double`; no cambia el valor ni el tipo original de `points`. Ahora uno de los operands es `double`, así que la división se hace con decimales.

El estilo antiguo `(double)points` también puede aparecer en código existente — de hecho, lo vieron en el Lab 2 al mostrar un `unsigned char` como número — pero a partir de ahora preferiremos `static_cast<type>(value)` porque hace la intención más visible.

**Regla para recordar:** convierte antes de la operación cuyo resultado necesitas cambiar, no después.

```cpp
double incorrect = static_cast<double>(17 / 4); // Cast happens after losing .25
double correct = static_cast<double>(17) / 4;   // Cast happens before division: 4.25
```

### 3.3 — Overflow y underflow

Cada tipo puede guardar solo un rango limitado de valores. Si un resultado es mayor que el máximo que cabe, ocurre **overflow**; si es menor que el mínimo representable, ocurre **underflow**. El resultado puede depender del tipo y del sistema, por lo que no debemos diseñar programas que dependan de ese comportamiento.

Esto conecta con el Lab 2: un `unsigned char` solo tiene espacio para valores de 0 a 255. Al superar 255, el valor vuelve al inicio de su rango. La lección práctica es escoger tipos adecuados y revisar si una fórmula puede producir valores muy grandes.

**Para practicar por tu cuenta:**

¿Cuál de estas dos líneas calcula correctamente un promedio de 13 puntos entre 2 tareas? Explica por qué.

```cpp
double truncatedAverage = 13 / 2;                // Integer division produces 6.0
double decimalAverage = static_cast<double>(13) / 2; // Decimal division produces 6.5
```

<details>
<summary>Ver respuesta</summary>

`decimalAverage` calcula el promedio correctamente: vale `6.5`. En `truncatedAverage`, ambos operandos son enteros, por lo que `13 / 2` se calcula primero como `6`; después ese `6` se convierte a `double` y queda `6.0`.

</details>

---

## Parte 4 — Funciones matemáticas y la hipotenusa (15 min)

La biblioteca estándar incluye funciones que no tienen un operador simple. Para usarlas, incluimos `<cmath>`. Una que usaremos de inmediato es `sqrt`, que calcula una raíz cuadrada.

Para un triángulo rectángulo, el teorema de Pitágoras dice:

\[
h = \sqrt{a^2 + b^2}
\]

### 4.1 — Mathematical library functions

Para resolver un problema concreto, supón que un técnico necesita calcular el cable mínimo para conectar dos puntos separados por los catetos de un triángulo rectángulo. En C++, traducimos cada parte de la fórmula de manera explícita. Usamos `legA * legA` y `legB * legB` para los cuadrados, y `sqrt(...)` para la raíz:

```cpp
#include <iostream> // Enables standard input and output
#include <cmath>    // Declares sqrt
using namespace std;

int main()
{
    double legA, legB, hypotenuse; // Store the triangle side lengths

    cout << "Enter the two triangle legs: "; // Explains the required measurements
    cin >> legA >> legB;                      // Reads both decimal side lengths

    hypotenuse = sqrt(legA * legA + legB * legB); // Applies the Pythagorean theorem

    cout << "The hypotenuse is " << hypotenuse << endl; // Displays the calculated cable length
    return 0;                                            // Ends the program successfully
}
```

Lee la expresión de adentro hacia afuera: primero se multiplican los catetos por sí mismos, luego se suman ambos resultados y finalmente `sqrt` calcula la raíz de esa suma.

Algunas funciones matemáticas comunes también viven en `<cmath>`:

| Función | Propósito | Ejemplo |
|---|---|---|
| `sqrt(x)` | raíz cuadrada de `x` | `sqrt(81.0)` da `9.0` |
| `pow(base, exponente)` | potencia | `pow(2.0, 3.0)` da `8.0` |
| `abs(x)` | valor absoluto entero | `abs(-12)` da `12` |

Por ahora, incluye solo las bibliotecas que usas. Si llamas a `sqrt` sin `#include <cmath>`, el compilador no tiene la declaración que necesita para trabajar con esa función.

**Para practicar por tu cuenta:**

Si los catetos miden 5 y 12, ¿cuál debe ser la hipotenusa? Traza primero la fórmula a mano y luego prueba el programa.

<details>
<summary>Ver respuesta</summary>

`sqrt(5 * 5 + 12 * 12)` = `sqrt(25 + 144)` = `sqrt(169)` = `13`.

</details>

---

## Parte 5 — Formato de salida numérica (15 min)

### 5.1 — Output formatting

Un programa puede calcular correctamente y aun así comunicar mal su resultado. Por ejemplo, mostrar demasiados decimales para un precio distrae y parece poco profesional. Los manipuladores de `<iomanip>` permiten controlar el formato de `cout`. Para un informe de costos, queremos mostrar siempre dos decimales, incluso si el valor es exacto; el programa necesita esta biblioteca:

```cpp
#include <iomanip> // Declares output manipulators such as setprecision
```

Los tres manipuladores más útiles en este momento son:

| Manipulador | Efecto |
|---|---|
| `fixed` | Muestra números decimales en notación decimal fija. |
| `setprecision(n)` | Con `fixed`, muestra exactamente `n` dígitos después del punto decimal. |
| `showpoint` | Muestra el punto decimal aun cuando el valor no tenga fracción visible. |

```cpp
double cost = 7.5;   // Price of one item
double total = 15.0; // Final amount to display

cout << fixed << setprecision(2);     // Keeps two digits after the decimal point
cout << "Cost: $" << cost << endl;   // Displays 7.50 for a price
cout << "Total: $" << total << endl; // Displays 15.00 for the final amount
```

La salida es:

```
Cost: $7.50
Total: $15.00
```

`fixed` y `setprecision` permanecen activos en el flujo de salida hasta que se cambien. Por eso normalmente se colocan una vez, antes de imprimir una sección de resultados. Sin `fixed`, `setprecision(2)` significa dos dígitos significativos, no necesariamente dos decimales.

**Para practicar por tu cuenta:**

Un programa de calificaciones necesita mostrar un promedio con tres decimales. ¿Qué `#include` falta para que compile?

```cpp
#include <iostream> // Enables cout
using namespace std;

int main()
{
    double average = 91.375;                    // Sample grade average
    cout << fixed << setprecision(3) << average << endl; // Formats the average
    return 0;                                   // Ends the program successfully
}
```

<details>
<summary>Ver respuesta</summary>

Falta `#include <iomanip>`, porque ahí se declara `setprecision`.

</details>

---

## Parte 6 — Asignación combinada y texto breve (10 min)

### 6.1 — Combined assignment

Supón que un carrito de compra ya contiene 10 artículos y el cliente agrega 3 más. Hay una forma compacta de actualizar la variable usando el resultado que ya tiene:

```cpp
int totalItems = 10;         // Items already in the shopping cart
totalItems = totalItems + 3; // Adds the three new items
```

Esto equivale a:

```cpp
totalItems += 3; // Adds three items to the existing total
```

Existen operadores combinados para las operaciones aritméticas que ya conocen:

| Forma larga | Forma combinada |
|---|---|
| `balance = balance + deposit;` | `balance += deposit;` |
| `lives = lives - 1;` | `lives -= 1;` |
| `total = total * 2;` | `total *= 2;` |
| `half = half / 2;` | `half /= 2;` |

No uses una forma combinada solo por hacer el código más corto. Úsala cuando conserve o aumente la claridad. Por ejemplo, `counter += 1;` expresa claramente que el contador aumenta una unidad.

### 6.2 — Multiple assignment e initialization

Para iniciar el conteo de problemas encontrados al revisar un programa, puedes asignar el mismo valor inicial a variables del mismo tipo:

```cpp
int errors = 0;   // Counts errors found during review
int warnings = 0; // Counts warnings found during review
```

Aunque `errors = warnings = 0;` es válido después de declarar ambas variables, para este curso preferiremos declaraciones claras en líneas separadas cuando los nombres representan ideas diferentes.

---

## Parte 7 — Trazar un programa a mano y encontrar errores lógicos (25 min)

Un programa puede compilar y correr sin producir la respuesta correcta. Eso es un **error lógico**. El compilador no sabe cuál era tu intención matemática; solo ejecuta exactamente las instrucciones que escribiste.

Una herramienta sencilla para encontrar estos errores es el **trazado a mano**. Consiste en actuar como la computadora: avanzar instrucción por instrucción y anotar cómo cambian las variables.

### 7.1 — Hand tracing

Examina este programa, que intenta calcular el precio final de varias libretas. El problema indica que el descuento es 10%, pero el cálculo contiene un error lógico:

```cpp
int quantity = 4;             // Number of notebooks purchased
double unitPrice = 2.75;      // Price of each notebook
double discountRate = 0.10;   // Represents a 10 percent discount

double subtotal = quantity * unitPrice; // Calculates the amount before discount
double total = subtotal - discountRate; // Incorrectly subtracts ten cents
```

El código compila, pero el descuento se está tratando como si fuera diez centavos. Si `discountRate` representa 10%, primero hay que calcular la cantidad descontada.

| Línea ejecutada | `quantity` | `unitPrice` | `subtotal` | `discountRate` | `total` |
|---|---:|---:|---:|---:|---:|
| después de las declaraciones | 4 | 2.75 | — | 0.10 | — |
| `subtotal = ...` | 4 | 2.75 | 11.00 | 0.10 | — |
| `total = subtotal - discountRate` | 4 | 2.75 | 11.00 | 0.10 | 10.90 |

El resultado esperado para 10% de descuento es `9.90`, no `10.90`. Una corrección posible es:

```cpp
double discountAmount = subtotal * discountRate; // Calculates ten percent of the subtotal
double total = subtotal - discountAmount;        // Subtracts the calculated discount
```

### 7.2 — Hand-tracing method

1. Escribe los valores iniciales de todas las variables.
2. Lee una instrucción ejecutable a la vez, de arriba hacia abajo.
3. Calcula el lado derecho de una asignación antes de cambiar la variable del lado izquierdo.
4. Anota el nuevo valor en una tabla.
5. Compara el resultado final con un valor que puedas verificar a mano.

El trazado también permite detectar división entera. Por ejemplo, supón que 25 puntos se distribuyen entre 4 tareas:

```cpp
int totalPoints = 25;        // Total points earned
int assignments = 4;         // Number of assignments
double average = totalPoints / assignments; // Integer division happens before assignment
```

| Paso | `totalPoints` | `assignments` | Expresión calculada | `average` |
|---|---:|---:|---:|---:|
| inicialización | 25 | 4 | — | — |
| asignación de `average` | 25 | 4 | `25 / 4` = `6` | 6.0 |

El tipo de `average` no recupera el `.25` que se perdió durante la división. La corrección es convertir uno de los operandos antes de dividir.

**Para practicar por tu cuenta:**

Una tienda aplica un 20% de descuento sobre un artículo de `$50.00`. Traza el siguiente código y determina el valor final de `result`; luego identifica el error lógico.

```cpp
double price = 50.0;     // Original item price
double discountRate = 20; // Intended percentage, but stored incorrectly
double result = price - discountRate; // Incorrectly subtracts 20 dollars
```

<details>
<summary>Ver respuesta</summary>

`result` vale `30.0`. El programa restó 20 dólares, no 20%. Una posible corrección es guardar la tasa como `0.20` y calcular primero `price * discountRate`.

</details>

---

## Parte 8 — Conectar entrada, proceso y salida (15 min)

### 8.1 — IPO model

La mayoría de los programas de esta etapa siguen el patrón **IPO**:

| Etapa | Pregunta que debes responder |
|---|---|
| Input (entrada) | ¿Qué datos necesita el programa? |
| Process (proceso) | ¿Qué fórmulas o transformaciones debe aplicar? |
| Output (salida) | ¿Qué resultados debe comunicar y con qué formato? |

Antes de escribir código, organiza el problema. Supón que queremos calcular cuánto tarda un estudiante en recorrer cierta distancia a una velocidad constante.

| Elemento | Diseño |
|---|---|
| Entrada | distancia en kilómetros y velocidad en km/h |
| Proceso | `time = distance / speed` |
| Salida | tiempo estimado en horas, con dos decimales |

Un programa original que implementa ese diseño pide primero las dos entradas, calcula el tiempo y muestra el resultado formateado:

```cpp
#include <iostream> // Enables standard input and output
#include <iomanip>  // Declares fixed and setprecision
using namespace std;

int main()
{
    double distance, speed, time; // Store the trip data and calculated duration

    cout << "Enter the distance in kilometers: "; // Prompts for the trip distance
    cin >> distance;                              // Reads the distance from standard input

    cout << "Enter the speed in km/h: ";          // Prompts for the travel speed
    cin >> speed;                                 // Reads the speed from standard input

    time = distance / speed;                      // Calculates time in hours

    cout << fixed << setprecision(2);             // Formats decimal output to two places
    cout << "Estimated time: " << time << " hours" << endl; // Displays the result

    return 0;                                     // Ends the program successfully
}
```

Este programa todavía no valida que la velocidad sea distinta de cero; la validación con estructuras de selección llegará en la Semana 5. Por ahora, el objetivo es reconocer con precisión qué es entrada, proceso y salida, y probar con valores sensatos.

**Para practicar por tu cuenta:**

Diseña las tres partes IPO para un programa que reciba el largo y ancho de una pared y calcule cuántos metros cuadrados se deben pintar. No escribas código todavía.

<details>
<summary>Ver una posible respuesta</summary>

- **Entrada:** largo y ancho de la pared, ambos como `double`.
- **Proceso:** `area = length * width`.
- **Salida:** el área en metros cuadrados, posiblemente con dos decimales.

</details>

---

## Resumen de la sesión

- `cin >> variable;` lee un dato del teclado; un prompt claro con `cout` debe indicarle al usuario qué escribir.
- Las expresiones obedecen precedencia; los paréntesis hacen explícita la intención matemática.
- La división entre enteros trunca. `static_cast<double>(value)` debe ocurrir antes de dividir si necesitas decimales.
- `<cmath>` da acceso a funciones como `sqrt`; `<iomanip>` permite usar `fixed` y `setprecision`.
- Un trazado a mano muestra cómo cambian las variables y ayuda a localizar errores lógicos que el compilador no detecta.
- Antes de programar, separa entrada, proceso y salida.

## Próxima sesión

**Lab 4 — Trazar expresiones y detectar errores lógicos** — van a comprobar a mano y en C++ los efectos de la precedencia, la división entera, el type casting, `sqrt`, y el formato de resultados.
