#pragma once

#include <atomic>

namespace {
	std::vector<std::string> EVENTS_FROM_PAPYRUS_TESTS;
	std::atomic<bool> papyrusHelperRegistered = false;

	void SkySpecRunnerSpecHelper_EventHappened(RE::StaticFunctionTag*, std::string somethingThatHappened) {
		EVENTS_FROM_PAPYRUS_TESTS.emplace_back(somethingThatHappened);
	}

	bool BindPapyrusHelper(RE::BSScript::IVirtualMachine* vm) {
		vm->RegisterFunction("EventHappened", "SkySpecRunnerSpecHelper", SkySpecRunnerSpecHelper_EventHappened);
		return true;
	}
}

void RegisterPapyrusHelper() {
	if (!papyrusHelperRegistered.exchange(true)) SKSE::GetPapyrusInterface()->Register(BindPapyrusHelper);
}

void ResetPapyrusHelper() { EVENTS_FROM_PAPYRUS_TESTS.clear(); }
std::vector<std::string>& GetEventsFromPapyrusTests() { return EVENTS_FROM_PAPYRUS_TESTS; }
