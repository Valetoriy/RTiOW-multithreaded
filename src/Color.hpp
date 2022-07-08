#pragma once

#include <iostream>

#include "Vec3.hpp"
#include "rtweekend.hpp"

inline auto write_color(std::ostream &out, const Color &pixel_color,
                        const int &samples_per_pixel) {
    auto r{pixel_color.x() / samples_per_pixel};
    auto g{pixel_color.y() / samples_per_pixel};
    auto b{pixel_color.z() / samples_per_pixel};
    out << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n';
}
