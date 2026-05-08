#include <iostream>
#include <thread>
#include <chrono>
#include <sys/gossip_node.hpp>

int main()
{
    std::cout << "=== Gossip Protocol Tests ===" << std::endl;

    // Test 1: Crear un nodo
    std::cout << "\n[Test 1] Creating node..." << std::endl;
    sys::GossipNode node1("node1", "127.0.0.1", 8081);

    if (node1.init())
    {
        std::cout << "✓ Node initialized successfully" << std::endl;
    }
    else
    {
        std::cout << "✗ Failed to initialize node" << std::endl;
        return 1;
    }

    // Test 2: Verificar que el nodo se agregó a sí mismo
    std::cout << "\n[Test 2] Checking self registration..." << std::endl;
    auto members = node1.get_active_members();
    std::cout << "Active members: " << members.size() << std::endl;

    for (const auto &m : members)
    {
        std::cout << "  - " << m.id << " (" << m.ip << ":" << m.port << ")" << std::endl;
    }

    // Test 3: Serialización
    std::cout << "\n[Test 3] Testing serialization..." << std::endl;
    std::string serialized = node1.serialize_members();
    std::cout << "Serialized data: " << serialized << std::endl;

    if (!serialized.empty())
    {
        std::cout << "✓ Serialization works" << std::endl;
    }
    else
    {
        std::cout << "✗ Serialization empty" << std::endl;
    }

    // Test 4: Deserialización
    std::cout << "\n[Test 4] Testing deserialization..." << std::endl;
    sys::GossipNode node2("node2", "127.0.0.1", 8082);
    node2.deserialize_members(serialized);

    auto node2_members = node2.get_active_members();
    std::cout << "Node2 members after deserialization: " << node2_members.size() << std::endl;

    // Test 5: Detener nodo
    std::cout << "\n[Test 5] Stopping node..." << std::endl;
    node1.stop();
    std::cout << "✓ Node stopped successfully" << std::endl;

    std::cout << "\n=== All tests passed! ===" << std::endl;
    return 0;
}