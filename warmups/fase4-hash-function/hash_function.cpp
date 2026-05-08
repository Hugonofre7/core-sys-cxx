#include <iostream>
#include <string>
#include <functional>

// ============================================
// FUNCIÓN HASH SIMPLE (tipo djb2)
// ============================================
// Algoritmo creado por Daniel J. Bernstein
// Muy usado en sistemas de hash simples
unsigned long djb2_hash(const std::string &str)
{
    unsigned long hash = 5381;

    for (char c : str)
    {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

// ============================================
// FUNCIÓN HASH SIMPLE (tipo sdbm)
// ============================================
// Usado en bases de datos sdbm
unsigned long sdbm_hash(const std::string &str)
{
    unsigned long hash = 0;

    for (char c : str)
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

// ============================================
// FUNCIÓN HASH PARA NÚMEROS
// ============================================
size_t int_hash(int value)
{
    // Mezclar bits para distribuir mejor
    value = ((value >> 16) ^ value) * 0x45d9f3b;
    value = ((value >> 16) ^ value) * 0x45d9f3b;
    value = (value >> 16) ^ value;
    return value;
}

// ============================================
// FUNCIÓN HASH PARA STRING (usando std::hash)
// ============================================
size_t std_string_hash(const std::string &str)
{
    std::hash<std::string> hasher;
    return hasher(str);
}

// ============================================
// MÉTRICAS Y DEMOSTRACIÓN
// ============================================

// Calcular y mostrar hash de un string
void test_hash(const std::string &name, const std::string &str)
{
    std::cout << "[" << name << "]" << std::endl;
    std::cout << "  String: \"" << str << "\"" << std::endl;
    std::cout << "  djb2:   " << djb2_hash(str) << std::endl;
    std::cout << "  sdbm:   " << sdbm_hash(str) << std::endl;
    std::cout << "  std:    " << std_string_hash(str) << std::endl;
    std::cout << std::endl;
}

// Mostrar distribución para números pequeños
void test_int_hash()
{
    std::cout << "[Enteros]" << std::endl;
    for (int i = 0; i <= 10; i++)
    {
        std::cout << "  int_hash(" << i << ") = " << int_hash(i) << std::endl;
    }
    std::cout << std::endl;
}

// Demostrar el problema de colisiones
void demonstrate_collisions()
{
    std::cout << "[Demostración de colisiones]" << std::endl;

    // Palabras similares con diferentes hashes
    std::cout << "  djb2(\"cat\")   = " << djb2_hash("cat") << std::endl;
    std::cout << "  djb2(\"dog\")   = " << djb2_hash("dog") << std::endl;
    std::cout << "  djb2(\"car\")   = " << djb2_hash("car") << std::endl;

    // Misma palabra, mismo hash (debe ser igual)
    std::cout << "  djb2(\"hello\") = " << djb2_hash("hello") << std::endl;
    std::cout << "  djb2(\"hello\") = " << djb2_hash("hello") << std::endl;

    std::cout << std::endl;
}

int main()
{
    std::cout << "=== FUNCIONES HASH ===" << std::endl;
    std::cout << std::endl;

    // Probar diferentes strings
    test_hash("Palabra corta", "hola");
    test_hash("Palabra larga", "algoritmo de hash");
    test_hash("Palabra con números", "user12345");
    test_hash("Fruta 1", "manzana");
    test_hash("Fruta 2", "pera");
    test_hash("Fruta 3", "uva");

    // Probar enteros
    test_int_hash();

    // Demostrar colisiones
    demonstrate_collisions();

    // Explicación
    std::cout << "[¿Qué es una función hash?]" << std::endl;
    std::cout << "  - Convierte datos de tamaño variable en un valor fijo" << std::endl;
    std::cout << "  - Debe ser determinística (misma entrada = mismo hash)" << std::endl;
    std::cout << "  - Distribución uniforme (evitar colisiones)" << std::endl;
    std::cout << "  - Rápida de calcular" << std::endl;
    std::cout << std::endl;

    std::cout << "✅ Todas las pruebas completadas" << std::endl;

    return 0;
}