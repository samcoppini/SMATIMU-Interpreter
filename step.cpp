#include "step.hpp"
#include "string-things.hpp"
#include <iostream>
#include <string>

Step::Step(const std::string &str) {
    auto tokens = split_tokens(str);

    if (tokens_match(tokens, {"output", "this", "block's", "position"})) {
        command = Output{};
    } else if (tokens_match(tokens, {"swap", "", "with", ""})) {
        if (is_number(tokens[1]) and is_number(tokens[3])) {
            command = Swap{std::stoi(tokens[1]), std::stoi(tokens[3])};
        } else {
            command = Swap{INVALID_STEP, INVALID_STEP};
        }
    } else {
        command = Nop{};
    }
}
