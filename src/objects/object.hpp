#pragma once
#include <array>
#include <optional>

#include "../image_tools/displayTools.hpp"
#include "../linalg/linalg.hpp"

class Shape
{
public:
    virtual std::optional<float> hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection) const = 0;
    virtual linalg::vec3 normal(const linalg::vec3 &hitPoint,
                                const linalg::vec3 &position) const = 0;
};

class Sphere : public Shape
{
private:
    float radius;

public:
    Sphere(float radius);
    std::optional<float> hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection) const override;
    linalg::vec3 normal(const linalg::vec3 &hitPoint, const linalg::vec3 &position) const override;
};

class Ground : public Shape
{
private:
    float groundHeight = 0.0f;

public:
    Ground();
    std::optional<float> hit(linalg::vec3 rayOrigin, linalg::vec3 rayDirection) const override;
    linalg::vec3 normal(const linalg::vec3 &hitPoint, const linalg::vec3 &position) const override;
};

class Material
{
public:
    color_t color;
    Material(color_t color)
        : color(color)
    {}
    virtual linalg::vec3 scatter(linalg::vec3 &rayDir,
                                 linalg::vec3 &normal) = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(color_t color)
        : Material(color)
    {}

    linalg::vec3 scatter(linalg::vec3 &rayDir, linalg::vec3 &normal)
    {
        return normal + linalg::vec3::random();
    }
};

class Metal : public Material
{
public:
    float fuzz = 0.0f;
    Metal(color_t color)
        : Material(color)
    {}

    Metal()
        : Material(color_t(1.0f, 1.0f, 1.0f))
    {}

    Metal(color_t color, float fuzz)
        : Material(color)
        , fuzz(fuzz)
    {}

    Metal(float fuzz)
        : Material(color_t(1.0f, 1.0f, 1.0f))
        , fuzz(fuzz)
    {}

    linalg::vec3 scatter(linalg::vec3 &rayDir, linalg::vec3 &normal)
    {
        auto unit_direction = rayDir.normalize();
        linalg::vec3 return_vector =
            unit_direction - 2.0f * dot(unit_direction, normal) * normal;
        return_vector += fuzz * linalg::vec3::random();
        return return_vector;
    }
};

class Dielectric : public Material
{
public:
    float refraction_index;
    float fuzz = 0.0f;

    Dielectric(color_t color, float refraction_index)
        : Material(color)
        , refraction_index(refraction_index)
    {}

    Dielectric(float refraction_index)
        : Material(color_t(1.0f, 1.0f, 1.0f))
        , refraction_index(refraction_index)
    {}

    Dielectric(color_t color, float refraction_index, float fuzz)
        : Material(color)
        , refraction_index(refraction_index)
        , fuzz(fuzz)
    {}

    Dielectric(float refraction_index, float fuzz)
        : Material(color_t(1.0f, 1.0f, 1.0f))
        , refraction_index(refraction_index)
        , fuzz(fuzz)
    {}

    float reflectance(float cosine, float ref_idx)
    {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * powf((1 - cosine), 5);
    }

    linalg::vec3 scatter(linalg::vec3 &rayDir, linalg::vec3 &normal)
    {
        linalg::vec3 unit_direction = rayDir.normalize();
        bool front_face = dot(unit_direction, normal) < 0.0f;
        float refraction_ratio =
            front_face ? 1.0f / refraction_index : refraction_index;
        linalg::vec3 true_normal = front_face ? normal : -normal;

        float cos_theta = fmin(dot(-unit_direction, true_normal), 1.0f);
        float sin_theta = sqrt(1.0f - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0f;

        linalg::vec3 return_vector;

        if (cannot_refract
            || reflectance(cos_theta, refraction_ratio)
                > linalg::random_float())
            return_vector = linalg::reflect(unit_direction, true_normal);
        else
            return_vector =
                linalg::refract(unit_direction, true_normal, refraction_ratio);

        return_vector += fuzz * linalg::vec3::random();
        return return_vector;
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