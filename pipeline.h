//
// Created by Дмитрий Сергиенко on 22.10.2023.
//

#ifndef CPP_HSE_PIPELINE_H
#define CPP_HSE_PIPELINE_H

#include <string>
#include <vector>
#include "filters/filter.h"
#include "bmp_utils.h"
#include <stdexcept>

class Pipeline {

public:
    Pipeline(std::string input_path, std::string output_path) : input_path(input_path), output_path(output_path) {
    }

    Pipeline() {
    }

    ~Pipeline() {
    }

    void CheckReference(int argv);

    void ChangeInputPath(std::string path) {
        input_path = path;
    }

    void ChangeOutputPath(std::string path) {
        output_path = path;
    }

    void Parse(int argc, char** argv);

    void AddFilter(const std::vector<std::string>& arg);

    void Run();

protected:
    struct FilterParams {
        FilterParams() {
        }

        FilterParams(std::string filter_name, std::vector<std::string> params)
            : filter_name(filter_name), params(params){};

        std::string filter_name;
        std::vector<std::string> params;
    };

    void PrintFilterSuccess(const std::string& filter_name);

    void PrintFilterError(const std::string& filter_name, const std::exception& exception);

    void ApplyFilters(Image& image);

    void PrintInputError(const std::exception& exception);
    void PrintOutputError(const std::exception& exception);

    std::string input_path;
    std::string output_path;
    std::vector<FilterParams> filters;
    static const std::string REFERENCE;
};

#endif  // CPP_HSE_PIPELINE_H
