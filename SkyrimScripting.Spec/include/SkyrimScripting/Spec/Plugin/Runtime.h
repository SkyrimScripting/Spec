#pragma once

#include "Windows.h"

namespace SkyrimScripting::Spec::Plugin {

	void RunSpecs() {
#if defined(SPEC_RUN_IMMEDIATE) || defined(SPEC_RUN_PLUGINS_LOADED) || defined(SPEC_RUN_MODS_LOADED) || \
	defined(SPEC_RUN_GAME_STARTED)
		std::cout << "Running tests" << std::endl;
#if defined(SPEC_RUN_IMMEDIATE)
		std::cout << "Running SpecRunImmediate tests" << std::endl;
		SPEC_ADAPTER::RunSpecs(GetTestFilterForEvent(TestRunEvent::Immediate));
#if defined(SPEC_EXIT_AFTER_RUN) && !defined(SPEC_RUN_PLUGINS_LOADED) && !defined(SPEC_RUN_MODS_LOADED) && \
	!defined(SPEC_RUN_GAME_STARTED)
		SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
#endif
#endif
#if defined(SPEC_RUN_PLUGINS_LOADED) || defined(SPEC_RUN_MODS_LOADED)
		SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* message) {
#if defined(SPEC_RUN_PLUGINS_LOADED)
			if (message->type == SKSE::MessagingInterface::kPostLoad) {
				std::cout << "Running SpecRunPluginsLoaded tests" << std::endl;
				SPEC_ADAPTER::RunSpecs(GetTestFilterForEvent(TestRunEvent::PluginsLoaded));
#if defined(SPEC_EXIT_AFTER_RUN) && !defined(SPEC_RUN_MODS_LOADED) && !defined(SPEC_RUN_GAME_STARTED)
				SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
#endif
			}
#endif
#if defined(SPEC_RUN_MODS_LOADED)
			if (message->type == SKSE::MessagingInterface::kDataLoaded) {
				std::cout << "Runnings SpecRunModsLoaded tests" << std::endl;
				SPEC_ADAPTER::RunSpecs(GetTestFilterForEvent(TestRunEvent::ModsLoaded));
#if defined(SPEC_EXIT_AFTER_RUN) && !defined(SPEC_RUN_GAME_STARTED)
				SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
#endif
#if defined(SPEC_RUN_GAME_STARTED)
#if defined(SPEC_GAME_START_SCRIPT)
				std::cout << std::format("Running game start script: '{}'", SPEC_GAME_START_SCRIPT) << std::endl;
				WinExec(SPEC_GAME_START_SCRIPT, SW_HIDE);
#else
				auto* scriptPath = std::getenv("SPEC_GAME_START_SCRIPT");
				if (scriptPath) {
					std::cout << std::format("Running game start script: '{}'", scriptPath) << std::endl;
					WinExec(scriptPath, SW_HIDE);
				} else {
					std::cout << "No game start script found" << std::endl;
				}
#endif
#endif
			}
#endif
		});
#if defined(SPEC_RUN_GAME_STARTED)
		auto eventSource = RE::ScriptEventSourceHolder::GetSingleton()->GetEventSource<RE::TESCellFullyLoadedEvent>();
		eventSource->AddEventSink(&CellFullyLoadedEventSink::GetSingleton());
#endif
#endif
#else
		std::cout << "No tests defined." << std::endl;
		std::cout << "Please add one or more of the following to your code:" << std::endl;
		std::cout << "#define SPEC_RUN_IMMEDIATE" << std::endl;
		std::cout << "#define SPEC_RUN_PLUGINS_LOADED" << std::endl;
		std::cout << "#define SPEC_RUN_MOD_LOADED" << std::endl;
		std::cout << "#define SPEC_RUN_GAME_STARTED" << std::endl;
#endif
	}
}
