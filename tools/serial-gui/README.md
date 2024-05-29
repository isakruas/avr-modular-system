# Serial Communication Project with GUI

## Description
The Serial Communication Project is a C-based application using the GTK library to provide a graphical user interface for serial communication. It allows users to configure the baud rate, send commands through the serial port, and view received messages. Additionally, users can export the communication log to an XML file with timestamps and clear the text view.

## Project Structure
The project is organized as follows:
```
serial-gui
├── Makefile
└── src
    ├── main.c
    ├── main.h
```

- **/src**: Contains the source files of the project.
  - **main.c**: Main file with the `main` function and GTK-related functionality.
  - **main.h**: Header file for the main source file.
- **Makefile**: Configuration file for compiling the project.

## Compilation and Usage Instructions
1. Make sure you have GCC, GTK development libraries, and libxml2 installed on your system.
2. Clone the repository to your local machine.
3. Navigate to the project's root directory.
4. Run the command `make` to compile the project.
5. Execute the `main` binary to launch the GUI.
    - Example: `./main`

## Function Descriptions
- **Baud Rate Combobox**: Select the desired baud rate for the serial port communication.
- **Command Entry**: Enter commands to be sent to the serial port.
- **Send Button**: Send the command entered in the Command Entry to the serial port.
- **Text View**: Display messages received from the serial port.
- **Export to XML Button**: Export the messages in the Text View to an XML file with timestamps.
- **Clear Text View Button**: Clear the contents of the Text View.

## License
This project is distributed under the [MIT License](https://opensource.org/licenses/MIT).