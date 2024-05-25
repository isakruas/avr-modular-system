/*
 * Include the header file for UART
 */
#include "uart.h"

/*
 * @brief Initializes the UART communication with the specified baud rate.
 *
 * This function initializes the UART communication by configuring the baud rate
 * and other communication parameters.
 *
 * @param baud The desired baud rate for the communication.
 */
void UART_Init(unsigned int baud) {
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    // Configure the baud rate
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSRB = (1 << RXEN) | (1 << TXEN);
    // Configure frame: 8 data bits, 1 stop bit
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

/*
 * @brief Transmits a single byte of data over the UART.
 *
 * This function transmits a single byte of data over the UART communication.
 *
 * @param data The data byte to be transmitted.
 */
void UART_Transmit(unsigned char data) {
    // Wait for the buffer to be empty
    while (!(UCSRA & (1 << UDRE)))
        ;
    // Send the data
    UDR = data;
}

/*
 * @brief Receives a single byte of data from the UART.
 *
 * This function receives a single byte of data from the UART communication.
 *
 * @return The received data byte.
 */
unsigned char UART_Receive(void) {
    // Wait for data
    while (!(UCSRA & (1 << RXC)))
        ;
    // Receive the data
    return UDR;
}