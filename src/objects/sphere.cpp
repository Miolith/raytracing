#include <iostream>

#include "object.hpp"

Sphere::Sphere(float radius)
    : radius(radius)
{}

std::optional<float> Sphere::hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection) const
{
    // rayOrigin = rayOrigin - position;
    float a = linalg::dot(rayDirection, rayDirection);
    float half_b = linalg::dot(rayDirection, rayOrigin);
    float c = linalg::dot(rayOrigin, rayOrigin) - radius * radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0f)
        return std::nullopt;

    float sqrtd = sqrtf(discriminant);

    float root = (-half_b - sqrtd) / a;
    if (root < 0.001f)
    {
        root = (-half_b + sqrtd) / a;
        if (root < 0.001f)
            return std::nullopt;
    }

    return root;
}

linalg::vec3 Sphere::normal(const linalg::vec3 &hitPoint, const linalg::vec3 &position) const
{
    return (hitPoint - position) / radius;
}