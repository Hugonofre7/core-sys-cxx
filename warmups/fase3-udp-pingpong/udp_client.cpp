#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client_fd;
    struct sockaddr_in server_addr; // ← LÍNEA CORREGIDA
    char buffer[1024];
    socklen_t addr_len = sizeof(server_addr);

    // 1. Crear socket UDP
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0)
    {
        std::cerr << "Error al crear socket" << std::endl;
        return 1;
    }

    // 2. Configurar dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // 3. Enviar mensaje "PING"
    std::string message = "PING";
    sendto(client_fd, message.c_str(), message.size(), 0,
           (struct sockaddr *)&server_addr, addr_len);
    std::cout << "Enviado PING al servidor" << std::endl;

    // 4. Recibir respuesta
    memset(buffer, 0, sizeof(buffer));
    int n = recvfrom(client_fd, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&server_addr, &addr_len);

    if (n > 0)
    {
        std::cout << "Respuesta del servidor: " << buffer << std::endl;
    }

    close(client_fd);
    return 0;
}