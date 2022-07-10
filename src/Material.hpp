#pragma once

#include "Hittable.hpp"
#include "rtweekend.hpp"

class Material {
   public:
    virtual auto scatter(const Ray &r_in, const hit_record &rec,
                         Color &attenuation, Ray &scattered) const -> bool = 0;
};

class Lambertian : public Material {
   public:
    constexpr Lambertian(const Color &a) : albedo{a} {}
    virtual auto scatter([[maybe_unused]] const Ray &r_in,
                         const hit_record &rec, Color &attenuation,
                         Ray &scattered) const -> bool override {
        auto scatter_direction{rec.normal + random_unit_vector()};
        if (scatter_direction.near_zero()) scatter_direction = rec.normal;

        scattered = Ray{rec.P, scatter_direction};
        attenuation = albedo;

        return true;
    }

   public:
    Color albedo;
};

class Metal : public Material {
   public:
    constexpr Metal(const Color &a, const double &f) : albedo{a}, fuzz{f} {}

    virtual auto scatter(const Ray &r_in, const hit_record &rec,
                         Color &attenuation, Ray &scattered) const
        -> bool override {
        auto reflected{reflect(unit_vector(r_in.direction()), rec.normal)};
        scattered = Ray{rec.P, reflected + fuzz * random_in_unit_sphere()};
        attenuation = albedo;

        return dot(scattered.direction(), rec.normal) > 0;
    }

   public:
    Color albedo;
    double fuzz;
};

class Dielectric : public Material {
   public:
    Dielectric(const double &ior) : index_of_refraction{ior} {}

    virtual auto scatter(const Ray &r_in, const hit_record &rec,
                         Color &attenuation, Ray &scattered) const
        -> bool override {
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

   public:
    double index_of_refraction;

   private:
    // Аппроксимация Шлика
    static auto reflectance(const double &cosine, const double &ref_idx)
        -> double {
        auto R0{(1 - ref_idx) / (1 + ref_idx)};
        R0 *= R0;

        return R0 + (1 - R0) * std::pow(1 - cosine, 5);
    }
};
