#include <iostream>
#include <string>
#include <sys/bloom_filter.hpp>

void test_basic_operations()
{
    std::cout << "\n[Test 1] Operaciones básicas" << std::endl;

    sys::BloomFilter<std::string> filter(100, 3);

    std::cout << "  Tamaño del bitset: " << filter.size() << std::endl;
    std::cout << "  Número de hashes: " << filter.hash_count() << std::endl;
    std::cout << "  Factor de carga inicial: " << filter.load_factor() << std::endl;
}

void test_insert_and_contains()
{
    std::cout << "\n[Test 2] Insertar y verificar" << std::endl;

    sys::BloomFilter<std::string> filter(100, 3);

    // Insertar elementos
    filter.insert("manzana");
    filter.insert("pera");
    filter.insert("uva");

    // Verificar elementos insertados
    std::cout << "  'manzana' está? " << (filter.contains("manzana") ? "Sí" : "No") << std::endl;
    std::cout << "  'pera' está? " << (filter.contains("pera") ? "Sí" : "No") << std::endl;
    std::cout << "  'uva' está? " << (filter.contains("uva") ? "Sí" : "No") << std::endl;

    // Verificar elemento no insertado
    std::cout << "  'sandía' está? " << (filter.contains("sandía") ? "Sí (falso positivo)" : "No") << std::endl;
}

void test_false_positives()
{
    std::cout << "\n[Test 3] Probando falsos positivos" << std::endl;

    sys::BloomFilter<int> filter(1000, 5);

    // Insertar muchos elementos
    for (int i = 0; i < 500; i++)
    {
        filter.insert(i);
    }

    // Verificar elementos que NO fueron insertados
    int false_positives = 0;
    int total_tests = 1000;

    for (int i = 500; i < 500 + total_tests; i++)
    {
        if (filter.contains(i))
        {
            false_positives++;
        }
    }

    double false_positive_rate = 100.0 * false_positives / total_tests;
    std::cout << "  Falsos positivos: " << false_positives << " / " << total_tests
              << " (" << false_positive_rate << "%)" << std::endl;
    std::cout << "  Factor de carga: " << filter.load_factor() << std::endl;
}

void test_clear()
{
    std::cout << "\n[Test 4] Limpiar el filtro" << std::endl;

    sys::BloomFilter<std::string> filter(100, 3);

    filter.insert("test");
    std::cout << "  Antes de clear: contiene 'test'? " << (filter.contains("test") ? "Sí" : "No") << std::endl;

    filter.clear();
    std::cout << "  Después de clear: contiene 'test'? " << (filter.contains("test") ? "Sí (error)" : "No") << std::endl;
}

void test_different_types()
{
    std::cout << "\n[Test 5] Diferentes tipos de datos" << std::endl;

    sys::BloomFilter<int> int_filter(100, 3);
    int_filter.insert(42);
    std::cout << "  int_filter contiene 42? " << (int_filter.contains(42) ? "Sí" : "No") << std::endl;

    sys::BloomFilter<double> double_filter(100, 3);
    double_filter.insert(3.14159);
    std::cout << "  double_filter contiene 3.14159? " << (double_filter.contains(3.14159) ? "Sí" : "No") << std::endl;
}

int main()
{
    std::cout << "=== BLOOM FILTER TESTS ===" << std::endl;

    test_basic_operations();
    test_insert_and_contains();
    test_false_positives();
    test_clear();
    test_different_types();

    std::cout << "\n=== TODOS LOS TESTS COMPLETADOS ===" << std::endl;

    return 0;
}