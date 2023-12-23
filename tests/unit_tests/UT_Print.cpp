#include "Print.h"
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

class PrintUnitTests : public ::testing::Test {
protected:
    // Setup code that will be called before each test
    void SetUp() override
    {
        spdlog::default_logger_raw()->set_level(spdlog::level::debug);
        // Initialize resources, if needed
    }

    // Teardown code that will be called after each test
    void TearDown() override
    {
        // Clean up resources, if needed
    }
    uint8_t result;
};

TEST_F(PrintUnitTests, Test_Print_Number)
{
    /* Arrange */
    /* Act */
    result = printNumber(10, 0);
    /* Assert */
    EXPECT_EQ(1, result);
}
