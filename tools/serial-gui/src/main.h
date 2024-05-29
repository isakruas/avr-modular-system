#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <gtk/gtk.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

/**
 * @brief Get the selected baud rate from the combobox
 *
 * @return The baud rate constant for termios
 */
int get_baudrate_from_combobox();

/**
 * @brief Configure the serial port with the specified baud rate
 *
 * @param baudrate The baud rate constant for termios
 */
void configure_serial_port(int baudrate);

/**
 * @brief Send the command entered in the entry widget to the serial port
 *
 * @param widget The widget that triggered the callback
 * @param data User data (unused)
 */
void send_command(GtkWidget *widget, gpointer data);

/**
 * @brief Export the messages in the text view to an XML file with timestamps
 *
 * @param widget The widget that triggered the callback
 * @param data User data (unused)
 */
void export_to_xml(GtkWidget *widget, gpointer data);

/**
 * @brief Clear the text view buffer
 *
 * @param widget The widget that triggered the callback
 * @param data User data (unused)
 */
void clear_text_view(GtkWidget *widget, gpointer data);

/**
 * @brief Callback for window destroy signal
 *
 * @param widget The widget that triggered the callback
 * @param data User data (unused)
 */
void on_window_destroy(GtkWidget *widget, gpointer data);

/**
 * @brief Main function
 *
 * @param argc Argument count
 * @param argv Argument values
 *
 * @return Exit status
 */
int main(int argc, char *argv[]);

#endif  // MAIN_H