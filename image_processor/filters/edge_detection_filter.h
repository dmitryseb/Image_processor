//
// Created by Дмитрий Сергиенко on 26.10.2023.
//

#ifndef CPP_HSE_EDGE_DETECTION_FILTER_H
#define CPP_HSE_EDGE_DETECTION_FILTER_H

#include "filter.h"

class EdgeDetectionFilter : public Filter {
public:
    void Apply(Image &image, std::vector<std::string> params) override;

    ~EdgeDetectionFilter() override {
    }

protected:
    Pixel EdgeDetection(const Pixel &pixel, double threshold);

    Pixel MakeGray(const Pixel &pixel) const;

    const double RED_MULTIPLIER = 0.299;
    const double GREEN_MULTIPLIER = 0.587;
    const double BLUE_MULTIPLIER = 0.114;
    static const std::vector<std::vector<double>> MATRIX;
};

#endif  // CPP_HSE_EDGE_DETECTION_FILTER_H
