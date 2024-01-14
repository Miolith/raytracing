#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "camera.hpp"
#include "displayTools.hpp"
#include "scene.hpp"

struct Ray
{
    linalg::vec3 origin;
    linalg::vec3 direction;
};

class Renderer
{
public:
    Scene &scene;
    Camera &camera;
    int max_depth = 50;
    int samples_per_pixel = 100;
    pixelbuffer_t framebuffer;

    Renderer(Scene &scene, Camera &camera);
    color_t rayColor(Ray ray, int max_depth, float &t_min);
    void render();
    void save(std::string filename);
};