#ifndef PCF8574_H
#define PCF8574_H

#include <stdint.h>

/*
 * Declarations of functions for PCF8574 I/O Expander.
 */

/*
 * @brief Reads a byte from the PCF8574 device at the specified address.
 *
 * @param address The I2C address of the PCF8574 device.
 * @return The byte read from the PCF8574 device.
 */
uint8_t PCF8574_ReadByte(uint8_t address);

/*
 * @brief Writes a byte to the PCF8574 device at the specified address.
 *
 * @param address The I2C address of the PCF8574 device.
 * @param data The byte to be written to the PCF8574 device.
 */
void PCF8574_WriteByte(uint8_t address, uint8_t data);

/*
 * @brief Reads the state of a specific pin from the PCF8574 device.
 *
 * @param address The I2C address of the PCF8574 device.
 * @param pin The pin number whose state is to be read.
 * @return The state of the specified pin (0 or 1).
 */
int PCF8574_ReadPin(uint8_t address, uint8_t pin);

/*
 * @brief Writes a state to a specific pin of the PCF8574 device.
 *
 * @param address The I2C address of the PCF8574 device.
 * @param pin The pin number to which the state is to be written.
 * @param state The state to be written to the specified pin (0 or 1).
 */
void PCF8574_WritePin(uint8_t address, uint8_t pin, uint8_t state);

#endif  // PCF8574_H
