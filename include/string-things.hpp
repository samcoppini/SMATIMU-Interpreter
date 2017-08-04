#ifndef STRING_THINGS_HPP
#define STRING_THINGS_HPP

#include <string>
#include <vector>

using tok_list = std::vector<std::string>;

bool is_number(const std::string &str);
std::string strip_whitespace(const std::string &str);
std::string to_lower(std::string str);
tok_list split_tokens(const std::string &str);
bool tokens_match(const tok_list &tokens, const tok_list &to_match);

#endif
