#pragma once

#include <iostream>
#include <string>

#include "SkyrimScripting/Spec/Runner/DiscoveredPapyrusSpecs.h"
#include "SkyrimScripting/Spec/Runner/SpecLookup.h"
#include "SkyrimScripting/Spec/Runner/GameLoadedEvent.h"

namespace SkyrimScripting::Spec::Runner {

	void RunSpecs() {
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
			auto eventSource =
				RE::ScriptEventSourceHolder::GetSingleton()->GetEventSource<RE::TESCellFullyLoadedEvent>();
			eventSource->AddEventSink(&CellFullyLoadedEventSink::GetSingleton());
		}
	}
}
