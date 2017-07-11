#include "steplist.hpp"
#include "string-things.hpp"
#include <fstream>
#include <iostream>
#include <optional>

// Returns a step list with steps from the file, returning nothing if there is
// a syntax error in the file.
std::optional<StepList> get_steps(std::ifstream &file) {
    std::string line;
    StepList steps;

    int cur_line = 1;
    while (std::getline(file, line)) {
        line = strip_whitespace(line);

        if (line.length() == 0)
            continue;

        auto step_start = line.find('.');
        if (step_start == std::string::npos) {
            std::cerr << "Error! Line " << cur_line
                      << " is not blank, but has no step number.\n";
            return std::nullopt;
        }
        else if (!is_number(line.substr(0, step_start))) {
            std::cerr << "Error! \"" << line.substr(0, step_start)
                      << "\" is not a valid line number.\n";
            return std::nullopt;
        }

        auto step_end = line.find('.', step_start + 1);
        if (step_end == std::string::npos) {
            std::cerr << "Error! Line " << cur_line
                      << " is not ended with a period.\n";
            return std::nullopt;
        }
        else if (step_end != line.length() - 1) {
            std::cerr << "Error! Excess characters found after first period on"
                      << " line " << cur_line << ".\n";
            return std::nullopt;
        }

        auto step_text = line.substr(step_start + 1, step_end - step_start - 1);
        auto step_num = std::stoi(line.substr(0, step_start));
        if (steps.add_step(step_num, to_lower(step_text))) {
            std::cerr << "Error! Step " << step_num
                      << " is defined multiple times.\n";
            return std::nullopt;
        }

        cur_line++;
    }

    return steps;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Please provide a SMATIMU file to use the interpreter.\n";
        return 1;
    }
    std::ifstream file{argv[1]};
    if (!file.is_open()) {
        std::cerr << "Unable to open \"" << argv[1] << "\".\n";
        return 1;
    }
    if (auto steps = get_steps(file)) {
        steps->execute();
        return 0;
    } else {
        return 1;
    }
}
