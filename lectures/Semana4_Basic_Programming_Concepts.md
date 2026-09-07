# Semana 4 — Conceptos Básicos de Programación y Elementos
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Gaddis, *Starting Out with C++: From Control Structures through Objects* — Capítulo 3, "Expressions and Interactivity" (secciones 3.1–3.10)

**Duración:** 170 min (lectura)
**Precede a:** Lab 4 — trazar expresiones, detectar errores lógicos, entrada con `cin`, `sqrt`, formato de salida y type casting

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:

1. Usar `cin` con prompts claros para leer datos del teclado y almacenarlos en variables.
2. Construir expresiones matemáticas en C++ respetando la precedencia de operadores y los tipos de datos.
3. Explicar el efecto de la división entera, las conversiones automáticas y `static_cast` en un cálculo.
4. Usar `sqrt` de `<cmath>` y manipuladores de `<iomanip>` para producir resultados numéricos correctos y legibles.
5. Trazar un programa a mano para localizar errores lógicos antes de ejecutarlo.

---

## Parte 1 — Entrada por teclado con `cin` (25 min)

Hasta ahora, los valores de nuestros programas estaban escritos directamente en el código:

```cpp
const double RADIO = 5.4;
```

Eso es útil para practicar una fórmula, pero no es interactivo. Un programa se vuelve más útil cuando una persona puede proporcionarle datos mientras corre. Para eso usamos `cin`, el objeto de entrada estándar.

Al igual que `cout`, `cin` está disponible al incluir `<iostream>`. Mientras `cout` usa `<<` para enviar algo hacia la pantalla, `cin` usa `>>` para tomar algo del teclado y guardarlo en una variable.

```cpp
int cantidad;

cout << "¿Cuántos créditos estás tomando? ";
cin >> cantidad;
```

La línea con `cout` se llama un **prompt**: un mensaje que le indica claramente a la persona qué debe escribir. No asumas que el usuario sabe qué dato espera el programa; cada `cin` debe tener un prompt útil antes.

Cuando la persona escribe, por ejemplo, `15` y presiona Enter, `cin` interpreta ese texto como un valor del tipo de la variable y lo guarda en `cantidad`.

| Parte | Qué ocurre en el ejemplo |
|---|---|
| `int cantidad;` | Se reserva una variable para un número entero. |
| `cout << ...` | Se muestra una pregunta en pantalla. |
| `cin >> cantidad;` | Se lee la respuesta y se guarda como `int`. |

### ¿Qué pasa si el tipo no coincide con lo que se escribió?

**El tipo importa.** Observa una situación concreta:

```cpp
int cantidad;

cout << "Escribe la cantidad de piezas: ";
cin >> cantidad;
```

Si la persona escribe `3.75`, `cin` puede leer la parte entera `3` y dejar `.75` pendiente en el **buffer de entrada**. El buffer es la secuencia de caracteres que el teclado ya entregó al programa, pero que una lectura todavía no ha consumido. No redondea a `4`, ni convierte mágicamente ese dato completo a un entero.

La parte pendiente importa mucho porque la próxima instrucción `cin` la encuentra antes de esperar una respuesta nueva. El resultado depende del tipo de la siguiente variable.

### Si la próxima lectura es un `double`

```cpp
int cantidad = 0;
double medida = 0.0;

cout << "Escribe una cantidad entera: ";
cin >> cantidad;

cout << "Escribe una medida decimal: ";
cin >> medida;
```

Si la persona responde `3.75` al primer prompt, ocurre esta secuencia:

| Momento | Variable | Valor | Buffer de entrada |
|---|---|---:|---|
| Después de escribir `3.75` | — | — | `3.75` |
| Después de `cin >> cantidad` | `cantidad` | `3` | `.75` |
| Después de `cin >> medida` | `medida` | `0.75` | vacío |

El segundo `cin` no espera que la persona escriba otra medida: toma automáticamente `.75` que quedó pendiente. La pantalla puede mostrar el segundo prompt, pero el programa parece "saltárselo" porque ya había texto disponible en el buffer.

### Si la próxima lectura es otro `int`

```cpp
int cantidad = 0;
int siguienteCantidad = 0;

cout << "Escribe una cantidad entera: ";
cin >> cantidad;

cout << "Escribe otra cantidad entera: ";
cin >> siguienteCantidad;
```

Con la entrada inicial `3.75`, el primer `cin` vuelve a guardar `3` y deja `.75`. Pero `.75` no es el inicio válido de un entero, así que el segundo `cin` falla. `siguienteCantidad` conserva el valor que ya tenía (`0` en este ejemplo) y el flujo de entrada queda en estado de error. Las lecturas posteriores con `cin >> ...` también fallarán hasta que el programa limpie ese estado y descarte la entrada problemática, una técnica que veremos cuando estudiemos validación de datos.

Este es un error común porque el mensaje de la segunda pregunta sí aparece, pero el programa no se detiene a esperar una respuesta. Cuando un programa "ignora" una entrada, revisa primero si una lectura anterior consumió solo parte de lo escrito.

Si el dato puede tener decimales, declara un `double` desde el principio:

```cpp
double temperatura;

cout << "Escribe la temperatura en grados Celsius: ";
cin >> temperatura;
cout << "La temperatura registrada es " << temperatura << " grados.\n";
```

### Conversión de entrada, conversión automática y casting

En programación usamos la palabra **conversión** para varios procesos relacionados, pero no son exactamente lo mismo:

| Proceso | Cuándo sucede | Ejemplo |
|---|---|---|
| Conversión de entrada | `cin` interpreta texto escrito por la persona. | Los caracteres `"27"` se guardan como el `int` `27`. |
| Conversión automática | C++ adapta tipos compatibles durante una expresión. | En `3 * 2.5`, el `3` se trata temporalmente como decimal. |
| **Casting** explícito | El programador pide una conversión concreta en código. | `static_cast<double>(puntos)` |

Un **cast** no cambia el tipo declarado de la variable original. Crea un valor convertido para la operación que se está realizando. Por ejemplo, si `puntos` es `int`, `static_cast<double>(puntos)` usa una versión decimal de ese valor; `puntos` sigue siendo `int`. Veremos el mecanismo y la razón de usarlo para evitar división entera en la Parte 3.

También puedes leer varias variables con una sola instrucción. La persona debe escribir los datos en el mismo orden, separados por espacios o por Enter:

```cpp
double largo, ancho;

cout << "Escribe el largo y el ancho del salón: ";
cin >> largo >> ancho;
```

Si se escribe `8.5 6`, `largo` recibe `8.5` y `ancho` recibe `6`. El orden de las variables es parte del contrato del programa.

**Para practicar por tu cuenta:**

¿Qué tipo de dato escogerías y qué prompt escribirías para pedir cada uno de estos datos?

1. La cantidad de libros prestados en una biblioteca.
2. El costo de una pieza electrónica.
3. La inicial de la sección de un estudiante.

<details>
<summary>Ver una posible respuesta</summary>

1. `int libros;` y `cout << "¿Cuántos libros prestaste? ";`
2. `double costo;` y `cout << "Escribe el costo de la pieza: $";`
3. `char seccion;` y `cout << "Escribe la inicial de tu sección: ";`

Hay otros prompts válidos si expresan con claridad el dato esperado.

</details>

---

## Parte 2 — Expresiones, precedencia y repaso aplicado (20 min)

Una **expresión** es cualquier combinación de literales, variables y operadores que produce un valor. Una variable sola es una expresión; `7.5` también lo es; `largo * ancho` es una expresión matemática.

```cpp
double area;
area = largo * ancho;
```

La computadora no interpreta álgebra como una persona. Debes escribir explícitamente cada multiplicación y traducir con cuidado los paréntesis.

| Matemática | C++ |
|---|---|
| área = largo × ancho | `area = largo * ancho;` |
| perímetro = 2(largo + ancho) | `perimetro = 2 * (largo + ancho);` |
| promedio = suma / cantidad | `promedio = suma / cantidad;` |
| pendiente = (y₂ − y₁) / (x₂ − x₁) | `pendiente = (y2 - y1) / (x2 - x1);` |

No existe un operador de exponenciación `^` para elevar números al cuadrado en C++. Ese símbolo se usa para otra operación que veremos mucho más adelante. Por ahora, un cuadrado se puede expresar multiplicando el valor por sí mismo: `lado * lado`. También veremos `pow` y `sqrt` más adelante en esta misma sesión.

### Precedencia y asociatividad

C++ sigue un orden de operaciones parecido al de matemáticas:

1. Paréntesis interiores primero.
2. Negación unaria, como `-valor`.
3. Multiplicación, división y residuo: `*`, `/`, `%`, de izquierda a derecha.
4. Suma y resta: `+`, `-`, de izquierda a derecha.

Observa la diferencia:

```cpp
int resultado1 = 2 + 2 * 2 - 2;       // 4
int resultado2 = (2 + 2) * 2 - 2;     // 6
int resultado3 = 2 + 2 * (2 - 2);     // 2
```

Los paréntesis no son solo para el compilador: también ayudan a otra persona a leer tu intención. Cuando una fórmula tenga varias operaciones, es preferible usar paréntesis aunque conozcas la precedencia.

### Repaso aplicado: división entera

En la Semana 3 conociste los operadores aritméticos, el módulo (`%`) y la división entera. Aquí los usaremos para leer expresiones completas y anticipar errores lógicos. Por ejemplo:

```cpp
int piezas = 7;
int cajas = 2;

cout << piezas / cajas << endl;
```

La salida es `3`, no `3.5`. Como ambos operandos son `int`, C++ hace **división entera**: elimina la parte decimal. La variable que recibe el resultado no cambia esta decisión; lo que decide la operación son los tipos de los valores a ambos lados de `/`.

```cpp
double promedio;
int puntos = 17;
int estudiantes = 4;

promedio = puntos / estudiantes;  // guarda 4.0, no 4.25
```

En la próxima parte veremos cómo corregirlo de forma intencional con `static_cast`. La idea importante no es memorizar otra vez la definición de `/`, sino identificar el tipo de los operandos **antes** de confiar en el resultado de una fórmula.

**Para practicar por tu cuenta:**

Calcula a mano el resultado de cada expresión antes de verificarlo en C++:

1. `18 / 5`
2. `18 % 5`
3. `4 + 3 * 5`
4. `(4 + 3) * 5`

<details>
<summary>Ver respuesta</summary>

1. `3` — la división es entera.
2. `3` — el residuo de 18 dividido entre 5.
3. `19` — primero `3 * 5`.
4. `35` — los paréntesis cambian el orden.

</details>

---

## Parte 3 — Conversión de tipos y `static_cast` (20 min)

En ocasiones una expresión mezcla tipos. C++ realiza conversiones automáticas para poder operar, pero conviene entenderlas porque pueden cambiar un resultado.

```cpp
int unidades = 3;
double precio = 2.50;
double total = unidades * precio;
```

Para multiplicar, C++ convierte temporalmente `unidades` a `double`. El resultado es `7.5`, que se guarda correctamente en `total`.

La conversión puede ser problemática en la dirección contraria:

```cpp
double medida = 9.8;
int medidaEntera = medida;
```

`medidaEntera` termina con `9`. Al pasar de `double` a `int`, se descarta la parte decimal; no se redondea automáticamente.

### Forzar una conversión intencionalmente

Para obtener un promedio decimal a partir de dos enteros, convierte uno de los operandos **antes** de dividir:

```cpp
int puntos = 17;
int estudiantes = 4;
double promedio;

promedio = static_cast<double>(puntos) / estudiantes;
cout << promedio << endl;  // 4.25
```

`static_cast<double>(puntos)` crea una versión temporal de `puntos` como `double`; no cambia el valor ni el tipo original de `puntos`. Ahora uno de los operandos es `double`, así que la división se hace con decimales.

El estilo antiguo `(double)puntos` también puede aparecer en código existente — de hecho, lo vieron en el Lab 2 al mostrar un `unsigned char` como número — pero a partir de ahora preferiremos `static_cast<tipo>(valor)` porque hace la intención más visible.

**Regla para recordar:** convierte antes de la operación cuyo resultado necesitas cambiar, no después.

```cpp
double incorrecto = static_cast<double>(17 / 4);  // 4.0: ya se perdió .25
double correcto = static_cast<double>(17) / 4;    // 4.25
```

### Overflow y underflow

Cada tipo puede guardar solo un rango limitado de valores. Si un resultado es mayor que el máximo que cabe, ocurre **overflow**; si es menor que el mínimo representable, ocurre **underflow**. El resultado puede depender del tipo y del sistema, por lo que no debemos diseñar programas que dependan de ese comportamiento.

Esto conecta con el Lab 2: un `unsigned char` solo tiene espacio para valores de 0 a 255. Al superar 255, el valor vuelve al inicio de su rango. La lección práctica es escoger tipos adecuados y revisar si una fórmula puede producir valores muy grandes.

**Para practicar por tu cuenta:**

¿Cuál de estas dos líneas calcula correctamente un promedio de 13 puntos entre 2 tareas? Explica por qué.

```cpp
double a = 13 / 2;
double b = static_cast<double>(13) / 2;
```

<details>
<summary>Ver respuesta</summary>

`b` calcula el promedio correctamente: vale `6.5`. En `a`, ambos operandos son enteros, por lo que `13 / 2` se calcula primero como `6`; después ese `6` se convierte a `double` y queda `6.0`.

</details>

---

## Parte 4 — Funciones matemáticas y la hipotenusa (15 min)

La biblioteca estándar incluye funciones que no tienen un operador simple. Para usarlas, incluimos `<cmath>`. Una que usaremos de inmediato es `sqrt`, que calcula una raíz cuadrada.

Para un triángulo rectángulo, el teorema de Pitágoras dice:

\[
h = \sqrt{a^2 + b^2}
\]

En C++, traducimos cada parte de la fórmula de manera explícita. Usamos `a * a` y `b * b` para los cuadrados, y `sqrt(...)` para la raíz:

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double catetoA, catetoB, hipotenusa;

    cout << "Escribe los dos catetos del triangulo: ";
    cin >> catetoA >> catetoB;

    hipotenusa = sqrt(catetoA * catetoA + catetoB * catetoB);

    cout << "La hipotenusa es " << hipotenusa << endl;
    return 0;
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

Un programa puede calcular correctamente y aun así comunicar mal su resultado. Por ejemplo, mostrar demasiados decimales para un precio distrae y parece poco profesional. Los manipuladores de `<iomanip>` permiten controlar el formato de `cout`.

```cpp
#include <iomanip>
```

Los tres manipuladores más útiles en este momento son:

| Manipulador | Efecto |
|---|---|
| `fixed` | Muestra números decimales en notación decimal fija. |
| `setprecision(n)` | Con `fixed`, muestra exactamente `n` dígitos después del punto decimal. |
| `showpoint` | Muestra el punto decimal aun cuando el valor no tenga fracción visible. |

```cpp
double costo = 7.5;
double total = 15.0;

cout << fixed << setprecision(2);
cout << "Costo: $" << costo << endl;
cout << "Total: $" << total << endl;
```

La salida es:

```
Costo: $7.50
Total: $15.00
```

`fixed` y `setprecision` permanecen activos en el flujo de salida hasta que se cambien. Por eso normalmente se colocan una vez, antes de imprimir una sección de resultados. Sin `fixed`, `setprecision(2)` significa dos dígitos significativos, no necesariamente dos decimales.

**Para practicar por tu cuenta:**

¿Qué incluye falta en este programa para que compile y muestre el promedio con tres decimales?

```cpp
#include <iostream>
using namespace std;

int main()
{
    double promedio = 91.375;
    cout << fixed << setprecision(3) << promedio << endl;
    return 0;
}
```

<details>
<summary>Ver respuesta</summary>

Falta `#include <iomanip>`, porque ahí se declara `setprecision`.

</details>

---

## Parte 6 — Asignación combinada y texto breve (10 min)

Hay una forma compacta de actualizar una variable usando el resultado que ya tiene:

```cpp
int total = 10;
total = total + 3;
```

Esto equivale a:

```cpp
total += 3;
```

Existen operadores combinados para las operaciones aritméticas que ya conocen:

| Forma larga | Forma combinada |
|---|---|
| `saldo = saldo + deposito;` | `saldo += deposito;` |
| `vidas = vidas - 1;` | `vidas -= 1;` |
| `total = total * 2;` | `total *= 2;` |
| `mitad = mitad / 2;` | `mitad /= 2;` |

No uses una forma combinada solo por hacer el código más corto. Úsala cuando conserve o aumente la claridad. Por ejemplo, `contador += 1;` expresa claramente que el contador aumenta una unidad.

También puedes asignar el mismo valor inicial a variables del mismo tipo:

```cpp
int errores = 0;
int advertencias = 0;
```

Aunque `errores = advertencias = 0;` es válido después de declarar ambas variables, para este curso preferiremos declaraciones claras en líneas separadas cuando los nombres representan ideas diferentes.

---

## Parte 7 — Trazar un programa a mano y encontrar errores lógicos (25 min)

Un programa puede compilar y correr sin producir la respuesta correcta. Eso es un **error lógico**. El compilador no sabe cuál era tu intención matemática; solo ejecuta exactamente las instrucciones que escribiste.

Una herramienta sencilla para encontrar estos errores es el **trazado a mano**. Consiste en actuar como la computadora: avanzar instrucción por instrucción y anotar cómo cambian las variables.

Examina este programa, que intenta calcular el precio final de varias libretas:

```cpp
int cantidad = 4;
double precioUnitario = 2.75;
double descuento = 0.10;

double subtotal = cantidad * precioUnitario;
double total = subtotal - descuento;
```

El código compila, pero el descuento se está tratando como si fuera diez centavos. Si `descuento` representa 10%, primero hay que calcular la cantidad descontada.

| Línea ejecutada | `cantidad` | `precioUnitario` | `subtotal` | `descuento` | `total` |
|---|---:|---:|---:|---:|---:|
| después de las declaraciones | 4 | 2.75 | — | 0.10 | — |
| `subtotal = ...` | 4 | 2.75 | 11.00 | 0.10 | — |
| `total = subtotal - descuento` | 4 | 2.75 | 11.00 | 0.10 | 10.90 |

El resultado esperado para 10% de descuento es `9.90`, no `10.90`. Una corrección posible es:

```cpp
double montoDescuento = subtotal * descuento;
double total = subtotal - montoDescuento;
```

### Método de trazado

1. Escribe los valores iniciales de todas las variables.
2. Lee una instrucción ejecutable a la vez, de arriba hacia abajo.
3. Calcula el lado derecho de una asignación antes de cambiar la variable del lado izquierdo.
4. Anota el nuevo valor en una tabla.
5. Compara el resultado final con un valor que puedas verificar a mano.

El trazado también permite detectar división entera. Por ejemplo:

```cpp
int totalPuntos = 25;
int tareas = 4;
double promedio = totalPuntos / tareas;
```

| Paso | `totalPuntos` | `tareas` | Expresión calculada | `promedio` |
|---|---:|---:|---:|---:|
| inicialización | 25 | 4 | — | — |
| asignación de `promedio` | 25 | 4 | `25 / 4` = `6` | 6.0 |

El tipo de `promedio` no recupera el `.25` que se perdió durante la división. La corrección es convertir uno de los operandos antes de dividir.

**Para practicar por tu cuenta:**

Traza el siguiente código y determina el valor final de `resultado`. Luego identifica el error lógico si la intención era calcular 20% de descuento sobre `50.0`.

```cpp
double precio = 50.0;
double tasaDescuento = 20;
double resultado = precio - tasaDescuento;
```

<details>
<summary>Ver respuesta</summary>

`resultado` vale `30.0`. El programa restó 20 dólares, no 20%. Una posible corrección es guardar la tasa como `0.20` y calcular primero `precio * tasaDescuento`.

</details>

---

## Parte 8 — Conectar entrada, proceso y salida (15 min)

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
| Proceso | tiempo = distancia / velocidad |
| Salida | tiempo estimado en horas, con dos decimales |

Un programa original que implementa ese diseño sería:

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double distancia, velocidad, tiempo;

    cout << "Escribe la distancia en kilometros: ";
    cin >> distancia;

    cout << "Escribe la velocidad en km/h: ";
    cin >> velocidad;

    tiempo = distancia / velocidad;

    cout << fixed << setprecision(2);
    cout << "Tiempo estimado: " << tiempo << " horas" << endl;

    return 0;
}
```

Este programa todavía no valida que la velocidad sea distinta de cero; la validación con estructuras de selección llegará en la Semana 5. Por ahora, el objetivo es reconocer con precisión qué es entrada, proceso y salida, y probar con valores sensatos.

**Para practicar por tu cuenta:**

Diseña las tres partes IPO para un programa que reciba el largo y ancho de una pared y calcule cuántos metros cuadrados se deben pintar. No escribas código todavía.

<details>
<summary>Ver una posible respuesta</summary>

- **Entrada:** largo y ancho de la pared, ambos como `double`.
- **Proceso:** área = largo × ancho.
- **Salida:** el área en metros cuadrados, posiblemente con dos decimales.

</details>

---

## Resumen de la sesión

- `cin >> variable;` lee un dato del teclado; un prompt claro con `cout` debe indicarle al usuario qué escribir.
- Las expresiones obedecen precedencia; los paréntesis hacen explícita la intención matemática.
- La división entre enteros trunca. `static_cast<double>(valor)` debe ocurrir antes de dividir si necesitas decimales.
- `<cmath>` da acceso a funciones como `sqrt`; `<iomanip>` permite usar `fixed` y `setprecision`.
- Un trazado a mano muestra cómo cambian las variables y ayuda a localizar errores lógicos que el compilador no detecta.
- Antes de programar, separa entrada, proceso y salida.

## Próxima sesión

**Lab 4 — Trazar expresiones y detectar errores lógicos** — van a comprobar a mano y en C++ los efectos de la precedencia, la división entera, el type casting, `sqrt`, y el formato de resultados.
