#include "object.hpp"

Ground::Ground()
{}

std::optional<float> Ground::hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection) const
{
    // rayOrigin.y -= groundHeight;
    if (rayDirection.y < 0.001f)
        return std::nullopt;
    
    float root = -rayOrigin.y / rayDirection.y;

    if (root < 0.001f)
        return std::nullopt;

    return root;
}

linalg::vec3 Ground::normal(const linalg::vec3 &hitPoint, const linalg::vec3 &position) const
{
    return { 0.0f, 1.0f, 0.0f };
}