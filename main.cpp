#include "camera.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "object.hpp"

int main()
{
    Sphere sphere(1.0f);
    DefaultMaterial material(color_t{1.0f, 0.0f, 0.0f});
    linalg::vec3 position(0.0f, 0.0f, -5.0f);
    Scene scene;
    scene.add(
        Object(
            sphere,
            material,
            position
        )
    );
    Camera camera(480, 640);
    Renderer renderer(scene, camera);

    renderer.render();

    renderer.save("image.jpg");

    return 0;
}