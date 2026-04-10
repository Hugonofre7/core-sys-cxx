#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

// Flag atómico (más ligero que mutex)
std::atomic<bool> ready(false);

// Función que espera a que la bandera esté activa
void wait_for_signal(int id)
{
    std::cout << "Thread " << id << " waiting..." << std::endl;

    // Espera activa (busy-wait) hasta que ready sea true
    while (!ready.load())
    {
        // Opcional: pequeña pausa para no saturar la CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "Thread " << id << " received signal!" << std::endl;
}

int main()
{
    std::cout << "Main: starting 5 threads" << std::endl;

    // Crear 5 hilos que esperan
    std::thread threads[5];
    for (int i = 0; i < 5; i++)
    {
        threads[i] = std::thread(wait_for_signal, i);
    }

    // Simular trabajo principal
    std::cout << "Main: doing some work..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Activar la bandera
    std::cout << "Main: sending signal!" << std::endl;
    ready.store(true);

    // Esperar a que todos terminen
    for (int i = 0; i < 5; i++)
    {
        threads[i].join();
    }

    std::cout << "Main: all threads finished" << std::endl;

    return 0;
}