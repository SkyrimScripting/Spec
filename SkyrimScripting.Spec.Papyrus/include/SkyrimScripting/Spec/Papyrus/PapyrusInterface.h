#pragma once

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

#include "SkyrimScripting/Spec/Papyrus/PapyrusInterface/SkySpec.h"

namespace SkyrimScripting::Spec::Papyrus::PapyrusInterface {
    bool BIND(RE::BSScript::IVirtualMachine* vm) {
        SkySpec::BIND(vm);
        return true;
    }

    void Setup() { SKSE::GetPapyrusInterface()->Register(BIND); }
}
