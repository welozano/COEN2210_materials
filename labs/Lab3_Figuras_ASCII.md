# Lab 3 — Figuras Geométricas y Arte ASCII
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
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

## Formato de encabezado (a partir de este lab)

A partir de hoy, **todo archivo `.cpp` que entregues debe empezar con este encabezado**, con los campos llenos:

```cpp
/*
 * Curso: COEN 2210 - Introduction to Programming
 * Nombre: [Tu Nombre Completo]
 * Lab: 3 - Figuras Geometricas y Arte ASCII
 * Descripcion: [Que hace este programa, 1-2 lineas]
 * Fecha de entrega: [Fecha]
 */
```

Es una versión simplificada de los headers que vas a ver en código profesional real — identifica qué es el archivo, quién lo escribió, y cuándo, sin campos que no aplican todavía a este nivel del curso (versión, licencia, dependencias). El starter code de cada archivo de este lab ya lo trae — solo llena los campos entre corchetes.

> ⚠️ **Recordatorio:** actualiza el encabezado en **cada uno** de los archivos `.cpp` que entregues este lab (`datos_personales.cpp` y `figuras.cpp`) — no solo en el primero. El campo `Descripcion` debe reflejar lo que hace *ese archivo específico*, no ser copiado igual entre ambos.

---

## Parte 0 — Preparar la carpeta y el repositorio (10 min)

> ⚠️ **Este paso es el que más se presta a error — léelo con cuidado antes de hacer clic en nada.**

Ya tienes una carpeta padre de curso (la creaste en el Lab 1), algo como `COEN2210` o `COEN2210_intro_to_programming` — el nombre exacto depende de lo que tú le hayas puesto, y dentro de ella, carpetas separadas para cada lab (`lab1-git`, `lab2-numeros`, etc.). **Cada lab es su propio repositorio independiente** — nunca conviertas la carpeta padre del curso en un repositorio.

> 🖱️ **Vas a usar VS Code.**

1. Abre VS Code.
2. `File → Open Folder...`
3. Navega hasta tu carpeta `COEN2210` o `COEN2210_intro_to_programming` (dependiendo del nombre que le diste en labs anteriores) — **pero no la selecciones a ella misma.** Entra a esa carpeta primero (haciendo doble clic para navegar adentro en el diálogo).
4. Dentro del mismo diálogo, crea una carpeta nueva llamada `lab3-figuras` (la mayoría de los diálogos de "Open Folder" tienen un botón o clic derecho para "Nueva carpeta") — **hermana** de `lab1-git` y `lab2-numeros`, al mismo nivel, no una dentro de otra.
5. Selecciona esa carpeta `lab3-figuras` recién creada (entra a ella) y confirma con **Open** / **Select Folder**.

**Cómo saber si abriste la carpeta correcta:** mira el panel Explorer a la izquierda en VS Code — el nombre en la parte superior debe decir `LAB3-FIGURAS`, no `COEN2210_INTRO_TO_PROGRAMMING`. Si ves el nombre de la carpeta padre ahí, cierra la carpeta (`File → Close Folder`) y repite los pasos 2-5 con más cuidado.

> **¿Por qué importa tanto esto?** Si inicializas el repositorio de Git en la carpeta padre por accidente, terminas con un solo repositorio gigante que incluye *todos* tus labs anteriores mezclados — imposible de separar después sin trabajo extra. Cada lab debe vivir en su propio repositorio, exactamente como hicimos en el Lab 1 y Lab 2.

5. Con `lab3-figuras` abierta como carpeta raíz en VS Code, abre el panel de Source Control (`Ctrl+Shift+G` / `Cmd+Shift+G`) y haz clic en **"Initialize Repository"**.

**Qué deberías ver:** el panel de Source Control pasa de mostrar un botón de inicializar a mostrar "No changes" o similar — confirma que ahora `lab3-figuras` es un repositorio Git válido.

---

## Parte A — `datos_personales.cpp`: cout y arte ASCII (35 min)

Crea el archivo `datos_personales.cpp` dentro de `lab3-figuras` (clic derecho en el Explorer → New File). **Todo lo de esta Parte A — datos personales y arte ASCII — va en este mismo archivo**, uno después del otro.

**Primero, información personal con `cout`:**

```cpp
/*
 * Curso: COEN 2210 - Introduction to Programming
 * Nombre: [Tu Nombre Completo]
 * Lab: 3 - Figuras Geometricas y Arte ASCII
 * Descripcion: [Que hace este programa, 1-2 lineas]
 * Fecha de entrega: [Fecha]
 */

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

> ⚠️ **Privacidad:** no uses tu información personal real. Usa datos inventados (nombre, dirección, y teléfono ficticios) — el ejercicio evalúa el uso de `cout` y secuencias de escape, no requiere datos verdaderos.

**Ejemplo de output esperado** (con datos ficticios — el tuyo tendrá tu nombre inventado, no este):
```
Juan Perez
Calle Ficticia 123
San Juan, PR 00926



787-555-0100
```

Compila y corre desde la terminal integrada (`g++ datos_personales.cpp -o datos_personales`, luego `./datos_personales`).

**Qué deberías ver:** tu información (ficticia) impresa con las tres líneas en blanco en el lugar correcto, como en el ejemplo de arriba.

---

**Ahora, arte ASCII — en el mismo archivo, después de los datos personales.**

Con solo instrucciones `cout` y secuencias de escape, se pueden dibujar figuras simples usando caracteres de texto. Aquí un ejemplo de una carita sonriente:

```cpp
cout << "\n\n";
cout << "   ^     ^ \n";
cout << "      *    \n";
cout << "   \\___/   \n";
```

**Nota sobre el `\\`:** para mostrar una sola barra invertida `\` en pantalla, hay que escribirla como `\\` dentro del string (secuencia de escape, vista en la lecture de esta semana) — una sola `\` sola se interpretaría como el inicio de otra secuencia de escape.

Agrega este ejemplo a tu archivo, **justo después de las líneas de tu información personal** (mismo archivo, mismo `main()`), cómpialo, y corre de nuevo.

**Ejemplo de output esperado completo** (datos personales + carita, todo en una sola ejecución del programa):
```
Juan Perez
Calle Ficticia 123
San Juan, PR 00926



787-555-0100

   ^     ^ 
      *    
   \___/   
```

**Ahora, crea tus propias figuras** (en el mismo archivo, después de la carita de ejemplo):

1. **Tu propia figura #1:** diseña **tu propia variación** de la carita de ejemplo — cambia la expresión (ojos distintos, boca distinta), usando el mismo patrón de `cout` con espacios y caracteres.
2. **Tu propia figura #2:** diseña una **segunda figura completamente distinta** a la carita — no una variación, algo nuevo (un objeto simple, un patrón geométrico, un animal simplificado), de al menos 4 líneas de alto.

Compila y corre después de agregar cada una, para confirmar que se ven como esperas.

**Esto es lo que debes entregar (obligatorio, no es opcional ni de tarea):** la carita de ejemplo + tus 2 figuras propias, las tres en `datos_personales.cpp`, después de tus datos personales, y todas deben aparecer al correr el programa una sola vez.

**Para practicar por tu cuenta (esto sí es opcional, no se entrega):** una vez tengas tus figuras funcionando, intenta hacer una versión adicional usando variables `string` para las piezas repetidas, en vez de escribir el `cout` completo de nuevo.

---

## Parte B — `figuras.cpp`: círculo, rectángulo, triángulo, y cuadrado (55 min)

Crea el archivo `figuras.cpp`. Este archivo va a crecer progresivamente — vamos a resolver **cuatro** figuras geométricas, una tras otra, en el mismo `main()`.

**Fórmulas a implementar:**

| Figura | Fórmula |
|---|---|
| Círculo | circunferencia = 2 × π × radio &nbsp;&nbsp;&nbsp; área = π × radio² |
| Rectángulo | área = largo × ancho &nbsp;&nbsp;&nbsp; perímetro = 2 × (largo + ancho) |
| Triángulo | área = (base × altura) / 2 |
| Cuadrado | área = lado² &nbsp;&nbsp;&nbsp; perímetro = 4 × lado |

**Estructura inicial — el círculo ya está resuelto como ejemplo; el resto lo implementas tú siguiendo el mismo patrón:**

```cpp
/*
 * Curso: COEN 2210 - Introduction to Programming
 * Nombre: [Tu Nombre Completo]
 * Lab: 3 - Figuras Geometricas y Arte ASCII
 * Descripcion: [Que hace este programa, 1-2 lineas]
 * Fecha de entrega: [Fecha]
 */

#include <iostream>
using namespace std;

const double PI = 3.14159;
const double RADIO = 5.4;
const double LARGO = 8.0;
const double ANCHO = 3.0;
const double BASE = 6.0;
const double ALTURA = 4.0;
const double LADO = 7.0;

int main()
{
    // --- Circulo (circunferencia ya resuelta como ejemplo) ---
    double circunferencia;
    circunferencia = 2 * PI * RADIO;
    cout << "La circunferencia del circulo es " << circunferencia << endl;

    // TODO: calcula tambien el area del circulo, usando la formula
    // de la tabla de arriba, y muestrala con cout


    // --- Rectangulo ---
    // TODO: declara las variables necesarias, calcula area y perimetro
    // usando la formula de la tabla de arriba, y muestralos con cout


    // --- Triangulo ---
    // TODO: declara las variables necesarias, calcula el area
    // usando la formula de la tabla de arriba, y muestrala con cout


    // --- Cuadrado ---
    // TODO: declara las variables necesarias, calcula area y perimetro
    // usando la formula de la tabla de arriba, y muestralos con cout


    return 0;
}
```

**Instrucciones:**

1. **Círculo:** la circunferencia ya está resuelta arriba como ejemplo del patrón a seguir (declarar variable → calcular con la fórmula → mostrar con `cout` y un mensaje descriptivo). Tú completas el **área**, usando el mismo patrón.
2. **Rectángulo:** implementa tú mismo el mismo patrón, usando la fórmula de la tabla.
3. **Triángulo:** implementa tú mismo el mismo patrón, usando la fórmula de la tabla.
4. **Cuadrado:** implementa tú mismo el mismo patrón, usando la fórmula de la tabla.

**Cuidado con un error común:** si divides `(BASE * ALTURA) / 2` y las variables son `double`, no hay problema — pero si en algún punto usas literales enteros para la división (como escribir `/ 2` en vez de `/ 2.0` sobre variables `int`), recuerda lo visto en la lecture de esta semana sobre división entera truncada. Aquí no debería pasar porque `BASE` y `ALTURA` ya son `double`, pero vale la pena que lo verifiques tú mismo revisando los tipos.

Compila y corre. **Qué deberías ver** (con los valores dados):
```
La circunferencia del circulo es 33.9332
El area del circulo es 91.6197
El area del rectangulo es 24
El perimetro del rectangulo es 22
El area del triangulo es 12
El area del cuadrado es 49
El perimetro del cuadrado es 28
```

**Esto es lo que debes entregar (obligatorio):** `figuras.cpp` con las cuatro figuras completas (círculo, rectángulo, triángulo, cuadrado), produciendo un output como el de arriba al correr el programa una sola vez.

**Para practicar por tu cuenta (opcional, no se entrega):** agrega un triángulo **equilátero** calculando su área con la fórmula alternativa (lado² × √3) / 4 — vas a necesitar `#include <cmath>` y la función `sqrt()`, que se ve formalmente la próxima semana, pero intenta investigarla por tu cuenta.

---

## Cierre — Commit, push, y ejercicios adicionales (10 min)

Con `datos_personales.cpp` y `figuras.cpp` completos y guardados, es momento de subir tu trabajo a GitHub.

> 🖱️ **Vas a usar el panel de Source Control de VS Code** (mismo flujo del Lab 2).

1. Stage ambos archivos (`+` junto a "Changes", o archivo por archivo si prefieres commits separados por concepto).
2. Escribe un mensaje descriptivo (ej. "Lab 3: datos personales, arte ASCII, y figuras geometricas").
3. Commit, luego **Publish Branch** (si es la primera vez en este repo) o **Sync Changes**.

**Qué deberías ver:** al revisar tu repositorio en GitHub, `lab3-figuras` aparece como un repo **separado** de `lab1-git` y `lab2-numeros`, con ambos archivos `.cpp` adentro (encabezados actualizados incluidos).

**Ejercicio adicional para practicar por tu cuenta (o de tarea si no alcanza el tiempo):**

En `figuras.cpp`, ¿qué pasaría si `BASE` y `ALTURA` fueran de tipo `int` en vez de `double`? Cambia los tipos, recompila, y observa si el resultado del área del triángulo cambia.

<details>
<summary>Ver respuesta</summary>

Si `BASE` y `ALTURA` son `int` con los valores dados (6 y 4), `BASE * ALTURA` = 24 (int), y `24 / 2` = 12 — en este caso particular el resultado **no cambia** porque 24 es divisible exactamente entre 2. Pero si cambiaras `ALTURA` a un valor que no diera un producto par (por ejemplo, `ALTURA = 5`), sí verías truncamiento: `6 * 5 = 30`, `30 / 2 = 15` (todavía exacto) — prueba con `BASE = 5, ALTURA = 4`: `20 / 2 = 10`, exacto también. El punto clave es que con enteros, **cualquier caso donde el producto no fuera divisible exactamente entre 2 sí truncaría** — vale la pena que pruebes valores impares para verlo en acción (ej. `BASE = 5, ALTURA = 3` → `15 / 2` = 7 en vez de 7.5).

</details>

---

## Próxima sesión

**Semana 4 — Basic programming concepts and elements** (Capítulo 3: `cin`, expresiones matemáticas, type casting) — el **Lab 4** va a usar `cin` para leer datos del usuario en vez de solo constantes fijas, y van a formatear la salida con `setprecision`.
