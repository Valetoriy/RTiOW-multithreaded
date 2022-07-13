#include "Camera.hpp"

// TODO: перенести константы в аргументы конструктора
Camera::Camera(const Point3 &lookfrom, const Point3 &lookat, const Vec3 &vup,
               const double &fov, const double &aspect_ratio,
               const double &aperture, const double &focus_dist) {
    auto theta{degrees_to_radians(fov)};
    auto h{std::tan(theta / 2)};
    auto viewport_height{2.0 * h};
    auto viewport_width{aspect_ratio * viewport_height};

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

    lens_radius = aperture / 2;
}

auto Camera::get_ray(const double &s, const double &t) const -> Ray {
    auto rd{lens_radius * random_in_unit_disk()};
    auto offset{u * rd.x() + v * rd.y()};
    return {origin + offset, lower_left_corner + s * horizontal + t * vertical -
                                 origin - offset};
}
