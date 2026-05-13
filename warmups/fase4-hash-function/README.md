# Hash Function

Ejercicio de calentamiento de la **Fase 4: STL y Rendimiento**.

## 📌 Objetivo

Implementar diferentes **funciones hash** desde cero, entender cómo funcionan y por qué son fundamentales en estructuras de datos como `std::unordered_map`.

## 🧠 Conceptos Clave

| Concepto | Explicación |
|----------|-------------|
| **Función hash** | Convierte cualquier dato en un número de tamaño fijo |
| **Determinística** | Misma entrada → mismo hash |
| **Colisión** | Dos entradas diferentes producen el mismo hash |
| **Distribución uniforme** | Las salidas se distribuyen uniformemente |
| **Eficiencia** | Debe ser rápida de calcular |

## 🚀 Cómo compilar y ejecutar

```bash
g++ hash_function.cpp -o hash_function
./hash_function


📋 Ejemplo de ejecución
=== FUNCIONES HASH ===

[Palabra corta]
  String: "hola"
  djb2:   6385302889
  sdbm:   29358378301628796
  std:    16100555142912586306

[Palabra larga]
  String: "algoritmo de hash"
  djb2:   16568458059114330368
  sdbm:   11467014600727542809

[Enteros]
  int_hash(0) = 0
  int_hash(1) = 824515495
  int_hash(2) = 1722258072
  int_hash(3) = 541708869

[Demostración de colisiones]
  djb2("cat")   = 193488125
  djb2("dog")   = 193489663
  djb2("car")   = 193488123
  djb2("hello") = 210714636441
  djb2("hello") = 210714636441  ← mismo valor (determinístico)

✅ Todas las pruebas completadas