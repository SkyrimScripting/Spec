project(SkyrimScripting.Spec.Papyrus.Unit.Specs LANGUAGES CXX)

set(spec_cpp "// GENERATED - DO NOT EDIT\n#include \"SpecHelper.h\"\n#include \"specs.h\"\n")
file(GLOB_RECURSE spec_headers "${CMAKE_SOURCE_DIR}/SkyrimScripting.Spec.Papyrus/*.Spec.h")
foreach(spec ${spec_headers})
    file(RELATIVE_PATH spec "${CMAKE_SOURCE_DIR}/SkyrimScripting.Spec.Papyrus/include" "${spec}")
    string(CONCAT spec_cpp "${spec_cpp}" "#include \"${spec}\"\n")
endforeach()
file(WRITE specs.cpp "${spec_cpp}")

include(Bandit)

bandit_specs(${PROJECT_NAME} SOURCES specs.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/SkyrimScripting.Spec.Papyrus/include")
target_include_directories(${PROJECT_NAME} PUBLIC .)
