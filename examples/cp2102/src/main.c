/*
 * Define the CPU frequency as 8MHz (8000000Hz).
 */

#define F_CPU 8000000UL
#define BUFFER_SIZE 41

#include "main.h"

/**
 * @brief Initializes the UART with a baud rate of 9600.
 *
 * This function sets up the initial configurations for the microcontroller
 * by initializing the UART communication with a specified baud rate.
 */
static inline void setup() { UART_Init(9600); }

/**
 * @brief The primary function that runs the main program loop.
 *
 * This function continuously listens for commands over UART. It processes
 * the command 'U' to read a fixed size buffer from UART and acknowledges
 * with 'K'. For the command 'E', it acknowledges with 'D' and breaks the loop.
 * After exiting the loop, it waits for 600ms before transmitting the entire
 * buffer contents over UART.
 */
static inline void loop() {
    unsigned cmd;
    unsigned char buffer[BUFFER_SIZE];
    uint8_t i;
    while (1) {
        cmd = UART_Receive();
        if (cmd == 'U') {
            for (i = 0; i < BUFFER_SIZE; i++) {
                buffer[i] = UART_Receive();
            }
            UART_Transmit('K');  // Acknowledge with 'K'
        } else if (cmd == 'E') {
            UART_Transmit('D');  // Acknowledge with 'D'
            break;
        }
    }
    _delay_ms(600);
    for (i = 0; i < BUFFER_SIZE; i++) {
        UART_Transmit(buffer[i]);
    }
    // Sample input example: U\x00\x01\x02x\x03\x04\x05\x06\x07\x08\x09E
}

/**
 * @brief The main function.
 *
 * The main function initializes the setup and then repeatedly executes
 * the main program loop.
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