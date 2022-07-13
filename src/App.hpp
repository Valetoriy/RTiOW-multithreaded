#pragma once

#include "Camera.hpp"
#include "HittableList.hpp"
#include "Material.hpp"
#include "Sphere.hpp"
#include "color.hpp"
#include "rtweekend.hpp"

class App {
   public:
    App();

    auto exec() -> void;

   private:
    auto random_scene() -> HittableList;

    auto ray_color(const Ray &r, const HittableList &world, const int &depth)
        -> Color;

   private:
    HittableList world;
};
