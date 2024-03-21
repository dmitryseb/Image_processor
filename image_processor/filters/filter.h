//
// Created by Дмитрий Сергиенко on 18.10.2023.
//
#pragma once

#include <string>
#include "../image.h"

#ifndef CPP_HSE_FILTER_H
#define CPP_HSE_FILTER_H

class Filter {
public:
    virtual void Apply(Image &image, std::vector<std::string> params);

    virtual ~Filter() {
    }

protected:
    Pixel NearestPixel(int i, int j, const Image &image);

    Pixel ApplyMatrix(size_t i, size_t j, const Image &image, const std::vector<std::vector<double> > &matrix);

    bool CheckIntParam(std::string param);

    bool CheckDoubleParam(std::string param);
};

#endif  // CPP_HSE_FILTER_H
