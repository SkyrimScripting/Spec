#pragma once

namespace SkyrimScripting::Spec::Implementation::PapyrusInterface {

    // TODO - use VMStackID to get the name of the test the output is coming from!
    void Specification_Print(RE::BSScript::Internal::VirtualMachine*, const RE::VMStackID, RE::Actor*, std::string text) {
        TestOutput::GetSingleton().Output(text);
    }

    bool BIND(RE::BSScript::IVirtualMachine* vm) {
        vm->RegisterFunction("Print", "Specification", Specification_Print);
        return true;
    }
}
