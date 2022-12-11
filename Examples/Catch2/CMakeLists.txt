
function(add_spec_suite TARGET)
    set(options)
    set(oneValueArgs MODS_FOLDER)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(SPEC_SUITE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    add_commonlibsse_plugin(${TARGET} SOURCES ${SOURCE})
    target_link_libraries(${TARGET} PRIVATE SkyrimScripting.Spec)
    target_compile_features(${TARGET} PRIVATE cxx_std_23)
    # Make sure we direct this to our own shipped PCH.h
    target_precompile_headers(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/Examples/GoogleTest/PCH.h)
    if(SPEC_SUITE_MODS_FOLDER)
        if(EXISTS "${SPEC_SUITE_MODS_FOLDER}")
            set(MOD_FOLDER "${SPEC_SUITE_MODS_FOLDER}/${TARGET}")
            set(DLL_FOLDER "${MOD_FOLDER}/SKSE/Plugins")
            message(STATUS "Plugin output directory: ${MOD_FOLDER}")
            add_custom_command(
                TARGET "${TARGET}"
                POST_BUILD
                COMMAND "${CMAKE_COMMAND}" -E make_directory    "${DLL_FOLDER}"
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${TARGET}>"     "${DLL_FOLDER}/$<TARGET_FILE_NAME:${TARGET}>"
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${TARGET}>" "${DLL_FOLDER}/$<TARGET_PDB_FILE_NAME:${TARGET}>"
                VERBATIM
            )
        endif()
    endif()
endfunction()







project(SkyrimScripting.Spec.Example.Catch2 VERSION 0.0.1 LANGUAGES CXX)

find_package(Catch2 CONFIG REQUIRED)

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES tests.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SkyrimScripting.Spec)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Examples/GoogleTest/PCH.h)

# add_spec_suite(
#     ${PROJECT_NAME}
#     MODS_FOLDER "C:/Users/mrowr/Dropbox/Skyrim Scripting/Projects/MO2 Mods Deploy Folder/"
#     SOURCES tests.cpp
# )
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)

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
