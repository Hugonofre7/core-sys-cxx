# The Race Counter

Ejercicio de calentamiento de la **Fase 2: Concurrencia**.

## 📌 Objetivo

Demostrar el problema de **race condition** cuando múltiples hilos acceden a una variable compartida sin protección, y solucionarlo usando **mutex** (`std::mutex`).

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| Race condition | Varios hilos modifican la misma variable sin sincronización |
| Sección crítica | Bloque de código que solo un hilo puede ejecutar a la vez |
| `std::mutex` | Exclusión mutua: solo un hilo puede tener el lock |
| `mtx.lock()` | Bloquear el mutex (si está ocupado, el hilo espera) |
| `mtx.unlock()` | Liberar el mutex |

## 🚀 Cómo compilar y ejecutar

```bash
g++ race_counter.cpp -o race_counter -pthread
./race_counter

