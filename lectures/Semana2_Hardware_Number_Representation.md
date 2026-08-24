# Semana 2 — Hardware & Number Representation
## COEN 2210 — Introduction to Programming

**Duración:** 3 horas (lectura)
**Precede a:** Lab 2 — ejercicios de conversión binario/hex/decimal (con Git desde el IDE)

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:
1. Explicar por qué las computadoras representan información en binario.
2. Convertir números entre binario, octal, decimal, y hexadecimal.
3. Relacionar bits y bytes con el tamaño de los tipos de datos en C++.
4. Leer y escribir literales hexadecimales en C++.

---

## Parte 1 — ¿Por qué binario? (30 min)

A nivel físico, una computadora es un conjunto masivo de interruptores electrónicos (transistores) que solo tienen dos estados posibles: **encendido** o **apagado**. No existe un estado intermedio confiable a esa escala — por eso toda la información, sin excepción (números, texto, imágenes, sonido, instrucciones de programa), termina representada como secuencias de **1s y 0s**.

**Analogía del interruptor de luz:** piensa en un interruptor de luz normal — está encendido o apagado, no hay "medio encendido" de forma confiable. Ahora imagina millones de esos interruptores cambiando de estado miles de millones de veces por segundo, sin margen de error. Un sistema de solo dos estados es mucho más fácil de mantener confiable a esa velocidad que uno que tuviera que distinguir, digamos, 10 niveles distintos de voltaje (uno por cada dígito decimal) — la diferencia entre esos niveles sería tan pequeña que el ruido eléctrico normal causaría errores constantemente.

**Nota histórica:** no fue obvio desde el principio que binario era la única opción. Algunas de las primeras computadoras (como el ENIAC, 1945) en realidad operaban internamente en **decimal**, usando circuitos mucho más complejos para representar los 10 dígitos. Con el tiempo, el diseño binario ganó porque simplifica enormemente el hardware (circuitos más simples, más baratos, más confiables) — un principio que sigue siendo válido hoy.

- **Bit** (*binary digit*) — la unidad más pequeña de información: un solo 1 o 0.
- **Byte** — un grupo de 8 bits. Es la unidad estándar para medir tamaño de datos (`char` en C++ ocupa 1 byte).

**Conexión con hardware:** cuando lleguen a cursos de sistemas embebidos, van a manipular directamente registros de memoria y puertos de entrada/salida a nivel de bits — entender esta representación ahora es la base de eso.

**Para discutir en clase (sin respuesta única correcta):**
1. Fuera de las computadoras, ¿qué otros sistemas de comunicación humanos usan solo dos estados o señales? (Piensa en código Morse, semáforos, señales de humo.)
2. Si tuvieras que diseñar un sistema de conteo usando solo velas encendidas/apagadas en vez de dígitos escritos, ¿cómo representarías el número 13?

---

## Parte 2 — Sistema binario (base 2) (30 min)

El sistema decimal (el que usamos normalmente) es base 10 — cada posición vale una potencia de 10. El binario es base 2 — cada posición vale una potencia de 2.

**Ejemplo — convertir binario a decimal:**

```
1 0 1 1  (binario)
```

| Posición | 2³ = 8 | 2² = 4 | 2¹ = 2 | 2⁰ = 1 |
|---|---|---|---|---|
| Bit | 1 | 0 | 1 | 1 |
| Valor | 8 | 0 | 2 | 1 |

**Suma:** 8 + 0 + 2 + 1 = **11** en decimal.

**Ejemplo — convertir decimal a binario (método de divisiones sucesivas entre 2):**

Convertir 13 a binario:

```
13 ÷ 2 = 6  residuo 1
 6 ÷ 2 = 3  residuo 0
 3 ÷ 2 = 1  residuo 1
 1 ÷ 2 = 0  residuo 1
```

Leyendo los residuos de abajo hacia arriba: **1101** en binario.

**Verificación:** 8+4+0+1 = 13 ✓

**Ejercicio en clase:** convertir 25 a binario, y verificar convirtiendo el resultado de vuelta a decimal.

**Método alterno para decimal → binario (restar potencias de 2):** en vez de dividir sucesivamente, puedes restar la potencia de 2 más grande posible, repetir con el residuo, y marcar 1 donde restaste y 0 donde no.

```
Convertir 19 a binario:
19 - 16 (2⁴) = 3   → bit del 16: 1
 3 -  8 (2³)  no cabe → bit del 8: 0
 3 -  4 (2²)  no cabe → bit del 4: 0
 3 -  2 (2¹) = 1   → bit del 2: 1
 1 -  1 (2⁰) = 0   → bit del 1: 1

Resultado: 10011
```

Ambos métodos llegan al mismo resultado — usa el que te resulte más natural.

**Ejercicios propuestos (para practicar por tu cuenta o en clase):**

1. Convierte 42 a binario.

<details>
<summary>Ver respuesta</summary>

42 = 32 + 8 + 2 = 2⁵ + 2³ + 2¹ → **101010**

</details>

2. Convierte 100 a binario.

<details>
<summary>Ver respuesta</summary>

100 = 64 + 32 + 4 = 2⁶ + 2⁵ + 2² → **1100100**

</details>

3. Convierte el binario `110101` a decimal.

<details>
<summary>Ver respuesta</summary>

32 + 16 + 0 + 4 + 0 + 1 = **53**

</details>

4. Convierte el binario `10000000` a decimal. ¿Qué potencia de 2 reconoces en el resultado?

<details>
<summary>Ver respuesta</summary>

**128** — es exactamente 2⁷. Cualquier binario con un solo 1 seguido de ceros siempre es una potencia de 2 exacta.

</details>

5. ¿Cuántos bits necesitas como mínimo para representar el número 200 en binario?

<details>
<summary>Ver respuesta</summary>

**8 bits.** Con 7 bits el máximo posible es 127 (2⁷-1), insuficiente. Con 8 bits el máximo es 255 (2⁸-1), suficiente para 200. (200 en binario: `11001000`)

</details>



---

## Parte 3 — Sistema octal (base 8) (15 min)

Menos común hoy en día, pero aparece en algunos contextos (permisos de archivos en Unix/Linux, por ejemplo). Cada posición vale una potencia de 8, y los dígitos válidos son 0-7 únicamente.

**Ejemplo — convertir octal a decimal:**

```
27 (octal) = 2×8¹ + 7×8⁰ = 16 + 7 = 23 (decimal)
```

**Atajo entre binario y octal:** cada dígito octal corresponde exactamente a **3 bits** (porque 2³ = 8). Esto permite convertir binario ↔ octal agrupando de 3 en 3 sin pasar por decimal:

```
Binario:  101 111
Octal:     5    7   → 57 (octal)
```

**Ejemplo — convertir decimal a octal (mismo método de divisiones sucesivas, pero entre 8):**

```
23 ÷ 8 = 2  residuo 7
 2 ÷ 8 = 0  residuo 2
```

Leyendo los residuos de abajo hacia arriba: **27** en octal (coincide con el ejemplo anterior, en sentido inverso).

**Ejercicios propuestos (para practicar por tu cuenta):**

1. Convierte 50 (decimal) a octal.

<details>
<summary>Ver respuesta</summary>

50 ÷ 8 = 6 residuo 2; 6 ÷ 8 = 0 residuo 6 → **62** (octal)

</details>

2. Convierte el octal `34` a decimal.

<details>
<summary>Ver respuesta</summary>

3×8¹ + 4×8⁰ = 24 + 4 = **28**

</details>

3. Convierte el binario `111 010` a octal usando el atajo de agrupación.

<details>
<summary>Ver respuesta</summary>

111 = 7, 010 = 2 → **72** (octal)

</details>



---

## Parte 4 — Sistema hexadecimal (base 16) (30 min)

El más importante de los tres para programación — se usa constantemente para representar direcciones de memoria, colores (RGB), y valores de bytes de forma compacta.

Como base 16 necesita 16 símbolos distintos, se usan las letras A-F para representar los valores 10-15:

| Decimal | 10 | 11 | 12 | 13 | 14 | 15 |
|---|---|---|---|---|---|---|
| Hex | A | B | C | D | E | F |

**Ejemplo — convertir hex a decimal:**

```
2F (hex) = 2×16¹ + F×16⁰ = 2×16 + 15×1 = 32 + 15 = 47 (decimal)
```

**Ejemplo — convertir decimal a hex (divisiones sucesivas entre 16):**

```
47 ÷ 16 = 2  residuo 15 (F)
 2 ÷ 16 = 0  residuo 2
```

Leyendo los residuos de abajo hacia arriba: **2F** en hex (mismo resultado que el ejemplo anterior, en sentido inverso).

**Atajo entre binario y hexadecimal:** cada dígito hex corresponde exactamente a **4 bits** (porque 2⁴ = 16). Igual que con octal, se agrupa de 4 en 4:

```
Binario:  1011 1100
Hex:        B    C   → BC (hexadecimal)
```

**Por qué esto es tan usado en programación:** un byte completo (8 bits) se representa exactamente con **2 dígitos hexadecimales** — mucho más compacto y legible que escribir 8 dígitos binarios. Por eso las direcciones de memoria y los colores casi siempre se ven en hex (ej. `0xFF0000` para rojo puro).

**Ejercicio en clase:** convertir el byte `11010110` a hexadecimal usando el atajo de agrupar de 4 en 4.

**Ejercicios propuestos adicionales (para practicar por tu cuenta):**

1. Convierte 200 (decimal) a hexadecimal.

<details>
<summary>Ver respuesta</summary>

200 ÷ 16 = 12 residuo 8; 12 = C → **C8** (hex)

</details>

2. Convierte el hex `A3` a decimal.

<details>
<summary>Ver respuesta</summary>

10×16 + 3 = 160 + 3 = **163**

</details>

3. Convierte el hex `FF` a binario usando el atajo de agrupación (¿coincide con algo que ya calculaste en la Parte 5?).

<details>
<summary>Ver respuesta</summary>

F = 1111, F = 1111 → **11111111** — coincide con el 255 de la tabla de la Parte 5, el valor máximo de un byte.

</details>

4. El color "verde puro" en RGB se representa como `0x00FF00`. ¿Cuál es el valor decimal del componente verde?

<details>
<summary>Ver respuesta</summary>

`FF` = 15×16 + 15 = **255** — el máximo posible en un byte, por eso es "verde puro" (intensidad máxima).

</details>



---

## Parte 5 — Tabla resumen de conversión rápida (10 min)

| Decimal | Binario | Octal | Hex |
|---|---|---|---|
| 0 | 0000 | 0 | 0 |
| 5 | 0101 | 5 | 5 |
| 10 | 1010 | 12 | A |
| 15 | 1111 | 17 | F |
| 16 | 10000 | 20 | 10 |
| 255 | 11111111 | 377 | FF |

**Nota sobre 255 y FF:** este es el valor máximo que cabe en un solo byte (8 bits) sin signo — van a ver este número constantemente al trabajar con `unsigned char` y colores RGB.

**Actividad rápida en clase — completa la tabla:** con lo aprendido en las Partes 2-4, completa los valores faltantes (sin usar la tabla de arriba como referencia):

| Decimal | Binario | Octal | Hex |
|---|---|---|---|
| 7 | ? | ? | ? |
| ? | 1100 | ? | ? |
| ? | ? | 30 | ? |
| ? | ? | ? | 1F |

<details>
<summary>Ver respuestas</summary>

| Decimal | Binario | Octal | Hex |
|---|---|---|---|
| 7 | 0111 | 7 | 7 |
| 12 | 1100 | 14 | C |
| 24 | 11000 | 30 | 18 |
| 31 | 11111 | 37 | 1F |

</details>

---

## Parte 6 — Conexión con C++ (30 min)

En C++, puedes escribir literales numéricos directamente en distintas bases usando prefijos:

```cpp
int decimal_val = 47;      // decimal (sin prefijo)
int hex_val = 0x2F;        // hexadecimal (prefijo 0x)
int octal_val = 057;       // octal (prefijo 0)
```

Los tres representan **el mismo valor** (47) — solo cambia cómo lo escribes en el código fuente. El compilador siempre los convierte internamente a binario para almacenarlos.

**Tamaños de tipos comunes** (referencia — puede variar ligeramente según el compilador/sistema):

| Tipo | Tamaño típico | Rango aproximado (sin signo) |
|---|---|---|
| `char` | 1 byte (8 bits) | 0 a 255 |
| `int` | 4 bytes (32 bits) | 0 a ~4,294 millones |
| `bool` | 1 byte | 0 o 1 |

**Mostrar valores en distintas bases al imprimir:** C++ permite cambiar la base en la que `cout` muestra un número usando manipuladores de `<iostream>`:

```cpp
#include <iostream>
using namespace std;

int main() {
    int valor = 47;

    cout << dec << valor << endl;  // 47   (decimal, es el default)
    cout << hex << valor << endl;  // 2f   (hexadecimal)
    cout << oct << valor << endl;  // 57   (octal)

    return 0;
}
```

**Nota:** una vez usas `hex` o `oct`, ese formato se queda activo para las siguientes salidas hasta que vuelvas a cambiarlo con `dec` — es un cambio de "modo", no algo que se aplique una sola vez. Van a usar esto directamente en el Lab 2.

**¿Qué pasa si un valor no cabe en el tipo? (overflow)** Cada tipo tiene un límite fijo de bits, y por lo tanto un valor máximo. Si un `unsigned char` (0-255) llega a 255 y le sumas 1, no da error — **se desborda y vuelve a 0**:

```cpp
unsigned char contador = 255;
contador = contador + 1;   // contador ahora vale 0, no 256
```

Esto no es un capricho del lenguaje — es consecuencia directa de que solo hay 8 bits disponibles para representar el valor: al llegar al máximo, el siguiente incremento simplemente "da la vuelta". Es el mismo concepto que un odómetro mecánico de carro que vuelve a 000000 después de llegar al máximo de dígitos que puede mostrar.

**Ejercicio de cierre:** dado que `char` es 1 byte (8 bits), ¿cuál es el valor decimal máximo que puede almacenar sin signo? *(Respuesta: 255 — mismo valor de la Parte 5.)*

**Ejercicios propuestos adicionales (para practicar por tu cuenta):**

1. Escribe el literal hexadecimal correspondiente a 100 en decimal.

<details>
<summary>Ver respuesta</summary>

100 ÷ 16 = 6 residuo 4 → **0x64**

</details>

2. Si un `unsigned char` vale 250 y le sumas 10, ¿qué valor final tiene? (Piensa en el overflow.)

<details>
<summary>Ver respuesta</summary>

250 + 10 = 260, pero el máximo de `unsigned char` es 255. El desborde "da la vuelta": 260 - 256 = **4**.

</details>

3. Investiga (o discutan en grupo): ¿por qué `int` en la tabla de arriba dice "sin signo" da como máximo ~4,294 millones — qué crees que cambia si el tipo sí tiene signo (permite negativos)?

<details>
<summary>Ver una posible respuesta</summary>

Con signo, uno de los 32 bits se reserva para indicar si el número es positivo o negativo, dejando 31 bits para el valor — por eso el rango se divide aproximadamente a la mitad en cada dirección: de aproximadamente -2,147 millones a +2,147 millones, en vez de 0 a ~4,294 millones. El total de valores representables es el mismo (2³²), solo cambia cómo se reparten entre positivos y negativos.

</details>



---

## Resumen de la sesión

- Las computadoras representan todo en binario porque los transistores solo tienen dos estados.
- Binario (base 2), octal (base 8), y hexadecimal (base 16) son formas distintas de representar el mismo valor.
- Octal y hexadecimal existen porque son más compactos que binario y se convierten fácilmente agrupando bits (3 para octal, 4 para hex).
- Hexadecimal es el más relevante en programación — usado en memoria, colores, y representación compacta de bytes.

## Próxima sesión

**Lab 2** — practicarán estas conversiones de forma manual y con código, además de continuar con Git/GitHub desde el IDE (VS Code).
