#pragma once

#define BANDIT_CONFIG_COLOR_ANSI

#include <bandit/bandit.h>
#include <spdlog/spdlog.h>

using namespace bandit;
using namespace snowhouse;

#define define_specs(...) go_bandit(__VA_ARGS__)
#define describe_specs(...) go_bandit([]() { describe(__VA_ARGS__); })

namespace SkyrimScripting::Spec::Papyrus {}

using namespace SkyrimScripting::Spec::Papyrus;
