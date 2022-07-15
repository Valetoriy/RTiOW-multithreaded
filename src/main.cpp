#include <iostream>

#include "App.hpp"

auto main() -> int {
    constexpr auto aspect_ratio{16.0 / 9.0};
    constexpr auto image_width{400};
    constexpr auto samples_per_pixel{50};
    constexpr auto max_depth{50};
    App app{aspect_ratio, image_width, samples_per_pixel, max_depth};
    app.exec();

    return 0;
}
