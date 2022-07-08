#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Полезные функции
constexpr inline double degrees_to_radians(const double &degrees) {
    return degrees * std::numbers::pi / 180;
}

inline auto random_double() {
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    static std::uniform_real_distribution dist{0.0, 1.0};

    return dist(gen);
}

inline auto random_double(const double &min, const double &max) {
    return std::lerp(min, max, random_double());
}

inline auto clamp(const double &x, const double &min, const double &max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Часто используемые заголовочные файлы
#include "Ray.hpp"
#include "Vec3.hpp"
