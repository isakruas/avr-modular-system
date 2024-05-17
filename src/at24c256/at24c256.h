#ifndef AT24C256_H
#define AT24C256_H

#include <stdint.h>

/**
 * @brief Writes a byte to the AT24C256 EEPROM.
 *
 * @param eepromAddress The I2C address of the EEPROM device.
 * @param address The memory address within the EEPROM where the data will be written.
 * @param data The byte of data to be written to the EEPROM.
 */
void AT24C256_WriteByte(uint16_t eepromAddress, uint16_t address, uint8_t data);

/**
 * @brief Reads a byte from the AT24C256 EEPROM.
 *
 * @param eepromAddress The I2C address of the EEPROM device.
 * @param address The memory address within the EEPROM from which the data will be read.
 * @return The byte of data read from the EEPROM.
 */
uint8_t AT24C256_ReadByte(uint16_t eepromAddress, uint16_t address);

/**
 * @brief Reads a page of data from the AT24C256 EEPROM.
 *
 * @param eepromAddress The I2C address of the EEPROM device.
 * @param addressStart The starting memory address within the EEPROM from which the data will be read.
 * @param data Pointer to the data array where the read data will be stored.
 * @param pageSize The number of bytes to be read in one page (typically 64 bytes for AT24C256).
 */
void AT24C256_ReadPage(uint16_t eepromAddress, uint16_t addressStart, uint8_t *data, uint8_t pageSize);

/**
 * @brief Writes a page of data to the AT24C256 EEPROM.
 *
 * @param eepromAddress The I2C address of the EEPROM device.
 * @param addressStart The starting memory address within the EEPROM where the data will be written.
 * @param data Pointer to the data array to be written.
 * @param pageSize The number of bytes to be written in one page (typically 64 bytes for AT24C256).
 */
void AT24C256_WritePage(uint16_t eepromAddress, uint16_t addressStart, uint8_t *data, uint8_t pageSize);

#endif // AT24C256_H
