# data-stream-filters - Bloom Filter

Proyecto final de la **Fase 4: STL y Rendimiento**.

## 📌 Objetivo

Implementar un **Filtro Bloom**, una estructura de datos probabilística que permite saber si un elemento **podría estar** en un conjunto con alta eficiencia de memoria.

## 🧠 ¿Qué es un Filtro Bloom?

Es una estructura que:
- **Nunca da falsos negativos:** Si dice "no está", es 100% seguro
- **Puede dar falsos positivos:** Si dice "sí está", puede ser un error
- **Usa muy poca memoria:** Bits en lugar de elementos completos
- **Muy rápido:** O(k) donde k es el número de funciones hash

### Analogía

Imagina una hoja de respuestas de examen donde cada pregunta tiene 3 respuestas posibles. Varias personas marcan sus respuestas. Para saber si alguien respondió una pregunta específica:

- Si la pregunta NO tiene ninguna marca → seguro que nadie la respondió
- Si la pregunta SÍ tiene marcas → alguien pudo haberla respondido (o no)

## 🏗️ Estructura del Proyecto

data-stream-filters/
├── include/sys/
│ └── bloom_filter.hpp ← Implementación completa (header-only)
├── tests/
│ └── test_bloom_filter.cpp ← Tests unitarios
└── CMakeLists.txt


## 🚀 Cómo compilar y ejecutar

```bash
cd /Users/hugonofre7/Projects/C++/core-sys-cxx/build
cmake --build .
./projects/data-stream-filters/test_bloom_filter


📋 Ejemplo de ejecución.

=== BLOOM FILTER TESTS ===

[Test 1] Operaciones básicas
  Tamaño del bitset: 100
  Número de hashes: 3
  Factor de carga inicial: 0

[Test 2] Insertar y verificar
  'manzana' está? Sí
  'pera' está? Sí
  'uva' está? Sí
  'sandía' está? No

[Test 3] Probando falsos positivos
  Falsos positivos: 762 / 1000 (76.2%)
  Factor de carga: 0.892

[Test 4] Limpiar el filtro
  Antes de clear: contiene 'test'? Sí
  Después de clear: contiene 'test'? No

[Test 5] Diferentes tipos de datos
  int_filter contiene 42? Sí
  double_filter contiene 3.14159? Sí

=== TODOS LOS TESTS COMPLETADOS ===