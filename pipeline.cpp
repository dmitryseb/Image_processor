//
// Created by Дмитрий Сергиенко on 22.10.2023.
//

#include "pipeline.h"
#include "add_basic_filters.h"
#include <iostream>

const std::string Pipeline::REFERENCE =
    "Reference for Image processor. Available Filters:\n"
    "\n"
    "Crop (-crop width height)\n"
    "Crop the image to the specified chairs and height. The top left part of the image was used.\n"
    "width and height are positive integer arguments.\n"
    "\n"
    "Grayscale (-gs)\n"
    "Converts an image to grayscale.\n"
    "\n"
    "Negative (-neg)\n"
    "Converts an image to negative.\n"
    "\n"
    "Sharpening (-sharp)\n"
    "Sharpens the image.\n"
    "\n"
    "Edge Detection (-edge threshold)\n"
    "The boundaries are highlighted, then pixels with a value exceeding the threshold are colored "
    "white, the rest - black.\n"
    "threshold - real positive number.\n"
    "\n"
    "Gaussian Blur (-blur sigma)\n"
    "blur is performed with the sigma parameter.\n"
    "sigma - real positive number.\n"
    "\n"
    "Pixelation (-pixel size)\n"
    "The image is pixelated with pixel width size.\n"
    "size - positive integer number.\n";

void Pipeline::Parse(int argc, char **argv) {
    if (argc == 2) {
        std::cerr << "Wrong arguments for program.";
        exit(0);
    }

    input_path = argv[1];
    output_path = argv[2];
    int i = 3;
    while (i < argc) {
        if (argv[i][0] != '-') {
            std::cerr << "Wrong arguments for program.";
            exit(0);
        }
        std::vector<std::string> filter = {argv[i]};
        ++i;
        while (i < argc && argv[i][0] != '-') {
            filter.push_back(argv[i]);
            ++i;
        }
        AddFilter(filter);
    }
}

void Pipeline::AddFilter(const std::vector<std::string> &filter) {
    FilterParams filter_params;
    filter_params.filter_name = filter[0].substr(1, filter[0].size() - 1);
    for (size_t i = 1; i < filter.size(); ++i) {
        filter_params.params.push_back(filter[i]);
    }
    filters.push_back(filter_params);
}

void Pipeline::PrintFilterSuccess(const std::string &filter_name) {
    std::cout << "Access applying filter " + filter_name + "." << std::endl;
}

void Pipeline::PrintFilterError(const std::string &filter_name, const std::exception &exception) {
    std::cerr << "Error with applying filter " + filter_name + ". " << exception.what() << std::endl;
}

void Pipeline::PrintInputError(const std::exception &exception) {
    std::cerr << "Error with reading image. " << exception.what() << std::endl;
}

void Pipeline::PrintOutputError(const std::exception &exception) {
    std::cerr << "Error with writing image. " << exception.what() << std::endl;
}

void Pipeline::ApplyFilters(Image &image) {
    FilterTable filter_table;
    AddBasicFilters(filter_table);
    for (const FilterParams &filter_params : filters) {
        try {
            Filter *filter = filter_table.GetFilter(filter_params.filter_name);
            filter->Apply(image, filter_params.params);
            PrintFilterSuccess(filter_params.filter_name);
        } catch (const std::exception &exception) {
            PrintFilterError(filter_params.filter_name, exception);
        }
    }
}

void Pipeline::Run() {
    BmpStream bmp_stream;
    Image image;
    try {
        bmp_stream.Open(input_path, 'r');
        image = bmp_stream.ReadImage();
        bmp_stream.Close();
    } catch (const std::exception &exception) {
        PrintInputError(exception);
        return;
    }
    ApplyFilters(image);
    try {
        bmp_stream.Open(output_path, 'w');
        bmp_stream.WriteImage(image);
        bmp_stream.Close();
    } catch (const std::exception &exception) {
        PrintOutputError(exception);
        return;
    }
}

void Pipeline::CheckReference(int argv) {
    if (argv == 1) {
        std::cout << REFERENCE;
        exit(0);
    }
}
