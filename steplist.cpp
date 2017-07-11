#include "steplist.hpp"
#include "string-things.hpp"
#include <iostream>

StepList::Step::Step(int step_num, const std::string &str): step_num(step_num) {
    auto tokens = split_tokens(str);
    if (tokens == tok_list{"output", "this", "block's", "position"}) {
        command = Output{};
    } else {
        command = Nop{};
    }
}

// Adds a step to the steplist, returning whether a step with that number
// already exists in the list
bool StepList::add_step(int step_num, std::string step_text) {
    Step new_step{step_num, step_text};

    for (auto it = steps.begin(); it != steps.end(); ++it) {
        if (it->step_num > step_num) {
            steps.insert(it, new_step);
            return false;
        }
        else if (it->step_num == step_num)
            return true;
    }
    steps.push_back(new_step);
    return false;
}

// Executes the instructions
void StepList::execute() {
    for (auto &step: steps) {
        if (std::get_if<Step::Output>(&step.command)) {
            std::wcout << (wchar_t) step.step_num;
        }
    }
}
