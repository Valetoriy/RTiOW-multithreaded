#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
   public:
    auto x() const { return e[0]; }
    auto y() const { return e[1]; }
    auto z() const { return e[2]; }

    auto length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    auto length() const { return std::sqrt(length_squared()); }

    auto operator[](const size_t &i) const { return e[i]; }
    auto &operator[](const size_t &i) { return e[i]; }

    auto operator-() -> Vec3 const { return {-e[0], -e[1], -e[2]}; }

    auto &operator+=(const Vec3 &other) {
        e[0] += other.e[0];
        e[1] += other.e[1];
        e[2] += other.e[2];
        return *this;
    }

    auto &operator*=(const double &t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    auto &operator/=(const double &t) { return *this *= 1 / t; }

   public:
    double e[3];
};

inline auto &operator<<(std::ostream &out, const Vec3 &other) {
    return out << other.e[0] << ' ' << other.e[1] << ' ' << other.e[2];
}

inline auto operator+(const Vec3 &v1, const Vec3 &v2) -> Vec3 {
    return {v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]};
}

inline auto operator-(const Vec3 &v1, const Vec3 &v2) -> Vec3 {
    return {v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]};
}

inline auto operator*(const Vec3 &v1, const Vec3 &v2) -> Vec3 {
    return {v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]};
}

inline auto operator*(const double &t, const Vec3 &v) -> Vec3 {
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline auto operator*(const Vec3 &v, const double &t) { return t * v; }

inline auto operator/(const Vec3 &v, const double &t) { return (1 / t) * v; }

inline auto dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] + v2.e[2];
}

inline auto cross(const Vec3 &v1, const Vec3 &v2) -> Vec3 {
    return {v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
            v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
            v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]};
}

inline auto unit_vector(const Vec3 &v) { return v / v.length(); }

using Point3 = Vec3;
using Color = Vec3;
