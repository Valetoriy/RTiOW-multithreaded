#include "Material.hpp"

Lambertian::Lambertian(const Color &a) : albedo{a} {}

auto Lambertian::scatter([[maybe_unused]] const Ray &r_in,
                         const hit_record &rec, Color &attenuation,
                         Ray &scattered) const -> bool {
    auto scatter_direction{rec.normal + random_unit_vector()};
    if (scatter_direction.near_zero()) scatter_direction = rec.normal;

    scattered = Ray{rec.P, scatter_direction};
    attenuation = albedo;

    return true;
}

Metal::Metal(const Color &a, const double &f) : albedo{a}, fuzz{f} {}

auto Metal::scatter(const Ray &r_in, const hit_record &rec, Color &attenuation,
                    Ray &scattered) const -> bool {
    auto reflected{reflect(unit_vector(r_in.direction()), rec.normal)};
    scattered = Ray{rec.P, reflected + fuzz * random_in_unit_sphere()};
    attenuation = albedo;

    return dot(scattered.direction(), rec.normal) > 0;
}

Dielectric::Dielectric(const double &ior) : index_of_refraction{ior} {}

auto Dielectric::scatter(const Ray &r_in, const hit_record &rec,
                         Color &attenuation, Ray &scattered) const -> bool {
    // Стекло не поглощает лучи
    attenuation = {1.0, 1.0, 1.0};
    auto refraction_ratio{rec.front_face ? 1.0 / index_of_refraction
                                         : index_of_refraction};

    auto unit_direction{unit_vector(r_in.direction())};
    auto cos_theta{std::fmin(dot(-unit_direction, rec.normal), 1.0)};
    auto sin_theta{std::sqrt(1.0 - cos_theta * cos_theta)};

    Vec3 direction;
    if (refraction_ratio * sin_theta > 1 ||
        reflectance(cos_theta, refraction_ratio) >
            random_double())  // Если луч не может приломиться
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);
    scattered = {rec.P, direction};

    return true;
}

auto Dielectric::reflectance(const double &cosine, const double &ref_idx)
    -> double {
    auto R0{(1 - ref_idx) / (1 + ref_idx)};
    R0 *= R0;

    return R0 + (1 - R0) * std::pow(1 - cosine, 5);
}
