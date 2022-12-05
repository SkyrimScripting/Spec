project(SkyrimScripting.Spec.Example.Catch2 VERSION 0.0.1 LANGUAGES CXX)

find_package(Catch2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)
