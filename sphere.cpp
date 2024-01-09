#include <iostream>
#include "object.hpp"

Sphere::Sphere(float radius)
    : radius(radius)
{}

bool Sphere::hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection)
{
    // rayOrigin = rayOrigin - position;
    float a = linalg::dot(rayDirection, rayDirection);
    float b = 2.0f * linalg::dot(rayDirection, rayOrigin);
    float c = linalg::dot(rayOrigin, rayOrigin) - radius * radius;
    float discriminant = b * b - 4.0f * a * c;
    return discriminant >= 0.0f;
}