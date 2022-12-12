#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace SkyrimScripting::Spec::Papyrus {

    std::vector<std::string> GetSpecScriptScriptNames() {
        std::vector<std::string> scriptNames;
        for (auto& file : std::filesystem::directory_iterator("Data/Scripts"))
            if (file.path().string().ends_with("_Spec.pex"))
                scriptNames.emplace_back(file.path().stem().string().c_str());
        return scriptNames;
    }
}
