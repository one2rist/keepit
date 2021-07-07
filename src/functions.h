#pragma once

#include <iostream>
#include <sstream>
#include <string>

//this function template is the subject for further improvement
namespace cmmn {

template<typename StringContainer>
void split(StringContainer& sc, const std::string& str, const char /* unused for delimeter */) {
    std::istringstream ss(str);
    std::string word;
    while (ss) {
        ss >> word;
        if (!word.empty()) {
            sc.emplace(std::move(word));
        }
    }
}

void visualize_progress(char c = '.') {
    std::cout << c << std::flush;
}

} // namespace cmmn
