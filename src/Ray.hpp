#pragma once

#include "Vec3.hpp"

class Ray {
   public:
    auto origin() const -> Point3;
    auto direction() const -> Vec3;

    auto at(const double &t) const -> Point3;

   public:
    Point3 orig;
    Vec3 dir;
};
