/*
 * Define the CPU frequency as 16MHz (16000000Hz).
 */
#define F_CPU 16000000UL

#include "main.h"

#include <util/delay.h>

/**
 * @brief Sets up the initial configurations for the microcontroller.
 *
 */
static inline void setup() {
    ST77XX_Reset();
    ST77XX_InitDisplay();
    DDRA |= (1 << PA6) | (1 << PA7);
}

/**
 * @brief Converts an integer to a string representation.
 *
 * @param number The integer number to convert.
 * @param stringBuffer The buffer to store the string representation.
 */
void convertIntToString(int number, char *stringBuffer) {
    stringBuffer[0] = '0' + (number % 10);  // Get the last digit of the integer and convert it to a character
    stringBuffer[1] = '\0';                 // Terminate the string with a null character
}

/**
 * @brief Continuously executes the main functionality of the program.
 *
 */
static inline void loop() {
    PORTA ^= (1 << PA6);

    // Clear the screen and fill it with black
    ST77XX_FillScreenWithColor(0x000);

    // Example string to draw
    char fullAsciiString[] =
        "!\"#$ "
        "%&'()*+,-./"
        "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
        "abcdefghijklmnopqrstuvwxyz{|}~";
    uint16_t pos1 = ST77XX_DrawString(0, 0, fullAsciiString, 0xFFFF, 0x0000);
    uint16_t pos2 = ST77XX_DrawString(pos1 & 0xFF, (pos1 >> 8) & 0xFF, fullAsciiString, 0xFFFF, 0x0000);
    ST77XX_DrawString(pos2 & 0xFF, (pos2 >> 8) & 0xFF, fullAsciiString, 0xFFFF, 0x0000);
    _delay_ms(1000);

    // Clear the screen again
    ST77XX_FillScreenWithColor(0x000);

    char helloWorldString[] = "Hello, world!";

    static int counter = 0;  // Declare 'counter' as static to maintain its value between calls

    // Convert the counter to a string
    char counterString[2];  // Character array to store the counter as string
    convertIntToString(counter,
                       counterString);  // Call the function to convert the counter to a string

    // Draw the "Hello, world!" string
    ST77XX_DrawString(0, 0, helloWorldString, 0xFFFF, 0x0000);

    // Draw the counter string
    ST77XX_DrawString(6 * 6, 8 * 8, counterString, 0xFFFF, 0x0000);

    // Increment the counter
    counter++;

    // Reset the counter to 0 when it reaches 10
    if (counter == 10) {
        counter = 0;
    }
    _delay_ms(1000);

    // Cycle through different colors as a demonstration
    ST77XX_FillScreenWithColor(0xFFFF);  // White color
    _delay_ms(1000);

    ST77XX_FillScreenWithColor(0xF800);  // Red color
    _delay_ms(1000);

    ST77XX_FillScreenWithColor(0x07E0);  // Green color
    _delay_ms(1000);

    ST77XX_FillScreenWithColor(0x001F);  // Blue color
    _delay_ms(1000);

    ST77XX_FillScreenWithColor(0xFFE0);  // Yellow color
    _delay_ms(1000);

    // Clear the screen back to black
    ST77XX_FillScreenWithColor(0x000);
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
