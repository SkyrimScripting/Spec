function(bandit_specs TARGET)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(BANDIT_SPECS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    find_path(BANDIT_INCLUDE_DIRS "bandit/adapters.h")
    find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")

    add_executable(${TARGET} "${BANDIT_SPECS_SOURCES}")
    target_include_directories(${TARGET} PRIVATE ${BANDIT_INCLUDE_DIRS})
    target_include_directories(${TARGET} PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
endfunction()