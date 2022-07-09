#pragma once

#include <iostream>

#include "Vec3.hpp"
#include "rtweekend.hpp"

inline auto write_color(std::ostream &out, const Color &pixel_color,
                        const int &samples_per_pixel) {
    auto r{pixel_color.x()};
    auto g{pixel_color.y()};
    auto b{pixel_color.z()};

    // Гамма-коррекция, гамма = 2
    auto scale{1.0 / samples_per_pixel};
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n';
}
