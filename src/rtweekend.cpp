#include "rtweekend.hpp"

auto degrees_to_radians(const double &degrees) -> double {
    return degrees * std::numbers::pi / 180;
}

auto random_double() -> double {
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    static std::uniform_real_distribution dist{0.0, 1.0};

    return dist(gen);
}

auto random_double(const double &min, const double &max) -> double {
    return std::lerp(min, max, random_double());
}

auto random_vec3() -> Vec3 {
    return {random_double(), random_double(), random_double()};
}

auto random_vec3(const double &min, const double &max) -> Vec3 {
    return {random_double(min, max), random_double(min, max),
            random_double(min, max)};
}

auto random_in_unit_sphere() -> Vec3 {
    while (true) {
        auto p{random_vec3(-1, 1)};
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

auto random_in_unit_disk() -> Vec3 {
    while (true) {
        Vec3 p{random_double(-1, 1), random_double(-1, 1), 0};
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

auto random_unit_vector() -> Vec3 {
    return unit_vector(random_in_unit_sphere());
}

auto random_in_hemisphere(const Vec3 &normal) -> Vec3 {
    auto in_unit_sphere{random_in_unit_sphere()};
    if (dot(in_unit_sphere, normal) > 0)
        return in_unit_sphere;  // В одном полушарии с нормалью
    else
        return -in_unit_sphere;  // В разных полушариях с нормалью
}

auto clamp(const double &x, const double &min, const double &max) -> double {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
