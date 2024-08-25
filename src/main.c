/*
 * Define the CPU frequency as 16MHz (16000000Hz).
 */
#define F_CPU 16000000UL

#include "main.h"

#include <util/delay.h>

/*
 * @brief Sets up the initial configurations for modules 1 and 2.
 *
 * This function initializes the setup for both module 1 and module 2.
 */
static inline void setup() {
    setupModule1();
    setupModule2();
}

/*
 * @brief Continuously executes the functions of module 1 and module 2 with a
 * delay of 1000 milliseconds between each execution.
 *
 * This function loops through the execution of module 1 and module 2 functions
 * with a delay of 1000 milliseconds between each execution.
 */
static inline void loop() {
    executeModule1Function();
    _delay_ms(1000);
    executeModule2Function();
    _delay_ms(1000);
}

/*
 * @brief The main function initializes the setup and then continuously executes
 * the loop.
 *
 * @return This function does not return any value.
 */
int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
