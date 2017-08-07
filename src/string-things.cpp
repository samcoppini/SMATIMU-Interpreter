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

// Returns whether a string contains a valid step value
bool valid_step_val(const std::string &str) {
    return is_number(str) or str.size() > 1 or (str[0] != '+' and str[0] != '-');
}

// Returns whether a string is a valid variable name
bool valid_var_name(const std::string &str) {
    if (str[0] == '+' or str[0] == '-') {
        return not is_number(str.substr(1));
    } else {
        return not is_number(str);
    }
}

// Removes the whitespace from both ends of a string
std::string strip_whitespace(const std::string &str) {
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
    tok_list tokens;
    std::string cur_tok;

    for (const auto &c: str) {
        if (std::isspace(c)) {
            if (cur_tok.size() > 0) {
                tokens.push_back(cur_tok);
                cur_tok.clear();
            }
        } else {
            cur_tok += c;
        }
    }

    if (cur_tok.size() > 0) {
        tokens.push_back(cur_tok);
    }

    return tokens;
}

// Returns whether two lists of tokens are the same, where empty strings in the
// second token list are allowed to match any token
bool tokens_match(const tok_list &tokens, const tok_list &to_match) {
    if (tokens.size() != to_match.size()) {
        return false;
    }
    for (std::size_t i = 0; i < tokens.size(); i++) {
        if (to_match[i].size() != 0) {
            if (to_match[i] != tokens[i]) {
                return false;
            }
        }
    }
    return true;
}
