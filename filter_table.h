//
// Created by Дмитрий Сергиенко on 22.10.2023.
//

#include <map>
#include "filters/filter.h"

#ifndef CPP_HSE_FILTERTABLE_H
#define CPP_HSE_FILTERTABLE_H

class FilterTable {
public:
    FilterTable() {
    }

    ~FilterTable();

    void AddFilter(std::string filter_name, Filter* filter);

    void DeleteFilter(std::string filter_name);

    Filter* GetFilter(std::string filter_name);

    size_t Size() const;

protected:
    std::map<std::string, Filter*> table_;
};

#endif  // CPP_HSE_FILTERTABLE_H
