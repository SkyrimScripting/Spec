#pragma once

#include <string>

#include "SkyrimScripting/Spec/Papyrus/Logger.h"
#include "SkyrimScripting/Spec/Papyrus/PapyrusVM.h"
#include "SkyrimScripting/Spec/Papyrus/TestFixture.h"

namespace SkyrimScripting::Spec::Papyrus {

    class SpecScriptLoader {
        IPapyrusVM& _vm;
        TestFixture& _fixture;

        SpecScriptLoader(TestFixture& fixture) : _fixture(fixture), _vm(GetPapyrusVM()) {}

        void Load() {
            logger::trace("Load()");
            auto& scriptName = _fixture.GetScriptName();
            auto globalFunctionNames = _vm.GetGlobalFunctionNames(scriptName);
            for (auto& fn : globalFunctionNames) logger::trace("global FUNCTION: {}", fn);
        }

    public:
        static TestFixture ScriptToFixture(const std::string& scriptName) {
            logger::info("Loading script {} ...", scriptName);
            TestFixture fixture{scriptName};
            SpecScriptLoader(fixture).Load();
            return fixture;
        }
    };
}
