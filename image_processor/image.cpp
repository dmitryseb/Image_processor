//
// Created by Дмитрий Сергиенко on 24.10.2023.
//

#include "image.h"
#include <stdexcept>

const bool Image::IncorrectIndex(size_t i, size_t j) const {
    return i >= height_ || j >= width_;
}

const Pixel Image::GetPixel(size_t i, size_t j) const {
    if (IncorrectIndex(i, j)) {
        throw std::invalid_argument("Incorrect table indexes.");
    }

    return table_[i][j];
}

void Image::ChangePixel(size_t i, size_t j, Pixel pixel) {
    if (IncorrectIndex(i, j)) {
        throw std::invalid_argument("Incorrect table indexes.");
    }

    table_[i][j] = pixel;
}

void Image::Resize(size_t h, size_t w) {
    table_.resize(h, std::vector<Pixel>(w));
    width_ = w;
    height_ = h;
}

void Image::CropImage(size_t i1, size_t j1, size_t i2, size_t j2) {
    if (i1 > i2 || j1 > j2 || i2 > height_ || j2 > width_) {
        throw std::invalid_argument("Incorrect size for cropping image.");
    }

    std::vector<std::vector<Pixel>> new_table(i2 - i1, std::vector<Pixel>(j2 - j1));
    for (size_t i = i1; i < i2; ++i) {
        for (size_t j = j1; j < j2; ++j) {
            new_table[i - i1][j - j1] = table_[i][j];
        }
    }
    table_ = new_table;
    height_ = i2 - i1;
    width_ = j2 - j1;
}

const std::vector<Pixel> Image::GetRow(size_t i) const {
    if (i >= height_) {
        throw std::invalid_argument("Incorrect table indexes.");
    }

    return table_[i];
}

const std::vector<Pixel> Image::GetCol(size_t j) const {
    if (j >= width_) {
        throw std::invalid_argument("Incorrect table indexes.");
    }

    std::vector<Pixel> col(height_);
    for (size_t i = 0; i < height_; ++i) {
        col[i] = table_[i][j];
    }
    return col;
}

Pixel ToPixel(IntPixel int_pixel) {
    Pixel pixel;
    pixel.blue = static_cast<double>(int_pixel.blue) / UINT8_MAX;
    pixel.green = static_cast<double>(int_pixel.green) / UINT8_MAX;
    pixel.red = static_cast<double>(int_pixel.red) / UINT8_MAX;
    return pixel;
}

double &Pixel::operator[](size_t col_ind) {
    if (col_ind >= 3) {
        throw std::invalid_argument("Wrong arguments for Pixel operator [].");
    }

    if (col_ind == 0) {
        return blue;
    }
    if (col_ind == 1) {
        return green;
    }
    return red;
}

double Pixel::operator[](size_t col_ind) const {
    if (col_ind >= 3) {
        throw std::invalid_argument("Wrong arguments for Pixel operator [].");
    }

    if (col_ind == 0) {
        return blue;
    }
    if (col_ind == 1) {
        return green;
    }
    return red;
}
