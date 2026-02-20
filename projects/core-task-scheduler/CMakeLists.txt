include(compiler_warnings)

add_library(core_task_scheduler
    src/work_stealing_queue.cpp
)

target_include_directories(core_task_scheduler
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_project_warnings(core_task_scheduler)
