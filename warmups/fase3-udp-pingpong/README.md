# UDP Ping-Pong

Ejercicio de calentamiento de la **Fase 3: Redes y Sistemas Distribuidos**.

## 📌 Objetivo

Implementar una **comunicación UDP** entre un servidor y un cliente:
- El cliente envía "PING"
- El servidor recibe "PING" y responde "PONG"

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| `socket(AF_INET, SOCK_DGRAM, 0)` | Crear socket UDP |
| `sockaddr_in` | Estructura para direcciones IPv4 |
| `bind()` | Asignar puerto al servidor |
| `sendto()` | Enviar datagrama a una dirección |
| `recvfrom()` | Recibir datagrama (bloqueante) |
| `htons()` / `ntohs()` | Convertir a network byte order |
| `inet_ntoa()` / `inet_pton()` | Convertir IP texto ↔ binario |

## 🚀 Cómo compilar y ejecutar

### Compilación

```bash
g++ udp_server.cpp -o udp_server
g++ udp_client.cpp -o udp_client

Ejecución (necesitas 2 terminales)
Terminal 1 (Servidor):

bash
./udp_server
Terminal 2 (Cliente):

bash
./udp_client

📋 Ejemplo de ejecución
Servidor
Servidor UDP escuchando en puerto 8080...
Recibido de 127.0.0.1:54460 -> PING
Enviado PONG a 127.0.0.1:54460

Cliente
Enviado PING al servidor
Respuesta del servidor: PONG