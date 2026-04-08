#include <iostream>
#include <thread>
#include <vector>
#include <mutex> // ← NUEVO

// Variable compartida
int counter = 0;
std::mutex mtx; // ← Mutex para proteger counter

// Función que incrementa el contador (con protección)
void increment(int times)
{
    for (int i = 0; i < times; i++)
    {
        mtx.lock();   // ← Bloquear el mutex
        counter++;    // ← Sección crítica
        mtx.unlock(); // ← Desbloquear
    }
}

int main()
{
    const int num_threads = 10;
    const int increments_per_thread = 100000;

    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; i++)
    {
        threads.emplace_back(increment, increments_per_thread);
    }

    for (auto &t : threads)
    {
        t.join();
    }

    std::cout << "Expected value: " << num_threads * increments_per_thread << std::endl;
    std::cout << "Actual value:   " << counter << std::endl;

    return 0;
}