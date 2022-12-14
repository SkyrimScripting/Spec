#pragma once

#include <SkyrimScripting/Spec/Papyrus/SpecScriptDiscovery.h>

#include "SpecHelper.h"

describe_specs("SpecScriptDiscovery", []() {
    it("can get the names of scripts ending in _Spec", []() {
        auto papyrusPexScriptsFolder = "../../../../../Papyrus";
        auto scriptNames = SpecScriptDiscovery::DiscoverPapyrusScriptNames(papyrusPexScriptsFolder);
        AssertThat(scriptNames, Is().Not().Empty());
        AssertThat(scriptNames, Contains("SkySpec_Demo_Global_Spec"));
    });
});
