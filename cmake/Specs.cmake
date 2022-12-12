

function(add_skse_spec_suite TARGET)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(SPEC_SUITE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_commonlibsse_plugin(
        ${TARGET}
        SOURCES ${SPEC_SUITE_SOURCES}
    )
    target_link_libraries(${TARGET} PRIVATE SkyrimScripting.Spec)
    target_compile_features(${TARGET} PRIVATE cxx_std_23)

    # TODO We need to ship this along with our package and provide a way to reference it, e.g. via a CMake variable
    target_precompile_headers(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/cmake/PCH.h)
endfunction()

function(add_catch2_skse_specs TARGET)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(CATCH2_SPECS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_skse_spec_suite(${TARGET} SOURCES "${CATCH2_SPECS_SOURCES}")

    find_package(Catch2 CONFIG REQUIRED)
    target_link_libraries(${TARGET} PRIVATE Catch2::Catch2)
endfunction()

function(add_gtest_skse_specs TARGET)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(CATCH2_SPECS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_skse_spec_suite(${TARGET} SOURCES "${CATCH2_SPECS_SOURCES}")

    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(${TARGET} PRIVATE GTest::gtest)
endfunction()

function(add_bandit_skse_specs TARGET)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(CATCH2_SPECS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_skse_spec_suite(${TARGET} SOURCES "${CATCH2_SPECS_SOURCES}")

    find_path(BANDIT_INCLUDE_DIRS "bandit/adapters.h")
    find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")
    target_include_directories(${TARGET} PRIVATE ${BANDIT_INCLUDE_DIRS})
    target_include_directories(${TARGET} PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
endfunction()
