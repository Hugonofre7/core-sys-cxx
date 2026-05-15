include(compiler_warnings)

# Header-only library (no .cpp files)
add_library(data_stream_filters INTERFACE)

target_include_directories(data_stream_filters
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Test ejecutable
add_executable(test_bloom_filter tests/test_bloom_filter.cpp)
target_link_libraries(test_bloom_filter data_stream_filters)
target_include_directories(test_bloom_filter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_project_warnings(test_bloom_filter)