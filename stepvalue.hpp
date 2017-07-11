#ifndef STEPVALUE_HPP
#define STEPVALUE_HPP

#include <climits>
#include <map>
#include <string>
#include <variant>

const int INVALID_STEP = INT_MIN;

using var_map = std::map<std::string, int>;

class StepValue {
    private:
        bool is_relative;
        std::variant<std::string, int> step_val;

    public:
        StepValue(const std::string &str);
        int get_step(const var_map &vars, int cur_step) const;
};

#endif
