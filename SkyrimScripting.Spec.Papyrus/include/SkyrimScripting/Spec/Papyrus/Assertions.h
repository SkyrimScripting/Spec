#pragma once

#include <format>
#include <iostream>
#include <string>

namespace SkyrimScripting::Spec::Papyrus::Assertions {

    void Assert(bool assertPassed, const std::string& failureMessage) {
        if (!assertPassed) std::cout << std::format("FAIL! '{}'", failureMessage) << std::endl;
    }
}
