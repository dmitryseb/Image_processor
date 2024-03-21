//
// Created by Дмитрий Сергиенко on 26.10.2023.
//

#include "edge_detection_filter.h"
#include <stdexcept>

const std::vector<std::vector<double>> EdgeDetectionFilter::MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

Pixel EdgeDetectionFilter::MakeGray(const Pixel& pixel) const {
    double col = RED_MULTIPLIER * pixel.red + GREEN_MULTIPLIER * pixel.green + BLUE_MULTIPLIER * pixel.blue;
    return Pixel(col, col, col);
}

Pixel EdgeDetectionFilter::EdgeDetection(const Pixel& pixel, double threshold) {
    if (pixel.red > threshold) {
        return Pixel(1.0, 1.0, 1.0);
    }
    return Pixel(0.0, 0.0, 0.0);
}

void EdgeDetectionFilter::Apply(Image& image, std::vector<std::string> params) {
    if (params.size() != 1) {
        throw std::invalid_argument("Wrong params for filter Edge Detection.");
    }

    if (!CheckDoubleParam(params[0])) {
        throw std::range_error("Wrong params for filter Edge Detection. Params must be double and less than 1e9");
    }

    double threshold = std::stod(params[0]);
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image.ChangePixel(i, j, MakeGray(image.GetPixel(i, j)));
        }
    }

    Image edge_image(image.GetHeight(), image.GetWidth());
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            edge_image.ChangePixel(i, j, EdgeDetection(ApplyMatrix(i, j, image, MATRIX), threshold));
        }
    }
    image = edge_image;
}
