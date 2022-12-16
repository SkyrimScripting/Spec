#pragma once

#include <string>

#include "SkyrimScripting/Spec/Papyrus/Logger.h"
#include "SkyrimScripting/Spec/Papyrus/PapyrusVM.h"
#include "SkyrimScripting/Spec/Papyrus/TestFixture.h"
#include "SkyrimScripting/Spec/Papyrus/Util.h"

namespace SkyrimScripting::Spec::Papyrus {

    constexpr auto SPEC_FUNCTION_PREFIX_TEST_CASE = "test";
    // constexpr auto SPEC_FUNCTION_PREFIX_SETUP = "setup";
    // constexpr auto SPEC_FUNCTION_PREFIX_TEARDOWN = "tearDown";
    // constexpr auto SPEC_FUNCTION_PREFIX_FIXTURE_SETUP = "specsetup";
    // constexpr auto SPEC_FUNCTION_PREFIX_FIXTURE_TEARDOWN = "spectearDown";

    class SpecScriptLoader {
        IPapyrusVM& _vm;
        TestFixture& _fixture;

        SpecScriptLoader(TestFixture& fixture) : _vm(GetPapyrusVM()), _fixture(fixture) {}

        void Load() {
            logger::trace("Load()");
            auto& scriptName = _fixture.GetScriptName();
            auto globalFunctionNames = _vm.GetGlobalFunctionNames(scriptName);
            for (auto& fn : globalFunctionNames) {
                logger::trace("global FUNCTION: {}", fn);
                auto fnName = Util::LowerCase(fn);
                if (fnName.starts_with(SPEC_FUNCTION_PREFIX_TEST_CASE)) {
                    _fixture.GetTestCaseFunctionNames().emplace_back(fnName);
                }
            }
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
