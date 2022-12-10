#pragma once

// Setup the global TestCaseRunFunction to use the GoogleTest SpecRunner
#include "SkyrimScripting/Spec/Config.h"
#include "SkyrimScripting/Spec/GoogleTest/SpecRunner.h"
#include "SkyrimScripting/Spec/Internal/FunctionRunner.h"

namespace SkyrimScripting::Spec::GoogleTest {
    namespace {
        Internal::FunctionRunner initSpecRunner{[]() { Config::TestCaseRunFunction = GoogleTest::RunSpecs; }};
    }
}