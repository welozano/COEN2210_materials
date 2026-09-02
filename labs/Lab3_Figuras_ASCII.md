# Lab 3 — Figuras Geométricas y Arte ASCII
## COEN 2210 — Introduction to Programming

**Basado en:** Semana 3 — Introduction to C++ (Gaddis, Capítulo 2)
**Duración:** 110 min
**Requisitos:** Labs 1 y 2 completados (Git básico + VS Code funcionando)

---

## Objetivos

Al finalizar este laboratorio, el estudiante podrá:
1. Usar `cout` y secuencias de escape para producir salida formateada, incluyendo arte ASCII propio.
2. Declarar constantes y variables con el tipo de dato apropiado según el problema.
3. Aplicar operadores aritméticos para resolver fórmulas geométricas (círculo, rectángulo, triángulo).
4. Repetir el flujo completo de carpeta → repo → commits → push desde VS Code, con atención específica a **dónde** se crea el repositorio.

---

## Parte 0 — Preparar la carpeta y el repositorio (10 min)

> ⚠️ **Este paso es el que más se presta a error — léelo con cuidado antes de hacer clic en nada.**

Ya tienes una carpeta padre de curso (la creaste en el Lab 1), algo como `COEN2210_intro_to_programming`, y dentro de ella, carpetas separadas para cada lab (`lab1-git`, `lab2-numeros`, etc.). **Cada lab es su propio repositorio independiente** — nunca conviertas la carpeta padre del curso en un repositorio.

> 🖱️ **Vas a usar VS Code y la terminal integrada.**

1. Abre VS Code.
2. `File → Open Folder...`
3. Navega hasta tu carpeta `COEN2210_intro_to_programming` — **pero no la selecciones a ella misma.** Entra a esa carpeta primero (haciendo doble clic para navegar adentro en el diálogo), y ahí mismo, antes de confirmar, vamos a crear la carpeta nueva del lab.

**Alternativa más segura (recomendada): crea la carpeta desde la terminal primero, y abre esa carpeta específica directamente.**

Abre una terminal (fuera de VS Code, o la terminal integrada si ya tienes abierta la carpeta padre) y navega hasta `COEN2210_intro_to_programming`:

```bash
cd COEN2210_intro_to_programming
mkdir lab3-figuras
```

**¿Qué hace esto?** Crea una carpeta nueva `lab3-figuras`, **hermana** de `lab1-git` y `lab2-numeros` — al mismo nivel, no una dentro de otra.

**Qué deberías ver:** si listas el contenido (`dir` o `ls`) de `COEN2210_intro_to_programming`, deberías ver algo como:
```
lab1-git/
lab1-git-clon/
lab2-numeros/
lab3-figuras/
```

4. Ahora sí, en VS Code: `File → Open Folder...` y selecciona específicamente **`lab3-figuras`** (no la carpeta padre `COEN2210_intro_to_programming`).

**Cómo saber si abriste la carpeta correcta:** mira el panel Explorer a la izquierda — el nombre en la parte superior debe decir `LAB3-FIGURAS`, no `COEN2210_INTRO_TO_PROGRAMMING`. Si ves el nombre de la carpeta padre ahí, cierra la carpeta (`File → Close Folder`) y repite el paso 4 seleccionando la carpeta correcta.

> **¿Por qué importa tanto esto?** Si inicializas el repositorio de Git en la carpeta padre por accidente, terminas con un solo repositorio gigante que incluye *todos* tus labs anteriores mezclados — imposible de separar después sin trabajo extra. Cada lab debe vivir en su propio repositorio, exactamente como hicimos en el Lab 1 y Lab 2.

5. Con `lab3-figuras` abierta como carpeta raíz en VS Code, abre el panel de Source Control (`Ctrl+Shift+G` / `Cmd+Shift+G`) y haz clic en **"Initialize Repository"**.

**Qué deberías ver:** el panel de Source Control pasa de mostrar un botón de inicializar a mostrar "No changes" o similar — confirma que ahora `lab3-figuras` es un repositorio Git válido.

---

## Parte A — `datos_personales.cpp`: cout y arte ASCII (30 min)

Crea el archivo `datos_personales.cpp` dentro de `lab3-figuras` (clic derecho en el Explorer → New File).

**Primero, repite el ejercicio de datos personales (similar al del Lab 1 de tu profesor anterior, pero ahora tú lo escribes desde cero):**

```cpp
// Programa que muestra informacion personal usando cout
// Nombre: [tu nombre aqui]

#include <iostream>
using namespace std;

int main()
{
    // Escribe aqui las lineas que muestran tu nombre, direccion,
    // ciudad/estado/codigo postal, y telefono, cada uno en su propia linea
    
    return 0;
}
```

**Requisito:** que haya **tres líneas en blanco** entre tu nombre y tu número de teléfono (usa `\n` para lograrlo, sin usar `endl` repetido).

Compila y corre desde la terminal integrada (`g++ datos_personales.cpp -o datos_personales`, luego `./datos_personales`).

**Qué deberías ver:** tu información impresa con las tres líneas en blanco en el lugar correcto.

**Ahora, arte ASCII propio:** usando solo instrucciones `cout` (como vimos en el ejemplo de la carita sonriente en la lecture), diseña **tu propia figura** de al menos 4 líneas de alto — puede ser una cara distinta, un objeto simple, o un patrón geométrico. No tiene que ser complejo — el objetivo es practicar cómo el espaciado y los caracteres dentro de un string controlan la salida visual.

Agrega esto al mismo archivo, después de tu información personal.

**Para practicar por tu cuenta:** una vez tengas tu figura funcionando, intenta hacer una segunda versión ligeramente distinta (por ejemplo, la misma cara pero con una expresión diferente) usando variables `string` para las piezas repetidas, en vez de escribir el `cout` completo de nuevo.

---

## Parte B — `figuras.cpp`: círculo, rectángulo, y triángulo (45 min)

Crea el archivo `figuras.cpp`. Este archivo va a crecer progresivamente — vamos a resolver tres figuras geométricas, una tras otra, en el mismo `main()`.

**Estructura inicial:**

```cpp
// Programa que calcula circunferencia/area de un circulo,
// area/perimetro de un rectangulo, y area de un triangulo
// Nombre: [tu nombre aqui]

#include <iostream>
using namespace std;

const double PI = 3.14159;
const double RADIO = 5.4;
const double LARGO = 8.0;
const double ANCHO = 3.0;
const double BASE = 6.0;
const double ALTURA = 4.0;

int main()
{
    // --- Circulo ---
    // Declara las variables necesarias y calcula circunferencia y area
    // circunferencia = 2 * PI * RADIO
    // area = PI * RADIO * RADIO


    // --- Rectangulo ---
    // Declara las variables necesarias y calcula area y perimetro
    // area = LARGO * ANCHO
    // perimetro = 2 * (LARGO + ANCHO)


    // --- Triangulo ---
    // Declara las variables necesarias y calcula el area
    // area = (BASE * ALTURA) / 2


    return 0;
}
```

**Instrucciones:**

1. **Círculo:** declara las variables (tipo `double`) para circunferencia y área, calcula ambas usando las constantes dadas, y muestra los resultados con un mensaje descriptivo (ej. `"La circunferencia del circulo es " << circunferencia`).
2. **Rectángulo:** mismo patrón — variables, cálculo, mensaje descriptivo para área y perímetro.
3. **Triángulo (nuevo):** la fórmula del área de un triángulo es:

   **área = (base × altura) / 2**

   Declara las variables necesarias, calcula el área usando `BASE` y `ALTURA`, y muéstrala con su propio mensaje descriptivo.

**Cuidado con un error común:** si divides `(BASE * ALTURA) / 2` y las variables son `double`, no hay problema — pero si en algún punto usas literales enteros para la división (como escribir `/ 2` en vez de `/ 2.0` sobre variables `int`), recuerda lo visto en la lecture de esta semana sobre división entera truncada. Aquí no debería pasar porque `BASE` y `ALTURA` ya son `double`, pero vale la pena que lo verifiques tú mismo revisando los tipos.

Compila y corre. **Qué deberías ver** (con los valores dados):
```
La circunferencia del circulo es 33.9332
El area del circulo es 91.6197
El area del rectangulo es 24
El perimetro del rectangulo es 22
El area del triangulo es 12
```

**Para practicar por tu cuenta:** agrega una cuarta figura al mismo archivo — un cuadrado, usando una sola constante `LADO` (ya que todos los lados son iguales). Calcula su área y perímetro.

---

## Cierre — Commit, push, y ejercicios adicionales (15 min)

> 🖱️ **Vas a usar el panel de Source Control de VS Code** (mismo flujo del Lab 2).

1. Stage ambos archivos (`+` junto a "Changes", o archivo por archivo si prefieres commits separados por concepto).
2. Escribe un mensaje descriptivo (ej. "Lab 3: datos personales, arte ASCII, y figuras geometricas").
3. Commit, luego **Publish Branch** (si es la primera vez en este repo) o **Sync Changes**.

**Qué deberías ver:** al revisar tu repositorio en GitHub, `lab3-figuras` aparece como un repo **separado** de `lab1-git` y `lab2-numeros`, con ambos archivos `.cpp` adentro.

**Ejercicios adicionales para practicar por tu cuenta (o de tarea si no alcanza el tiempo):**

1. En `figuras.cpp`, ¿qué pasaría si `BASE` y `ALTURA` fueran de tipo `int` en vez de `double`? Cambia los tipos, recompila, y observa si el resultado del área del triángulo cambia.

<details>
<summary>Ver respuesta</summary>

Si `BASE` y `ALTURA` son `int` con los valores dados (6 y 4), `BASE * ALTURA` = 24 (int), y `24 / 2` = 12 — en este caso particular el resultado **no cambia** porque 24 es divisible exactamente entre 2. Pero si cambiaras `ALTURA` a un valor que no diera un producto par (por ejemplo, `ALTURA = 5`), sí verías truncamiento: `6 * 5 = 30`, `30 / 2 = 15` (todavía exacto) — prueba con `BASE = 5, ALTURA = 4`: `20 / 2 = 10`, exacto también. El punto clave es que con enteros, **cualquier caso donde el producto no fuera divisible exactamente entre 2 sí truncaría** — vale la pena que pruebes valores impares para verlo en acción (ej. `BASE = 5, ALTURA = 3` → `15 / 2` = 7 en vez de 7.5).

</details>

2. Agrega un triángulo **equilátero** calculando su área con la fórmula alternativa (lado² × √3) / 4 — vas a necesitar `#include <cmath>` y la función `sqrt()`, que se ve formalmente la próxima semana, pero intenta investigarla por tu cuenta.

---

## Próxima sesión

**Semana 4 — Basic programming concepts and elements** (Capítulo 3: `cin`, expresiones matemáticas, type casting) — el **Lab 4** va a usar `cin` para leer datos del usuario en vez de solo constantes fijas, y van a formatear la salida con `setprecision`.
