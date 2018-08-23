#include "common.c"
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    /* Init GTK+ */
    gtk_init(&argc, &argv);
    showWindow("MainMenu","mainMenu");
    /* Start main loop */
    gtk_main();

    return 0;
}

// Evento cuando se da click al botón de ruta mas corta
int floydAction(GtkButton *button, GtkWidget *targetWindow)
{
    system("./floyd &");
    return 0;
}

int pendingAction(GtkButton *button, GtkWidget *targetWindow)
{
    system("./pending &");
    return 0;
}
