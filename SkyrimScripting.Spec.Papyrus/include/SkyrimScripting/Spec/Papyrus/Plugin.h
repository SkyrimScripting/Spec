#pragma once

#include <SKSE/SKSE.h>

namespace SkyrimScripting::Spec::Papyrus {

    void RedirectStdoutToFile() {
        auto stdout_path = SKSE::log::log_directory();
        *stdout_path /= fmt::format("{}.test.log", SKSE::PluginDeclaration::GetSingleton()->GetName());
        freopen(stdout_path->string().c_str(), "w", stdout);
    }

    SKSEPluginLoad(const SKSE::LoadInterface* skse) {
        SKSE::Init(skse);

        RedirectStdoutToFile();

        return true;
    }
}
