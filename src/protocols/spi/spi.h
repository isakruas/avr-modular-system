#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

/*
 * @brief DDR register for SPI.
 *
 * This macro defines the Data Direction Register (DDR) for the SPI
 * communication.
 */
#define DDR_SPI DDRB

/*
 * @brief MOSI pin for SPI.
 *
 * This macro defines the Data Direction (DD) for the Master Output Slave Input
 * (MOSI) pin of SPI communication.
 */
#define DD_MOSI PB5

/*
 * @brief MISO pin for SPI.
 *
 * This macro defines the Data Direction (DD) for the Master Input Slave Output
 * (MISO) pin of SPI communication.
 */
#define DD_MISO PB6

/*
 * @brief SCK pin for SPI.
 *
 * This macro defines the Data Direction (DD) for the Serial Clock (SCK) pin of
 * SPI communication.
 */
#define DD_SCK PB7

/*
 * @brief Initializes SPI communication as master with a given clock preescaler.
 *
 * @param prescaler An integer indicating the desired SPI clock prescaler. The valid values are
 *        2, 4, 8, 16, 32, 64, and 128. If an invalid value is provided or zero, the default value
 *        of 4 will be used.
 */
void SPI_MasterInit(uint8_t prescaler);

/*
 * @brief Transmits data via SPI communication as master.
 *
 * @param data The data byte to be transmitted.
 *
 * This function transmits a single byte of data via SPI communication in master
 * mode.
 */
void SPI_MasterTransmit(char data);

/*
 * @brief Initializes SPI communication as slave.
 *
 * This function initializes SPI communication in slave mode and sets up the
 * corresponding pins.
 */
void SPI_SlaveInit(void);

/*
 * @brief Receives data via SPI communication as slave.
 *
 * @return The received data byte.
 *
 * This function receives a single byte of data via SPI communication in slave
 * mode.
 */
char SPI_SlaveReceive(void);

#endif  // SPI_H
