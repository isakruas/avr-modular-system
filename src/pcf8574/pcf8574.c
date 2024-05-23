/*
 * Include the header file for PCF8574 I/O Expander.
 */
#include "pcf8574.h"

/*
 * Include the I2C header file for I2C communication.
 */
#include "../i2c/i2c.h"

/*
 * @brief Reads a byte from the PCF8574 device at the specified address.
 *
 * @param address The I2C address of the PCF8574 device.
 * @return The byte read from the PCF8574 device.
 */
uint8_t PCF8574_ReadByte(uint8_t address) {
    uint8_t data;
    I2C_Start();                    // Send START condition
    I2C_Write((address << 1) | 1);  // Send address with read bit (1)
    data = I2C_ReadNack();          // Read a byte of data from PCF8574
    I2C_Stop();                     // Send STOP condition
    return data;
}

/*
 * @brief Writes a byte to the PCF8574 device at the specified address.
 *
 * @param address The I2C address of the PCF8574 device.
 * @param data The byte to be written to the PCF8574 device.
 */
void PCF8574_WriteByte(uint8_t address, uint8_t data) {
    I2C_Start();              // Send START condition
    I2C_Write(address << 1);  // Send address with write bit (0)
    I2C_Write(data);          // Send the data
    I2C_Stop();               // Send STOP condition
}

/*
 * @brief Reads the state of a specific pin from the PCF8574 device.
 *
 * @param address The I2C address of the PCF8574 device.
 * @param pin The pin number whose state is to be read.
 * @return The state of the specified pin (0 or 1).
 */
int PCF8574_ReadPin(uint8_t address, uint8_t pin) {
    uint8_t data = PCF8574_ReadByte(address);
    return (data & (1 << pin)) ? 1 : 0;
}

/*
 * @brief Writes a state to a specific pin of the PCF8574 device.
 *
 * @param address The I2C address of the PCF8574 device.
 * @param pin The pin number to which the state is to be written.
 * @param state The state to be written to the specified pin (0 or 1).
 */
void PCF8574_WritePin(uint8_t address, uint8_t pin, uint8_t state) {
    uint8_t data = PCF8574_ReadByte(address);
    if (state) {
        data |= (1 << pin);  // Set the bit (write 1 to the pin)
    } else {
        data &= ~(1 << pin);  // Clear the bit (write 0 to the pin)
    }
    PCF8574_WriteByte(address, data);
}
