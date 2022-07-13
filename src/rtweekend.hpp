#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Часто используемые заголовочные файлы
#include "Ray.hpp"
#include "Vec3.hpp"

// Полезные функции
auto degrees_to_radians(const double &degrees) -> double;

auto random_double() -> double;

auto random_double(const double &min, const double &max) -> double;

auto random_vec3() -> Vec3;

auto random_vec3(const double &min, const double &max) -> Vec3;

auto random_in_unit_sphere() -> Vec3;

auto random_in_unit_disk() -> Vec3;

auto random_unit_vector() -> Vec3;

auto random_in_hemisphere(const Vec3 &normal) -> Vec3;

auto clamp(const double &x, const double &min, const double &max) -> double;
