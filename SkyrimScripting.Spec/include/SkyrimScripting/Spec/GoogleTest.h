#pragma once

#include "SkyrimScripting/Spec/GoogleTest/SpecRunner.h"
#define SPEC_ADAPTER GoogleTest
#include "SkyrimScripting/Spec/GoogleTest/Macros.h"
#include "SkyrimScripting/Spec/Plugin.h"

class Haha {
public:
	Haha() { SkyrimScripting::Spec::Plugin::Configuration::TestCaseRunFunction = SkyrimScripting::Spec::GoogleTest::RunSpecs; }
};

Haha h;
