# Resource Wrapper (RAII)

Ejercicio de calentamiento de la **Fase 1: Gestión de Memoria**.

## 📌 Objetivo

Implementar una clase que encapsule un recurso (memoria dinámica) utilizando el patrón **RAII (Resource Acquisition Is Initialization)** para garantizar que la liberación del recurso ocurra automáticamente.

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| RAII | Adquirir recurso en constructor, liberar en destructor |
| Constructor | `IntArray(int n)` - asigna memoria con `new[]` |
| Destructor | `~IntArray()` - libera memoria con `delete[]` |
| Encapsulación | El puntero crudo es `private`, solo accesible mediante métodos |
| Ámbito de vida | El recurso vive mientras el objeto existe |

## 🚀 Cómo compilar y ejecutar

```bash
g++ resource_wrapper.cpp -o resource_wrapper
./resource_wrapper

## 📋 Ejemplo de ejecución

Entering main
Constructor: allocating array of size 5
Array contents: 0 10 20 30 40
Exiting main
Destructor: freeing memory