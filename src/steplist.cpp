#include "steplist.hpp"
#include "string-things.hpp"
#include <chrono>
#include <climits>
#include <iostream>
#include <random>
#include <set>
#include <utility>
#include <vector>

StepList::StepList() {
    top_left = new StepNode{INT_MIN, new Step{""}, nullptr, nullptr};
}

StepList::StepList(const StepList &other) {
    copy_nodes(other);
}

StepList& StepList::operator=(const StepList &other) {
    if (this != &other) {
        delete_nodes();
        copy_nodes(other);
    }
    return *this;
}

StepList::StepList(StepList &&other) {
    top_left = other.top_left;
    other.top_left = new StepNode{INT_MIN, new Step{""}, nullptr, nullptr};
}

StepList& StepList::operator=(StepList &&other) {
    if (this != &other) {
        delete_nodes();
        top_left = other.top_left;
        other.top_left = new StepNode{INT_MIN, new Step{""}, nullptr, nullptr};
    }
    return *this;
}

StepList::~StepList() {
    delete_nodes();
}

// Frees all the nodes in the skiplist
void StepList::delete_nodes() {
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

// Copies all of the nodes present in another skiplist to this skiplist
void StepList::copy_nodes(const StepList &other) {
    std::vector<StepNode *> other_left_nodes;
    std::vector<StepNode *> new_left_nodes;
    StepNode *cur_node = other.top_left;

    Step *blank_step = new Step{""};
    while (cur_node) {
        other_left_nodes.push_back(cur_node);
        auto new_node = new StepNode{INT_MIN, blank_step, nullptr, nullptr};
        if (not new_left_nodes.empty()) {
            new_left_nodes.back()->down = new_node;
        }
        new_left_nodes.push_back(new_node);
        cur_node = cur_node->down;
    }
    top_left = new_left_nodes.front();
    auto height = other_left_nodes.size();

    cur_node = other_left_nodes.back()->right;
    while (cur_node != nullptr) {
        Step *new_step = new Step{*cur_node->step};
        auto step_num = cur_node->step_num;
        StepNode *prev_node = nullptr;

        for (size_t i = 0; i < height; i++) {
            auto index = height - 1 - i;
            auto next_in_line = other_left_nodes[index]->right;
            if (not next_in_line or next_in_line->step_num != step_num) {
                break;
            }
            auto new_node = new StepNode{step_num, new_step, nullptr, prev_node};
            new_left_nodes[index]->right = new_node;
            other_left_nodes[index] = next_in_line;
            new_left_nodes[index] = new_node;
            prev_node = new_node;
        }
        cur_node = cur_node->right;
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
Step *StepList::add_step(int step_num, const std::string &step_text) {
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
    std::size_t height = 0;
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

// Executes a step node, returning the location of the step after its execution
int StepList::execute_step(var_map &vars, const StepNode *node) {
    auto cur_step = node->step_num;
    auto command = &node->step->command;

    if (std::get_if<Step::Output>(command)) {
        std::wcout << (wchar_t) node->step_num;
    }
    else if (auto swap = std::get_if<Step::Swap>(command)) {
        auto swap1 = swap->step1.get_step(vars, cur_step);
        auto swap2 = swap->step2.get_step(vars, cur_step);

        if (swap1 != INVALID_STEP and swap2 != INVALID_STEP) {
            swap_steps(swap1, swap2);
            if (cur_step == swap1) {
                return swap2;
            } else if (cur_step == swap2) {
                return swap1;
            }
        }
    }
    else if (auto range = std::get_if<Step::RangeSwap>(command)) {
        auto start1 = range->start1.get_step(vars, cur_step);
        auto start2 = range->start2.get_step(vars, cur_step);
        auto end1 = range->end1.get_step(vars, cur_step);
        auto end2 = range->end2.get_step(vars, cur_step);

        if (start1 != INVALID_STEP and end1 != INVALID_STEP and
            start2 != INVALID_STEP and end2 != INVALID_STEP)
        {
            return swap_range(start1, end1, start2, end2, cur_step);
        }
    }
    else if (auto set = std::get_if<Step::Set>(command)) {
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

    return cur_step;
}

// Executes the instructions
void StepList::execute() {
    auto node = get_node(INT_MIN);
    var_map vars;

    while (node->right) {
        node = node->right;
        auto old_step = node->step_num;
        auto new_step = execute_step(vars, node);
        if (old_step != new_step) {
            node = get_node(new_step);
        }
    }
}

void StepList::execute_with_debugger() {
    auto node = get_node(INT_MIN);
    std::set<int> breakpoints;
    std::string command, last_command;
    bool paused = true, output_cur_line = true;
    var_map vars;

    std::wcout << "Welcome to the SMATIMU debugger.\n"
               << "Type \"help\" for a list of commands.\n";

    if (not node->right) {
        std::wcout << "No instructions loaded.\n";
    }

    auto do_step = [&] () {
        node = node->right;
        auto old_step = node->step_num;
        auto new_step = execute_step(vars, node);
        if (old_step != new_step) {
            node = get_node(new_step);
        }
    };

    while (node->right) {
        if (output_cur_line) {
            std::cout << node->right->step_num << ". "
                      << static_cast<std::string>(*node->right->step) << "\n";
        }
        output_cur_line = true;
        std::wcout << ">> ";
        std::getline(std::cin, command);
        if (command.empty()) {
            command = last_command;
        }
        auto toks = split_tokens(command);
        if (tokens_match(toks, {"help"}) or tokens_match(toks, {"h"})) {
            output_cur_line = false;
            std::wcout << "help, h               Output this help screen\n"
                       << "continue, c           Resume program execution\n"
                       << "break [n], b [n]      Add a breakpoint on a given step\n"
                       << "print [n], p [n]      Print out a given step\n"
                       << "step, s               Execute a single step of the program\n"
                       << "quit, q               Exit the interpreter\n";
        }
        else if (tokens_match(toks, {"continue"}) or tokens_match(toks, {"c"})) {
            paused = false;
        } else if (tokens_match(toks, {"quit"}) or tokens_match(toks, {"q"})) {
            return;
        } else if (tokens_match(toks, {"step"}) or tokens_match(toks, {"s"})) {
            do_step();
        } else if (tokens_match(toks, {"break", ""}) or tokens_match(toks, {"b", ""})) {
            output_cur_line = false;
            StepValue step_val{toks[1]};
            auto step_num = step_val.get_step(vars, node->right->step_num);
            if (step_num == INVALID_STEP) {
                std::wcout << "Undefined variable!\n";
            } else {
                breakpoints.insert(step_num);
                std::wcout << "Breakpoint added for step " << step_num << ".\n";
            }
        } else if (tokens_match(toks, {"print", ""}) or tokens_match(toks, {"p", ""})) {
            output_cur_line = false;
            StepValue step_val{toks[1]};
            auto step_num = step_val.get_step(vars, node->right->step_num);

            if (step_num == INVALID_STEP) {
                std::wcout << "Undefined variable!\n";
            } else {
                auto out_node = get_step(step_num);
                auto string = static_cast<std::string>(*out_node);
                std::wstring wstring{string.begin(), string.end()};
                std::wcout << step_num << ". " << wstring << "\n";
            }
        } else {
            output_cur_line = false;
            if (strip_whitespace(command).size() > 0) {
                std::wcout << "Invalid command!\n";
                continue;
            }
        }

        last_command = command;

        while (not paused and node->right) {
            do_step();
            if (node->right and breakpoints.count(node->right->step_num)) {
                paused = true;
            }
        }
    }

    std::wcout << "Program execution ended.\n";
}
