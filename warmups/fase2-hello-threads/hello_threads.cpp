#include <iostream>
#include <thread>

// Funcion que ejecutara el thread
void hello(int id)
{
    std::cout << "Hello from thread " << id << std::endl;
}

int main()
{
    std::cout << "Main thread: Starting" << std::endl;

    // Crear 3 threads que ejecutaran la funcion hello()
    std::thread t1(hello, 1);
    std::thread t2(hello, 2);
    std::thread t3(hello, 3);

    // Esperar a que terminen
    t1.join();
    t2.join();
    t3.join();

    std::cout << "Main thread: all threads finished" << std::endl;

    return 0;
}
