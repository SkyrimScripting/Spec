#pragma once

#include <RE/Skyrim.h>

#include <atomic>

#include "SkyrimScripting/Spec/Runner/SpecRunner.h"

namespace SkyrimScripting::Spec::Runner {

	class CellFullyLoadedEventSink : public RE::BSTEventSink<RE::TESCellFullyLoadedEvent> {
		CellFullyLoadedEventSink() = default;
		~CellFullyLoadedEventSink() = default;
		CellFullyLoadedEventSink(const CellFullyLoadedEventSink&) = delete;
		CellFullyLoadedEventSink(CellFullyLoadedEventSink&&) = delete;
		CellFullyLoadedEventSink& operator=(const CellFullyLoadedEventSink&) = delete;
		CellFullyLoadedEventSink& operator=(CellFullyLoadedEventSink&&) = delete;
		std::atomic<bool> testsRun = false;

	public:
		static CellFullyLoadedEventSink& GetSingleton() {
			static CellFullyLoadedEventSink singleton;
			return singleton;
		}

		RE::BSEventNotifyControl ProcessEvent(const RE::TESCellFullyLoadedEvent*,
											  RE::BSTEventSource<RE::TESCellFullyLoadedEvent>*) override {
			if (!testsRun.exchange(true)) RunAllPapyrusSpecs();
			return RE::BSEventNotifyControl::kContinue;
		}
	};
}
