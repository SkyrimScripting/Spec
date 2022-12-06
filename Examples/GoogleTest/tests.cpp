// GoogleTest documentation
// http://google.github.io/googletest/primer.html

#include <gtest/gtest.h>

TEST(FirstTestSuite, HelloWorld) { EXPECT_EQ(69, 420); }
TEST(SecondTestSuite, GoodnightMoon) { EXPECT_EQ(111, 222); }

// Providing your own main() function with GoogleTest
// http://google.github.io/googletest/primer.html#writing-the-main-function
int main(int _argc, char** _argv) {
	// Running a subset of the tests with GoogleTest
	// https://github.com/google/googletest/blob/main/docs/advanced.md#running-a-subset-of-the-tests
	std::vector<std::string> args = {"", "--gtest_filter=*First*"};

	// Generate `argc` and `argv`, combining inputs with `args` specified above.
	std::vector<char*> argv{_argv + 1, _argv + _argc};
	for (const auto& arg : args) argv.push_back((char*)arg.data());
	int argc = (int)argv.size();

	::testing::InitGoogleTest(&argc, argv.data());
	return RUN_ALL_TESTS();
}
