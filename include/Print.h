#ifndef __PRINT_H__
#define __PRINT_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Computes the length of a null-terminated string.
 *
 * @param str A pointer to the null-terminated string for which the length is to be calculated.
 * @return uint8_t The length of the string (number of characters excluding the null terminator).
 *
 * @note The function assumes that the input string is null-terminated.
 * @note The function uses pointer arithmetic to determine the length efficiently.
 */
uint8_t strlength(const char* str);

/**
 * @brief Writes a null-terminated string to an output device or stream.
 *
 * @param str Pointer to a null-terminated string to be printed.
 * @return uint8_t Returns the number of charcters written if successful,
 * zero otherwise.
 *
 * @note The function assumes that the input string is null-terminated.
 */
uint8_t print(const char* str);

/**
 * @brief Prints a string followed by a newline ("\r\n").
 *
 * This function prints the specified string, followed by a newline character
 * sequence ("\r\n"). It returns the total number of characters printed.
 *
 * @param str The string to be printed.
 * @return The number of characters printed.
 */
uint8_t println(const char* str);

/**
 * @brief Writes a buffer of characters to an output device or stream.
 *
 * @param buffer Pointer to the buffer containing the characters to be printed.
 * @param size Number of characters to be printed from the buffer.
 * @return uint8_t Returns the number of charcters written if successful,
 * zero otherwise.
 *
 * @note The function assumes that the input buffer is not null.
 */
uint8_t printBuffer(const char* buffer, uint8_t size);

/**
 * @brief Converts an integer 'n' to a null-terminated string representation in
 * the specified 'base' and stores the result in the provided 'buffer'. The
 * supported bases are 2 through 36. The result is stored with the least
 * significant digit at the end of the buffer.
 *
 * @param number The integer to be converted.
 * @param base The base for the conversion. Must be between 2 and 36.
 * @return uint8_t Digits printed out
 *
 * @note The buffer size should be at least 8 * sizeof(long) + 1 to accommodate
 * the largest possible representation plus a null terminator.
 */
uint8_t printDigits(unsigned long number, uint8_t base);

/**
 * @brief Prints a floating-point number with specified precision.
 *
 * This function prints a floating-point number with the specified precision.
 * If the number is NaN (Not a Number), it prints "NaN".
 * If the number is positive infinity, it prints "Inf".
 * If the number is greater than 4294967040.0 or less than -4294967040.0,
 * it prints "Ovf" (Overflow).
 *
 * @param number The floating-point number to be printed.
 * @param precision The number of digits to print after the decimal point.
 * @return The number of characters printed.
 */
uint8_t printFloat(double number, uint8_t precision);

/**
 * @brief Prints a boolean value as "true" or "false".
 *
 * This function prints a boolean value as either "true" or "false" and
 * returns the number of characters printed.
 *
 * @param value The boolean value to be printed.
 * @return The number of characters printed.
 */
uint8_t printBool(uint8_t value);

/**
 * @brief Prints a newline ("\r\n") and moves to the next line.
 *
 * This function prints a newline character sequence ("\r\n") to the output
 * and moves to the next line. It returns the number of characters printed.
 *
 * @return The number of characters printed.
 */
uint8_t newline(void);

/* Interface Functions */
extern uint8_t writeByte(uint8_t byte);
extern uint8_t writeBytes(const uint8_t* buffer, uint8_t size);

#ifdef __cplusplus
}
#endif
#endif