add_library(sys_memory_engine
    src/slab_allocator.cpp
)

target_include_directories(sys_memory_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_project_warnings(sys_memory_engine)

