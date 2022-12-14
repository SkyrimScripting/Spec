#pragma once

#include <string>
#include <unordered_map>

#include "SkyrimScripting/Spec/Papyrus/TestSuite.h"

namespace SkyrimScripting::Spec::Papyrus {

    class TestEnvironment {
        std::unordered_map<std::string, TestSuite> _testSuites;

    public:
        void Initialize() { logger::info("Init TestEnvironment"); }
        void RunSpecs() { logger::info("RunSpecs()"); }
    };
}
