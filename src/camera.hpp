#pragma once
#include "linalg/linalg.hpp"

struct Camera
{
    int screenHeight;
    int screenWidth;
    linalg::vec3 position = { 0.0f, 0.0f, -3.0f };
    linalg::vec3 lookat = { 0.0f, 0.0f, -2.0f };
    linalg::vec3 vup = { 0.0f, 1.0f, 0.0f };
    float fov = 90.0f;

    float defocus_angle = 10.0f;
    float focus_distance = 3.4f;

    Camera(int screenHeight, int screenWidth);
    ~Camera();
};