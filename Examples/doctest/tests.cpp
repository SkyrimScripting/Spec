// doctest documentation
// https://github.com/doctest/doctest#documentation

#define DOCTEST_CONFIG_IMPLEMENT

#include <doctest/doctest.h>

TEST_CASE("Hello World") { CHECK(69 == 420); }

// Providing your own main() function with doctest
// https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
int main(int argc, char **argv) {
	doctest::Context context;
	context.applyCommandLine(argc, argv);
	return context.run();
}
