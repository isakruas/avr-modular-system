#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

/**
 * @brief Initializes the I2C (TWI) interface.
 *
 * This function sets up the I2C interface with a clock frequency of 100kHz.
 * It sets the TWI status register and TWI bit rate register accordingly.
 */
void I2C_Init();

/**
 * @brief Sends a START condition on the I2C bus.
 *
 * This function generates a START condition and waits until it is transmitted.
 */
void I2C_Start();

/**
 * @brief Sends a STOP condition on the I2C bus.
 *
 * This function generates a STOP condition and waits until it is transmitted.
 */
void I2C_Stop();

/**
 * @brief Transmits a byte of data on the I2C bus.
 *
 * @param data The byte of data to be transmitted.
 *
 * This function loads a byte of data into the TWI data register and waits until
 * the transmission is complete.
 */
void I2C_Write(uint8_t data);

/**
 * @brief Reads a byte of data from the I2C bus with acknowledgment.
 *
 * @return The received byte of data.
 *
 * This function reads a byte of data from the I2C bus and sends an
 * acknowledgment after receiving it.
 */
uint8_t I2C_ReadAck();

/**
 * @brief Reads a byte of data from the I2C bus without acknowledgment.
 *
 * @return The received byte of data.
 *
 * This function reads a byte of data from the I2C bus and sends a
 * non-acknowledgment after receiving it.
 */
uint8_t I2C_ReadNack();

#endif  // I2C_H
