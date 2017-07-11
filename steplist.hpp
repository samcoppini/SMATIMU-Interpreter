#ifndef STEP_LIST_HPP
#define STEP_LIST_HPP

#include <string>
#include <variant>
#include <vector>

class StepList {
    private:
        struct Step {
            struct Output {};
            struct Nop {};

            std::variant<Output, Nop> command;
            int step_num;
            Step(int step_num, const std::string &str);
        };
        std::vector<Step> steps;

    public:
        bool add_step(int step_num, std::string step_text);
        void execute();
};

#endif
