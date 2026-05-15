#pragma once

#include <vector>
#include <string>
#include <cstddef>
#include <functional>
#include <cmath>
#include <algorithm>

namespace sys
{

    // Filtro Bloom - Estructura probabilística para pruebas de pertenencia
    template <typename T>
    class BloomFilter
    {
    public:
        // Constructor: tamaño del bitset y número de funciones hash
        BloomFilter(size_t size, size_t num_hashes)
            : bits_(size, false), num_hashes_(num_hashes), inserted_count_(0)
        {
        }

        ~BloomFilter() = default;

        // No copiable
        BloomFilter(const BloomFilter &) = delete;
        BloomFilter &operator=(const BloomFilter &) = delete;

        // Insertar un elemento
        void insert(const T &element)
        {
            auto indices = get_hash_indices(element);
            for (size_t idx : indices)
            {
                bits_[idx] = true;
            }
            inserted_count_++;
        }

        // Verificar si un elemento podría estar
        bool contains(const T &element) const
        {
            auto indices = get_hash_indices(element);
            for (size_t idx : indices)
            {
                if (!bits_[idx])
                {
                    return false; // Definitivamente NO está
                }
            }
            return true; // Posiblemente está
        }

        // Estadísticas
        size_t size() const { return bits_.size(); }
        size_t hash_count() const { return num_hashes_; }

        double load_factor() const
        {
            size_t bits_set = 0;
            for (bool b : bits_)
            {
                if (b)
                    bits_set++;
            }
            return static_cast<double>(bits_set) / bits_.size();
        }

        // Limpiar el filtro
        void clear()
        {
            std::fill(bits_.begin(), bits_.end(), false);
            inserted_count_ = 0;
        }

    private:
        // Función hash 1
        size_t hash1(const T &element) const
        {
            std::hash<T> hasher;
            return hasher(element);
        }

        // Función hash 2 (versión diferente)
        size_t hash2(const T &element) const
        {
            std::hash<T> hasher;
            return hasher(element) * 0x9e3779b9;
        }

        // Obtener índices para todas las funciones hash
        std::vector<size_t> get_hash_indices(const T &element) const
        {
            std::vector<size_t> indices;
            indices.reserve(num_hashes_);

            size_t h1 = hash1(element);
            size_t h2 = hash2(element);

            // Técnica de hash doble
            for (size_t i = 0; i < num_hashes_; i++)
            {
                size_t index = (h1 + i * h2) % bits_.size();
                indices.push_back(index);
            }

            return indices;
        }

        std::vector<bool> bits_;
        size_t num_hashes_;
        size_t inserted_count_;
    };

} // namespace sys