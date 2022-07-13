#pragma once

#include "Hittable.hpp"
#include "Vec3.hpp"

class Sphere : public Hittable {
   public:
    Sphere() = default;
    Sphere(const Point3 &c, const double &r,
           const std::shared_ptr<Material> &m);

    auto hit(const Ray &r, const double &t_min, const double &t_max,
             hit_record &rec) const -> bool override;

   public:
    Point3 center;
    double radius;
    std::shared_ptr<Material> mat_ptr;
};
