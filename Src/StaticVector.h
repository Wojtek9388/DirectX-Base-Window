#ifndef StaticVector_H
#define StaticVector_H

#include <cstddef>
#include <array>

/**
 * @brief allows the creation of statically sized vectors.
 */
namespace StaticVector
{
    template <typename T>
    struct Vector2 {
        T x;
        T y;

        // Constructors
        Vector2() : x(0), y(0) {}
        Vector2(T x, T y) : x(x), y(y) {}

        // Addition
        Vector2 operator+(const Vector2& other) const {
            return Vector2(x + other.x, y + other.y);
        }

        // Subtraction
        Vector2 operator-(const Vector2& other) const {
            return Vector2(x - other.x, y - other.y);
        }

        // Scalar multiply
        Vector2 operator*(T scalar) const {
            return Vector2(x * scalar, y * scalar);
        }

        // In-place versions
        Vector2& operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2& operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }
    };

    template <size_t N, typename T>
    struct Vector {
        std::array<T, N> data;

        // Default constructor
        Vector() {
            for (size_t i = 0; i < N; i++)
                data[i] = T{};
        }

        // Initializer-list constructor
        Vector(std::initializer_list<T> init) {
            size_t i = 0;
            for (T v : init) {
                if (i < N) data[i++] = v;
            }
            for (; i < N; i++) data[i] = T{};
        }

        // Index operator
        T& operator[](size_t i) { return data[i]; }
        const T& operator[](size_t i) const { return data[i]; }

        // Add
        Vector operator+(const Vector& other) const {
            Vector result;
            for (size_t i = 0; i < N; i++)
                result[i] = data[i] + other[i];
            return result;
        }

        // Scalar multiply
        Vector operator*(T scalar) const {
            Vector result;
            for (size_t i = 0; i < N; i++)
                result[i] = data[i] * scalar;
            return result;
        }
    };
};

#endif // StaticVector_H
