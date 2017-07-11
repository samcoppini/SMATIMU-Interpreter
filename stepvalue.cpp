#include "stepvalue.hpp"
#include "string-things.hpp"

StepValue::StepValue(const std::string &str): is_relative(false) {
    if (str[0] == '-' or str[0] == '+') {
        is_relative = true;

        if (str.size() == 1) {
            return;
        }
    }
    bool is_var = not (is_relative ? is_number(str.substr(1)): is_number(str));
    if (is_var) {
        step_val = str;
    } else {
        step_val = std::stoi(str);
    }
}

// Returns the step that this step corresponds to, based on the current line if
// the step is relative,  and the currently defined variables if the step is
// based on a variable. Returns INVALID_STEP if the step value is not defined
int StepValue::get_step(const var_map &vars, int cur_step) const {
    if (auto int_val = std::get_if<int>(&step_val)) {
        if (is_relative) {
            return *int_val + cur_step;
        } else {
            return *int_val;
        }
    } else if (auto str_val = std::get_if<std::string>(&step_val)) {
        try {
            if (is_relative) {
                auto int_val = vars.at(str_val->substr(1));
                if (str_val->front() == '-') {
                    return cur_step - int_val;
                } else {
                    return cur_step + int_val;
                }
            } else {
                return vars.at(*str_val);
            }
        } catch (const std::out_of_range&) {
            return INVALID_STEP;
        }
    } else {
        return INVALID_STEP;
    }
}
