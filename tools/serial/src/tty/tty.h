#ifndef TTY_H
#define TTY_H

#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/*
 * @brief Sets the interface attributes for a given file descriptor and speed.
 *
 * This function sets the interface attributes, such as the baud rate and data
 * format, for a given file descriptor and speed.
 *
 * @param fd The file descriptor of the serial port.
 * @param speed The desired baud rate.
 */
void set_interface_attribs(int fd, int speed);

/*
 * @brief Sets whether a given file descriptor is blocking or non-blocking.
 *
 * This function sets whether a given file descriptor is set to blocking or
 * non-blocking mode.
 *
 * @param fd The file descriptor.
 * @param should_block Boolean value indicating whether the file descriptor
 *        should be set to blocking or non-blocking mode.
 */
void set_blocking(int fd, int should_block);

#endif /* TTY_H */