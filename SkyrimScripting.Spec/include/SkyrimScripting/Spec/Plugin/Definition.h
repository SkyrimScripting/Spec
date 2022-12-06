#pragma once

namespace SkyrimScripting::Spec::Plugin {

	SKSEPluginLoad(const SKSE::LoadInterface* skse) {
		RedirectStdoutToFile();
		SKSE::Init(skse);
		RunSpecs();
		return true;
	}
}