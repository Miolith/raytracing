#pragma once

#include <array>
#include <cstdint>
#include <vector>

#define FLOAT static_cast<float>
#define UINT8 static_cast<uint8_t>

class color_t
{
public:
    std::array<uint8_t, 3> rgb;
    uint8_t &r = rgb[0];
    uint8_t &g = rgb[1];
    uint8_t &b = rgb[2];

    color_t(uint8_t r, uint8_t g, uint8_t b)
        : rgb({ r, g, b})
    {}

    color_t()
        : rgb({ 0, 0, 0})
    {}

    color_t(uint8_t *pixel)
        : rgb({ pixel[0], pixel[1], pixel[2]})
    {}  
};

inline color_t mix(color_t a, color_t b, float t)
{
    return color_t(
        UINT8(FLOAT(a.r) * (1.0f - t) + FLOAT(b.r) * t),
        UINT8(FLOAT(a.g) * (1.0f - t) + FLOAT(b.g) * t),
        UINT8(FLOAT(a.b) * (1.0f - t) + FLOAT(b.b) * t)
    );
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
        pixel[0] = color.r;
        pixel[1] = color.g;
        pixel[2] = color.b;
    }
};
