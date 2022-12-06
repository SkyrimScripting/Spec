#pragma once

namespace SkyrimScripting::Spec::Plugin {

	namespace TestRunEvent {
		enum Kind { Immediate, PluginsLoaded, ModsLoaded, GameStarted };
	}

	std::string GetTestFilterForEvent(TestRunEvent::Kind event) {
		switch (event) {
			case TestRunEvent::Immediate:
				return "SpecRunImmediate";
			case TestRunEvent::PluginsLoaded:
				return "SpecRunPluginsLoaded";
			case TestRunEvent::ModsLoaded:
				return "SpecRunModsLoaded";
			case TestRunEvent::GameStarted:
				return "SpecRunGameStart";
			default:
				return {};
		}
	}
}
