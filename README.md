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
- **/build**: Directory to store the files generated during compilation.
- **/examples**: Examples demonstrating the usage of the firmware.
- **/src**: Contains the source files of the project, organized into subdirectories:
  - **/modules**: Files related to the project modules.
  - **/protocols**: Implementations of communication protocols.
- **/tools**: Additional tools for the project.
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
