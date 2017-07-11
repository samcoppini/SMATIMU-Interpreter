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
        struct Output {};
        struct Nop {};

        std::variant<Nop, Output, Swap> command;
    public:
        Step(const std::string &str);
};

#endif
