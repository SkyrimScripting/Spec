// GoogleTest documentation
// http://google.github.io/googletest/primer.html

// To automatically run code on the Main Menu, you set set the SPEC_GAME_START_SCRIPT environment variable
// to an executable (e.g. a .bat file) or specify a path using the `spec_game_start_script` macro:
// spec_game_start_script("C:/path/to/main_manu.bat");

// This will auto-detect your test framework with support for
// GoogleTest, Catch2, doctest, and Bandit:
// #include <SkyrimScripting/Spec.h>

// Using explicit include (only because we import every vcpkg for all test
// frameworks, which doesn't allow the auto-detection to work for this project)
#include <SkyrimScripting/Spec/GoogleTest.h>

spec_exit_after_tests;

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
