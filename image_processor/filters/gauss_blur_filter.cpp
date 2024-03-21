//
// Created by Дмитрий Сергиенко on 27.10.2023.
//

#include "gauss_blur_filter.h"
#include <cmath>
#include <stdexcept>

void GaussBlurFilter::BlurVert(const Image& image, Image& image_blur_vert, double sigma) {
    size_t imp_len = ceil(sigma * 3);
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel pixel;
            double max_color = 0;
            for (size_t i1 = i - std::min(i, imp_len); i1 < std::min(image.GetHeight(), i + imp_len + 1); ++i1) {
                double k = GetAddition(sigma, i, i1);
                pixel.blue += image.GetPixel(i1, j).blue * k;
                pixel.green += image.GetPixel(i1, j).green * k;
                pixel.red += image.GetPixel(i1, j).red * k;
                max_color += k;
            }
            image_blur_vert.ChangePixel(i, j,
                                        Pixel(pixel.blue / max_color, pixel.green / max_color, pixel.red / max_color));
        }
    }
}

void GaussBlurFilter::BlurHorizon(const Image& image, Image& image_blur_horizon, double sigma) {
    size_t imp_len = ceil(sigma * 3);
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel pixel;
            double max_color = 0;
            for (size_t j1 = j - std::min(j, imp_len); j1 < std::min(image.GetWidth(), j + imp_len + 1); ++j1) {
                double k = GetAddition(sigma, j, j1);
                pixel.blue += image.GetPixel(i, j1).blue * k;
                pixel.green += image.GetPixel(i, j1).green * k;
                pixel.red += image.GetPixel(i, j1).red * k;
                max_color += k;
            }

            image_blur_horizon.ChangePixel(
                i, j, Pixel(pixel.blue / max_color, pixel.green / max_color, pixel.red / max_color));
        }
    }
}

double GaussBlurFilter::GetAddition(double sigma, size_t x0, size_t x) {
    double dist_x = abs(static_cast<double>(x) - static_cast<double>(x0));
    double r = 2 * sigma * sigma;
    return 1 / sqrt(r * M_PI) * pow(M_E, -(dist_x * dist_x) / r);
}

void GaussBlurFilter::Apply(Image& image, std::vector<std::string> params) {
    if (params.size() != 1) {
        throw std::invalid_argument("Wrong params for filter Gaussian Blur.");
    }

    if (!CheckDoubleParam(params[0])) {
        throw std::range_error("Wrong params for filter Gaussian Blur. Params must be double and less than 1e9");
    }

    double sigma = std::stod(params[0]);
    Image image_blur_vert(image.GetHeight(), image.GetWidth());
    BlurVert(image, image_blur_vert, sigma);
    Image image_blur_horizon(image.GetHeight(), image.GetWidth());
    BlurHorizon(image_blur_vert, image_blur_horizon, sigma);
    image = image_blur_horizon;
}
