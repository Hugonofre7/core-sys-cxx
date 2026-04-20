#include <sys/work_stealing_queue.hpp>
#include <thread>
#include <algorithm>
#include <functional>

namespace sys
{

    // Inicialización del ID local para cada hilo
    template <typename T>
    thread_local size_t WorkStealingQueue<T>::thread_id_ = 0;

    // Constructor: crea una cola por cada hilo
    template <typename T>
    WorkStealingQueue<T>::WorkStealingQueue(size_t num_threads)
        : queues_(num_threads)
    {
        // Cada hilo obtendrá su ID al ejecutar current_thread_id()
    }

    // Insertar tarea en la cola del hilo actual
    template <typename T>
    void WorkStealingQueue<T>::push(T &&task)
    {
        size_t id = current_thread_id();
        LocalQueue &lq = queues_[id];

        std::lock_guard<std::mutex> lock(lq.mtx);
        lq.deque.push_back(std::forward<T>(task));
    }

    // Tomar tarea de la cola local (pop_back)
    template <typename T>
    std::optional<T> WorkStealingQueue<T>::pop_local()
    {
        size_t id = current_thread_id();
        LocalQueue &lq = queues_[id];

        std::lock_guard<std::mutex> lock(lq.mtx);
        if (lq.deque.empty())
        {
            return std::nullopt;
        }

        T task = std::move(lq.deque.back());
        lq.deque.pop_back();
        return task;
    }

    // Robar tarea de otro hilo (pop_front)
    template <typename T>
    std::optional<T> WorkStealingQueue<T>::steal()
    {
        size_t my_id = current_thread_id(); // ← DECLARAR my_id
        size_t num = queues_.size();

        // Intentar robar de otros hilos en orden aleatorio
        size_t start = (my_id + 1) % num;

        for (size_t i = 0; i < num - 1; ++i)
        {
            size_t victim = (start + i) % num;
            LocalQueue &lq = queues_[victim];

            // Intentar bloquear la cola de la víctima
            if (lq.mtx.try_lock())
            {
                if (!lq.deque.empty())
                {
                    T task = std::move(lq.deque.front());
                    lq.deque.pop_front();
                    lq.mtx.unlock();
                    return task;
                }
                lq.mtx.unlock();
            }
        }

        return std::nullopt;
    }

    // Obtener ID del hilo actual (0..num_threads-1)
    template <typename T>
    size_t WorkStealingQueue<T>::current_thread_id()
    {
        if (thread_id_ == 0)
        {
            static std::atomic<size_t> next_id(1);
            thread_id_ = next_id.fetch_add(1);
        }
        return thread_id_ - 1;
    }

    // Instanciación explícita para std::function<void()>
    template class WorkStealingQueue<std::function<void()>>;
    template class WorkStealingQueue<int>;

} // namespace sys