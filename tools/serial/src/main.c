#include "main.h"

// Structure to store serial port data
typedef struct {
    char *portname;
    int fd;
} SerialData;

/*
 * @brief Function executed by the read thread.
 *
 * This function is executed by the read thread and handles the reading of data
 * from the serial port.
 *
 * @param arg A pointer to any additional arguments passed to the thread.
 * @return A pointer to the thread exit status.
 */

void *read_thread_func(void *arg) {
    SerialData *serial_data = (SerialData *)arg;
    char buf[1000];
    while (1) {
        int n = read(serial_data->fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("Received: %s\n", buf);
            usleep(500000);  // Delay of 0.5 seconds
        }
    }
    return NULL;
}

/*
 * @brief Function executed by the write thread.
 *
 * This function is executed by the write thread and handles the writing of data
 * to the serial port.
 *
 * @param arg A pointer to any additional arguments passed to the thread.
 * @return A pointer to the thread exit status.
 */
void *write_thread_func(void *arg) {
    SerialData *serial_data = (SerialData *)arg;
    char buf[100];
    while (1) {
        printf("Enter command: ");
        if (fgets(buf, sizeof(buf), stdin) != NULL) {
            buf[strcspn(buf, "\n")] = '\0';  // Remove newline character
            if (strlen(buf) > 0) {
                write(serial_data->fd, buf, strlen(buf));
                usleep(500000);  // Delay of 0.5 seconds
            }
        }
    }
    return NULL;
}

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

int main(int argc, char *argv[]) {
    char *portname = (argc > 1) ? argv[1] : "/dev/ttyUSB0";  // Default port or argument
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    set_interface_attribs(fd, B9600);
    set_blocking(fd, 1);

    // Data structure to pass to the threads
    SerialData serial_data = {portname, fd};

    // Create threads
    pthread_t read_thread, write_thread;

    pthread_create(&read_thread, NULL, read_thread_func, &serial_data);
    pthread_create(&write_thread, NULL, write_thread_func, &serial_data);

    // Wait for the threads to finish (although in our case they run indefinitely)
    pthread_join(read_thread, NULL);
    pthread_join(write_thread, NULL);

    // Close the serial port
    close(fd);
    return 0;
}