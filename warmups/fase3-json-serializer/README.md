# JSON Serializer

Ejercicio de calentamiento de la **Fase 3: Redes y Sistemas Distribuidos**.

## 📌 Objetivo

Implementar **serialización y deserialización** de una estructura de datos (`SensorData`) a formato **JSON** y viceversa. Esto es fundamental para enviar datos por la red.

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| Serialización | Convertir struct → string (JSON) |
| Deserialización | Convertir string (JSON) → struct |
| `std::stringstream` | Construir strings de forma eficiente |
| `std::fixed` / `std::setprecision` | Controlar formato numérico |
| `std::string::find()` | Buscar substrings en JSON |
| `std::stoi()` / `std::stof()` | Convertir string a número |

## 🚀 Cómo compilar y ejecutar

g++ json_serializer.cpp -o json_serializer
./json_serializer

📋 Ejemplo de ejecución
text
JSON serializado: {"id":1,"temperature":23.50,"humidity":65.20,"active":true}
Datos restaurados:
  ID: 1
  Temperature: 23.5
  Humidity: 65.2
  Active: true

✅ Serialización/Deserialización correcta!