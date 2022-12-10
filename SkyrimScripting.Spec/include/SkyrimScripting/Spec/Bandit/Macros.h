#pragma once

#include <format>

#include "SkyrimScripting/Spec/Internal/Macros.h"

#define describe_immediate(desc, ...) describe(std::format("SpecRunImmediate {}", desc), __VA_ARGS__)
#define describe_on_plugins_load(desc, ...) describe(std::format("SpecRunPluginsLoaded {}" desc), __VA_ARGS__)
#define describe_on_mods_load(desc, ...) describe(std::format("SpecRunModsLoaded {}", desc), __VA_ARGS__)
#define describe_on_game_start(desc, ...) describe(std::format("SpecRunGameStart {}", desc), __VA_ARGS__)

#define it_immediate(desc, ...) it(std::format("SpecRunImmediate {}", desc), __VA_ARGS__)
#define it_on_plugins_load(desc, ...) it(std::format("SpecRunPluginsLoaded {}" desc), __VA_ARGS__)
#define it_on_mods_load(desc, ...) it(std::format("SpecRunModsLoaded {}", desc), __VA_ARGS__)
#define it_on_game_start(desc, ...) it(std::format("SpecRunGameStart {}", desc), __VA_ARGS__)

#define go_spec_immediate(lambdaWithDefinitions) \
    _SPEC_ENABLE_SPECS_IMMEDIATE;                \
    go_bandit([]() { describe("SpecRunImmediate", lambdaWithDefinitions); });
#define go_spec_on_plugins_load(lambdaWithDefinitions) \
    _SPEC_ENABLE_SPECS_SKSE_LOADED;                    \
    go_bandit([]() { describe("SpecRunPluginsLoaded", lambdaWithDefinitions); });
#define go_spec_on_mods_load(lambdaWithDefinitions) \
    _SPEC_ENABLE_SPECS_MODS_LOADED;                 \
    go_bandit([]() { describe("SpecRunModsLoaded", lambdaWithDefinitions); });
#define go_spec_on_game_start(lambdaWithDefinitions) \
    _SPEC_ENABLE_SPECS_GAME_STARTED;                 \
    go_bandit([]() { describe("SpecRunGameStart", lambdaWithDefinitions); });

#define go_spec_immediate_describe(desc, ...) go_spec_immediate([](){ describe(desc, __VA_ARGS__); });
#define go_spec_on_plugins_load_describe(desc, ...) go_spec_on_plugins_load([](){ describe(desc, __VA_ARGS__); });
#define go_spec_on_mods_load_describe(desc, ...) go_spec_on_mods_load([](){ describe(desc, __VA_ARGS__); });
#define go_spec_on_game_start_describe(desc, ...) go_spec_on_game_start([](){ describe(desc, __VA_ARGS__); });
