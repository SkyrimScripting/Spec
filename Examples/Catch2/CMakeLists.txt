project(SkyrimScripting.Spec.Example.Catch2 VERSION 0.0.1 LANGUAGES CXX)

include(Specs)
include(SKSE)

add_catch2_skse_specs(${PROJECT_NAME} SOURCES tests.cpp)
target_skyrim_mods_root(${PROJECT_NAME} "${DEPLOY_ROOT}")
