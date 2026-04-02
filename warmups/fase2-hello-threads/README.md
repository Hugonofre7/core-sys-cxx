# The Hello Threads

Ejercicio de calentamiento de la **Fase 2: Concurrencia**.

## 📌 Objetivo

Aprender a crear y manejar **hilos** (`std::thread`) en C++, entender cómo se ejecutan en paralelo y la importancia de `join()` para sincronización.

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| `std::thread` | Crear un hilo que ejecuta una función |
| `join()` | Esperar a que un hilo termine |
| Hilo principal | `main()` se ejecuta en un hilo |
| Paralelismo | Múltiples hilos ejecutándose simultáneamente |
| Flag `-pthread` | Necesario para enlazar la librería pthreads |

## 🚀 Cómo compilar y ejecutar

```bash
g++ hello_threads.cpp -o hello_threads -pthread
./hello_threads

📋 Ejemplo de ejecución

Main thread: starting
Hello from thread 1
Hello from thread 3
Hello from thread 2
Main thread: all threads finished

