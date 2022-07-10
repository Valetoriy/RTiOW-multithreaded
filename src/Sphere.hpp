#pragma once

#include "Hittable.hpp"
#include "Vec3.hpp"

class Sphere : public Hittable {
   public:
    constexpr Sphere() = default;
    Sphere(const Point3 &c, const double &r, const std::shared_ptr<Material> &m)
        : center{c}, radius{r}, mat_ptr{m} {}
    constexpr virtual auto hit(const Ray &r, const double &t_min,
                               const double &t_max, hit_record &rec) const
        -> bool override;

   public:
    Point3 center;
    double radius;
    std::shared_ptr<Material> mat_ptr;
};

constexpr inline auto Sphere::hit(const Ray &r, const double &t_min,
                                  const double &t_max, hit_record &rec) const
    -> bool {
    // r^2 = (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2
    // P - точка на поверхности сферы; вектор P - C в || = r
    // (P - C)^2 = (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2
    // => (P - C)^2 = r^2 => (A + tb - C)^2 = r^2
    // => t^2 * b . b + 2 * t * b . (A - C) + (A - C) . (A - C) - r^2 = 0
    // ^^ - квадратное уравнение

    // . вектора на себя = его длинна ^2
    // т.к. b - чётное => b = 2 * h; x12 = (- h +- sqrt(h^2 - a * c)) / a
    auto AmC{r.origin() - center};
    auto a{r.direction().length_squared()};
    auto half_b{dot(r.direction(), AmC)};
    auto c{AmC.length_squared() - radius * radius};

    auto discriminant{half_b * half_b - a * c};
    if (discriminant < 0) return false;
    auto sqrtd{std::sqrt(discriminant)};

    // Находим ближайший корень в промежутке t_min <= t <= t_max
    auto root{(-half_b - sqrtd) / a};
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max) return false;
    }

    rec.t = root;
    rec.P = r.at(rec.t);
    // <=> unit_vector()
    auto outward_normal = (rec.P - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}
