/*
 * This header guard prevents multiple inclusions of the "main.h" header file.
 */
#ifndef MAIN_H
#define MAIN_H

/*
 * Include the necessary header files for modules
 */
#include <avr/io.h>

#include "modules/module1/module1.h"
#include "modules/module2/module2.h"

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
