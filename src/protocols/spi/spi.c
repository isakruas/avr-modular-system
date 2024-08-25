/*
 * Include the header file for SPI
 */
#include "spi.h"

/*
 * @brief Initializes SPI communication as master with a given clock preescaler.
 *
 * @param prescaler An integer indicating the desired SPI clock prescaler. The valid values are
 *        2, 4, 8, 16, 32, 64, and 128. If an invalid value is provided or zero, the default value
 *        of 4 will be used.
 */
void SPI_MasterInit(uint8_t prescaler) {
    /* Set MOSI and SCK output, all others input */
    DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK);

    /* Enable SPI, Master mode */
    SPCR = (1 << SPE) | (1 << MSTR);

    /* Set SPI clock rate based on the given prescaler */
    switch (prescaler) {
        case 2:
            /* SPI Clock Frequency = F_CPU / (2 * 2) */
            SPSR = (1 << SPI2X);  // Enable double speed mode
            break;
        case 4:
            /* SPI Clock Frequency = F_CPU / (2 * 4) */
            SPSR = 0;  // No double speed mode
            break;
        case 8:
            /* SPI Clock Frequency = F_CPU / (2 * 8) */
            SPCR |= (1 << SPR0);  // Set SPR0
            SPSR = 0;             // No double speed mode
            break;
        case 16:
            /* SPI Clock Frequency = F_CPU / (2 * 16) */
            SPCR |= (1 << SPR1);  // Set SPR1
            SPSR = 0;             // No double speed mode
            break;
        case 32:
            /* SPI Clock Frequency = F_CPU / (2 * 32) */
            SPCR |= (1 << SPR1);  // Set SPR1
            SPSR = 0;             // No double speed mode
            break;
        case 64:
            /* SPI Clock Frequency = F_CPU / (2 * 64) */
            SPCR |= (1 << SPR0) | (1 << SPR1);  // Set SPR0 and SPR1
            SPSR |= (1 << SPI2X);               // Enable double speed mode
            break;
        case 128:
            /* SPI Clock Frequency = F_CPU / (2 * 128) */
            SPCR |= (1 << SPR0) | (1 << SPR1);  // Set SPR0 and SPR1
            SPSR = 0;                           // No double speed mode
            break;
        default:
            // If invalid prescaler is given or zero, default to 4
            SPSR = 0;  // No double speed mode
            break;
    }
}

/*
 * @brief Transmits data via SPI communication as master.
 *
 * @param data The data byte to be transmitted.
 *
 * This function transmits a single byte of data via SPI communication in master
 * mode.
 */
void SPI_MasterTransmit(char data) {
    /* Start transmission */
    SPDR = data;
    /* Wait for transmission complete */
    while (!(SPSR & (1 << SPIF)))
        ;
}

/*
 * @brief Initializes SPI communication as slave.
 *
 * This function initializes SPI communication in slave mode and sets up the
 * corresponding pins.
 */
void SPI_SlaveInit(void) {
    /* Set MISO output, all others input */
    DDR_SPI = (1 << DD_MISO);
    /* Enable SPI */
    SPCR = (1 << SPE);
}

/*
 * @brief Receives data via SPI communication as slave.
 *
 * @return The received data byte.
 *
 * This function receives a single byte of data via SPI communication in slave
 * mode.
 */
char SPI_SlaveReceive(void) {
    /* Wait for reception complete */
    while (!(SPSR & (1 << SPIF)))
        ;
    /* Return data register */
    return SPDR;
}
