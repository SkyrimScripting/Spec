#pragma once

#if __has_include("gtest/gtest.h")
    #include "SkyrimScripting/Spec/GoogleTest.h"
#elif __has_include("bandit/bandit.h")
    #include "SkyrimScripting/Spec/Bandit.h"
#endif
