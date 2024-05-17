/*
 * Define the CPU frequency as 8MHz (8000000Hz).
 */
#define F_CPU 8000000UL

#include <util/delay.h>
#include "main.h"

#define EEPROM_ADDRESS 0b10100000 // Address of the AT24C256 EEPROM
#define EEPROM_PAGE_SIZE 64       // Page size of the EEPROM

uint8_t writeBuffer[EEPROM_PAGE_SIZE] = {0}; // Data to write to the EEPROM
uint8_t readBuffer[EEPROM_PAGE_SIZE] = {0};  // Data read from the EEPROM

/**
 * @brief Sets up the initial configurations for the microcontroller.
 *
 * This function configures the necessary settings for the modules, writes initial data to the EEPROM,
 * and prepares data for page writing to the EEPROM.
 */
static inline void setup()
{
    // Set PA6 and PA7 as output pins
    DDRA |= (1 << PA6) | (1 << PA7);

    // Write the value 0xAB to the EEPROM at address 0x0040
    AT24C256_WriteByte(EEPROM_ADDRESS, 0x0040, 0xAB);

    // Fill the write buffer with data to be written to the EEPROM
    for (uint8_t i = 0; i < EEPROM_PAGE_SIZE; i++)
    {
        writeBuffer[i] = i;
    }

    // Write the data array to the EEPROM starting from address 0
    AT24C256_WritePage(EEPROM_ADDRESS, 0, writeBuffer, EEPROM_PAGE_SIZE);

    // Wait for the write cycle to complete
    _delay_ms(10);
}

/**
 * @brief Continuously executes the main functionality of the program.
 *
 * This function toggles the state of PA6, reads and verifies data from the EEPROM,
 * and toggles the state of PA7 based on the read data.
 */
static inline void loop()
{
    // Toggle the state of PA6
    PORTA ^= (1 << PA6);

    // Read a byte from the EEPROM at address 0x0040
    uint8_t readData = AT24C256_ReadByte(EEPROM_ADDRESS, 0x0040);

    // If the read data matches the expected value, toggle PA7 with a delay
    if (readData == 0xAB)
    {
        _delay_ms(1000);
        PORTA ^= (1 << PA7); // Toggle the state of PA7
        _delay_ms(1000);
    }

    // Toggle the state of PA7
    PORTA ^= (1 << PA7);

    // Read a page of data from the EEPROM starting from address 0
    AT24C256_ReadPage(EEPROM_ADDRESS, 0, readBuffer, EEPROM_PAGE_SIZE);

    // Verify if the read data matches the written data
    uint8_t verificationError = 0;
    for (uint8_t i = 0; i < EEPROM_PAGE_SIZE; i++)
    {
        if (readBuffer[i] != writeBuffer[i])
        {
            verificationError = 1;
            break;
        }
    }

    // If data verification is successful, toggle PA6 with a delay
    if (verificationError == 0)
    {
        _delay_ms(1000);
        PORTA ^= (1 << PA6);
        _delay_ms(1000);
    }
}

/**
 * @brief The main function initializes the setup and then continuously executes the loop.
 *
 * @return This function does not return any value.
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
