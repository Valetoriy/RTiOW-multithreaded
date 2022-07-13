#pragma once

#include "rtweekend.hpp"

// Для избежания цикла зависимостей
class Material;

struct hit_record {
    Point3 P;
    Vec3 normal;
    std::shared_ptr<Material> mat_ptr;
    double t;
    bool front_face;

    auto set_face_normal(const Ray &r, const Vec3 &outward_normal) -> void;
};

// TODO: CRTP
class Hittable {
   public:
    virtual auto hit(const Ray &r, const double &t_min, const double &t_max,
                     hit_record &rec) const -> bool = 0;
};
