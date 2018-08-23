#include <string.h>
#include <gtk/gtk.h>

void showWindow(char *filename, char *windowName)
{
    GtkBuilder *gtkBuilder;
    GtkWidget *window;

    char GLADE_FILE[120] = "glade/";
    strcat(GLADE_FILE, filename);
    strcat(GLADE_FILE, ".glade");


    /* Create new GtkBuilder object */
    gtkBuilder = gtk_builder_new();
    /* Load UI from file */
    gtk_builder_add_from_file(gtkBuilder, GLADE_FILE , NULL);
    /* Get main window pointer from UI */
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, windowName));
    /* Connects with the signals in Glade */
    gtk_builder_connect_signals(gtkBuilder, NULL);

    /* Destroy builder */
    g_object_unref(G_OBJECT(gtkBuilder));
    /* Show window. */
    gtk_widget_show(window);
}

// Called when window is closed
void on_main_destroy()
{
    gtk_main_quit();
}
