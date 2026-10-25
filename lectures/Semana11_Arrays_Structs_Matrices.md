# Semana 11 — Arrays, structs y matrices
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Gaddis, *Starting Out with C++: From Control Structures through Objects*, 8.ª edición de trabajo — Capítulo 7, secciones 7.1–7.4, 7.6 y 7.9; Capítulo 11, secciones 11.2–11.5

**Duración:** 170 min (lectura)
**Precede a:** Lab 11 — Basic Integer Calculator, múltiples archivos, arrays y structs del proyecto

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:

1. Declarar e inicializar un array de capacidad fija e identificar sus índices válidos.
2. Leer, modificar y mostrar sus elementos mediante índices y loops.
3. Distinguir entre capacidad y cantidad de elementos utilizados.
4. Definir un `struct`, declarar variables de ese tipo y acceder a sus members con el dot operator.
5. Recorrer un array de structs, distinguiendo entre index, ID y disponibilidad de un slot.
6. Declarar y recorrer una matriz usando row index, column index y nested loops.
7. Justificar qué representación necesita cada problema y cómo se relaciona con CoRe Data Analyzer.

---

## Cómo probar los programas de esta lecture

Los ejemplos ejecutables son **programas completos e independientes**. Compila uno a la vez en una carpeta de práctica. Los bloques identificados como formas de sintaxis sirven para reconocer una declaración y no sustituyen un programa completo.

Antes de ejecutar, predice qué index se utilizará y qué value contendrá ese elemento. Después compara la predicción con el output. Los inputs que cambian se solicitan por consola; las capacidades y los límites propios del problema permanecen como constants.

En los ejemplos de hoy, entra números cuando se soliciten números. La recuperación de input no numérico sigue siendo una destreza de validación ya disponible; aquí concentraremos el análisis en los límites y en la organización de los datos.

---

## Parte 1 — Arrays: conservar una colección de valores (25 min)

Hasta ahora hemos usado variables como `int count` o `double duration` para guardar un valor a la vez. Un **arreglo**, llamado **array** en C++, permite reservar bajo un mismo nombre varias posiciones para guardar valores del mismo tipo. Cada posición se llama **elemento** y puede leerse o modificarse por separado, sin cambiar los valores de las demás.

Por ejemplo, un array de cinco números `double` tiene espacio para cinco valores con parte decimal. Sus elementos se almacenan consecutivamente en memoria. La cantidad de posiciones reservadas es su **capacidad**; en los arrays de tamaño fijo que usaremos, esa capacidad no cambia durante la ejecución.

Para distinguir sus elementos usamos un **índice**, llamado **index** o **subscript**. Es un número entero que identifica una posición dentro del array. En C++, el primer índice es `0`: un array de cinco elementos tiene índices `0`, `1`, `2`, `3` y `4`. El nombre identifica la colección; el índice entre corchetes selecciona un elemento de esa colección.

### 1.1 — Conservar las mediciones de una prueba

**Problema:** una persona técnica verifica un generador de pulsos eléctricos que se utilizará para probar sensores. Realiza cinco mediciones de la duración de sus pulsos, en milisegundos, y las entra en la consola en el orden en que las tomó. Necesita que el programa conserve las cinco para revisarlas juntas al terminar. Si descubre que escribió mal una medición, debe poder corregir esa lectura sin volver a entrar las otras cuatro.

Por ejemplo, después de entrar `2.5`, `3.0`, `4.5`, `3.5` y `5.0`, la revisión debe mostrar los cinco valores en ese orden. Para lograrlo, cada nueva lectura necesita su propio espacio de almacenamiento. Si se asignaran sucesivamente a una sola variable `duration`, cada lectura reemplazaría la anterior: al mostrar `duration`, solo veríamos `5.0`.

Cinco variables separadas permitirían conservar los valores, pero un array ofrece una organización común: el mismo nombre para las cinco mediciones y un índice para seleccionar cada una. Primero construiremos un programa que las guarde y muestre; en la Parte 2 agregaremos la selección y corrección de una lectura.

Para estas duraciones usaríamos `double pulseDurations[5]`. `double` indica el tipo de cada elemento, `pulseDurations` es el nombre del array y `5` es su capacidad. La siguiente tabla conecta el orden de las mediciones con las posiciones que utilizará el programa:

| Lectura del problema | Index en C++ | Elemento |
|---|---:|---|
| Primer pulso | 0 | `pulseDurations[0]` |
| Segundo pulso | 1 | `pulseDurations[1]` |
| Tercer pulso | 2 | `pulseDurations[2]` |
| Cuarto pulso | 3 | `pulseDurations[3]` |
| Quinto pulso | 4 | `pulseDurations[4]` |

En un array de `SIZE` elementos, los índices válidos van de `0` a `SIZE - 1`. Por eso `pulseDurations[5]` queda fuera del array de este problema: la capacidad cuenta los elementos, mientras el último índice es uno menos.

### 1.2 — Declaración, initialization y acceso

La forma de declaración es la siguiente. Es una plantilla de sintaxis, no un programa ejecutable:

```cpp
dataType arrayName[SIZE]; // Declares SIZE elements of the same type
```

`dataType` es el type de cada elemento, `arrayName` identifica la colección y `SIZE` es una constant integer expression positiva. Usaremos una named constant para que la capacidad tenga significado en el problema y no se repita como un número aislado.

Después de reservar las posiciones del array, necesitamos distinguir entre **crear el espacio** y **dar valores iniciales a sus elementos**. Esta segunda tarea se llama **inicialización** (*initialization*) y ocurre al declarar el array.

C++ permite escribir una **lista de valores iniciales entre llaves**, después de `=`. Los valores se asignan en orden: el primero al índice `0`, el segundo al índice `1`, y así sucesivamente. Por ejemplo, en la declaración `double pulseDurations[5] = {2.5, 3.0, 4.5, 3.5, 5.0};`, los cinco elementos comienzan con esas cinco duraciones. Este ejemplo solo ilustra la sintaxis; en nuestro programa las mediciones reales se pedirán por consola.

Si la lista contiene menos valores que la capacidad, los elementos numéricos restantes se inicializan a cero. Por ejemplo, `double pulseDurations[5] = {2.5};` deja `2.5` en el índice `0` y `0.0` en los otros cuatro.

Las llaves vacías de `double pulseDurations[5] = {};` representan una **lista sin valores explícitos**. Como no se proporcionó ningún valor, los cinco elementos se inicializan a `0.0`. En un array de `int`, el mismo patrón los inicializa a `0`.

Usaremos esa lista vacía para que todas las posiciones comiencen con valores conocidos. Luego cada `cin` reemplazará el cero de la posición correspondiente por la medición entrada. Esos ceros iniciales no representan mediciones tomadas.

En cambio, `double pulseDurations[5];`, declarado dentro de una function y sin inicialización, reserva las cinco posiciones pero no les da valores numéricos iniciales seguros para consultar. Antes de leer o mostrar un elemento, debe habérsele asignado un valor. No debe suponerse que comienza en cero.

El programa completo siguiente recibe las cinco duraciones y muestra qué valor quedó en cada posición. Todavía usa statements separados para que el acceso por index sea visible antes de automatizarlo con un loop.

```cpp
#include <iostream> // Provides console input and output
using namespace std;

int main() {
    const int PULSE_COUNT = 5; // Defines the number of readings to preserve
    double pulseDurations[PULSE_COUNT] = {}; // Initializes all five elements to zero

    cout << "Enter duration for pulse 1 (ms): ";
    cin >> pulseDurations[0]; // Stores the first reading at index zero
    cout << "Enter duration for pulse 2 (ms): ";
    cin >> pulseDurations[1]; // Stores the second reading at index one
    cout << "Enter duration for pulse 3 (ms): ";
    cin >> pulseDurations[2]; // Stores the third reading at index two
    cout << "Enter duration for pulse 4 (ms): ";
    cin >> pulseDurations[3]; // Stores the fourth reading at index three
    cout << "Enter duration for pulse 5 (ms): ";
    cin >> pulseDurations[4]; // Stores the fifth reading at index four

    cout << "Index 0: " << pulseDurations[0] << " ms" << endl;
    cout << "Index 1: " << pulseDurations[1] << " ms" << endl;
    cout << "Index 2: " << pulseDurations[2] << " ms" << endl;
    cout << "Index 3: " << pulseDurations[3] << " ms" << endl;
    cout << "Index 4: " << pulseDurations[4] << " ms" << endl;
    return 0; // Ends the complete program
}
```

Con inputs `2.5`, `3.0`, `4.5`, `3.5` y `5.0`, cada output debe conservar su lectura correspondiente. Si cambia la segunda lectura, solamente `pulseDurations[1]` cambia; no se reemplaza el array completo.

### 1.3 — Una posición inválida no se vuelve válida porque compile

En nuestro array de cinco elementos, solo existen las posiciones `pulseDurations[0]` hasta `pulseDurations[4]`. Intentar leer o escribir `pulseDurations[5]` o `pulseDurations[-1]` es un **acceso fuera de rango** (*out-of-bounds access*). No crea un elemento nuevo ni amplía el array.

C++ no comprueba automáticamente los límites de estos arrays. El programa puede compilar aunque un índice sea inválido, especialmente cuando se calcula durante la ejecución o se recibe por consola. Por eso, compilar correctamente no garantiza que el acceso sea válido.

Al usar un índice fuera del rango, el programa intenta acceder a una ubicación de memoria que no corresponde a uno de los elementos del array. Esto provoca **undefined behavior**: C++ no garantiza qué ocurrirá. El efecto puede variar entre ejecuciones, computadoras o versiones compiladas del mismo programa.

| Operación inválida | Posibles consecuencias |
|---|---|
| Leer una posición fuera del array | Mostrar un valor sin sentido, terminar inesperadamente o aparentar que se obtuvo un dato válido. No hay garantía de recibir cero ni un mensaje de error. |
| Escribir en una posición fuera del array | Alterar datos ajenos al array, causar resultados incorrectos más adelante o terminar inesperadamente. Tampoco se garantiza una falla inmediata. |

Estas son posibles consecuencias, no resultados que puedan predecirse o usarse como parte de la lógica. Incluso si el programa parece funcionar, el acceso sigue siendo incorrecto. La inicialización con `= {}` solo establece valores para los cinco elementos existentes; no hace seguros los índices fuera del rango.

La comprobación debe ocurrir **antes** de acceder al elemento: el index debe ser mayor o igual a cero y menor que la capacidad. No pruebes accesos inválidos para descubrir qué pasa; identifica y corrige el límite en el código.

**Para practicar por tu cuenta:** si `PULSE_COUNT` es `5`, ¿cuáles de estos accesos son válidos: index `0`, `4`, `5` y `-1`? ¿Por qué inicializar con cero no significa que ya se tomaron cinco mediciones reales?

<details>
<summary>Ver respuesta</summary>

Son válidos `0` y `4`. `5` queda después del último elemento y `-1` antes del primero. Initialization establece values conocidos; no registra que la persona haya entrado mediciones. Un cero inicial y una medición real de cero pueden tener el mismo value, pero distinto significado.

</details>

---

## Parte 2 — Recorrer, ocupar y modificar un array (30 min)

### 2.1 — Capacidad frente a cantidad utilizada

En la Parte 1, cada ejecución pedía exactamente cinco mediciones. **Ahora la persona técnica necesita realizar pruebas de distinta duración:** algunas sesiones requieren dos pulsos y otras tres, cuatro o cinco. El programa debe conservar espacio para cinco lecturas, pero mostrar únicamente las que se tomaron en la sesión actual. También debe permitir corregir una lectura existente sin pedir otra vez todas las mediciones.

Esto introduce dos cantidades con responsabilidades diferentes. La **capacidad** es el número de elementos que existen en el array; sigue siendo cinco durante toda la ejecución. La **cantidad utilizada** es el número de elementos que contienen datos registrados para el problema en ese momento. Puede ser menor que la capacidad y cambiar según la sesión.

El array no lleva automáticamente un registro de cuáles valores representan mediciones reales. Para distinguirlos, el programa necesita una regla. En este ejemplo guardaremos las lecturas en posiciones consecutivas, comenzando en el índice `0`, y usaremos `readingCount` para indicar cuántas se van a recibir. Primero se solicita y valida esa cantidad; después se llena exactamente ese número de posiciones. Al terminar la entrada, `readingCount` coincide con la cantidad de lecturas almacenadas.

Si la persona solicita tres lecturas y entra `2.5`, `3.0` y `4.5`, los índices `0`, `1` y `2` contienen mediciones. Los índices `3` y `4` también existen, pero sus ceros iniciales no son mediciones de esta sesión. Mostrar o incluir esas dos posiciones en un cálculo daría un significado incorrecto a sus valores.

La siguiente tabla distingue las cantidades que necesitamos para decidir qué posiciones procesar:

| Concepto | Valor en el ejemplo | Uso en el programa |
|---|---:|---|
| Capacidad | 5 | Se fija al declarar el array. |
| `readingCount` | 3 | Controla cuántos elementos llenamos y mostramos. |
| Último índice utilizado | 2 | Es `readingCount - 1`, no `readingCount`. |

**¿Siempre hace falta una variable para la cantidad utilizada?** No. Si el problema exige llenar y procesar siempre los cinco elementos, como en la Parte 1, podemos recorrer directamente hasta la capacidad. Una cantidad separada resulta útil cuando el número de datos válidos puede ser menor: al cargar un archivo con menos registros que espacio disponible, recibir mediciones hasta que la persona decida terminar o agregar datos gradualmente.

En una entrada gradual, la cantidad utilizada podría comenzar en cero y aumentar después de cada registro válido. Nuestro programa sigue otra estrategia más sencilla: pregunta la cantidad por adelantado y luego recibe todas esas lecturas. En ambos casos debe cumplirse que la cantidad utilizada no exceda la capacidad.

Este contador funciona porque acordamos ocupar primero los índices consecutivos desde cero. Más adelante, al permitir eliminar registros y dejar huecos intermedios, necesitaremos otra forma de reconocer los slots utilizados; la veremos en la Parte 4.

### 2.2 — Un loop selecciona un elemento en cada vuelta

Ya sabemos cuántas lecturas recibiremos y dónde deben quedar. Falta decidir cómo repetir la entrada sin escribir cinco pares de `cout` y `cin`, como hicimos en la Parte 1. La tarea es la misma en cada posición: pedir una duración y guardarla. Lo único que cambia es el índice del elemento seleccionado.

Usaremos un `for` cuyo contador `index` haga esa selección. Si `readingCount` vale `3`, necesitamos visitar `0`, `1` y `2`, y detenernos antes de `3`. Por eso la condición usa **menor que**, `index < readingCount`: el contador de lecturas indica cuántos elementos procesar, no el índice del último.

Cada parte del `for` responde a una necesidad de ese recorrido:

| Parte del loop | Código | Relación con las lecturas |
|---|---|---|
| Inicio | `int index = 0` | Selecciona la primera posición del array. |
| Condición | `index < readingCount` | Permite visitar solo las posiciones que debemos llenar. |
| Body | `cin >> pulseDurations[index]` | Guarda la nueva duración en el elemento seleccionado. |
| Update | `index++` | Selecciona la siguiente posición después de guardar la lectura actual. |

Para mostrar las lecturas, otro `for` recorrerá esos mismos índices, pero usará `cout` en lugar de `cin`. Leer de la consola y mostrar el array son dos recorridos separados: primero se completa la colección y luego se consulta lo guardado.

### 2.3 — Seleccionar una lectura para corregirla

La persona ve las lecturas numeradas desde `1`, mientras el array empieza en índice `0`. Si solicita corregir la lectura número `2`, debemos modificar `pulseDurations[1]`. La relación es **índice = número de lectura − 1**.

Antes de aplicar esa relación, validamos el número visible: debe estar entre `1` y `readingCount`. Una posición puede existir dentro de la capacidad y aun así no contener una lectura registrada. Por ejemplo, si solo se entraron tres mediciones, solicitar la lectura `5` no es una corrección válida, aunque el array tenga cinco elementos.

Una vez validado el número, `selectedIndex` identifica el elemento que recibirá el nuevo valor. Esta operación reemplaza una lectura existente: no agrega una posición, no cambia la capacidad y no aumenta `readingCount`.

El siguiente programa reúne el flujo completo: solicitar la cantidad, llenar el array, mostrar las lecturas, corregir una y volver a mostrar la colección.

```cpp
#include <iostream> // Provides console input and output
using namespace std;

int main() {
    const int CAPACITY = 5; // Defines the fixed array capacity
    double pulseDurations[CAPACITY] = {}; // Initializes every storage position
    int readingCount;
    int readingNumber;

    cout << "How many pulse readings (1-5): ";
    cin >> readingCount;
    while (readingCount < 1 || readingCount > CAPACITY) {
        cout << "Enter a count from 1 to 5: ";
        cin >> readingCount; // Validates the count before indexing the array
    }

    for (int index = 0; index < readingCount; index++) {
        cout << "Enter duration for pulse " << index + 1 << " (ms): ";
        cin >> pulseDurations[index]; // Stores each reading in its own element
    }

    cout << "Recorded readings:" << endl;
    for (int index = 0; index < readingCount; index++) {
        cout << "Pulse " << index + 1 << ": " << pulseDurations[index] << endl;
    }

    cout << "Which pulse reading should be corrected: ";
    cin >> readingNumber;
    while (readingNumber < 1 || readingNumber > readingCount) {
        cout << "Enter an existing pulse number: ";
        cin >> readingNumber; // Rejects numbers that do not identify a stored reading
    }

    int selectedIndex = readingNumber - 1; // Converts the visible number to a zero-based index
    cout << "Enter the corrected duration (ms): ";
    cin >> pulseDurations[selectedIndex]; // Replaces only the selected element

    cout << "Updated readings:" << endl;
    for (int index = 0; index < readingCount; index++) {
        cout << "Pulse " << index + 1 << ": " << pulseDurations[index] << endl;
    }

    return 0;
}
```

### 2.4 — Trace y errores de límite

Ejecuta con count `3`, duraciones `2.5`, `3.0`, `4.5` y corrección de pulse `2` a `3.5`. Antes de compilar, sigue la relación entre número visible e index:

| Acción | Index usado | Resultado |
|---|---:|---|
| Entrar pulse 1 | 0 | Se guarda `2.5`. |
| Entrar pulse 2 | 1 | Se guarda `3.0`. |
| Entrar pulse 3 | 2 | Se guarda `4.5`. |
| Corregir pulse 2 | 1 | `3.0` se reemplaza por `3.5`. |

Ahora revisa la condición de los `for` del programa anterior: `index < readingCount`. Con `readingCount = 3`, el loop procesa los índices `0`, `1` y `2`; cuando `index` llega a `3`, la condición es falsa y el loop termina.

Si en uno de esos loops se escribiera `index <= readingCount`, la comparación también sería verdadera cuando `index` vale `3`. El loop ejecutaría una cuarta vuelta usando `pulseDurations[3]`, aunque la sesión solo debía procesar tres lecturas. En el loop de entrada pediría una medición adicional; en los loops de salida mostraría una posición que no contiene una medición de la sesión. Si la persona hubiera solicitado cinco lecturas, esa misma condición incorrecta permitiría llegar al índice `5`, que está fuera del array.

Este error al establecer el límite de un recorrido se llama **off-by-one error**: se procesa una posición de más o de menos respecto a las que necesita el problema.

Conviene distinguir esos dos errores: procesar el índice `3` cuando solo hay tres lecturas no sale de un array de cinco, pero utiliza un dato que no pertenece a la sesión. Procesar el índice `5` sí sale del array y provoca undefined behavior. Validar los límites del almacenamiento y respetar la cantidad de datos reales son responsabilidades relacionadas, pero diferentes.

**Takeaway:** cuando los datos ocupan posiciones consecutivas desde cero, recorre hasta la cantidad utilizada para mostrar o procesar datos reales. Usa la capacidad para limitar cuántos puedes almacenar. Si todos los elementos se utilizan siempre, ambas cantidades coinciden y no hace falta mantener un contador separado.

**Para practicar por tu cuenta:** con `readingCount = 2`, ¿por qué no se permite corregir la lectura número `4`, aunque el array tenga cinco posiciones? ¿Por qué no basta con validar contra `CAPACITY`?

<details>
<summary>Ver respuesta</summary>

Solo hay dos lecturas de esa sesión. Las demás posiciones existen físicamente, pero no contienen lecturas registradas. La corrección debe validar contra la cantidad utilizada; validar solo contra la capacidad permitiría modificar una posición que no corresponde a un dato existente.

</details>

---

## Parte 3 — Structs: agrupar los campos de un registro (25 min)

### 3.1 — De varias mediciones a los datos de un sensor

**Problema:** la persona técnica utiliza el generador de pulsos para verificar un sensor instalado en el marco de una puerta. Al terminar la prueba, necesita registrar qué sensor examinó y cuántos pulsos se registraron. Para eso entra el ID `42`, la etiqueta `Door frame sensor` y una cantidad de `3` pulsos. El programa debe conservar los tres datos y mostrarlos juntos como resumen de la prueba de ese sensor.

Esta tarea es distinta de guardar las duraciones de los pulsos. Las duraciones eran varios valores del mismo tipo; ahora queremos reunir información de distinta naturaleza sobre una sola entidad. El ID identifica el sensor, la etiqueta lo describe y la cantidad resume la prueba. Los dos primeros no deben confundirse con el número de pulsos.

A ese conjunto de datos relacionados lo llamamos **registro**. Cada dato individual del registro es un **campo**: ID, etiqueta y cantidad. Los campos no tienen que compartir el mismo tipo: para este problema, ID y cantidad serán `int`, mientras que la etiqueta será `string`.

Podríamos declarar tres variables independientes, pero sus declaraciones no expresarían que forman un solo registro. Tampoco basta un array de `int`, porque todos sus elementos deben ser del mismo tipo y la etiqueta es texto. C++ ofrece `struct` para definir la forma de un registro con campos de distintos tipos.

Un **struct** define un nuevo tipo de dato; sus campos se llaman **members** en C++. Cada member tiene un nombre y un tipo. La definición describe qué información tendrá cada registro de ese tipo, pero todavía no crea un registro particular ni recibe datos de la persona.

Antes de llevarlo al problema del sensor, observa la forma de una definición sencilla. Es una plantilla de sintaxis, no un programa ejecutable:

```cpp
struct RecordType { // Defines the fields shared by variables of this type
    int identifier; // Declares an integer member
    string label; // Declares a string member
}; // Ends the type definition with a required semicolon
```

`RecordType` nombra el nuevo tipo. `identifier` y `label` son sus members. El punto y coma después de la llave final, `};`, termina la definición del tipo y es obligatorio. Para nuestro caso usaremos el nombre `SensorRecord` y agregaremos el campo `pulseCount`.

### 3.2 — Del tipo a una variable concreta y sus campos

Definir `SensorRecord` es establecer qué campos tendrá un registro. Para guardar los datos de la prueba necesitamos además una **variable de ese tipo**, que llamaremos `sensor`. La relación es la misma que en `int count`: primero se indica el tipo y luego el nombre de la variable. Aquí `SensorRecord sensor` crea espacio para un registro completo con ID, etiqueta y cantidad de pulsos.

Para acceder a un campo de esa variable usamos el **dot operator**, `.`. La expresión `sensor.id` selecciona el campo `id` del registro guardado en `sensor`. Como ese campo es un `int`, puede recibir un valor mediante `cin`, participar en una comparación o mostrarse con `cout`, igual que una variable numérica individual.

La siguiente tabla conecta las tres decisiones que debemos distinguir antes de leer el programa:

| Expresión | Qué representa | Qué permite hacer |
|---|---|---|
| `SensorRecord` | El tipo definido por el programa. | Declarar variables con esos campos. |
| `sensor` | Una variable de tipo `SensorRecord`. | Conservar el registro de un sensor específico. |
| `sensor.id` | Un campo `int` de esa variable. | Leer o mostrar el ID de ese sensor. |
| `sensor.label` | Un campo `string` de esa variable. | Conservar su etiqueta completa. |

Al declarar `SensorRecord sensor = {};`, usamos las llaves vacías que vimos en la Parte 1. En este struct, cuyos campos no tienen valores iniciales explícitos en la definición, los campos numéricos comienzan en cero y el `string` comienza vacío. Después, las lecturas por consola reemplazan esos valores iniciales. Si el struct tuviera un campo `bool` sin valor inicial explícito, este patrón lo inicializaría a `false`; en la Parte 4 veremos cómo especificar otro valor inicial cuando el problema lo requiera.

También debemos preparar la lectura de la etiqueta. Después de `cin >> sensor.id`, el newline de Enter puede permanecer pendiente; un `getline` directo podría consumirlo y producir una etiqueta vacía. En `getline(cin >> ws, sensor.label)`, el manipulador **`ws`** consume primero el whitespace inicial pendiente, incluidos espacios y saltos de línea, y después `getline` lee la etiqueta completa, conservando sus espacios interiores. Usaremos este patrón porque la etiqueta debe contener texto; no sirve para registrar intencionalmente una línea vacía ni para preservar espacios al comienzo.

El programa completo coloca la definición de `SensorRecord` antes de `main`, para que el compiler conozca el tipo. Dentro de `main`, crea e inicializa `sensor`, recibe sus tres campos y muestra el resumen. Sigue ese orden al leerlo:

```cpp
#include <iostream> // Provides cin, cout, and the ws manipulator
#include <string> // Provides string and getline
using namespace std;

struct SensorRecord {
    int id; // Identifies one sensor
    string label; // Stores its descriptive label
    int pulseCount; // Stores how many pulses were recorded
}; // Defines the type, not a particular sensor variable

int main() {
    SensorRecord sensor = {}; // Creates one record with zero numbers and an empty string

    cout << "Enter sensor ID: ";
    cin >> sensor.id; // Reads one member of the record
    cout << "Enter sensor label: ";
    getline(cin >> ws, sensor.label); // Reads a complete label after numeric input
    cout << "Enter recorded pulse count: ";
    cin >> sensor.pulseCount;

    cout << "Sensor ID: " << sensor.id << endl;
    cout << "Label: " << sensor.label << endl;
    cout << "Recorded pulses: " << sensor.pulseCount << endl;
    return 0;
}
```

### 3.3 — Seguir los cambios dentro del registro

Ejecuta con `42`, `Door frame sensor` y `3`. Antes de observar el output, sigue cómo cambia la variable `sensor` con cada lectura. Cada assignment actualiza un campo; los otros conservan sus valores.

| Momento | `sensor.id` | `sensor.label` | `sensor.pulseCount` |
|---|---:|---|---:|
| Después de `SensorRecord sensor = {};` | 0 | Cadena vacía | 0 |
| Después de leer el ID | 42 | Cadena vacía | 0 |
| Después de leer la etiqueta | 42 | `Door frame sensor` | 0 |
| Después de leer la cantidad | 42 | `Door frame sensor` | 3 |

El output muestra el último estado de esos tres campos. Guardarlos en un struct mantiene su relación como un registro, pero no valida automáticamente sus valores: un pulse count negativo requeriría una comprobación adicional con las selection structures y loops ya conocidos.

**Takeaway:** el tipo describe la forma del registro, la variable conserva un registro concreto y el dot operator selecciona uno de sus campos. Si se declarara una segunda variable de tipo `SensorRecord`, tendría sus propios campos; cambiar `sensor.id` no modificaría el ID de esa otra variable.

**Para practicar por tu cuenta:** ¿por qué `SensorRecord.id` no identifica el ID entrado por la persona? ¿Qué falta si se escribe la definition con `}` en lugar de `};`?

<details>
<summary>Ver respuesta</summary>

`SensorRecord` nombra el tipo, no la variable concreta. El acceso correcto es `sensor.id`. El punto y coma después de la llave final es obligatorio al terminar la definición del struct.

</details>

---

## Parte 4 — Array de structs: varios registros con disponibilidad (35 min)

### 4.1 — Una colección de registros completos

En la Parte 3 guardamos el resumen de prueba de un sensor. **Ahora la persona técnica debe administrar una sesión con hasta cuatro sensores:** recibe los datos de cada uno, revisa la lista y puede retirar de la sesión uno de los registros. Si retira el segundo, los demás deben conservar sus datos y su ubicación. Ese espacio quedará disponible para un registro futuro.

Para conservar varios registros completos usaremos un **array de structs**: cada elemento del array será un `SensorRecord`, con su propio ID, etiqueta y cantidad de pulsos. En lugar de declarar una sola variable para un sensor, reservaremos cuatro registros bajo el nombre común `sensors`.

Llamaremos **slot** a cada posición disponible para almacenar un registro. Tener un slot reservado no significa que ya exista un sensor registrado allí. Además, al retirar un sensor, puede quedar un slot vacío entre otros ocupados. La cantidad de registros por sí sola ya no nos dice cuáles posiciones deben mostrarse.

Por eso añadiremos a `SensorRecord` un campo `bool isEmpty`. Este **flag de disponibilidad** responderá una pregunta sobre cada slot: ¿está vacío? `true` significa que está disponible y no se procesa como un registro activo; `false`, que contiene un registro que debemos mostrar. Usar cero como ID no sustituye esta decisión: es el flag el que establece si el registro participa en la sesión.

Para visualizar esa diferencia entre un registro y una colección de registros, observa estas declaraciones. Este snippet supone que ya se definió `SensorRecord`; muestra la sintaxis de reserva de espacio, no un programa completo ni la entrada de datos. En 4.2 prepararemos los valores iniciales de cada campo antes de usar los registros.

```cpp
const int CAPACITY = 4; // Defines the number of record slots
SensorRecord sensor; // Reserves space for one complete sensor record
SensorRecord sensors[CAPACITY]; // Reserves space for four complete sensor records
```

El **ID** tiene otra responsabilidad: identificar al sensor según el dato entrado por la persona. El **índice** identifica su ubicación dentro del array. Un sensor con ID 42 puede almacenarse en índice 0; su ID no se utiliza entre corchetes para localizarlo.

La siguiente tabla muestra cómo seleccionar primero un registro y luego uno de sus campos. El acceso combina los dos operadores conocidos: los corchetes seleccionan el registro del array y el punto selecciona un campo de ese registro.

| Expresión | Qué selecciona |
|---|---|
| `sensors` | La colección completa. |
| `sensors[0]` | El registro guardado en índice `0`. |
| `sensors[0].id` | El ID de ese registro. |
| `sensors[0].isEmpty` | La disponibilidad de ese slot. |

### 4.2 — Preparar los slots y planificar sus cambios de estado

Antes de registrar sensores, los cuatro slots deben comenzar vacíos. En la Parte 3, las llaves vacías inicializaban a cero los números; un campo `bool` sin un valor inicial explícito comenzaría en `false`. Pero aquí `isEmpty == false` significa **ocupado**, lo contrario del estado que necesitamos al iniciar.

Para indicar el estado correcto, escribiremos `bool isEmpty = true;` dentro de la definición del struct. Eso es un **default member initializer**: establece el valor inicial de ese campo cuando no se proporciona otro explícitamente al crear el registro. También daremos valores iniciales de cero a `id` y `pulseCount`; `label`, por ser `string`, comienza vacío.

Al declarar `SensorRecord sensors[CAPACITY] = {};`, cada elemento utiliza esos valores iniciales. Las llaves vacías no anulan `isEmpty = true`: los cuatro slots comienzan disponibles. Cuando se complete la entrada de los campos de un sensor, el programa cambiará únicamente su flag a `false`. Cuando se retire ese sensor, lo cambiará otra vez a `true`.

Con ese estado inicial definido, el programa seguirá esta secuencia:

1. Crear cuatro slots vacíos y pedir cuántos sensores se registrarán, entre uno y cuatro.
2. Recibir los campos de cada sensor en posiciones consecutivas desde el índice `0` y marcar cada registro completo como ocupado.
3. Recorrer toda la capacidad y mostrar solo los registros cuyo `isEmpty` sea `false`.
4. Pedir el número de un slot ocupado y marcarlo vacío, sin mover los demás registros.
5. Recorrer nuevamente toda la capacidad para comprobar que el registro retirado ya no se muestra.

En los prompts, los slots se numeran desde `1` para la persona; internamente se usan índices desde `0`. Liberar el slot número `2` modifica `sensors[1].isEmpty`, aplicando la misma conversión que usamos en la Parte 2. Validaremos contra `sensorCount` porque, en esta demostración, los registros iniciales son consecutivos y solo se libera uno una vez. Si se permitieran eliminaciones repetidas, también habría que comprobar que el slot elegido siga ocupado.

**Recordatorio sobre `cin >> ws`:** `ws` es un manipulador de input cuyo nombre se refiere a *whitespace*. Descarta los espacios, tabs y saltos de línea que encuentre al comienzo de la entrada pendiente. Aquí elimina, entre otros, el newline que dejó `cin >> sensors[index].id`, para que `getline` pueda leer la etiqueta que la persona escriba después. `ws` no lee la etiqueta ni la almacena: esa tarea la hace `getline`. Los espacios interiores de una etiqueta como `Door frame sensor` se conservan; los espacios iniciales y las líneas vacías se descartan.

El código completo siguiente implementa ese recorrido. La selección por slot permite observar los índices sin introducir todavía la búsqueda por ID de Semana 12.

```cpp
#include <iostream> // Provides console input and output
#include <string> // Provides string and getline
using namespace std;

struct SensorRecord {
    int id = 0; // Initializes the identifier before a sensor is entered
    string label; // Starts as an empty string
    int pulseCount = 0; // Initializes the recorded pulse count
    bool isEmpty = true; // Marks a new slot as available
};

int main() {
    const int CAPACITY = 4; // Reserves storage for at most four sensor records
    SensorRecord sensors[CAPACITY] = {}; // Creates four initialized record slots
    int sensorCount; // Stores how many sensors will be registered initially
    int slotNumber; // Stores the user-visible slot number, starting at one

    cout << "How many sensors will be entered (1-4): ";
    cin >> sensorCount;
    while (sensorCount < 1 || sensorCount > CAPACITY) { // Keeps the requested count within the array capacity
        cout << "Enter a count from 1 to 4: ";
        cin >> sensorCount;
    }

    for (int index = 0; index < sensorCount; index++) { // Fills only the requested consecutive slots
        cout << "Enter ID for sensor " << index + 1 << ": ";
        cin >> sensors[index].id; // Stores the ID in the record selected by index
        cout << "Enter sensor label: ";
        getline(cin >> ws, sensors[index].label); // Skips leading whitespace, then reads the full label
        cout << "Enter recorded pulse count: ";
        cin >> sensors[index].pulseCount; // Updates another member of the same record
        sensors[index].isEmpty = false; // Marks the completed record as occupied
    }

    cout << "Occupied sensor slots:" << endl;
    for (int index = 0; index < CAPACITY; index++) { // Checks every slot, including unused positions
        if (!sensors[index].isEmpty) { // Excludes slots without a sensor record
            cout << "Slot " << index + 1 << ", ID " << sensors[index].id
                 << ", " << sensors[index].label << endl;
        }
    }

    cout << "Enter an occupied slot number to release: ";
    cin >> slotNumber;
    while (slotNumber < 1 || slotNumber > sensorCount) { // Validates against the initially occupied slots
        cout << "Enter one of the occupied slot numbers: ";
        cin >> slotNumber; // Initial occupied slots are consecutive in this example
    }
    sensors[slotNumber - 1].isEmpty = true; // Releases the slot without moving other records

    cout << "Sensor records after releasing the slot:" << endl;
    for (int index = 0; index < CAPACITY; index++) { // Checks every slot, including unused positions
        if (!sensors[index].isEmpty) {
            cout << "Slot " << index + 1 << ", ID " << sensors[index].id
                 << ", pulses " << sensors[index].pulseCount << endl;
        }
    }

    return 0;
}
```

Esta demostración no implementa todavía la validación de IDs duplicados ni el menú del proyecto. Su tarea es mostrar cómo cada slot mantiene unidos sus fields y cómo el recorrido excluye un registro liberado.

### 4.3 — Un hueco cambia la forma de recorrer

Prueba con `sensorCount = 3`. Entra IDs `42`, `57` y `81`, etiquetas `Door sensor`, `Window sensor` y `Gate sensor`, y cantidades de pulsos `3`, `4` y `5`, respectivamente. Antes de liberar un slot, el primer recorrido debe mostrar los tres sensores. Después, solicita liberar slot `2`.

La tabla compara el estado inmediatamente después de registrar los sensores con el estado después de liberar ese slot. El único campo que cambia en esa operación es `sensors[1].isEmpty`.

| Índice | ID almacenado | `isEmpty` antes | `isEmpty` después | ¿Se muestra al final? |
|---:|---:|---|---|---|
| 0 | 42 | `false` | `false` | Sí. |
| 1 | 57 | `false` | `true` | No. |
| 2 | 81 | `false` | `false` | Sí. |
| 3 | 0 | `true` | `true` | No. |

El ID `57`, su etiqueta y su cantidad de pulsos siguen almacenados, porque el código no los borra. Sin embargo, el registro dejó de pertenecer a la sesión activa: el flag indica que debe ignorarse. En una inserción posterior, se reemplazarían los campos de un slot vacío antes de marcarlo ocupado otra vez.

Ahora hay dos registros ocupados, pero están en índices `0` y `2`. Un recorrido que examinara solamente dos posiciones desde cero visitaría `0` y `1`, y omitiría el sensor `81`. Por eso los loops de presentación usan `index < CAPACITY` y luego `if (!sensors[index].isEmpty)`: revisan todas las posiciones y seleccionan solo las ocupadas. El operador `!` invierte el flag; si `isEmpty` es `false`, la condición del `if` es verdadera.

En este programa, `sensorCount` conserva la cantidad que se pidió registrar al inicio: sigue valiendo `3` después de liberar el slot. No representa un contador actualizado de registros activos ni debe interpretarse como tal. Para saber cuántos están ocupados después de cambios, podríamos contarlos durante un recorrido que compruebe sus flags.

**Takeaway:** cuando pueden existir huecos, el límite del recorrido y la condición de participación cumplen tareas distintas: la capacidad permite visitar todos los slots, y el flag decide qué registros procesar. El ID identifica el sensor; ni su valor ni el número total de sensores sustituye al flag.

### 4.4 — Conexión con CoRe Data Analyzer

CoRe Data Analyzer aplica esta misma organización a resultados electorales. Un struct reunirá los campos de una observation: ID, state, county, total votes, democratic votes, republican votes y democratic share. Un array reservará espacio para 100 registros, aunque el CSV inicial solo contiene 50.

Load ocupará slots al leer registros, Add utilizará uno vacío y Delete lo liberará. Display, Save y las estadísticas deberán ignorar los slots vacíos, incluso si todavía conservan valores antiguos en sus campos. Esta es la conexión entre la disponibilidad que acabamos de observar y el comportamiento exigido por el proyecto.

El CSV conserva los IDs como datos; no se usan como índices. Recuperar o verificar un registro por ID requerirá buscar entre los slots ocupados, tema de Semana 12. La lectura y escritura de archivos sigue usando los streams ya conocidos; la construcción del parser del CSV se desarrollará al integrar el proyecto.

**Para practicar por tu cuenta:** después de liberar slot `2`, ¿por qué un loop con `index < 2` omitiría un sensor válido? ¿Es suficiente asignar `sensors[1].id = 0` para indicar que el slot está vacío?

<details>
<summary>Ver respuesta</summary>

Ese loop solo examina índices `0` y `1`, y omite al sensor `81` en index `2`. El member que define disponibilidad es `isEmpty`, no el ID. Cambiar un ID no actualiza automáticamente el flag.

</details>

---

## Parte 5 — Matrices: identificar una posición con fila y columna (20 min)

### 5.1 — Definir y usar un array bidimensional

Los arrays que hemos usado hasta ahora son **unidimensionales**: seleccionamos un elemento con un solo índice. Un **array bidimensional**, o **two-dimensional array**, organiza elementos del mismo tipo en filas y columnas. También lo llamaremos **matriz**. Para seleccionar uno de sus elementos necesitamos dos índices: la fila y la columna. Cada elemento de esa cuadrícula se llama **celda**.

Antes de aplicarlo a un problema, observa la forma de declaración. Es una plantilla de sintaxis, no un programa ejecutable:

```cpp
dataType arrayName[ROW_COUNT][COLUMN_COUNT]; // Declares rows with the same number of columns
```

`dataType` indica el tipo de todas las celdas y `arrayName` nombra la matriz. El primer tamaño, `ROW_COUNT`, indica cuántas filas habrá; el segundo, `COLUMN_COUNT`, cuántos elementos habrá en cada fila. Ambos deben ser constantes enteras positivas para los arrays de tamaño fijo que usamos.

Al **declarar**, los números entre corchetes indican tamaños. Después, al **usar** el array, indican los índices de una celda concreta: primero fila y después columna. Veamos cómo se aplica esa diferencia a un panel físico.

**Problema:** una persona técnica inspecciona un panel de diagnóstico con seis indicadores luminosos, distribuidos en dos filas de tres. Cada indicador corresponde a una conexión distinta del equipo. La persona entra `0` si está apagado y `1` si está encendido; después necesita consultar una representación del panel para identificar cuáles conexiones estaban activas al inspeccionarlo.

No basta con informar que tres indicadores estaban encendidos: importa cuáles eran y dónde estaban. Por ejemplo, un indicador encendido en la esquina superior izquierda corresponde a una conexión distinta del situado en la esquina inferior derecha. El programa debe conservar esa distribución y mostrar dos filas de tres valores en el mismo orden que el panel físico.

Para representar el panel, elegimos `int` como tipo de cada celda porque guardaremos los estados `0` y `1`. Declararemos una matriz llamada `panel` con dos filas y tres columnas. Este snippet aplica la plantilla anterior; el programa completo aparece en 5.2.

```cpp
const int ROWS = 2; // Defines the number of rows
const int COLUMNS = 3; // Defines the number of columns in each row
int panel[ROWS][COLUMNS] = {}; // Initializes all six integer cells to zero
```

La primera dimensión indica que existen dos filas; la segunda indica tres columnas en cada fila. La cantidad total de elementos es el producto: `2 × 3 = 6`. Las llaves vacías inicializan a cero todas las celdas, aplicando el mismo principio que usamos en los arrays de una dimensión. Esos ceros son valores iniciales; las lecturas posteriores registrarán el estado observado de cada indicador.

Una vez declarada la matriz, podemos seleccionar una celda y tratarla como una variable `int`: asignarle un estado, recibirlo mediante `cin` o consultarlo con `cout`. Ambos índices comienzan en cero; por eso `panel[1][2]` selecciona la segunda fila y tercera columna, no una matriz de una fila y dos columnas.

El siguiente fragmento supone que `panel` ya está declarado como arriba y que se dispone de `cin` y `cout`. Muestra cómo recibir y consultar el estado de una sola celda antes de recorrer todas con loops:

```cpp
cout << "Enter state for row 2, column 3 (0/1): "; // Prompts for the bottom-right indicator
cin >> panel[1][2]; // Stores the entered state in one selected cell
cout << "Selected indicator state: " << panel[1][2] << endl; // Reads back the same cell
```

La siguiente tabla extiende esa misma relación a las seis posiciones del panel. Cada expresión selecciona una celda diferente del array ya declarado:

| | Columna 0 | Columna 1 | Columna 2 |
|---|---|---|---|
| Fila 0 | `panel[0][0]` | `panel[0][1]` | `panel[0][2]` |
| Fila 1 | `panel[1][0]` | `panel[1][1]` | `panel[1][2]` |

Cada dimensión tiene su propio límite: la fila debe estar entre `0` y `ROWS - 1`, y la columna entre `0` y `COLUMNS - 1`. En este caso, las filas válidas son `0–1` y las columnas `0–2`. Tener una fila válida no hace válida una columna fuera de rango: tanto `panel[2][0]` como `panel[0][3]` son accesos inválidos. Como con los arrays anteriores, C++ no comprueba estos límites automáticamente.

### 5.2 — Nested loops para visitar cada celda

Ya sabemos dónde guardar cada estado. Ahora necesitamos pedir los seis valores en un orden que permita a la persona reconocer qué indicador está registrando: primero las tres posiciones de la fila superior, de izquierda a derecha, y luego las tres de la fila inferior.

Usaremos dos `for` anidados. El **outer loop** selecciona una fila y mantiene ese índice fijo mientras el **inner loop** recorre sus columnas. Cuando el inner loop termina, el outer loop avanza a la siguiente fila. Al entrar otra vez al inner loop, su variable `column` se declara e inicializa nuevamente a cero: el recorrido comienza por la primera columna de la nueva fila.

Por eso las condiciones son `row < ROWS` y `column < COLUMNS`. Con los tamaños de este panel, el recorrido de entrada seguirá esta secuencia:

| Lectura | Fila interna (`row`) | Columna interna (`column`) | Celda que recibe el estado | Valor del test |
|---:|---:|---:|---|---:|
| 1 | 0 | 0 | `panel[0][0]` | 1 |
| 2 | 0 | 1 | `panel[0][1]` | 0 |
| 3 | 0 | 2 | `panel[0][2]` | 1 |
| 4 | 1 | 0 | `panel[1][0]` | 0 |
| 5 | 1 | 1 | `panel[1][1]` | 1 |
| 6 | 1 | 2 | `panel[1][2]` | 0 |

Los prompts mostrarán fila y columna desde `1` para la persona, usando `row + 1` y `column + 1`; el acceso a la matriz seguirá usando los índices desde cero. Dentro de cada celda, un `while` pedirá nuevamente el estado si la persona entra un número distinto de `0` o `1`. Ese `while` valida el estado del indicador; los límites de los dos `for` controlan las posiciones que se visitan.

Después de recibir los estados, otro par de nested loops recorrerá la matriz para mostrarla. El `cout` del inner loop imprime las tres celdas de la fila actual; el salto de línea se coloca después de ese loop, cuando la fila esté completa. Así el output conserva la forma del panel.

```cpp
#include <iostream> // Provides console input and output
using namespace std;

int main() {
    const int ROWS = 2;
    const int COLUMNS = 3;
    int panel[ROWS][COLUMNS] = {}; // Initializes every indicator to zero

    for (int row = 0; row < ROWS; row++) { // Selects one row for input
        for (int column = 0; column < COLUMNS; column++) { // Visits each column of the selected row
            cout << "Enter state for row " << row + 1
                 << ", column " << column + 1 << " (0/1): ";
            cin >> panel[row][column]; // Selects one cell using two indices
            while (panel[row][column] != 0 && panel[row][column] != 1) { // Accepts only valid indicator states
                cout << "Enter 0 or 1: ";
                cin >> panel[row][column];
            }
        }
    }

    cout << "Diagnostic panel:" << endl;
    for (int row = 0; row < ROWS; row++) { // Selects one row for display
        for (int column = 0; column < COLUMNS; column++) { // Restarts at column zero for each row
            cout << panel[row][column] << ' '; // Displays cells across the current row
        }
        cout << endl; // Ends the row only after all its columns have been displayed
    }

    return 0;
}
```

Con inputs `1`, `0`, `1`, `0`, `1`, `0`, el output debe ser:

```text
Diagnostic panel:
1 0 1
0 1 0
```

**Takeaway:** una matriz usa un tipo común para todas sus celdas y dos índices para expresar su ubicación. Un array de structs utiliza un índice para seleccionar un registro y nombres de campos para acceder a datos de distintos tipos. Por eso las observations del analyzer se representan con structs, mientras que una matriz de caracteres puede representar las posiciones visuales de su histograma de bono.

**Para practicar por tu cuenta:** ¿cuántas iteraciones del inner loop ocurren en el recorrido de entrada? ¿Y en el recorrido de salida? En este último recorrido, ¿qué cambiaría visualmente si `cout << endl;` estuviera dentro del inner loop?

<details>
<summary>Ver respuesta</summary>

Ocurren seis iteraciones en el recorrido de entrada y otras seis en el de salida: dos filas por tres columnas en cada recorrido. Los intentos adicionales del `while` de validación repiten la entrada de una misma celda, sin agregar iteraciones al `for`. Si el salto de línea estuviera dentro del inner loop de salida, cada celda aparecería en una línea distinta y se perdería la distribución de la cuadrícula.

</details>

---

## Práctica guiada — Leer un registro completo y conservarlo en una colección (35 min)

### Versión 1 — Un tiempo estimado por ticket (15 min)

**Problema:** un centro de reparación recibe hasta tres herramientas por turno. De cada herramienta registra un ticket ID, una descripción y los minutos estimados de trabajo. Después de recibir una cantidad indicada por la persona, debe mostrar los tickets y el total de minutos estimados. El total solo incluye registros ocupados.

Este ejemplo reúne arrays, structs y functions. No incluye búsqueda ni sorting. Antes del code, define las responsabilidades: `main` solicita y conserva los registros; `displayTicket` recibe un registro para mostrarlo. Un parameter de type `RepairTicket` por value recibe una copia de sus members; la function no cambia el registro almacenado en el array.

El programa está resuelto para analizarlo en clase. Primero sigue las function calls y los índices; después ejecútalo para contrastar tus predicciones.

```cpp
#include <iostream> // Provides console input and output
#include <string> // Provides string and getline
using namespace std;

struct RepairTicket {
    int id = 0;
    string description;
    int estimatedMinutes = 0;
    bool isEmpty = true; // Distinguishes unused slots from registered tickets
};

void displayTicket(RepairTicket ticket); // Declares a function that receives a record copy

int main() {
    const int CAPACITY = 3;
    RepairTicket tickets[CAPACITY] = {};
    int ticketCount;
    int totalMinutes = 0; // Accumulates work only from occupied records

    cout << "How many repair tickets (1-3): ";
    cin >> ticketCount;
    while (ticketCount < 1 || ticketCount > CAPACITY) {
        cout << "Enter a count from 1 to 3: ";
        cin >> ticketCount;
    }

    for (int index = 0; index < ticketCount; index++) {
        cout << "Enter ticket ID: ";
        cin >> tickets[index].id;
        cout << "Enter tool description: ";
        getline(cin >> ws, tickets[index].description);
        cout << "Enter estimated repair minutes: ";
        cin >> tickets[index].estimatedMinutes;
        while (tickets[index].estimatedMinutes < 0) {
            cout << "Enter zero or a positive number of minutes: ";
            cin >> tickets[index].estimatedMinutes;
        }
        tickets[index].isEmpty = false; // Activates the record after its fields are entered
    }

    cout << "Registered repair tickets:" << endl;
    for (int index = 0; index < CAPACITY; index++) {
        if (!tickets[index].isEmpty) {
            displayTicket(tickets[index]); // Passes the complete record to the display function
            totalMinutes += tickets[index].estimatedMinutes;
        }
    }
    cout << "Total estimated minutes: " << totalMinutes << endl;
    return 0;
}

void displayTicket(RepairTicket ticket) {
    cout << "Ticket " << ticket.id << ": " << ticket.description
         << " - " << ticket.estimatedMinutes << " minutes" << endl;
}
```

Prueba con dos tickets: ID `501`, descripción `Cordless drill`, `20` minutos; ID `508`, descripción `Bench vise`, `35` minutos. Deben mostrarse dos tickets y un total de `55`, aunque la capacidad sea tres.

Responde estas preguntas sobre el programa:

1. ¿Qué type tiene `tickets[1]`? ¿Y `tickets[1].estimatedMinutes`?
2. ¿Cuántas veces se hace la function call a `displayTicket` con el test anterior? ¿Por qué no tres?
3. Si un ticket ocupado requiere cero minutos, ¿debe omitirse? ¿Qué field decide si se procesa?
4. Si se marca el primer ticket como vacío antes del último recorrido, ¿cuál será el total y cuántos tickets se mostrarán?
5. Si `displayTicket` cambia su parameter local, ¿cambia también el registro del array? Explica usando pass-by-value.
6. ¿Por qué el ID `508` no se utiliza como index?

<details>
<summary>Ver respuestas</summary>

1. `tickets[1]` es un `RepairTicket`; su member `estimatedMinutes` es un `int`.
2. Dos calls: solo los primeros dos slots están ocupados.
3. Se procesa. Cero minutos es un value; `isEmpty` determina la disponibilidad.
4. Se mostrará solo el ticket `508` y el total será `35`.
5. No. El parameter es una copia local del registro. Cambiarla no altera los members del elemento original.
6. El array solo admite índices `0`, `1` y `2`. El ID identifica el ticket, no su ubicación física.

</details>

### Versión 2 — Un array de tiempos dentro de cada registro (20 min)

El centro de reparación necesita ahora un desglose del trabajo. Conservar solo un total permite saber cuánto tiempo requiere una herramienta, pero no cuánto corresponde a revisarla, repararla o comprobar el resultado. **La nueva necesidad es registrar tres tiempos por ticket:** diagnóstico, reparación y verificación. La persona entra los minutos de cada etapa; el programa calcula el total por ticket y el total de los tickets ocupados.

Seguimos trabajando con los mismos tickets de la versión inicial. Lo que cambia es la forma de representar el tiempo: sustituiremos el campo individual `estimatedMinutes` por un **array miembro**, llamado `stageMinutes`. Un member de un struct también puede ser un array: en este caso, cada registro conserva su propia colección de tres números `int`.

Antes de mirar el código, acordamos qué significa cada posición. Esa relación será fija para todos los tickets:

| Índice de etapa | Etapa | Dato que conserva |
|---:|---|---|
| 0 | Diagnosis | Minutos estimados de diagnóstico. |
| 1 | Repair | Minutos estimados de reparación. |
| 2 | Verification | Minutos estimados para verificar el resultado. |

No necesitamos una cantidad utilizada para las etapas: cada ticket debe recibir exactamente tres tiempos. Si una etapa no requiere trabajo, la persona entra cero minutos; esa posición sigue representando una etapa válida. En cambio, la cantidad de tickets sí puede ser menor que la capacidad.

**Cómo se selecciona un tiempo.** En la expresión `tickets[index].stageMinutes[stage]`, cada parte tiene una responsabilidad. Primero se selecciona un registro de la colección; después su array de tiempos; finalmente una posición de ese array:

| Expresión | Qué selecciona |
|---|---|
| `tickets[index]` | Un ticket completo. |
| `tickets[index].stageMinutes` | El array de tres tiempos de ese ticket. |
| `tickets[index].stageMinutes[stage]` | Los minutos de una etapa de ese ticket. |

Por ejemplo, `tickets[1].stageMinutes[0]` es el tiempo de diagnóstico del segundo ticket, no del primero. Los dos índices comienzan en cero, pero seleccionan cosas distintas: `index` selecciona un registro y `stage` selecciona una etapa dentro de él. Aunque ambos tamaños sean tres en esta demostración, la capacidad de tickets y la cantidad de etapas son decisiones independientes.

**Cómo se recibe la información.** El outer loop conserva el ticket actual mientras el inner loop solicita sus tres tiempos. Solo después de completar las etapas se marca el ticket ocupado y se avanza al siguiente. Los límites del recorrido de entrada serán `index < ticketCount` y `stage < STAGE_COUNT`.

**Cómo se calculan los totales.** Al mostrar cada ticket ocupado, necesitamos dos acumuladores con alcances distintos:

- `ticketMinutes` comienza en cero para cada ticket y suma sus tres etapas. Se declara dentro del bloque que procesa ese registro para que no arrastre el subtotal del anterior.
- `totalMinutes` comienza en cero una sola vez antes del recorrido y recibe cada subtotal. Así conserva el total de trabajo de toda la sesión.

La function `displayTicket` ahora recibe dos arguments: una copia del ticket completo y su subtotal calculado por `main`. La copia del struct incluye los tres elementos de su array miembro. La function presenta esos datos; el cálculo permanece en `main`, donde los dos acumuladores son visibles para el trace.

El siguiente programa es una **segunda versión completa**: compílalo en un archivo separado del anterior. La constante `STAGE_COUNT` se declara antes del struct para que tanto la definición del array miembro como las functions conozcan su tamaño. Es un límite fijo compartido, no una variable global que cambie durante la ejecución. La declaración del member `int stageMinutes[STAGE_COUNT] = {};` establece ceros como valores iniciales para las tres etapas de cada registro.

```cpp
#include <iostream> // Provides console input and output
#include <string> // Provides string and getline
using namespace std;

const int STAGE_COUNT = 3; // Defines the fixed number of stages in every ticket

struct RepairTicket {
    int id = 0; // Initializes the ticket identifier
    string description; // Stores the tool description
    int stageMinutes[STAGE_COUNT] = {}; // Gives each ticket its own three initialized times
    bool isEmpty = true; // Marks a new ticket slot as unused
};

void displayTicket(RepairTicket ticket, int ticketMinutes); // Receives a record copy and its calculated subtotal

int main() {
    const int CAPACITY = 3; // Limits the number of stored tickets
    const string stageNames[STAGE_COUNT] = {"Diagnosis", "Repair", "Verification"}; // Labels the fixed stage order
    RepairTicket tickets[CAPACITY] = {}; // Creates independent records with their own member arrays
    int ticketCount;
    int totalMinutes = 0; // Accumulates all occupied-ticket subtotals

    cout << "How many repair tickets (1-3): ";
    cin >> ticketCount;
    while (ticketCount < 1 || ticketCount > CAPACITY) {
        cout << "Enter a count from 1 to 3: ";
        cin >> ticketCount;
    }

    for (int index = 0; index < ticketCount; index++) { // Selects the ticket being registered
        cout << "Enter ticket ID: ";
        cin >> tickets[index].id;
        cout << "Enter tool description: ";
        getline(cin >> ws, tickets[index].description);

        for (int stage = 0; stage < STAGE_COUNT; stage++) { // Visits all three stages of the current ticket
            cout << "Enter " << stageNames[stage] << " minutes: ";
            cin >> tickets[index].stageMinutes[stage]; // Stores one time inside the selected record
            while (tickets[index].stageMinutes[stage] < 0) {
                cout << "Enter zero or a positive number of minutes: ";
                cin >> tickets[index].stageMinutes[stage];
            }
        }
        tickets[index].isEmpty = false; // Activates the ticket after all stages are entered
    }

    cout << "Registered repair tickets:" << endl;
    for (int index = 0; index < CAPACITY; index++) { // Examines every reserved ticket slot
        if (!tickets[index].isEmpty) {
            int ticketMinutes = 0; // Starts a new subtotal for this occupied ticket
            for (int stage = 0; stage < STAGE_COUNT; stage++) {
                ticketMinutes += tickets[index].stageMinutes[stage]; // Adds one stage to this ticket subtotal
            }
            displayTicket(tickets[index], ticketMinutes); // Displays the record and its completed subtotal
            totalMinutes += ticketMinutes; // Adds the subtotal once to the session total
        }
    }
    cout << "Total estimated minutes: " << totalMinutes << endl;
    return 0;
}

void displayTicket(RepairTicket ticket, int ticketMinutes) {
    cout << "Ticket " << ticket.id << ": " << ticket.description << endl;
    for (int stage = 0; stage < STAGE_COUNT; stage++) {
        cout << "  Stage " << stage + 1 << ": " << ticket.stageMinutes[stage]
             << " minutes" << endl; // Displays each time from the local record copy
    }
    cout << "  Ticket total: " << ticketMinutes << " minutes" << endl;
}
```

Prueba con los mismos dos tickets, ahora distribuyendo sus tiempos entre las tres etapas. El test mantiene el total de la versión inicial para comprobar qué cambió en la representación y qué resultado se conserva:

| Ticket ID | Descripción | Diagnosis | Repair | Verification | Total por ticket |
|---:|---|---:|---:|---:|---:|
| 501 | `Cordless drill` | 5 | 10 | 5 | 20 |
| 508 | `Bench vise` | 10 | 20 | 5 | 35 |

El subtotal del primer ticket progresa `0 → 5 → 15 → 20`. Para el segundo, `ticketMinutes` comienza nuevamente en cero y progresa `0 → 10 → 30 → 35`. En cambio, `totalMinutes` progresa `0 → 20 → 55` porque acumula una sola vez cada subtotal. El tercer slot permanece vacío y no aporta tiempos al total.

El programa debe mostrar los tres tiempos y el subtotal de cada ticket, y terminar con `Total estimated minutes: 55`. Luego cambia solo la verificación del segundo ticket de `5` a `8`: su subtotal debe ser `38` y el total general `58`.

Responde estas preguntas sobre la modificación:

1. ¿Qué tipo tiene `tickets[1].stageMinutes[2]` y qué dato del test contiene?
2. ¿Por qué ya no basta una sola lectura de minutos dentro del outer loop?
3. ¿Cuántas veces se ejecuta el body del inner loop de entrada con dos tickets? ¿Y cuántas con la capacidad completa de tres?
4. ¿Qué subtotales y total produciría el test si `ticketMinutes` se inicializara una sola vez antes del recorrido de presentación y no se reiniciara por ticket?
5. ¿Qué ocurriría si se usara `stage <= STAGE_COUNT` como condición del loop?
6. Si las tres etapas de un ticket tienen cero minutos, ¿debe omitirse ese registro?
7. ¿Es esto una matriz de enteros como `panel`? Explica la diferencia de organización.

<details>
<summary>Ver respuestas</summary>

1. Es un `int`: los minutos de verificación del segundo ticket, que en el test original valen `5`.
2. Cada ticket ahora tiene tres tiempos independientes; el inner loop recibe uno por etapa sin cambiar de ticket.
3. Seis ejecuciones con dos tickets y nueve con tres. Los reintentos del `while` no agregan etapas.
4. Mostraría `20` para el primero y `55` para el segundo; `totalMinutes` terminaría en `75`, sumando dos veces los minutos del primer ticket.
5. Intentaría acceder al índice `3` de un array cuyos índices válidos son `0`, `1` y `2`: acceso fuera de rango y undefined behavior.
6. No. `isEmpty` decide si se procesa; cero es un tiempo válido para una etapa.
7. No es una matriz declarada de enteros. Es un array de registros; cada registro contiene campos de distintos tipos, incluido su propio array de tiempos. Ambos diseños pueden requerir nested loops, pero sus datos no tienen la misma estructura.

</details>

Las ejecuciones y preguntas de ambas versiones permiten dedicar tiempo a trace, correcciones y discusión. Si alguna queda pendiente, sirve de repaso antes del lab.

---

## Resumen de la sesión

- Un array conserva una colección de elementos del mismo type con índices desde cero.
- Capacity y cantidad utilizada no significan lo mismo; los límites se validan antes del acceso.
- Un struct define un registro con members relacionados de distintos types; `.` selecciona un member.
- Un array de structs permite conservar varios registros completos. El ID identifica un registro y el index ubica su slot.
- Con slots vacíos intermedios, se recorre la capacidad y se verifica el flag de disponibilidad.
- Una matriz utiliza row y column indices; los nested loops recorren sus celdas.
- Un member de un struct también puede ser un array; seleccionar el registro y luego un elemento de ese member permite conservar colecciones dentro de cada registro.

## Próxima sesión

El Lab 11 comenzará con Basic Integer Calculator: headers, múltiples `.cpp`, compilación y linking. Después aplicaremos arrays y structs a componentes del proyecto. Semana 12 desarrollará search, sorting y los cálculos de mean, median y mode.
