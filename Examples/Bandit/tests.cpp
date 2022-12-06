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
	describe("First Test Suite", [](){
		it("hello world", [](){
			AssertThat(69, Equals(420));
		});
	});
	describe("Second Test Suite", [](){
		it("goodnight moon", [](){
			AssertThat(111, Equals(222));
		});
	});
});
// clang-format on

// Providing your own main() function with bandit
// https://banditcpp.github.io/bandit/writingtests.html#entry-point
int main(int _argc, char** _argv) {
	// bandit command-line options
	// https://banditcpp.github.io/bandit/runningtests.html
	std::vector<std::string> args = {"", "--only=First", "--reporter=spec", "--colorizer=off"};

	// Generate `argc` and `argv`, combining inputs with `args` specified above.
	std::vector<char*> argv{_argv + 1, _argv + _argc};
	for (const auto& arg : args) argv.push_back((char*)arg.data());

	return bandit::run((int)argv.size(), argv.data());
}
