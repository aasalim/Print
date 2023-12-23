#ifndef __MOCK_SERIAL_H__
#define __MOCK_SERIAL_H__
#include "Print.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

class MocksSerial {
public:
    MOCK_METHOD(uint8_t, writeByte, (uint8_t byte));
    MOCK_METHOD(uint8_t, writeBytes, (const uint8_t* buffer, uint8_t size));
};
#endif