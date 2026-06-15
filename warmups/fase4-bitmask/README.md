# Bitmask Manager

Ejercicio de calentamiento de la **Fase 4: STL y Rendimiento**.

## 📌 Objetivo

Aprender a usar **operadores de bits** (`&`, `|`, `^`, `~`, `<<`) para gestionar flags y permisos de forma eficiente en memoria.

## 🧠 Conceptos Clave

| Operador | Nombre | Uso |
|----------|--------|-----|
| `<<` | Shift left | Crear máscaras (`1 << n`) |
| `\|` | OR | Activar bits (agregar permisos) |
| `&` | AND | Verificar bits (tiene permiso) |
| `~` | NOT | Desactivar bits (quitar permisos) |
| `^` | XOR | Alternar bits (toggle) |

## 🚀 Cómo compilar y ejecutar

```bash
g++ bitmask_manager.cpp -o bitmask_manager
./bitmask_manager
```

## 📋 Ejemplo de ejecución
```
=== BITMASK MANAGER ===

Estado inicial:
Permisos: - - - - - | Valor binario: 00000000

Agregando permisos READ y EXECUTE...
Permisos: R - X - - | Valor binario: 00000101

Agregando permiso WRITE...
Permisos: R W X - - | Valor binario: 00000111

Quitando permiso EXECUTE...
Permisos: R W - - - | Valor binario: 00000011

Alternando permiso DELETE (agregar)...
Permisos: R W - D - | Valor binario: 00001011

Alternando permiso DELETE (quitar)...
Permisos: R W - - - | Valor binario: 00000011

Verificando permisos:
  Tiene READ? Sí
  Tiene WRITE? Sí
  Tiene EXECUTE? No
  Tiene ADMIN? No
  ```
  