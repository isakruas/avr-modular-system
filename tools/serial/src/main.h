#ifndef MAIN_H
#define MAIN_H

#include "tty/tty.h"

/*
 * @brief Function executed by the read thread.
 *
 * This function is executed by the read thread and handles the reading of data
 * from the serial port.
 *
 * @param arg A pointer to any additional arguments passed to the thread.
 * @return A pointer to the thread exit status.
 */
void *read_thread_func(void *arg);

/*
 * @brief Function executed by the write thread.
 *
 * This function is executed by the write thread and handles the writing of data
 * to the serial port.
 *
 * @param arg A pointer to any additional arguments passed to the thread.
 * @return A pointer to the thread exit status.
 */
void *write_thread_func(void *arg);

/*
 * @brief The main function of the program.
 *
 * This is the main entry point of the program and is responsible for creating
 * and managing the read and write threads.
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of strings containing the command-line arguments.
 * @return The exit status of the program.
 */

int main(int argc, char *argv[]);

#endif  // MAIN_H