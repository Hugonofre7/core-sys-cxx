include(compiler_warnings)

add_library(data_stream_filters
    src/bloom_filter.cpp
)

target_include_directories(data_stream_filters
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_project_warnings(data_stream_filters)
