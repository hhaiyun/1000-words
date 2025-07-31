#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"

using HSV = vec3<float>;
using RGB = vec3<int>;

void write_colour(std::ofstream &ofs, const RGB &pixel_colour)
{
    unsigned char r = static_cast<unsigned char>(pixel_colour.x);
    unsigned char g = static_cast<unsigned char>(pixel_colour.y);
    unsigned char b = static_cast<unsigned char>(pixel_colour.z);

    // Write out the pixel colour components.
    ofs << r << g << b;
}

// REFERENCE: https://www.rapidtables.com/convert/color/rgb-to-hsv.html
HSV rgb_to_hsv(RGB rgb)
{
    // Normalized to [0, 1]
    float r = rgb.x / 255.0;
    float g = rgb.y / 255.0;
    float b = rgb.z / 255.0;

    float max_val = std::max({r, g, b});
    float min_val = std::min({r, g, b});
    float delta = max_val - min_val;

    float h = 0.0; // Hue
    if (delta > 0)
    {
        if (max_val == r)
        {
            h = 60.0 * std::fmod((g - b) / delta, 6.0);
        }
        else if (max_val == g)
        {
            h = 60.0 * ((b - r) / delta + 2.0);
        }
        else
        {
            h = 60.0 * ((r - g) / delta + 4.0);
        }
    }

    if (h < 0)
    {
        h += 360.0; // Wrap negatives
    }

    float s = max_val == 0 ? 0 : delta / max_val; // Saturation
    float v = max_val;                            // Value

    return {h, s, v};
}

// REFERENCE: https://www.rapidtables.com/convert/color/hsv-to-rgb.html
RGB hsv_to_rgb(HSV hsv)
{
    float h = hsv.x;
    float s = hsv.y;
    float v = hsv.z;

    float c = v * s;
    float x = c * (1 - std::fabs(std::fmod(h / 60.0, 2) - 1));
    float m = v - c;

    float r1, g1, b1;
    if (h < 60)
    {
        r1 = c, g1 = x, b1 = 0;
    }
    else if (h < 120)
    {
        r1 = x, g1 = c, b1 = 0;
    }
    else if (h < 180)
    {
        r1 = 0, g1 = c, b1 = x;
    }
    else if (h < 240)
    {
        r1 = 0, g1 = x, b1 = c;
    }
    else if (h < 300)
    {
        r1 = x, g1 = 0, b1 = c;
    }
    else
    {
        r1 = c, g1 = 0, b1 = x;
    }

    return {
        static_cast<int>((r1 + m) * 255),
        static_cast<int>((g1 + m) * 255),
        static_cast<int>((b1 + m) * 255)};
}

HSV analogous_colour(float base_hue, unsigned long checksum, float spread = 20.0)
{
    static std::mt19937 rng(checksum);
    std::uniform_real_distribution<float> hue_shift(-spread, spread);
    std::uniform_real_distribution<float> sat(0.5, 0.9);
    std::uniform_real_distribution<float> val(0.5, 0.9);

    float h = std::fmod((base_hue + hue_shift(rng) + 360.0), 360.0);
    return {h, sat(rng), val(rng)};
}

void harmonize_RGBs(std::vector<RGB> &RGB_list, unsigned long checksum, float base_hue = 210.0)
{
    for (auto &colour : RGB_list)
    {
        HSV harmonious_hsv = analogous_colour(base_hue, checksum);
        RGB rgb = hsv_to_rgb(harmonious_hsv);
        colour.x = rgb.x;
        colour.y = rgb.y;
        colour.z = rgb.z;
    }
}

#endif // COLOUR_H