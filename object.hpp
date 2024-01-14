#pragma once
#include <array>

#include "displayTools.hpp"
#include "linalg.hpp"

class Shape
{
public:
    virtual float hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection) = 0;
    virtual linalg::vec3 normal(linalg::vec3 hitPoint,
                                linalg::vec3 position) = 0;
};

class Sphere : public Shape
{
private:
    float radius;

public:
    Sphere(float radius);
    float hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection);
    linalg::vec3 normal(linalg::vec3 hitPoint, linalg::vec3 position);
};

class Ground : public Shape
{
private:
    float groundHeight = 0.0f;

public:
    Ground();
    float hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection);
    linalg::vec3 normal(linalg::vec3 hitPoint, linalg::vec3 position);
};

class Material
{
public:
    color_t color;
    Material(color_t color)
        : color(color)
    {}
    virtual linalg::vec3 scatter(linalg::vec3 &hitPoint, linalg::vec3 &normal) = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(color_t color)
        : Material(color)
    {}

    linalg::vec3 scatter(linalg::vec3 &hitPoint, linalg::vec3 &normal)
    {
        return normal + linalg::vec3::random();
    }
};

class Object
{
public:
    Shape &shape;
    Material &material;
    linalg::vec3 &position;

    Object(Shape &shape, Material &material, linalg::vec3 &position)
        : shape(shape)
        , material(material)
        , position(position)
    {}

    Object(Shape &&shape, Material &&material, linalg::vec3 &&position)
        : shape(shape)
        , material(material)
        , position(position)
    {}
};