#pragma once

#include "SkyrimScripting/Spec/Config.h"
#include "SkyrimScripting/Spec/GoogleTest/Macros.h"
#include "SkyrimScripting/Spec/GoogleTest/SpecRunner.h"
#include "SkyrimScripting/Spec/Internal/FunctionRunner.h"
#include "SkyrimScripting/Spec/Plugin.h"

namespace SkyrimScripting::Spec::GoogleTest {
    namespace {
        Internal::FunctionRunner initSpecRunner{[]() { Config::TestCaseRunFunction = GoogleTest::RunSpecs; }};
    }
}
