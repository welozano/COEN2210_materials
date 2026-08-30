# Semana 3 — Introduction to C++
## COEN 2210 — Introduction to Programming

**Basado en:** Gaddis, *Starting Out with C++: From Control Structures through Objects* — Capítulo 2, "Introduction to C++"

**Duración:** 3 horas (lectura)
**Precede a:** Lab 3 — compilar/correr programas, leer errores del compilador, `cin`/`cout` básico

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:
1. Explicar la estructura de un programa C++ línea por línea.
2. Usar `cout` para mostrar texto y secuencias de escape.
3. Declarar variables con nombres válidos y el tipo de dato apropiado.
4. Diferenciar entre los tipos de datos principales de C++ y cuándo usar cada uno.
5. Usar operadores aritméticos, comentarios, y constantes nombradas.

---

## Parte 1 — Anatomía de un programa C++ (20 min)

Vamos a examinar un programa completo, línea por línea, para entender qué hace cada parte.

```cpp
// A simple C++ program
#include <iostream>
using namespace std;

int main()
{
    cout << "Programming is great fun!";
    return 0;
}
```

**Línea por línea:**

- **`// A simple C++ program`** — un **comentario**. El compilador ignora todo desde `//` hasta el final de la línea. No afecta cómo corre el programa, es solo para que las personas que lean el código entiendan qué hace.
- **`#include <iostream>`** — una **directiva de preprocesador** (empieza con `#`, no es una instrucción de C++ en sí). Le dice al preprocesador "inserta aquí el contenido del archivo `iostream`" — ese archivo contiene todo lo necesario para poder usar `cout` (mostrar texto) y `cin` (leer datos del teclado, lo veremos en la Semana 4). Sin este `#include`, el compilador no sabría qué es `cout`.
- **`using namespace std;`** — C++ organiza nombres de variables, funciones, y objetos dentro de "espacios de nombres" (namespaces) para evitar conflictos entre nombres. Esta línea le dice al programa "voy a usar los nombres que pertenecen al namespace `std`" (donde vive `cout`, entre otros), así no hay que escribir el nombre completo cada vez.
- **`int main()`** — todo programa C++ debe tener una función llamada `main` — es el punto donde arranca la ejecución. El `int` antes indica que la función va a devolver un número entero al terminar (ver `return 0;` abajo).
- **`{` y `}`** — las llaves marcan el inicio y el final del cuerpo de la función. Todo lo que `main` hace va entre estas dos llaves.
- **`cout << "Programming is great fun!";`** — envía el texto entre comillas hacia `cout`, que lo muestra en pantalla. El `;` al final marca el fin de la instrucción — **toda instrucción en C++ termina en punto y coma** (excepto las directivas de preprocesador, como `#include`, que nunca lo llevan).
- **`return 0;`** — termina la función `main`, devolviendo el valor `0`. Por convención, `0` significa "el programa terminó sin errores".

**Advertencia importante:** nunca pongas punto y coma después de `#include`. Como no es una instrucción de C++ sino una directiva de preprocesador, un `;` ahí puede causar un error de compilación.

**Para practicar por tu cuenta:**

Este programa tiene las líneas desordenadas. Reordénalas para que compile y muestre `Success` tres veces:

```
cout << "Success\n";
cout << " Success\n\n";
int main()
cout << "Success";
using namespace std;
// It's a mad, mad program
#include <iostream>
cout << "Success\n";
{
return 0;
```

<details>
<summary>Ver respuesta</summary>

```cpp
// It's a mad, mad program
#include <iostream>
using namespace std;

int main()
{
    cout << "Success\n";
    cout << " Success\n\n";
    cout << "Success";
    return 0;
}
```

</details>

---

## Parte 2 — El objeto `cout` (15 min)

`cout` (se lee "C-out", de *console output*) es un objeto que envía datos hacia la pantalla, usando el operador `<<` ("operador de inserción").

```cpp
cout << "Hola" << " " << "mundo" << endl;
```

Puedes encadenar varios `<<` en una sola instrucción — cada uno agrega algo más a la salida.

**Secuencias de escape:** dentro de un string, ciertas combinaciones que empiezan con `\` tienen un significado especial:

| Secuencia | Qué hace |
|---|---|
| `\n` | Salto de línea |
| `\t` | Tabulación |
| `\\` | Una sola barra invertida literal |
| `\"` | Comillas dobles literales dentro del string |

```cpp
cout << "One\nTwo\nThree\n";
```

**Qué mostraría esto:** cada `\n` cuenta como **un solo carácter** (aunque se escriba con dos símbolos), y produce:
```
One
Two
Three
```

**`endl` vs. `\n`:** ambos producen un salto de línea. `endl` es un manipulador de flujo (lo vimos con `hex`/`oct` en la Semana 2); `\n` es parte del string mismo. Para este curso, cualquiera de los dos es válido — vas a ver ambos usados en el libro y en el código de otros programadores.

**Para practicar por tu cuenta:**

Modifica este programa para que imprima dos líneas en blanco entre cada línea de texto:
```cpp
#include <iostream>
using namespace std;
int main()
{
    cout << "Two mandolins like creatures in the";
    cout << "dark";
    cout << "Creating the agony of ecstasy.";
    cout << " - George Barker";
    return 0;
}
```

<details>
<summary>Ver respuesta</summary>

```cpp
#include <iostream>
using namespace std;
int main()
{
    cout << "Two mandolins like creatures in the" << "\n\n\n";
    cout << "dark" << "\n\n\n";
    cout << "Creating the agony of ecstasy." << "\n\n\n";
    cout << " - George Barker";
    return 0;
}
```
(Dos líneas en blanco requieren tres `\n`: uno para terminar la línea actual, y dos más para las líneas vacías.)

</details>

---

## Parte 3 — Variables y literales (25 min)

Una **variable** es un espacio con nombre en la memoria donde se guarda un valor que puede cambiar durante la ejecución del programa. Un **literal** es un valor escrito directamente en el código (como `72`, `'A'`, o `"Hola"`).

**Declarar una variable:**
```cpp
int edad;
edad = 20;
```

**Reglas para nombres de variables (identificadores) válidos en C++:**
1. Solo pueden contener letras, dígitos, y guión bajo (`_`).
2. No pueden empezar con un dígito.
3. No pueden ser una palabra reservada del lenguaje (`int`, `return`, etc.).
4. C++ **distingue mayúsculas de minúsculas** — `Sales` y `sales` son variables distintas.
5. No pueden contener espacios ni símbolos como `&`, `%`, `-`.

**Para practicar por tu cuenta:**

¿Cuáles de estos son nombres de variable **inválidos**, y por qué?
```
X
99bottles
july97
theSalesFigureForFiscalYear98
r&d
grade_report
```

<details>
<summary>Ver respuesta</summary>

- `99bottles` — inválido, empieza con un dígito.
- `r&d` — inválido, contiene el símbolo `&`.
- El resto (`X`, `july97`, `theSalesFigureForFiscalYear98`, `grade_report`) son válidos.

</details>

---

## Parte 4 — Panorama de tipos de datos (25 min)

C++ tiene varios tipos de datos — en esta sesión vemos un **panorama comparativo** de cuándo usar cada uno; el detalle fino de cada tipo lo van a practicar en el Lab 3.

### Enteros

| Tipo | Tamaño típico | Rango típico |
|---|---|---|
| `short int` | 2 bytes | -32,768 a 32,767 |
| `int` | 4 bytes | ~-2,147 millones a ~2,147 millones |
| `long int` | 4 bytes | igual que `int` en muchos sistemas |
| `long long int` | 8 bytes | rango mucho mayor |
| `unsigned int` | 4 bytes | 0 a ~4,294 millones (sin negativos) |

**¿Cuándo usar `unsigned`?** Cuando sabes que el valor nunca va a ser negativo (por ejemplo, una edad o un conteo de artículos) — ganas rango positivo a cambio de perder la posibilidad de representar negativos. Esto conecta directamente con lo que vimos en la Semana 2 sobre cómo el tamaño en bits determina el rango representable.

### `char` — un solo carácter

```cpp
char letra = 'A';
```

Los literales de carácter van en **comillas simples**, no dobles — `'A'` es un `char`, `"A"` es un `string` (son tipos distintos, no se pueden mezclar). Internamente, un `char` es en realidad un número entero pequeño (1 byte) — cada carácter tiene un código numérico asignado (el estándar más común es ASCII), y por eso pudimos usar `(int)` para ver el valor numérico de un `char` en el Lab 2.

### `string` — texto

```cpp
string nombre = "Ana";
```

A diferencia de `char`, un `string` puede contener múltiples caracteres, y sus literales van en **comillas dobles**.

### Punto flotante — números con decimales

| Tipo | Precisión |
|---|---|
| `float` | precisión simple |
| `double` | precisión doble (el más usado por defecto) |
| `long double` | mayor precisión aún |

```cpp
double precio = 19.99;
```

### `bool` — verdadero/falso

```cpp
bool activo = true;
```

Internamente, `true` se representa como `1` y `false` como `0` — vamos a usar `bool` extensamente cuando lleguemos a estructuras de selección (`if`) en la Semana 5.

**Para practicar por tu cuenta:**

¿Qué tipo de dato usarías para cada uno de estos casos?
1. La cantidad de estudiantes en un salón.
2. El promedio de notas de un estudiante (con decimales).
3. La inicial del segundo nombre de una persona.
4. Si un estudiante aprobó o no un examen.

<details>
<summary>Ver respuesta</summary>

1. `int` (o `unsigned int`, ya que no hay estudiantes negativos).
2. `double`.
3. `char`.
4. `bool`.

</details>

---

## Parte 5 — `sizeof` y asignación/inicialización (15 min)

**El operador `sizeof`** te dice cuántos bytes ocupa un tipo de dato en tu sistema específico:

```cpp
cout << "El tamano de un entero es " << sizeof(int);
```

Esto conecta con la Semana 2 — recuerda que `char` = 1 byte, `int` normalmente 4 bytes = 32 bits.

**Diferencia entre declarar e inicializar:**

```cpp
int contador;        // declaración, sin valor inicial (contiene "basura")
contador = 0;         // asignación, ahora sí tiene un valor

int total = 0;        // declaración + inicialización en una sola línea
```

**Buena práctica:** siempre inicializa tus variables al declararlas — una variable sin inicializar contiene lo que haya quedado en esa dirección de memoria de antes, lo cual puede causar comportamiento impredecible.

---

## Parte 6 — Scope (introducción breve) (10 min)

El **scope** (alcance) de una variable es la parte del programa donde esa variable existe y puede usarse. La regla principal por ahora: **una variable no puede usarse antes de haber sido declarada.**

```cpp
int main()
{
    cout << valor;      // ERROR: valor todavía no existe
    int valor = 100;
    return 0;
}
```

El compilador lee de arriba hacia abajo — si encuentra un nombre que todavía no se ha declarado, marca error. Vamos a retomar este concepto con más profundidad más adelante en el curso, cuando trabajemos con funciones.

---

## Parte 7 — Operadores aritméticos (15 min)

| Operador | Operación |
|---|---|
| `+` | Suma |
| `-` | Resta (o negación, como operador unario) |
| `*` | Multiplicación |
| `/` | División |
| `%` | Módulo (residuo de una división entera) |

**Cuidado con la división entera:** si divides dos `int`, el resultado se trunca (se descarta la parte decimal), aunque lo guardes en una variable `double`:

```cpp
double resultado;
resultado = 15 / 6;    // resultado = 2.0, no 2.5!
```

Para obtener un resultado con decimales, al menos uno de los operandos debe ser de tipo flotante:
```cpp
resultado = 15.0 / 6;  // resultado = 2.5
```

Esto va a ser importante para el Lab 3 — es un error muy común entre estudiantes nuevos.

**Para practicar por tu cuenta:**

¿Qué valor queda almacenado en `resultado` en cada caso?
```cpp
int a = 7, b = 2;
double resultado;
resultado = a / b;
```

<details>
<summary>Ver respuesta</summary>

`resultado` = **3.0**, no 3.5 — porque `a` y `b` son ambos `int`, la división ya se trunca a `3` antes de asignarse a `resultado` (que es `double`).

</details>

---

## Parte 8 — Comentarios y constantes nombradas (15 min)

**Comentarios de una línea:** `//` — todo lo que sigue en esa línea es ignorado por el compilador.

```cpp
// Este programa calcula el area de un circulo
```

**Por qué importan los comentarios:** aunque no afectan cómo corre el programa, son esenciales para que tú (o cualquier otra persona) entienda el código semanas o meses después. Un programa de miles de líneas sin comentarios es mucho más difícil de mantener o corregir.

**Constantes nombradas** — valores que no deben cambiar durante la ejecución:

```cpp
const double PI = 3.14159;
```

**¿Por qué usar `const` en vez de escribir el número directamente cada vez?** Si el valor aparece en muchos lugares del programa y necesitas cambiarlo, solo lo actualizas en un lugar. Además, si accidentalmente intentas reasignar una variable `const`, el compilador te va a dar un error — protegiéndote de modificar algo que no debería cambiar.

---

## Parte 9 — Estilo de programación (10 min)

Buenas prácticas que vamos a exigir en labs y en el proyecto desde ahora:

- **Nombres de variables descriptivos** — `totalVentas` es mejor que `tv` o `x`.
- **Indentación consistente** — el código dentro de `{ }` debe estar alineado, facilita ver la estructura del programa de un vistazo.
- **Comentarios donde el código no es obvio** — no hace falta comentar cada línea, pero sí las decisiones no evidentes.
- **Una instrucción por línea** — evita amontonar varias instrucciones separadas por `;` en la misma línea, aunque C++ lo permita.

---

## Resumen de la sesión

- Todo programa C++ tiene una estructura fija: `#include`, `using namespace std;`, `int main() { ... return 0; }`.
- `cout` envía datos a pantalla; las secuencias de escape (`\n`, `\t`) controlan formato dentro de un string.
- Los identificadores tienen reglas estrictas de nomenclatura, y C++ distingue mayúsculas/minúsculas.
- Cada tipo de dato tiene un propósito: enteros para conteos, `double` para decimales, `char`/`string` para texto, `bool` para verdadero/falso.
- La división entre dos enteros trunca el resultado — un error común a evitar.

## Próxima sesión

**Lab 3** — van a compilar y correr programas propios, aprender a leer e interpretar errores del compilador (muchos de los cuales van a venir de los temas de hoy: `;` faltante, tipos de dato incorrectos, variables no declaradas), y usar `cin` para leer datos del usuario por primera vez.
