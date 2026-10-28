# COEN 2210 — Introduction to Programming
## Materiales del curso

Repositorio con los materiales del curso (lectures y laboratorios), en C++. Cada guía de lab está pensada para una sesión de 2 horas; cada lecture, para una sesión de 3 horas.

**Textbook:** Gaddis, *Starting Out with C++: From Control Structures through Objects*, 11th Edition, Pearson, 2027.

---

> 💻 **¿Necesitas repasar el uso de la terminal/consola?** Antes de empezar, visita el [**Tutorial Básico de Terminal**](Tutorial_Basico_Terminal.md) — no es un laboratorio numerado del curso, es un recurso de apoyo para quien lo necesite.

### Índice de Lectures

| # | Semana | Tema | Enlace |
|---|---|---|---|
| 1 | 1 | Introduction | *(pendiente)* |
| 2 | 2 | Hardware & Number Representation (binary, hex, octal) | [Semana2_Hardware_Number_Representation.md](lectures/Semana2_Hardware_Number_Representation.md) |
| 3 | 3 | Introduction to C++ | [Semana3_Introduction_to_CPP.md](lectures/Semana3_Introduction_to_CPP.md) |
| 4 | 4 | Basic programming concepts and elements | [Semana4_Basic_Programming_Concepts.md](lectures/Semana4_Basic_Programming_Concepts.md) |
| 5 | 5 | Control structures — Selection structures | [Semana5_Selection_Structures.md](lectures/Semana5_Selection_Structures.md) |
| 6 | 6 | Control structures — Repetition structures | [Semana6_Repetition_Structures.md](lectures/Semana6_Repetition_Structures.md) |
| 7 | 7 | Review + Midterm 1 | *(evaluación realizada; no hay material de lecture publicado)* |
| 8 | 8-9 | Functions | [Parte I — modularidad, parameters y reference](lectures/Semana8_Functions.md)<br>[Parte II — return values, `bool` y scope local](lectures/Semana9_Functions_Return_Values_Scope.md) |
| 9 | 10 | File Input/Output Management | [Semana10_File_IO.md](lectures/Semana10_File_IO.md) |
| 10 | 11-12 | Semana 11: arrays, `structs`, arrays de registros, matrices y arrays como miembros; Semana 12: search, sorting, mean, median y mode | [Semana 11 — Arrays, structs y matrices](lectures/Semana11_Arrays_Structs_Matrices.md) · Semana 12: pendiente |
| 11 | 13 | Review + Midterm 2 | *(pendiente)* |
| 12 | 14 | Project work — integración, pruebas y consultas | *(pendiente)* |
| 13 | 15 | Project Defense | *(pendiente)* |

### Índice de Laboratorios

| # | Semana | Tema | Enlace |
|---|---|---|---|
| 1 | 1 | Git y GitHub desde la consola | [Lab1 Git-GitHub - Consola](labs/Lab1_Git_GitHub_Consola.md) |
| 2 | 2 | VS Code + Git/GitHub desde el IDE | [Lab2 VSCode - Git - Representacion Numerica](labs/Lab2_VSCode_Git_Representacion_Numerica.md) |
| 3 | 3 | Compilar/correr programas, leer errores del compilador | [Lab3 Intro to CPP](labs/Lab3_Figuras_ASCII.md) |
| 4 | 4 | No se ofreció: la sesión se usó para impartir la lecture de Semana 4, desplazada por el feriado del lunes. | *(no aplica)* |
| 5 | 5 | If-else structures y `switch` | [Lab5_Selection_Structures.md](labs/Lab5_Selection_Structures.md) |
| 6 | 6 | Loops I — `while` y `do while`, integrando selection structures | [Lab6_Loops_I.md](labs/Lab6_Loops_I.md) |
| 7 | 7 | Loops II — `for`, contadores y acumuladores | [Lab7_Loops_II.md](labs/Lab7_Loops_II.md) |
| 8 | 8 | Functions — call-by-value / call-by-reference | [Lab8_Functions.md](labs/Lab8_Functions.md) |
| 9 | 9 | File I/O | [Lab9_File_IO.md](labs/Lab9_File_IO.md) |
| 10 | 10 | Colchón / File I/O (cont.) | *(pendiente)* |
| 11 | 11 | Basic Calculator: múltiples archivos y compilación; arrays y `structs` del proyecto | [Lab11_Arrays_Structs_Project.md](labs/Lab11_Arrays_Structs_Project.md) |
| 12 | 12 | Search, sorting y estadísticas aplicadas al proyecto | *(pendiente)* |
| 13 | 13 | Integración del proyecto con los conceptos ya cubiertos | *(pendiente)* |
| 14 | 14 | Project work session | *(pendiente)* |
| 15 | 15 | Project Defense | *(pendiente)* |

---

### Proyecto final — CoRe Data Analyzer

**Entrega:** 2 de diciembre de 2026.

- [Enunciado y rúbrica](final_project/COEN2210_ProyectoFinal_DataScience.md)
- [Dataset inicial — 50 observations (CSV)](final_project/swingStatesDF_50.csv)
- [Basic Integer Calculator — código de apoyo e instrucciones](final_project/BasicCalculator/README.md)

### Cómo usar este repositorio

- Cada guía está en formato Markdown dentro de `labs/` o `lectures/`, y se puede leer directamente en GitHub (se renderiza con formato automáticamente).
- Este repo se actualiza según se van creando/revisando los materiales — el historial de commits sirve como registro de versiones de cada guía.

### Estructura de carpetas

```
coen2210-labs/
├── README.md                      ← este archivo (índice general)
├── Tutorial_Basico_Terminal.md    ← recurso de apoyo (no es un lab numerado)
├── final_project/                 ← enunciado Markdown, imágenes, dataset y calculadora de apoyo
├── labs/
│   ├── Lab1_Git_GitHub_Consola.md
│   ├── Lab2_VSCode_Git_Representacion_Numerica.md
│   ├── Lab3_Figuras_ASCII.md
│   ├── Lab5_Selection_Structures.md
│   ├── Lab6_Loops_I.md
│   └── ...
└── lectures/
    ├── Semana2_Hardware_Number_Representation.md
    ├── Semana3_Introduction_to_CPP.md
    ├── Semana4_Basic_Programming_Concepts.md
    ├── Semana5_Selection_Structures.md
    └── ...
```
