#pragma once
#include <string>
#include "scene.hpp"

class Renderer
{
public:
  Renderer(Scene& scene);
  ~Renderer();
  void render();
  void save(std::string filename);
};