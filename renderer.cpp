#include <iostream>

#include "renderer.hpp"
#include "camera.hpp"
#include "scene.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Renderer::Renderer(Scene &scene, Camera &camera)
    : scene(scene)
    , camera(camera)
    , framebuffer(camera.screenWidth, camera.screenHeight)
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
            float gradient_x = 1.0f - FLOAT(x) / FLOAT(framebuffer.width);
            framebuffer.set(x, y, color_t{0.2f * gradient_x, 0.4f * gradient, 0.8f});
        }
    }
}

void Renderer::render()
{
    drawSkybox();
    auto aspect_ratio = FLOAT(camera.screenWidth) / FLOAT(camera.screenHeight);
    int image_width = camera.screenWidth;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = std::max(image_height, 1);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (FLOAT(image_width)/image_height);
    auto camera_center = linalg::vec3();

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = linalg::vec3(viewport_width, 0, 0);
    auto viewport_v = linalg::vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - linalg::vec3(0, 0, camera.focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5f;

    for (int y = 0; y < framebuffer.height; y++)
    {
        for (int x = 0; x < framebuffer.width; x++)
        {
            float t_min = MAXFLOAT;
            for(Object* object : scene.getObjects())
            {
                auto pixel_loc = pixel00_loc + pixel_delta_u * x + pixel_delta_v * y;
                auto ray = Ray{camera_center, pixel_loc - camera_center};
                float t = object->shape.hit(ray.origin - object->position, ray.direction);

                if (t < 0.0f)
                    continue;
                
                t_min = std::min(t, t_min);

                if (t_min < t)
                    continue;

                linalg::vec3 hit_point = ray.origin + ray.direction * t;
                linalg::vec3 normal = object->shape.normal(hit_point, object->position);
                framebuffer.set(x, y, color_t(normal * 0.5f + 0.5f));
            }
        }
    }
}

void Renderer::save(std::string filename)
{
    stbi_write_jpg(filename.c_str(), framebuffer.width, framebuffer.height, 3, framebuffer.data(), 100);
}