#include "camera.hpp"

Camera::Camera(int screenHeight, int screenWidth)
    : screenHeight(screenHeight)
    , screenWidth(screenWidth)
    , position({ 0.0f, 0.0f, 0.0f })
    , rotation({ 0.0f, 0.0f, 0.0f })
    , focal_length(1.0f)
{}

Camera::~Camera()
{}