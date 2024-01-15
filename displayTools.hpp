#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

#include "linalg.hpp"

#define FLOAT static_cast<float>
#define UINT8 static_cast<uint8_t>

class color_t : public linalg::vec3
{
public:
    color_t(int r, int g, int b)
        : vec3(FLOAT(r) / 255.0f, FLOAT(g) / 255.0f, FLOAT(b) / 255.0f)
    {}

    color_t()
        : vec3(0.0f, 0.0f, 0.0f)
    {}

    color_t(uint8_t *pixel)
        : vec3(FLOAT(pixel[0]) / 255.0f, FLOAT(pixel[1]) / 255.0f,
               FLOAT(pixel[2]) / 255.0f)
    {}

    color_t(linalg::vec3 rgb)
        : vec3(rgb)
    {}

    color_t(float r, float g, float b)
        : vec3(r, g, b)
    {}

    color_t(std::string hex)
    {
        if (hex[0] == '#')
            hex = hex.substr(1);
        if (hex.length() == 3)
        {
            this->x = std::stoi(hex.substr(0, 1), nullptr, 16) / 15.0f;
            this->y = std::stoi(hex.substr(1, 1), nullptr, 16) / 15.0f;
            this->z = std::stoi(hex.substr(2, 1), nullptr, 16) / 15.0f;
        }
        else if (hex.length() == 6)
        {
            this->x = std::stoi(hex.substr(0, 2), nullptr, 16) / 255.0f;
            this->y = std::stoi(hex.substr(2, 2), nullptr, 16) / 255.0f;
            this->z = std::stoi(hex.substr(4, 2), nullptr, 16) / 255.0f;
        }
        else
        {
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
        }
    }

    std::tuple<uint8_t, uint8_t, uint8_t> toRGB()
    {
        const float gamma = 1.0f;
        return std::make_tuple(UINT8(std::pow(x, gamma) * 255.0f),
                               UINT8(std::pow(y, gamma) * 255.0f),
                               UINT8(std::pow(z, gamma) * 255.0f));
    }
};

static const color_t RED = color_t(1.0f, 0.0f, 0.0f);
static const color_t GREEN = color_t(0.0f, 1.0f, 0.0f);
static const color_t BLUE = color_t(0.0f, 0.0f, 1.0f);
static const color_t WHITE = color_t(1.0f, 1.0f, 1.0f);
static const color_t BLACK = color_t(0.0f, 0.0f, 0.0f);
static const color_t YELLOW = color_t(1.0f, 1.0f, 0.0f);
static const color_t CYAN = color_t(0.0f, 1.0f, 1.0f);
static const color_t MAGENTA = color_t(1.0f, 0.0f, 1.0f);
static const color_t GRAY = color_t(0.5f, 0.5f, 0.5f);
static const color_t BEIGE = color_t(0.8f, 0.6f, 0.6f);
static const color_t SUNSET = color_t(225, 145, 190);
static const color_t SUNSET2 = color_t(249, 231, 207);

class pixelbuffer_t
{
public:
    int width;
    int height;
    std::unique_ptr<uint8_t[]> pixels;

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

    uint8_t *data()
    {
        return pixels.get();
    }

    void set(int x, int y, color_t color)
    {
        uint8_t *pixel = &pixels[(x + y * this->width) * 3];
        auto [r, g, b] = color.toRGB();
        pixel[0] = r;
        pixel[1] = g;
        pixel[2] = b;
    }
};
