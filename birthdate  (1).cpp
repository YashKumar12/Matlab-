#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <gtk/gtk.h>

// Function to handle button click event
static void button_clicked(GtkWidget *widget, gpointer data) {
    // Retrieve the text from the input fields
    GtkWidget *year_entry = GTK_WIDGET(data);
    GtkWidget *month_entry = GTK_ENTRY(gtk_builder_get_object(builder, "month_entry"));
    GtkWidget *time_entry = GTK_ENTRY(gtk_builder_get_object(builder, "time_entry"));
    GtkWidget *date_entry = GTK_ENTRY(gtk_builder_get_object(builder, "date_entry"));

    const gchar *year_text = gtk_entry_get_text(GTK_ENTRY(year_entry));
    const gchar *month_text = gtk_entry_get_text(GTK_ENTRY(month_entry));
    const gchar *time_text = gtk_entry_get_text(GTK_ENTRY(time_entry));
    const gchar *date_text = gtk_entry_get_text(GTK_ENTRY(date_entry));

    // Perform calculations based on the input

    // Save the calculation history to a file
    std::ofstream historyFile("history.txt", std::ios::app);
    if (historyFile.is_open()) {
        std::string historyEntry = std::string(year_text) + ", " + std::string(month_text) + ", " +
                                   std::string(time_text) + ", " + std::string(date_text) + "\n";
        historyFile << historyEntry;
        historyFile.close();
    } else {
        std::cerr << "Error opening history file!" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Load the UI from the Glade file
    GtkBuilder *builder = gtk_builder_new_from_file("calculator.glade");

    // Get the main window widget
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    // Connect the button click event to the handler function
    GtkWidget *calculate_button = GTK_WIDGET(gtk_builder_get_object(builder, "calculate_button"));
    GtkWidget *year_entry = GTK_WIDGET(gtk_builder_get_object(builder, "year_entry"));
    g_signal_connect(calculate_button, "clicked", G_CALLBACK(button_clicked), year_entry);

    // Show the window and start the GTK main loop
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
