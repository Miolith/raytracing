#include "renderer.hpp"

#include <iostream>
#include <ranges>

#include "camera.hpp"
#include "scene.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Renderer::Renderer(Scene &scene, Camera &camera)
    : scene(scene)
    , camera(camera)
    , framebuffer(camera.screenWidth, camera.screenHeight)
{}

color_t Renderer::rayColor(Ray ray, int max_depth)
{
    if (max_depth <= 0)
        return color_t(0.0f, 0.0f, 0.0f);

    float t_min = MAXFLOAT;
    auto a = 0.5 + 0.5 * (ray.direction.normalize().y);
    auto color =
        (1.0f - a) * color_t(1.0f, 1.0f, 1.0f) + a * color_t(0.5f, 0.7f, 1.0f);

    for (Object *object : scene.getObjects())
    {
        float t =
            object->shape.hit(ray.origin - object->position, ray.direction);

        if (t < 0.0f)
            continue;

        t_min = std::min(t, t_min);

        if (t_min < t)
            continue;

        linalg::vec3 hit_point = ray.origin + ray.direction * t;
        linalg::vec3 normal = object->shape.normal(hit_point, object->position);
        color = 0.5f
            * rayColor(Ray{hit_point, object->material.scatter(hit_point, normal)},
                       max_depth - 1);
        break;
    }
    return color;
}

void Renderer::render()
{
    float aspect_ratio = FLOAT(camera.screenWidth) / FLOAT(camera.screenHeight);
    int image_height = camera.screenHeight;
    int image_width = camera.screenWidth;

    linalg::vec3 center = camera.position;

    // Determine viewport dimensions.
    auto focal_length = (camera.position - camera.lookat).length();
    auto theta = camera.fov * M_PI / 180;
    auto h = tan(theta / 2);
    auto viewport_height = 2 * h * focal_length;
    auto viewport_width = viewport_height * aspect_ratio;

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    auto w = (camera.position - camera.lookat).normalize();
    auto u = (cross(camera.vup, w)).normalize();
    auto v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical
    // viewport edges.
    linalg::vec3 viewport_u =
        viewport_width * u; // Vector across viewport horizontal edge
    linalg::vec3 viewport_v =
        viewport_height * -v; // Vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    linalg::vec3 pixel_delta_u = viewport_u / image_width;
    linalg::vec3 pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    linalg::vec3 viewport_upper_left =
        center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
    linalg::vec3 pixel00_loc =
        viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    auto camera_center = camera.position;

    for (auto [y, x] :
         std::views::cartesian_product(std::views::iota(0, image_height),
                                       std::views::iota(0, image_width)))
    {
        color_t color = color_t(0.0f, 0.0f, 0.0f);
        for (int s = 0; s < samples_per_pixel; s++)
        {
            auto pixel_loc = pixel00_loc
                + pixel_delta_u * (x + linalg::random_float())
                + pixel_delta_v * (y + linalg::random_float());
            auto ray_direction = pixel_loc - camera_center;
            auto ray = Ray{ camera_center, ray_direction };
            color += rayColor(ray, this->max_depth);
        }
        color /= samples_per_pixel;
        framebuffer.set(x, y, color);
    }
}

void Renderer::save(std::string filename)
{
    stbi_write_jpg(filename.c_str(), framebuffer.width, framebuffer.height, 3,
                   framebuffer.data(), 100);
}