#pragma once

#include "SkyrimScripting/Spec/Config.h"
#include "SkyrimScripting/Spec/Internal/FunctionRunner.h"

#define _SPEC_MACRO_CONCAT0(x, y) x##y
#define _SPEC_MACRO_CONCAT(x, y) _SPEC_MACRO_CONCAT0(x, y)
#define _SPEC_UNIQ_FUNCTIONRUNNER _SPEC_MACRO_CONCAT(_specfunctionRunner, __COUNTER__)

#define _SPEC_ENABLE_SPECS_IMMEDIATE                                           \
	SkyrimScripting::Spec::Internal::FunctionRunner _SPEC_UNIQ_FUNCTIONRUNNER{ \
		[]() { SkyrimScripting::Spec::Config::AnySpecsRunImmediately = true; }};

#define _SPEC_ENABLE_SPECS_SKSE_LOADED                                         \
	SkyrimScripting::Spec::Internal::FunctionRunner _SPEC_UNIQ_FUNCTIONRUNNER{ \
		[]() { SkyrimScripting::Spec::Config::AnySpecsRunAfterSKSEPluginsLoad = true; }};

#define _SPEC_ENABLE_SPECS_MODS_LOADED                                         \
	SkyrimScripting::Spec::Internal::FunctionRunner _SPEC_UNIQ_FUNCTIONRUNNER{ \
		[]() { SkyrimScripting::Spec::Config::AnySpecsRunAfterModsLoad = true; }};

#define _SPEC_ENABLE_SPECS_GAME_STARTED                                        \
	SkyrimScripting::Spec::Internal::FunctionRunner _SPEC_UNIQ_FUNCTIONRUNNER{ \
		[]() { SkyrimScripting::Spec::Config::AnySpecsRunAfterGameStart = true; }};

#define _SPEC_DISABLE_SPECS_IMMEDIATE                                          \
	SkyrimScripting::Spec::Internal::FunctionRunner _SPEC_UNIQ_FUNCTIONRUNNER{ \
		[]() { SkyrimScripting::Spec::Config::DisableSpecsRunImmediately = true; }};

#define _SPEC_DISABLE_SPECS_SKSE_LOADED                                        \
	SkyrimScripting::Spec::Internal::FunctionRunner _SPEC_UNIQ_FUNCTIONRUNNER{ \
		[]() { SkyrimScripting::Spec::Config::DisableSpecsRunAfterSKSEPluginsLoad = true; }};

#define _SPEC_DISABLE_SPECS_MODS_LOADED                                        \
	SkyrimScripting::Spec::Internal::FunctionRunner _SPEC_UNIQ_FUNCTIONRUNNER{ \
		[]() { SkyrimScripting::Spec::Config::DisableSpecsRunAfterModsLoad = true; }};

#define _SPEC_DISABLE_SPECS_GAME_STARTED                                       \
	SkyrimScripting::Spec::Internal::FunctionRunner _SPEC_UNIQ_FUNCTIONRUNNER{ \
		[]() { SkyrimScripting::Spec::Config::DisableSpecsRunAfterGameStart = true; }};

#define _SPEC_EXIT_AFTER_TESTS                                                 \
	SkyrimScripting::Spec::Internal::FunctionRunner _SPEC_UNIQ_FUNCTIONRUNNER{ \
		[]() { SkyrimScripting::Spec::Config::ExitGameAfterSpecs = true; }};

#define _SPEC_SET_GAME_START_SCRIPT(path)                                      \
	SkyrimScripting::Spec::Internal::FunctionRunner _SPEC_UNIQ_FUNCTIONRUNNER{ \
		[]() { SkyrimScripting::Spec::Config::PathToScriptToRunOnMainMenuLoad = path; }};

#define spec_run_immediate            \
	namespace {                       \
		_SPEC_ENABLE_SPECS_IMMEDIATE; \
	}
#define spec_run_on_skse_plugins_loaded \
	namespace {                         \
		_SPEC_ENABLE_SPECS_SKSE_LOADED; \
	}
#define spec_run_on_mods_loaded         \
	namespace {                         \
		_SPEC_ENABLE_SPECS_MODS_LOADED; \
	}
#define spec_run_on_game_start           \
	namespace {                          \
		_SPEC_ENABLE_SPECS_GAME_STARTED; \
	}

#define spec_disable_immediate         \
	namespace {                        \
		_SPEC_DISABLE_SPECS_IMMEDIATE; \
	}
#define spec_disable_on_skse_plugins_loaded \
	namespace {                             \
		_SPEC_DISABLE_SPECS_SKSE_LOADED;    \
	}
#define spec_disable_on_mods_loaded      \
	namespace {                          \
		_SPEC_DISABLE_SPECS_MODS_LOADED; \
	}
#define spec_disable_on_game_start        \
	namespace {                           \
		_SPEC_DISABLE_SPECS_GAME_STARTED; \
	}

#define spec_exit_after_tests   \
	namespace {                 \
		_SPEC_EXIT_AFTER_TESTS; \
	}

#define spec_game_start_script(path)       \
	namespace {                            \
		_SPEC_SET_GAME_START_SCRIPT(path); \
	}
