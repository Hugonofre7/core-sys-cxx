#pragma once

#include <vector>
#include <string>
#include <cstddef>
#include <functional>

namespace sys
{

    // Filtro Bloom - Estructura probabilística para pruebas de pertenencia
    template <typename T>
    class BloomFilter
    {
    public:
        // Constructor: tamaño del bitset y número de funciones hash
        BloomFilter(size_t size, size_t num_hashes);
        ~BloomFilter() = default;

        // No copiable
        BloomFilter(const BloomFilter &) = delete;
        BloomFilter &operator=(const BloomFilter &) = delete;

        // Insertar un elemento en el filtro
        void insert(const T &element);

        // Verificar si un elemento podría estar en el conjunto
        // Retorna true: posiblemente está (puede ser falso positivo)
        // Retorna false: definitivamente NO está
        bool contains(const T &element) const;

        // Estadísticas
        size_t size() const { return bits_.size(); }
        size_t hash_count() const { return num_hashes_; }
        double load_factor() const;

        // Limpiar el filtro
        void clear();

    private:
        // Aplicar las funciones hash al elemento
        std::vector<size_t> get_hash_indices(const T &element) const;

        std::vector<bool> bits_; // Bitset (más compacto que vector<char>)
        size_t num_hashes_;      // Número de funciones hash
        size_t inserted_count_;  // Cantidad de elementos insertados

        // Funciones hash combinadas
        size_t hash1(const T &element) const;
        size_t hash2(const T &element) const;
    };

} // namespace sys