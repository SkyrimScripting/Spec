// GoogleTest documentation
// http://google.github.io/googletest/primer.html

#include "gtest/gtest.h"

TEST(MyTestSuite, HelloWorld) { EXPECT_EQ(69, 420); }

// http://google.github.io/googletest/primer.html#writing-the-main-function
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
