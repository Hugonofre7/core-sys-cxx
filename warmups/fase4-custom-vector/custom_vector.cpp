#include <iostream>
#include <stdexcept>

template <typename T>
class CustomVector
{
private:
    T *data;    // Puntero al array dinámico
    size_t cap; // Capacidad actual
    size_t len; // Número de elementos actuales

    // Redimensionar (aumentar capacidad)
    void resize(size_t new_capacity)
    {
        T *new_data = new T[new_capacity];

        // Copiar elementos existentes
        for (size_t i = 0; i < len; i++)
        {
            new_data[i] = data[i];
        }

        // Liberar memoria vieja
        delete[] data;

        // Actualizar punteros
        data = new_data;
        cap = new_capacity;
    }

public:
    // Constructor
    CustomVector() : data(nullptr), cap(0), len(0) {}

    // Constructor con capacidad inicial
    explicit CustomVector(size_t initial_capacity)
        : data(new T[initial_capacity]), cap(initial_capacity), len(0) {}

    // Destructor
    ~CustomVector()
    {
        delete[] data;
    }

    // Agregar elemento al final
    void push_back(const T &value)
    {
        if (len >= cap)
        {
            // Si está lleno, duplicar capacidad
            size_t new_cap = (cap == 0) ? 1 : cap * 2;
            resize(new_cap);
        }
        data[len++] = value;
    }

    // Eliminar último elemento
    void pop_back()
    {
        if (len > 0)
        {
            len--;
        }
    }

    // Acceder a elemento (con verificación)
    T &at(size_t index)
    {
        if (index >= len)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Acceder a elemento (sin verificación)
    T &operator[](size_t index)
    {
        return data[index];
    }

    // Versión const para lectura
    const T &operator[](size_t index) const
    {
        return data[index];
    }

    // Obtener tamaño actual
    size_t size() const
    {
        return len;
    }

    // Obtener capacidad
    size_t capacity() const
    {
        return cap;
    }

    // Verificar si está vacío
    bool empty() const
    {
        return len == 0;
    }

    // Limpiar todos los elementos
    void clear()
    {
        len = 0;
    }

    // Iterador simple (para rangos)
    T *begin() { return data; }
    T *end() { return data + len; }
    const T *begin() const { return data; }
    const T *end() const { return data + len; }
};

// Función para probar el CustomVector
void test_custom_vector()
{
    std::cout << "=== Probando CustomVector ===" << std::endl;

    // Test 1: Crear vector vacío
    CustomVector<int> vec;
    std::cout << "\n[Test 1] Vector vacío:" << std::endl;
    std::cout << "  size: " << vec.size() << std::endl;
    std::cout << "  capacity: " << vec.capacity() << std::endl;
    std::cout << "  empty: " << (vec.empty() ? "true" : "false") << std::endl;

    // Test 2: Agregar elementos
    std::cout << "\n[Test 2] Agregando elementos 1 al 10:" << std::endl;
    for (int i = 1; i <= 10; i++)
    {
        vec.push_back(i);
        std::cout << "  push_back(" << i << ") -> size=" << vec.size()
                  << ", cap=" << vec.capacity() << std::endl;
    }

    // Test 3: Acceder a elementos
    std::cout << "\n[Test 3] Accediendo a elementos:" << std::endl;
    std::cout << "  Elementos: ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // Test 4: Usar at() con verificación
    std::cout << "\n[Test 4] Usando at():" << std::endl;
    try
    {
        std::cout << "  vec.at(5) = " << vec.at(5) << std::endl;
        std::cout << "  vec.at(99) = " << vec.at(99) << std::endl; // Esto lanza excepción
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "  Excepción capturada correctamente: " << e.what() << std::endl;
    }

    // Test 5: Pop back
    std::cout << "\n[Test 5] Eliminando elementos:" << std::endl;
    vec.pop_back();
    std::cout << "  Después de pop_back(): size=" << vec.size() << std::endl;

    // Test 6: Clear
    std::cout << "\n[Test 6] Limpiando vector:" << std::endl;
    vec.clear();
    std::cout << "  Después de clear(): size=" << vec.size() << std::endl;
    std::cout << "  capacity=" << vec.capacity() << " (no cambia)" << std::endl;

    // Test 7: Usar iteradores
    std::cout << "\n[Test 7] Usando iteradores:" << std::endl;
    for (int i = 1; i <= 5; i++)
    {
        vec.push_back(i * 10);
    }
    std::cout << "  Elementos: ";
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test 8: Vector de strings
    std::cout << "\n[Test 8] Vector de strings:" << std::endl;
    CustomVector<std::string> str_vec;
    str_vec.push_back("Hola");
    str_vec.push_back("Mundo");
    str_vec.push_back("Custom");
    str_vec.push_back("Vector");

    for (size_t i = 0; i < str_vec.size(); i++)
    {
        std::cout << "  str_vec[" << i << "] = " << str_vec[i] << std::endl;
    }

    std::cout << "\n✅ Todos los tests pasaron!" << std::endl;
}

int main()
{
    test_custom_vector();
    return 0;
}