//
// Created by Дмитрий Сергиенко on 24.10.2023.
//

#include "grayscale_filter.h"
#include <stdexcept>

Pixel GrayscaleFilter::MakeGray(const Pixel &pixel) const {
    double col = RED_MULTIPLIER * pixel.red + GREEN_MULTIPLIER * pixel.green + BLUE_MULTIPLIER * pixel.blue;
    return Pixel(col, col, col);
}

void GrayscaleFilter::Apply(Image &image, std::vector<std::string> params) {
    if (!params.empty()) {
        throw std::invalid_argument("Wrong params for filter Grayscale");
    }

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image.ChangePixel(i, j, MakeGray(image.GetPixel(i, j)));
        }
    }
}
