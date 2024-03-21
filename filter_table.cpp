//
// Created by Дмитрий Сергиенко on 22.10.2023.
//

#include "filter_table.h"
#include <stdexcept>

void FilterTable::AddFilter(std::string filter_name, Filter *filter) {
    table_.insert(std::make_pair(filter_name, filter));
}

void FilterTable::DeleteFilter(std::string filter_name) {
    if (table_.find(filter_name) == table_.end()) {
        throw std::invalid_argument(filter_name + " not found.");
    }

    Filter *filter = table_.find(filter_name)->second;
    table_.erase(filter_name);
    delete filter;
}

Filter *FilterTable::GetFilter(std::string filter_name) {
    if (table_.find(filter_name) == table_.end()) {
        throw std::invalid_argument("Filter for param -" + filter_name + " not found.");
    }

    return table_.find(filter_name)->second;
}

size_t FilterTable::Size() const {
    return table_.size();
}

FilterTable::~FilterTable() {
    while (!table_.empty()) {
        std::string filter_name = table_.begin()->first;
        DeleteFilter(filter_name);
    }
}
