#pragma once

#include <catch2/catch_session.hpp>

namespace SkyrimScripting::Spec::Catch2 {

    class Catch2SessionWrapper {
        Catch2SessionWrapper() = default;
        ~Catch2SessionWrapper() = default;
        Catch2SessionWrapper(const Catch2SessionWrapper&) = delete;
        Catch2SessionWrapper(Catch2SessionWrapper&&) = delete;
        Catch2SessionWrapper& operator=(const Catch2SessionWrapper&) = delete;
        Catch2SessionWrapper& operator=(Catch2SessionWrapper&&) = delete;
    public:
        Catch::Session Catch2Session;

        void ResetSession() {
            std::cout << "Trying to reset Catch 2's session..." << std::endl;
            Catch2Session.configData().testsOrTags.clear();
            Catch2Session.configData().sectionsToRun.clear();
        }

        static Catch2SessionWrapper& GetSingleton() {
            static Catch2SessionWrapper singleton;
            return singleton;
        }
    };

    // Providing your own main() function with Catch2
    // https://github.com/catchorg/Catch2/blob/devel/docs/own-main.md#top
    //
    // Specifying which tests to run
    // https://github.com/catchorg/Catch2/blob/devel/docs/command-line.md#specifying-which-tests-to-run
    //
    void RunSpecs(const std::string& filter) {
        std::vector<std::string> args = {"", std::format("*{}*", filter)};

        // Generate `argc` and `argv`, combining inputs with `args` specified above.
        std::vector<char*> argv{};
        for (const auto& arg : args) argv.push_back((char*)arg.data());

        Catch2SessionWrapper::GetSingleton().ResetSession();
        Catch2SessionWrapper::GetSingleton().Catch2Session.run((int)argv.size(), argv.data());
    }
}
