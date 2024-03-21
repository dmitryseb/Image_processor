#include "filter.h"

void Filter::Apply(Image &image, std::vector<std::string> params) {
}

Pixel Filter::ApplyMatrix(size_t i, size_t j, const Image &image, const std::vector<std::vector<double> > &matrix) {
    Pixel result_pixel;
    int sz = static_cast<int>(matrix.size()) / 2;
    for (int i1 = -sz; i1 < sz + 1; ++i1) {
        for (int j1 = -sz; j1 < sz + 1; ++j1) {
            Pixel pixel = NearestPixel(static_cast<int>(i) + i1, static_cast<int>(j) + j1, image);
            result_pixel.red += matrix[i1 + sz][j1 + sz] * pixel.red;
            result_pixel.green += matrix[i1 + sz][j1 + sz] * pixel.green;
            result_pixel.blue += matrix[i1 + sz][j1 + sz] * pixel.blue;
        }
    }
    result_pixel.red = std::max(result_pixel.red, 0.0);
    result_pixel.red = std::min(result_pixel.red, 1.0);
    result_pixel.green = std::max(result_pixel.green, 0.0);
    result_pixel.green = std::min(result_pixel.green, 1.0);
    result_pixel.blue = std::max(result_pixel.blue, 0.0);
    result_pixel.blue = std::min(result_pixel.blue, 1.0);
    return result_pixel;
}

Pixel Filter::NearestPixel(int i, int j, const Image &image) {
    i = std::max(0, i);
    j = std::max(0, j);
    i = std::min(static_cast<int>(image.GetHeight()) - 1, i);
    j = std::min(static_cast<int>(image.GetWidth()) - 1, j);
    return image.GetPixel(i, j);
}

bool Filter::CheckIntParam(std::string param) {
    if (param.empty() || param.size() >= std::to_string(INT32_MAX).size()) {
        return false;
    }
    for (const char &c : param) {
        if (!isdigit(c)) {
            return false;
        }
    }
    if (std::to_string(std::stoi(param)) != param) {
        return false;
    }
    return true;
}

bool Filter::CheckDoubleParam(std::string param) {
    if (param.empty() || !isdigit(param[0])) {
        return false;
    }
    if (std::count(param.begin(), param.end(), '.') > 1) {
        return false;
    }
    for (const char &c : param) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    for (size_t i = 0; i < param.size() && param[i] != '.'; ++i) {
        if (i + 1 >= std::to_string(INT32_MAX).size()) {
            return true;
        }
    }
    return true;
}
