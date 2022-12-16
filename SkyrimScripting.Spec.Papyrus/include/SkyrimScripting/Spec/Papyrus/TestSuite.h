#pragma once

#include <string>
#include <unordered_map>

#include "SkyrimScripting/Spec/Papyrus/SpecScriptLoader.h"
#include "SkyrimScripting/Spec/Papyrus/TestFixture.h"

namespace SkyrimScripting::Spec::Papyrus {

    class TestSuite {
        std::unordered_map<std::string, TestFixture> _testFixturesByScriptName;

    public:
        void AddSpecScript(const std::string& scriptName) {
            logger::info("[TestSuite] Add Spec Script {}", scriptName);
            _testFixturesByScriptName.insert_or_assign(scriptName, SpecScriptLoader::ScriptToFixture(scriptName));
        }
        auto& GetTestFixtures() { return _testFixturesByScriptName; }
        auto& GetTestFixture(const std::string& scriptName) { return _testFixturesByScriptName.at(scriptName); }
    };
}