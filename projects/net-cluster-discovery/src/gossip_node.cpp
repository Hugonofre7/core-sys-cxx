#include <sys/gossip_node.hpp>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <chrono>
#include <sstream>

namespace sys
{

    // Constructor
    GossipNode::GossipNode(const std::string &node_id, const std::string &ip, int port)
        : node_id_(node_id), ip_(ip), port_(port), socket_fd_(-1), running_(false), rng_(rd_())
    {
    }

    // Destructor
    GossipNode::~GossipNode()
    {
        stop();
    }

    // Inicializar el nodo
    bool GossipNode::init(const std::string &seed_ip, int seed_port)
    {
        // Crear socket UDP
        socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
        if (socket_fd_ < 0)
        {
            std::cerr << "Error creating socket" << std::endl;
            return false;
        }

        // Configurar dirección local
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port_);

        // Bind al puerto
        if (bind(socket_fd_, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            std::cerr << "Error binding socket" << std::endl;
            close(socket_fd_);
            socket_fd_ = -1;
            return false;
        }

        // Agregarse a sí mismo como miembro
        update_member(node_id_, ip_, port_);

        // Si hay seed, contactarlo
        if (!seed_ip.empty() && seed_port > 0)
        {
            // TODO: Contactar seed node
            std::cout << "Node " << node_id_ << " contacting seed " << seed_ip << ":" << seed_port << std::endl;
        }

        running_ = true;

        // Iniciar hilos
        gossip_thread_ = std::thread(&GossipNode::gossip_thread, this);
        update_thread_ = std::thread(&GossipNode::update_thread, this);

        std::cout << "Node " << node_id_ << " initialized on " << ip_ << ":" << port_ << std::endl;
        return true;
    }

    // Detener el nodo
    void GossipNode::stop()
    {
        running_ = false;

        if (gossip_thread_.joinable())
        {
            gossip_thread_.join();
        }

        if (update_thread_.joinable())
        {
            update_thread_.join();
        }

        if (socket_fd_ >= 0)
        {
            close(socket_fd_);
            socket_fd_ = -1;
        }
    }

    // Obtener miembros activos
    std::vector<MemberInfo> GossipNode::get_active_members() const
    {
        std::lock_guard<std::mutex> lock(members_mutex_);
        std::vector<MemberInfo> active;

        auto now = std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                       .count();

        for (const auto &pair : members_)
        {
            if (pair.second.is_active && (now - pair.second.last_seen) < 30)
            {
                active.push_back(pair.second);
            }
        }

        return active;
    }

    // Serializar miembros a string
    std::string GossipNode::serialize_members() const
    {
        std::lock_guard<std::mutex> lock(members_mutex_);
        std::stringstream ss;

        for (const auto &pair : members_)
        {
            if (pair.second.is_active)
            {
                ss << pair.second.id << "|"
                   << pair.second.ip << "|"
                   << pair.second.port << ";";
            }
        }

        return ss.str();
    }

    // Deserializar miembros desde string
    void GossipNode::deserialize_members(const std::string &data)
    {
        std::stringstream ss(data);
        std::string member_str;

        while (std::getline(ss, member_str, ';'))
        {
            if (member_str.empty())
                continue;

            std::stringstream member_ss(member_str);
            std::string id, ip, port_str;

            std::getline(member_ss, id, '|');
            std::getline(member_ss, ip, '|');
            std::getline(member_ss, port_str, '|');

            if (!id.empty() && !ip.empty() && !port_str.empty())
            {
                int port = std::stoi(port_str);
                update_member(id, ip, port);
            }
        }
    }

    // Hilo de gossip
    void GossipNode::gossip_thread()
    {
        std::uniform_int_distribution<> dist(1000, 3000);

        while (running_)
        {
            // Esperar un tiempo aleatorio
            std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng_)));

            if (!running_)
                break;

            // Obtener lista de miembros
            auto members = get_active_members();

            if (members.size() <= 1)
                continue;

            // Elegir un miembro aleatorio (sin incluirse a sí mismo)
            std::uniform_int_distribution<> member_dist(0, members.size() - 1);
            int idx = member_dist(rng_);

            // Si elegimos nosotros mismos, continuar
            if (members[idx].id == node_id_)
                continue;

            // Serializar y enviar
            std::string data = serialize_members();
            std::cout << "Gossiping to " << members[idx].id << ": " << data << std::endl;

            send_message(members[idx].ip, members[idx].port, data);
        }
    }

    // Hilo de actualización
    void GossipNode::update_thread()
    {
        while (running_)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));

            if (!running_)
                break;

            // Limpiar miembros inactivos
            prune_inactive_members();
        }
    }

    // Enviar mensaje UDP
    bool GossipNode::send_message(const std::string &target_ip, int target_port, const std::string &msg)
    {
        if (socket_fd_ < 0)
            return false;

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(target_port);
        inet_pton(AF_INET, target_ip.c_str(), &addr.sin_addr);

        int n = sendto(socket_fd_, msg.c_str(), msg.size(), 0,
                       (struct sockaddr *)&addr, sizeof(addr));

        return n > 0;
    }

    // Recibir mensaje UDP
    std::string GossipNode::receive_message(int timeout_ms)
    {
        if (socket_fd_ < 0)
            return "";

        // Configurar timeout
        struct timeval tv;
        tv.tv_sec = timeout_ms / 1000;
        tv.tv_usec = (timeout_ms % 1000) * 1000;
        setsockopt(socket_fd_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

        char buffer[4096];
        struct sockaddr_in sender_addr;
        socklen_t addr_len = sizeof(sender_addr);

        int n = recvfrom(socket_fd_, buffer, sizeof(buffer) - 1, 0,
                         (struct sockaddr *)&sender_addr, &addr_len);

        if (n > 0)
        {
            buffer[n] = '\0';

            // Actualizar información del remitente
            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &sender_addr.sin_addr, ip_str, sizeof(ip_str));
            int port = ntohs(sender_addr.sin_port);

            // Buscar el ID del remitente (esto es simplificado)
            // En una implementación real, se extraería del mensaje

            return std::string(buffer);
        }

        return "";
    }

    // Actualizar miembro
    void GossipNode::update_member(const std::string &id, const std::string &ip, int port)
    {
        std::lock_guard<std::mutex> lock(members_mutex_);

        auto it = members_.find(id);
        if (it == members_.end())
        {
            std::cout << "New member discovered: " << id << " (" << ip << ":" << port << ")" << std::endl;
            members_[id] = MemberInfo(id, ip, port);
        }

        auto now = std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                       .count();

        members_[id].last_seen = now;
        members_[id].is_active = true;
    }

    // Limpiar miembros inactivos
    void GossipNode::prune_inactive_members()
    {
        std::lock_guard<std::mutex> lock(members_mutex_);

        auto now = std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                       .count();

        for (auto &pair : members_)
        {
            if (pair.second.is_active && (now - pair.second.last_seen) > 30)
            {
                std::cout << "Member " << pair.second.id << " marked as inactive" << std::endl;
                pair.second.is_active = false;
            }
        }
    }

} // namespace sys