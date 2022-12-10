#include "PapyrusHelperSetup.h"
#include "SpecHelper.h"

#define SPEC_RUN_IMMEDIATE
#define SPEC_RUN_MODS_LOADED
#define SPEC_RUN_GAME_STARTED
#define SPEC_EXIT_AFTER_RUN

#include <SkyrimScripting/Spec/Bandit.h>
#include <SkyrimScripting/Spec/Runner/SpecLookup.h>

constexpr auto INSTANCE_SPEC = "SpecExample_Spec";
constexpr auto GLOBAL_SPEC = "SpecExample_Global_Spec";
constexpr auto HELPER_SPEC = "SkySpecRunnerSpecHelper";
constexpr auto EVENT_TEST_FN = "JustCallTheSpecHelper";

go_bandit([]() {
    describe("SpecRunImmediate", []() {
        it("can get list of all .pex scripts ending in _Spec.pex", [&]() {
            auto scriptNames = SkyrimScripting::Spec::Runner::GetAllSpecScriptNames();
            AssertThat(scriptNames, Contains(INSTANCE_SPEC));
            AssertThat(scriptNames, Contains(GLOBAL_SPEC));
        });
    });
    describe("SpecRunModsLoaded", []() {
        it("all of our 3 scripts are actually loaded into the VM", [&]() {
            AssertThat(TypeExists(INSTANCE_SPEC), IsTrue());
            AssertThat(TypeExists(GLOBAL_SPEC), IsTrue());
            AssertThat(TypeExists(HELPER_SPEC), IsTrue());
        });
    });
    // Can't - because we need a test framework which supports WAITING for callbacks.
    // describe("SpecRunGameStart", []() {
    // 	before_each([&]() {
    // 		RegisterPapyrusHelper();
    // 		ResetPapyrusHelper();
    // 	});
    // 	it("can invoke a Papyrus function which saves an event in EVENTS_FROM_PAPYRUS_TESTS", [&]() {
    // 		auto& events = GetEventsFromPapyrusTests();
    // 		AssertThat(events.size(), Equals(0));
    // 		InvokeGlobalFunctionNoArgs(GLOBAL_SPEC, EVENT_TEST_FN);
    // 		AssertThat(events.size(), Equals(2));
    // 		AssertThat(events[0], Equals("FIRST!"));
    // 		AssertThat(events[0], Equals("SECOND!"));
    // 	});
    // });
});
