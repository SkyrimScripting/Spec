#pragma once

#include <atomic>

namespace SkyrimScripting::Spec::Plugin {

	class CellFullyLoadedEventSink : public RE::BSTEventSink<RE::TESCellFullyLoadedEvent> {
		CellFullyLoadedEventSink() = default;
		~CellFullyLoadedEventSink() = default;
		CellFullyLoadedEventSink(const CellFullyLoadedEventSink&) = delete;
		CellFullyLoadedEventSink(CellFullyLoadedEventSink&&) = delete;
		CellFullyLoadedEventSink& operator=(const CellFullyLoadedEventSink&) = delete;
		CellFullyLoadedEventSink& operator=(CellFullyLoadedEventSink&&) = delete;
		std::atomic<bool> loaded = false;

	public:
		static CellFullyLoadedEventSink& GetSingleton() {
			static CellFullyLoadedEventSink singleton;
			return singleton;
		}

		RE::BSEventNotifyControl ProcessEvent(const RE::TESCellFullyLoadedEvent*,
											  RE::BSTEventSource<RE::TESCellFullyLoadedEvent>*) override {
			if (!loaded.exchange(true)) {
				std::cout << "Runnings SpecRunGameStart tests" << std::endl;
				SPEC_ADAPTER::RunSpecs(GetTestFilterForEvent(TestRunEvent::GameStarted));
#if defined(SPEC_EXIT_AFTER_RUN)
				std::cout << "Tests complete. Exiting. (Not exiting temporarily tho...)" << std::endl;
// SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
#endif
			}
			return RE::BSEventNotifyControl::kContinue;
		}
	};
}
