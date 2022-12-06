// GoogleTest documentation
// http://google.github.io/googletest/primer.html

#define SPEC_RUN_IMMEDIATE
// #define SPEC_RUN_PLUGINS_LOADED
#define SPEC_RUN_MODS_LOADED
#define SPEC_RUN_GAME_STARTED
#define SPEC_EXIT_AFTER_RUN

// Specify via #define or set the SPEC_GAME_START_SCRIPT environment variable
// #define SPEC_GAME_START_SCRIPT R"(C:\Code\Skyrim Scripting Projects\Spec\coc)"

#include <gtest/gtest.h>

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

void RunGoogleTests(std::string filter) {
	GTEST_FLAG_SET(filter, std::format("*{}*", filter));
	::testing::InitGoogleTest();
	RUN_ALL_TESTS();
}

enum TestRunEvent { Immediate, PluginsLoaded, ModsLoaded, GameStarted };

std::string GetTestFilterForEvent(TestRunEvent event) {
	switch (event) {
		case TestRunEvent::Immediate:
			return "SpecRunImmediate";
		case TestRunEvent::PluginsLoaded:
			return "SpecRunPluginsLoaded";
		case TestRunEvent::ModsLoaded:
			return "SpecRunModsLoaded";
		case TestRunEvent::GameStarted:
			return "SpecRunGameStart";
		default:
			return {};
	}
}

class CellFullyLoadedEventSink : public RE::BSTEventSink<RE::TESCellFullyLoadedEvent> {
	CellFullyLoadedEventSink() = default;
	~CellFullyLoadedEventSink() = default;
	CellFullyLoadedEventSink(const CellFullyLoadedEventSink&) = delete;
	CellFullyLoadedEventSink(CellFullyLoadedEventSink&&) = delete;
	CellFullyLoadedEventSink& operator=(const CellFullyLoadedEventSink&) = delete;
	CellFullyLoadedEventSink& operator=(CellFullyLoadedEventSink&&) = delete;
	std::atomic<bool> loaded = false;

public:
	static CellFullyLoadedEventSink& GetSingleton() {
		static CellFullyLoadedEventSink singleton;
		return singleton;
	}

	RE::BSEventNotifyControl ProcessEvent(const RE::TESCellFullyLoadedEvent*,
										  RE::BSTEventSource<RE::TESCellFullyLoadedEvent>*) override {
		if (!loaded.exchange(true)) {
			RunGoogleTests(GetTestFilterForEvent(TestRunEvent::GameStarted));
#if defined(SPEC_EXIT_AFTER_RUN)
			SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
#endif
		}
		return RE::BSEventNotifyControl::kContinue;
	}
};

void RedirectStdoutToFile() {
	auto stdout_path = SKSE::log::log_directory();
	*stdout_path /= fmt::format("{}.test.log", SKSE::PluginDeclaration::GetSingleton()->GetName());
	freopen(stdout_path->string().c_str(), "w", stdout);
}

#include "Windows.h"

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
	RedirectStdoutToFile();
	SKSE::Init(skse);

#if defined(SPEC_RUN_IMMEDIATE) || defined(SPEC_RUN_PLUGINS_LOADED) || defined(SPEC_RUN_MODS_LOADED) || \
	defined(SPEC_RUN_GAME_STARTED)
	std::cout << "Running tests" << std::endl;
#if defined(SPEC_RUN_IMMEDIATE)
	std::cout << "Running SpecRunImmediate tests" << std::endl;
	RunGoogleTests(GetTestFilterForEvent(TestRunEvent::Immediate));
#if defined(SPEC_EXIT_AFTER_RUN) && !defined(SPEC_RUN_PLUGINS_LOADED) && !defined(SPEC_RUN_MODS_LOADED) && \
	!defined(SPEC_RUN_GAME_STARTED)
	SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
#endif
#endif
#if defined(SPEC_RUN_PLUGINS_LOADED) || defined(SPEC_RUN_MODS_LOADED)
	SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* message) {
#if defined(SPEC_RUN_PLUGINS_LOADED)
		if (message->type == SKSE::MessagingInterface::kPostLoad) {
			std::cout << "Running SpecRunPluginsLoaded tests" << std::endl;
			RunGoogleTests(GetTestFilterForEvent(TestRunEvent::PluginsLoaded));
#if defined(SPEC_EXIT_AFTER_RUN) && !defined(SPEC_RUN_MODS_LOADED) && !defined(SPEC_RUN_GAME_STARTED)
			SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
#endif
		}
#endif
#if defined(SPEC_RUN_MODS_LOADED)
		if (message->type == SKSE::MessagingInterface::kDataLoaded) {
			std::cout << "Runnings SpecRunModsLoaded tests" << std::endl;
			RunGoogleTests(GetTestFilterForEvent(TestRunEvent::ModsLoaded));
#if defined(SPEC_EXIT_AFTER_RUN) && !defined(SPEC_RUN_GAME_STARTED)
			SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
#endif
#if defined(SPEC_RUN_GAME_STARTED)
#if defined(SPEC_GAME_START_SCRIPT)
			std::cout << std::format("Running game start script: '{}'", SPEC_GAME_START_SCRIPT) << std::endl;
			WinExec(SPEC_GAME_START_SCRIPT, SW_HIDE);
#else
			auto* scriptPath = std::getenv("SPEC_GAME_START_SCRIPT");
			if (scriptPath) {
				std::cout << std::format("Running game start script: '{}'", scriptPath) << std::endl;
				WinExec(scriptPath, SW_HIDE);
			} else {
				std::cout << "No game start script found" << std::endl;
			}
#endif
#endif
		}
#endif
	});
#if defined(SPEC_RUN_GAME_STARTED)
	auto eventSource = RE::ScriptEventSourceHolder::GetSingleton()->GetEventSource<RE::TESCellFullyLoadedEvent>();
	eventSource->AddEventSink(&CellFullyLoadedEventSink::GetSingleton());
#endif
#endif
#else
	std::cout << "No tests defined." << std::endl;
	std::cout << "Please add one or more of the following to your code:" << std::endl;
	std::cout << "#define SPEC_RUN_IMMEDIATE" << std::endl;
	std::cout << "#define SPEC_RUN_PLUGINS_LOADED" << std::endl;
	std::cout << "#define SPEC_RUN_MOD_LOADED" << std::endl;
	std::cout << "#define SPEC_RUN_GAME_STARTED" << std::endl;
#endif

	return true;
}
