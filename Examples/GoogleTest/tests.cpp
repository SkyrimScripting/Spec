// GoogleTest documentation
// http://google.github.io/googletest/primer.html

#define SPEC_RUN_IMMEDIATE
// #define SPEC_RUN_PLUGINS_LOADED
#define SPEC_RUN_MODS_LOADED
#define SPEC_RUN_GAME_STARTED
#define SPEC_EXIT_AFTER_RUN

// Specify via #define or set the SPEC_GAME_START_SCRIPT environment variable
// #define SPEC_GAME_START_SCRIPT R"(C:\Code\Skyrim Scripting Projects\Spec\coc)"

#include <SkyrimScripting/Spec.h>

TEST(SpecRunImmediate_TestSuite, CanGetPluginName) {
	// Getting the PluginDeclaration only works when the game is running
	// but it doens't have any other dependencies
	auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
	EXPECT_EQ(pluginName, "SkyrimScripting.Spec.Example.GoogleTest");
}

TEST(SpecRunModsLoaded_TestSuite, CanGetTheNameOfAQuest) {
	// Querying for Forms breaks unless mods data has been loaded (kDataLoaded)
	auto* mainQuest = RE::TESForm::LookupByEditorID("MQ101");
	EXPECT_STREQ(mainQuest->GetName(), "Unbound");
}

TEST(SpecRunModsLoaded_TestSuite, CanGetReturnTypeOfPapyrusFunction) {
	// Interacting with the VM... hmm... let's find out?
	// Actually, this works without the game running because it's only introspection.
	auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
	ASSERT_TRUE(vm != nullptr);

	RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo> typeInfo;
	vm->GetScriptObjectType("Actor", typeInfo);
	ASSERT_TRUE(typeInfo.get() != nullptr);

	auto* functions = typeInfo.get()->GetMemberFuncIter();
	auto functionCount = typeInfo.get()->GetNumMemberFuncs();
	auto functionName = RE::BSFixedString("GetCrimeFaction");
	RE::BSTSmartPointer<RE::BSScript::IFunction> Actor_getCrimeFaction;
	for (uint32_t i = 0; i < functionCount; i++) {
		if (functions[i].func->GetName() == functionName) {
			Actor_getCrimeFaction = functions[i].func;
			break;
		}
	}
	ASSERT_TRUE(Actor_getCrimeFaction.get() != nullptr);

	// Actor.GetCrimeFaction returns a Faction
	ASSERT_STREQ(Actor_getCrimeFaction.get()->GetReturnType().GetTypeInfo()->GetName(), "Faction");
}

TEST(SpecRunGameStart_TestSuite, CanGetPlayersCurrentLocation) {
	// Get the player's current location? Hmm, it probably has a default?
	auto* player = RE::TESForm::LookupByID(0x14)->As<RE::TESObjectREFR>();
	EXPECT_TRUE(player != nullptr);

	auto location = player->GetCurrentLocation();
	EXPECT_TRUE(location != nullptr);
	EXPECT_STREQ(location->GetFullName(), "Riverwood");
}
