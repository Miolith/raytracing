#include "camera.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "scene.hpp"

int main()
{
    Scene scene;

    Sphere sphere(1.0f);
    DefaultMaterial material(color_t{ 1.0f, 0.0f, 0.0f });
    linalg::vec3 position(0.0f, 0.0f, -5.0f);
    auto obj1 = Object(sphere, material, position);
    scene.add(obj1);

    Sphere ground{ 100.0f };
    DefaultMaterial material2(color_t{ 1.0f, 0.0f, 1.0f });
    linalg::vec3 groundPosition(0.0f, -100.5f, -5.0f);
    auto obj = Object(ground, material2, groundPosition);
    scene.add(obj);
    Camera camera(480, 640);
    Renderer renderer(scene, camera);

    renderer.render();

    renderer.save("image.jpg");

    return 0;
}