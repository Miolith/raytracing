#pragma once
#include "vec3.hpp"

struct Camera
{
    int screenHeight;
    int screenWidth;
    linalg::vec3 position = {0.0f, 0.0f, -3.0f};
    linalg::vec3 rotation = {0.0f, 0.0f, 0.0f};
    float focal_length = 1.0f;

    Camera(int screenHeight, int screenWidth);
    ~Camera();
};