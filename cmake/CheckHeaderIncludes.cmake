function(check_header_includes)
    set(options)
    set(oneValueArgs TARGET INCLUDE_DIR TEMP_DIR)
    set(multiValueArgs HEADERS PACKAGES LIBRARY_PATHS LIBRARIES)
    cmake_parse_arguments(CHECK_HEADER_INCLUDES "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT CMAKE_OBJECT_PATH_MAX OR CMAKE_OBJECT_PATH_MAX LESS 1000)
        # Bump up the max object path or CMake can get angry with some generated paths
        # https://stackoverflow.com/questions/68351713/maximum-path-lengths-with-cmake
        set(CMAKE_OBJECT_PATH_MAX 1000 PARENT_SCOPE)
    endif()

    file(RELATIVE_PATH folder_path "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")    
    string(REGEX REPLACE "[^a-zA-Z0-9]" _ folder_name "${folder_path}")

    if(NOT CHECK_HEADER_INCLUDES_TARGET)
        set(CHECK_HEADER_INCLUDES_TARGET "check_headers_${folder_name}")
    endif()

    if(NOT CHECK_HEADER_INCLUDES_INCLUDE_DIR)
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
            set(CHECK_HEADER_INCLUDES_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
        else()
            set(CHECK_HEADER_INCLUDES_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
        endif()
    endif()

    if(NOT CHECK_HEADER_INCLUDES_TEMP_DIR)
        set(CHECK_HEADER_INCLUDES_TEMP_DIR "$ENV{TEMP}")
    endif()

    # Setup a temporary directory to output a bunch of .cpp files to
    # where each .cpp file simply contains one #include for the header we're checking
    string(SHA1 tmp_folder_name "${CMAKE_CURRENT_SOURCE_DIR}")
    set(tmp_dir "${CHECK_HEADER_INCLUDES_TEMP_DIR}/${tmp_folder_name}/${CHECK_HEADER_INCLUDES_TARGET}")
    if(EXISTS "${tmp_dir}")
        file(REMOVE_RECURSE "${tmp_dir}")
    endif()
    file(MAKE_DIRECTORY "${tmp_dir}")

    add_custom_target(${CHECK_HEADER_INCLUDES_TARGET})

    foreach(package ${CHECK_HEADER_INCLUDES_PACKAGES})
        find_package(${package} CONFIG REQUIRED)
    endforeach()

    set(library_paths "")
    foreach(lib_path ${CHECK_HEADER_INCLUDES_LIBRARY_PATHS})
        find_path(include_dir "${library_path}")
        list(APPEND library_paths "${include_dir}")
    endforeach()

    file(GLOB_RECURSE headers ${CHECK_HEADER_INCLUDES_HEADERS})
    set(header_i 1)
    foreach(header ${headers})
        file(RELATIVE_PATH header_relative "${CHECK_HEADER_INCLUDES_INCLUDE_DIR}" "${header}")
        string(REGEX REPLACE "[^a-zA-Z0-9]" _ header_name "${header_relative}")

        if(header_name MATCHES "^include_.*")
            string(REGEX REPLACE ^include_ "" header_name ${header_name})
        endif()
        if(header_name MATCHES "\.h$")
            string(REGEX REPLACE .h$ "" header_name ${header_name})
        endif()

        set(header_cpp_tmp_file "${tmp_dir}/${header_i}-${header_name}.cpp")
        string(REPLACE "\\" / header_cpp_tmp_file "${header_cpp_tmp_file}") # or add_library gets angry (???)
        file(WRITE "${header_cpp_tmp_file}" "#include \"${header_relative}\"")

        set(header_target "check_${header_i}_${header_name}")
        add_library("${header_target}" STATIC "${header_cpp_tmp_file}")

        foreach(library ${CHECK_HEADER_INCLUDES_LIBRARIES})
            target_link_libraries(${header_target} PRIVATE ${library})
        endforeach()

        foreach(include_dir ${library_paths})
            target_include_directories(${header_target} PRIVATE ${include_dir})
        endforeach()

        add_dependencies(${CHECK_HEADER_INCLUDES_TARGET} ${header_target})

        MATH(EXPR header_i "${header_i}+1")
    endforeach()
endfunction()
