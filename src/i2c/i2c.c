/*
 * Define the CPU frequency as 8MHz (8000000Hz).
 */
#define F_CPU 8000000UL

#include "i2c.h"
#include <util/delay.h>
#include <compat/twi.h>

/**
 * @brief Initializes the I2C (TWI) interface.
 *
 * This function sets up the I2C interface with a clock frequency of 100kHz.
 * It sets the TWI status register and TWI bit rate register accordingly.
 */
void I2C_Init()
{
    TWSR = 0;                             // Prescaler value = 1
    TWBR = ((F_CPU / 100000UL) - 16) / 2; // Set bit rate for 100kHz with prescaler of 1
    TWCR = (1 << TWEN);                   // Enable TWI
}

/**
 * @brief Sends a START condition on the I2C bus.
 *
 * This function generates a START condition and waits until it is transmitted.
 */
void I2C_Start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // Send START condition
    while (!(TWCR & (1 << TWINT)))
        ; // Wait for TWINT Flag set. This indicates that the START condition has been transmitted.
}

/**
 * @brief Sends a STOP condition on the I2C bus.
 *
 * This function generates a STOP condition and waits until it is transmitted.
 */
void I2C_Stop()
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); // Send STOP condition
    while (TWCR & (1 << TWSTO))
        ; // Wait for STOP condition to be executed and bus released
}

/**
 * @brief Transmits a byte of data on the I2C bus.
 *
 * @param data The byte of data to be transmitted.
 *
 * This function loads a byte of data into the TWI data register and waits until the transmission is complete.
 */
void I2C_Write(uint8_t data)
{
    TWDR = data;                       // Load data into TWDR register
    TWCR = (1 << TWINT) | (1 << TWEN); // Start transmission
    while (!(TWCR & (1 << TWINT)))
        ; // Wait for TWINT Flag set. This indicates that the data has been transmitted, and ACK/NACK has been received.
}

/**
 * @brief Reads a byte of data from the I2C bus with acknowledgment.
 *
 * @return The received byte of data.
 *
 * This function reads a byte of data from the I2C bus and sends an acknowledgment after receiving it.
 */
uint8_t I2C_ReadAck()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Enable TWI and acknowledge bit
    while (!(TWCR & (1 << TWINT)))
        ;        // Wait for TWINT Flag set. This indicates that the data has been received.
    return TWDR; // Return received data
}

/**
 * @brief Reads a byte of data from the I2C bus without acknowledgment.
 *
 * @return The received byte of data.
 *
 * This function reads a byte of data from the I2C bus and sends a non-acknowledgment after receiving it.
 */
uint8_t I2C_ReadNack()
{
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable TWI without acknowledge bit
    while (!(TWCR & (1 << TWINT)))
        ;        // Wait for TWINT Flag set. This indicates that the data has been received.
    return TWDR; // Return received data
}
