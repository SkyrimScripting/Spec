#pragma once

#include "SkyrimScripting/Spec/Internal/Macros.h"

#define TEST_IMMEDIATE(test_suite_name, test_name) \
    _SPEC_ENABLE_SPECS_IMMEDIATE;                  \
    TEST(SpecRunImmediate_##test_suite_name, test_name)
#define TEST_SKSE_LOADED(test_suite_name, test_name) \
    _SPEC_ENABLE_SPECS_SKSE_LOADED;                  \
    TEST(SpecRunPluginsLoaded_##test_suite_name, test_name)
#define TEST_MODS_LOADED(test_suite_name, test_name) \
    _SPEC_ENABLE_SPECS_MODS_LOADED;                  \
    TEST(SpecRunModsLoaded_##test_suite_name, test_name)
#define TEST_GAME_STARTED(test_suite_name, test_name) \
    _SPEC_ENABLE_SPECS_GAME_STARTED;                  \
    TEST(SpecRunGameStart_##test_suite_name, test_name)

#define TEST_IMMEDIATE_CASE(test_name) \
    _SPEC_ENABLE_SPECS_IMMEDIATE;      \
    TEST(SpecRunImmediate, test_name)
#define TEST_SKSE_LOADED_CASE(test_name) \
    _SPEC_ENABLE_SPECS_SKSE_LOADED;      \
    TEST(SpecRunPluginsLoaded, test_name)
#define TEST_MODS_LOADED_CASE(test_name) \
    _SPEC_ENABLE_SPECS_MODS_LOADED;      \
    TEST(SpecRunModsLoaded, test_name)
#define TEST_GAME_STARTED_CASE(test_name) \
    _SPEC_ENABLE_SPECS_GAME_STARTED;      \
    TEST(SpecRunGameStart, test_name)

#define TEST_F_IMMEDIATE(test_fixture, test_name) \
    _SPEC_ENABLE_SPECS_IMMEDIATE;                 \
    TEST_F(test_fixture, SpecRunImmediate_##test_name)
#define TEST_F_SKSE_LOADED(test_fixture, test_name) \
    _SPEC_ENABLE_SPECS_SKSE_LOADED;                 \
    TEST_F(test_fixture, SpecRunPluginsLoaded_##test_name)
#define TEST_F_MODS_LOADED(test_fixture, test_name) \
    _SPEC_ENABLE_SPECS_MODS_LOADED;                 \
    TEST_F(test_fixture, SpecRunModsLoaded_##test_name)
#define TEST_F_GAME_STARTED(test_fixture, test_name) \
    _SPEC_ENABLE_SPECS_GAME_STARTED;                 \
    TEST_F(test_fixture, SpecRunGameStart_##test_name)
