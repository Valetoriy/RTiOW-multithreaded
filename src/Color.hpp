#pragma once

#include <iostream>

#include "Vec3.hpp"

inline auto write_color(std::ostream &out, const Color &pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}