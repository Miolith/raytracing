#pragma once
#include "object.hpp"

class Scene
{
private:
    std::vector<Object*> objects;
public:
    Scene(/* args */);
    Scene(Scene&& scene) = default;
    ~Scene();
    void add(Object& object);
    void add(Object&& object);
    std::vector<Object*> getObjects();
};
