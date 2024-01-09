#include "object.hpp"

Ground::Ground()
{}

float Ground::hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection)
{
    // rayOrigin.y -= groundHeight;
    float t = -rayOrigin.y / rayDirection.y;
    if (t < 0.0f)
    {
        return -1.0f;
    }
    else
    {
        return t;
    }
}

linalg::vec3 Ground::normal(linalg::vec3 hitPoint, linalg::vec3 position)
{
    return {0.0f, 1.0f, 0.0f};
}