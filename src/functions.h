#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace cmmn {

//this function template is the subject for further improvement
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

namespace {
template<typename... Args>
void __log_error(
    const std::string& file,
    int line,
    const std::string& func,
    Args&&... args
    )
{
    std::ostringstream stream;
    stream
       << "\n[ERROR] : "
       << file << ":" << line << ": " << func;
    // print variadic args
    (void) std::initializer_list<int>{((void) (stream << " " << std::forward<Args>(args)), 0)...};
    std::cout << stream.str() << std::endl;
}
}

#define log_error(...) \
    __log_error(__FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__);

} // namespace cmmn
