//
// Created by Дмитрий Сергиенко on 25.10.2023.
//

#include "add_basic_filters.h"

void AddBasicFilters(FilterTable& filter_table) {
    CropFilter* crop_filter = new CropFilter;
    filter_table.AddFilter("crop", crop_filter);
    GrayscaleFilter* grayscale_filter = new GrayscaleFilter;
    filter_table.AddFilter("gs", grayscale_filter);
    NegativeFilter* negative_filter = new NegativeFilter;
    filter_table.AddFilter("neg", negative_filter);
    SharpeningFilter* sharpening_filter = new SharpeningFilter;
    filter_table.AddFilter("sharp", sharpening_filter);
    EdgeDetectionFilter* edge_detection_filter = new EdgeDetectionFilter;
    filter_table.AddFilter("edge", edge_detection_filter);
    GaussBlurFilter* gauss_blur_filter = new GaussBlurFilter;
    filter_table.AddFilter("blur", gauss_blur_filter);
    PixelationFilter* pixelation_filter = new PixelationFilter;
    filter_table.AddFilter("pixel", pixelation_filter);
}