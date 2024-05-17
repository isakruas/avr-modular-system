# AVR Modular System

## Description
The AVR Modular System is a project for developing firmware for AVR microcontrollers, aiming at a modular architecture that allows easy expansion and integration of different functionality modules. Each module can be configured and executed independently, allowing for a high degree of flexibility and code reuse.

## Microcontroller
AVR ATmega32A-PU

## Programmer
USBasp

## Port
USB

## Project Structure
- **/src**: Contains the source files of the project.
  - **/module1**: Files related to module 1.
  - **/module2**: Files related to module 2.
  - **main.c**: Main file with the `main` function.
  - **main.h**: Declaration of main functions.
- **/build**: Directory to store the files generated during compilation.
- **Makefile**: Configuration file for compiling and programming the firmware.

## Compilation and Usage Instructions
1. Make sure you have the AVR GNU Toolchain installed on your system.
2. Clone the repository to your local machine.
3. Navigate to the project's root directory.
4. Run the command `make` to compile the firmware.
5. Connect the AVR ATmega32A-PU microcontroller to your system using the USBasp programmer.
6. Run the command `make flash` to program the firmware into the microcontroller.

## License
This project is distributed under the [MIT License](https://opensource.org/licenses/MIT).
