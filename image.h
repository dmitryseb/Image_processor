//
// Created by Дмитрий Сергиенко on 24.10.2023.
//

#ifndef CPP_HSE_IMAGE_H
#define CPP_HSE_IMAGE_H

#include <vector>
#include <stdint.h>
#include <exception>
#include <math.h>

struct Pixel {
    Pixel() : blue(0), green(0), red(0) {
    }

    Pixel(double blue, double green, double red) : blue(blue), green(green), red(red) {
    }

    double &operator[](size_t col_ind);
    double operator[](size_t col_ind) const;

    double blue;
    double green;
    double red;
};

struct IntPixel {
    IntPixel() : blue(0.0), green(0.0), red(0.0) {
    }

    IntPixel(uint8_t blue, uint8_t green, uint8_t red) : blue(blue), green(green), red(red) {
    }

    explicit IntPixel(Pixel pixel) {
        blue = static_cast<uint8_t>(round(pixel.blue * UINT8_MAX));
        green = static_cast<uint8_t>(round(pixel.green * UINT8_MAX));
        red = static_cast<uint8_t>(round(pixel.red * UINT8_MAX));
    }

    uint8_t blue;
    uint8_t green;
    uint8_t red;
} __attribute__((packed));

Pixel ToPixel(IntPixel int_pixel);

class Image {

public:
    Image() {
        height_ = 0;
        width_ = 0;
    }

    ~Image() {
    }

    Image(size_t height, size_t width) : height_(height), width_(width) {
        table_.assign(height, std::vector<Pixel>(width, Pixel()));
    }

    const size_t GetWidth() const {
        return width_;
    }
    const size_t GetHeight() const {
        return height_;
    }

    const std::vector<Pixel> GetRow(size_t i) const;

    const std::vector<Pixel> GetCol(size_t j) const;

    const bool IncorrectIndex(size_t i, size_t j) const;

    const Pixel GetPixel(size_t i, size_t j) const;

    void ChangePixel(size_t i, size_t j, Pixel pixel);

    void Resize(size_t i, size_t j);

    void CropImage(size_t i1, size_t j1, size_t i2, size_t j2);

protected:
    size_t height_;
    size_t width_;
    std::vector<std::vector<Pixel> > table_;
};
#endif  // CPP_HSE_IMAGE_H
