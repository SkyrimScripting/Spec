// bandit documentation
// https://banditcpp.github.io/bandit/index.html

// snowhouse documentation
// https://github.com/banditcpp/snowhouse

#include <bandit/bandit.h>
#include <snowhouse/snowhouse.h>

using namespace bandit;
using namespace snowhouse;

// clang-format off
go_bandit([](){
	describe("My Test Suite", [](){
		it("hello world", [](){
			AssertThat(69, Equals(420));
		});
	});
});
// clang-format on

// Providing your own main() function with bandit
// https://banditcpp.github.io/bandit/writingtests.html#entry-point
int main(int argc, char **argv) { return bandit::run(argc, argv); }
