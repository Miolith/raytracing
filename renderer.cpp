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

void Renderer::render()
{}

void Renderer::save(std::string filename)
{
    stbi_write_png(filename.c_str(), camera.screenWidth, camera.screenHeight, 3,
                   framebuffer.data(), camera.screenWidth * 3);
}