include(compiler_warnings)

add_library(net_cluster_discovery
    src/gossip_node.cpp
)

target_include_directories(net_cluster_discovery
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_project_warnings(net_cluster_discovery)

