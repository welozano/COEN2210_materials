# Semana 12 — Search, Sorting and Descriptive Statistics
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano
**Basado en:** Gaddis, *Starting Out with C++: From Control Structures through Objects*, 8.ª edición de trabajo — Capítulo 7, sección 7.8; Capítulo 8, secciones 8.1 y 8.3. Aplicación de los algoritmos a las estadísticas requeridas por CoRe Data Analyzer.

**Duración:** 170 min (lectura)
**Precede a:** Lab 12 — Search, sorting y estadísticas aplicadas al proyecto

---

## Objetivos

Al finalizar esta sesión, el estudiante podrá:

1. Declarar y llamar functions que reciben un array y un límite de recorrido, usando `const` cuando solo consultan sus elementos.
2. Implementar linear search para localizar un ID y distinguir entre devolver un índice y devolver el ID.
3. Recorrer un array de registros con slots vacíos para encontrar una o varias coincidencias.
4. Extraer los valores de un campo numérico a una copia compacta, conservando los registros originales.
5. Explicar y aplicar selection sort en orden ascendente.
6. Calcular mean, median y mode, incluyendo cantidades pares, ausencia de repeticiones y empates entre modas.
7. Verificar los resultados con datos pequeños y explicar cómo se aplican los algoritmos al proyecto.

---

## Cómo trabajar los ejemplos

Los cinco programas de esta guía son **completos e independientes**. Guarda cada uno con el nombre indicado; no los unas en un mismo archivo porque cada uno tiene su propio `main`. Las formas de sintaxis se identifican aparte y no son programas ejecutables.

Los datos que se desean experimentar se reciben mediante prompts y `cin`. Las tablas con valores concretos son casos de prueba: entra esos valores para comparar tu trace con la ejecución y luego cámbialos. Como en Semana 11, para estas demostraciones entra números cuando se soliciten números; la recuperación de input no numérico se conserva como requisito de validación del proyecto.

En clase, primero predice el resultado y sigue los índices en papel. Después ejecuta el programa. Las definitions que ya se explicaron se incluyen nuevamente cuando un programa las necesita para compilar de forma independiente; concentremos la discusión en lo nuevo de cada parte.

---

## Parte 1 — Functions que procesan un array (20 min)

En Semana 11 aprendimos a guardar varios valores en un array, recorrerlos con loops y agrupar campos mediante structs. En Lab 11 organizamos el analyzer en varios archivos y usamos una function para presentar un registro a la vez: el loop que seleccionaba los registros permanecía en `main`.

El próximo paso del proyecto requiere operaciones sobre la colección completa. Para buscar un ID hay que examinar varios registros; para calcular una estadística hay que reunir y procesar varios valores. Si colocamos todos esos recorridos en `main`, mezclaremos la organización del menú con los detalles de cada operación. Necesitamos que una function pueda recibir la colección y realizar su propio recorrido.

### 1.1 — De recibir un elemento a recibir la colección

Antes de estudiar search y sorting, aprenderemos cómo entregar un array a una function, cómo indicarle qué posiciones puede procesar y cómo distinguir una consulta de una modificación. Empezaremos con pesos de paquetes para observar esos efectos en pocos datos; después aplicaremos la misma forma de trabajar a colecciones de registros.

**Problema:** una estación de empaque pesa entre uno y cinco paquetes antes de enviarlos. La persona operadora entra cuántos pesará y luego sus pesos en kilogramos, en el mismo orden en que están los paquetes sobre la mesa. El programa debe conservar y mostrar esos pesos para revisarlos. Si al compararlos con la balanza detecta un error de entrada, debe poder indicar el número del paquete afectado y entrar su peso correcto, conservando los demás valores. En esta ejecución realizaremos una corrección y volveremos a mostrar la colección para comprobar el resultado. Queremos separar la presentación y la corrección en functions para que `main` organice esas tareas.

Para resolverlo necesitamos dos operaciones: una function que recorra los pesos para mostrarlos y otra que cambie el peso del paquete seleccionado. Pasar un array con la sintaxis que veremos no crea una copia de todos sus elementos: la function trabaja con los elementos del array original. Así podremos observar tanto la lectura de la colección como una modificación que se conserva después de la function call.

La siguiente forma de sintaxis muestra los dos tipos de acceso que necesitamos. Son prototypes ilustrativos:

```cpp
void displayWeights(const double weights[], int count); // Reads existing elements
void replaceWeight(double weights[], int count, int selectedIndex, double newWeight); // Updates a selected element
```

Los corchetes vacíos después del nombre del parameter indican que la function recibirá un array. El límite se recibe por separado: la function no obtiene automáticamente cuántos elementos debe procesar. En estos ejemplos, `count` indica que las posiciones utilizadas van de `0` a `count - 1`.

`const` expresa que la function no debe modificar los elementos a través de ese parameter. Por ejemplo, si `displayWeights` intenta asignar otro valor a `weights[0]`, el compiler lo rechaza. Usamos el índice `0` solo para ilustrar el acceso a un elemento concreto; la restricción de `const` aplica a todos los elementos, cualquiera que sea su índice. `replaceWeight` no lleva ese `const` porque su trabajo sí incluye una modificación. Su parameter `selectedIndex` indica cuál elemento debe cambiar; no obliga a corregir una posición fija.

No agregamos `&` al parameter del array. Esta sintaxis tiene un comportamiento distinto del parameter individual por value que ya conocíamos: modificar un elemento mediante `weights[]` sin `const` afecta al array del programa que hizo la function call.

### 1.2 — Conectar los arguments con los parameters

Para llamar estas functions se escribe el **nombre del array**, sin corchetes ni un índice, y se pasa el límite acordado. Es distinto de seleccionar un solo elemento: por ejemplo, `weights[0]` representa el primer `double` del array. Aquí el `0` es únicamente un ejemplo de índice, no una posición obligatoria para trabajar con arrays. También podemos escribir `weights[index]`, donde la variable `index` selecciona una posición válida durante la ejecución. Ambas expresiones seleccionan un elemento; el nombre del array sin índice permite pasarlo a las functions que procesan la colección.

En el programa que construiremos, el array de `main` se llama `packageWeights`, la cantidad utilizada se guarda en `packageCount` y el peso de reemplazo en `correctedWeight`. La persona seleccionará un número de paquete entre `1` y `packageCount`. Después de validar ese número, `main` le restará uno y guardará el índice correspondiente en `selectedIndex`: el paquete número `2`, por ejemplo, ocupa el índice `1`.

Estas son las dos function calls que utilizará `main` cuando tenga los datos necesarios para cada operación; el bloque ilustra las llamadas, no es un programa independiente:

```cpp
displayWeights(packageWeights, packageCount); // Displays the used elements
replaceWeight(packageWeights, packageCount, selectedIndex, correctedWeight); // Updates the selected weight
```

El array de `main` se llama `packageWeights`, pero el parameter de las definitions se llama `weights`. Los nombres pueden ser distintos: cada argument se conecta con el parameter de la misma posición. La tabla siguiente relaciona los arguments que acabamos de ver con la información que recibe cada function:

| Elemento de la function call | Qué recibe la function | Para qué sirve |
|---|---|---|
| `packageWeights` | Acceso a los elementos del array original | Leerlos o modificarlos, según el parameter |
| `packageCount` | Una copia del número de pesos utilizados | Limitar el recorrido |
| `selectedIndex` | Una copia del índice seleccionado | Identificar el elemento que se debe corregir |
| `correctedWeight` | Una copia del peso de reemplazo | Asignar el nuevo peso al elemento seleccionado |

El límite debe corresponder al array real. Pasar un `count` mayor que su capacidad no crea espacio adicional ni vuelve válidos los índices fuera del array. La validación en `main` garantiza que aquí utilizaremos entre uno y cinco pesos.

### 1.3 — Programa completo: `array_functions.cpp`

Primero se recibe y muestra la colección. Después se pide el número del paquete que necesita una corrección, se valida que corresponda a un paquete ingresado y se recibe su peso correcto. `main` convierte el número del paquete a un índice y llama a `replaceWeight`; esa function comprueba el rango del índice antes de modificar el elemento. La segunda presentación permitirá comprobar que se conservó la corrección y que los otros pesos no cambiaron.

```cpp
#include <iostream> // Provides console input and output
#include <iomanip> // Provides decimal formatting
using namespace std;

void displayWeights(const double weights[], int count);
void replaceWeight(double weights[], int count, int selectedIndex, double newWeight);

int main() {
    const int CAPACITY = 5;
    double packageWeights[CAPACITY] = {}; // Reserves five positions
    int packageCount = 0;
    int packageNumber = 0;
    double correctedWeight = 0.0;

    do {
        cout << "How many packages (1-5)? ";
        cin >> packageCount;
    } while (packageCount < 1 || packageCount > CAPACITY);

    for (int index = 0; index < packageCount; index++) {
        cout << "Enter weight for package " << index + 1 << " (kg): ";
        cin >> packageWeights[index];
    }

    cout << fixed << setprecision(2);
    cout << "Before correction: ";
    displayWeights(packageWeights, packageCount); // Passes the array and its used count

    do {
        cout << "Enter the package number to correct (1-" << packageCount << "): ";
        cin >> packageNumber;
    } while (packageNumber < 1 || packageNumber > packageCount);

    int selectedIndex = packageNumber - 1; // Converts the validated package number to an index
    cout << "Enter the corrected weight for package " << packageNumber << " (kg): ";
    cin >> correctedWeight;
    replaceWeight(packageWeights, packageCount, selectedIndex, correctedWeight);

    cout << "After correction: ";
    displayWeights(packageWeights, packageCount); // Reads the original array again
    return 0;
}

void displayWeights(const double weights[], int count) {
    for (int index = 0; index < count; index++) {
        cout << weights[index] << " "; // Reads without changing an element
    }
    cout << endl;
}

void replaceWeight(double weights[], int count, int selectedIndex, double newWeight) {
    if (selectedIndex >= 0 && selectedIndex < count) {
        weights[selectedIndex] = newWeight; // Updates only the selected element in the caller's array
    }
}
```

Con tres pesos `2`, `4` y `6`, selecciona el paquete número `2` y entra `3` como peso correcto. Ese número se convierte al índice `1`; la segunda presentación debe ser `2.00 3.00 6.00`. La function no devuelve el array: el cambio ya ocurrió en sus elementos originales. Seleccionar `0` o `4` no es válido para esta colección de tres paquetes; el programa vuelve a pedir el número antes de solicitar el peso de reemplazo.

**Para practicar por tu cuenta:** ¿qué pasaría si la function call de presentación recibiera `CAPACITY` en lugar de `packageCount` después de entrar tres pesos? ¿Qué ocurre si agregas `const` al parameter de `replaceWeight` y mantienes su assignment? Con los pesos originales `2`, `4` y `6`, ¿qué índice se usa y qué colección resulta al corregir el paquete número `3` a `5`?

<details>
<summary>Ver respuesta</summary>

La presentación mostraría cinco posiciones: los tres pesos y los dos ceros de inicialización. No sería un acceso fuera de rango en este caso, pero presentaría posiciones sin datos como si fueran paquetes. Con `const`, el assignment al elemento seleccionado no compilaría. Para comprobar ese diagnóstico puedes hacer el cambio temporalmente y luego restaurarlo. El paquete número `3` corresponde al índice `2`; al corregir su peso a `5`, la colección queda `2.00 4.00 5.00`.

</details>

---

## Parte 2 — Linear search: encontrar uno o varios registros (35 min)

Ya sabemos cómo una function puede recibir un array y un límite para recorrerlo. Hasta ahora, la presentación revisaba todos los elementos utilizados. Una consulta del proyecto necesita algo más: decidir cuáles registros cumplen lo que pide la persona usuaria, por ejemplo un ID específico o un estado.

En esta parte aprenderemos a comparar los registros durante el recorrido y a comunicar el resultado de la búsqueda. Separaremos dos necesidades: localizar un registro único y recuperar todas las coincidencias de un campo compartido. El ejemplo de equipos nos permitirá seguir los índices y los slots vacíos antes de trasladar esos patrones a las observations del analyzer.

### 2.1 — Qué significa buscar dentro de una colección

**Problema:** un centro de pruebas conserva un inventario de los equipos de sus estaciones de trabajo. Cada equipo registrado tiene un ID único y una sala asignada. Cuando se reporta una falla indicando el ID del equipo, la persona técnica necesita consultar en qué sala se encuentra para ir a revisarlo. Además, antes de una visita de verificación a una sala, necesita obtener la lista completa de los equipos registrados allí para comprobarlos uno por uno. Son dos consultas distintas: localizar un equipo específico y preparar la lista de trabajo de una sala. Un registro retirado deja su slot vacío, por lo que los equipos activos pueden quedar separados por huecos.

El programa necesita una **búsqueda**, o **search**: examinar una colección para localizar datos que cumplan un criterio. Ese criterio puede producir un solo resultado —un ID único— o varios —equipos de la misma sala—. No debemos asumir que el ID coincide con la posición del registro.

**Linear search**, también llamada sequential search, revisa las posiciones una tras otra. En un array de structs como el nuestro, primero comprueba si el slot está ocupado y después compara el campo requerido. No necesita que los registros estén ordenados.

Para consultar un ID único, el resultado será **el índice del registro encontrado**. Si no aparece, usaremos `-1`. Ese valor funciona como señal de ausencia porque nunca es un índice válido; no debe utilizarse para acceder al array.

Antes de ver el código, consideremos una ejecución de ejemplo: se registraron cuatro equipos con IDs `42`, `64`, `57` y `81`, en ese orden. Después se retiró el segundo equipo, ID `64`, y se marcó su slot como vacío sin desplazar los otros registros. La siguiente tabla muestra el estado posterior al retiro y las decisiones al buscar el ID `81`. Los datos del equipo retirado pueden permanecer en sus campos, pero su flag indica que ya no participa en el inventario activo:

| Index | Estado del slot | ID | Sala | Decisión al buscar `81` |
|---:|---|---:|---|---|
| 0 | Ocupado | 42 | Assembly Lab | Comparar: no coincide |
| 1 | Vacío | 64 | Assembly Lab | Ignorar sus campos: equipo retirado |
| 2 | Ocupado | 57 | Test Lab | Comparar: no coincide |
| 3 | Ocupado | 81 | Assembly Lab | Coincide: devolver `3` |

El resultado es `3`, no `81`. El programa que recibe ese resultado puede consultar el registro en el índice `3`. Si se busca `99`, debe terminar el recorrido y devolver `-1`.

### 2.2 — Una coincidencia frente a todas las coincidencias

Volvamos a las dos tareas de la persona técnica usando los datos de la tabla anterior. Si el reporte de falla identifica al equipo `81`, la pregunta es «¿en qué sala está ese equipo?». Al encontrar el ID `81` en el índice `3`, sabemos que está en `Assembly Lab`. Como los IDs son únicos, ningún otro registro puede aportar otro resultado para ese mismo equipo: la consulta está completa y podemos terminar la búsqueda.

En cambio, si la persona prepara una visita de verificación a `Assembly Lab`, la pregunta es «¿cuáles son todos los equipos que debo revisar en esa sala?». Encontrar el equipo `42` en el índice `0` solo agrega un equipo a la lista de trabajo. Si terminamos allí, el equipo `81`, que también pertenece a esa sala, quedaría fuera de la lista y podría quedarse sin revisar.

Para completar esa segunda tarea, mantenemos fijo el nombre de sala solicitado y avanzamos por los registros restantes. No estamos buscando otra sala llamada igual ni volviendo a revisar el mismo equipo: estamos comprobando qué otros equipos tienen `Assembly Lab` en su campo `room`. En nuestro ejemplo, el recorrido hace lo siguiente:

1. Índice `0`: el equipo `42` pertenece a `Assembly Lab`; mostrar su ID y contar una coincidencia.
2. Índice `1`: el slot está vacío; continuar sin consultar sus campos como un registro activo.
3. Índice `2`: el equipo `57` pertenece a `Test Lab`; no incluirlo en la lista solicitada.
4. Índice `3`: el equipo `81` pertenece a `Assembly Lab`; mostrar su ID y contar la segunda coincidencia.

Al terminar todos los slots, la lista contiene los IDs `42` y `81`, y la cantidad de coincidencias es `2`. Solo entonces sabemos que no quedan registros por comprobar. Si ningún equipo pertenece a la sala solicitada, la lista estará vacía y la cantidad será `0`.

Representaremos cada equipo con un struct llamado `Equipment`, cuyos campos serán `id`, `room` e `isEmpty`. El array contendrá esos registros completos, como el array de observations de Lab 11. Sobre esa colección usaremos dos functions con resultados distintos:

- `findEquipmentById` devuelve el índice en cuanto encuentra el ID solicitado; si termina el recorrido sin encontrarlo, devuelve `-1`. `main` usa ese resultado para mostrar la sala del equipo o informar que no aparece.
- `displayEquipmentByRoom` muestra el ID de cada equipo de la sala solicitada y acumula las coincidencias. Devuelve esa cantidad después de terminar el recorrido, porque la tarea requiere una lista completa.

Ambas reciben `const Equipment equipment[]`, ya que buscar no debe alterar los registros. El segundo parameter se llama `capacity`: aquí el recorrido debe alcanzar todos los slots, incluidos los que vienen después de un hueco. Recorrer solo la cantidad de equipos activos podría dejar el último sin revisar.

### 2.3 — Programa completo: `equipment_search.cpp`

Queremos comprobar que las búsquedas encuentren equipos ubicados **después de un slot vacío**. Ese estado puede aparecer en el inventario cuando se retira un registro: el hueco no significa que los registros de las posiciones siguientes hayan dejado de existir. Una búsqueda que terminara al encontrar el primer slot vacío daría resultados incompletos.

El programa recibirá cuatro equipos en posiciones consecutivas y mostrará una lista numerada con sus IDs y salas. Después, la persona seleccionará cuál retirar del inventario. Se validará que el número esté entre `1` y `4`, se convertirá a un índice restando uno y se marcará ese slot con `isEmpty = true`. Quedarán tres registros activos; los otros equipos conservarán sus posiciones. El programa no borra sus campos ni desplaza elementos: las búsquedas reconocerán el retiro mediante el flag.

Para reproducir la ejecución explicada en 2.1 y 2.2, entra estos datos y selecciona el equipo número `2` para retirarlo. Son datos de prueba, no valores fijados en el código; puedes cambiar los equipos y la selección en otra ejecución. Entra IDs distintos, pues esta demostración supone su unicidad y no implementa aún la validación de duplicados.

| Número mostrado a la persona | Index | ID de prueba | Sala |
|---:|---:|---:|---|
| 1 | 0 | 42 | Assembly Lab |
| 2 | 1 | 64 | Assembly Lab |
| 3 | 2 | 57 | Test Lab |
| 4 | 3 | 81 | Assembly Lab |

Después del retiro, buscar `81` debe llegar al índice `3` a pesar del hueco. Buscar `64` debe informar que no se encuentra entre los equipos activos. La consulta por `Assembly Lab` debe mostrar `42` y `81`, excluyendo el equipo retirado aunque conserve ese nombre de sala en su registro.

Después realiza las dos consultas. Para las salas utiliza `getline(cin >> ws, ...)`, el patrón de Semana 11 que descarta whitespace inicial pendiente y conserva los espacios interiores del nombre.

```cpp
#include <iostream> // Provides console input and output
#include <string> // Provides string and getline
using namespace std;

struct Equipment {
    int id = 0;
    string room;
    bool isEmpty = true; // Marks unused positions
};

int findEquipmentById(const Equipment equipment[], int capacity, int targetId);
int displayEquipmentByRoom(const Equipment equipment[], int capacity, string targetRoom);

int main() {
    const int CAPACITY = 4;
    Equipment equipment[CAPACITY] = {};
    int equipmentNumber = 0;
    int targetId = 0;
    string targetRoom;

    for (int index = 0; index < CAPACITY; index++) {
        cout << "Enter a unique ID for equipment " << index + 1 << ": ";
        cin >> equipment[index].id;
        cout << "Enter its room: ";
        getline(cin >> ws, equipment[index].room);
        equipment[index].isEmpty = false; // Registers every entered equipment record
    }

    cout << "Registered equipment:" << endl;
    for (int index = 0; index < CAPACITY; index++) {
        cout << index + 1 << ". ID: " << equipment[index].id
             << " | Room: " << equipment[index].room << endl;
    }

    do {
        cout << "Enter the equipment number to remove (1-" << CAPACITY << "): ";
        cin >> equipmentNumber;
    } while (equipmentNumber < 1 || equipmentNumber > CAPACITY);

    int removedIndex = equipmentNumber - 1; // Converts the validated list number to an index
    equipment[removedIndex].isEmpty = true; // Removes the record from the active inventory
    cout << "Removed equipment ID: " << equipment[removedIndex].id << endl;

    cout << "Enter the equipment ID to find: ";
    cin >> targetId;
    int foundIndex = findEquipmentById(equipment, CAPACITY, targetId);

    if (foundIndex != -1) { // Checks the result before accessing the array
        cout << "Found at index " << foundIndex << endl;
        cout << "ID: " << equipment[foundIndex].id << endl;
        cout << "Room: " << equipment[foundIndex].room << endl;
    } else {
        cout << "Equipment not found." << endl;
    }

    cout << "Enter a room to list its equipment: ";
    getline(cin >> ws, targetRoom);
    int matchCount = displayEquipmentByRoom(equipment, CAPACITY, targetRoom);
    cout << "Matches: " << matchCount << endl;
    return 0;
}

int findEquipmentById(const Equipment equipment[], int capacity, int targetId) {
    for (int index = 0; index < capacity; index++) {
        if (!equipment[index].isEmpty && equipment[index].id == targetId) {
            return index; // Ends the search at the first occupied match
        }
    }
    return -1; // Reports that no occupied record matched
}

int displayEquipmentByRoom(const Equipment equipment[], int capacity, string targetRoom) {
    int matchCount = 0;
    for (int index = 0; index < capacity; index++) {
        if (!equipment[index].isEmpty && equipment[index].room == targetRoom) {
            cout << "ID: " << equipment[index].id << endl;
            matchCount++; // Counts every match instead of ending the search
        }
    }
    return matchCount;
}
```

El hueco ahora es consecuencia del retiro seleccionado, no de una posición omitida durante la entrada. En la ejecución de prueba, `equipmentNumber` vale `2` y `removedIndex` vale `1`. Los registros de los índices `2` y `3` siguen activos; por eso las functions de búsqueda recorren la capacidad y consultan el flag en cada posición. Si en otra ejecución retiras un equipo diferente, cambia el slot vacío sin cambiar la lógica de búsqueda.

**Expected output — equipo activo después del hueco:** entra los cuatro equipos de la tabla, retira el número `2`, busca el ID `81` y consulta la sala `Assembly Lab`. Esta transcripción incluye los valores escritos por la persona después de cada prompt:

```text
Enter a unique ID for equipment 1: 42
Enter its room: Assembly Lab
Enter a unique ID for equipment 2: 64
Enter its room: Assembly Lab
Enter a unique ID for equipment 3: 57
Enter its room: Test Lab
Enter a unique ID for equipment 4: 81
Enter its room: Assembly Lab
Registered equipment:
1. ID: 42 | Room: Assembly Lab
2. ID: 64 | Room: Assembly Lab
3. ID: 57 | Room: Test Lab
4. ID: 81 | Room: Assembly Lab
Enter the equipment number to remove (1-4): 2
Removed equipment ID: 64
Enter the equipment ID to find: 81
Found at index 3
ID: 81
Room: Assembly Lab
Enter a room to list its equipment: Assembly Lab
ID: 42
ID: 81
Matches: 2
```

La lista numerada inicial muestra los cuatro equipos porque se presenta **antes del retiro**. Las consultas posteriores consideran solo los tres activos: encuentran `81` después del hueco y excluyen `64` de la lista de `Assembly Lab`.

**Expected output — equipo retirado:** ejecuta nuevamente el programa con los mismos cuatro equipos y retira otra vez el número `2`. Esta vez busca el ID `64` y consulta `Assembly Lab`. El tramo final debe ser:

```text
Enter the equipment number to remove (1-4): 2
Removed equipment ID: 64
Enter the equipment ID to find: 64
Equipment not found.
Enter a room to list its equipment: Assembly Lab
ID: 42
ID: 81
Matches: 2
```

El mensaje no significa que nunca se ingresó ese ID: significa que ya no corresponde a un registro activo. Para comprobar también una sala sin coincidencias, repite la ejecución y entra `Storage Room` en la consulta por sala, conservando los datos de la tabla. Esa consulta debe terminar así:

```text
Enter a room to list its equipment: Storage Room
Matches: 0
```

### 2.4 — Aplicar las búsquedas al proyecto CoRe Data Analyzer

Recordemos el propósito del [proyecto final, CoRe Data Analyzer](../final_project/COEN2210_ProyectoFinal_DataScience.md): construir un programa de consola para consultar y analizar resultados electorales por condado de Estados Unidos. Cada registro, llamado observation en el enunciado, reúne un ID, el estado (`state`), el condado (`county`), cantidades de votos y el porcentaje de votos demócratas (`dem_share`). El dataset suministrado contiene 50 observations de Pennsylvania, Ohio y Florida.

En Lab 11 comenzamos su representación mediante un struct `Observation` y un array con capacidad de 100 registros. El prototipo recibía de uno a tres registros por consola y mostraba los ocupados; todavía no implementaba las búsquedas. Su campo interno `isEmpty` permite distinguir un slot disponible de uno que contiene una observation activa. Por eso, igual que en el ejemplo de equipos, una búsqueda debe recorrer los slots y comprobar su disponibilidad antes de comparar los campos.

Ahora podemos relacionar cada consulta del proyecto con el ejemplo que acabamos de ejecutar. Buscar una observation por su ID corresponde a buscar un equipo por su ID: la function devuelve el índice encontrado o `-1`. Buscar por estado o por nombre de condado corresponde a listar equipos por sala: varios registros pueden compartir ese campo, así que se muestran todas las coincidencias ocupadas, sin terminar al encontrar la primera.

La comparación de `string` que usamos es exacta y distingue mayúsculas de minúsculas; en el ejemplo de equipos, `Test Lab` y `test lab` no coinciden. Al aplicar ese patrón a `state` o `county`, el texto de búsqueda debe coincidir con el almacenado. No se está implementando búsqueda por fragmentos ni normalización de nombres.

El proyecto también requiere agregar observations con un ID entrado por la persona usuaria y rechazar IDs duplicados entre los registros activos. La misma búsqueda por ID permite comprobar esa condición antes de solicitar los demás campos. Cuando se implemente la eliminación, la búsqueda deberá ignorar los slots marcados como vacíos, aunque todavía contengan datos del registro eliminado: el flag decide si ese registro participa en la colección actual.

Una búsqueda exitosa puede terminar en la primera posición; una búsqueda fallida necesita revisar toda la región acordada. Con cien slots, esto sigue siendo un recorrido pequeño y fácil de verificar. No necesitamos ordenar las observations ni introducir binary search para cumplir estas consultas.

**Para practicar por tu cuenta:** usa los cuatro equipos de la tabla de 2.3 y retira el segundo. ¿Qué devuelven las búsquedas de IDs `42`, `81`, `64` y `99`? Repite el programa para probar cada ID. ¿Por qué buscar `64` no debe encontrarlo aunque su campo `id` todavía conserve ese valor? ¿Qué ocurre si la búsqueda por sala hace `return matchCount` inmediatamente después de la primera coincidencia? ¿Puede utilizarse `equipment[targetId]` para consultar el resultado? ¿Qué sucede si seleccionas `0` o `5` como número del equipo que deseas retirar?

<details>
<summary>Ver respuesta</summary>

Los resultados son `0`, `3`, `-1` y `-1`. El registro del ID `64` está marcado como vacío y no participa en la búsqueda, aunque sus campos conserven los datos anteriores. Terminar en la primera coincidencia de sala omitiría el equipo `81` de `Assembly Lab`. El ID no es un índice: `equipment[81]` quedaría fuera del array de cuatro posiciones. El acceso debe usar el índice devuelto y solo después de descartar `-1`. Las selecciones `0` y `5` se rechazan y se vuelve a pedir un número entre `1` y `4`, antes de convertirlo a índice o acceder al registro.

</details>

---

## Parte 3 — Extraer valores y ordenar una copia (35 min)

Las búsquedas de la parte anterior permiten localizar registros sin cambiar su orden. En CoRe Data Analyzer, el proyecto de resultados electorales por condado que retomamos en 2.4, también necesitaremos analizar los valores de un campo numérico, por ejemplo los votos demócratas de todas las observations activas. Para identificar los valores centrales y reunir las repeticiones, prepararemos una lista numérica de menor a mayor sin alterar los registros de los condados.

En esta parte aprenderemos ese proceso con pesos de paquetes: conservaremos un array original, copiaremos sus elementos utilizados y ordenaremos la copia mediante selection sort. El resultado de esta parte será mostrar ambas listas y comprobar que solo la copia cambió de orden. En la Parte 4 usaremos el orden para calcular estadísticas; en la práctica guiada extraeremos los valores desde un array de structs con slots vacíos.

### 3.1 — Por qué necesitamos otra organización de los datos

**Problema:** retomemos la estación de empaque de la Parte 1, donde una persona pesa los paquetes de un lote y registra sus pesos en kilogramos en el orden en que los recibe. Ahora la persona responsable necesita identificar qué peso queda en el centro cuando se consideran desde el más liviano hasta el más pesado; usará ese dato como resumen del lote. No puede seleccionar simplemente la posición central de la lista recibida, porque los paquetes no necesariamente se pesaron en orden de peso.

Por ejemplo, con pesos `7`, `3`, `7`, `1` y `5`, el tercer dato recibido es `7`, pero al organizarlos de menor a mayor quedan `1 3 5 7 7` y el central es `5`. Estos valores ilustran la necesidad de ordenar; no están fijados en el programa. También debemos conservar la lista original: su posición sigue indicando a cuál paquete pesado corresponde cada valor. Prepararemos una segunda lista para el análisis y mantendremos intacta la primera para las consultas y correcciones.

**Sorting** es reorganizar una colección según un criterio de orden. Aquí utilizaremos orden ascendente: cada valor debe ser menor o igual que el siguiente. Los valores repetidos se conservan; ordenar no significa eliminar duplicados.

La solución será copiar los pesos a un array separado y ordenar esa copia. C++ no permite copiar estos arrays de tamaño fijo mediante un assignment entre sus nombres: copiaremos elemento por elemento con un loop. El array `originalWeights` conservará los pesos recibidos; `sortedWeights` comenzará con los mismos valores y será el único que entregaremos a la function de sorting. Su nombre expresa para qué lo usaremos, pero declararlo con ese nombre no ordena sus elementos.

Para esta demostración, la persona entrará una cantidad de uno a cinco paquetes y un peso positivo para cada uno. Los pesos utilizados ocuparán posiciones consecutivas desde el índice `0`; no habrá retiros ni huecos. Si entra tres pesos, solo se copiarán y ordenarán esos tres. Las otras dos posiciones reservadas seguirán inicializadas en cero, pero no representan paquetes y no deben participar en el análisis.

Cuando trabajemos con registros completos, como las observations del proyecto, tampoco debemos ordenar un campo dentro de los registros dejando los demás inmóviles: asociaríamos los valores a IDs equivocados. En la práctica guiada recorreremos los slots ocupados y extraeremos sus pesos a una copia compacta antes de ordenar. Aquí aislamos primero la copia y el sorting de valores numéricos para entender sus pasos.

### 3.2 — Selection sort: fijar una posición en cada pasada

Un **algoritmo** es una secuencia de pasos para resolver un problema. Usaremos **selection sort**, que coloca el menor valor pendiente en la primera posición que falta ordenar. Llamaremos **pasada** al proceso de revisar esa región pendiente y dejar una posición resuelta. Después de cada pasada, el array tiene una parte inicial que ya contiene los valores más pequeños en su orden definitivo y una parte que todavía falta ordenar. Al comenzar, ninguna posición está resuelta.

En cada pasada:

1. Elegir la primera posición pendiente, llamada `start` en el programa.
2. Revisar desde esa posición hasta el final para localizar el menor valor pendiente.
3. Intercambiar ese valor con el de `start`.
4. Avanzar `start`: esa posición ya contiene el menor valor de la región que acabamos de revisar.

La posición `start` cambia durante la ejecución; no es un índice fijo que debamos repetir en todas las pasadas. El código necesitará además `minimumIndex`, que guarda **el índice del menor valor encontrado hasta ese momento**, no el peso mismo. Si `minimumIndex` vale `3`, el peso candidato se consulta con `values[3]`. La variable `index` irá revisando las otras posiciones para decidir si hay un candidato menor.

La búsqueda del menor no termina en cuanto aparece un valor más pequeño que el inicial. En la primera pasada sobre `7 3 7 1 5`, comenzamos considerando el `7` del índice `0` como el menor conocido. Al comparar el `3` del índice `1`, encontramos un candidato mejor, pero todavía quedan posiciones sin revisar. Si termináramos ahí, colocaríamos `3` al principio aunque más adelante está `1`.

Continuamos comparando: el siguiente `7` no mejora el candidato; el `1` sí lo mejora; el último `5` no lo cambia. Solo después de revisar toda la región pendiente sabemos que `1` es su menor valor y podemos intercambiarlo con el de `start`. Esta es la diferencia entre encontrar **un valor que cumple una condición** y encontrar **el menor de todos los valores pendientes**: la segunda tarea exige terminar las comparaciones de esa región.

En esa primera pasada ya terminamos de buscar el menor: `start` vale `0` y `minimumIndex` vale `3`. Esos son **índices**, mientras que los pesos guardados en esas posiciones son `values[0] = 7` y `values[3] = 1`. Queremos que el `1` termine en el índice `0` y el `7` en el índice `3`, sin perder ninguno. Este intercambio se llama **swap**.

Un assignment copia el valor del lado derecho en la variable o elemento del lado izquierdo, reemplazando lo que había allí. No intercambia ambos valores automáticamente. Por eso, antes de sobrescribir el `7`, lo guardamos en una variable auxiliar llamada `temporary`. Esa variable guarda un peso; no es un índice ni una posición adicional del array.

El siguiente fragmento muestra los tres statements del intercambio que aparecerán dentro de la function de sorting en 3.3. No es un programa independiente. Los índices se expresan con variables para que el mismo código pueda intercambiar las posiciones seleccionadas en cualquier pasada:

```cpp
double temporary = values[start]; // Saves the weight that will be overwritten
values[start] = values[minimumIndex]; // Copies the smallest weight into its final position
values[minimumIndex] = temporary; // Copies the saved weight into the other position
```

**Cómo leer la tabla:** sigue las filas de arriba hacia abajo. La primera muestra el estado antes de ejecutar esos statements; cada fila numerada muestra los valores **después de ejecutar un statement**, en el mismo orden que el fragmento. Las columnas `values[0]` y `values[3]` son los pesos almacenados en esas posiciones, no los índices. La última columna muestra el peso conservado fuera del array en `temporary`. Durante estos tres pasos, `start` sigue valiendo `0` y `minimumIndex` sigue valiendo `3`; solo cambian los valores almacenados.

Mostramos únicamente las dos posiciones que intervienen en este swap. Las posiciones `1`, `2` y `4` del array no cambian durante el intercambio. Los índices `0` y `3` corresponden a esta primera pasada del caso de prueba; no son posiciones que deban fijarse en el algoritmo.

| Estado | Statement que acaba de ejecutarse | `values[0]` (peso) | `values[3]` (peso) | `temporary` (peso) |
|---|---|---:|---:|---:|
| Antes del swap | Ninguno todavía | 7 | 1 | Todavía no declarada |
| Después del paso 1 | `double temporary = values[start];` | 7 | 1 | 7 |
| Después del paso 2 | `values[start] = values[minimumIndex];` | 1 | 1 | 7 |
| Después del paso 3 | `values[minimumIndex] = temporary;` | 1 | 7 | 7 |

Por ejemplo, la fila «Después del paso 1» muestra que guardar el `7` en `temporary` no modifica el array: las dos posiciones todavía contienen `7` y `1`. En el paso 2 aparecen dos unos en el array porque el assignment copia el `1` y reemplaza el `7` del índice `0`; el peso `7` sigue disponible en `temporary`. El paso 3 lo copia al índice `3` y completa el swap. La variable auxiliar conserva su valor, pero ya cumplió su propósito para este intercambio.

Al terminar esos tres statements, la copia completa pasó de `7 3 7 1 5` a `1 3 7 7 5`. Si hubiéramos sobrescrito el `7` sin guardarlo primero, no podríamos recuperarlo consultando el índice `0`, porque allí ya habría un `1`.

La tabla anterior amplió **un solo swap**. La siguiente cambia de escala: muestra el array completo al terminar **cada pasada de selection sort**, después de buscar el menor y realizar el intercambio si hace falta. Lee también sus filas de arriba hacia abajo. La columna central identifica el tramo inicial cuyas posiciones ya están resueltas; la última muestra tanto ese tramo como los elementos todavía pendientes. Son estados sucesivos de la misma copia, no arrays nuevos.

| Estado | Región inicial ya ordenada | Copia completa |
|---|---|---|
| Inicial | Ninguna | `7 3 7 1 5` |
| Después de `start = 0` | `1` | `1 3 7 7 5` |
| Después de `start = 1` | `1 3` | `1 3 7 7 5` |
| Después de `start = 2` | `1 3 5` | `1 3 5 7 7` |
| Después de `start = 3` | `1 3 5 7` | `1 3 5 7 7` |

En las pasadas con `start = 1` y `start = 3` no se intercambian valores: el menor de la región pendiente ya está en `start`. Esa posición también queda resuelta, aunque no cambie el contenido del array.

El programa implementará este proceso con dos loops. El **outer loop** elige sucesivamente la posición que se va a resolver; el **inner loop** revisa las posiciones que faltan para encontrar el menor candidato de esa pasada. No hace falta una pasada para la última posición: al colocar las otras cuatro, el valor restante ya ocupa su lugar. Por eso el outer loop usa `start < count - 1`. El inner loop empieza en `start + 1`, porque inicialmente asumimos que el menor está en `start`, y continúa mientras `index < count` para incluir la última posición utilizada sin salir de la colección.

### 3.3 — Programa completo: `weight_sort.cpp`

Este es un programa independiente de los anteriores: recibe un lote nuevo de uno a cinco pesos positivos, los copia y ordena la copia con una function. Finalmente muestra ambas colecciones para verificar que el original conserva su orden. No calcula todavía el peso central ni las otras estadísticas; ese será el paso siguiente de la guía.

Dentro del loop de entrada, cada lectura válida se guarda en `originalWeights[index]` y se copia a `sortedWeights[index]`. La function call `selectionSort(sortedWeights, weightCount)` entrega solo la copia y su cantidad utilizada. Dentro de la definition, el parameter `values` permite modificar esos mismos elementos de `sortedWeights`; no crea una tercera copia. Observa esa conexión al seguir el programa.

```cpp
#include <iostream> // Provides console input and output
#include <iomanip> // Provides decimal formatting
using namespace std;

void selectionSort(double values[], int count);
void displayValues(const double values[], int count);

int main() {
    const int CAPACITY = 5;
    double originalWeights[CAPACITY] = {};
    double sortedWeights[CAPACITY] = {};
    int weightCount = 0;

    do {
        cout << "How many weights (1-5)? ";
        cin >> weightCount;
    } while (weightCount < 1 || weightCount > CAPACITY);

    for (int index = 0; index < weightCount; index++) {
        do {
            cout << "Enter weight " << index + 1 << " (kg, greater than zero): ";
            cin >> originalWeights[index];
        } while (originalWeights[index] <= 0.0);
        sortedWeights[index] = originalWeights[index]; // Copies one element
    }

    selectionSort(sortedWeights, weightCount); // Changes only the copy
    cout << fixed << setprecision(2);
    cout << "Original: ";
    displayValues(originalWeights, weightCount);
    cout << "Sorted copy: ";
    displayValues(sortedWeights, weightCount);
    return 0;
}

void selectionSort(double values[], int count) {
    for (int start = 0; start < count - 1; start++) {
        int minimumIndex = start; // Stores the index of the smallest candidate so far
        for (int index = start + 1; index < count; index++) {
            if (values[index] < values[minimumIndex]) {
                minimumIndex = index; // Remembers the smallest pending value
            }
        }
        if (minimumIndex != start) {
            double temporary = values[start]; // Preserves the value before overwriting it
            values[start] = values[minimumIndex];
            values[minimumIndex] = temporary;
        }
    }
}

void displayValues(const double values[], int count) {
    for (int index = 0; index < count; index++) {
        cout << values[index] << " ";
    }
    cout << endl; // Ends the displayed collection
}
```

La function `selectionSort` no lleva `const` porque modifica elementos. `displayValues` sí lo lleva porque solo los consulta. La condición `minimumIndex != start` evita un intercambio innecesario cuando el menor ya está en su posición.

### 3.4 — Expected outputs y análisis del resultado

Para reproducir las pasadas de 3.2, entra cantidad `5` y los pesos `7`, `3`, `7`, `1` y `5`. Esta transcripción incluye lo escrito por la persona después de cada prompt. El programa muestra el resultado final; los estados intermedios se siguen en las tablas, no se imprimen en esta versión.

```text
How many weights (1-5)? 5
Enter weight 1 (kg, greater than zero): 7
Enter weight 2 (kg, greater than zero): 3
Enter weight 3 (kg, greater than zero): 7
Enter weight 4 (kg, greater than zero): 1
Enter weight 5 (kg, greater than zero): 5
Original: 7.00 3.00 7.00 1.00 5.00
Sorted copy: 1.00 3.00 5.00 7.00 7.00
```

El original mantiene el orden de entrada y la copia queda en orden ascendente. Ambos contienen los mismos cinco pesos, incluidos los dos `7`: ningún intercambio debe perder, agregar o eliminar valores.

En una nueva ejecución, entra cantidad `3` y pesos `2.5`, `1.5` y `2.5`. El tramo final esperado es:

```text
Original: 2.50 1.50 2.50
Sorted copy: 1.50 2.50 2.50
```

Aunque la capacidad siga siendo cinco, no aparecen los dos ceros de las posiciones no utilizadas. Sorting y presentación reciben `weightCount`, que en esta ejecución vale tres. Esta es una comprobación distinta de ordenar correctamente: también debemos procesar exactamente los datos del lote.

Con cinco elementos, los inner loops realizan `4 + 3 + 2 + 1 = 10` comparaciones entre valores, aunque el input ya venga ordenado. El algoritmo es adecuado para entender el proceso y para la capacidad pequeña del proyecto; no estamos afirmando que sea el más rápido para cualquier volumen de datos.

**Para practicar por tu cuenta:**

1. En la primera pasada del caso `7 3 7 1 5`, ¿qué guardan `minimumIndex` y `values[minimumIndex]` al terminar el inner loop? ¿Por qué encontrar el `3` no permite terminar esa búsqueda?
2. ¿Qué sucede con un solo peso? ¿Y con cinco pesos iguales?
3. Con tres pesos positivos y capacidad cinco, ¿qué error provocaría pasar `CAPACITY` en lugar de `weightCount` a la function de sorting?
4. ¿Qué colección cambiaría si la function call de sorting recibiera `originalWeights`?
5. Si luego aplicamos el algoritmo a pesos extraídos de registros con ID, ¿por qué no debemos escribir los pesos ordenados sobre los campos de los registros originales en ese nuevo orden?

<details>
<summary>Ver respuesta</summary>

1. `minimumIndex` vale `3`; `values[minimumIndex]` vale `1`. Encontrar `3` solo mejora el candidato conocido: todavía falta revisar las posiciones siguientes, entre ellas la que contiene `1`.
2. Con un peso no se ejecuta el outer loop; la colección ya está ordenada. Con cinco iguales se realizan las comparaciones, pero no hay intercambios porque ningún candidato es estrictamente menor que el de `start`.
3. El algoritmo incluiría los dos ceros de inicialización y los movería al comienzo de la copia. No accedería fuera de la capacidad, pero mezclaría posiciones sin datos con pesos reales. Mostrar después solo tres posiciones daría dos ceros y el menor peso, omitiendo otros pesos del lote.
4. Se modificaría el orden del original; el nombre del parameter `values` no protege ni copia el array recibido.
5. Reasignar pesos ordenados a registros sin mover sus demás campos asociaría datos a los paquetes equivocados. La copia numérica se utiliza para el análisis y no para sobrescribir los campos originales.

</details>

---

## Parte 4 — Mean, median y mode (45 min)

Ya podemos conservar una colección original y obtener una copia numérica ordenada. Sin embargo, mostrar esa lista todavía deja a la persona usuaria la tarea de interpretar los datos. El proyecto pide que el programa produzca tres resúmenes numéricos: mean, median y mode.

En esta parte definiremos qué representa cada medida y cómo calcularla con los arrays que sabemos recorrer. Aprovecharemos el orden de la copia para localizar el centro y contar repeticiones, y distinguiremos los casos que requieren decisiones diferentes: colección vacía, cantidad par o impar, ausencia de repeticiones y empates entre modas. Esos resultados completarán el conjunto de operaciones que integraremos en la práctica guiada.

### 4.1 — Tres preguntas sobre la misma colección

**Problema:** al cerrar el lote de la estación de empaque, la persona responsable prepara un resumen de sus pesos. Además de conservar la lista para consultar paquetes individuales, necesita informar el peso promedio por paquete, el peso que ocupa el centro de la lista ordenada y el peso que más se repite, si existe una repetición. Son preguntas distintas: conocer el promedio no revela necesariamente ni el centro de la lista ni sus valores más frecuentes.

Con los pesos `7`, `3`, `7`, `1` y `5`, el promedio es `4.6` kg, el peso central es `5` kg y el más frecuente es `7` kg. El promedio distribuye la suma total de pesos entre los cinco paquetes; no significa que alguno pese exactamente `4.6` kg. El valor central describe la posición intermedia al ordenar los pesos. El más frecuente identifica un peso repetido, pero no garantiza que sea el de la mayoría de los paquetes. El programa calculará los tres para que el resumen no confunda esas descripciones.

La siguiente tabla da nombre a esas tres preguntas y anticipa qué procedimiento necesitaremos para responder cada una. Después desarrollaremos sus cálculos por separado antes de reunirlos en el programa.

| Medida | Pregunta que responde | Procedimiento |
|---|---|---|
| Mean — media aritmética | ¿Cuál es el promedio de los valores? | Sumar y dividir entre la cantidad |
| Median — mediana | ¿Qué valor ocupa el centro de la colección ordenada? | Seleccionar el central o promediar los dos centrales |
| Mode — moda | ¿Qué valor o valores aparecen más veces? | Comparar las frecuencias de los valores |

Mean no requiere ordenar. Median sí requiere el orden; para mode aprovecharemos ese mismo orden porque deja juntas las repeticiones de cada valor. Ninguna medida se calculará cuando la cantidad utilizada sea cero. Cero paquetes significa ausencia de datos, no un lote cuyo peso promedio sea cero.

### 4.2 — Mean: dividir usando la cantidad real

Para los pesos `7`, `3`, `7`, `1` y `5`, la suma es `23` y hay cinco datos. Su mean es `23 / 5 = 4.6`. Debemos dividir entre la cantidad utilizada, no entre la capacidad del array.

En el código usaremos un acumulador `double total`. Por eso `total / count` produce un resultado con parte decimal aunque `count` sea `int`: el cálculo utiliza floating-point arithmetic. Si ambos operands fueran enteros, la división entera descartaría la parte fraccionaria antes de guardar el resultado.

La function de mean solo consulta sus elementos y devuelve un `double`. Su requisito de uso será `count > 0`; `main` comprobará ese requisito antes de llamarla.

### 4.3 — Median: posiciones centrales e índices desde cero

Después del sorting, nuestro ejemplo queda `1 3 5 7 7`. Con cinco elementos, el valor central es el tercero, cuyo índice es `2`. La división entera `count / 2` produce precisamente `2` cuando `count` vale `5`.

Con cuatro elementos ordenados, por ejemplo `1 3 7 7`, no hay un único elemento central. Los dos centrales tienen índices `1` y `2`; se promedian sus valores: `(3 + 7) / 2.0 = 5.0`.

La siguiente tabla reúne las reglas para poder traducirlas al programa sin confundir posición humana e índice:

| Cantidad utilizada | Índices centrales | Cálculo |
|---|---|---|
| Impar | `count / 2` | Valor de ese elemento |
| Par | `count / 2 - 1` y `count / 2` | Promedio de esos dos valores |

Usaremos `count % 2` para distinguir ambos casos. Como el array contiene `double`, sus valores ya permiten un promedio decimal; escribir `/ 2.0` también hace explícita esa intención. Un solo elemento tiene mean y median iguales a su valor.

### 4.4 — Mode: contar grupos de valores iguales

**Frecuencia** es la cantidad de veces que aparece un valor. En la copia ordenada `1 3 5 7 7`, las frecuencias son uno para `1`, `3` y `5`, y dos para `7`. La moda es `7` porque su frecuencia es la mayor.

Para este curso y el proyecto, aplicaremos estas reglas:

- Si ninguna frecuencia supera uno, mostrar `N/A`.
- Si un valor tiene la frecuencia máxima, mostrar ese valor.
- Si varios valores comparten la frecuencia máxima y esta es mayor que uno, mostrar todos esos valores.

Por ejemplo, `1 1 3 7 7` tiene dos modas, `1` y `7`, ambas con frecuencia dos. Un solo dato produce `N/A` bajo la regla de ausencia de repeticiones del proyecto.

En el array ordenado, cada grupo de valores iguales ocupa posiciones consecutivas. Para contarlos, comenzaremos en el primer valor del grupo, avanzaremos mientras los siguientes sean iguales y registraremos cuántos elementos se recorrieron. El siguiente recorrido comienza en el primer valor diferente.

Usaremos **dos pasadas** sobre los grupos, con objetivos distintos:

1. Encontrar la mayor frecuencia. Todavía no se sabe qué valores terminarán siendo modas; una repetición posterior puede superar la frecuencia encontrada al principio.
2. Volver a contar los grupos y mostrar solo aquellos cuya frecuencia sea igual a la máxima. Así se conservan todos los empates sin imprimir prematuramente valores que después dejarían de ser modas.

En el código, `index` avanzará dentro de un `while` para consumir cada grupo. La condición del inner loop revisa primero `index < count` y después consulta el elemento. Con `&&`, si la primera condición es falsa, la segunda no se evalúa: se evita consultar la posición `count` al terminar el último grupo. Esta es una aplicación del short-circuit evaluation de los operadores lógicos.

Compararemos igualdad exacta de los valores almacenados. En el proyecto no se está pidiendo agrupar valores aproximadamente iguales ni redondearlos para decidir su frecuencia. Mostrar dos decimales cambia la presentación, no los datos usados en la comparación.

### 4.5 — Programa completo: `weight_statistics.cpp`

El programa recibe de cero a seis pesos. Cero representa una colección vacía y permite comprobar que se evita el cálculo. Con datos, ordena la copia y llama a las functions de las tres medidas. La definition de selection sort es la de la Parte 3; las definitions nuevas son las de estadísticas.

```cpp
#include <iostream> // Provides console input and output
#include <iomanip> // Provides decimal formatting
using namespace std;

void selectionSort(double values[], int count);
double calculateMean(const double values[], int count);
double calculateMedian(const double sortedValues[], int count);
void displayModes(const double sortedValues[], int count);

int main() {
    const int CAPACITY = 6;
    double weights[CAPACITY] = {};
    double sortedWeights[CAPACITY] = {};
    int weightCount = 0;

    do {
        cout << "How many weights (0-6)? ";
        cin >> weightCount;
    } while (weightCount < 0 || weightCount > CAPACITY);

    for (int index = 0; index < weightCount; index++) {
        cout << "Enter weight " << index + 1 << " (kg): ";
        cin >> weights[index];
        sortedWeights[index] = weights[index]; // Preserves the input order separately
    }

    if (weightCount == 0) {
        cout << "No data available for statistics." << endl;
        return 0; // Prevents division and invalid middle-element access
    }

    selectionSort(sortedWeights, weightCount);
    cout << fixed << setprecision(2);
    cout << "Mean: " << calculateMean(weights, weightCount) << endl;
    cout << "Median: " << calculateMedian(sortedWeights, weightCount) << endl;
    cout << "Mode: ";
    displayModes(sortedWeights, weightCount);
    return 0;
}

void selectionSort(double values[], int count) {
    for (int start = 0; start < count - 1; start++) {
        int minimumIndex = start;
        for (int index = start + 1; index < count; index++) {
            if (values[index] < values[minimumIndex]) {
                minimumIndex = index;
            }
        }
        if (minimumIndex != start) {
            double temporary = values[start]; // Exchanges two values without losing either
            values[start] = values[minimumIndex];
            values[minimumIndex] = temporary;
        }
    }
}

double calculateMean(const double values[], int count) {
    double total = 0.0;
    for (int index = 0; index < count; index++) {
        total += values[index];
    }
    return total / count; // Requires count greater than zero
}

double calculateMedian(const double sortedValues[], int count) {
    int middle = count / 2; // Uses integer division to select an index
    if (count % 2 != 0) {
        return sortedValues[middle];
    }
    return (sortedValues[middle - 1] + sortedValues[middle]) / 2.0;
}

void displayModes(const double sortedValues[], int count) {
    int maximumFrequency = 0;
    int index = 0;

    while (index < count) { // First pass: determines the greatest frequency
        double currentValue = sortedValues[index];
        int frequency = 0;
        while (index < count && sortedValues[index] == currentValue) {
            frequency++;
            index++;
        }
        if (frequency > maximumFrequency) {
            maximumFrequency = frequency;
        }
    }

    if (maximumFrequency <= 1) {
        cout << "N/A" << endl;
        return; // No value repeats
    }

    index = 0; // Starts the second pass at the beginning again
    while (index < count) {
        double currentValue = sortedValues[index];
        int frequency = 0;
        while (index < count && sortedValues[index] == currentValue) {
            frequency++;
            index++;
        }
        if (frequency == maximumFrequency) {
            cout << currentValue << " "; // Displays each tied mode once
        }
    }
    cout << endl;
}
```

Aunque los loops de `displayModes` están anidados en el texto, el índice del recorrido avanza a lo largo de cada grupo y no vuelve a empezar en cero para cada valor. En cada pasada se consumen los elementos una vez. Solo se reinicia `index` al comenzar la segunda pasada, porque esa pasada tiene otro objetivo.

### 4.6 — Casos de prueba y trace de las frecuencias

Ejecuta primero el caso de cinco valores de las partes anteriores. Después utiliza los casos de esta tabla para distinguir los caminos de median y mode. Los valores se entran en el orden indicado; el programa prepara la copia ordenada.

| Valores de entrada | Mean | Median | Mode |
|---|---:|---:|---|
| `7 3 7 1 5` | 4.60 | 5.00 | 7.00 |
| `7 1 7 3` | 4.50 | 5.00 | 7.00 |
| `7 1 3 1 7` | 3.80 | 3.00 | 1.00 y 7.00 |
| `4 1 3 2` | 2.50 | 2.50 | N/A |
| `2 2 2` | 2.00 | 2.00 | 2.00 |
| `6` | 6.00 | 6.00 | N/A |
| Ningún dato: cantidad `0` | No calcular | No calcular | No calcular |

**Para practicar por tu cuenta:** sigue las dos pasadas de mode con `1 1 3 7 7`. Anota `currentValue`, `frequency` y el siguiente `index` al terminar cada grupo. ¿Por qué no sería correcto mostrar `1` como moda definitiva en cuanto termina el primer grupo? Prueba también `1 1 7 7 7`.

<details>
<summary>Ver respuesta</summary>

En `1 1 3 7 7`, los grupos son `(1, frecuencia 2, siguiente index 2)`, `(3, frecuencia 1, siguiente index 3)` y `(7, frecuencia 2, siguiente index 5)`. La frecuencia máxima es dos; la segunda pasada muestra `1` y `7`. En `1 1 7 7 7`, el grupo de `7` alcanza frecuencia tres y supera al de `1`: solo `7` es moda. La primera pasada necesita terminar antes de conocer la frecuencia máxima definitiva.

</details>

---

## Parte 5 — Práctica guiada: consultar y analizar un lote de paquetes (25 min)

Hasta aquí estudiamos por separado cómo entregar un array a una function, buscar registros, ordenar valores y calcular estadísticas. Ahora necesitamos comprobar que esas operaciones funcionan juntas sobre los mismos datos, especialmente cuando una exclusión deja un slot vacío.

Seguiremos un programa completo de paquetes que conserva los registros originales y construye una copia compacta de sus pesos para el análisis. Nos concentraremos en las conexiones entre las functions ya explicadas: qué recibe cada una, qué devuelve y qué cantidad limita cada recorrido. Esta integración prepara el trabajo de Lab 12 sobre el analyzer.

### 5.1 — Problema y decisiones de diseño

**Problema:** un centro de distribución prepara lotes pequeños de paquetes para distintas zonas de entrega. Cada registro conserva un ID único, una zona y un peso en kilogramos. Antes de despachar el lote, la persona operadora debe responder tres tipos de solicitudes sobre los paquetes que saldrán en ese envío:

- Si recibe el ID de un paquete que debe localizar, necesita consultar su zona y su peso. Encontrar ese ID completa la consulta porque identifica un solo paquete.
- Al preparar los paquetes destinados a una zona, necesita la lista completa de sus IDs y pesos. Encontrar uno no basta: cualquier otro paquete de la misma zona también debe incluirse para preparar ese envío.
- Para el resumen del lote, necesita mean, median y mode de los pesos de todos sus paquetes activos, con los significados que estudiamos en la Parte 4. El análisis solo queda completo cuando se han considerado todos esos pesos.

El programa resolverá esas solicitudes sobre una misma colección. Las consultas y el análisis deben conservar la relación entre ID, zona y peso, así como el orden original de los registros, para que un resultado estadístico no cambie los datos de un paquete.

La demostración acepta entre cero y cinco paquetes. Después permite excluir uno del lote antes del análisis, por ejemplo porque no saldrá en ese envío. La exclusión solo marca su slot como vacío y puede dejar un hueco entre registros activos. Los demás paquetes mantienen sus posiciones e IDs. Cero paquetes permite verificar la colección vacía.

Para distinguir estas decisiones, responderemos antes de ejecutar:

1. ¿La consulta por ID necesita una coincidencia o todas? Una, porque los IDs se mantendrán únicos durante la entrada.
2. ¿La consulta por zona puede detenerse en la primera? No; puede haber varios paquetes para esa zona.
3. ¿Qué posiciones participan en las estadísticas? Solo los slots ocupados, aunque no sean consecutivos.
4. ¿Dónde hacemos sorting? En un array separado de pesos, no en los registros originales.

El programa siguiente es una **solución completa para estudiar y ejecutar**. Reutiliza los algoritmos ya explicados; la tarea nueva es seguir cómo se conectan. No es el menú completo del proyecto ni una implementación de lectura de CSV.

### 5.2 — Programa completo: `package_analysis.cpp`

Trabaja en tres momentos: primero recibe y muestra el lote; después sigue las consultas de ID y zona; finalmente observa la extracción de pesos y compara los registros originales antes y después de las estadísticas. La function `copyWeights` es el puente entre el array de structs y las functions numéricas.

Antes de leer el programa, identifiquemos dos conexiones nuevas. `displayPackages` reúne la presentación general y la búsqueda por zona. El parameter `filterByZone` indica qué consulta se está haciendo: `false` muestra todos los registros ocupados y `true` exige además que su zona coincida con `targetZone`. Por eso las function calls de presentación general pasan `""` como zona: ese argument no se utiliza como filtro cuando `filterByZone` es `false`.

En su condición, `!filterByZone || packages[index].zone == targetZone` permite pasar cualquier zona si el filtro está desactivado. La comprobación externa de `isEmpty` sigue siendo necesaria en ambos casos. Esta combinación aplica los operadores lógicos ya estudiados.

En `copyWeights`, `index` identifica el slot de origen y `weightCount` identifica la siguiente posición libre del destino. No siempre tienen el mismo valor. Si el slot `1` queda vacío, el peso del slot `2` se copia a la posición `1` del destino. Incrementar `weightCount` fuera del `if` dejaría huecos en la copia y contaría registros excluidos.

`packages` lleva `const` en esa function porque no se modifica. `weights` no lo lleva porque debe recibir los valores copiados. El destino tiene capacidad suficiente: ambos arrays tienen cinco posiciones y cada registro puede aportar como máximo un peso. En el proyecto se mantiene el mismo razonamiento con capacidad cien.

```cpp
#include <iostream> // Provides console input and output
#include <iomanip> // Provides table and decimal formatting
#include <string> // Provides string and getline
using namespace std;

struct PackageRecord {
    int id = 0;
    string zone;
    double weight = 0.0;
    bool isEmpty = true; // Excludes unused or removed records
};

int findPackageById(const PackageRecord packages[], int capacity, int targetId);
int displayPackages(const PackageRecord packages[], int capacity, string targetZone, bool filterByZone);
int copyWeights(const PackageRecord packages[], int capacity, double weights[]);
void selectionSort(double values[], int count);
double calculateMean(const double values[], int count);
double calculateMedian(const double sortedValues[], int count);
void displayModes(const double sortedValues[], int count);

int main() {
    const int CAPACITY = 5;
    PackageRecord packages[CAPACITY] = {};
    double sortedWeights[CAPACITY] = {};
    int enteredCount = 0;
    int excludedNumber = 0;
    int targetId = 0;
    string targetZone;

    do {
        cout << "How many packages (0-5)? ";
        cin >> enteredCount;
    } while (enteredCount < 0 || enteredCount > CAPACITY);

    for (int index = 0; index < enteredCount; index++) {
        int newId = 0;
        do {
            cout << "Enter a unique positive ID: ";
            cin >> newId;
        } while (newId <= 0 || findPackageById(packages, CAPACITY, newId) != -1);
        packages[index].id = newId; // Stores an ID only after checking occupied records
        cout << "Enter delivery zone: ";
        getline(cin >> ws, packages[index].zone);
        do {
            cout << "Enter package weight (kg, greater than zero): ";
            cin >> packages[index].weight;
        } while (packages[index].weight <= 0.0);
        packages[index].isEmpty = false; // Makes the completed record available
    }

    if (enteredCount > 0) {
        do {
            cout << "Exclude package number (1-" << enteredCount << ", 0 to keep all): ";
            cin >> excludedNumber;
        } while (excludedNumber < 0 || excludedNumber > enteredCount);
        if (excludedNumber != 0) {
            packages[excludedNumber - 1].isEmpty = true; // Converts an entry number to an index
        }
    }

    cout << fixed << setprecision(2);
    cout << "Active records before analysis:" << endl;
    displayPackages(packages, CAPACITY, "", false);

    cout << "Enter a package ID to find: ";
    cin >> targetId;
    int foundIndex = findPackageById(packages, CAPACITY, targetId);
    if (foundIndex == -1) {
        cout << "Package not found." << endl;
    } else {
        cout << "Index: " << foundIndex << ", zone: " << packages[foundIndex].zone
             << ", weight: " << packages[foundIndex].weight << " kg" << endl;
    }

    cout << "Enter a zone to list its packages: ";
    getline(cin >> ws, targetZone);
    int matchCount = displayPackages(packages, CAPACITY, targetZone, true);
    cout << "Zone matches: " << matchCount << endl;

    int weightCount = copyWeights(packages, CAPACITY, sortedWeights);
    if (weightCount == 0) {
        cout << "No data available for statistics." << endl;
    } else {
        selectionSort(sortedWeights, weightCount); // Sorts the compact copy only
        cout << "Weights used: " << weightCount << endl;
        cout << "Mean: " << calculateMean(sortedWeights, weightCount) << endl;
        cout << "Median: " << calculateMedian(sortedWeights, weightCount) << endl;
        cout << "Mode: ";
        displayModes(sortedWeights, weightCount);
    }

    cout << "Active records after analysis:" << endl;
    displayPackages(packages, CAPACITY, "", false); // Verifies that records kept their order
    return 0;
}

int findPackageById(const PackageRecord packages[], int capacity, int targetId) {
    for (int index = 0; index < capacity; index++) {
        if (!packages[index].isEmpty && packages[index].id == targetId) {
            return index; // Returns a position instead of an ID
        }
    }
    return -1;
}

int displayPackages(const PackageRecord packages[], int capacity, string targetZone, bool filterByZone) {
    int matchCount = 0;
    cout << left << setw(8) << "ID" << setw(22) << "Zone" << "Weight (kg)" << endl;
    for (int index = 0; index < capacity; index++) {
        if (!packages[index].isEmpty && (!filterByZone || packages[index].zone == targetZone)) {
            cout << left << setw(8) << packages[index].id
                 << setw(22) << packages[index].zone << packages[index].weight << endl;
            matchCount++; // Includes every occupied match
        }
    }
    return matchCount;
}

int copyWeights(const PackageRecord packages[], int capacity, double weights[]) {
    int weightCount = 0;
    for (int index = 0; index < capacity; index++) {
        if (!packages[index].isEmpty) {
            weights[weightCount] = packages[index].weight; // Uses the next compact destination
            weightCount++;
        }
    }
    return weightCount; // Reports the number of copied values
}

void selectionSort(double values[], int count) {
    for (int start = 0; start < count - 1; start++) {
        int minimumIndex = start;
        for (int index = start + 1; index < count; index++) {
            if (values[index] < values[minimumIndex]) {
                minimumIndex = index;
            }
        }
        if (minimumIndex != start) {
            double temporary = values[start]; // Preserves both values during the exchange
            values[start] = values[minimumIndex];
            values[minimumIndex] = temporary;
        }
    }
}

double calculateMean(const double values[], int count) {
    double total = 0.0;
    for (int index = 0; index < count; index++) {
        total += values[index];
    }
    return total / count; // Called only for a nonempty collection
}

double calculateMedian(const double sortedValues[], int count) {
    int middle = count / 2;
    if (count % 2 != 0) {
        return sortedValues[middle];
    }
    return (sortedValues[middle - 1] + sortedValues[middle]) / 2.0;
}

void displayModes(const double sortedValues[], int count) {
    int maximumFrequency = 0;
    int index = 0;
    while (index < count) { // Finds the maximum group size
        double currentValue = sortedValues[index];
        int frequency = 0;
        while (index < count && sortedValues[index] == currentValue) {
            frequency++;
            index++;
        }
        if (frequency > maximumFrequency) {
            maximumFrequency = frequency;
        }
    }
    if (maximumFrequency <= 1) {
        cout << "N/A" << endl;
        return;
    }
    index = 0;
    while (index < count) { // Displays every group tied at the maximum
        double currentValue = sortedValues[index];
        int frequency = 0;
        while (index < count && sortedValues[index] == currentValue) {
            frequency++;
            index++;
        }
        if (frequency == maximumFrequency) {
            cout << currentValue << " ";
        }
    }
    cout << endl;
}
```

### 5.3 — Ejecutar y responder sobre el programa

Usa primero este lote y selecciona `0` para conservar todos los paquetes:

| Orden de entrada | ID | Zone | Weight (kg) |
|---:|---:|---|---:|
| 1 | 42 | North | 7 |
| 2 | 57 | South | 3 |
| 3 | 81 | North | 7 |
| 4 | 96 | West | 1 |
| 5 | 105 | North | 5 |

Busca el ID `81` y la zona `North`. Luego responde y verifica:

1. ¿Qué índice devuelve la búsqueda de `81`? ¿Cuántos registros muestra la consulta de `North`?
2. ¿Cuáles son mean, median y mode? ¿Por qué el primer registro todavía tiene peso `7` al terminar?
3. Ejecuta nuevamente y excluye el paquete número `2`. ¿Qué índices quedan ocupados? ¿Cómo se llena la copia de pesos y cuáles son las nuevas estadísticas?
4. Para probar empate entre modas, conserva todos y cambia los pesos a `7 1 3 1 7`. ¿Qué debe mostrarse?
5. Entra dos paquetes y repite el ID del primero al entrar el segundo. ¿En qué function call se detecta el duplicado? ¿Por qué se rechaza antes de marcar el segundo slot como ocupado?
6. ¿Qué sucede al entrar cantidad `0`? ¿Y si entra un paquete y luego lo excluyes? Identifica el `if` que protege los cálculos en ambos casos.

<details>
<summary>Ver respuesta</summary>

1. Devuelve `2`; `North` produce tres coincidencias, IDs `42`, `81` y `105`.
2. Mean `4.60`, median `5.00` y mode `7.00`. Solo se ordenó la copia numérica; ningún peso se reasignó a otro registro.
3. Quedan ocupados los índices `0`, `2`, `3` y `4`. La copia recibe `7 7 1 5` en posiciones `0` a `3`; ordenada queda `1 5 7 7`. Mean `5.00`, median `6.00` y mode `7.00`.
4. Mean `3.80`, median `3.00` y modes `1.00` y `7.00`.
5. La function call `findPackageById(packages, CAPACITY, newId)` devuelve un índice distinto de `-1`, así que el loop vuelve a pedir el ID. La búsqueda reconoce el primer registro porque ya está ocupado; el segundo todavía está en preparación y no participa como un registro completo.
6. Las consultas no encuentran registros y `copyWeights` devuelve cero. En ambos casos, `if (weightCount == 0)` muestra el mensaje de ausencia y evita llamar a las functions de estadísticas.

</details>

---

## Cierre — Resumen y conexión con Lab 12 (10 min)

### Resumen de la sesión

- Una function que recibe un array necesita un límite explícito. `const` evita modificar sus elementos mediante ese parameter.
- Linear search revisa las posiciones en secuencia; una búsqueda por ID devuelve un índice o `-1`. Las búsquedas por campos compartidos deben conservar todas las coincidencias.
- Con huecos intermedios se recorre la capacidad y se comprueba `isEmpty`; no se sustituye ese recorrido por la cantidad de registros ocupados.
- Una copia compacta reúne solo los valores válidos desde el índice cero. Su cantidad utilizada determina los límites del sorting y de las estadísticas.
- Selection sort coloca el menor valor pendiente en una posición definitiva en cada pasada.
- Mean utiliza suma y cantidad; median necesita el orden; mode compara frecuencias e incluye empates. Primero se comprueba que haya datos.
- Ordenar una copia conserva el orden, los IDs y la asociación entre campos de las observations originales.

### Próxima sesión

Lab 12 aplicará estos patrones al prototipo de Lab 11: búsquedas por ID/state/county y estadísticas sobre una columna numérica seleccionada. El proyecto permite `total_votes`, `dem_votes`, `rep_votes` y `dem_share`; el ID y el flag de disponibilidad no son columnas estadísticas. Una columna no admitida o una colección vacía debe producir un mensaje y volver al menú sin calcular.

Mean, median y mode son obligatorias. El histograma sigue siendo bono de hasta diez puntos adicionales. Las siguientes sesiones de integración conectarán las operaciones del proyecto; la lecture de Semana 13 se reserva para repaso y Midterm 2, sin contenido nuevo.
