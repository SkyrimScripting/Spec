#pragma once

#include <format>

#include "SkyrimScripting/Spec/Internal/Macros.h"

#define SPEC_IMMEDIATE_TEST_CASE(test_case_name, ...) \
    _SPEC_ENABLE_SPECS_IMMEDIATE;                  \
    TEST_CASE(std::format("SpecRunImmediate {}", test_case_name), __VA_ARGS__)

#define SPEC_PLUGINS_LOADED_TEST_CASE(test_case_name, ...) \
    _SPEC_ENABLE_SPECS_SKSE_LOADED;                  \
    TEST_CASE(std::format("SpecRunPluginsLoaded_ {}", test_case_name), __VA_ARGS__)

#define SPEC_MODS_LOADED_TEST_CASE(test_case_name, ...) \
    _SPEC_ENABLE_SPECS_MODS_LOADED;                  \
    TEST_CASE(std::format("SpecRunModsLoaded {}", test_case_name), __VA_ARGS__)

#define SPEC_GAME_STARTED_TEST_CASE(test_case_name, ...) \
    _SPEC_ENABLE_SPECS_GAME_STARTED;                  \
    TEST_CASE(std::format("SpecRunGameStart {}", test_case_name), __VA_ARGS__)
