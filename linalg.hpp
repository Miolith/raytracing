#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <unordered_map>

namespace linalg
{
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

    struct vec3
    {
        union {float x, r;};
        union {float y, g;};
        union {float z, b;};

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

        vec3 operator*(vec3 other)
        {
            return vec3(this->x * other.x, this->y * other.y,
                        this->z * other.z);
        }

        vec3 operator-()
        {
            return vec3(-this->x, -this->y, -this->z);
        }

        vec3 operator+(float scalar)
        {
            return vec3(this->x + scalar, this->y + scalar, this->z + scalar);
        }

        void operator*=(float scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
        }

        void operator/=(float scalar)
        {
            *this *= 1.0f / scalar;
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

        static vec3 random()
        {
            return vec3(random_float(-1, 1), random_float(-1, 1),
                        random_float(-1, 1))
                .normalize();
        }

        static vec3 random_unit_disk()
        {
            while (true)
            {
                auto p = vec3(random_float(-1, 1), random_float(-1, 1), 0);
                if (p.x*p.x + p.y*p.y < 1)
                    return p;
            }
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

    inline vec3 operator-(const vec3 &v)
    {
        return vec3(-v.x, -v.y, -v.z);
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

    inline vec3 refract(const vec3 &uv, const vec3 &n, float etai_over_etat)
    {
        float cos_theta = fmin(dot(-uv, n), 1.0f);
        vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
        vec3 r_out_parallel =
            -sqrt(fabs(1.0f - dot(r_out_perp, r_out_perp))) * n;
        return r_out_perp + r_out_parallel;
    }

    inline vec3 reflect(const vec3 &v, const vec3 &n)
    {
        return v - 2.0f * dot(v, n) * n;
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