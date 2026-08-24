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

- **Bit** (*binary digit*) — la unidad más pequeña de información: un solo 1 o 0.
- **Byte** — un grupo de 8 bits. Es la unidad estándar para medir tamaño de datos (`char` en C++ ocupa 1 byte).

**Conexión con hardware:** cuando lleguen a cursos de sistemas embebidos, van a manipular directamente registros de memoria y puertos de entrada/salida a nivel de bits — entender esta representación ahora es la base de eso.

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

**Atajo entre binario y hexadecimal:** cada dígito hex corresponde exactamente a **4 bits** (porque 2⁴ = 16). Igual que con octal, se agrupa de 4 en 4:

```
Binario:  1011 1100
Hex:        B    C   → BC (hexadecimal)
```

**Por qué esto es tan usado en programación:** un byte completo (8 bits) se representa exactamente con **2 dígitos hexadecimales** — mucho más compacto y legible que escribir 8 dígitos binarios. Por eso las direcciones de memoria y los colores casi siempre se ven en hex (ej. `0xFF0000` para rojo puro).

**Ejercicio en clase:** convertir el byte `11010110` a hexadecimal usando el atajo de agrupar de 4 en 4.

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

**Ejercicio de cierre:** dado que `char` es 1 byte (8 bits), ¿cuál es el valor decimal máximo que puede almacenar sin signo? *(Respuesta: 255 — mismo valor de la Parte 5.)*

---

## Resumen de la sesión

- Las computadoras representan todo en binario porque los transistores solo tienen dos estados.
- Binario (base 2), octal (base 8), y hexadecimal (base 16) son formas distintas de representar el mismo valor.
- Octal y hexadecimal existen porque son más compactos que binario y se convierten fácilmente agrupando bits (3 para octal, 4 para hex).
- Hexadecimal es el más relevante en programación — usado en memoria, colores, y representación compacta de bytes.

## Próxima sesión

**Lab 2** — practicarán estas conversiones de forma manual y con código, además de continuar con Git/GitHub desde el IDE (VS Code).
