#include "Vec3.hpp"

auto Vec3::x() const -> double { return e[0]; }
auto Vec3::y() const -> double { return e[1]; }
auto Vec3::z() const -> double { return e[2]; }

auto Vec3::length_squared() const -> double {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

auto Vec3::length() const -> double { return std::sqrt(length_squared()); }

auto Vec3::near_zero() const -> bool {
    const auto s{1e-8};
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) &&
           (std::fabs(e[2]) < s);
}

auto Vec3::operator[](const size_t &i) const -> double { return e[i]; }
auto Vec3::operator[](const size_t &i) -> double & { return e[i]; }

auto Vec3::operator-() const -> Vec3 { return {-e[0], -e[1], -e[2]}; }

auto Vec3::operator+=(const Vec3 &other) -> Vec3 & {
    e[0] += other.e[0];
    e[1] += other.e[1];
    e[2] += other.e[2];
    return *this;
}

auto Vec3::operator*=(const double &t) -> Vec3 & {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

auto Vec3::operator/=(const double &t) -> Vec3 & { return *this *= 1 / t; }

auto operator<<(std::ostream &out, const Vec3 &other) -> std::ostream & {
    return out << other.e[0] << ' ' << other.e[1] << ' ' << other.e[2];
}

auto operator+(const Vec3 &v1, const Vec3 &v2) -> Vec3 {
    return {v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]};
}

auto operator-(const Vec3 &v1, const Vec3 &v2) -> Vec3 {
    return {v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]};
}

auto operator*(const Vec3 &v1, const Vec3 &v2) -> Vec3 {
    return {v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]};
}

auto operator*(const double &t, const Vec3 &v) -> Vec3 {
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

auto operator*(const Vec3 &v, const double &t) -> Vec3 { return t * v; }

auto operator/(const Vec3 &v, const double &t) -> Vec3 { return (1 / t) * v; }

auto dot(const Vec3 &v1, const Vec3 &v2) -> double {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

auto cross(const Vec3 &v1, const Vec3 &v2) -> Vec3 {
    return {v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
            v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
            v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]};
}

auto unit_vector(const Vec3 &v) -> Vec3 { return v / v.length(); }

auto reflect(const Vec3 &v, const Vec3 &n) -> Vec3 {
    return v - 2 * dot(v, n) * n;
}

auto refract(const Vec3 &uv, const Vec3 &n, const double &etai_over_etap)
    -> Vec3 {
    auto cos_theta{std::fmin(dot(-uv, n), 1.0)};
    auto r_out_perp{etai_over_etap * (uv + cos_theta * n)};
    auto r_out_parr{-std::sqrt(std::fabs(1 - r_out_perp.length_squared())) * n};

    return r_out_perp + r_out_parr;
}
