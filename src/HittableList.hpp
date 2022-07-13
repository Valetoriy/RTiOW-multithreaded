#pragma once

#include <memory>
#include <vector>

#include "Hittable.hpp"

class HittableList : public Hittable {
   public:
    // Не constexpr из-за std::shared_ptr
    auto hit(const Ray &r, const double &t_min, const double &t_max,
             hit_record &rec) const -> bool override;

   public:
    std::vector<std::shared_ptr<Hittable>> objects;
};
