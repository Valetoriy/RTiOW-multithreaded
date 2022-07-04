#include <fmt/format.h>

#include <iostream>

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
            auto g{float(i) / image_height + float(j) / image_width};

            fmt::print("0 {} 0\n", static_cast<int>(g * 127.999));
        }
    }

    std::cerr << "\nГотово.\n";

    return 0;
}
