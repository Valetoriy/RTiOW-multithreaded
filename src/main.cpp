#include <fmt/format.h>

#include <iostream>

#include "Camera.hpp"
#include "Color.hpp"
#include "HittableList.hpp"
#include "Material.hpp"
#include "Sphere.hpp"
#include "rtweekend.hpp"

auto ray_color(const Ray &r, const HittableList &world, const int &depth)
    -> Color {
    if (depth <= 0) return {0, 0, 0};

    hit_record rec;
    // При t_min = 0 лучи часто натыкаются на тот же объект, от которого
    // отразились
    if (world.hit(r, 0.001, std::numeric_limits<double>::infinity(), rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return {0, 0, 0};
    }

    auto unit_direction{unit_vector(r.direction())};
    auto t = 0.5 * (unit_direction.y() + 1.0);

    // (1 - t) * начЗначение + t * конЗначение
    return (1.0 - t) * Color{1.0, 1.0, 1.0} + t * Color{0.5, 0.7, 1.0};
    // <=> std::lerp (начЗначение + t * (конЗначение - начЗначение)
    // return Color{1.0, 1.0, 1.0} + t * (Color{1.0, 0, 0} -
    // Color{1.0, 1.0, 1.0});
}

auto random_scene() {
    HittableList world;

    auto ground_material{std::make_shared<Lambertian>(Color{0.5, 0.5, 0.5})};
    world.objects.push_back(
        std::make_shared<Sphere>(Point3{0, -1000, 0}, 1000, ground_material));

    for (int a{-11}; a < 11; ++a) {
        for (int b{-11}; b < 11; ++b) {
            auto choose_mat{random_double()};
            Point3 center{a + 0.9 * random_double(), 0.2,
                          b + 0.9 * random_double()};

            if ((center - Point3{4, 0.2, 0}).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    auto albedo{random_vec3() * random_vec3()};
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.objects.push_back(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    auto albedo{random_vec3(0.5, 1)};
                    auto fuzz{random_double(0, 0.5)};
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.objects.push_back(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.objects.push_back(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1{std::make_shared<Dielectric>(1.5)};
    world.objects.push_back(
        std::make_shared<Sphere>(Point3{0, 1, 0}, 1, material1));

    auto material2{std::make_shared<Lambertian>(Color{0.4, 0.2, 0.1})};
    world.objects.push_back(
        std::make_shared<Sphere>(Point3{-4, 1, 0}, 1, material2));

    auto material3{std::make_shared<Metal>(Color{0.7, 0.6, 0.5}, 0)};
    world.objects.push_back(
        std::make_shared<Sphere>(Point3{4, 1, 0}, 1, material3));

    return world;
}

auto main() -> int {
    // Изображение
    constexpr auto aspect_raio{16.0 / 9.0};
    constexpr auto image_width{400};
    constexpr auto image_height{static_cast<int>(image_width / aspect_raio)};
    constexpr auto samples_per_pixel{100};
    constexpr auto max_depth{50};

    // Мир
    auto world{random_scene()};

    // Камера
    Point3 lookfrom{13, 2, 3};
    Point3 lookat{0, 0, 0};
    auto dist_to_focus{10};
    Camera cam(lookfrom, lookat, {0, 1, 0}, 20, aspect_raio, 0.1,
               dist_to_focus);

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
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nГотово.\n";

    return 0;
}
