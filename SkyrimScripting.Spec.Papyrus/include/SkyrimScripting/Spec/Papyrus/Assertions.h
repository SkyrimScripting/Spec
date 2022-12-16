#pragma once

#include <format>
#include <iostream>
#include <string>

#include "SkyrimScripting/Spec/Papyrus/Logger.h"

namespace SkyrimScripting::Spec::Papyrus::Assertions {

    void Assert(bool assertPassed, const std::string& failureMessage) {
        if (!assertPassed) logger::info("FAIL! '{}'", failureMessage);
    }
}
