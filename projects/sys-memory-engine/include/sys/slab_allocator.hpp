#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>

namespace sys
{

    template <typename T, size_t PoolSize>
    class SlabAllocator
    {
    public:
        SlabAllocator() noexcept;
        ~SlabAllocator() noexcept;

        // No copiable
        SlabAllocator(const SlabAllocator &) = delete;
        SlabAllocator &operator=(const SlabAllocator &) = delete;

        // Movible
        SlabAllocator(SlabAllocator &&other) noexcept;
        SlabAllocator &operator=(SlabAllocator &&other) noexcept;

        T *allocate() noexcept;
        void deallocate(T *ptr) noexcept;

        // Utilidades
        size_t capacity() const noexcept { return PoolSize; }
        size_t used() const noexcept { return used_count_; }
        size_t free() const noexcept { return PoolSize - used_count_; }

    private:
        // Union fuerza alineación correcta entre nodo y datos
        union Node
        {
            Node *next;
            T data; // Solo para alineación, no se usa directamente
        };

        Node *free_list_ = nullptr;
        size_t used_count_ = 0;
        alignas(Node) std::byte storage_[PoolSize * sizeof(Node)];
    };

}