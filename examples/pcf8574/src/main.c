/*
 * Define the CPU frequency as 8MHz (8000000Hz).
 */
#define F_CPU 8000000UL

#include "main.h"

#include <util/delay.h>

#define PCF8574_ADDRESS 0b00100000

/**
 * @brief Sets up the initial configurations for the microcontroller.
 *
 * In this function, you can perform any initialization required for the microcontroller.
 */
static inline void setup() {}

/**
 * @brief Continuously executes the main functionality of the program.
 *
 * This function toggles the state of two LEDs connected to the PCF8574 I/O expander,
 * reads the state of the LEDs, and performs actions based on their states.
 */
static inline void loop() {
    // Turns on the LED connected to pin P0
    PCF8574_WritePin(PCF8574_ADDRESS, 0, 1);
    _delay_ms(1000);

    // Reads the state of pin P0
    if (PCF8574_ReadPin(PCF8574_ADDRESS, 0) == 1) {
        // Rapidly toggles the LED connected to pin P1 if pin P0 is on
        for (int i = 0; i < 10; i++) {
            PCF8574_WritePin(PCF8574_ADDRESS, 1, 1);  // Turns on P1
            _delay_ms(100);
            PCF8574_WritePin(PCF8574_ADDRESS, 1, 0);  // Turns off P1
            _delay_ms(100);
        }
    }

    // Turns off the LED connected to pin P0
    PCF8574_WritePin(PCF8574_ADDRESS, 0, 0);
    _delay_ms(1000);

    // Turns on the LED connected to pin P1
    PCF8574_WritePin(PCF8574_ADDRESS, 1, 1);
    _delay_ms(1000);

    // Reads the state of pin P1
    if (PCF8574_ReadPin(PCF8574_ADDRESS, 1) == 1) {
        // Rapidly toggles the LED connected to pin P0 if pin P1 is on
        for (int i = 0; i < 10; i++) {
            PCF8574_WritePin(PCF8574_ADDRESS, 0, 1);  // Turns on P0
            _delay_ms(100);
            PCF8574_WritePin(PCF8574_ADDRESS, 0, 0);  // Turns off P0
            _delay_ms(100);
        }
    }

    // Turns off the LED connected to pin P1
    PCF8574_WritePin(PCF8574_ADDRESS, 1, 0);
    _delay_ms(1000);
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
