#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace SkyrimScripting::Spec::Papyrus::SpecScriptDiscovery {

    constexpr auto DATA_SCRIPTS_PATH = "Data/Scripts";
    constexpr auto SCRIPT_FILENAME_SUFFIX = "_Spec.pex";

    std::vector<std::string> DiscoverPapyrusScriptNames(const std::string& scriptsPath = DATA_SCRIPTS_PATH) {
        std::vector<std::string> scriptNames;
        for (auto& file : std::filesystem::directory_iterator(scriptsPath))
            if (file.path().string().ends_with(SCRIPT_FILENAME_SUFFIX))
                scriptNames.emplace_back(file.path().stem().string().c_str());
        return scriptNames;
    }
}
