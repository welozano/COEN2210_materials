# Lab 12 — Search, Sorting and Statistics
## COEN 2210 — Introduction to Programming

**Prof.:** Wilson Lozano<br>
**Basado en:** Semana 12 — Search, sorting y estadísticas; Gaddis, Capítulos 7 y 8<br>
**Duración:** 110 min<br>
**Requisitos:** Labs 1–3 y 5–11; arrays, `struct`, functions, `const`, `for`, `while`, `string`, `getline`, validación y `fixed`/`setprecision`

---

## Objetivos

Al finalizar este laboratorio, el estudiante podrá:

1. Usar linear search para encontrar un registro por ID y devolver su índice o `-1`.
2. Recorrer todos los registros para mostrar las coincidencias de un campo compartido.
3. Extraer una medición numérica de un array de `struct` a una copia separada.
4. Ordenar la copia con selection sort sin cambiar los registros originales.
5. Calcular mean, median y mode, incluidos empates y ausencia de repeticiones.
6. Diseñar pruebas que comprueben consultas y estadísticas sobre una misma colección.

---

## Parte 0 — Preparar la carpeta y el repositorio (5 min)

Crea una carpeta nueva llamada `lab12-search-sorting-statistics`, ábrela como carpeta raíz en VS Code e inicializa un repositorio desde Source Control. Dentro crea estos archivos:

1. `maintenance_queries_demo.cpp`
2. `inspection_analysis.cpp`
3. `.gitignore`

Cada archivo `.cpp` debe comenzar con el header estándar en inglés. La `Description` debe indicar la responsabilidad particular del archivo.

```cpp
/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Your Full Name]
 * Lab: 12 - Search, Sorting and Statistics
 * Description: [What this specific file does]
 * Due Date: [Date]
 */
```

En `.gitignore` agrega:

```gitignore
# Compiled programs
maintenance_queries_demo
maintenance_queries_demo.exe
inspection_analysis
inspection_analysis.exe
```

**¿Qué hace esto?** Separa esta práctica del proyecto final y evita incluir executables en el repositorio.

**Qué deberías ver:** los dos archivos fuente y `.gitignore` aparecen en Explorer; los executables no aparecerán en Source Control después de compilar.

---

## Parte 1 — `maintenance_queries_demo.cpp`: ejemplo guiado de búsquedas (20 min)

Un taller de mantenimiento conserva hasta cuatro órdenes activas. Cada orden tiene un ID único, un área responsable y una cantidad de horas estimadas. La persona supervisora necesita dos consultas: localizar una orden específica por ID y obtener todas las órdenes de una misma área para distribuir el trabajo. Un ID identifica una sola orden; un área puede tener varias.

Este programa es un ejemplo completo y distinto del proyecto final. Primero recibe cuatro órdenes por consola, luego busca un ID y finalmente lista las órdenes de un área. Observa que ambas functions reciben el array y su límite, pero terminan en momentos distintos: la búsqueda por ID termina al hallar una coincidencia; la consulta por área revisa todas las posiciones.

```cpp
#include <iostream> // Provides console input and output
#include <iomanip> // Provides decimal formatting
#include <string> // Provides string and getline
using namespace std;

struct MaintenanceOrder {
    int id = 0;
    string area;
    double estimatedHours = 0.0;
};

int findOrderById(const MaintenanceOrder orders[], int count, int targetId);
int displayOrdersByArea(const MaintenanceOrder orders[], int count, string targetArea);

int main() {
    const int ORDER_COUNT = 4;
    MaintenanceOrder orders[ORDER_COUNT] = {};
    int targetId = 0;
    string targetArea;

    for (int index = 0; index < ORDER_COUNT; index++) {
        cout << "Enter ID for order " << index + 1 << ": ";
        cin >> orders[index].id;
        cout << "Enter area for order " << index + 1 << ": ";
        getline(cin >> ws, orders[index].area);
        cout << "Enter estimated hours: ";
        cin >> orders[index].estimatedHours;
    }

    cout << "Enter an order ID to find: ";
    cin >> targetId;
    int foundIndex = findOrderById(orders, ORDER_COUNT, targetId);
    if (foundIndex == -1) {
        cout << "Order not found." << endl;
    } else {
        cout << fixed << setprecision(2);
        cout << "Found order " << orders[foundIndex].id
             << " in " << orders[foundIndex].area
             << " with " << orders[foundIndex].estimatedHours << " hours." << endl;
    }

    cout << "Enter an area to list its orders: ";
    getline(cin >> ws, targetArea);
    int matchCount = displayOrdersByArea(orders, ORDER_COUNT, targetArea);
    cout << "Orders in area: " << matchCount << endl;
    return 0;
}

int findOrderById(const MaintenanceOrder orders[], int count, int targetId) {
    for (int index = 0; index < count; index++) {
        if (orders[index].id == targetId) {
            return index; // Stops because an ID identifies one order
        }
    }
    return -1; // Reports that no valid index was found
}

int displayOrdersByArea(const MaintenanceOrder orders[], int count, string targetArea) {
    int matchCount = 0;
    cout << fixed << setprecision(2);
    for (int index = 0; index < count; index++) {
        if (orders[index].area == targetArea) {
            cout << "ID: " << orders[index].id
                 << " | Hours: " << orders[index].estimatedHours << endl;
            matchCount++; // Counts every matching order
        }
    }
    return matchCount;
}
```

Compila y ejecuta el programa. Prueba, por ejemplo, las órdenes `41`, `58`, `73` y `86`; usa `Electrical`, `Mechanical`, `Electrical` y `Electrical` como áreas. Busca `73` y consulta `Electrical`.

> 💻 **Vas a usar la terminal integrada de VS Code.** Ejecuta los comandos desde la carpeta del lab.

**Windows — compilar:**

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic maintenance_queries_demo.cpp -o maintenance_queries_demo.exe
```

**Mac — compilar:**

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic maintenance_queries_demo.cpp -o maintenance_queries_demo
```

**¿Qué hace esto?** Construye un executable para comprobar las dos formas de búsqueda antes de escribir la práctica integrada.

**Qué deberías ver:** no hay errores ni warnings y aparece un executable ignorado por Git.

**Windows — ejecutar:**

```powershell
.\maintenance_queries_demo.exe
```

**Mac — ejecutar:**

```bash
./maintenance_queries_demo
```

**¿Qué hace esto?** Ejecuta el programa y permite entrar las cuatro órdenes y las dos consultas.

**Qué deberías ver:** la búsqueda de `73` devuelve su posición; la consulta de `Electrical` muestra tres órdenes, porque no termina después de la primera.

**Analysis — no se entrega:** responde estas preguntas en tus notas antes de continuar.

1. ¿Por qué `findOrderById` devuelve un índice y no el ID que la persona escribió?
2. ¿Por qué `findOrderById` puede terminar al encontrar una coincidencia, pero `displayOrdersByArea` debe continuar el recorrido?
3. ¿Qué impide que `findOrderById` cambie el ID o el área de una orden mediante su parameter `orders`?

**Esto es lo que debes entregar (obligatorio):** `maintenance_queries_demo.cpp` completo y ejecutado con un ID encontrado y un área con más de una coincidencia.

---

## Parte 2 — `inspection_analysis.cpp`: starter de práctica integrada (55 min)

Ahora aplicarás los mismos patrones a una colección pequeña de inspecciones de seguridad. El laboratorio entrega seis inspecciones ya registradas para concentrarnos en las operations nuevas. La persona usuaria cambia las consultas y decide cuándo calcular las estadísticas desde el menú.

Cada inspección contiene un ID único, un área, una lectura de vibración y un flag de disponibilidad. Las seis posiciones comienzan ocupadas; el flag se conserva porque el mismo patrón permitirá ignorar registros removidos cuando un programa necesite esa operación. El programa debe consultar solamente registros con `isEmpty == false`.

El starter ya contiene la colección, el menú, los prototypes, la presentación de una fila y las function calls. Completa únicamente los TODOs de las functions al final. No cambies los datos iniciales, el menú ni los prototypes: así podremos comparar los mismos resultados durante las pruebas.

```cpp
#include <iostream> // Provides console input and output
#include <iomanip> // Provides table and decimal formatting
#include <string> // Provides string and getline
using namespace std;

struct Inspection {
    int id = 0;
    string area;
    double vibration = 0.0;
    bool isEmpty = true;
};

int findInspectionById(const Inspection inspections[], int capacity, int targetId);
int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea);
int copyVibrations(const Inspection inspections[], int capacity, double values[]);
void selectionSort(double values[], int count);
double calculateMean(const double values[], int count);
double calculateMedian(const double sortedValues[], int count);
void displayModes(const double sortedValues[], int count);
void displayInspection(Inspection inspection);

int main() {
    const int CAPACITY = 6;
    Inspection inspections[CAPACITY] = {
        {101, "Assembly", 0.30, false},
        {104, "Power", 0.15, false},
        {109, "Assembly", 0.30, false},
        {115, "Thermal", 0.45, false},
        {118, "Power", 0.10, false},
        {123, "Assembly", 0.15, false}
    };
    double sortedVibrations[CAPACITY] = {};
    int menuChoice = 0;

    cout << fixed << setprecision(2);
    do {
        cout << "\nInspection Analysis\n";
        cout << "1. Find inspection by ID\n";
        cout << "2. List inspections by area\n";
        cout << "3. Analyze vibration readings\n";
        cout << "4. Exit\n";
        cout << "Enter option number: ";
        cin >> menuChoice;

        if (menuChoice == 1) {
            int targetId = 0;
            cout << "Enter inspection ID: ";
            cin >> targetId;
            int foundIndex = findInspectionById(inspections, CAPACITY, targetId);
            if (foundIndex == -1) {
                cout << "Inspection not found." << endl;
            } else {
                displayInspection(inspections[foundIndex]);
            }
        } else if (menuChoice == 2) {
            string targetArea;
            cout << "Enter area: ";
            getline(cin >> ws, targetArea);
            int matchCount = displayInspectionsByArea(inspections, CAPACITY, targetArea);
            cout << "Matches: " << matchCount << endl;
        } else if (menuChoice == 3) {
            int valueCount = copyVibrations(inspections, CAPACITY, sortedVibrations);
            if (valueCount == 0) {
                cout << "No readings available for statistics." << endl;
            } else {
                selectionSort(sortedVibrations, valueCount);
                cout << "Values used: " << valueCount << endl;
                cout << "Mean: " << calculateMean(sortedVibrations, valueCount) << endl;
                cout << "Median: " << calculateMedian(sortedVibrations, valueCount) << endl;
                cout << "Mode: ";
                displayModes(sortedVibrations, valueCount);
            }
        } else if (menuChoice != 4) {
            cout << "Invalid option." << endl;
        }
    } while (menuChoice != 4);

    return 0;
}

void displayInspection(Inspection inspection) {
    cout << "ID: " << inspection.id
         << " | Area: " << inspection.area
         << " | Vibration: " << inspection.vibration << endl;
}

int findInspectionById(const Inspection inspections[], int capacity, int targetId) {
    // TODO: Traverse every position. Ignore empty slots and return the index of the matching ID.
    // TODO: Return -1 only after the complete search finds no occupied match.
    return -1;
}

int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea) {
    int matchCount = 0;
    // TODO: Traverse every position, display every occupied inspection in targetArea, and update matchCount.
    return matchCount;
}

int copyVibrations(const Inspection inspections[], int capacity, double values[]) {
    int valueCount = 0;
    // TODO: Copy the vibration from each occupied inspection into the next position of values.
    // TODO: Return the number of copied values, not capacity.
    return valueCount;
}

void selectionSort(double values[], int count) {
    // TODO: Complete selection sort in ascending order for the used positions only.
}

double calculateMean(const double values[], int count) {
    double total = 0.0;
    // TODO: Accumulate the used values and return total divided by count.
    return 0.0;
}

double calculateMedian(const double sortedValues[], int count) {
    // TODO: Use the middle value for odd counts or average the two middle values for even counts.
    return 0.0;
}

void displayModes(const double sortedValues[], int count) {
    // TODO: Find the maximum repeated frequency, then display every value tied at that frequency.
    // TODO: Display N/A when no value repeats.
}
```

### Orden de trabajo

1. Implementa `findInspectionById` y prueba con `109` y `999`.
2. Implementa `displayInspectionsByArea` y prueba con `Assembly` y `Optics`.
3. Implementa `copyVibrations` y verifica que devuelve `6`, no la capacidad por accidente.
4. Implementa `selectionSort`, `calculateMean`, `calculateMedian` y `displayModes` usando los algoritmos de Semana 12.
5. Ejecuta la opción 3. El sorting ocurre solo en `sortedVibrations`; no reasignes una vibración a un elemento de `inspections`.

Para los seis valores iniciales, la copia ordenada debe ser `0.10 0.15 0.15 0.30 0.30 0.45`. El mean es `0.24` al mostrar dos decimales, la median es `0.23`, y las modas son `0.15` y `0.30`. La cantidad es par, por lo que la median requiere las dos posiciones centrales.

> 💻 **Vas a usar la terminal integrada de VS Code.** Compila después de completar cada grupo de functions, desde la carpeta del lab.

**Windows — compilar:**

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic inspection_analysis.cpp -o inspection_analysis.exe
```

**Mac — compilar:**

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic inspection_analysis.cpp -o inspection_analysis
```

**¿Qué hace esto?** Construye la práctica completa y activa los warnings que ayudan a detectar variables, returns o parameters sin usar.

**Qué deberías ver:** al completar los TODOs, la compilación termina sin errores ni warnings. La opción 3 calcula sobre la copia ordenada y las consultas siguen mostrando los IDs y áreas originales.

**Windows — ejecutar:**

```powershell
.\inspection_analysis.exe
```

**Mac — ejecutar:**

```bash
./inspection_analysis
```

**¿Qué hace esto?** Ejecuta el menú de práctica sobre las seis inspecciones incluidas en el starter.

**Qué deberías ver:** las opciones 1 y 2 responden a las consultas ingresadas; la opción 3 muestra los resultados de la copia ordenada sin cambiar los registros originales.

**Esto es lo que debes entregar (obligatorio):** `inspection_analysis.cpp` con todos los TODOs completados y funcionando. No entregues el executable.

**Para practicar por tu cuenta (opcional, no se entrega):** cambia temporalmente una vibración para que solo haya una moda y vuelve a ejecutar la opción 3. Restaura los datos originales antes de entregar.

---

## Parte 3 — Test cases y análisis (25 min)

Ejecuta, como mínimo, estos casos. Anota los inputs, el resultado esperado y el resultado observado dentro de `inspection_analysis.cpp`, después de la última llave y antes del bloque `Analysis`. No necesitas usar una tabla ni Markdown.

| Prueba | Resultado esperado |
|---|---|
| Buscar ID `109` | Muestra la inspección de Assembly con vibración `0.30`. |
| Buscar ID `999` | Muestra `Inspection not found.` |
| Consultar `Assembly` | Muestra tres inspecciones y reporta `Matches: 3`. |
| Consultar `Optics` | No muestra filas y reporta `Matches: 0`. |
| Analizar vibraciones | Mean `0.24`, median `0.23`, modes `0.15` y `0.30`. |
| Seleccionar opción `8` | Informa que la opción no es válida y conserva los datos. |

Primero agrega este bloque y reemplaza cada texto entre corchetes con tus resultados reales:

```cpp
/*
 * Test Cases:
 * 1. Inputs: [Write the inputs for the successful ID search]
 *    Expected: [Write the expected result]
 *    Observed: [Write the result from your execution]
 * 2. Inputs: [Write the inputs for the ID not found]
 *    Expected: [Write the expected result]
 *    Observed: [Write the result from your execution]
 * 3. Inputs: [Write the inputs for the area search]
 *    Expected: [Write the expected result]
 *    Observed: [Write the result from your execution]
 * 4. Inputs: [Write the inputs for the statistics option]
 *    Expected: [Write the expected result]
 *    Observed: [Write the result from your execution]
 */
```

Después del bloque de test cases, agrega y responde en inglés:

```cpp
/*
 * Analysis:
 * 1. Why does findInspectionById return an index instead of the ID?
 * 2. Why must displayInspectionsByArea continue after its first match?
 * 3. Why does copyVibrations use valueCount separately from index?
 * 4. Why is selectionSort applied to sortedVibrations instead of inspections?
 * 5. Which two values determine the median when six readings are sorted?
 */
```

**Esto es lo que debes entregar (obligatorio):** `inspection_analysis.cpp` completo, con los bloques `Test Cases` y `Analysis` respondidos al final.

---

## Parte 4 — Cierre y conexión con el proyecto (5 min)

Antes de entregar, verifica que:

- Cada archivo tiene su header personal completo en inglés.
- Los dos programas compilan sin errores ni warnings.
- La búsqueda por ID distingue entre una coincidencia y `-1`.
- La consulta por área muestra todas las coincidencias.
- Las estadísticas usan la copia ordenada, no los registros originales.
- Incluiste los bloques `Test Cases` y `Analysis`, pero no los executables.

Haz stage de los dos `.cpp` y `.gitignore`; crea un commit como `Lab 12: search sorting and statistics` y publica/sincroniza el repositorio.

**¿Qué hace esto?** Conserva evidencia de que practicaste los algoritmos antes de decidir cómo integrarlos a tu propio proyecto.

**Qué deberías ver:** el remoto contiene las fuentes y las pruebas, sin ejecutables.

## Próxima sesión

En Semana 13 trabajarás en tu propio CoRe Data Analyzer. Podrás decidir cómo adaptar estos patrones a sus fields y menú, sin copiar este programa como si fuera una parte del proyecto.
