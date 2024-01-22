#include "renderer.hpp"

#include <iostream>
#include <ranges>

#include "camera.hpp"
#include "scene.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../extern/stb/stb_image_write.h"

Renderer::Renderer(Scene &scene, Camera &camera)
    : scene(scene)
    , camera(camera)
    , framebuffer(camera.screenWidth, camera.screenHeight)
{}

color_t Renderer::rayColor(Ray ray, int max_depth)
{
    if (max_depth <= 0)
        return color_t(0.0f, 0.0f, 0.0f);

    float t_min = std::numeric_limits<float>::max();
    Object *hit_object = nullptr;

    for (Object *object : scene.getObjects())
    {
        std::optional<float> t =
            object->shape.hit(ray.origin - object->position, ray.direction);

        if (!t.has_value())
            continue;

        if (t_min < t.value())
            continue;

        t_min = t.value();
        hit_object = object;
    }

    if (hit_object == nullptr)
    {
        float a = 0.5 + 0.5 * (ray.direction.normalize().y);
        return (1.0f - a) * SUNSET2 + a * SUNSET;
    }

    linalg::vec3 hit_point = ray.origin + ray.direction * t_min;
    linalg::vec3 normal =
        hit_object->shape.normal(hit_point, hit_object->position);
    color_t color = hit_object->material.color
        * rayColor(Ray{ hit_point,
                        hit_object->material.scatter(ray.direction, normal) },
                   max_depth - 1);

    return color;
}

void Renderer::render()
{
    float aspect_ratio = FLOAT(camera.screenWidth) / FLOAT(camera.screenHeight);
    int image_height = camera.screenHeight;
    int image_width = camera.screenWidth;

    linalg::vec3 center = camera.position;

    // Determine viewport dimensions.
    auto theta = camera.fov * M_PI / 180;
    auto h = tan(theta / 2);
    auto viewport_height = 2 * h * camera.focus_distance;
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
        center - (camera.focus_distance * w) - viewport_u / 2 - viewport_v / 2;
    linalg::vec3 pixel00_loc =
        viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    float defocus_radius =
        camera.focus_distance * tan(camera.defocus_angle / 2);
    linalg::vec3 defocus_disk_u = defocus_radius * u;
    linalg::vec3 defocus_disk_v = defocus_radius * v;

    for (auto [y, x] :
         std::views::cartesian_product(std::views::iota(0, image_height),
                                       std::views::iota(0, image_width)))
    {
        color_t color = color_t(0.0f, 0.0f, 0.0f);
        for (int s = 0; s < samples_per_pixel; s++)
        {
            linalg::vec3 pixel_loc = pixel00_loc
                + pixel_delta_u * (x + linalg::random_float())
                + pixel_delta_v * (y + linalg::random_float());

            linalg::vec3 ray_origin = camera.position;

            if (defocus_radius > 0.0f)
            {
                linalg::vec3 point = linalg::vec3::random_unit_disk();
                ray_origin +=
                    point.x * defocus_disk_u + point.y * defocus_disk_v;
            }

            linalg::vec3 ray_direction = pixel_loc - ray_origin;
            auto ray = Ray{ ray_origin, ray_direction };

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