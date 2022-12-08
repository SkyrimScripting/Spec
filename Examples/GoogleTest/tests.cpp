// GoogleTest documentation
// http://google.github.io/googletest/primer.html

#define SPEC_RUN_IMMEDIATE
// #define SPEC_RUN_PLUGINS_LOADED
// #define SPEC_RUN_MODS_LOADED
// #define SPEC_RUN_GAME_STARTED
#define SPEC_EXIT_AFTER_RUN

// Specify via #define or set the SPEC_GAME_START_SCRIPT environment variable
// #define SPEC_GAME_START_SCRIPT R"(C:\Code\Skyrim Scripting Projects\Spec\coc)"

// This will auto-detect your test framework with support for
// GoogleTest, Catch2, doctest, and Bandit:
// #include <SkyrimScripting/Spec.h>

// Using explicit include (only because we import every vcpkg for all test
// frameworks, which doesn't allow the auto-detection to work for this project)
#include <SkyrimScripting/Spec/GoogleTest.h>

TEST_IMMEDIATE_CASE(CanGetPluginName) {
	// Getting the PluginDeclaration only works when the game is running
	// but it doens't have any other dependencies
	auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
	EXPECT_EQ(pluginName, "SkyrimScripting.Spec.Example.GoogleTest");
}

TEST_MODS_LOADED_CASE(CanGetTheNameOfAQuest) {
	// Querying for Forms breaks unless mods data has been loaded (kDataLoaded)
	auto* mainQuest = RE::TESForm::LookupByEditorID("MQ101");
	EXPECT_STREQ(mainQuest->GetName(), "Unbound");
}

TEST_GAME_STARTED_CASE(CanGetPlayerCurrentLocation) {
	// Can only get the player's current location if the game is running
	auto* player = RE::TESForm::LookupByID(0x14)->As<RE::TESObjectREFR>();
	auto location = player->GetCurrentLocation();
	EXPECT_STREQ(location->GetFullName(), "Riverwood");
}
