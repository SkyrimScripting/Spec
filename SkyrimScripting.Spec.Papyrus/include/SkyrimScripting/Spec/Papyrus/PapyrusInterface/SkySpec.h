#pragma once

#include <RE/Skyrim.h>

namespace SkyrimScripting::Spec::Papyrus::PapyrusInterface::SkySpec {
    constexpr auto CLASS_NAME = "SkySpec";

    constexpr auto ASSERT_FN = "Assert";
    bool Assert(RE::BSScript::Internal::VirtualMachine*, const RE::VMStackID stackID, RE::StaticFunctionTag*,
                bool condition, std::string failureMessage) {
        return condition;
    }

    void BIND(RE::BSScript::IVirtualMachine* vm) { vm->RegisterFunction(ASSERT_FN, CLASS_NAME, Assert); }
}
