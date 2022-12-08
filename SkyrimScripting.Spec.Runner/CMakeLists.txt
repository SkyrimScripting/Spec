project(SkyrimScripting.Spec.Runner VERSION 0.0.1 LANGUAGES CXX)

add_commonlibsse_plugin(
    ${PROJECT_NAME}
    NAME SkyrimScripting.Spec
    SOURCES plugin.cpp
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h)
target_link_libraries(${PROJECT_NAME} PRIVATE SkyrimScripting.Spec)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME SkyrimScripting.Spec)

# TODO Shouldn't be necesary?
target_link_libraries(${PROJECT_NAME} PRIVATE CommonLibSSE::CommonLibSSE)

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
