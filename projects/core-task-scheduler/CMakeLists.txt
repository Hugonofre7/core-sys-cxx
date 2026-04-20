include(compiler_warnings)

add_library(core_task_scheduler
    src/work_stealing_queue.cpp
)

target_include_directories(core_task_scheduler
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_project_warnings(core_task_scheduler)

# Test ejecutable
add_executable(test_work_stealing tests/test_work_stealing.cpp)
target_link_libraries(test_work_stealing core_task_scheduler)
target_include_directories(test_work_stealing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_project_warnings(test_work_stealing)

