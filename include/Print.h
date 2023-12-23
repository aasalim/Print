#ifndef __PRINT_H__
#define __PRINT_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

/**
 * @brief Prints a number
 *
 * @param number Number to be printed
 * @param base Base of number
 * @return uint8_t Digits printed out
 */
uint8_t printNumber(unsigned long number, uint8_t base);

#ifdef __cplusplus
}
#endif
#endif