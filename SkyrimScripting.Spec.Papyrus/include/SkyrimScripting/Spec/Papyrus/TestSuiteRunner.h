#pragma once

#include <vector>

#include "SkyrimScripting/Spec/Papyrus/Logger.h"
#include "SkyrimScripting/Spec/Papyrus/TestSuite.h"

namespace SkyrimScripting::Spec::Papyrus {

    class TestSuiteRunner {
        static std::vector<TestSuiteRunner> _activeRunners;

        TestSuite& _testSuite;

        TestSuiteRunner(TestSuite& suite) : _testSuite(suite) {}

        void RunTestSuite() { logger::info("RUN TEST SUITE"); }

    public:
        static void Run(TestSuite& suite) {
            auto runner = TestSuiteRunner(suite);
            _activeRunners.emplace_back(std::move(runner));
            runner.RunTestSuite();
        }
    };

    std::vector<TestSuiteRunner> TestSuiteRunner::_activeRunners;
}
