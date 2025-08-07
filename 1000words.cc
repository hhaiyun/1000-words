#include "common.h"

#include "colour.h"
#include "image.h"

// Get hue from checksum
float select_hue(unsigned long &checksum, float step = 0.1f)
{
    int steps = static_cast<int>(360.0f / step);
    float hue = (checksum % steps) * step;
    checksum /= steps;
    return hue;
}

// Get configuration from checksum (0–5)
int select_combination(unsigned long &checksum)
{
    int config = checksum % 6;
    checksum /= 6;
    return config;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " INPUT.txt\n";
        return 1;
    }

    std::string input_filename = argv[1];
    std::ifstream infile(input_filename);

    if (!infile.is_open())
    {
        std::cerr << "Error: Could not open " << input_filename << "\n";
        return 1;
    }

    unsigned long checksum = 0;
    std::vector<RGB> RGB_list;

    char byte;
    int preset;
    while (infile.get(byte) && RGB_list.size() < 2000)
    {
        if (checksum == 0)
        {
            preset = byte;
        }

        checksum = (checksum * 31) + static_cast<unsigned char>(byte);

        switch (preset % 3)
        {
        case 0:
            RGB_list.emplace_back(byte, (byte << 3) | (byte >> 5), (byte * 73) % 256);
            break;
        case 1:
            RGB_list.emplace_back((byte << 3) | (byte >> 5), (byte * 73) % 256, byte);
            break;
        case 2:
            RGB_list.emplace_back((byte * 73) % 256, byte, (byte << 3) | (byte >> 5));
            break;
        }
    }

    infile.close();

    while (RGB_list.size() < 2000)
    {
        RGB_list.emplace_back(0, 0, 0);
    }

    int config = select_combination(checksum);

    bool sel_hue = (config == 3 || config == 4 || config == 5);
    bool sel_pxl_sort_v = (config == 0 || config == 2 || config == 3 || config == 5);
    bool sel_pxl_sort_h = (config == 1 || config == 2 || config == 4 || config == 5);

    float hue = 0.0f;
    if (sel_hue)
    {
        hue = select_hue(checksum);
    }

    image img;

    img.paint(RGB_list, hue, sel_hue, sel_pxl_sort_v, sel_pxl_sort_h, checksum);

    return 0;
}