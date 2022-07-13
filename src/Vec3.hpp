#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
   public:
    auto x() const -> double;
    auto y() const -> double;
    auto z() const -> double;

    auto length_squared() const -> double;

    auto length() const -> double;

    auto near_zero() const -> bool;

    auto operator[](const size_t &i) const -> double;
    auto operator[](const size_t &i) -> double &;

    auto operator-() const -> Vec3;

    auto operator+=(const Vec3 &other) -> Vec3 &;

    auto operator*=(const double &t) -> Vec3 &;

    auto operator/=(const double &t) -> Vec3 &;

   public:
    double e[3];
};

auto operator<<(std::ostream &out, const Vec3 &other) -> std::ostream &;

auto operator+(const Vec3 &v1, const Vec3 &v2) -> Vec3;

auto operator-(const Vec3 &v1, const Vec3 &v2) -> Vec3;

auto operator*(const Vec3 &v1, const Vec3 &v2) -> Vec3;

auto operator*(const double &t, const Vec3 &v) -> Vec3;

auto operator*(const Vec3 &v, const double &t) -> Vec3;

auto operator/(const Vec3 &v, const double &t) -> Vec3;

auto dot(const Vec3 &v1, const Vec3 &v2) -> double;

auto cross(const Vec3 &v1, const Vec3 &v2) -> Vec3;

auto unit_vector(const Vec3 &v) -> Vec3;

auto reflect(const Vec3 &v, const Vec3 &n) -> Vec3;

auto refract(const Vec3 &uv, const Vec3 &n, const double &etai_over_etap)
    -> Vec3;

using Point3 = Vec3;
using Color = Vec3;
