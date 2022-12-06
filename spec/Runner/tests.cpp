#include "SpecHelper.h"
#include "PapyrusHelperSetup.h"

#define SPEC_RUN_IMMEDIATE
#define SPEC_EXIT_AFTER_RUN

#include <SkyrimScripting/Spec/Bandit.h>
#include <SkyrimScripting/Spec/Runner/SpecLookup.h>

constexpr auto INSTANCE_SPEC = "SpecExample_Spec";
constexpr auto GLOBAL_SPEC = "SpecExample_Global_Spec";

go_bandit([]() {
	describe("SpecRunImmediate", []() {
		before_each([&]() { RegisterPapyrusHelper(); });
		it("can get list of all .pex scripts ending in _Spec.pex", [&]() {
			auto scriptNames = SkyrimScripting::Spec::Runner::GetAllSpecScriptNames();
			AssertThat(scriptNames, Contains(INSTANCE_SPEC));
			AssertThat(scriptNames, Contains(GLOBAL_SPEC));
		});
	});
});
