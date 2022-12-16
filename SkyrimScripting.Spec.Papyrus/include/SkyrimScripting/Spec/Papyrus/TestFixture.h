#pragma once

#include <string>
#include <vector>

namespace SkyrimScripting::Spec::Papyrus {

    class TestFixture {
        std::string _scriptName;
        std::vector<std::string> _fixtureSetupFunctionNames;
        std::vector<std::string> _fixtureTeardownFunctionNames;
        std::vector<std::string> _setupFunctionNames;
        std::vector<std::string> _teardownFunctionNames;
        std::vector<std::string> _testCaseFunctionNames;

    public:
        TestFixture(const std::string& scriptName) : _scriptName(scriptName) {}

        auto& GetScriptName() { return _scriptName; }
        auto& GetFixtureSetupFunctionNames() { return _fixtureSetupFunctionNames; }
        auto& GetFixtureTeardownFunctionNames() { return _fixtureTeardownFunctionNames; }
        auto& GetSetupFunctionNames() { return _setupFunctionNames; }
        auto& GetTeardownFunctionNames() { return _teardownFunctionNames; }
        auto& GetTestCaseFunctionNames() { return _testCaseFunctionNames; }
    };
}