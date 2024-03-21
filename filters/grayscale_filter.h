//
// Created by Дмитрий Сергиенко on 24.10.2023.
//

#ifndef CPP_HSE_GRAYSCALE_FILTER_H
#define CPP_HSE_GRAYSCALE_FILTER_H

#include "filter.h"

class GrayscaleFilter : public Filter {
public:
    void Apply(Image &image, std::vector<std::string> params) override;

    ~GrayscaleFilter() override {
    }

protected:
    Pixel MakeGray(const Pixel &pixel) const;

    const double RED_MULTIPLIER = 0.299;
    const double GREEN_MULTIPLIER = 0.587;
    const double BLUE_MULTIPLIER = 0.114;
};

#endif  // CPP_HSE_GRAYSCALE_FILTER_H
