/*
 * Define the CPU frequency as 8MHz (8000000Hz).
 */
#define F_CPU 8000000UL

#include <util/delay.h>
#include "main.h"

/*
 * This function sets up the initial configurations for modules 1 and 2.
 */
static inline void setup()
{
    setupModule1();
    setupModule2();
}

/*
 * This function continuously executes the functions of module 1 and module 2
 * with a delay of 1000 milliseconds between each execution.
 */
static inline void loop()
{
    executeModule1Function();
    _delay_ms(1000);
    executeModule2Function();
    _delay_ms(1000);
}

/*
 * The main function initializes the setup and then continuously executes the loop.
 */
int main(void)
{
    setup();
    while (1)
    {
        loop();
    }
    return 0;
}
