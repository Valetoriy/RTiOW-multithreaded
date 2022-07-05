#include <fmt/format.h>

#include <iostream>

#include "Color.hpp"
#include "Vec3.hpp"

auto main() -> int {
    constexpr auto image_width{256};
    constexpr auto image_height{256};

    // P3 => использует ASCII
    // ширина высота
    // 255 => максимальное значение цвета
    // красный зелёный жёлтый X кол-во пикселей
    fmt::print("P3\n{} {}\n255\n", image_width, image_height);

    for (int i{}; i < image_height; ++i) {
        std::cerr << fmt::format("\rОсталось скан-линий: {} ", image_height - i)
                  << std::flush;
        for (int j{}; j < image_width; ++j) {
            Color pixel_color{
                0, (double(i) / image_height + double(j) / image_width) / 2, 0};
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nГотово.\n";

    return 0;
}
