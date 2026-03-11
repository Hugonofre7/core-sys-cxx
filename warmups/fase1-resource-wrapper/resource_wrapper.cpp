#include <iostream>

// Clase que encapsula un recurso (memoria dinámica)
class IntArray
{
private:
    int *data; // Puntero al array
    int size;  // Tamaño del array

public:
    // Constructor: adquiere el recurso
    IntArray(int n)
    {
        std::cout << "Constructor: allocating array of size " << n << std::endl;
        size = n;
        data = new int[size];
    }

    // Destructor: libera el recurso
    ~IntArray()
    {
        std::cout << "Destructor: freeing memory" << std::endl;
        delete[] data;
    }

    // Método para establecer un valor
    void set(int index, int value)
    {
        if (index >= 0 && index < size)
        {
            data[index] = value;
        }
    }

    // Método para obtener un valor
    int get(int index)
    {
        if (index >= 0 && index < size)
        {
            return data[index];
        }
        return -1;
    }
};

int main()
{
    std::cout << "Entering main" << std::endl;

    // Crear objeto (se llama al constructor)
    IntArray arr(5);

    // Usar el objeto
    for (int i = 0; i < 5; i++)
    {
        arr.set(i, i * 10);
    }

    std::cout << "Array contents: ";
    for (int i = 0; i < 5; i++)
    {
        std::cout << arr.get(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Exiting main" << std::endl;
    // Al salir de main, se llama al destructor automáticamente

    return 0;
}