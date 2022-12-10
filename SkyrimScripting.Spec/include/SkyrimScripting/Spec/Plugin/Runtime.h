#pragma once

#include <SKSE/SKSE.h>
#include <Windows.h>

#include "SkyrimScripting/Spec/Config.h"
#include "SkyrimScripting/Spec/Plugin/GameLoadedEvent.h"
#include "SkyrimScripting/Spec/Plugin/TestRunEvent.h"


namespace SkyrimScripting::Spec::Plugin {

	void TryExitSkyrim() {
		if (Config::ExitGameAfterSpecs) {
			std::cout << "Exiting Skyrim." << std::endl;
			SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
		}
	}

	void RunSpecStage(TestRunEvent::Kind event) { Config::TestCaseRunFunction(GetTestFilterForEvent(event)); }

	void RunSpecsImmediately() {
		if (!Config::RunSpecsImmediately()) return;
		std::cout << "Running SpecRunImmediate tests" << std::endl;
		RunSpecStage(TestRunEvent::Immediate);
		if (!Config::RunSpecsAfterSKSEPluginsLoad() && !Config::RunSpecsAfterModsLoad() &&
			!Config::RunSpecsAfterGameStart())
			TryExitSkyrim();
	}

	void RunSpecsAfterSKSEPluginsLoad() {
		if (!Config::RunSpecsAfterSKSEPluginsLoad()) return;
		std::cout << "Running SpecRunPluginsLoaded tests" << std::endl;
		RunSpecStage(TestRunEvent::PluginsLoaded);
		if (!Config::RunSpecsAfterModsLoad() && !Config::RunSpecsAfterGameStart()) TryExitSkyrim();
	}

	void RunSpecsAfterModsLoad() {
		if (!Config::RunSpecsAfterModsLoad()) return;
		std::cout << "Runnings SpecRunModsLoaded tests" << std::endl;
		RunSpecStage(TestRunEvent::ModsLoaded);
		if (!Config::RunSpecsAfterGameStart()) TryExitSkyrim();
	}

	void RunSpecsAfterGameStart() {
		if (!Config::RunSpecsAfterGameStart()) return;
		if (!Config::PathToScriptToRunOnMainMenuLoad.empty()) {
			std::cout << std::format("Running game start script: '{}'", Config::PathToScriptToRunOnMainMenuLoad)
					  << std::endl;
			WinExec(Config::PathToScriptToRunOnMainMenuLoad.c_str(), SW_HIDE);
		} else {
			auto* scriptPath = std::getenv(Config::PathToScriptToRunOnMainMenuLoad_EnvVariable.c_str());
			if (scriptPath) {
				std::cout << std::format("Running game start script: '{}'", scriptPath) << std::endl;
				WinExec(scriptPath, SW_HIDE);
			} else {
				std::cout << "No game start script found" << std::endl;
			}
		}
	}

	void RunSpecs() {
		if (!Config::AnySpecsConfiguredToRun()) {
			std::cout << "No tests defined." << std::endl;
			std::cout << "Please add one or more of the following to your code:" << std::endl;
			std::cout << "#define SPEC_RUN_IMMEDIATE" << std::endl;
			std::cout << "#define SPEC_RUN_PLUGINS_LOADED" << std::endl;
			std::cout << "#define SPEC_RUN_MOD_LOADED" << std::endl;
			std::cout << "#define SPEC_RUN_GAME_STARTED" << std::endl;
			TryExitSkyrim();
			return;
		}

		if (!Config::TestCaseRunFunction) {
			std::cout << "No test case runner defined" << std::endl;
			return;
		}

		std::cout << "Running tests" << std::endl;

		RunSpecsImmediately();

		SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* message) {
			if (message->type == SKSE::MessagingInterface::kPostLoad) {
				RunSpecsAfterSKSEPluginsLoad();
			} else if (message->type == SKSE::MessagingInterface::kDataLoaded) {
				RunSpecsAfterModsLoad();
				RunSpecsAfterGameStart();
			}
		});

		if (Config::RunSpecsAfterGameStart()) {
			auto eventSourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
			auto eventSource = eventSourceHolder->GetEventSource<RE::TESCellFullyLoadedEvent>();
			eventSource->AddEventSink(&CellFullyLoadedEventSink::GetSingleton());
		}
	}
}
