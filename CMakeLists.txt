# CMake Minimum Version Required
cmake_minimum_required(VERSION 3.15)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Make our cmake scripts available
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CTEST_OPTIONS "--verbose")

# Create C Project
project(Print LANGUAGES C CXX)

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

# External Submodules
add_subdirectory(external)

# Source Directory
add_subdirectory(src)

# Examples
add_subdirectory(examples)

# Tests
enable_testing()
add_subdirectory(tests)
