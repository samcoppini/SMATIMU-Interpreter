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

Step::operator std::string() const {
    if (std::get_if<Output>(&command)) {
        return "Output this block's position.";
    }
    else if (std::get_if<Nop>(&command)) {
        return "Do nothing.";
    }
    else if (auto swap = std::get_if<Swap>(&command)) {
        return "Swap " + static_cast<std::string>(swap->step1) +
               " with " + static_cast<std::string>(swap->step2) + ".";
    }
    else if (auto set = std::get_if<Set>(&command)) {
        return "Set " + static_cast<std::string>(set->name) +
               " to " + static_cast<std::string>(set->new_val) + ".";
    }
    else if (auto range = std::get_if<RangeSwap>(&command)) {
        return "Swap " + static_cast<std::string>(range->start1) +
               " through " + static_cast<std::string>(range->end1) +
               " with " + static_cast<std::string>(range->start2) +
               " through " + static_cast<std::string>(range->end2) + ".";
    }
    else if (auto replace = std::get_if<Replace>(&command)) {
        return "Replace " + static_cast<std::string>(replace->to_replace) +
               " with " + static_cast<std::string>(*replace->new_step);
    }
    else {
        return "INVALID INSTRUCTION";
    }
}

Step::Step(const std::string &str): Step(split_tokens(str)) {
}
