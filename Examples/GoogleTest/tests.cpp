// GoogleTest documentation
// http://google.github.io/googletest/primer.html

#include <gtest/gtest.h>

TEST(FirstTestSuite, HelloWorld) {
	auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
	EXPECT_EQ(pluginName, "SkyrimScripting.Spec.Example.GoogleTest");

	// If not kDataLoaded, this gets:
	// unknown file: error: SEH exception with code 0xc0000005 thrown in the test body.
	// auto* mainQuest = RE::TESForm::LookupByEditorID("MQ101");
	// EXPECT_STREQ(mainQuest->GetName(), "Unbound");
}
TEST(SecondTestSuite, GoodnightMoon) { EXPECT_EQ(111, 222); }

void RedirectStdoutToFile() {
	auto stdout_path = SKSE::log::log_directory();
	*stdout_path /= fmt::format("{}.test.log", SKSE::PluginDeclaration::GetSingleton()->GetName());
	freopen(stdout_path->string().c_str(), "w", stdout);
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
	RedirectStdoutToFile();
	SKSE::Init(skse);
	std::cout << "Running tests..." << std::endl;

	// Run GoogleTest
	std::vector<std::string> args = {"", "--gtest_filter=*First*"};
	std::vector<char*> argv;
	for (const auto& arg : args) argv.push_back((char*)arg.data());
	int argc = (int)argv.size();
	::testing::InitGoogleTest(&argc, argv.data());
	RUN_ALL_TESTS();

	return true;
}
