// GoogleTest documentation
// http://google.github.io/googletest/primer.html

#define SPEC_RUN_IMMEDIATE
// #define SPEC_RUN_PLUGINS_LOADED
#define SPEC_RUN_MODS_LOADED

#include <gtest/gtest.h>

TEST(SpecRunImmediate_TestSuite, CanGetPluginName) {
	auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
	EXPECT_EQ(pluginName, "SkyrimScripting.Spec.Example.GoogleTest");
}

TEST(SpecRunModsLoaded_TestSuite, CanGetTheNameOfAQuest) {
	auto* mainQuest = RE::TESForm::LookupByEditorID("MQ101");
	EXPECT_STREQ(mainQuest->GetName(), "Unbound");
}

void RunGoogleTests(const std::string& filter) {
	std::cout << std::format("[RunGoogleTests] filter:'{}'", filter) << std::endl;
	std::vector<std::string> args = {"", std::format("--gtest_filter=*{}*", filter)};
	std::vector<char*> argv;
	for (const auto& arg : args) argv.push_back((char*)arg.data());
	int argc = (int)argv.size();
	::testing::InitGoogleTest(&argc, argv.data());
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

void RedirectStdoutToFile() {
	auto stdout_path = SKSE::log::log_directory();
	*stdout_path /= fmt::format("{}.test.log", SKSE::PluginDeclaration::GetSingleton()->GetName());
	freopen(stdout_path->string().c_str(), "w", stdout);
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
	RedirectStdoutToFile();
	SKSE::Init(skse);

#if defined(SPEC_RUN_IMMEDIATE) || defined(SPEC_RUN_PLUGINS_LOADED) || defined(SPEC_RUN_MODS_LOADED) || \
	defined(SPEC_RUN_GAME_STARTED)
	std::cout << "Running tests" << std::endl;
#if defined(SPEC_RUN_IMMEDIATE)
	std::cout << "Running SpecRunImmediate tests" << std::endl;
	RunGoogleTests(GetTestFilterForEvent(TestRunEvent::Immediate));
#endif
#if defined(SPEC_RUN_PLUGINS_LOADED) || defined(SPEC_RUN_MODS_LOADED)
	SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* message) {
#if defined(SPEC_RUN_PLUGINS_LOADED)
		if (message->type == SKSE::MessagingInterface::kPostLoad) {
			std::cout << "Running SpecRunPluginsLoaded tests" << std::endl;
			RunGoogleTests(GetTestFilterForEvent(TestRunEvent::PluginsLoaded));
		}
#endif
#if defined(SPEC_RUN_MODS_LOADED)
		if (message->type == SKSE::MessagingInterface::kPostLoad) {
			std::cout << "Running SpecRunModsLoaded tests" << std::endl;
			RunGoogleTests(GetTestFilterForEvent(TestRunEvent::ModsLoaded));
		}
#endif
	});
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
