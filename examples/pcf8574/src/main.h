/*
 * This header guard prevents multiple inclusions of the "main.h" header file.
 */
#ifndef MAIN_H
#define MAIN_H

/*
 * Include the necessary header files for modules
 */
#include <avr/io.h>

#include "../../src/pcf8574/pcf8574.h"

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

#endif  // MAIN_H
