#include "Ray.hpp"

auto Ray::origin() const -> Point3 { return orig; }

auto Ray::direction() const -> Vec3 { return dir; }

auto Ray::at(const double &t) const -> Point3 { return orig + t * dir; }
