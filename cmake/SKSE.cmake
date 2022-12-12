function(target_skyrim_mods_root TARGET MODS_ROOT_FOLDER)
	if(EXISTS "${MODS_ROOT_FOLDER}")
        set(MOD_FOLDER "${MODS_ROOT_FOLDER}/${PROJECT_NAME}")
        set(DLL_FOLDER "${MOD_FOLDER}/SKSE/Plugins")
        message(STATUS "${TARGET} SKSE output folder: ${DLL_FOLDER}")
        add_custom_command(
            TARGET "${TARGET}"
            POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E make_directory    "${DLL_FOLDER}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${TARGET}>"     "${DLL_FOLDER}/$<TARGET_FILE_NAME:${TARGET}>"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${TARGET}>" "${DLL_FOLDER}/$<TARGET_PDB_FILE_NAME:${TARGET}>"
            VERBATIM
        )
    else()
        message(STATUS "Skyrim mods root not found '${MODS_ROOT_FOLDER}'")
    endif()
endfunction()
