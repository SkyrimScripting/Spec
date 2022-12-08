#pragma once

#include "SkyrimScripting/Spec/Runner/RedirectStandardOut.h"
#include "SkyrimScripting/Spec/Runner/Runtime.h"

namespace SkyrimScripting::Spec::Runner {

	SKSEPluginLoad(const SKSE::LoadInterface* skse) {
		RedirectStdoutToFile();
		SKSE::Init(skse);
		RunSpecs();
		return true;
	}
}