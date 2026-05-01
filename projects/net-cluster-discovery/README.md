# net-cluster-discovery - Gossip Protocol

Proyecto final de la **Fase 3: Redes y Sistemas Distribuidos**.

## 📌 Objetivo

Implementar un **protocolo Gossip** para descubrimiento de nodos en un cluster distribuido. Cada nodo:
- Mantiene una lista de miembros activos
- Periódicamente intercambia información con otros nodos
- Detecta nodos caídos sin servidor central

## 🧠 Conceptos Clave

| Concepto | Aplicación |
|----------|------------|
| **Gossip Protocol** | Propagación de información epidemiológica |
| **UDP Sockets** | Comunicación sin conexión entre nodos |
| **Eventual consistency** | Todos los nodos eventualmente tienen la misma vista |
| **Failure detection** | Detectar nodos caídos por timeout |
| **Membership list** | Lista distribuida de nodos activos |

## 🏗️ Estructura del Proyecto
net-cluster-discovery/
├── include/sys/
│ └── gossip_node.hpp ← Interfaz pública
├── src/
│ └── gossip_node.cpp ← Implementación
├── tests/
│ └── test_gossip.cpp ← Tests
└── CMakeLists.txt


## 🚀 Cómo compilar y ejecutar

### Compilación

```bash
cd /Users/hugonofre7/Projects/C++/core-sys-cxx/build
cmake --build .

./projects/net-cluster-discovery/test_gossip

📋 Ejemplo de ejecución
text
=== Gossip Protocol Tests ===
Tests coming soon...