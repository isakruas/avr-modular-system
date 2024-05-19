/*
 * Include the header file for SPI
 */
#include "spi.h"

/*
 * @brief Initializes SPI communication as master.
 *
 * This function initializes SPI communication in master mode and sets up the corresponding pins.
 */
void SPI_MasterInit(void)
{
    /* Set MOSI and SCK output, all others input */
    DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK);

    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

/*
 * @brief Transmits data via SPI communication as master.
 *
 * @param data The data byte to be transmitted.
 *
 * This function transmits a single byte of data via SPI communication in master mode.
 */
void SPI_MasterTransmit(char data)
{
    /* Start transmission */
    SPDR = data;
    /* Wait for transmission complete */
    while (!(SPSR & (1 << SPIF)))
        ;
}

/*
 * @brief Initializes SPI communication as slave.
 *
 * This function initializes SPI communication in slave mode and sets up the corresponding pins.
 */
void SPI_SlaveInit(void)
{
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
 * This function receives a single byte of data via SPI communication in slave mode.
 */
char SPI_SlaveReceive(void)
{
    /* Wait for reception complete */
    while (!(SPSR & (1 << SPIF)))
        ;
    /* Return data register */
    return SPDR;
}
