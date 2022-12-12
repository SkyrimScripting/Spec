#pragma once

// Setup the global TestCaseRunFunction to use the GoogleTest SpecRunner
#include "SkyrimScripting/Spec/Config.h"
#include "SkyrimScripting/Spec/Catch2/SpecRunner.h"
#include "SkyrimScripting/Spec/Internal/FunctionRunner.h"

namespace SkyrimScripting::Spec::Catch2 {
    namespace {
        Internal::FunctionRunner initSpecRunner{[]() { Config::TestCaseRunFunction = RunSpecs; }};
    }
}