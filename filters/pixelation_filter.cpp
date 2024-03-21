//
// Created by Дмитрий Сергиенко on 28.10.2023.
//

#include "pixelation_filter.h"
#include <stdexcept>
#include <vector>

void PixelationFilter::Apply(Image& image, std::vector<std::string> params) {
    if (params.size() != 1) {
        throw std::invalid_argument("Wrong params for filter Pixelation.");
    }

    if (!CheckIntParam(params[0])) {
        throw std::range_error("Wrong params for filter Pixelation. Params must be int and less than 1e9");
    }

    int cnt_pixels = std::stoi(params[0]);
    for (size_t i = 0; i < (image.GetHeight() + cnt_pixels - 1) / cnt_pixels; ++i) {
        for (size_t j = 0; j < (image.GetWidth() + cnt_pixels - 1) / cnt_pixels; ++j) {
            double pixels_num = 0;
            Pixel pixel;
            for (size_t i1 = i * cnt_pixels; i1 < std::min(image.GetHeight(), (i + 1) * cnt_pixels); ++i1) {
                for (size_t j1 = j * cnt_pixels; j1 < std::min(image.GetWidth(), (j + 1) * cnt_pixels); ++j1) {
                    pixel.blue += image.GetPixel(i1, j1).blue;
                    pixel.green += image.GetPixel(i1, j1).green;
                    pixel.red += image.GetPixel(i1, j1).red;
                    pixels_num++;
                }
            }
            pixel.blue /= pixels_num;
            pixel.green /= pixels_num;
            pixel.red /= pixels_num;
            for (size_t i1 = i * cnt_pixels; i1 < std::min(image.GetHeight(), (i + 1) * cnt_pixels); ++i1) {
                for (size_t j1 = j * cnt_pixels; j1 < std::min(image.GetWidth(), (j + 1) * cnt_pixels); ++j1) {
                    image.ChangePixel(i1, j1, pixel);
                }
            }
        }
    }
}
