/*
 * This header guard prevents multiple inclusions of the "main.h" header file.
 */
#ifndef MAIN_H
#define MAIN_H

/*
 * Include the necessary header files for modules
 */
#include <util/delay.h>

#include "../../../src/protocols/uart/uart.h"

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
