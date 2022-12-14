#pragma once

#include <string>
#include <vector>

#include "SkyrimScripting/Spec/Papyrus/TestFixture.h"

namespace SkyrimScripting::Spec::Papyrus {

    class TestSuite {
        std::vector<TestFixture> _testFixtures;

    public:
        void AddSpecScript(const std::string& scriptName) {
            logger::info("[TestSuite] Add Spec Script {}", scriptName);
        }
        auto& GetTestFixtures() { return _testFixtures; }
    };
}