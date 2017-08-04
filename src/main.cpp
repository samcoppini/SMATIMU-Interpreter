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

    int cur_line = 0;
    while (std::getline(file, line)) {
        cur_line++;

        line = strip_whitespace(line);

        if (line.length() == 0)
            continue;

        auto step_start = line.find('.');
        if (step_start == std::string::npos) {
            std::cerr << "Error! Line " << cur_line
                      << " is not blank, but has no step number.\n";
            return std::nullopt;
        }
        else if (!is_number(line.substr(0, step_start)) or
                 line.substr(0, step_start) == "0")
        {
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
        if (not steps.add_step(step_num, to_lower(step_text))) {
            std::cerr << "Error! Step " << step_num
                      << " is defined multiple times.\n";
            return std::nullopt;
        }
    }

    return std::move(steps);
}

int main(int argc, char *argv[]) {
    bool debug_mode = false;
    std::string file_name;

    for (int i = 1; i < argc; i++) {
        std::string arg{argv[i]};
        if (arg[0] == '-') {
            if (arg == "--debug" or arg == "-d") {
                debug_mode = true;
            } else {
                std::cerr << "Unknown command line argument \"" << arg << "\".\n";
                return 1;
            }
        } else {
            if (file_name != "") {
                std::cerr << "Please provide only one SMATIMU file at a time.\n";
                return 1;
            } else {
                file_name = arg;
            }
        }
    }

    if (file_name == "") {
        std::cerr << "Please provide a SMATIMU file to use the interpreter.\n";
        return 1;
    }

    std::ifstream file{file_name};
    if (!file.is_open()) {
        std::cerr << "Unable to open \"" << file_name << "\".\n";
        return 1;
    }
    if (auto steps = get_steps(file)) {
        if (debug_mode) {
            steps->execute_with_debugger();
        } else {
            steps->execute();
        }
        return 0;
    } else {
        return 1;
    }
}
