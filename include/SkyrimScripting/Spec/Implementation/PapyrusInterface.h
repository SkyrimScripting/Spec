#pragma once

#undef GetObject

namespace SkyrimScripting::Spec::Implementation::PapyrusInterface {

    void Specification_Print(RE::BSScript::Internal::VirtualMachine*, const RE::VMStackID stackID, RE::Actor*, std::string text) {
        auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
        auto stack = vm->allRunningStacks.find(stackID);
        auto scriptName = stack->second->top->previousFrame->self.GetObject()->GetTypeInfo()->GetName();
        TestOutput::GetSingleton().Output(std::format("[{}] {}", scriptName, text));
    }

    bool BIND(RE::BSScript::IVirtualMachine* vm) {
        vm->RegisterFunction("Print", "Specification", Specification_Print);
        return true;
    }
}
