#include "string-things.hpp"
#include <cctype>

bool is_number(const std::string &str) {
    for (auto &c: str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

std::string strip_whitespace(std::string str) {
    auto str_start = str.find_first_not_of(" \t");
    auto str_end = str.find_last_not_of(" \t");
    return str.substr(str_start, str_end - str_start + 1);
}
