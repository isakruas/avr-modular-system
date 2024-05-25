#ifndef UART_H
#define UART_H

#include <avr/io.h>

/*
 * @brief Initializes the UART communication with the specified baud rate.
 *
 * This function initializes the UART communication by configuring the baud rate
 * and other communication parameters.
 *
 * @param baud The desired baud rate for the communication.
 */
void UART_Init(unsigned int baud);

/*
 * @brief Transmits a single byte of data over the UART.
 *
 * This function transmits a single byte of data over the UART communication.
 *
 * @param data The data byte to be transmitted.
 */

void UART_Transmit(unsigned char data);

/*
 * @brief Receives a single byte of data from the UART.
 *
 * This function receives a single byte of data from the UART communication.
 *
 * @return The received data byte.
 */

unsigned char UART_Receive(void);

#endif  // UART_H