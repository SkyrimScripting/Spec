project(PapyrusSpecRunner.Specs VERSION 0.0.1 LANGUAGES CXX)

find_path(BANDIT_INCLUDE_DIRS "bandit/adapters.h")
find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES tests.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${BANDIT_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
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
