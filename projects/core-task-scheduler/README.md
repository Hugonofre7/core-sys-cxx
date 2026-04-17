# core-task-scheduler - Work Stealing Queue

Proyecto final de la **Fase 2: Concurrencia**.

## 📌 Objetivo

Implementar una **cola de robo de trabajo (Work Stealing Queue)** para balancear tareas entre múltiples hilos. Es el corazón de sistemas como Go Goroutines, Java Fork/Join y Intel TBB.

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| Work Stealing | Hilos sin trabajo roban tareas de otros hilos |
| `std::deque` | Cola de doble extremo (push/pop por ambos lados) |
| `std::mutex` | Protege cada cola individualmente |
| `std::optional` | Retorna tarea o "sin tarea" |
| `std::atomic` | Asigna IDs únicos a cada hilo |
| `thread_local` | Cada hilo tiene su propio ID |

## 🚀 Cómo compilar y ejecutar

```bash
cd /Users/hugonofre7/Projects/C++/core-sys-cxx/build
cmake --build .

std::optional no reconocido por VS Code
namespace std has no member optional

Causa: VS Code usa C++11/14 por defecto.

Solución: Configurar c_cpp_properties.json

{
    "configurations": [{
        "cppStandard": "c++17",
        "compileCommands": "${workspaceFolder}/build/compile_commands.json"
    }]
}

my_id no definido en steal()
'my_id' was not declared in this scope

Solución: Declarar la variable:
size_t my_id = current_thread_id();  // ← Añadir esta línea

current_thread_id() marcado como "not a template"
Error en editor: VS Code confunde la sintaxis de templates.

Solución: Ignorar si compila bien, o regenerar compile_commands.json
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
ln -sf build/compile_commands.json ..

Invalid explicit instantiation
Error:
invalid explicit instantiation declaration
Solución: Añadir el include:
#include <functional>
try_lock() sin comprobar resultado
Advertencia: No verificar si try_lock() tuvo éxito.

Solución: Siempre comprobar:
if (lq.mtx.try_lock()) {
    // Acceder a la cola
    lq.mtx.unlock();
}


