#pragma once
#include "vec3.hpp"

class Camera
{
public:
    int screenHeight;
    int screenWidth;
    linalg::vec3 position;
    linalg::vec3 rotation;
    float fov;

    Camera(int screenHeight, int screenWidth);
    ~Camera();
};