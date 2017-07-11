#ifndef STEP_HPP
#define STEP_HPP

#include "stepvalue.hpp"
#include "string-things.hpp"
#include <memory>
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
        struct Replace {
            StepValue to_replace;
            std::shared_ptr<Step> new_step;
        };
        struct Output {};
        struct Nop {};

        std::variant<Nop, Output, Swap, Set, Replace> command;
    public:
        Step(const tok_list &tokens);
        Step(const std::string &str);
        ~Step() {};
};

#endif
