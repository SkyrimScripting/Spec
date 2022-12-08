#pragma once

namespace SkyrimScripting::Spec::Plugin::EnabledRunStages {
	bool RunSpecsImmediately = true;
	bool RunSpecsAfterSKSEPluginsLoad = false;
	bool RunSpecsAfterModsLoad = false;
	bool RunSpecsAfterGameStart = false;
	bool AnyEnabled() { return RunSpecsImmediately || RunSpecsAfterSKSEPluginsLoad || RunSpecsAfterModsLoad || RunSpecsAfterGameStart; }
}
