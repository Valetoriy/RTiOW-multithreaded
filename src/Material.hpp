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
    explicit Lambertian(const Color &a);

    auto scatter(const Ray &r_in, const hit_record &rec, Color &attenuation,
                 Ray &scattered) const -> bool override;

   public:
    Color albedo;
};

class Metal : public Material {
   public:
    Metal(const Color &a, const double &f);

    auto scatter(const Ray &r_in, const hit_record &rec, Color &attenuation,
                 Ray &scattered) const -> bool override;

   public:
    Color albedo;
    double fuzz;
};

class Dielectric : public Material {
   public:
    explicit Dielectric(const double &ior);

    auto scatter(const Ray &r_in, const hit_record &rec, Color &attenuation,
                 Ray &scattered) const -> bool override;

   public:
    double index_of_refraction;

   private:
    // Аппроксимация Шлика
    static auto reflectance(const double &cosine, const double &ref_idx)
        -> double;
};
