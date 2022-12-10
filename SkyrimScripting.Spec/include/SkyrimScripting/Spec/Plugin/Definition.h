#pragma once

#include <SKSE/SKSE.h>

#include "SkyrimScripting/Spec/Plugin/RedirectStandardOut.h"
#include "SkyrimScripting/Spec/Plugin/Runtime.h"

namespace SkyrimScripting::Spec::Plugin {

    SKSEPluginLoad(const SKSE::LoadInterface* skse) {
        RedirectStdoutToFile();
        SKSE::Init(skse);
        RunSpecs();
        return true;
    }
}