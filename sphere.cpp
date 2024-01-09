#include <iostream>
#include "object.hpp"

Sphere::Sphere(float radius)
    : radius(radius)
{}

float Sphere::hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection)
{
    // rayOrigin = rayOrigin - position;
    float a = linalg::dot(rayDirection, rayDirection);
    float b = 2.0f * linalg::dot(rayDirection, rayOrigin);
    float c = linalg::dot(rayOrigin, rayOrigin) - radius * radius;
    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f)
    {
        return -1.0f;
    }
    else
    {
        float t1 = (-b + sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b - sqrt(discriminant)) / (2.0f * a);

        if (t1 < 0.0f && t2 < 0.0f)
        {
            return -1.0f;
        }
        else if (t1 < 0.0f)
        {
            return t2;
        }
        else if (t2 < 0.0f)
        {
            return t1;
        }
        else
        {
            return std::min(t1, t2);
        }
    }
}

linalg::vec3 Sphere::normal(linalg::vec3 hitPoint, linalg::vec3 position)
{
    return (hitPoint - position) / radius;
}