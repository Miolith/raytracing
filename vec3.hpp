#pragma once
#include <array>


namespace linalg
{

class vec3
{
private:
    std::array<float, 3> data;
public:
    vec3(float x, float y, float z)
        : data({ x, y, z })
    {}

    vec3()
        : data({ 0.0f, 0.0f, 0.0f })
    {}

    float &x = data[0];
    float &y = data[1];
    float &z = data[2];

    vec3 operator+(vec3 other)
    {
        return vec3(
            this->x + other.x,
            this->y + other.y,
            this->z + other.z
        );
    }

    vec3 operator-(vec3 other)
    {
        return vec3(
            this->x - other.x,
            this->y - other.y,
            this->z - other.z
        );
    }

    vec3 operator*(float scalar)
    {
        return vec3(
            this->x * scalar,
            this->y * scalar,
            this->z * scalar
        );
    }

    vec3 operator/(float scalar)
    {
        return vec3(
            this->x / scalar,
            this->y / scalar,
            this->z / scalar
        );
    }

    float operator[](int index)
    {
        return this->data[index];
    }
};


inline float dot(vec3 a, vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 cross(vec3 a, vec3 b)
{
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z, 
        a.x * b.y - a.y * b.x
    );
}

class mat3
{
private:
    std::array<float, 9> data;
public:
    mat3(
        float a00, float a01, float a02,
        float a10, float a11, float a12,
        float a20, float a21, float a22
    )
        : data({
            a00, a01, a02,
            a10, a11, a12,
            a20, a21, a22
        })
    {}
};
}