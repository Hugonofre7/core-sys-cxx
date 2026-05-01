include(compiler_warnings)

add_library(net_cluster_discovery
    src/gossip_node.cpp
)

target_include_directories(net_cluster_discovery
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(net_cluster_discovery
    pthread
)

set_project_warnings(net_cluster_discovery)

# Test ejecutable
add_executable(test_gossip tests/test_gossip.cpp)
target_link_libraries(test_gossip net_cluster_discovery pthread)
target_include_directories(test_gossip PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_project_warnings(test_gossip)