#pragma once

class Scene
{
public:
    Scene(/* args */);
    Scene(Scene&& scene) = default;
    ~Scene();
};
