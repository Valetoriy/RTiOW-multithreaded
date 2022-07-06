#pragma once

#include "Vec3.hpp"

class Ray {
   public:
    constexpr auto origin() const { return orig; }
    constexpr auto direction() const { return dir; }

    constexpr auto at(const double &t) const { return orig + t * dir; }

   public:
    Point3 orig;
    Vec3 dir;
};
