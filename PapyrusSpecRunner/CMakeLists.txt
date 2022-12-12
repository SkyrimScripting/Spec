project(PapyrusSpecRunner VERSION 0.0.1 LANGUAGES CXX)

include(SKSE)

add_commonlibsse_plugin(
    ${PROJECT_NAME}
    NAME SkyrimScripting.Spec
    SOURCES plugin.cpp
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h)
target_link_libraries(${PROJECT_NAME} PRIVATE SkyrimScripting.Spec)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME SkyrimScripting.Spec)
target_skyrim_mods_root(${PROJECT_NAME} "${DEPLOY_ROOT}")
