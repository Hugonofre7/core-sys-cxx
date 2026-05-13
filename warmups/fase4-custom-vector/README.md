# Custom Vector Container

Ejercicio de calentamiento de la **Fase 4: STL y Rendimiento**.

## 📌 Objetivo

Implementar un contenedor dinámico similar a `std::vector` desde cero, entendiendo:
- Gestión de memoria dinámica
- Redimensionamiento automático
- Templates para tipos genéricos
- Iteradores básicos

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| **Templates** | `template <typename T>` para cualquier tipo |
| **Memoria dinámica** | `new T[]`, `delete[]` |
| **RAII** | Constructor asigna, destructor libera |
| **Redimensionamiento** | Duplicar capacidad cuando está lleno |
| **Operador `[]`** | Acceso directo sin verificación |
| **`at()`** | Acceso con verificación de límites |
| **Iteradores** | `begin()`, `end()` para rangos |

## 🚀 Cómo compilar y ejecutar

```bash
g++ custom_vector.cpp -o custom_vector
./custom_vector

📋 Ejemplo de ejecución

=== Probando CustomVector ===

[Test 1] Vector vacío:
  size: 0
  capacity: 0
  empty: true

[Test 2] Agregando elementos 1 al 10:
  push_back(1) -> size=1, cap=1
  push_back(2) -> size=2, cap=2
  push_back(3) -> size=3, cap=4
  push_back(4) -> size=4, cap=4
  push_back(5) -> size=5, cap=8
  ...

[Test 3] Accediendo a elementos:
  Elementos: 1 2 3 4 5 6 7 8 9 10

[Test 4] Usando at():
  vec.at(5) = 6
  Excepción capturada correctamente: Index out of range

✅ Todos los tests pasaron!