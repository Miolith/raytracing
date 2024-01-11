#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include "vec3.hpp"

#define FLOAT static_cast<float>
#define UINT8 static_cast<uint8_t>

class color_t
{
public:
    linalg::vec3 rgb;
    float &r = rgb.x;
    float &g = rgb.y;
    float &b = rgb.z;

    color_t(int r, int g, int b)
        : rgb({ FLOAT(r) / 256.0f, FLOAT(g) / 256.0f, FLOAT(b) / 256.0f })
    {}

    color_t()
        : rgb({ 0.0f, 0.0f, 0.0f })
    {}

    color_t(uint8_t *pixel)
        : rgb({ FLOAT(pixel[0]) / 256.0f, FLOAT(pixel[1]) / 256.0f,
                FLOAT(pixel[2]) / 256.0f })
    {}

    color_t(linalg::vec3 rgb)
        : rgb(rgb)
    {}

    color_t(float r, float g, float b)
        : rgb({ r, g, b })
    {}

    void operator=(color_t other)
    {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
    }

    color_t operator*(float scalar)
    {
        return color_t(this->r * scalar, this->g * scalar, this->b * scalar);
    }

    color_t operator+(color_t other)
    {
        return color_t(this->r + other.r, this->g + other.g, this->b + other.b);
    }

    std::array<uint8_t, 3> toRGB()
    {
        return { UINT8(this->r * 255.99f), UINT8(this->g * 255.99f),
                 UINT8(this->b * 255.99f) };
    }
};

inline color_t operator*(float scalar, color_t color)
{
    return color * scalar;
}

class pixelbuffer_t
{
public:
    int width;
    int height;
    uint8_t *pixels;

    pixelbuffer_t(int width, int height)
        : width(width)
        , height(height)
        , pixels(new uint8_t[width * height * 3])
    {}

    color_t operator()(int x, int y)
    {
        return color_t(&pixels[(x + y * this->width) * 3]);
    }

    void clear()
    {
        for (int i = 0; i < this->width * this->height * 3; i++)
        {
            this->pixels[i] = 0;
        }
    }

    ~pixelbuffer_t()
    {
        delete[] pixels;
    }

    uint8_t *data()
    {
        return pixels;
    }

    void set(int x, int y, color_t color)
    {
        uint8_t *pixel = &pixels[(x + y * this->width) * 3];
        std::array<uint8_t, 3> rgb = color.toRGB();
        pixel[0] = rgb[0];
        pixel[1] = rgb[1];
        pixel[2] = rgb[2];
    }
};
