/*
 * Define the CPU frequency as 8MHz (8000000Hz).
 */
#define F_CPU 8000000UL

#include "main.h"

/**
 * @brief Sets up the initial configurations for the microcontroller.
 *
 */
static inline void setup() { UART_Init(9600); }

/**
 * @brief Continuously executes the main functionality of the program.
 *
 */
static inline void loop() {
    unsigned char receive = UART_Receive();
    UART_Transmit(receive);
}

/**
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
