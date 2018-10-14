#include "common.c"
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    /* Init GTK+ */
    gtk_init(&argc, &argv);
    createBuilder("Pending");
    gtk_builder_connect_signals(gtkBuilder, NULL);

    showWindow(gtkBuilder,"main");
    /* Start main loop */
    gtk_main();

    return 0;
}
