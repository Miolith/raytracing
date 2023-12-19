#include "camera.hpp"
#include "renderer.hpp"
#include "scene.hpp"

int main()
{
    Scene scene;
    Camera camera(480, 640);
    Renderer renderer(scene, camera);

    renderer.render();

    renderer.save("image.png");

    return 0;
}