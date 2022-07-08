#pragma once

#include "rtweekend.hpp"

class Camera {
   public:
    // TODO: перенести константы в аргументы конструктора
    constexpr Camera() {
        auto aspect_ratio{16.0 / 9.0};
        auto viewport_height{2.0};
        auto viewport_width{aspect_ratio * viewport_height};
        auto focal_length{1.0};

        origin = {0, 0, 0};
        horizontal = {viewport_width, 0, 0};
        vertical = {0, viewport_height, 0};
        lower_left_corner =
            origin - horizontal / 2 - vertical / 2 - Point3{0, 0, focal_length};
    }

    auto get_ray(const double &u, const double &v) -> Ray {
        return {origin,
                lower_left_corner + u * horizontal + v * vertical - origin};
    }

   private:
    Point3 origin;
    Vec3 horizontal;
    Vec3 vertical;
    Point3 lower_left_corner;
};
