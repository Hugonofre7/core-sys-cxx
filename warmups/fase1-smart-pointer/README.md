# Smart Pointer Clone

Ejercicio de calentamiento de la **Fase 1: Gestión de Memoria**.

## 📌 Objetivo

Implementar una versión simplificada de `std::unique_ptr` usando **templates** y **RAII** para entender cómo funcionan los smart pointers por dentro.

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| Templates | `template <typename T>` - funciona con cualquier tipo |
| RAII | Recurso en constructor, liberación en destructor |
| Puntero crudo | `T* ptr` - el recurso gestionado |
| Sobrecarga de operadores | `operator*` y `operator->` para acceso tipo puntero |
| `explicit` | Evita conversiones implícitas peligrosas |

## 🚀 Cómo compilar y ejecutar

```bash
g++ smart_ptr_clone.cpp -o smart_ptr_clone
./smart_ptr_clone

## 📋 Ejemplo de ejecución

Entering main
Test constructor (1)
SmartPtr constructor
Hello from Test 1
Exiting main
SmartPtr destructor
Test destructor (1)