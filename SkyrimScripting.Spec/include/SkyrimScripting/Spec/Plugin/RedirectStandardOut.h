#pragma once

// TODO consolidate with the other version of this please

#include <SKSE/SKSE.h>

namespace SkyrimScripting::Spec::Plugin {

	void RedirectStdoutToFile() {
		auto stdout_path = SKSE::log::log_directory();
		*stdout_path /= fmt::format("{}.test.log", SKSE::PluginDeclaration::GetSingleton()->GetName());
		freopen(stdout_path->string().c_str(), "w", stdout);
	}
}
