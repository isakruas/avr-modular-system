/*
 * This header guard prevents multiple inclusions of the "main.h" header file.
 */
#ifndef MAIN_H
#define MAIN_H

/*
 * Include the necessary header files for modules
 */
#include <avr/io.h>
#include "../../src/st7735s/st7735s.h"

/**
 * @brief Converts an integer to a string representation.
 *
 * @param number The integer number to convert.
 * @param stringBuffer The buffer to store the string representation.
 */
void convertIntToString(int number, char *stringBuffer);

/*
 * @brief Sets up the initial configurations for the microcontroller.
 *
 */
static inline void setup();

/*
 * @brief Continuously executes the main functionality of the program.
 *
 */
static inline void loop();

#endif // MAIN_H
