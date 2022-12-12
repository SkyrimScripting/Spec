# GoogleTest CMake documentation
# http://google.github.io/googletest/quickstart-cmake.html
#
# Note: pulling the latest version of GoogleTest using FetchContent
#       is recommended. But, meh. You do you. I'm using vcpkg.

project(SkyrimScripting.Spec.Example.GoogleTest VERSION 0.0.1 LANGUAGES CXX)

include(Specs)
include(SKSE)

add_gtest_skse_specs(${PROJECT_NAME} SOURCES tests.cpp)
target_skyrim_mods_root(${PROJECT_NAME} "${DEPLOY_ROOT}")
