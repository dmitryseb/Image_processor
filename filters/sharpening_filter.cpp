//
// Created by Дмитрий Сергиенко on 25.10.2023.
//

#include "sharpening_filter.h"
#include <stdexcept>

const std::vector<std::vector<double>> SharpeningFilter::MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

Pixel SharpeningFilter::Sharpening(size_t i, size_t j, Image& image) {
    return ApplyMatrix(i, j, image, MATRIX);
}

void SharpeningFilter::Apply(Image& image, std::vector<std::string> params) {
    if (!params.empty()) {
        throw std::invalid_argument("Wrong params for filter Sharpening");
    }

    Image sharpening_image(image.GetHeight(), image.GetWidth());
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            sharpening_image.ChangePixel(i, j, Sharpening(i, j, image));
        }
    }
    image = sharpening_image;
}
