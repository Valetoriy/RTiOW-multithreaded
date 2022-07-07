#pragma once

#include <memory>
#include <vector>

#include "Hittable.hpp"

class HittableList : public Hittable {
   public:
    virtual auto hit(const Ray &r, const double &t_min, const double &t_max,
                     hit_record &rec) const -> bool override;

   public:
    // TODO?: переписать в std::array + std::unique_ptr
    std::vector<std::shared_ptr<Hittable>> objects;
};

inline auto HittableList::hit(const Ray &r, const double &t_min,
                              const double &t_max, hit_record &rec) const
    -> bool {
    hit_record temp_rec;
    auto hit_anything{false};
    auto closest_so_far{t_max};

    for (const auto &object : objects)
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }

    return hit_anything;
}
