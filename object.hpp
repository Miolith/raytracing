#pragma once
#include <array>
#include "vec3.hpp"
#include "displayTools.hpp"

class Shape
{
public:
    virtual bool hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection) = 0;
};

class Sphere : public Shape
{
private:
    float radius;
public:
    Sphere(float radius);
    bool hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection);
};


class Material
{
public:
    color_t &color;
    Material(color_t &color) : color(color)
    {}
    virtual float BRDF(linalg::vec3 normal) = 0;
};

class Lambertian : public Material
{
public:
    float BRDF(linalg::vec3 normal);
};

class DefaultMaterial : public Material
{
public:
    color_t color;

    DefaultMaterial() : Material(color)
    {}

    float BRDF(linalg::vec3 normal)
    {
        return 1.0f;
    }
};

class Object
{
public:
    Shape &shape;
    Material &material;
    linalg::vec3 &position;

    Object(Shape &shape, Material &material, linalg::vec3 &position)
        : shape(shape),
          material(material),
          position(position)
    {}

    Object(Shape &&shape, Material &&material, linalg::vec3 &&position)
        : shape(shape),
          material(material),
          position(position)
    {}
};