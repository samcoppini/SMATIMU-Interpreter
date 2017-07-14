#include "steplist.hpp"
#include "string-things.hpp"
#include <chrono>
#include <climits>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

StepList::StepList() {
    top_left = new StepNode{INT_MIN, new Step{""}, nullptr, nullptr};
}

StepList::StepList(StepList &&other) {
    top_left = other.top_left;
    other.top_left = nullptr;
}

StepList::~StepList() {
    auto cur_node = top_left;
    while (cur_node) {
        auto next_level = cur_node->down;
        while (cur_node) {
            auto temp_ptr = cur_node;
            if (next_level == nullptr) {
                delete temp_ptr->step;
            }
            cur_node = cur_node->right;
            delete temp_ptr;
        }
        cur_node = next_level;
    }
}

// Returns true with 50/50 odds
bool coin_flip() {
    static int seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator{seed};
    static std::uniform_int_distribution<int> dist(0, 1);
    return dist(generator);
}

// Adds a step to the steplist, returning a pointer to the newly-created step,
// or nullptr if there was already a step in the list with that number
Step *StepList::add_step(int step_num, std::string step_text) {
    std::vector<StepNode*> levels;
    auto cur_node = top_left;

    // Find the appropriate place to insert the step node in the skip list
    while (cur_node->down or (cur_node->right and cur_node->right->step_num <= step_num)) {
        while (cur_node->right and cur_node->right->step_num <= step_num) {
            cur_node = cur_node->right;
        }
        if (cur_node->down) {
            levels.push_back(cur_node);
            cur_node = cur_node->down;
        }
    }

    // Don't reinsert an already-present step
    if (cur_node->step_num == step_num) {
        return nullptr;
    }

    // Insert the node in the bottom layer of the skip list
    auto step = new Step{step_text};
    auto new_ptr = new StepNode{step_num, step, cur_node->right, nullptr};
    cur_node->right = new_ptr;

    // Grow the tower in the skip list upwards
    unsigned height = 0;
    while (height <= levels.size() and coin_flip()) {
        if (height == levels.size()) {
            top_left = new StepNode{INT_MIN, top_left->step, nullptr, top_left};
            cur_node = top_left;
        } else {
            cur_node = levels[levels.size() - height - 1];
        }

        new_ptr = new StepNode{step_num, step, cur_node->right, new_ptr};
        cur_node->right = new_ptr;
        height++;
    }

    return step;
}

// Returns a pointer to the step corresponding to a step number
// If no such step exists, this inserts a NOP step for that number, and returns
// a pointer to that step
Step *StepList::get_step(int step_num) {
    auto cur_node = top_left;
    do {
        while (cur_node->right and cur_node->right->step_num <= step_num) {
            cur_node = cur_node->right;
        }
        if (cur_node->step_num == step_num) {
            return cur_node->step;
        }
        cur_node = cur_node->down;
    } while (cur_node);

    return add_step(step_num, "");
}

// Returns a pointer to the step node corresponding to step number, or nullptr
// if no such step node exists.
// Always returns the bottommost step node with that step number
StepList::StepNode *StepList::get_node(int step_num) {
    auto node = top_left;
    while (node and node->step_num != step_num) {
        while (node->right and node->right->step_num <= step_num) {
            node = node->right;
        }
        if (node->down) {
            node = node->down;
        }
    }
    while (node and node->down) {
        node = node->down;
    }
    return node;
}

void StepList::swap_steps(int swap1, int swap2) {
    auto step1 = get_step(swap1), step2 = get_step(swap2);
    std::swap(*step1, *step2);
}

// Swaps a range of steps, unless the two ranges overlap, or they aren't the
// same length. Returns the new position of step.
int StepList::swap_range(int start1, int end1, int start2, int end2, int step) {
    if (start1 > end1) {
        std::swap(start1, end1);
    }
    if (start2 > end2) {
        std::swap(start2, end2);
    }

    // Check to see if the ranges to be swapped overlap or are different lengths
    if ((start1 <= end2 and start2 <= end1) or (end1 - start1 != end2 - start2)) {
        return step;
    }
    int len = end1 - start1 + 1;
    for (int i = 0; i < len; i++) {
        swap_steps(start1 + i, start2 + i);
    }

    if (step >= start1 and step <= end1) {
        return step - start1 + start2;
    } else if (step >= start2 and step <= end2) {
        return step - start2 + start1;
    } else {
        return step;
    }
}

// Executes the instructions
void StepList::execute() {
    auto node = get_node(INT_MIN);
    var_map vars;

    while (node->right) {
        node = node->right;
        auto cur_step = node->step_num;

        if (std::get_if<Step::Output>(&node->step->command)) {
            std::wcout << (wchar_t) node->step_num;
        }
        else if (auto swap = std::get_if<Step::Swap>(&node->step->command)) {
            auto swap1 = swap->step1.get_step(vars, cur_step);
            auto swap2 = swap->step2.get_step(vars, cur_step);

            if (swap1 != INVALID_STEP and swap2 != INVALID_STEP) {
                swap_steps(swap1, swap2);
                if (cur_step == swap1) {
                    node = get_node(swap2);
                } else if (cur_step == swap2) {
                    node = get_node(swap1);
                }
            }
        }
        else if (auto range = std::get_if<Step::RangeSwap>(&node->step->command)) {
            auto start1 = range->start1.get_step(vars, cur_step);
            auto start2 = range->start2.get_step(vars, cur_step);
            auto end1 = range->end1.get_step(vars, cur_step);
            auto end2 = range->end2.get_step(vars, cur_step);
            if (start1 != INVALID_STEP and start2 != INVALID_STEP and
                end1 != INVALID_STEP and end2 != INVALID_STEP)
            {
                auto old_step = cur_step;
                cur_step = swap_range(start1, end1, start2, end2, cur_step);
                if (cur_step != old_step) {
                    node = get_node(cur_step);
                }
            }
        }
        else if (auto set = std::get_if<Step::Set>(&node->step->command)) {
            auto set_val = set->new_val.get_step(vars, cur_step);
            if (set_val != INVALID_STEP) {
                vars[set->name] = set_val;
            }
        }
        else if (auto replace = std::get_if<Step::Replace>(&node->step->command)) {
            auto to_replace = replace->to_replace.get_step(vars, cur_step);
            if (to_replace != INVALID_STEP) {
                *get_step(to_replace) = *replace->new_step;
            }
        }
    }
}
