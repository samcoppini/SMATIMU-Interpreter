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
        struct RangeSwap {
            StepValue start1, end1;
            StepValue start2, end2;
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

        std::variant<Nop, Output, Swap, RangeSwap, Set, Replace> command;
    public:
        Step(const tok_list &tokens);
        Step(const std::string &str);
        operator std::string() const;
        ~Step() {};
};

#endif
