#include <sys/slab_allocator.hpp>
#include <cassert>

int main()
{
    using sys::SlabAllocator;

    // Allocator para 10 enteros
    SlabAllocator<int, 10> alloc;

    // Test 1: Capacidad correcta
    assert(alloc.capacity() == 10);
    assert(alloc.used() == 0);
    assert(alloc.free() == 10);

    // Test 2: Allocar un elemento
    int *p1 = alloc.allocate();
    assert(p1 != nullptr);
    assert(alloc.used() == 1);
    assert(alloc.free() == 9);

    // Test 3: Liberar y reusar
    alloc.deallocate(p1);
    assert(alloc.used() == 0);
    assert(alloc.free() == 10);

    // Test 4: Allocar hasta el límite
    int *ptrs[10];
    for (int i = 0; i < 10; ++i)
    {
        ptrs[i] = alloc.allocate();
        assert(ptrs[i] != nullptr);
    }
    assert(alloc.used() == 10);
    assert(alloc.free() == 0);

    // Test 5: Fallo cuando está lleno
    assert(alloc.allocate() == nullptr);

    return 0;
}