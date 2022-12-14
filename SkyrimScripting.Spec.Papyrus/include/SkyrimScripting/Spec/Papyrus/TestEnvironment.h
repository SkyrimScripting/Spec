#pragma once

#include <string>
#include <vector>

#include "SkyrimScripting/Spec/Papyrus/Logger.h"
#include "SkyrimScripting/Spec/Papyrus/TestSuite.h"
#include "SkyrimScripting/Spec/Papyrus/TestSuiteRunner.h"

namespace SkyrimScripting::Spec::Papyrus {

    class TestEnvironment {
        std::vector<TestSuite> _testSuites;

    public:
        void RunSpecScripts(std::vector<std::string> scriptNames) {
            TestSuite suite;
            for (auto& scriptName : scriptNames) suite.AddSpecScript(scriptName);
            _testSuites.emplace_back(std::move(suite));
            TestSuiteRunner::Run(suite);
        }
    };
}
