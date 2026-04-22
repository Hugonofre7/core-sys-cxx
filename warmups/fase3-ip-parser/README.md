# IP Parser

Ejercicio de calentamiento de la **Fase 3: Redes y Sistemas Distribuidos**.

## 📌 Objetivo

Implementar un validador de direcciones **IPv4** que verifique:
- Formato correcto (4 números separados por puntos)
- Rango válido (0-255 por cada octeto)
- Sin leading zeros (ej: `01` es inválido)
- Solo dígitos (sin letras ni caracteres especiales)

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| `std::stringstream` | Dividir string por delimitador (`.`) |
| `std::getline` | Extraer partes de un stream |
| Validación de dígitos | `c >= '0' && c <= '9'` |
| Leading zeros | `p.size() > 1 && p[0] == '0'` |
| Conversión string → int | `std::stoi()` |

## 🚀 Cómo compilar y ejecutar

```bash
g++ ip_parser.cpp -o ip_parser
./ip_parser