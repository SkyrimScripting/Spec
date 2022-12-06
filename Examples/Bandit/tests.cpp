// bandit documentation
// https://banditcpp.github.io/bandit/index.html

// snowhouse documentation
// https://github.com/banditcpp/snowhouse

#define SPEC_RUN_IMMEDIATE
// #define SPEC_RUN_PLUGINS_LOADED
#define SPEC_RUN_MODS_LOADED
#define SPEC_RUN_GAME_STARTED
#define SPEC_EXIT_AFTER_RUN

// Specify via #define or set the SPEC_GAME_START_SCRIPT environment variable
// #define SPEC_GAME_START_SCRIPT R"(C:\Code\Skyrim Scripting Projects\Spec\coc)"

// This will auto-detect your test framework with support for
// GoogleTest, Catch2, doctest, and Bandit:
// #include <SkyrimScripting/Spec.h>

// Using explicit include (only because we import every vcpkg for all test
// frameworks, which doesn't allow the auto-detection to work for this project)
#include <SkyrimScripting/Spec/Bandit.h>

go_bandit([]() {
	describe("SpecRunImmediate", []() {
		it("can get plugin name", [&]() {
			// Getting the PluginDeclaration only works when the game is running
			// but it doens't have any other dependencies
			auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
			AssertThat(pluginName, Equals("SkyrimScripting.Spec.Example.Bandit"));
		});
	});
	describe("SpecRunModsLoaded", []() {
		it("can get the name of a quest", [&]() {
			// Querying for Forms breaks unless mods data has been loaded (kDataLoaded)
			auto* mainQuest = RE::TESForm::LookupByEditorID("MQ101");
			AssertThat(mainQuest->GetName(), Equals("Unbound"));
		});
	});
	describe("SpecRunGameStart", []() {
		it("can get player current location", [&]() {
			// Can only get the player's current location if the game is running
			auto* player = RE::TESForm::LookupByID(0x14)->As<RE::TESObjectREFR>();
			auto location = player->GetCurrentLocation();
			AssertThat(location->GetFullName(), Equals("Riverwood"));
		});
	});
});
