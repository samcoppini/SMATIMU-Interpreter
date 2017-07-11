#include "step.hpp"
#include "string-things.hpp"
#include <iostream>

Step::Step(const std::string &str) {
    auto tokens = split_tokens(str);

    if (tokens_match(tokens, {"output", "this", "block's", "position"})) {
        command = Output{};
    } else if (tokens_match(tokens, {"swap", "", "with", ""})) {
        command = Swap{tokens[1], tokens[3]};
    } else if (tokens_match(tokens, {"set", "", "to", ""})) {
        command = Set{tokens[1], tokens[3]};
    } else {
        command = Nop{};
    }
}
