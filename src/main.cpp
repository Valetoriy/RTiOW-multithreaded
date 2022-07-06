#include <fmt/format.h>

#include <iostream>

#include "Color.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

constexpr auto hit_sphere(const Point3 &center, const double &radius,
                          const Ray &r) {
    // r^2 = (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2
    // P - точка на поверхности сферы; вектор P - C в || = r
    // (P - C)^2 = (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2
    // => (P - C)^2 = r^2 => (A + tb - C)^2 = r^2
    // => t^2 * b . b + 2 * t * b . (A - C) + (A - C) . (A - C) - r^2 = 0
    // ^^ - квадратное уравнение
    auto AmC{r.origin() - center};
    auto a{dot(r.direction(), r.direction())};
    auto b{2 * dot(r.direction(), AmC)};
    auto c{dot(AmC, AmC) - radius * radius};

    return (b * b - 4 * a * c) >= 0;
}

constexpr auto ray_color(const Ray &r) {
    if (hit_sphere({0, 0, -1}, 0.5, r)) return Color{1.0, 0, 0};

    auto unit_direction{unit_vector(r.direction())};
    auto t{0.5 * (unit_direction.y() + 1.0)};

    // (1 - t) * начЗначение + t * конЗначение
    return (1.0 - t) * Color{1.0, 1.0, 1.0} + t * Color{0.5, 0.7, 1.0};
    // <=> std::lerp (начЗначение + t * (конЗначение - начЗначение)
    // return Color{1.0, 1.0, 1.0} + t * (Color{1.0, 0, 0} -
    // Color{1.0, 1.0, 1.0});
}

auto main() -> int {
    // Изображение
    constexpr auto aspect_raio{16.0 / 9.0};
    constexpr auto image_width{400};
    constexpr auto image_height{static_cast<int>(image_width / aspect_raio)};

    // Камера
    constexpr auto viewport_height{2.0};
    constexpr auto viewport_width{aspect_raio * viewport_height};
    constexpr auto focal_length{1.0};

    constexpr Point3 origin{0, 0, 0};
    constexpr Vec3 horizontal{viewport_width, 0, 0};
    constexpr Vec3 vertical{0, viewport_height, 0};
    constexpr auto lower_left_corner{origin - horizontal / 2 - vertical / 2 -
                                     Vec3{0, 0, focal_length}};

    // Рендеринг
    fmt::print("P3\n{} {}\n255\n", image_width, image_height);

    for (int i{image_height - 1}; i >= 0; --i) {
        std::cerr << fmt::format("\rОсталось скан-линий: {} ", i) << std::flush;
        for (int j{}; j < image_width; ++j) {
            auto u{double(j) / (image_width - 1)};
            auto v{double(i) / (image_height - 1)};
            Ray r{origin,
                  lower_left_corner + u * horizontal + v * vertical - origin};
            auto pixel_color{ray_color(r)};
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nГотово.\n";

    return 0;
}
