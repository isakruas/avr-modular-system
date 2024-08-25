#include "i2c.h"

#include <compat/twi.h>
#include <util/delay.h>

/**
 * @brief Initializes the I2C (TWI) interface.
 *
 * This function sets up the I2C interface with a clock frequency
 * determined by the prescaler value passed.
 *
 * @param prescaler The desired prescaler value (0 for 1, 1 for 4, 2 for 16, 3 for 64).
 */
void I2C_Init(uint8_t prescaler) {
    // Set the prescaler bits in TWSR
    TWSR = (prescaler & 0x03);  // Mask to ensure only the lower 2 bits are used

    // Calculate and set the TWBR value for the corresponding frequency
    uint32_t frequency;
    switch (prescaler) {
        case 0:                    // Prescaler = 1
            frequency = 100000UL;  // 100kHz
            break;
        case 1:                    // Prescaler = 4
            frequency = 400000UL;  // 400kHz
            break;
        case 2:                   // Prescaler = 16
            frequency = 50000UL;  // 50kHz
            break;
        case 3:                   // Prescaler = 64
            frequency = 25000UL;  // 25kHz
            break;
        default:
            frequency = 100000UL;  // Default to 100kHz if an invalid prescaler is passed
            break;
    }

    // Calculate the TWBR value for the desired frequency
    TWBR = ((F_CPU / frequency) - 16) / 2;

    // Enable TWI
    TWCR = (1 << TWEN);
}

/**
 * @brief Sends a START condition on the I2C bus.
 *
 * This function generates a START condition and waits until it is transmitted.
 */
void I2C_Start() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);  // Send START condition
    while (!(TWCR & (1 << TWINT)))
        ;  // Wait for TWINT Flag set. This indicates that the START condition has
           // been transmitted.
}

/**
 * @brief Sends a STOP condition on the I2C bus.
 *
 * This function generates a STOP condition and waits until it is transmitted.
 */
void I2C_Stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);  // Send STOP condition
    while (TWCR & (1 << TWSTO))
        ;  // Wait for STOP condition to be executed and bus released
}

/**
 * @brief Transmits a byte of data on the I2C bus.
 *
 * @param data The byte of data to be transmitted.
 *
 * This function loads a byte of data into the TWI data register and waits until
 * the transmission is complete.
 */
void I2C_Write(uint8_t data) {
    TWDR = data;                        // Load data into TWDR register
    TWCR = (1 << TWINT) | (1 << TWEN);  // Start transmission
    while (!(TWCR & (1 << TWINT)))
        ;  // Wait for TWINT Flag set. This indicates that the data has been
           // transmitted, and ACK/NACK has been received.
}

/**
 * @brief Reads a byte of data from the I2C bus with acknowledgment.
 *
 * @return The received byte of data.
 *
 * This function reads a byte of data from the I2C bus and sends an
 * acknowledgment after receiving it.
 */
uint8_t I2C_ReadAck() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);  // Enable TWI and acknowledge bit
    while (!(TWCR & (1 << TWINT)))
        ;         // Wait for TWINT Flag set. This indicates that the data has been
                  // received.
    return TWDR;  // Return received data
}

/**
 * @brief Reads a byte of data from the I2C bus without acknowledgment.
 *
 * @return The received byte of data.
 *
 * This function reads a byte of data from the I2C bus and sends a
 * non-acknowledgment after receiving it.
 */
uint8_t I2C_ReadNack() {
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI without acknowledge bit
    while (!(TWCR & (1 << TWINT)))
        ;         // Wait for TWINT Flag set. This indicates that the data has been
                  // received.
    return TWDR;  // Return received data
}
