#include "object.hpp"

Ground::Ground()
{}

float Ground::hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection)
{
    // rayOrigin.y -= groundHeight;
    if (rayDirection.y < 0.001f)
    {
        return -1.0f;
    }
    float root = -rayOrigin.y / rayDirection.y;

    if (root < 0.001f)
    {
        return -1.0f;
    }

    std::cout << "hit ground" << std::endl;
    return root;
}

linalg::vec3 Ground::normal(linalg::vec3 hitPoint, linalg::vec3 position)
{
    return { 0.0f, 1.0f, 0.0f };
}