# Array Reverser

Ejercicio de calentamiento de la **Fase 1: Gestión de Memoria**.

## 📌 Objetivo

Practicar el uso de **punteros crudos**, **aritmética de punteros** y **memoria dinámica** (`new[]` / `delete[]`) invirtiendo un array sin usar corchetes `[]`.

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| Punteros crudos | `int* arr`, `int* left`, `int* right` |
| Aritmética de punteros | `arr + size - 1`, `left++`, `right--` |
| Memoria dinámica | `new int[size]`, `delete[] arr` |
| Dereferencia | `*left`, `*right` para acceder/modificar valores |

## 🚀 Cómo compilar y ejecutar

```bash
g++ array_reverser.cpp -o array_reverser
./array_reverser

## 📋 Ejemplo de uso ##

Enter the size of the array: 5
Enter 5 numbers: 1 2 3 4 5
Original array: 1 2 3 4 5
Reversed array: 5 4 3 2 1