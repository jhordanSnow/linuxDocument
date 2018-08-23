#include "common.c"
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    /* Init GTK+ */
    gtk_init(&argc, &argv);
    showWindow("Floyd", "main");
    /* Start main loop */
    gtk_main();

    return 0;
}


void on_newNode_click(GtkEntry textEntry){
  
}
