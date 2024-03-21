//
// Created by Дмитрий Сергиенко on 28.10.2023.
//

#ifndef CPP_HSE_PIXELATION_FILTER_H
#define CPP_HSE_PIXELATION_FILTER_H

#include "filter.h"

class PixelationFilter : public Filter {
public:
    void Apply(Image &image, std::vector<std::string> params) override;

    ~PixelationFilter() override {
    }

protected:
};

#endif  // CPP_HSE_PIXELATION_FILTER_H
