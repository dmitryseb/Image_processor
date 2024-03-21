//
// Created by Дмитрий Сергиенко on 24.10.2023.
//

#ifndef CPP_HSE_NEGATIVE_FILTER_H
#define CPP_HSE_NEGATIVE_FILTER_H

#include "filter.h"

class NegativeFilter : public Filter {
public:
    void Apply(Image &image, std::vector<std::string> params) override;
    ~NegativeFilter() override {
    }
};

#endif  // CPP_HSE_NEGATIVE_FILTER_H
