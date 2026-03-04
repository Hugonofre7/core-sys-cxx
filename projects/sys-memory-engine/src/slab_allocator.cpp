#include <sys/slab_allocator.hpp>
#include <cstddef>

namespace sys
{

    template <typename T, size_t PoolSize>
    SlabAllocator<T, PoolSize>::SlabAllocator() noexcept
        : free_list_(nullptr), used_count_(0)
    {

        printf("Constructor: PoolSize=%zu, sizeof(T)=%zu, total bytes=%zu\n",
               PoolSize, sizeof(T), PoolSize * sizeof(T));
        printf("storage_ address: %p\n", &storage_[0]);

        Node *current = reinterpret_cast<Node *>(&storage_[0]);
        printf("first Node address: %p\n", current);

        for (size_t i = 0; i < PoolSize; ++i)
        {
            printf("  i=%zu, current=%p, next=%p\n", i, current, free_list_);
            current->next = free_list_;
            free_list_ = current;
            current = reinterpret_cast<Node *>(
                reinterpret_cast<char *>(current) + sizeof(Node));
        }
        printf("free_list_ final: %p\n", free_list_);
    }

    template <typename T, size_t PoolSize>
    SlabAllocator<T, PoolSize>::~SlabAllocator() noexcept
    {
        // Nada que hacer, el storage_ se libera solo
    }

    template <typename T, size_t PoolSize>
    SlabAllocator<T, PoolSize>::SlabAllocator(SlabAllocator &&other) noexcept
        : free_list_(other.free_list_), used_count_(other.used_count_)
    {
        other.free_list_ = nullptr;
        other.used_count_ = 0;
    }

    template <typename T, size_t PoolSize>
    auto SlabAllocator<T, PoolSize>::operator=(SlabAllocator &&other) noexcept -> SlabAllocator &
    {
        if (this != &other)
        {
            free_list_ = other.free_list_;
            used_count_ = other.used_count_;
            other.free_list_ = nullptr;
            other.used_count_ = 0;
        }
        return *this;
    }

    template <typename T, size_t PoolSize>
    T *SlabAllocator<T, PoolSize>::allocate() noexcept
    {
        printf("allocate: free_list_=%p, used_count_=%zu\n", free_list_, used_count_);
        if (!free_list_)
        {
            printf("  free_list_ is null, returning nullptr\n");
            return nullptr;
        }

        Node *block = free_list_;
        free_list_ = block->next;
        printf("  after update: free_list_=%p\n", free_list_); // <-- AÑADE ESTA LÍNEA
        ++used_count_;

        printf("  returning %p as T*\n", reinterpret_cast<T *>(block));
        return reinterpret_cast<T *>(block);
    }

    template <typename T, size_t PoolSize>
    void SlabAllocator<T, PoolSize>::deallocate(T *ptr) noexcept
    {
        if (!ptr)
            return;

        Node *block = reinterpret_cast<Node *>(ptr);
        block->next = free_list_;
        free_list_ = block;
        --used_count_;
    }

    // Explicit instantiation for tests
    template class SlabAllocator<int, 10>;

}