#pragma once

#include <array>
#include <cstdint>
#include <vector>

class color_t
{
public:
    std::array<uint8_t, 4> rgba;
    uint8_t &r = rgba[0];
    uint8_t &g = rgba[1];
    uint8_t &b = rgba[2];
    uint8_t &a = rgba[3];

    color_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : rgba({ r, g, b, a })
    {}

    color_t()
        : rgba({ 0, 0, 0, 0 })
    {}

    color_t(uint8_t *pixel)
        : rgba({ pixel[0], pixel[1], pixel[2], pixel[3] })
    {}
    ~color_t() = default;
};

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
};
