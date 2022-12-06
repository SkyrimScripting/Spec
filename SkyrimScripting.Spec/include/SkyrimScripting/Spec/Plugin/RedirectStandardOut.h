#pragma once

namespace SkyrimScripting::Spec::Plugin {

	void RedirectStdoutToFile() {
		auto stdout_path = SKSE::log::log_directory();
		*stdout_path /= fmt::format("{}.test.log", SKSE::PluginDeclaration::GetSingleton()->GetName());
		freopen(stdout_path->string().c_str(), "w", stdout);
	}
}
