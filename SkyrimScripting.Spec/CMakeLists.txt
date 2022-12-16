project(SkyrimScripting.Spec VERSION 0.0.1 LANGUAGES CXX)

include(CheckHeaderIncludes)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE CommonLibSSE::CommonLibSSE)

check_header_includes(
    HEADERS       include/*.h
    PACKAGES      GTest Catch2
    LIBRARIES     ${PROJECT_NAME} CommonLibSSE::CommonLibSSE Catch2::Catch2 GTest::gtest
    LIBRARY_PATHS bandit/adapters.h snowhouse/assert.h
    TEMP_DIR      "${CMAKE_SOURCE_DIR}/.tmp"
)
