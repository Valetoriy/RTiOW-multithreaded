#pragma once

#include "rtweekend.hpp"

class Camera {
   public:
    // TODO: перенести константы в аргументы конструктора
    constexpr Camera(const Point3 &lookfrom, const Point3 &lookat,
                     const Vec3 &vup, const double &fov,
                     const double &aspect_ratio) {
        auto theta{degrees_to_radians(fov)};
        auto h{std::tan(theta / 2)};
        auto viewport_height{2.0 * h};
        auto viewport_width{aspect_ratio * viewport_height};

        auto w{unit_vector(lookfrom - lookat)};
        auto u{unit_vector(cross(vup, w))};
        auto v{cross(w, u)};

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
    }

    auto get_ray(const double &s, const double &t) -> Ray {
        return {origin,
                lower_left_corner + s * horizontal + t * vertical - origin};
    }

   private:
    Point3 origin;
    Vec3 horizontal;
    Vec3 vertical;
    Point3 lower_left_corner;
};
