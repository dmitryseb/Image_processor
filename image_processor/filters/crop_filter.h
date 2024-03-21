//
// Created by Дмитрий Сергиенко on 18.10.2023.
//
#ifndef CPP_HSE_CROP_FILTER_H
#define CPP_HSE_CROP_FILTER_H

#include "filter.h"

class CropFilter : public Filter {
public:
    ~CropFilter() override {
    }

    void Apply(Image &image, std::vector<std::string> params) override;

protected:
    int width;
    int height;
};

#endif  // CPP_HSE_CROP_FILTER_H
