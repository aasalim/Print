
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
