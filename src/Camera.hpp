#pragma once

#include "rtweekend.hpp"

class Camera {
   public:
    Camera(const Point3 &lookfrom, const Point3 &lookat, const Vec3 &vup,
           const double &fov, const double &aspect_ratio,
           const double &aperture, const double &focus_dist);

    auto get_ray(const double &s, const double &t) const -> Ray;

   private:
    Point3 origin;
    Vec3 horizontal;
    Vec3 vertical;
    Point3 lower_left_corner;
    Vec3 u, v, w;
    double lens_radius;
};
