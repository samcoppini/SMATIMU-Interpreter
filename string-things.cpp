#include "string-things.hpp"
#include <cctype>
#include <sstream>

bool is_number(const std::string &str) {
    for (auto &c: str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Removes the whitespace from both ends of a string
std::string strip_whitespace(std::string str) {
    auto str_start = str.find_first_not_of(" \t");
    // Check to see if a string is all whitespace
    if (str_start == std::string::npos) {
        return "";
    }
    auto str_end = str.find_last_not_of(" \t");
    return str.substr(str_start, str_end - str_start + 1);
}

// Converts a string to lowercase
std::string to_lower(std::string str) {
    for (auto &c: str) {
        c = std::tolower(c);
    }
    return str;
}

// Splits up a string into a list of tokens seperated by whitespace
tok_list split_tokens(const std::string &str) {
    std::string buffer;
    std::vector<std::string> tokens;
    std::stringstream tok_stream{str};

    while (tok_stream >> buffer) {
        tokens.push_back(buffer);
    }

    return tokens;
}
