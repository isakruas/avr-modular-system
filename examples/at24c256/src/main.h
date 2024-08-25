/*
 * This header guard prevents multiple inclusions of the "main.h" header file.
 */
#ifndef MAIN_H
#define MAIN_H

/*
 * Include the necessary header files for modules
 */
#include <avr/io.h>

#include "../../../src/modules/at24c256/at24c256.h"
#include "../../../src/protocols/i2c/i2c.h"

/*
 * @brief Sets up the initial configurations for the microcontroller.
 *
 * This function configures the necessary settings for the modules.
 */
static inline void setup();

/*
 * @brief Continuously executes the main functionality of the program.
 *
 * This function toggles the state of PA6, reads and verifies data from the
 * EEPROM, and toggles the state of PA7 based on the read data.
 */
static inline void loop();

#endif  // MAIN_H
