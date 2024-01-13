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
private:
    Scene &scene;
    Camera &camera;
    int max_depth = 50;
    int samples_per_pixel = 100;
    pixelbuffer_t framebuffer;

public:
    Renderer(Scene &scene, Camera &camera);
    Renderer(Scene &scene, Camera &camera, int max_depth,
             int samples_per_pixel);
    color_t rayColor(Ray ray, int depth);
    void render();
    void save(std::string filename);
};