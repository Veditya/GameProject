#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <type_traits>

template <typename T>
class Random
{
public:
    T get(T x, T y)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        if constexpr (std::is_integral<T>::value)
        {
            std::uniform_int_distribution<T> dist(x, y);
            return dist(gen);
        }
        else if constexpr (std::is_floating_point<T>::value)
        {
            std::uniform_real_distribution<T> dist(x, y);
            return dist(gen);
        }
        else
        {
            static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                          "Random<T> only supports integral or floating point types.");
        }
    }
};

#endif