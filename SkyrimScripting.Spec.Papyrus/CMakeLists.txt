project(SkyrimScripting.Spec.Papyrus VERSION 0.0.1 LANGUAGES CXX)

include(SKSE)

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES plugin.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_precompile_headers(${PROJECT_NAME} PUBLIC PCH.h)
target_skyrim_mods_root(${PROJECT_NAME} "${DEPLOY_ROOT}")
