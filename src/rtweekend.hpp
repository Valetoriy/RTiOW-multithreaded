#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Часто используемые заголовочные файлы
#include "Ray.hpp"
#include "Vec3.hpp"

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

inline auto random_vec3() -> Vec3 {
    return {random_double(), random_double(), random_double()};
}

inline auto random_vec3(const double &min, const double &max) -> Vec3 {
    return {random_double(min, max), random_double(min, max),
            random_double(min, max)};
}

inline auto random_in_unit_sphere() {
    while (true) {
        auto p{random_vec3(-1, 1)};
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline auto random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline auto random_in_hemisphere(const Vec3 &normal) {
    auto in_unit_sphere{random_in_unit_sphere()};
    if (dot(in_unit_sphere, normal) > 0)
        return in_unit_sphere;  // В одном полушарии с нормалью
    else
        return -in_unit_sphere;  // В разных полушариях с нормалью
}

inline auto clamp(const double &x, const double &min, const double &max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
