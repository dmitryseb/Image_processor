//
// Created by Дмитрий Сергиенко on 29.10.2023.
//

#include <catch.hpp>
#include "add_basic_filters.h"
#include "bmp_utils.h"

TEST_CASE("Wrong arguments checking") {

    Image image;
    REQUIRE_THROWS(image.ChangePixel(0, 0, Pixel(0, 0, 0)));

    CropFilter crop_filter;
    REQUIRE_THROWS(crop_filter.Apply(image, {"1"}));
    REQUIRE_THROWS(crop_filter.Apply(image, {"1", "1000000000"}));
    REQUIRE_NOTHROW(crop_filter.Apply(image, {"1", "2"}));

    EdgeDetectionFilter edge_detection_filter;
    REQUIRE_THROWS(edge_detection_filter.Apply(image, {}));
    REQUIRE_THROWS(edge_detection_filter.Apply(image, {".0"}));
    REQUIRE_NOTHROW(edge_detection_filter.Apply(image, {"1.1"}));

    Filter filter;
    REQUIRE_NOTHROW(filter.Apply(image, {"1", "2"}));

    GaussBlurFilter gauss_blur_filter;
    REQUIRE_THROWS(gauss_blur_filter.Apply(image, {}));
    REQUIRE_THROWS(gauss_blur_filter.Apply(image, {".0"}));
    REQUIRE_NOTHROW(gauss_blur_filter.Apply(image, {"1.1"}));

    GrayscaleFilter grayscale_filter;
    REQUIRE_THROWS(grayscale_filter.Apply(image, {"1.1"}));
    REQUIRE_NOTHROW(grayscale_filter.Apply(image, {}));

    NegativeFilter negative_filter;
    REQUIRE_THROWS(negative_filter.Apply(image, {"1.1"}));
    REQUIRE_NOTHROW(negative_filter.Apply(image, {}));

    PixelationFilter pixelation_filter;
    REQUIRE_THROWS(pixelation_filter.Apply(image, {}));
    REQUIRE_THROWS(pixelation_filter.Apply(image, {"1.1"}));
    REQUIRE_NOTHROW(pixelation_filter.Apply(image, {"100"}));

    SharpeningFilter sharpening_filter;
    REQUIRE_THROWS(sharpening_filter.Apply(image, {"100"}));
    REQUIRE_NOTHROW(sharpening_filter.Apply(image, {}));

    REQUIRE(image.GetWidth() == 0);
    REQUIRE(image.GetHeight() == 0);
}

TEST_CASE("FilterTable Checking") {

    FilterTable filter_table;
    REQUIRE(filter_table.Size() == 0);

    REQUIRE_THROWS(filter_table.GetFilter("none"));

    Filter* new_filter = new Filter;
    filter_table.AddFilter("test_filter", new_filter);
    REQUIRE_NOTHROW(filter_table.GetFilter("test_filter"));

    filter_table.DeleteFilter("test_filter");
    REQUIRE_THROWS(filter_table.GetFilter("test_filter"));
}

TEST_CASE("BmpStream Checking") {

    BmpStream bmp_stream;
    REQUIRE_THROWS(bmp_stream.Open("unknown.bmp", 'r'));
    REQUIRE_THROWS(bmp_stream.ReadImage());
}
