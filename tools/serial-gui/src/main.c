#include "main.h"

GtkWidget *command_entry;
GtkWidget *baudrate_combobox;
GtkTextBuffer *text_buffer;
int serial_port;

/**
 * @brief Get the selected baud rate from the combobox
 *
 * @return The baud rate constant for termios
 */
int get_baudrate_from_combobox() {
    const gchar *baudrate_str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(baudrate_combobox));
    int baudrate = atoi(baudrate_str);

    switch (baudrate) {
        case 9600:
            return B9600;
        case 19200:
            return B19200;
        case 38400:
            return B38400;
        case 57600:
            return B57600;
        case 115200:
            return B115200;
        default:
            return B9600;  // Default baud rate if none selected
    }
}

/**
 * @brief Configure the serial port with the specified baud rate
 *
 * @param baudrate The baud rate constant for termios
 */
void configure_serial_port(int baudrate) {
    struct termios tty;
    if (tcgetattr(serial_port, &tty) != 0) {
        perror("Error from tcgetattr");
        return;
    }

    cfsetospeed(&tty, baudrate);
    cfsetispeed(&tty, baudrate);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8-bit chars
    tty.c_iflag &= ~IGNBRK;                      // disable break processing
    tty.c_lflag = 0;                             // no signaling chars, no echo, no canonical processing
    tty.c_oflag = 0;                             // no remapping, no delays

    tty.c_cc[VMIN] = 0;   // read doesn't block
    tty.c_cc[VTIME] = 5;  // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);  // shut off xon/xoff ctrl
    tty.c_cflag |= (CLOCAL | CREAD);         // ignore modem controls, enable reading
    tty.c_cflag &= ~(PARENB | PARODD);       // shut off parity
    tty.c_cflag |= 0;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        return;
    }
}

/**
 * @brief Send the command entered in the entry widget to the serial port
 *
 * @param widget The widget that triggered the callback
 * @param data User data (unused)
 */
void send_command(GtkWidget *widget, gpointer data) {
    const gchar *command = gtk_entry_get_text(GTK_ENTRY(command_entry));

    if (g_strcmp0(command, "") == 0) {
        return;
    }

    int baudrate = get_baudrate_from_combobox();
    configure_serial_port(baudrate);

    write(serial_port, command, strlen(command));
    // write(serial_port, "\r\n", 2);

    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(text_buffer, &iter);

    gchar *sanitized_command = g_utf8_make_valid(command, -1);

    gtk_text_buffer_insert(text_buffer, &iter, "Sent: ", -1);
    gtk_text_buffer_insert(text_buffer, &iter, sanitized_command, -1);
    gtk_text_buffer_insert(text_buffer, &iter, "\n", -1);

    g_free(sanitized_command);

    usleep(500000);  // Wait for 500 milliseconds

    char response[10000];
    int response_length = 0;

    while (1) {
        int n = read(serial_port, response + response_length, sizeof(response) - response_length - 1);
        if (n <= 0) {
            // Break the loop if no bytes were read or if there's an error
            break;
        }

        response_length += n;
        response[response_length] = '\0';  // Null-terminate the string

        // Remove or replace invalid utf-8 sequences
        gchar *valid_response = g_utf8_make_valid(response, response_length);

        // Add messages to the text buffer line by line
        char *newline_pos;
        char *start_pos = valid_response;
        while ((newline_pos = strchr(start_pos, '\n')) != NULL) {
            *newline_pos = '\0';  // Replace newline with null terminator
            gtk_text_buffer_get_end_iter(text_buffer, &iter);
            gtk_text_buffer_insert(text_buffer, &iter, "Received: ", -1);
            gtk_text_buffer_insert(text_buffer, &iter, start_pos, -1);
            gtk_text_buffer_insert(text_buffer, &iter, "\n", -1);
            start_pos = newline_pos + 1;  // Move to the next line
        }

        // Move the remaining data to the start of the buffer
        response_length = strlen(start_pos);
        memmove(response, start_pos, response_length);

        g_free(valid_response);

        // Wait for a short period before reading more data
        usleep(500000);
    }

    gtk_entry_set_text(GTK_ENTRY(command_entry), "");
}

/**
 * @brief Export the messages in the text view to an XML file with timestamps
 *
 * @param widget The widget that triggered the callback
 * @param data User data (unused)
 */
void export_to_xml(GtkWidget *widget, gpointer data) {
    GtkFileChooser *dialog = GTK_FILE_CHOOSER(gtk_file_chooser_dialog_new(
        "Save File", GTK_WINDOW(gtk_widget_get_toplevel(widget)), GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel",
        GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL));
    gtk_file_chooser_set_do_overwrite_confirmation(dialog, TRUE);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        filename = gtk_file_chooser_get_filename(dialog);

        GtkTextIter start, end;
        gchar *contents;

        gtk_text_buffer_get_start_iter(text_buffer, &start);
        gtk_text_buffer_get_end_iter(text_buffer, &end);

        contents = gtk_text_buffer_get_text(text_buffer, &start, &end, FALSE);

        xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
        xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "textView");
        xmlDocSetRootElement(doc, root_node);

        gchar **lines = g_strsplit(contents, "\n", -1);

        for (int i = 0; lines[i] != NULL && lines[i][0] != '\0'; i++) {
            gchar *escaped_content = xmlEncodeSpecialChars(NULL, BAD_CAST lines[i]);
            xmlNodePtr row_node = xmlNewChild(root_node, NULL, BAD_CAST "row", NULL);

            xmlNodePtr content_node = xmlNewChild(row_node, NULL, BAD_CAST "content", BAD_CAST escaped_content);
            g_free(escaped_content);

            time_t rawtime;
            struct tm *timeinfo;
            char buffer[80];

            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(buffer, 80, "%Y-%m-%dT%H:%M:%S", timeinfo);

            xmlNodePtr timestamp_node = xmlNewChild(row_node, NULL, BAD_CAST "timestamp", BAD_CAST buffer);
        }

        xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);

        xmlFreeDoc(doc);
        xmlCleanupParser();
        g_strfreev(lines);
        g_free(contents);
        g_free(filename);
    }

    gtk_widget_destroy(GTK_WIDGET(dialog));
}

/**
 * @brief Clear the text view buffer
 *
 * @param widget The widget that triggered the callback
 * @param data User data (unused)
 */
void clear_text_view(GtkWidget *widget, gpointer data) { gtk_text_buffer_set_text(text_buffer, "", -1); }

/**
 * @brief Callback for window destroy signal
 *
 * @param widget The widget that triggered the callback
 * @param data User data (unused)
 */
void on_window_destroy(GtkWidget *widget, gpointer data) {
    close(serial_port);
    gtk_main_quit();
}

/**
 * @brief Main function
 *
 * @param argc Argument count
 * @param argv Argument values
 *
 * @return Exit status
 */
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    serial_port = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_SYNC);
    if (serial_port < 0) {
        perror("Error opening serial port");
        return 1;
    }

    GtkBuilder *builder = gtk_builder_new();

    gchar *glade_path = g_build_filename(g_get_current_dir(), "gui.glade", NULL);
    g_print("Loading GUI file from: %s\n", glade_path);

    if (!gtk_builder_add_from_file(builder, glade_path, NULL)) {
        g_critical("Unable to load GUI file: %s", glade_path);
        g_free(glade_path);
        return 1;
    }
    g_free(glade_path);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    command_entry = GTK_WIDGET(gtk_builder_get_object(builder, "command_entry"));
    baudrate_combobox = GTK_WIDGET(gtk_builder_get_object(builder, "baudrate_combobox"));
    GtkWidget *send_button = GTK_WIDGET(gtk_builder_get_object(builder, "send_button"));
    GtkWidget *export_menuitem = GTK_WIDGET(gtk_builder_get_object(builder, "export_menuitem"));
    GtkWidget *clear_menuitem = GTK_WIDGET(gtk_builder_get_object(builder, "clear_menuitem"));
    GtkWidget *text_view = GTK_WIDGET(gtk_builder_get_object(builder, "output_text_view"));

    if (!window || !command_entry || !baudrate_combobox || !send_button || !export_menuitem || !clear_menuitem ||
        !text_view) {
        g_critical("Unable to find all UI elements");
        return 1;
    }

    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    g_signal_connect(send_button, "clicked", G_CALLBACK(send_command), NULL);
    g_signal_connect(command_entry, "activate", G_CALLBACK(send_command), NULL);
    g_signal_connect(export_menuitem, "activate", G_CALLBACK(export_to_xml), NULL);   // Note "activate" for menu item
    g_signal_connect(clear_menuitem, "activate", G_CALLBACK(clear_text_view), NULL);  // "activate" for menu item
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
