#pragma once

#include <set>

namespace SkyrimScripting::Spec::Runner {

	std::set<std::string> GetAllSpecScriptNames() {
		std::set<std::string> names;
		for (auto& file : std::filesystem::directory_iterator("Data/Scripts"))
			if (file.path().string().ends_with("_Spec.pex")) names.emplace(file.path().stem().string());
		return names;
	}
}
