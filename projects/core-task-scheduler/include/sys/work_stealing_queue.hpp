#pragma once

#include <atomic>
#include <cstddef>
#include <deque>
#include <mutex>
#include <optional>
#include <vector>

namespace sys
{

    // Work Stealing Queue para tareas de tipo T
    template <typename T>
    class WorkStealingQueue
    {
    public:
        explicit WorkStealingQueue(size_t num_threads);
        ~WorkStealingQueue() = default;

        // No copiable, sí movible
        WorkStealingQueue(const WorkStealingQueue &) = delete;
        WorkStealingQueue &operator=(const WorkStealingQueue &) = delete;

        // Insertar tarea en la cola del hilo actual (push_back)
        void push(T &&task);

        // Robar tarea de otro hilo (pop_front)
        std::optional<T> steal();

        // Tomar tarea de la cola local (pop_back)
        std::optional<T> pop_local();

        // Obtener ID del hilo actual (0..num_threads-1)
        static size_t current_thread_id();

        // Obtener número de hilos
        size_t num_threads() const { return queues_.size(); }

    private:
        // Una cola por hilo
        struct LocalQueue
        {
            std::deque<T> deque;
            std::mutex mtx;
        };

        std::vector<LocalQueue> queues_;
        static thread_local size_t thread_id_;
    };

}
