#include "common.c"
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    /* Init GTK+ */
    gtk_init(&argc, &argv);
    showWindow("Pending","main");
    /* Start main loop */
    gtk_main();

    return 0;
}
