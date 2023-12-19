#include "renderer.hpp"
#include "scene.hpp"

int main() {
  Scene scene;
  Renderer renderer(scene);

  renderer.render();

  renderer.save("image.png");

  return 0;
}