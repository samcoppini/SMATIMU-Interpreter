#ifndef STEP_LIST_HPP
#define STEP_LIST_HPP

#include <string>
#include <vector>

class StepList {
    private:
        struct Step {
            int step_num;
            std::string step_text;
        };
        std::vector<Step> steps;

    public:
        bool add_step(int step_num, std::string step_text);
        void print() const;
};

#endif
