#pragma once

#if __has_include("gtest/gtest.h")
    #include "SkyrimScripting/Spec/GoogleTest.h"
#elif __has_include("bandit/bandit.h")
    #include "SkyrimScripting/Spec/Bandit.h"
#elif __has_include(<catch2/catch_test_macros.hpp>)
    #include "SkyrimScripting/Spec/Catch2.h"
#endif
