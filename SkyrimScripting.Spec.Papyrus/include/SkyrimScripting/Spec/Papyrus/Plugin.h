#pragma once

#include <SKSE/SKSE.h>

#include "SkyrimScripting/Spec/Papyrus/GameSession.h"
#include "SkyrimScripting/Spec/Papyrus/Logging.h"

namespace SkyrimScripting::Spec::Papyrus {

    SKSEPluginLoad(const SKSE::LoadInterface* skse) {
        SKSE::Init(skse);
        SetupLog();
        GameSession::GetSingleton().Initialize();
        return true;
    }
}
