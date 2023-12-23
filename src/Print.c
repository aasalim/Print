#include "Print.h"
#include <math.h>

uint8_t strlength(const char* str)
{
    /**
     * @brief Initialize a pointer 's' to the beginning of the input string.
     */
    const char* s = str;

    /**
     * @brief Iterate through each character in the string until the null
     * terminator is encountered.
     */
    while (*s) {
        ++s;
    }
    /**
     * @brief Calculate the length of the string by subtracting the initial
     * pointer position from the current position.
     */
    return (uint8_t)(s - str);
}

uint8_t print(const char* str)
{
    /**
     * @brief Check if the input string is null.
     */
    if (str == 0) {
        /**
         * @brief Return a zero value to indicate an error or invalid input.
         */
        return 0;
    }

    /**
     * @brief Write the string to an output device or stream using the
     *        writeBytes function, which writes the byte representation of the string.
     *
     * @note The specific implementation details may depend on the underlying system or
     *       output mechanism (e.g., UART, console, file, etc.).
     * @note The function uses the strlength function to determine the length of the
     *       input string, and it operates under the assumption that the string is null-terminated.
     */
    return writeBytes((const uint8_t*)str, strlength(str));
}

uint8_t println(const char* str)
{
    /**
     * @brief Print the specified string.
     */
    uint8_t n = print(str);

    /**
     * @brief Print a newline character sequence ("\r\n").
     */
    n += newline();

    /**
     * @brief Return the total number of characters printed.
     */
    return n;
}

uint8_t printBuffer(const char* buffer, uint8_t size)
{
    /**
     * @brief Write the buffer to an output device or stream using the
     *        writeBytes function, which writes the byte representation of the buffer.
     *
     * @note The specific implementation details may depend on the underlying system or
     *       output mechanism (e.g., UART, console, file, etc.).
     */
    return writeBytes((const uint8_t*)buffer, size);
}

uint8_t printDigits(unsigned long number, uint8_t base)
{
    /**
     * @brief Buffer to store digits. Assumes 8-bit chars plus null terminator.
     */
    char buffer[8 * sizeof(long) + 1];

    /**
     * @brief Initialize a pointer to the end of the buffer.
     */
    char* str = &buffer[sizeof(buffer) - 1];

    /**
     * @brief Ensure null-termination of the string.
     */
    *str = '\0';

    /**
     * @brief Prevent crash if called with base <= 1.
     */
    if (base < 2) {
        base = 10;
    }

    /**
     * @brief Convert the integer to a string representation in the specified base.
     */
    do {
        /**
         * @brief Calculate the remainder when dividing 'number' by the specified
         *  'base'.
         */
        char c = number % base;

        /**
         * @brief Update 'number' by performing integer division by the specified
         *  'base'.
         */
        number /= base;

        /**
         * @brief Convert the remainder 'c' to a character and store it in the buffer.
         * If 'c' is less than 10, convert it to a digit character ('0' to '9').
         * Otherwise, convert it to an uppercase letter ('A' to 'Z').
         */
        *--str = (c < 10) ? (c + '0') : (c + 'A' - 10);

    } while (number);

    /**
     * @brief Return value: Digits printed out.
     */
    return print(str);
}

uint8_t printFloat(double number, uint8_t precision)
{
    /**
     * @brief Initialize the character count.
     */
    uint8_t n = 0;

    /**
     * @brief Check if the number is NaN.
     */
    if (isnan(number)) {
        return print("NaN");
    }

    /**
     * @brief Check if the number is positive infinity.
     */
    if (isinf(number)) {
        return print("Inf");
    }

    /**
     * @brief Check for overflow conditions.
     */
    if (number > 4294967040.0f || number < -4294967040.0f) {
        return print("Ovf");
    }

    /**
     * @brief Handle negative numbers.
     */
    if (number < 0.0) {
        n += print("-");
        number = -number;
    }

    /**
     * @brief Set up rounding factor based on precision.
     */
    double rounding = 0.5;
    for (uint8_t i = 0; i < precision; ++i) {
        rounding /= 10.0;
    }

    /**
     * @brief Round the number to the specified precision.
     */
    number += rounding;

    /**
     * @brief Separate the integer and fractional parts.
     */
    unsigned long int_part = (unsigned long)number;
    double remainder = number - (double)int_part;

    /**
     * @brief Print the integer part.
     */
    n += printDigits(int_part, 10);

    /**
     * @brief Print the fractional part if precision is greater than 0.
     */
    if (precision > 0) {
        n += print(".");

        /**
         * @brief Extract digits from the fractional part.
         */
        while (precision-- > 0) {
            remainder *= 10.0;
        }
        unsigned int toPrint = (unsigned int)(remainder);
        n += printDigits(toPrint, 10);
    }

    /**
     * @brief Return the total number of characters printed.
     */
    return n;
}

uint8_t printBool(uint8_t value)
{
    /**
     * @brief Check if the boolean value is true.
     */
    if (value) {
        return print("true");
    }

    /**
     * @brief If the boolean value is false, print "false".
     */
    return print("false");
}

uint8_t newline(void)
{
    /**
     * @brief Print the newline character sequence ("\r\n").
     */
    return print("\r\n");
}