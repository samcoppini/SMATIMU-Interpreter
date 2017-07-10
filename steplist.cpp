#include "steplist.hpp"
#include <iostream>

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

// Prints out the steps in the list
void StepList::print() const {
    for (auto &step: steps) {
        std::cout << step.step_num << " " << step.step_text << "\n";
    }
}
