#pragma once

#include <atomic>

std::vector<std::string> EVENTS_FROM_PAPYRUS_TESTS;

namespace {
	std::atomic<bool> papyrusHelperRegistered = false;

	void SkySpecRunnerSpecHelper_EventHappened(RE::StaticFunctionTag*, std::string somethingThatHappened) {
		EVENTS_FROM_PAPYRUS_TESTS.emplace_back(somethingThatHappened);
	}

	bool BindPapyrusHelper(RE::BSScript::IVirtualMachine* vm) {
		vm->RegisterFunction("EventHappened", "SkySpecRunnerSpecHelper", SkySpecRunnerSpecHelper_EventHappened);
	}
}

void RegisterPapyrusHelper() {
	if (!papyrusHelperRegistered.exchange(true)) SKSE::GetPapyrusInterface()->Register(BindPapyrusHelper);
}