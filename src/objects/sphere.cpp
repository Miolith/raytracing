#include <cassert>
#include <iostream>

#include "object.hpp"

Sphere::Sphere(float radius)
    : radius(radius)
{}

float Sphere::hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection)
{
    // rayOrigin = rayOrigin - position;
    float a = linalg::dot(rayDirection, rayDirection);
    float half_b = linalg::dot(rayDirection, rayOrigin);
    float c = linalg::dot(rayOrigin, rayOrigin) - radius * radius;
    float discriminant = half_b * half_b - a * c;
    if (discriminant < 0.0f)
        return -1.0f;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < 0.001f)
    {
        root = (-half_b + sqrtd) / a;
        if (root < 0.001f)
            return -1.0f;
    }

    if (std::isnan(root))
        std::cout << "fail" << std::endl;
    return root;
}

linalg::vec3 Sphere::normal(linalg::vec3 hitPoint, linalg::vec3 position)
{
    return (hitPoint - position) / radius;
}