#pragma once

#include <string>
#include <vector>

namespace SkyrimScripting::Spec::Runner {

	class PapyrusTestFixture {
		std::vector<std::string> runBeforeEachSpec_functionNames;
		std::vector<std::string> runAfterEachSpec_functionNames;
		std::vector<std::string> runBeforeWholeScript_functionNames;
		std::vector<std::string> runAfterWholeScript_functionNames;
		std::vector<std::string> individualfunctionNames;
	};
}  // namespace SkyrimScripting::Spec::Runner
