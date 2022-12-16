#pragma once

#include <algorithm>
#include <string>

namespace SkyrimScripting::Spec::Papyrus::Util {

    std::string LowerCase(const std::string& text) {
        std::string copy = text;
        std::transform(copy.begin(), copy.end(), copy.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return copy;
    }
}
