#pragma once

#include <RE/Skyrim.h>

#include "SkyrimScripting/Spec/Papyrus/IPapyrusVM.h"
#include "SkyrimScripting/Spec/Papyrus/Logger.h"

namespace SkyrimScripting::Spec::Papyrus::Internal {

    class PapyrusVMImpl : public IPapyrusVM {
        RE::BSScript::IVirtualMachine* vm;

        RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo> GetTypeInfo(const std::string& scriptName) {
            RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo> typeInfoPtr;
            vm->GetScriptObjectType(scriptName, typeInfoPtr);
            return typeInfoPtr;
        }

    public:
        PapyrusVMImpl() : vm(RE::BSScript::Internal::VirtualMachine::GetSingleton()) {}

        std::vector<std::string> GetGlobalFunctionNames(const std::string& scriptName) override {
            logger::info("Real - GetGlobalFunctionNames of {}", scriptName);
            std::vector<std::string> functionNames;
            auto typeInfo = GetTypeInfo(scriptName);
            auto functionCount = typeInfo->GetNumGlobalFuncs();
            auto functions = typeInfo->GetGlobalFuncIter();
            for (uint32_t i = 0; i < functionCount; i++) functionNames.emplace_back(functions[i].func->GetName());
            return functionNames;
        }
    };
}