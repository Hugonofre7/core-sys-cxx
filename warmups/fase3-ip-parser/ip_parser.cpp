#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Función para validar una dirección IPv4
bool isValidIPv4(const std::string &ip)
{
    // 1. Verificar que no esté vacía
    if (ip.empty())
        return false;

    // 2. Contar puntos
    int dotCount = 0;
    for (char c : ip)
    {
        if (c == '.')
            dotCount++;
    }
    if (dotCount != 3)
        return false;

    // 3. Dividir en partes usando stringstream
    std::stringstream ss(ip);
    std::string part;
    std::vector<std::string> parts;

    while (std::getline(ss, part, '.'))
    {
        parts.push_back(part);
    }

    // 4. Verificar que tengamos exactamente 4 partes
    if (parts.size() != 4)
        return false;

    // 5. Validar cada parte
    for (const auto &p : parts)
    {
        // Verificar que no esté vacía
        if (p.empty())
            return false;

        // Verificar leading zeros (ej: "01" es inválido, excepto "0")
        if (p.size() > 1 && p[0] == '0')
            return false;

        // Verificar que todos sean dígitos
        for (char c : p)
        {
            if (c < '0' || c > '9')
                return false;
        }

        // Convertir a número
        int num = std::stoi(p);

        // Verificar rango
        if (num < 0 || num > 255)
            return false;
    }

    return true;
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