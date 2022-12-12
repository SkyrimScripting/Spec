#include <RE/Skyrim.h>
#include <catch2/catch_test_macros.hpp>
#include <SkyrimScripting/Spec/Catch2.h>

spec_exit_after_tests;

SPEC_IMMEDIATE_TEST_CASE("Skyrim Plugin Tests", "Can get the name of the current plugin") {
    // Getting the PluginDeclaration only works when the game is running
    // but it doens't have any other dependencies
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    REQUIRE( pluginName == "SkyrimScripting.Spec.Example.Catch2" );
}

SPEC_MODS_LOADED_TEST_CASE("Skyrim Form Tests", "Can get name of quest") {
    // Querying for Forms breaks unless mods data has been loaded (kDataLoaded)
    auto* mainQuest = RE::TESForm::LookupByEditorID("MQ101");
    REQUIRE( strcmp(mainQuest->GetName(), "Unbound") == 0 );
}

SPEC_GAME_STARTED_TEST_CASE("Tests in the game", "Can get player current location") {
    // Can only get the player's current location if the game is running
    auto* player = RE::TESForm::LookupByID(0x14)->As<RE::TESObjectREFR>();
    auto location = player->GetCurrentLocation();
    REQUIRE( strcmp(location->GetFullName(), "Riverwood") == 0 );
}
