# Array Reverser

Ejercicio de calentamiento de la **Fase 1: Gestión de Memoria**.

## Objetivo

Practicar el uso de **punteros crudos**, **aritmética de punteros** y **memoria dinámica** (`new[]` / `delete[]`) invirtiendo un array sin usar corchetes `[]`.

## Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| Punteros crudos | `int* arr`, `int* left`, `int* right` |
| Aritmética de punteros | `arr + size - 1`, `left++`, `right--` |
| Memoria dinámica | `new int[size]`, `delete[] arr` |
| Dereferencia | `*left`, `*right` para acceder/modificar valores |

## Código

```cpp
#include <iostream>

void reverse(int* arr, int size) {
    int* left = arr;
    int* right = arr + size - 1;
    
    while(left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

int main() {
    int size;
    
    std::cout << "Enter the size of the array: ";
    std::cin >> size;
    
    int* arr = new int[size];
    
    std::cout << "Enter " << size << " numbers: ";
    for(int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }
    
    std::cout << "Original array: ";
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    reverse(arr, size);
    
    std::cout << "Reversed array: ";
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    delete[] arr;
    
    return 0;
}
