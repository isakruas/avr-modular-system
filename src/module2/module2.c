/*
 * Include the header file for module 2.
 */
#include "module2.h"

/*
 * Include the AVR I/O header file for accessing hardware registers.
 */
#include <avr/io.h>

/*
 * Function: setupModule2
 * Description: Configures module 2 by setting pin PA6 as an output.
 */
void setupModule2()
{
    DDRA |= (1 << PA6); // Set PA6 as output
}

/*
 * Function: executeModule2Function
 * Description: Executes the functionality of module 2 by toggling pin PA6.
 */
void executeModule2Function()
{
    PORTA ^= (1 << PA6); // Toggle the state of PA6
}
