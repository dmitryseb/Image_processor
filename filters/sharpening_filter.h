//
// Created by Дмитрий Сергиенко on 25.10.2023.
//

#ifndef CPP_HSE_SHARPENING_FILTER_H
#define CPP_HSE_SHARPENING_FILTER_H

#include "filter.h"

class SharpeningFilter : public Filter {
public:
    void Apply(Image &image, std::vector<std::string> params) override;

    ~SharpeningFilter() override {
    }

protected:
    Pixel Sharpening(size_t i, size_t j, Image &image);

    static const std::vector<std::vector<double>> MATRIX;
};

#endif  // CPP_HSE_SHARPENING_FILTER_H
