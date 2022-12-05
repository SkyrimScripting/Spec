# GoogleTest CMake documentation
# http://google.github.io/googletest/quickstart-cmake.html
#
# Note: pulling the latest version of GoogleTest using FetchContent
#       is recommended. But, meh. You do you. I'm using vcpkg.

project(SkyrimScripting.Spec.Example.GoogleTest VERSION 0.0.1 LANGUAGES CXX)

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest)
