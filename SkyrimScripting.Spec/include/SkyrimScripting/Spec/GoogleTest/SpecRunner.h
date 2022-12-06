#pragma once

#include <gtest/gtest.h>

namespace SkyrimScripting::Spec::GoogleTest {

	void RunSpecs(const std::string& filter) {
		GTEST_FLAG_SET(filter, std::format("*{}*", filter));
		::testing::InitGoogleTest();
		RUN_ALL_TESTS();
	}
}
