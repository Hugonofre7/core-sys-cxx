#include <iostream>

// Versión simplificada de unique_ptr
template <typename T>
class SmartPtr
{
private:
    T *ptr; // Puntero crudo al recurso

public:
    // Constructor: adquiere el recurso
    explicit SmartPtr(T *p = nullptr)
    {
        std::cout << "SmartPtr constructor" << std::endl;
        ptr = p;
    }

    // Destructor: libera el recurso
    ~SmartPtr()
    {
        std::cout << "SmartPtr destructor" << std::endl;
        delete ptr;
    }

    // Sobrecarga de operadores para usarlo como puntero
    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }

    // Obtener el puntero crudo
    T *get() const { return ptr; }
};

// Una clase simple para probar
class Test
{
private:
    int id;

public:
    Test(int i) : id(i)
    {
        std::cout << "Test constructor (" << id << ")" << std::endl;
    }
    ~Test()
    {
        std::cout << "Test destructor (" << id << ")" << std::endl;
    }
    void greet() const
    {
        std::cout << "Hello from Test " << id << std::endl;
    }
};

int main()
{
    std::cout << "Entering main" << std::endl;

    // Crear SmartPtr que gestiona un objeto Test
    SmartPtr<Test> sp(new Test(1));

    // Usar el objeto a través del smart pointer
    sp->greet();

    std::cout << "Exiting main" << std::endl;
    // Al salir, se llama al destructor de SmartPtr y luego al de Test

    return 0;
}