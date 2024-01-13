#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <random>

namespace linalg
{

    struct vec3
    {
        float x;
        float y;
        float z;

        vec3(float x, float y, float z)
            : x(x)
            , y(y)
            , z(z)
        {}

        vec3()
            : x(0.0f)
            , y(0.0f)
            , z(0.0f)
        {}

        vec3(const vec3 &other)
            : x(other.x)
            , y(other.y)
            , z(other.z)
        {}

        vec3(vec3 &&other)
            : x(other.x)
            , y(other.y)
            , z(other.z)
        {}

        vec3 &operator=(const vec3 &other)
        {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
            return *this;
        }

        vec3(float scalar)
            : x(scalar)
            , y(scalar)
            , z(scalar)
        {}

        vec3 operator+(vec3 other)
        {
            return vec3(this->x + other.x, this->y + other.y,
                        this->z + other.z);
        }

        vec3 operator-(vec3 other)
        {
            return vec3(this->x - other.x, this->y - other.y,
                        this->z - other.z);
        }

        vec3 operator*(float scalar)
        {
            return vec3(this->x * scalar, this->y * scalar, this->z * scalar);
        }

        vec3 operator-()
        {
            return vec3(-this->x, -this->y, -this->z);
        }

        vec3 operator+(float scalar)
        {
            return vec3(this->x + scalar, this->y + scalar, this->z + scalar);
        }

        vec3 operator/=(float scalar)
        {
            this->x /= scalar;
            this->y /= scalar;
            this->z /= scalar;
            return *this;
        }

        vec3 operator*=(float scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            return *this;
        }

        vec3 operator+=(vec3 other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        float length()
        {
            return std::sqrt(this->x * this->x + this->y * this->y
                             + this->z * this->z);
        }

        vec3 normalize()
        {
            float length = this->length();
            return vec3(this->x / length, this->y / length, this->z / length);
        }

        std::ostream &operator<<(std::ostream &os)
        {
            os << "vec3(" << this->x << ", " << this->y << ", " << this->z
               << ")";
            return os;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, vec3 &v)
    {
        os << "vec3(" << v.x << ' ' << v.y << ' ' << v.z << ')';
        return os;
    }

    inline vec3 operator+(const vec3 &u, const vec3 &v)
    {
        return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
    }

    inline vec3 operator-(const vec3 &u, const vec3 &v)
    {
        return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
    }

    inline vec3 operator*(const vec3 &u, const vec3 &v)
    {
        return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
    }

    inline vec3 operator*(float t, const vec3 &v)
    {
        return vec3(t * v.x, t * v.y, t * v.z);
    }

    inline vec3 operator/(vec3 v, float t)
    {
        return (1 / t) * v;
    }

    inline vec3 operator+(vec3 v, float t)
    {
        return vec3(v.x + t, v.y + t, v.z + t);
    }

    inline float dot(const vec3 &u, const vec3 &v)
    {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    inline vec3 cross(const vec3 &u, const vec3 &v)
    {
        return vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
                    u.x * v.y - u.y * v.x);
    }

    inline float random_float()
    {
        static std::uniform_real_distribution<float> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline float random_float(float min, float max)
    {
        return min + (max - min) * random_float();
    }

    inline vec3 random()
    {
        return vec3(random_float(-1, 1), random_float(-1, 1),
                    random_float(-1, 1));
    }

    inline vec3 random_on_hemisphere(const vec3 &normal)
    {
        vec3 on_unit_sphere = random().normalize();
        if (dot(on_unit_sphere, normal)
            > 0.0f) // In the same hemisphere as the normal
            return on_unit_sphere;
        else
            return -on_unit_sphere;
    }

    class mat3
    {
    private:
        std::array<float, 9> data;

    public:
        mat3(float a00, float a01, float a02, float a10, float a11, float a12,
             float a20, float a21, float a22)
            : data({ a00, a01, a02, a10, a11, a12, a20, a21, a22 })
        {}
    };
} // namespace linalg