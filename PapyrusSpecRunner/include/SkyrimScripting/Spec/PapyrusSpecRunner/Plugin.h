#pragma once

#include <SKSE/SKSE.h>

#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#include <SkyrimScripting/Spec/Papyrus.h>
#include <SkyrimScripting/Spec/Internal/CellFullyLoadedEventSink.h>

namespace SkyrimScripting::Spec::PapyrusSpecRunner {

    constexpr auto GAME_START_SCRIPT_ENV_VAR_NAME = "SPEC_GAME_START_SCRIPT";

    std::vector<std::string> DiscoveredPapyrusSpecScriptNames;

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

    void ActuallyJustPrintOutTheNamesOfTestFunction(const std::string& scriptName) {
        auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();

        RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo> typeInfoPtr;
        vm->GetScriptObjectType(scriptName, typeInfoPtr);

        std::string testPrefix = "test";
        auto* typeInfo = typeInfoPtr.get();
        uint32_t globalFunctionCount = typeInfo->GetNumGlobalFuncs();
        auto* globalFunctions = typeInfo->GetGlobalFuncIter();
        for (uint32_t i = 0; i < globalFunctionCount; i++) {
            auto* function = globalFunctions[i].func.get();
            if (LowerCase(function->GetName().c_str()).starts_with(testPrefix)) {
                std::cout << std::format("FOUND TEST FUNCTION: {}", function->GetName().c_str()) << std::endl;
            }
        }
    }

    void ActuallyJustCallOneFunctionPlease() {
        auto scriptName = DiscoveredPapyrusSpecScriptNames.at(0);
        ActuallyJustPrintOutTheNamesOfTestFunction(scriptName);
    }

    void RunAllTheSpecScripts() {
        ActuallyJustCallOneFunctionPlease();
    }

    SKSEPluginLoad(const SKSE::LoadInterface* skse) {
        RedirectStdoutToFile();
        SKSE::Init(skse);
        DiscoveredPapyrusSpecScriptNames = Papyrus::GetSpecScriptScriptNames();
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
            SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* message){
                if (message->type == SKSE::MessagingInterface::kDataLoaded)
                    TryRunGameStartScript();
            });
            auto eventSourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
            auto eventSource = eventSourceHolder->GetEventSource<RE::TESCellFullyLoadedEvent>();
            auto* eventSink = new Internal::CellFullyLoadedEventSink([]() {
                RunAllTheSpecScripts();
            });
            eventSource->AddEventSink(eventSink);
        }

        return true;
    }
}
        