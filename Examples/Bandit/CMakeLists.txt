project(SkyrimScripting.Spec.Example.Bandit VERSION 0.0.1 LANGUAGES CXX)

find_path(BANDIT_INCLUDE_DIRS "bandit/adapters.h")
find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")

add_executable(${PROJECT_NAME} tests.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${BANDIT_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
