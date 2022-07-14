#pragma once

#include <vector>

#include "HittableList.hpp"
#include "rtweekend.hpp"

class App {
   public:
    App(const double &a_r, const int &i_w, const int &s_p_p, const int &m_d);
    ~App();

    auto exec() -> void;

   private:
    auto random_scene() -> HittableList;

    auto ray_color(const Ray &r, const HittableList &world, const int &depth)
        -> Color;

   private:
    double aspect_raio;
    int image_width;
    int image_height;
    int samples_per_pixel;
    int max_depth;
    std::vector<Color> buffer;
    HittableList world;
};
