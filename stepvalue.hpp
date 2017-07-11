#ifndef STEPVALUE_HPP
#define STEPVALUE_HPP

#include <climits>
#include <string>

const int INVALID_STEP = INT_MIN;

class StepValue {
    private:
        bool is_relative;
        int step_val;

    public:
        StepValue(const std::string &str);
        int get_step(int cur_step) const;
};

#endif
