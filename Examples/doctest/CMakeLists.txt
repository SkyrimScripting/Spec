project(SkyrimScripting.Spec.Example.doctest VERSION 0.0.1 LANGUAGES CXX)

find_package(doctest CONFIG REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest)
