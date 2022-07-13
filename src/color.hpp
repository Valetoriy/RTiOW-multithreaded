#pragma once

#include <iostream>

#include "rtweekend.hpp"

auto write_color(std::ostream &out, const Color &pixel_color,
                 const int &samples_per_pixel) -> void;
