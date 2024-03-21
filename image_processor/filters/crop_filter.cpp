//
// Created by Дмитрий Сергиенко on 18.10.2023.
//
#include "crop_filter.h"
#include <stdexcept>

void CropFilter::Apply(Image &image, std::vector<std::string> params) {
    if (params.size() != 2) {
        throw std::invalid_argument("Wrong params for filter Crop.");
    }

    if (!CheckIntParam(params[0]) || !CheckIntParam(params[1])) {
        throw std::range_error("Wrong params for filter Crop. Params must be int and less than 1e9");
    }

    width = std::stoi(params[0]);
    height = std::stoi(params[1]);
    size_t u_width = static_cast<size_t>(width);
    size_t u_height = static_cast<size_t>(height);
    u_width = std::min(u_width, image.GetWidth());
    u_height = std::min(u_height, image.GetHeight());
    image.CropImage(image.GetHeight() - u_height, 0, image.GetHeight(), u_width);
}