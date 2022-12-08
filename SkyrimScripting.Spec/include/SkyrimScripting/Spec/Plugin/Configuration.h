#pragma once

namespace SkyrimScripting::Spec::Plugin::Configuration {
	bool ExitGameAfterSpecs = false;
	std::string PathToScriptToRunOnMainMenuLoad;
	std::function<void(const std::string& filter)> TestCaseRunFunction;
}
