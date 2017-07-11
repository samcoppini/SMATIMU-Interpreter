#include "stepvalue.hpp"
#include "string-things.hpp"

StepValue::StepValue(const std::string &str) {
    if (str[0] == '-' or str[0] == '+') {
        is_relative = true;
    } else {
        is_relative = false;
    }
    if (!is_relative) {
        if (!is_number(str)) {
            step_val = INVALID_STEP;
        } else {
            step_val = std::stoi(str);
        }
    } else {
        if (str.size() <= 1 or not is_number(str.substr(1))) {
            step_val = INVALID_STEP;
        } else {
            step_val = std::stoi(str.substr(1));
            if (str[0] == '-') {
                step_val = -step_val;
            }
        }
    }
}

int StepValue::get_step(int cur_step) const {
    if (step_val == INVALID_STEP) {
        return INVALID_STEP;
    } else if (is_relative) {
        return cur_step + step_val;
    } else {
        return step_val;
    }
}
