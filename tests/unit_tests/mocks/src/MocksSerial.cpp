#include "MocksSerial.h"
#ifdef __cplusplus
extern "C" {
#endif
extern MocksSerial* pMocksSerial;

uint8_t writeByte(uint8_t byte)
{
    return (pMocksSerial->writeByte(byte));
}
uint8_t writeBytes(const uint8_t* buffer, uint8_t size)
{
    for (int i = 0; i < size; ++i) {
        spdlog::info("{}=======>{}", buffer[i], (char)buffer[i]);
    }
    return (pMocksSerial->writeBytes(buffer, size));
}

#ifdef __cplusplus
}
#endif
