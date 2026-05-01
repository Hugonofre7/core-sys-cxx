#pragma once

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <mutex>
#include <random>

namespace sys
{

    // Información de un miembro del cluster
    struct MemberInfo
    {
        std::string id; // Identificador único
        std::string ip; // Dirección IP
        int port;       // Puerto UDP
        long last_seen; // Timestamp de última comunicación
        bool is_active; // Estado actual

        MemberInfo() : port(0), last_seen(0), is_active(false) {}
        MemberInfo(const std::string &id, const std::string &ip, int port)
            : id(id), ip(ip), port(port), last_seen(0), is_active(true) {}
    };

    // Nodo Gossip para descubrimiento de miembros
    class GossipNode
    {
    public:
        GossipNode(const std::string &node_id, const std::string &ip, int port);
        ~GossipNode();

        // No copiable
        GossipNode(const GossipNode &) = delete;
        GossipNode &operator=(const GossipNode &) = delete;

        // Inicializar el nodo (opcionalmente con un seed)
        bool init(const std::string &seed_ip = "", int seed_port = 0);

        // Detener el nodo
        void stop();

        // Obtener lista de miembros activos
        std::vector<MemberInfo> get_active_members() const;

        // Serializar lista de miembros a string
        std::string serialize_members() const;

        // Deserializar lista de miembros desde string
        void deserialize_members(const std::string &data);

    private:
        // Hilo principal de gossip
        void gossip_thread();

        // Hilo de actualización de estado
        void update_thread();

        // Enviar mensaje UDP
        bool send_message(const std::string &target_ip, int target_port, const std::string &msg);

        // Recibir mensaje UDP (no bloqueante)
        std::string receive_message(int timeout_ms);

        // Agregar o actualizar un miembro
        void update_member(const std::string &id, const std::string &ip, int port);

        // Marcar miembros inactivos
        void prune_inactive_members();

        std::string node_id_;
        std::string ip_;
        int port_;
        int socket_fd_;
        bool running_;

        std::map<std::string, MemberInfo> members_;
        mutable std::mutex members_mutex_;

        std::thread gossip_thread_;
        std::thread update_thread_;

        std::random_device rd_;
        std::mt19937 rng_;
    };

} // namespace sys