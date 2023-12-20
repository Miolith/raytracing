#include <iostream>

#include "renderer.hpp"
#include "camera.hpp"
#include "scene.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Renderer::Renderer(Scene &scene, Camera &camera)
    : scene(scene)
    , camera(camera)
    , framebuffer(camera.screenHeight, camera.screenWidth)
{}

Renderer::~Renderer()
{}

void Renderer::drawSkybox()
{
    for (int y = 0; y < framebuffer.height; y++)
    {
        for (int x = 0; x < framebuffer.width; x++)
        {
            float gradient = 1.0f - FLOAT(y) / FLOAT(framebuffer.height);
            framebuffer.set(x, y, color_t{0.2f * gradient, 0.4f * gradient, 0.8f});
        }
    }
}

void Renderer::render()
{
    drawSkybox();
}

void Renderer::save(std::string filename)
{
    stbi_write_jpg(filename.c_str(), camera.screenWidth, camera.screenHeight, 3,
                   framebuffer.data(), 100);
}