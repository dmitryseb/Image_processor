//
// Created by Дмитрий Сергиенко on 24.10.2023.
//

#include "negative_filter.h"
#include <stdexcept>

void NegativeFilter::Apply(Image &image, std::vector<std::string> params) {
    if (!params.empty()) {
        throw std::invalid_argument("Wrong params for filter Negative");
    }

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel pixel = image.GetPixel(i, j);
            image.ChangePixel(i, j, Pixel(1 - pixel.blue, 1 - pixel.green, 1 - pixel.red));
        }
    }
}