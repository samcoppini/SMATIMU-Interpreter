#ifndef STEP_LIST_HPP
#define STEP_LIST_HPP

#include "step.hpp"
#include <memory>
#include <string>

class StepList {
    private:
        // A node for a skiplist structure
        struct StepNode {
            int step_num;
            Step *step;
            StepNode *right, *down;
        };
        // The top left node in the skip list
        StepNode *top_left;

        Step *get_step(int step_num);
        StepNode *get_node(int step_num);

    public:
        StepList();
        StepList(StepList &&other);
        ~StepList();
        Step *add_step(int step_num, std::string step_text);
        void swap_steps(int step1, int step2);
        void execute();
};

#endif
