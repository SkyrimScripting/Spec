#pragma once

#include <bandit/bandit.h>

#include "SkyrimScripting/Spec/Bandit/Macros.h"
#include "SkyrimScripting/Spec/Bandit/SpecRunner.h"
#include "SkyrimScripting/Spec/Config.h"
#include "SkyrimScripting/Spec/Internal/FunctionRunner.h"
#include "SkyrimScripting/Spec/Plugin.h"

namespace SkyrimScripting::Spec::Bandit {
	namespace {
		Internal::FunctionRunner initSpecRunner{[]() { Config::TestCaseRunFunction = Bandit::RunSpecs; }};
	}
}

// using namespace SkyrimScripting::Spec::Bandit;
