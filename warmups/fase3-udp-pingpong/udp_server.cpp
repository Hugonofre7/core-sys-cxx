#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(client_addr);

    // 1. Crear socket UDP
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0)
    {
        std::cerr << "Error al crear socket" << std::endl;
        return 1;
    }

    // 2. Configurar dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Escuchar en todas las interfaces
    server_addr.sin_port = htons(8080);       // Puerto 8080

    // 3. Enlazar socket al puerto
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Error al enlazar socket" << std::endl;
        close(server_fd);
        return 1;
    }

    std::cout << "Servidor UDP escuchando en puerto 8080..." << std::endl;

    // 4. Recibir y responder mensajes
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));

        // Recibir mensaje del cliente
        int n = recvfrom(server_fd, buffer, sizeof(buffer) - 1, 0,
                         (struct sockaddr *)&client_addr, &addr_len);

        if (n > 0)
        {
            std::string client_ip = inet_ntoa(client_addr.sin_addr);
            int client_port = ntohs(client_addr.sin_port);

            std::cout << "Recibido de " << client_ip << ":" << client_port
                      << " -> " << buffer << std::endl;

            // Responder con "PONG"
            std::string response = "PONG";
            sendto(server_fd, response.c_str(), response.size(), 0,
                   (struct sockaddr *)&client_addr, addr_len);
            std::cout << "Enviado PONG a " << client_ip << ":" << client_port << std::endl;
        }
    }

    close(server_fd);
    return 0;
}