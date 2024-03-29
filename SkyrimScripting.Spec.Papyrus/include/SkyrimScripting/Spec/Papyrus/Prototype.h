#pragma once

// One file to rule them all! Just kidding, it's only during prototyping...

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
#include <Windows.h>

#include <atomic>
#include <filesystem>
#include <format>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "SkyrimScripting/Spec/Papyrus/PapyrusInterface.h"

namespace SkyrimScripting::Spec::Papyrus {

    class CellFullyLoadedEventSink : public RE::BSTEventSink<RE::TESCellFullyLoadedEvent> {
        std::function<void()> callback;
        std::atomic<bool> loaded = false;

    public:
        explicit CellFullyLoadedEventSink(std::function<void()> callback) : callback(callback) {}

        RE::BSEventNotifyControl ProcessEvent(const RE::TESCellFullyLoadedEvent*,
                                              RE::BSTEventSource<RE::TESCellFullyLoadedEvent>*) override {
            if (!loaded.exchange(true)) callback();
            return RE::BSEventNotifyControl::kContinue;
        }
    };

    constexpr auto GAME_START_SCRIPT_ENV_VAR_NAME = "SPEC_GAME_START_SCRIPT";

    std::vector<std::string> DiscoveredPapyrusSpecScriptNames;

    std::string CurrentScriptName;
    std::queue<std::string> FunctionNamesOnCurrentScriptToCall;
    std::queue<std::string> SpecScriptNames;

    void TryRunGameStartScript() {
        auto* scriptPath = std::getenv(GAME_START_SCRIPT_ENV_VAR_NAME);
        if (scriptPath) {
            std::cout << std::format("Running game start script: '{}'", scriptPath) << std::endl;
            WinExec(scriptPath, SW_HIDE);
        } else {
            std::cout << "No game start script found" << std::endl;
        }
    }

    void RedirectStdoutToFile() {
        auto stdout_path = SKSE::log::log_directory();
        *stdout_path /= fmt::format("{}.test.log", SKSE::PluginDeclaration::GetSingleton()->GetName());
        freopen(stdout_path->string().c_str(), "w", stdout);
    }

    std::string LowerCase(const std::string& text) {
        std::string copy = text;
        std::transform(copy.begin(), copy.end(), copy.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return copy;
    }

    void CallAnotherFunction() {
        // ...
    }

    void CallNextFunction();
    void RunNextTestScript();

    class PapyrusCallbackHandler : public RE::BSScript::IStackCallbackFunctor {
        ~PapyrusCallbackHandler() override = default;
        void operator()(RE::BSScript::Variable result) override { CallNextFunction(); }
        bool CanSave() const override { return false; }
        void SetObject(const RE::BSTSmartPointer<RE::BSScript::Object>&) override {}
    };

    void CallGlobalFunction(const std::string& scriptName, const std::string& functionName) {
        auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();

        RE::BSScript::ZeroFunctionArguments args;

        auto callbackPtr = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>{new PapyrusCallbackHandler()};
        vm->DispatchStaticCall(scriptName, functionName, &args, callbackPtr);
    }

    void CallNextFunction() {
        if (FunctionNamesOnCurrentScriptToCall.empty()) {
            std::cout << "Run Next Test Script" << std::endl;
            RunNextTestScript();
        } else {
            auto functionName = FunctionNamesOnCurrentScriptToCall.front();
            std::cout << std::format("Running function {}", functionName) << std::endl;
            FunctionNamesOnCurrentScriptToCall.pop();
            CallGlobalFunction(CurrentScriptName, functionName);
        }
    }

    void RunTestFunctionsOnNextScript() {
        auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();

        RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo> typeInfoPtr;
        vm->GetScriptObjectType(CurrentScriptName, typeInfoPtr);

        // Populate the Queue with function names from this script
        std::string testPrefix = "test";
        auto* typeInfo = typeInfoPtr.get();
        uint32_t globalFunctionCount = typeInfo->GetNumGlobalFuncs();
        auto* globalFunctions = typeInfo->GetGlobalFuncIter();
        for (uint32_t i = 0; i < globalFunctionCount; i++) {
            auto* function = globalFunctions[i].func.get();
            if (LowerCase(function->GetName().c_str()).starts_with(testPrefix)) {
                std::cout << std::format("Adding test function to queue: {}", function->GetName().c_str()) << std::endl;
                FunctionNamesOnCurrentScriptToCall.emplace(function->GetName().c_str());
            }
        }

        // Kick off the first function from this script
        CallNextFunction();
    }

    void RunNextTestScript() {
        if (SpecScriptNames.empty()) {
            std::cout << "No more scripts to run" << std::endl;
        } else {
            CurrentScriptName = SpecScriptNames.front();
            std::cout << std::format("Running script {}", CurrentScriptName) << std::endl;
            SpecScriptNames.pop();
            RunTestFunctionsOnNextScript();
        }
    }

    void ActuallyJustCallOneFunctionPlease() {
        for (auto& scriptName : DiscoveredPapyrusSpecScriptNames) SpecScriptNames.emplace(scriptName);
        RunNextTestScript();
    }

    void RunAllTheSpecScripts() { ActuallyJustCallOneFunctionPlease(); }

    std::vector<std::string> GetSpecScriptScriptNames() {
        std::vector<std::string> scriptNames;
        for (auto& file : std::filesystem::directory_iterator("Data/Scripts"))
            if (file.path().string().ends_with("_Spec.pex"))
                scriptNames.emplace_back(file.path().stem().string().c_str());
        return scriptNames;
    }

    SKSEPluginLoad(const SKSE::LoadInterface* skse) {
        RedirectStdoutToFile();
        SKSE::Init(skse);
        DiscoveredPapyrusSpecScriptNames = GetSpecScriptScriptNames();
        if (DiscoveredPapyrusSpecScriptNames.empty()) {
            std::cout << "No Papyrus specs discovered" << std::endl;
            std::cout << "For auto-detection of Papyrus specs, please name your Papyrus spec *_Spec.psc" << std::endl;
            std::cout << "Your script can either be global or extend from Specification" << std::endl;
        } else {
            std::cout << std::format("Found {} Papyrus spec scripts", DiscoveredPapyrusSpecScriptNames.size())
                      << std::endl;
            for (auto& scriptName : DiscoveredPapyrusSpecScriptNames) {
                std::cout << std::format("- {}", scriptName) << std::endl;
            }
            SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* message) {
                if (message->type == SKSE::MessagingInterface::kDataLoaded) {
                    // TODO test if this can run immediately before any messages or else during kPostLoad out of
                    // curiosity
                    SKSE::GetPapyrusInterface()->Register(PapyrusInterface::BIND);
                    // Run script!
                    TryRunGameStartScript();
                }
            });
            auto eventSourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
            auto eventSource = eventSourceHolder->GetEventSource<RE::TESCellFullyLoadedEvent>();
            auto* eventSink = new CellFullyLoadedEventSink([]() { RunAllTheSpecScripts(); });
            eventSource->AddEventSink(eventSink);
        }

        return true;
    }
}
