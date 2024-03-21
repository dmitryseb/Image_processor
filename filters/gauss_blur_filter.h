//
// Created by Дмитрий Сергиенко on 27.10.2023.
//

#ifndef CPP_HSE_GAUSS_BLUR_FILTER_H
#define CPP_HSE_GAUSS_BLUR_FILTER_H

#include "filter.h"

class GaussBlurFilter : public Filter {
public:
    void Apply(Image& image, std::vector<std::string> params) override;

    ~GaussBlurFilter() override {
    }

private:
    void BlurVert(const Image& image, Image& image_blur_vert, double sigma);

    void BlurHorizon(const Image& image, Image& image_blur_horizon, double sigma);

    double GetAddition(double sigma, size_t x0, size_t x);
};

#endif  // CPP_HSE_GAUSS_BLUR_FILTER_H
