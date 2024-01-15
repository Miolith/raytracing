#include "camera.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "scene.hpp"

int main()
{
    Scene scene;

    Sphere sphere(1.0f);
    Lambertian material(BEIGE);
    linalg::vec3 position(0.0f, 0.5f, -3.0f);
    Object opaque_sphere{ sphere, material, position };
    scene.add(opaque_sphere);

    Sphere metal_sphere{ 1.0f };
    Metal material3{ 0.1f };
    linalg::vec3 metal_position(2.5f, 0.5f, -3.0f);
    Object metal_obj{ metal_sphere, material3, metal_position };
    scene.add(metal_obj);

    Sphere transparent_sphere{ 1.0f };
    Dielectric material_d{ 1.2f, 0.2f };
    linalg::vec3 trans_position(-2.5f, 0.5f, -3.0f);
    Object transparent_obj{ transparent_sphere, material_d, trans_position };
    scene.add(transparent_obj);

    Sphere ground{ 100.0f };
    Metal material2({ 0.9f, 0.9f, 1.0f }, 0.05f);
    linalg::vec3 groundPosition(0.0f, -100.5f, -5.0f);
    auto obj = Object(ground, material2, groundPosition);
    scene.add(obj);

    Camera camera(480, 640);
    camera.position = { -2.0f, 2.0f, 1.0f };
    camera.lookat = { 0.0f, 0.0f, -3.0f };
    camera.vup = { 0.0f, 1.0f, 0.0f };
    camera.fov = 90.0f;

    Renderer renderer(scene, camera);
    renderer.max_depth = 50;
    renderer.samples_per_pixel = 100;

    renderer.render();

    renderer.save("image.jpg");

    return 0;
}