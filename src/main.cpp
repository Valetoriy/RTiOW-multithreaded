#include <fmt/format.h>

#include <iostream>

#include "Camera.hpp"
#include "Color.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "rtweekend.hpp"

constexpr auto ray_color(const Ray &r, const HittableList &world) {
    hit_record rec;
    if (world.hit(r, 0, std::numeric_limits<double>::infinity(), rec))
        return 0.5 * (rec.normal + Color{1, 1, 1});

    auto unit_direction{unit_vector(r.direction())};
    auto t = 0.5 * (unit_direction.y() + 1.0);

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
    constexpr auto samples_per_pixel{100};

    // Мир
    HittableList world;
    world.objects.push_back(std::make_shared<Sphere>(Point3{0, 0, -1}, 0.5));
    world.objects.push_back(
        std::make_shared<Sphere>(Point3{0, -100.5, -1}, 100));

    // Камера
    Camera cam;

    // Рендеринг
    fmt::print("P3\n{} {}\n255\n", image_width, image_height);

    for (int i{image_height - 1}; i >= 0; --i) {
        std::cerr << fmt::format("\rОсталось скан-линий: {} ", i) << std::flush;
        for (int j{}; j < image_width; ++j) {
            Color pixel_color{0, 0, 0};
            for (int s{}; s < samples_per_pixel; ++s) {
                auto u{(j + random_double()) / (image_width - 1)};
                auto v{(i + random_double()) / (image_height - 1)};
                Ray r{cam.get_ray(u, v)};
                pixel_color += ray_color(r, world);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nГотово.\n";

    return 0;
}
