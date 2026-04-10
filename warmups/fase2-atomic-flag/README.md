# The Atomic Flag

Ejercicio de calentamiento de la **Fase 2: Concurrencia**.

## 📌 Objetivo

Aprender a usar **variables atómicas** (`std::atomic<bool>`) para comunicar eventos entre hilos de forma ligera y sin mutex.

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| `std::atomic<bool>` | Variable booleana con operaciones atómicas |
| `load()` | Lectura atómica del valor |
| `store()` | Escritura atómica del valor |
| Busy-wait | Hilo espera activamente hasta que cambia la bandera |
| Señalización | Un hilo notifica a otros mediante una bandera |

## 🚀 Cómo compilar y ejecutar

```bash
g++ atomic_flag.cpp -o atomic_flag -pthread
./atomic_flag


📋 Ejemplo de ejecución
Main: starting 5 threads
Thread 0 waiting...
Thread 1 waiting...
Thread 2 waiting...
Main: doing some work...
Thread 4 waiting...
Thread 3 waiting...
Main: sending signal!
Thread 2 received signal!
Thread 4 received signal!
Thread 1 received signal!
Thread 0 received signal!
Thread 3 received signal!
Main: all threads finished