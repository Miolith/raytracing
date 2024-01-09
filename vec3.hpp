#pragma once
#include <array>
#include <cmath>
#include <iostream>

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

    float operator[](int index)
    {
        return this->data[index];
    }

    void operator=(vec3 other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    vec3 operator-()
    {
        return vec3(
            -this->x,
            -this->y,
            -this->z
        );
    }

    vec3 operator+(float scalar)
    {
        return vec3(
            this->x + scalar,
            this->y + scalar,
            this->z + scalar
        );
    }

    float length()
    {
        return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    vec3 normalize()
    {
        float length = this->length();
        return vec3(
            this->x / length,
            this->y / length,
            this->z / length
        );
    }

    std::ostream &operator<<(std::ostream &os)
    {
        os << "vec3(" << this->x << ", " << this->y << ", " << this->z << ")";
        return os;
    }
};

inline std::ostream &operator<<(std::ostream &os, vec3 &v)
{
    os << "vec3(" << v.x << ' ' << v.y << ' ' << v.z << ')';
    return os;
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.x, t*v.y, t*v.z);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline vec3 operator+(vec3 v, double t) {
    return vec3(v.x + t, v.y + t, v.z + t);
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.x * v.x
         + u.y * v.y
         + u.z * v.z;
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x);
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