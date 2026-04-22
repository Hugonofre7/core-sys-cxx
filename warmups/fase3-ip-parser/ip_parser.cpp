#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Función para validar una dirección IPv4
bool isValidIPv4(const std::string &ip)
{
    // TODO: Implementar validación
    // 1. Contar puntos (debe haber 3)
    // 2. Dividir en 4 partes
    // 3. Cada parte debe ser número entre 0 y 255
    // 4. Sin leading zeros (excepto "0")
    return false;
}

int main()
{
    std::vector<std::string> test_cases = {
        "192.168.1.1",     // Válida
        "255.255.255.255", // Válida
        "0.0.0.0",         // Válida
        "256.1.1.1",       // Inválida (>255)
        "192.168.1",       // Inválida (faltan partes)
        "192.168.1.1.1",   // Inválida (sobran partes)
        "192.168.01.1",    // Inválida (leading zero)
        "abc.def.ghi.jkl", // Inválida (no números)
        ""                 // Inválida (vacía)
    };

    for (const auto &ip : test_cases)
    {
        std::cout << "IP: " << ip << " -> ";
        if (isValidIPv4(ip))
        {
            std::cout << "VÁLIDA" << std::endl;
        }
        else
        {
            std::cout << "INVÁLIDA" << std::endl;
        }
    }

    return 0;
}
