include(compiler_warnings)

add_library(sys_memory_engine
    src/slab_allocator.cpp
)

target_include_directories(sys_memory_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_project_warnings(sys_memory_engine)

add_executable(test_slab_allocator tests/test_slab_allocator.cpp)
target_link_libraries(test_slab_allocator sys_memory_engine)
target_include_directories(test_slab_allocator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_project_warnings(test_slab_allocator)