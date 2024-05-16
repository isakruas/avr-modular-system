/*
 * Include the header file for module 1.
 */
#include "module1.h"

/*
 * Include the AVR I/O header file for accessing hardware registers.
 */
#include <avr/io.h>

/*
 * Function: setupModule1
 * Description: Configures module 1 by setting pin PA7 as an output.
 */
void setupModule1()
{
    DDRA |= (1 << PA7); // Set PA7 as output
}

/*
 * Function: executeModule1Function
 * Description: Executes the functionality of module 1 by toggling pin PA7.
 */
void executeModule1Function()
{
    PORTA ^= (1 << PA7); // Toggle the state of PA7
}
