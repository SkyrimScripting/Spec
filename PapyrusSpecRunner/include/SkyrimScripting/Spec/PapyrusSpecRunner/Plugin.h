#pragma once

#include <SKSE/SKSE.h>

#include <iostream>
#include <string>
#include <Windows.h>

#include "SkyrimScripting/Spec/PapyrusSpecRunner/DiscoveredPapyrusSpecs.h"
#include "SkyrimScripting/Spec/PapyrusSpecRunner/SpecLookup.h"
#include "SkyrimScripting/Spec/PapyrusSpecRunner/CellFullyLoadedEventSink.h"

namespace SkyrimScripting::Spec::PapyrusSpecRunner {

    constexpr auto GAME_START_SCRIPT_ENV_VAR_NAME = "SPEC_GAME_START_SCRIPT";

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

    SKSEPluginLoad(const SKSE::LoadInterface* skse) {
        RedirectStdoutToFile();
        SKSE::Init(skse);
        
        DiscoveredPapyrusSpecScriptNames = GetAllSpecScriptNames();
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
            auto* eventSink = new CellFullyLoadedEventSink([]() {
                std::cout << "THIS WOULD RUN ALL PAPYRUS SPECS NOW!" << std::endl;
            });
            eventSource->AddEventSink(eventSink);
        }

        return true;
    }
}