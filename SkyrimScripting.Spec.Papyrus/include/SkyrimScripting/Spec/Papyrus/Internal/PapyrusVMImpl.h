#pragma once

#define ENABLE_SKYRIM_AE

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

        class PapyrusCallbackHandler : public RE::BSScript::IStackCallbackFunctor {
            std::function<void()> _callback;

        public:
            ~PapyrusCallbackHandler() override = default;
            PapyrusCallbackHandler(std::function<void()> callback) : _callback(callback) {}
            void operator()(RE::BSScript::Variable) override { _callback(); }
            bool CanSave() const override { return false; }
            void SetObject(const RE::BSTSmartPointer<RE::BSScript::Object>&) override {}
        };

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

        void InvokeGlobalFunction(const std::string& scriptName, const std::string& functionName,
                                  std::optional<std::function<void()>> callback) override {
            logger::info("Invoke Global Function {}::{}", scriptName, functionName);
            RE::BSScript::ZeroFunctionArguments args;
            if (callback) {
                RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callbackPtr{
                    new PapyrusCallbackHandler(callback.value())};
                vm->DispatchStaticCall(scriptName, functionName, &args, callbackPtr);
            } else {
                RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callbackPtr;
                vm->DispatchStaticCall(scriptName, functionName, &args, callbackPtr);
            }
        }
    };
}