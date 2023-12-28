#include "MocksSerial.h"
#include "Print.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

using testing::_;
using testing::Return;
using testing::SetArgPointee;
MocksSerial* pMocksSerial = 0;

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

TEST_F(PrintUnitTests, Test_strlength_String)
{
    /* Arrange */
    /* Act */
    result = strlength("Ahmed Salim\r\n");
    /* Assert */
    EXPECT_EQ(13, result);
}

TEST_F(PrintUnitTests, Test_strlength_NullTerminator)
{
    /* Arrange */
    /* Act */
    result = strlength("\0");
    /* Assert */
    EXPECT_EQ(0, result);
}

TEST_F(PrintUnitTests, Test_print_Null)
{
    /* Arrange */
    /* Act */
    result = print(0);
    /* Assert */
    EXPECT_EQ(0, result);
}

TEST_F(PrintUnitTests, Test_printBuffer)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;
    const char buffer[] = "Hello World!";

    EXPECT_CALL(Serial, writeBytes(_, _))
        .With(::testing::Args<0, 1>(::testing::ElementsAreArray(buffer)))
        .WillOnce(::testing::DoAll(
            ::testing::Return(sizeof(buffer))));

    /* Act */
    result = printBuffer(buffer, sizeof(buffer));

    /* Assert */
    EXPECT_EQ(sizeof(buffer), result);
}

TEST_F(PrintUnitTests, Test_printDigits_Digit_0)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;
    const uint8_t output[1] = { '0' };

    EXPECT_CALL(Serial, writeBytes(_, _))
        .With(::testing::Args<0, 1>(::testing::ElementsAreArray(output)))
        .WillOnce(::testing::DoAll(
            ::testing::Return(sizeof(output))));

    /* Act */
    result = printDigits(0, 10);

    /* Assert */
    EXPECT_EQ(result, 1);
}

TEST_F(PrintUnitTests, Test_printDigits_Digits_12345)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;

    uint8_t output[5] = { '1', '2', '3', '4', '5' };

    EXPECT_CALL(Serial, writeBytes(_, _))
        .With(::testing::Args<0, 1>(::testing::ElementsAreArray(output)))
        .WillOnce(::testing::DoAll(
            ::testing::Return(sizeof(output))));
    /* Act */
    result = printDigits(12345, 10);

    /* Assert */
    EXPECT_EQ(result, 5);
}

TEST_F(PrintUnitTests, Test_printDigits_Digits_12345_Base_2)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;

    uint8_t output[14] = {
        '1',
        '1',
        '0',
        '0',
        '0',
        '0',
        '0',
        '0',
        '1',
        '1',
        '1',
        '0',
        '0',
        '1',
    };

    EXPECT_CALL(Serial, writeBytes(_, _))
        .With(::testing::Args<0, 1>(::testing::ElementsAreArray(output)))
        .WillOnce(::testing::DoAll(
            ::testing::Return(sizeof(output))));

    /* Act */
    result = printDigits(12345, 2);

    /* Assert */
    EXPECT_EQ(result, 14);
}
TEST_F(PrintUnitTests, Test_printDigits_Digits_123456_Base_16)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;

    uint8_t output[5] = {
        '1',
        'E',
        '2',
        '4',
        '0',
    };

    EXPECT_CALL(Serial, writeBytes(_, _))
        .With(::testing::Args<0, 1>(::testing::ElementsAreArray(output)))
        .WillOnce(::testing::DoAll(
            ::testing::Return(sizeof(output))));

    /* Act */
    result = printDigits(123456, 16);

    /* Assert */
    EXPECT_EQ(result, 5);
}
TEST_F(PrintUnitTests, Test_printDigits_Digits_12345_Base_1)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;

    uint8_t output[5] = { '1', '2', '3', '4', '5' };

    EXPECT_CALL(Serial, writeBytes(_, _))
        .With(::testing::Args<0, 1>(::testing::ElementsAreArray(output)))
        .WillOnce(::testing::DoAll(
            ::testing::Return(sizeof(output))));

    /* Act */
    result = printDigits(12345, 1);

    /* Assert */
    EXPECT_EQ(result, 5);
}
TEST_F(PrintUnitTests, Test_printDigits_Digits_Max)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;

    uint8_t output[20] = {
        '1',
        '8',
        '4',
        '4',
        '6',
        '7',
        '4',
        '4',
        '0',
        '7',
        '3',
        '7',
        '0',
        '9',
        '5',
        '5',
        '1',
        '6',
        '1',
        '5'
    };

    EXPECT_CALL(Serial, writeBytes(_, _))
        .With(::testing::Args<0, 1>(::testing::ElementsAreArray(output)))
        .WillOnce(::testing::DoAll(
            ::testing::Return(sizeof(output))));

    /* Act */
    result = printDigits(18446744073709551615UL, 10);

    /* Assert */
    EXPECT_EQ(result, 20);
}

TEST_F(PrintUnitTests, Test_printFloat_PI)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;
    double value = 3.1415f;
    EXPECT_CALL(Serial, writeBytes(_, _)).Times(3).WillOnce(::testing::Return(1)).WillOnce(::testing::Return(1)).WillOnce(::testing::Return(4));

    /* Act */
    result
        = printFloat(value, 4);

    /* Assert */
    EXPECT_EQ(result, 6);
}
TEST_F(PrintUnitTests, Test_printFloat_Negative_PI)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;
    double value = -3.1415f;
    EXPECT_CALL(Serial, writeBytes(_, _)).Times(4).WillOnce(::testing::Return(1)).WillOnce(::testing::Return(1)).WillOnce(::testing::Return(1)).WillOnce(::testing::Return(4));

    /* Act */
    result
        = printFloat(value, 4);

    /* Assert */
    EXPECT_EQ(result, 7);
}
TEST_F(PrintUnitTests, Test_printFloat_Integer)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;
    int8_t value = -123;
    EXPECT_CALL(Serial, writeBytes(_, _)).Times(2).WillOnce(::testing::Return(1)).WillOnce(::testing::Return(3));
    /* Act */
    result = printFloat(value, 0);

    /* Assert */
    EXPECT_EQ(result, 4);
}
TEST_F(PrintUnitTests, Test_printFloat_NaN)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;
    volatile int x = 0;
    double value = 0.0f / x;

    EXPECT_CALL(Serial, writeBytes(_, _)).Times(1).WillOnce(::testing::Return(3));

    /* Act */
    result = printFloat(value, 0);

    /* Assert */
    EXPECT_EQ(result, 3);
}
TEST_F(PrintUnitTests, Test_printFloat_Inf)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;
    double value = INFINITY;

    EXPECT_CALL(Serial, writeBytes(_, _)).Times(1).WillOnce(::testing::Return(3));

    /* Act */
    result = printFloat(value, 0);

    /* Assert */
    EXPECT_EQ(result, 3);
}

TEST_F(PrintUnitTests, Test_printFloat_Ovf)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;
    double value = 4294968050.0f;

    EXPECT_CALL(Serial, writeBytes(_, _)).Times(1).WillOnce(::testing::Return(3));

    /* Act */
    result = printFloat(value, 0);

    /* Assert */
    EXPECT_EQ(result, 3);
}
TEST_F(PrintUnitTests, Test_printFloat_Negative_Ovf)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;
    double value = -4294968050.0f;

    EXPECT_CALL(Serial, writeBytes(_, _)).Times(1).WillOnce(::testing::Return(3));

    /* Act */
    result = printFloat(value, 0);

    /* Assert */
    EXPECT_EQ(result, 3);
}

TEST_F(PrintUnitTests, Test_printBool_True)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;
    uint8_t output[4] = { 't', 'r', 'u', 'e' };

    EXPECT_CALL(Serial, writeBytes(_, _))
        .With(::testing::Args<0, 1>(::testing::ElementsAreArray(output)))
        .WillOnce(::testing::DoAll(
            ::testing::Return(sizeof(output))));

    /* Act */
    result = printBool(true);

    /* Assert */
    EXPECT_EQ(result, 4);
}

TEST_F(PrintUnitTests, Test_printBool_False)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;

    uint8_t output[5] = { 'f', 'a', 'l', 's', 'e' };

    EXPECT_CALL(Serial, writeBytes(_, _))
        .With(::testing::Args<0, 1>(::testing::ElementsAreArray(output)))
        .WillOnce(::testing::DoAll(
            ::testing::Return(sizeof(output))));

    /* Act */
    result = printBool(false);

    /* Assert */
    EXPECT_EQ(result, 5);
}
TEST_F(PrintUnitTests, Test_newline)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;

    uint8_t output[2] = { '\r', '\n' };

    EXPECT_CALL(Serial, writeBytes(_, _))
        .With(::testing::Args<0, 1>(::testing::ElementsAreArray(output)))
        .WillOnce(::testing::DoAll(
            ::testing::Return(sizeof(output))));

    /* Act */
    result = newline();

    /* Assert */
    EXPECT_EQ(result, 2);
}
TEST_F(PrintUnitTests, Test_println)
{
    /* Arrange */
    MocksSerial Serial;
    pMocksSerial = &Serial;

    EXPECT_CALL(Serial, writeBytes(_, _)).Times(2).WillOnce(::testing::Return(11)).WillOnce(::testing::Return(2));

    /* Act */
    result = println("Hello World");

    /* Assert */
    EXPECT_EQ(result, 13);
}
