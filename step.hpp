#ifndef STEP_HPP
#define STEP_HPP

#include "stepvalue.hpp"
#include <variant>

class Step {
    friend class StepList;
    private:
        struct Swap {
            StepValue step1, step2;
        };
        struct Set {
            std::string name;
            StepValue new_val;
        };
        struct Output {};
        struct Nop {};

        std::variant<Nop, Output, Swap, Set> command;
    public:
        Step(const std::string &str);
};

#endif
