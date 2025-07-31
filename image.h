#ifndef IMAGE_H
#define IMAGE_H

#include "colour.h"

class image
{
public:
    int img_width = 50;
    int img_height = 40;

    void paint(std::vector<RGB> &RGB_list, float hue, bool sel_hue, bool sel_pxl_sort_v, bool sel_pxl_sort_h, unsigned long checksum)
    {
        std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);

        ofs << "P6\n"
            << img_width << ' ' << img_height << "\n255\n"; // Write header info

        if (sel_hue)
        {
            harmonize_RGBs(RGB_list, checksum, hue);
        }

        if (sel_pxl_sort_v)
        {
            for (int col = 0; col < img_width; ++col)
            {
                for (int pass = 0; pass < img_height; ++pass)
                {
                    for (int row = 0; row < img_height - 1 - pass; ++row)
                    {
                        int idx1 = row * img_width + col;
                        int idx2 = (row + 1) * img_width + col;

                        if (RGB_list[idx1].sum() > RGB_list[idx2].sum())
                        {
                            RGB temp = RGB_list[idx1];
                            RGB_list[idx1] = RGB_list[idx2];
                            RGB_list[idx2] = temp;
                        }
                    }
                }
            }
        }

        if (sel_pxl_sort_h)
        {
            for (int row = 0; row < img_height; ++row)
            {
                for (int i = 0; i < img_width; ++i)
                {
                    for (int j = row * img_width; j < (row * img_width) + img_width - 1 - i; ++j)
                    {
                        if (RGB_list[j].sum() > RGB_list[j + 1].sum())
                        {
                            RGB temp = RGB_list[j];
                            RGB_list[j] = RGB_list[j + 1];
                            RGB_list[j + 1] = temp;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < img_width * img_height; ++i)
        {
            write_colour(ofs, RGB_list[i]);
        }

        ofs.close();
    }
};

#endif // IMAGE_H