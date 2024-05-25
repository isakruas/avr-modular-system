# Serial Communication Project

## Description
The Serial Communication Project is a C-based application designed to facilitate serial communication using POSIX threads. It enables concurrent reading from and writing to a serial port. This project is ideal for applications that require continuous and real-time data exchange over serial connections.

## Project Structure
The project is organized as follows:
```
serial
├── Makefile
└── src
    ├── main.c
    ├── main.h
    └── tty
        ├── tty.c
        └── tty.h
```

- **/src**: Contains the source files of the project.
  - **tty/**: Directory containing files related to serial port configuration and handling.
  - **main.c**: Main file with the `main` function.
  - **main.h**: Header file for the main source file.
- **Makefile**: Configuration file for compiling the project.

## Compilation and Usage Instructions
1. Make sure you have GCC and the necessary development tools installed on your system.
2. Clone the repository to your local machine.
3. Navigate to the project's root directory.
4. Run the command `make` to compile the project.
5. Execute the `main` binary. Optionally, you can specify a serial port and an operation mode as command-line arguments, e.g., `./main /dev/ttyUSB0 both`.
    - The operation mode can be "read", "write", or "both". If not specified, it defaults to "both".

## Example Usage

```bash
make
./main /dev/ttyUSB0 both
```

## Functionality
  - The program will create read and/or write threads based on the specified mode:
  - The read thread continuously reads data from the specified serial port and prints it to the console.
  - The write thread waits for user input from the console and sends it to the serial port.


## License
This project is distributed under the [MIT License](https://opensource.org/licenses/MIT).