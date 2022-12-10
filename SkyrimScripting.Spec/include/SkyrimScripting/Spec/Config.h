#pragma once

#include <functional>
#include <string>

// TODO - clean me up + move me into a namespace (use macros to work with these from tests!) or make nicer or something
namespace SkyrimScripting::Spec::Config {
    bool AnySpecsRunImmediately = false;
    bool AnySpecsRunAfterSKSEPluginsLoad = false;
    bool AnySpecsRunAfterModsLoad = false;
    bool AnySpecsRunAfterGameStart = false;

    bool DisableSpecsRunImmediately = false;
    bool DisableSpecsRunAfterSKSEPluginsLoad = false;
    bool DisableSpecsRunAfterModsLoad = false;
    bool DisableSpecsRunAfterGameStart = false;

    // XXX If we keep '::Config', please move all the functions out of here. Only scalar values.
    bool RunSpecsImmediately() { return AnySpecsRunImmediately && !DisableSpecsRunImmediately; }
    bool RunSpecsAfterSKSEPluginsLoad() {
        return AnySpecsRunAfterSKSEPluginsLoad && !DisableSpecsRunAfterSKSEPluginsLoad;
    }
    bool RunSpecsAfterModsLoad() { return AnySpecsRunAfterModsLoad && !DisableSpecsRunAfterModsLoad; }
    bool RunSpecsAfterGameStart() { return AnySpecsRunAfterGameStart && !DisableSpecsRunAfterGameStart; }
    bool AnySpecsConfiguredToRun() {
        return RunSpecsImmediately() || RunSpecsAfterSKSEPluginsLoad() || RunSpecsAfterModsLoad() ||
               RunSpecsAfterGameStart();
    }

    bool ExitGameAfterSpecs = false;
    std::string PathToScriptToRunOnMainMenuLoad_EnvVariable = "SPEC_GAME_START_SCRIPT";
    std::string PathToScriptToRunOnMainMenuLoad;
    std::function<void(const std::string& filter)> TestCaseRunFunction;
}
