#ifndef STEP_HPP
#define STEP_HPP

#include <string>
#include <variant>

const int INVALID_STEP = -1;

class Step {
    friend class StepList;
    private:
        struct Swap {
            int step1, step2;
        };
        struct Output {};
        struct Nop {};

        std::variant<Swap, Output, Nop> command;
    public:
        Step(const std::string &str);
};

#endif
