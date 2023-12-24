# CMake Minimum Version Required
cmake_minimum_required(VERSION 3.15)

# Create C Project
project(Print LANGUAGES C CXX)

if(PROJECT_IS_TOP_LEVEL)
    # Generate compile_commands.json
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_VERBOSE_MAKEFILE ON)

    # Make our cmake scripts available
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

    set(CTEST_OPTIONS "--verbose")

    # Code Coverage
    include(CodeCoverage)
    set(GCOVR_ADDITIONAL_ARGS "-s" "--keep")
    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(
        NAME coverage
        EXECUTABLE test
        DEPENDENCIES Print
        BASE_DIRECTORY "${CMAKE_SOURCE_DIR}"
        EXCLUDE "build" "examples" "external" "tests")

    include(Warnings)
    include(StaticAnalyzers)
    include(Cache)
    check_enable_cache()

    tool_enable_cppcheck(ON "")

    # External Submodules
    add_subdirectory(external)
endif()

# Source Directory
add_subdirectory(src)

if(PROJECT_IS_TOP_LEVEL)
    target_set_warnings(Print ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Helper that can set default warning flags for you

    # Examples
    add_subdirectory(examples)

    # Tests
    enable_testing()
    add_subdirectory(tests)
endif()