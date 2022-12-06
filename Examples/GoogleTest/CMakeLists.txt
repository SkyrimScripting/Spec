# GoogleTest CMake documentation
# http://google.github.io/googletest/quickstart-cmake.html
#
# Note: pulling the latest version of GoogleTest using FetchContent
#       is recommended. But, meh. You do you. I'm using vcpkg.

project(SkyrimScripting.Spec.Example.GoogleTest VERSION 0.0.1 LANGUAGES CXX)

find_package(GTest CONFIG REQUIRED)

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES tests.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE CommonLibSSE::CommonLibSSE)
target_link_libraries(${PROJECT_NAME} PRIVATE SkyrimScripting.Spec)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h)

if(DEPLOY_MOD)
	if(EXISTS "${DEPLOY_ROOT}")
        set(MOD_FOLDER "${DEPLOY_ROOT}/${PROJECT_NAME}")
        set(DLL_FOLDER "${MOD_FOLDER}/SKSE/Plugins")
        message(STATUS "Plugin output directory: ${MOD_FOLDER}")
        add_custom_command(
            TARGET "${PROJECT_NAME}"
            POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E make_directory    "${DLL_FOLDER}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>"     "${DLL_FOLDER}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "${DLL_FOLDER}/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"
            VERBATIM
        )
    endif()
endif()
