/*
 * Define the CPU frequency as 8MHz (8000000Hz).
 */
#define F_CPU 8000000UL

#include "at24c256.h"
#include "../i2c/i2c.h"
#include <util/delay.h>

/**
 * @brief Writes a byte to the AT24C256 EEPROM.
 *
 * @param eepromAddress The I2C address of the EEPROM device.
 * @param address The memory address within the EEPROM where the data will be written.
 * @param data The byte of data to be written to the EEPROM.
 */
void AT24C256_WriteByte(uint16_t eepromAddress, uint16_t address, uint8_t data)
{
    // Initiate a Start condition
    I2C_Start();
    // Write device address with RW bit set to 0 (write)
    I2C_Write(eepromAddress);
    // Write the high byte of the memory address (MSB)
    I2C_Write(address >> 8);
    // Write the low byte of the memory address (LSB)
    I2C_Write(address & 0xFF);
    // Write the data byte
    I2C_Write(data);
    // Terminate the transmission
    I2C_Stop();
    // Wait for the write cycle to complete
    _delay_ms(5);
}

/**
 * @brief Reads a byte from the AT24C256 EEPROM.
 *
 * @param eepromAddress The I2C address of the EEPROM device.
 * @param address The memory address within the EEPROM from which the data will be read.
 * @return The byte of data read from the EEPROM.
 */
uint8_t AT24C256_ReadByte(uint16_t eepromAddress, uint16_t address)
{
    // Wait before reading the data
    _delay_ms(10);
    uint8_t data;
    // Initiate a Start condition
    I2C_Start();
    // Write device address with RW bit set to 0 (write)
    I2C_Write(eepromAddress);
    // Write the high byte of the memory address (MSB)
    I2C_Write(address >> 8);
    // Write the low byte of the memory address (LSB)
    I2C_Write(address & 0xFF);
    // Re-initiate a Start condition
    I2C_Start();
    // Write device address with RW bit set to 1 (read)
    I2C_Write(eepromAddress | 1);
    // Read the data byte
    data = I2C_ReadNack();
    // Terminate the transmission
    I2C_Stop();
    // Return the read byte
    return data;
}

/**
 * @brief Writes a page of data to the AT24C256 EEPROM.
 *
 * @param eepromAddress The I2C address of the EEPROM device.
 * @param addressStart The starting memory address within the EEPROM where the data will be written.
 * @param data Pointer to the data array to be written.
 * @param pageSize The number of bytes to be written in one page (typically 64 bytes for AT24C256).
 */
void AT24C256_WritePage(uint16_t eepromAddress, uint16_t addressStart, uint8_t *data, uint8_t pageSize)
{
    // Initiate a Start condition
    I2C_Start();
    // Write device address with RW bit set to 0 (write)
    I2C_Write(eepromAddress);
    // Write the high byte of the starting memory address (MSB)
    I2C_Write(addressStart >> 8);
    // Write the low byte of the starting memory address (LSB)
    I2C_Write(addressStart & 0xFF);
    // Write the page data
    for (uint8_t i = 0; i < pageSize; i++)
    {
        I2C_Write(data[i]);
        _delay_ms(5); // Small delay after each byte write (if necessary)
    }
    // Terminate the transmission
    I2C_Stop();
    // Wait for the write cycle to complete (minimum of 5 ms for AT24C256)
    _delay_ms(5);
}

/**
 * @brief Reads a page of data from the AT24C256 EEPROM.
 *
 * @param eepromAddress The I2C address of the EEPROM device.
 * @param addressStart The starting memory address within the EEPROM from which the data will be read.
 * @param data Pointer to the data array where the read data will be stored.
 * @param pageSize The number of bytes to be read in one page (typically 64 bytes for AT24C256).
 */
void AT24C256_ReadPage(uint16_t eepromAddress, uint16_t addressStart, uint8_t *data, uint8_t pageSize)
{
    // Initiate a Start condition
    I2C_Start();
    // Write device address with RW bit set to 0 (write)
    I2C_Write(eepromAddress);
    // Write the high byte of the starting memory address (MSB)
    I2C_Write(addressStart >> 8);
    // Write the low byte of the starting memory address (LSB)
    I2C_Write(addressStart & 0xFF);
    // Re-initiate a Start condition
    I2C_Start();
    // Write device address with RW bit set to 1 (read)
    I2C_Write(eepromAddress | 1);
    // Read the page data
    for (uint8_t i = 0; i < pageSize; i++)
    {
        if (i < pageSize - 1)
        {
            data[i] = I2C_ReadAck();
        }
        else
        {
            data[i] = I2C_ReadNack();
        }
    }
    // Terminate the transmission
    I2C_Stop();
}
