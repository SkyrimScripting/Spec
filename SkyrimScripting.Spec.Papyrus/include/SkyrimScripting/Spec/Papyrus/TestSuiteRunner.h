#pragma once

#include <queue>
#include <string>
#include <vector>

#include "SkyrimScripting/Spec/Papyrus/Logger.h"
#include "SkyrimScripting/Spec/Papyrus/PapyrusVM.h"
#include "SkyrimScripting/Spec/Papyrus/TestSuite.h"

namespace SkyrimScripting::Spec::Papyrus {

    class TestSuiteRunner {
        static std::vector<TestSuiteRunner> _activeRunners;

        IPapyrusVM& _vm;
        TestSuite& _testSuite;

        std::string _currentlyRunningTestFixture;
        std::string _currentlyRunningTestCase;

        std::queue<std::string> _testCaseQueue;
        std::queue<std::string> _testFixtureQueue;

        TestSuiteRunner(TestSuite& suite) : _vm(GetPapyrusVM()), _testSuite(suite) {
            logger::info("New TestSuiteRunner given TestSuite with {} fixtures", suite.GetTestFixtures().size());
        }

        void EnqueueTestFixtureCases(TestFixture& fixture) {
            for (auto& testCaseName : fixture.GetTestCaseFunctionNames()) {
                logger::info("QUEUE CASE {}", testCaseName);
                _testCaseQueue.push(testCaseName);
            }
        }

        void EnqueueTestFixtures() {
            logger::info("Enqueue. Test Suite has {} fixtures", _testSuite.GetTestFixtures().size());
            for (auto& [fixtureName, fixture] : _testSuite.GetTestFixtures()) {
                logger::info("QUEUE Script {}", fixtureName);
                _testFixtureQueue.push(fixtureName);
            }
        }

        void RunNextTestCase() {
            logger::info("Run Next Test Case");
            if (_testCaseQueue.empty()) {
                RunNextTestFixture();
                return;
            }
            _currentlyRunningTestCase = _testCaseQueue.front();
            _testCaseQueue.pop();
            logger::info("RUN TEST CASE {}::{}", _currentlyRunningTestFixture, _currentlyRunningTestCase);
            _vm.InvokeGlobalFunction(_currentlyRunningTestFixture, _currentlyRunningTestCase,
                                     [&]() { RunNextTestCase(); });
        }

        void RunNextTestFixture() {
            logger::info("Run Next Test Fixture");
            _currentlyRunningTestCase = "";
            if (_testFixtureQueue.empty()) return;
            _currentlyRunningTestFixture = _testFixtureQueue.front();
            _testFixtureQueue.pop();
            EnqueueTestFixtureCases(_testSuite.GetTestFixture(_currentlyRunningTestFixture));
            RunNextTestCase();
        }

        void RunTestSuite() {
            logger::info("RUN TEST SUITE");
            EnqueueTestFixtures();
            RunNextTestFixture();
        }

    public:
        static void Run(TestSuite& suite) {
            logger::info("Run() suite with {} fixtures", suite.GetTestFixtures().size());
            auto runner = TestSuiteRunner(suite);
            _activeRunners.emplace_back(std::move(runner));
            // _activeRunners.emplace_back(runner);
            // runner.RunTestSuite();
            _activeRunners.at(_activeRunners.size() - 1).RunTestSuite();
        }
    };

    std::vector<TestSuiteRunner> TestSuiteRunner::_activeRunners;
}
