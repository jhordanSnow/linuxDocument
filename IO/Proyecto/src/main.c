#include "common.c"
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    /* Init GTK+ */
    gtk_init(&argc, &argv);
    createBuilder("MainMenu");
    gtk_builder_connect_signals(gtkBuilder, NULL);

    showWindow(gtkBuilder,"mainMenu");
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

int knapsackAction(GtkButton *button, GtkWidget *targetWindow)
{
    system("./knapsack &");
    return 0;
}

int sportsSeriesAction(GtkButton *button, GtkWidget *targetWindow)
{
    system("./sportsSeries &");
    return 0;
}

int reemplazoDeEquiposAction(GtkButton *button, GtkWidget *targetWindow)
{
    system("./reemplazoDeEquipos &");
    return 0;
}

int BSTAction(GtkButton *button, GtkWidget *targetWindow)
{
  system("./BST &");
  return 0;
}

int pendingAction(GtkButton *button, GtkWidget *targetWindow)
{
    system("./pending &");
    return 0;
}
