cmake_minimum_required(VERSION 3.15)
project(core-sys-cxx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(compiler_warnings)
include(sanitizers)

add_subdirectory(projects/sys-memory-engine)
add_subdirectory(projects/net-cluster-discovery)
add_subdirectory(projects/core-task-scheduler)
add_subdirectory(projects/data-stream-filters)

