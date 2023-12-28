
include(FetchContent)

# Fetch GoogleTest from the GitHub repository
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main # Use the main branch
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.x # Use a specific release tag
)

# Fetch the content during the configure step
FetchContent_MakeAvailable(googletest spdlog)
include(GoogleTest)

add_executable(PrintUnitTests UT_Print.cpp ${CMAKE_SOURCE_DIR}/tests/unit_tests/mocks/src/MocksSerial.cpp)

target_include_directories(PrintUnitTests PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests/unit_tests/mocks/include
)

target_link_libraries(PrintUnitTests
    PUBLIC
    GTest::gtest_main
    GTest::gmock
    spdlog::spdlog
    Print
)

gtest_discover_tests(PrintUnitTests)
