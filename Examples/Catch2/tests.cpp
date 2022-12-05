// Catch2 documentation
// https://github.com/catchorg/Catch2

#include <catch2/catch_test_macros.hpp>

TEST_CASE("My Test Suite", "Hello World") { REQUIRE(69 == 420); }

#include <catch2/catch_session.hpp>

// Providing your own main() function with Catch2
// https://github.com/catchorg/Catch2/blob/devel/docs/own-main.md#top
int main(int argc, char* argv[]) { return Catch::Session().run(argc, argv); }
