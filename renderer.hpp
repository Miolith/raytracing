#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "camera.hpp"
#include "displayTools.hpp"
#include "scene.hpp"

class Renderer
{
private:
    Scene &scene;
    Camera &camera;
    pixelbuffer_t framebuffer;
    // ray
    struct Ray
    {
        linalg::vec3 origin;
        linalg::vec3 direction;
    } ray;

public:
    Renderer(Scene &scene, Camera &camera);
    ~Renderer();
    void render();
    void save(std::string filename);
    void drawSkybox();

};