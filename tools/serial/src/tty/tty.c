#include "tty.h"

/*
 * @brief Sets the interface attributes for a given file descriptor and speed.
 *
 * This function sets the interface attributes, such as the baud rate and data
 * format, for a given file descriptor and speed.
 *
 * @param fd The file descriptor of the serial port.
 * @param speed The desired baud rate.
 */
void set_interface_attribs(int fd, int speed) {
    struct termios tty;
    if (tcgetattr(fd, &tty) < 0) {
        perror("tcgetattr");
        return;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);  // Ignore modem controls
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;       // 8-bit characters
    tty.c_cflag &= ~PARENB;   // No parity bit
    tty.c_cflag &= ~CSTOPB;   // Only need 1 stop bit
    tty.c_cflag &= ~CRTSCTS;  // No hardware flow control

    // Setup for non-canonical mode
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // Make raw
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);          // Turn off software flow control
    tty.c_cc[VMIN] = 0;                              // Read doesn't block
    tty.c_cc[VTIME] = 5;                             // 0.5 seconds read timeout

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        return;
    }
}

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
void set_blocking(int fd, int should_block) {
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        return;
    }

    tty.c_cc[VMIN] = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;  // 0.5 seconds read timeout

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        return;
    }
}