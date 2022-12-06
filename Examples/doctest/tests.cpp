// doctest documentation
// https://github.com/doctest/doctest#documentation

#define DOCTEST_CONFIG_IMPLEMENT

#include <doctest/doctest.h>

TEST_CASE("First: Hello World") { CHECK(69 == 420); }
TEST_CASE("Second: Goodnight Moon") { CHECK(111 == 222); }

// Providing your own main() function with doctest
// https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
int main(int argc, char** argv) {
	// doctest command-line options
	// https://github.com/doctest/doctest/blob/master/doc/markdown/commandline.md
	doctest::Context context;
	context.addFilter("test-case", "*First*");
	context.applyCommandLine(argc, argv);
	return context.run();
}
