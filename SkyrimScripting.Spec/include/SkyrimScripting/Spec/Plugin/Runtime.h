#pragma once

#include <Windows.h>

#include "SkyrimScripting/Spec/Plugin/Configuration.h"
#include "SkyrimScripting/Spec/Plugin/RunStages.h"
#include "SkyrimScripting/Spec/Plugin/TestRunEvent.h"


namespace SkyrimScripting::Spec::Plugin {

	void RunSpecs() {
		if (!EnabledRunStages::AnyEnabled()) {
			std::cout << "No tests defined." << std::endl;
			std::cout << "Please add one or more of the following to your code:" << std::endl;
			std::cout << "#define SPEC_RUN_IMMEDIATE" << std::endl;
			std::cout << "#define SPEC_RUN_PLUGINS_LOADED" << std::endl;
			std::cout << "#define SPEC_RUN_MOD_LOADED" << std::endl;
			std::cout << "#define SPEC_RUN_GAME_STARTED" << std::endl;
			return;
		}

		if (!Configuration::TestCaseRunFunction) {
			std::cout << "No test case runner defined" << std::endl;
			return;
		}

		std::cout << "Running tests" << std::endl;

		// Immediate
		if (EnabledRunStages::RunSpecsImmediately) {
			std::cout << "Running SpecRunImmediate tests" << std::endl;
			Configuration::TestCaseRunFunction(GetTestFilterForEvent(TestRunEvent::Immediate));
			if (Configuration::ExitGameAfterSpecs && !EnabledRunStages::RunSpecsAfterSKSEPluginsLoad && !EnabledRunStages::RunSpecsAfterModsLoad &&
				!EnabledRunStages::RunSpecsAfterGameStart) {
				std::cout << "Tests complete. Exiting." << std::endl;
				SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
			}
		}

		// // Listen for SKSE Messaging Interface messages if:
		// // - Run when SKSE plugins loaded
		// // - Run when Mods loaded
		// // - Run when game started
		// if EnabledRunStages::RunSpecsAfterSKSEPluginsLoad || EnabledRunStages::RunSpecsAfterModsLoad || EnabledRunStages::RunSpecsAfterGameStart
		// 		SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* message) {
		// 		// Check for kPostLoad if running when SKSE plugins Loaded
		// 		if EnabledRunStages
		// 			::RunSpecsAfterSKSEPluginsLoad if (message->type == SKSE::MessagingInterface::kPostLoad) {
		// 				std::cout << "Running SpecRunPluginsLoaded tests" << std::endl;
		// 				SPEC_ADAPTER::RunSpecs(GetTestFilterForEvent(TestRunEvent::PluginsLoaded));
		// 				if Configuration
		// 					::ExitGameAfterSpecs && !EnabledRunStages::RunSpecsAfterModsLoad &&
		// 						!EnabledRunStages::RunSpecsAfterGameStart std::cout << "Tests complete. Exiting." << std::endl;
		// 				SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
		// 			}
		// 			}
		// }

		// // Check for kDataLoaded if running when Mods loaded -or- when Game started
		// if EnabledRunStages
		// 	::RunSpecsAfterModsLoad || EnabledRunStages::RunSpecsAfterGameStart if (message->type == SKSE::MessagingInterface::kDataLoaded) {
		// 		// Run Mods Loaded, if any
		// 		if EnabledRunStages
		// 			::RunSpecsAfterModsLoad std::cout << "Runnings SpecRunModsLoaded tests" << std::endl;
		// 		SPEC_ADAPTER::RunSpecs(GetTestFilterForEvent(TestRunEvent::ModsLoaded));
		// 		if Configuration
		// 			::ExitGameAfterSpecs && !EnabledRunStages::RunSpecsAfterGameStart std::cout << "Tests complete. Exiting." << std::endl;
		// 		SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
		// 	}
		// }
		// // Kick off a start game script, for the game started scenario (if any script provided)
		// if EnabledRunStages
		// 	::RunSpecsAfterGameStart if !Configuration::PathToScriptToRunOnMainMenuLoad.empty() std::cout
		// 		<< std::format("Running game start script: '{}'", Configuration::PathToScriptToRunOnMainMenuLoad) << std::endl;
		// WinExec(Configuration::PathToScriptToRunOnMainMenuLoad, SW_HIDE);
		// }
		// else {
		// 	auto* scriptPath = std::getenv("Configuration::PathToScriptToRunOnMainMenuLoad");
		// 	if (scriptPath) {
		// 		std::cout << std::format("Running game start script: '{}'", scriptPath) << std::endl;
		// 		WinExec(scriptPath, SW_HIDE);
		// 	} else {
		// 		std::cout << "No game start script found" << std::endl;
		// 	}
		// }
		// }
		// }
		// }
		// });

		// if EnabledRunStages
		// 	::RunSpecsAfterGameStart auto eventSource = RE::ScriptEventSourceHolder::GetSingleton() -> GetEventSource<RE::TESCellFullyLoadedEvent>();
		// eventSource->AddEventSink(&CellFullyLoadedEventSink::GetSingleton());
		// }
		// }
		// }
		// else {
		// }
	}
}
