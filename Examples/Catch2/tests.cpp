// Catch2 documentation
// https://github.com/catchorg/Catch2

#include <catch2/catch_test_macros.hpp>

TEST_CASE("First Test Suite", "Hello World") { REQUIRE(69 == 420); }
TEST_CASE("Second Test Suite", "Goodnight Moon") { REQUIRE(111 == 222); }

#include <catch2/catch_session.hpp>

// Providing your own main() function with Catch2
// https://github.com/catchorg/Catch2/blob/devel/docs/own-main.md#top
int main(int _argc, char* _argv[]) {
	// Specifying which tests to run
	// https://github.com/catchorg/Catch2/blob/devel/docs/command-line.md#specifying-which-tests-to-run
	std::vector<std::string> args = {"", "*First*"};

	// Generate `argc` and `argv`, combining inputs with `args` specified above.
	std::vector<char*> argv{_argv + 1, _argv + _argc};
	for (const auto& arg : args) argv.push_back((char*)arg.data());

	return Catch::Session().run((int)argv.size(), argv.data());
}
