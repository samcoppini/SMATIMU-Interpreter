#include "step.hpp"
#include "string-things.hpp"
#include <iostream>

Step::Step(const tok_list &tokens) {
    if (tokens_match(tokens, {"output", "this", "block's", "position"})) {
        command = Output{};
    } else if (tokens_match(tokens, {"swap", "", "with", ""})) {
        command = Swap{tokens[1], tokens[3]};
    } else if (tokens_match(tokens, {"swap", "", "through", "", "with", "", "through", ""})) {
        command = RangeSwap{tokens[1], tokens[3], tokens[5], tokens[7]};
    } else if (tokens_match(tokens, {"set", "", "to", ""})) {
        command = Set{tokens[1], tokens[3]};
    } else if (tokens.size() > 2 and tokens[0] == "replace" and tokens[2] == "with") {
        tok_list replace_toks{tokens.begin() + 3, tokens.end()};
        command = Replace{tokens[1], std::make_shared<Step>(replace_toks)};
    } else {
        command = Nop{};
    }
}

Step::Step(const std::string &str): Step(split_tokens(str)) {
}
