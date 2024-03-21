//
// Created by Дмитрий Сергиенко on 25.10.2023.
//

#ifndef CPP_HSE_ADD_BASIC_FILTERS_H
#define CPP_HSE_ADD_BASIC_FILTERS_H

#include "filters/filter.h"
#include "filter_table.h"
#include "filters/crop_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/negative_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/edge_detection_filter.h"
#include "filters/gauss_blur_filter.h"
#include "filters/pixelation_filter.h"

void AddBasicFilters(FilterTable &filter_table);

#endif  // CPP_HSE_ADD_BASIC_FILTERS_H
