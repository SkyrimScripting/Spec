#pragma once

namespace SkyrimScripting::Spec::Implementation {
    
    class TestOutput {
        std::vector<std::string> _consoleOutputPendingConsoleOpen = {};
        bool                     _consoleHasBeenOpenedByPlayer    = false;

        TestOutput() = default;

    public:
        TestOutput(const TestOutput&) = delete;
        TestOutput &operator=(const TestOutput&) = delete;
        static TestOutput& GetSingleton() {
            static TestOutput sink;
            return sink;
        }

        void Output(std::string text) {
            logger::info("[Test Output] {}", text);
            if (_consoleHasBeenOpenedByPlayer)
                RE::ConsoleLog::GetSingleton()->Print(std::format("[Test Output] {}", text).c_str());
            else
                _consoleOutputPendingConsoleOpen.emplace_back(std::format("[Test Output] {}", text).c_str());
        }

        void Clear() {
            _consoleOutputPendingConsoleOpen.clear();
            _consoleHasBeenOpenedByPlayer = false;
        }

        void ConsoleOpen() {
            if (! _consoleHasBeenOpenedByPlayer) {
                // Print the whole buffer of messages that we've been holding onto!
                auto* consoleLog = RE::ConsoleLog::GetSingleton();
                while (_consoleOutputPendingConsoleOpen.size() > 0) {
                    consoleLog->Print(_consoleOutputPendingConsoleOpen.at(0).c_str());
                    _consoleOutputPendingConsoleOpen.erase(_consoleOutputPendingConsoleOpen.begin());
                }
            }
        }
    };
}
