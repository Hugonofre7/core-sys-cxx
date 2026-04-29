#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

// Estructura de ejemplo para serializar
struct SensorData
{
    int id;
    float temperature;
    float humidity;
    bool active;
};

// Serializar SensorData a string formato JSON
std::string serialize(const SensorData &data)
{
    std::stringstream ss;
    ss << "{";
    ss << "\"id\":" << data.id << ",";
    ss << "\"temperature\":" << std::fixed << std::setprecision(2) << data.temperature << ",";
    ss << "\"humidity\":" << std::fixed << std::setprecision(2) << data.humidity << ",";
    ss << "\"active\":" << (data.active ? "true" : "false");
    ss << "}";
    return ss.str();
}

// Deserializar string JSON a SensorData (versión simple)
SensorData deserialize(const std::string &json)
{
    SensorData data = {0, 0.0f, 0.0f, false};

    // Buscar "id":
    size_t id_pos = json.find("\"id\":");
    if (id_pos != std::string::npos)
    {
        data.id = std::stoi(json.substr(id_pos + 5));
    }

    // Buscar "temperature":
    size_t temp_pos = json.find("\"temperature\":");
    if (temp_pos != std::string::npos)
    {
        size_t start = temp_pos + 14;
        size_t end = json.find(",", start);
        if (end == std::string::npos)
            end = json.find("}", start);
        data.temperature = std::stof(json.substr(start, end - start));
    }

    // Buscar "humidity":
    size_t hum_pos = json.find("\"humidity\":");
    if (hum_pos != std::string::npos)
    {
        size_t start = hum_pos + 11;
        size_t end = json.find(",", start);
        if (end == std::string::npos)
            end = json.find("}", start);
        data.humidity = std::stof(json.substr(start, end - start));
    }

    // Buscar "active":
    size_t act_pos = json.find("\"active\":");
    if (act_pos != std::string::npos)
    {
        size_t start = act_pos + 9;
        data.active = json.substr(start, 4) == "true";
    }

    return data;
}

int main()
{
    // Crear datos de ejemplo
    SensorData original = {1, 23.5f, 65.2f, true};

    // Serializar
    std::string json = serialize(original);
    std::cout << "JSON serializado: " << json << std::endl;

    // Deserializar
    SensorData restored = deserialize(json);
    std::cout << "Datos restaurados: " << std::endl;
    std::cout << "  ID: " << restored.id << std::endl;
    std::cout << "  Temperature: " << restored.temperature << std::endl;
    std::cout << "  Humidity: " << restored.humidity << std::endl;
    std::cout << "  Active: " << (restored.active ? "true" : "false") << std::endl;

    // Verificar que los datos coincidan
    if (original.id == restored.id &&
        original.temperature == restored.temperature &&
        original.humidity == restored.humidity &&
        original.active == restored.active)
    {
        std::cout << "\n✅ Serialización/Deserialización correcta!" << std::endl;
    }
    else
    {
        std::cout << "\n❌ Error: los datos no coinciden" << std::endl;
    }

    return 0;
}