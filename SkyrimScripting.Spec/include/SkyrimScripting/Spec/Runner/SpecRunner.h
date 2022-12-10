#pragma once

#include <RE/Skyrim.h>

#include <algorithm>
#include <functional>
#include <queue>

#include "SkyrimScripting/Spec/Runner/PapyrusTestFixture.h"

namespace SkyrimScripting::Spec::Runner {

    class PapyrusFunctionCallback : public RE::BSScript::IStackCallbackFunctor {
        std::function<void()> callback;
        void operator()(RE::BSScript::Variable result) override { callback(); }
        bool CanSave() const override { return false; }
        void SetObject(const RE::BSTSmartPointer<RE::BSScript::Object>&) override {}

    public:
        PapyrusFunctionCallback(std::function<void()> callback) : callback(callback) {}
    };

    std::string PapyrusTestQueue_CurrentScript;
    std::queue<std::string> PapyrusTestQueue_AllScripts;
    std::queue<std::string> PapyrusTestQueue_CurrentScriptFunctions;

    std::string LowerCase(const std::string& text) {
        std::string copy = text;
        std::transform(copy.begin(), copy.end(), copy.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return copy;
    }

    void EmptyCurrentScriptFunctions() {
        std::queue<std::string> newQueue;
        std::swap(PapyrusTestQueue_CurrentScriptFunctions, newQueue);
    }

    void AddScriptFunction(const std::string& functionName) {  // , bool isGlobal = true) {
        auto name = LowerCase(functionName);
        if (name.starts_with("test")) {
            //
        } else if (name.starts_with("setup")) {
            //
        } else if (name.starts_with("teardown")) {
            //
        }
    }

    // Do Global First
    void ReflectOnScriptFunctions(const std::string& scriptName) {
        EmptyCurrentScriptFunctions();
        auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
        RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo> typeInfoPtr;
        vm->GetScriptObjectType(scriptName, typeInfoPtr);
        auto* typeInfo = typeInfoPtr.get();
        auto globalFunctionCount = typeInfo->GetNumGlobalFuncs();
        auto globalFunctions = typeInfo->GetGlobalFuncIter();
        for (uint32_t i = 0; i < globalFunctionCount; i++) {
            auto* function = globalFunctions[i].func.get();
            // PapyrusTestQueue_CurrentScriptFunctions.push(function->GetName());
            AddScriptFunction(function->GetName().c_str());
        }
    }

    void RunPapyrusSpec(const std::string&) {}

    void RunPapyrusSpec() { RunPapyrusSpec(PapyrusTestQueue_CurrentScript); }

    void RunAllPapyrusSpecs() {
        // PapyrusTestQueue_AllScripts = GetAllSpecScriptNames();
        // if (!PapyrusTestQueue_AllScripts.empty()) {
        // 	std::cout << "Running Papyrus tests" << std::endl;
        // 	PapyrusTestQueue_CurrentScript = PapyrusTestQueue_AllScripts.front();
        // 	PapyrusTestQueue_AllScripts.pop();
        // 	RunPapyrusSpec();
        // }
    }
}
