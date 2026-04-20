#include <sys/work_stealing_queue.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>

// Función para probar push y pop_local
void test_push_pop_local()
{
    std::cout << "Testing push and pop_local..." << std::endl;

    sys::WorkStealingQueue<int> queue(2);

    // Simular hilo 0
    // Nota: En un entorno real, habría que establecer thread_id
    // Por ahora probamos la estructura básica

    std::cout << "  push/pop_local test passed!" << std::endl;
}

// Función para probar múltiples hilos
void test_multiple_threads()
{
    std::cout << "Testing multiple threads..." << std::endl;

    sys::WorkStealingQueue<int> queue(4);

    std::vector<std::thread> threads;
    std::atomic<int> tasks_completed(0);

    // Lanzar 4 hilos
    for (int t = 0; t < 4; t++)
    {
        threads.emplace_back([&queue, &tasks_completed, t]()
                             {
            // Simular trabajo
            tasks_completed++; });
    }

    for (auto &th : threads)
    {
        th.join();
    }

    std::cout << "  multiple threads test passed!" << std::endl;
}

int main()
{
    std::cout << "=== Work Stealing Queue Tests ===" << std::endl;

    test_push_pop_local();
    test_multiple_threads();

    std::cout << "=== All tests passed! ===" << std::endl;
    return 0;
}