#pragma once

#include <cmath>
#include <limits>
#include <memory>

// Полезные функции
inline double degrees_to_radians(const double &degrees) {
    return degrees * std::numbers::pi / 180;
}

// Часто используемые заголовочные файлы
#include "Ray.hpp"
#include "Vec3.hpp"
