#pragma once

#include <bandit/bandit.h>
#include <snowhouse/snowhouse.h>

using namespace bandit;
using namespace snowhouse;

namespace SkyrimScripting::Spec::Bandit {

    void RunSpecs(const std::string& filter) {
        std::vector<std::string> args = {"", std::format("--only={}", filter), "--reporter=spec", "--colorizer=off"};
        std::vector<char*> argv;
        for (const auto& arg : args) argv.push_back((char*)arg.data());
        bandit::run((int)argv.size(), argv.data());
    }
}
