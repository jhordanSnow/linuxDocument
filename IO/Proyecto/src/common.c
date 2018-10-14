#include <string.h>
#include <gtk/gtk.h>
GtkBuilder* gtkBuilder;

int validateEntry(char* entry){
  int i = 0;
  if (entry[0] == '-') return 0;
  for (; entry[i] != 0; i++){
    if (entry[i] > 57 || entry[i] < 48) return 0;
  }
  return 1;
}

void createBuilder(char* filename){

  char GLADE_FILE[120] = "glade/";
  strcat(GLADE_FILE, filename);
  strcat(GLADE_FILE, ".glade");

  /* Create new GtkBuilder object */
  gtkBuilder = gtk_builder_new();
  /* Load UI from file */
  gtk_builder_add_from_file(gtkBuilder, GLADE_FILE , NULL);
}

GtkWidget* showWindow(GtkBuilder *gtkBuilder, char *windowName){
    GtkWidget *window;
    /* Get main window pointer from UI */
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, windowName));
    /* Destroy builder */
    //g_object_unref(G_OBJECT(gtkBuilder));
    /* Show window. */
    gtk_widget_show_all(window);

    return window;
}

// Called when window is closed
void on_main_destroy(){

    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_main_quit();
}
