#include "App.hpp"

#include <atomic>
#include <mutex>
#include <thread>

#include "Camera.hpp"
#include "Material.hpp"
#include "Sphere.hpp"
#include "color.hpp"

App::App(const double &a_r, const int &i_w, const int &s_p_p, const int &m_d)
    : aspect_raio{a_r},
      image_width{i_w},
      image_height{static_cast<int>(image_width / aspect_raio)},
      samples_per_pixel{s_p_p},
      max_depth{m_d},
      buffer{static_cast<size_t>(image_width * image_height), {1.0, 0, 0}},
      world{random_scene()} {}

App::~App() {
    for (const auto &pixel_color : buffer)
        write_color(std::cout, pixel_color, samples_per_pixel);
    std::cerr << "\nГотово.\n";
}

auto App::exec() -> void {
    // Камера
    Point3 lookfrom{13, 2, 3};
    Point3 lookat{0, 0, 0};
    auto dist_to_focus{10};
    Camera cam(lookfrom, lookat, {0, 1, 0}, 20, aspect_raio, 0.1,
               dist_to_focus);

    // "Полезная" информация
    std::cerr << "Количество пикселей: " << buffer.size() << std::endl;
    auto num_of_threads{static_cast<int>(std::jthread::hardware_concurrency())};
    std::cerr << "Количество потоков: " << num_of_threads << std::endl;

    // Рендеринг
    std::cout << "P3\n"
              << image_width << ' ' << image_height << '\n'
              << "255\n";

    std::vector<std::jthread> thread_pool;
    thread_pool.reserve(static_cast<size_t>(num_of_threads));

    std::atomic_int line_counter{};
    std::mutex m;
    auto thread_safe_print{[&]() {
        std::scoped_lock l{m};
        std::cerr << "\rОсталось скан-линий: "
                  << image_height - line_counter / num_of_threads << ' '
                  << std::flush;
    }};

    auto do_work{
        [&](std::vector<Color> &buf, const int &start_index, const int &width) {
            for (int i{image_height - 1}; i >= 0; --i) {
                for (int j{start_index}; j < start_index + width; ++j) {
                    Color pixel_color{0, 0, 0};
                    for (int s{}; s < samples_per_pixel; ++s) {
                        auto u{(j + random_double()) / (image_width - 1)};
                        auto v{(i + random_double()) / (image_height - 1)};
                        Ray r{cam.get_ray(u, v)};
                        pixel_color += ray_color(r, world, max_depth);
                    }
                    buf[static_cast<size_t>(j + (image_height - i - 1) *
                                                    image_width)] = pixel_color;
                }
                ++line_counter;
                thread_safe_print();
            }
        }};

    auto width_per_thread{image_width / num_of_threads};
    // Ширина изображения не всегда делится на кол-во потоков без остатка
    auto remaining_width{image_width % num_of_threads};
    if (remaining_width) ++width_per_thread;

    for (int i{}, current_pos{}; i < num_of_threads;
         ++i, current_pos += width_per_thread) {
        if (remaining_width)
            --remaining_width;
        else if (width_per_thread > image_width / num_of_threads)
            --width_per_thread;

        thread_pool.emplace_back(do_work, std::ref(buffer), current_pos,
                                 width_per_thread);
    }
}

auto App::ray_color(const Ray &r, const HittableList &world, const int &depth)
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

auto App::random_scene() -> HittableList {
    HittableList temp_world;

    auto ground_material{std::make_shared<Lambertian>(Color{0.5, 0.5, 0.5})};
    temp_world.objects.push_back(
        std::make_shared<Sphere>(Point3{0, -1000, 0}, 1000, ground_material));

    for (int a{-11}; a < 11; ++a) {
        for (int b{-11}; b < 11; ++b) {
            Point3 center{a + 0.9 * random_double(), 0.2,
                          b + 0.9 * random_double()};

            if ((center - Point3{4, 0.2, 0}).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;
                auto choose_mat{random_double()};

                if (choose_mat < 0.8) {
                    auto albedo{random_vec3() * random_vec3()};
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    temp_world.objects.push_back(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    auto albedo{random_vec3(0.5, 1)};
                    auto fuzz{random_double(0, 0.5)};
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    temp_world.objects.push_back(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    temp_world.objects.push_back(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1{std::make_shared<Dielectric>(1.5)};
    temp_world.objects.push_back(
        std::make_shared<Sphere>(Point3{0, 1, 0}, 1, material1));

    auto material2{std::make_shared<Lambertian>(Color{0.4, 0.2, 0.1})};
    temp_world.objects.push_back(
        std::make_shared<Sphere>(Point3{-4, 1, 0}, 1, material2));

    auto material3{std::make_shared<Metal>(Color{0.7, 0.6, 0.5}, 0)};
    temp_world.objects.push_back(
        std::make_shared<Sphere>(Point3{4, 1, 0}, 1, material3));

    return temp_world;
}
