#include <string.h>
#include <math.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include "common.c"

typedef struct {
  GtkWidget *grid;
  GtkWidget *gridP;
  GtkWidget *cantNodes;
  GtkWidget *titleTable;
  GtkWidget *titleTableP;
  GtkWidget *contentPages;
  GtkWidget *btnNextTable;
  GtkWidget *contentGrafo;
  GtkWidget *editName;
  GtkWidget *graphArea;
  GtkWidget *nameList;
  GtkWidget *PMatrixContent;
  GtkWidget *uploadFilePicker;
  GtkWidget *btnPreviousTable;
  GtkWidget *targetName;
  GtkWidget *btnRutaOptima;
  GtkWidget *nodoPartida;
  GtkWidget *nodoLlegada;
  GtkWidget *modalRutaOptima;
} app_widgets;

GtkWidget *currentWindow;
PangoAttrList* attrDisable;
PangoAttrList* attrEnable;
PangoAttrList* attrChanged;
PangoAttrList* attrChanged2;

int CANT_NODES;
double ***D;
int ***P;
float **nodePos;

int currentTable;
int currentColor;

cairo_t *crGlobal;

char **names;
int currentShow;

void fillGrid(GtkGrid *grid, GtkGrid *gridP, app_widgets* appWdgets);
void draw_callback (GtkWidget *widget, cairo_t *cr, app_widgets* appWdgets, int color);
int getIdName(char* name);

int main(int argc, char *argv[]){
  currentTable = 0;
  currentColor = 0;
  currentShow = 0;

  gtk_init(&argc, &argv);
  createBuilder("Floyd");

  app_widgets *widgets = g_slice_new(app_widgets);

  widgets->grid  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "containerMatix"));
  widgets->gridP  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "containerMatrixP"));
  widgets->cantNodes  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "cantNodes"));
  widgets->titleTable  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "titleTable"));
  widgets->titleTableP  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "titleTableP"));
  widgets->contentGrafo  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "contentGrafo"));
  widgets->contentPages  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "contentPages"));
  widgets->btnNextTable  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "btnNextTable"));
  widgets->PMatrixContent  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "PMatrixContent"));
  widgets->uploadFilePicker  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "uploadFilePicker"));
  widgets->btnPreviousTable  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "btnPreviousTable"));
  widgets->graphArea  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "graphArea"));
  widgets->editName  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "editName"));
  widgets->nameList  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "nameList"));
  widgets->targetName  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "targetName"));
  widgets->btnRutaOptima  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "btnRutaOptima"));
  widgets->nodoPartida  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "nodoPartida"));
  widgets->nodoLlegada  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "nodoLlegada"));
  widgets->modalRutaOptima  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "modalRutaOptima"));

  attrDisable = pango_attr_list_new();
  attrEnable = pango_attr_list_new();
  attrChanged = pango_attr_list_new();
  attrChanged2 = pango_attr_list_new();

  PangoAttribute* textColor = pango_attr_foreground_new(0,0,0);
  pango_attr_list_insert(attrDisable, textColor);

  textColor = pango_attr_foreground_new(65535,0,0);
  pango_attr_list_insert(attrChanged, textColor);

  textColor = pango_attr_foreground_new(0,0,65535);
  pango_attr_list_insert(attrChanged2, textColor);

  textColor = pango_attr_foreground_new(10000,10000,10000);
  pango_attr_list_insert(attrEnable, textColor);

  gtk_builder_connect_signals(gtkBuilder, widgets);

  currentWindow = showWindow(gtkBuilder, "selection");
  gtk_main();

  return 0;
}

void automatic_entry(GtkButton *button, app_widgets *appWdgets){

  char *filename;
  GtkFileChooser *chooser = GTK_FILE_CHOOSER (appWdgets->uploadFilePicker);
  filename = gtk_file_chooser_get_filename (chooser);

  //int success = 1;

  FILE *f = fopen(filename, "r");
  if (f == NULL){
    showMessage("Error al abrir el archivo", currentWindow);
  }else{
    CANT_NODES = 20;
    nodePos = malloc(CANT_NODES * sizeof(float *));
    D = malloc((CANT_NODES + 1) * sizeof(double *));
    P = malloc((CANT_NODES + 1) * sizeof(int *));
    for (int i = 0; i <= CANT_NODES; i++) {
      nodePos[i] = malloc(2 * sizeof(float));
      D[i] = malloc(CANT_NODES * sizeof(double *));
      P[i] = malloc(CANT_NODES * sizeof(int *));
      for (int j = 0; j < CANT_NODES; j++) {
        D[i][j] = malloc(CANT_NODES * sizeof(double));
        P[i][j] = malloc(CANT_NODES * sizeof(int));
        for (int k = 0; k < CANT_NODES; k++) {
          P[i][j][k] = 0;
          if (j == k){
            D[i][j][k] = 0;
          }else{
            D[i][j][k] = INFINITY;
          }
        }
      }
    }

    int row = 0, col = 0;
    char fileContent[20];
    while(fscanf(f, "%s", fileContent) > 0){
      if (strcmp(fileContent, ";") == 0){
        CANT_NODES = col;
        row++;
        col = 0;
      }else{
        D[0][row][col] = atof(fileContent);
        col++;
      }
    }

    showMessage("Archivo cargado correctamente", currentWindow);
    fclose(f);


    gtk_widget_destroy(currentWindow);
    currentWindow = showWindow(gtkBuilder, "main");

    fillGrid(GTK_GRID(appWdgets->grid), GTK_GRID(appWdgets->gridP), appWdgets);
  }


}

void manual_entry(GtkButton *button, app_widgets *app_wdgts){
  CANT_NODES = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->cantNodes));

  nodePos = malloc(CANT_NODES * sizeof(float *));
  D = malloc((CANT_NODES + 1) * sizeof(double *));
  P = malloc((CANT_NODES + 1) * sizeof(int *));
  for (int i = 0; i <= CANT_NODES; i++) {
    nodePos[i] = malloc(2 * sizeof(float));
    D[i] = malloc(CANT_NODES * sizeof(double *));
    P[i] = malloc(CANT_NODES * sizeof(int *));
    for (int j = 0; j < CANT_NODES; j++) {
      D[i][j] = malloc(CANT_NODES * sizeof(double));
      P[i][j] = malloc(CANT_NODES * sizeof(int));
      for (int k = 0; k < CANT_NODES; k++) {
        P[i][j][k] = 0;
        if (j == k){
          D[i][j][k] = 0;
        }else{
          D[i][j][k] = INFINITY;
        }
      }
    }
  }

  gtk_widget_destroy(currentWindow);
  currentWindow = showWindow(gtkBuilder, "main");

  fillGrid(GTK_GRID(app_wdgts->grid), GTK_GRID(app_wdgts->gridP), app_wdgts);
}

void changedValue(GtkEntry* entry, app_widgets *app_wdgts){
  const char* text = gtk_entry_get_text(entry);
  char textTmp[20];
  sprintf(textTmp, "%s", text);
  if (gtk_widget_get_sensitive(GTK_WIDGET(entry)) == TRUE){
    if (validateEntry(textTmp) == 0){
      char defaultValue[10];
      sprintf(defaultValue, "%2.f", INFINITY);
      gtk_entry_set_text(entry, defaultValue);
    }
    //gtk_widget_queue_draw(app_wdgts->graphArea);
    draw_callback(app_wdgts->graphArea, crGlobal, app_wdgts,0);
  }
}

void addTooltips(GtkGrid *grid, GtkGrid *gridP){
  for (int i = 0; i < CANT_NODES; i++) {
    for (int j = 0; j < CANT_NODES; j++) {
      GtkWidget* entry = gtk_grid_get_child_at(grid, i+1, j+1);
      GtkWidget* entry2 = gtk_grid_get_child_at(gridP, i+1, j+1);
      char entryHelp[50];
      sprintf(entryHelp, "%s , %s", names[j+1], names[i+1]);
      gtk_widget_set_tooltip_text(entry, entryHelp);
      gtk_widget_set_tooltip_text(entry2, entryHelp);
    }
  }
}

void fillGrid(GtkGrid *grid, GtkGrid *gridP, app_widgets* appWdgets){
  char initialName = 65;

  gtk_grid_set_row_spacing(grid, 15);
  gtk_grid_set_column_spacing(grid, 15);
  gtk_grid_set_row_spacing(gridP, 15);
  gtk_grid_set_column_spacing(gridP, 40);

  names = malloc((CANT_NODES + 1) * sizeof(char *));
  for (int i = 1; i <= CANT_NODES; i++) {
    gtk_grid_insert_row(grid, i);
    gtk_grid_insert_row(gridP, i);

    int tmpRound = (i-1) / 26;
    char *name = malloc(5 * sizeof(char));
    name[0] = initialName + ((i-1) % 26);
    name[1] = (tmpRound == 0) ? 0 : 48 + tmpRound;
    name[2] = 0;

    names[i] = name;

    for (int j = 1; j <= CANT_NODES; j++) {
      if (i == 1){
        gtk_grid_insert_column(grid, j);
        gtk_grid_insert_column(gridP, j);
      }
      char defaultValue[10];
      sprintf(defaultValue, "%2.f", D[0][i-1][j-1]);

      GtkWidget *entry = gtk_entry_new_with_buffer(gtk_entry_buffer_new (defaultValue,-1));

      gtk_entry_set_width_chars(GTK_ENTRY(entry), 5);
      g_signal_connect(G_OBJECT(entry), "changed", G_CALLBACK(changedValue), appWdgets);

      gtk_grid_attach(grid, GTK_WIDGET(entry), j, i, 1, 1);
      gtk_grid_attach(gridP, gtk_label_new("0"), j, i, 1, 1);
    }

    gtk_grid_attach(grid, GTK_WIDGET(gtk_label_new(name)), i, 0, 1, 1);
    gtk_grid_attach(grid, GTK_WIDGET(gtk_label_new(name)), 0, i, 1, 1);
    gtk_grid_attach(gridP, GTK_WIDGET(gtk_label_new(name)), i, 0, 1, 1);
    gtk_grid_attach(gridP, GTK_WIDGET(gtk_label_new(name)), 0, i, 1, 1);
  }

  addTooltips(grid, gridP);
  gtk_widget_show_all(currentWindow);
}

void updateLastView(int row, int col, GtkGrid* grid, GtkGrid* gridP){
  GtkEntry* entryBox = GTK_ENTRY(gtk_grid_get_child_at(grid, row, col));
  GtkLabel* tablePEntry = GTK_LABEL(gtk_grid_get_child_at(gridP, row, col));
  char value[10];
  sprintf(value, "%2.f", D[currentTable][row-1][col-1]);
  gtk_entry_set_text(entryBox, value);

  sprintf(value, "%d", P[currentTable][row-1][col-1]);
  gtk_label_set_text(tablePEntry, value);

  gtk_entry_set_attributes(entryBox, attrDisable);
  if (currentTable == 0){
    gtk_entry_set_attributes(entryBox, attrEnable);
  }
}

void updateView(int row, int col, double newValue, GtkGrid* grid, GtkGrid* gridP){
  GtkEntry* entryBox = GTK_ENTRY(gtk_grid_get_child_at(grid, row, col));
  GtkLabel* tablePEntry = GTK_LABEL(gtk_grid_get_child_at(gridP, row, col));
  char value[10];
  sprintf(value, "%2.f", newValue);
  gtk_entry_set_text(entryBox, value);
  gtk_label_set_text(tablePEntry, names[currentTable]);

  if (currentColor == 0){
    gtk_entry_set_attributes(entryBox, attrChanged);
    gtk_label_set_attributes(tablePEntry, attrChanged);
  }else{
    gtk_entry_set_attributes(entryBox, attrChanged2);
    gtk_label_set_attributes(tablePEntry, attrChanged2);
  }
  gtk_widget_show_all(currentWindow);
}


void updateTable(GtkGrid* grid, GtkGrid* gridP){
  for (int i = 0; i < CANT_NODES; i++) {
    for (int j = 0; j < CANT_NODES; j++) {
      GtkEntry* entryBox = GTK_ENTRY(gtk_grid_get_child_at(grid, i+1, j+1));
      double val = atof(gtk_entry_get_text(entryBox));
      D[0][i][j] = val;
    }
  }
}

void disableFields(GtkGrid* grid, GtkGrid* gridP){
  for (int i = 0; i < CANT_NODES; i++) {
    for (int j = 0; j < CANT_NODES; j++) {
      GtkWidget* entry = gtk_grid_get_child_at(grid, i+1, j+1);
      gtk_widget_set_sensitive(entry,FALSE);
      gtk_entry_set_attributes(GTK_ENTRY(entry), attrDisable);

      GtkLabel* tablePEntry = GTK_LABEL(gtk_grid_get_child_at(gridP, i+1, j+1));
      gtk_label_set_attributes(GTK_LABEL(tablePEntry), attrDisable);
    }
  }
}

void enableFields(GtkGrid* grid, GtkGrid* gridP){
  for (int i = 0; i < CANT_NODES; i++) {
    for (int j = 0; j < CANT_NODES; j++) {
      GtkWidget* entry = gtk_grid_get_child_at(grid, i+1, j+1);
      gtk_entry_set_attributes(GTK_ENTRY(entry), attrEnable);

      GtkLabel* tablePEntry = GTK_LABEL(gtk_grid_get_child_at(gridP, i+1, j+1));
      gtk_label_set_attributes(GTK_LABEL(tablePEntry), attrDisable);
      gtk_widget_set_sensitive(entry,TRUE);
    }
  }
}

void updateTableTitle(GtkLabel* label, GtkLabel* labelP){
  char value[10];
  sprintf(value, "D(%d)", currentTable);
  gtk_label_set_text(label, value);
  sprintf(value, "P(%d)", currentTable);
  gtk_label_set_text(labelP, value);
}

void previousTable(GtkButton *button, app_widgets *appWdgets){
  if (currentTable == CANT_NODES){
    gtk_widget_set_sensitive(appWdgets->btnNextTable, TRUE);
    gtk_widget_set_sensitive(appWdgets->btnRutaOptima, FALSE);
  }
  currentTable--;
  if (currentTable == 0){
    enableFields(GTK_GRID(appWdgets->grid), GTK_GRID(appWdgets->gridP));
    gtk_widget_set_sensitive(appWdgets->btnPreviousTable, FALSE);
    gtk_stack_set_visible_child(GTK_STACK(appWdgets->contentPages), appWdgets->contentGrafo);
    currentShow = 0;
  }

  updateTableTitle(GTK_LABEL(appWdgets->titleTable), GTK_LABEL(appWdgets->titleTableP));

  for (int i = 0; i < CANT_NODES; i++) {
    for (int j = 0; j < CANT_NODES; j++) {
      updateLastView(i+1, j+1, GTK_GRID(appWdgets->grid), GTK_GRID(appWdgets->gridP));
    }
  }
}

void nextTable(GtkButton *button, app_widgets *appWdgets){
  disableFields(GTK_GRID(appWdgets->grid), GTK_GRID(appWdgets->gridP));
  if (currentTable + 1 == CANT_NODES){
    gtk_widget_set_sensitive(appWdgets->btnNextTable, FALSE);
    gtk_widget_set_sensitive(appWdgets->btnRutaOptima, TRUE);
  }
  if (currentTable == 0){
    updateTable(GTK_GRID(appWdgets->grid), GTK_GRID(appWdgets->gridP));
    gtk_widget_set_sensitive(appWdgets->btnPreviousTable, TRUE);
    gtk_stack_set_visible_child(GTK_STACK(appWdgets->contentPages), appWdgets->PMatrixContent);
    currentShow = 1;
  }

  currentTable++;
  updateTableTitle(GTK_LABEL(appWdgets->titleTable), GTK_LABEL(appWdgets->titleTableP));
  int tmpChanged = 0;
  for (int i = 0; i < CANT_NODES; i++) {
    for (int j = 0; j < CANT_NODES; j++) {
      for (int k = 0; k < CANT_NODES; k++) {
        double tmpValue = D[currentTable-1][j][currentTable-1] + D[currentTable-1][currentTable-1][k];
        if(tmpValue < D[currentTable-1][j][k]){
          D[currentTable][j][k] = tmpValue;
          P[currentTable][j][k] = currentTable;
          tmpChanged = 1;
          updateView(j+1, k+1, tmpValue, GTK_GRID(appWdgets->grid),  GTK_GRID(appWdgets->gridP));
        }else{
          D[currentTable][j][k] = D[currentTable-1][j][k];
        }
      }
    }
  }
  currentColor = (currentColor == 0 && tmpChanged == 1) ? 1 : 0;
}


void downloadFile(GtkButton button, app_widgets *appWdgets){
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;
  GtkWidget *dialog = gtk_file_chooser_dialog_new ("Guardar Como",GTK_WINDOW(currentWindow),action,"Cancelar",GTK_RESPONSE_CANCEL,"Guardar",GTK_RESPONSE_ACCEPT,NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT){
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);

    int success = 1;

    FILE *f = fopen(filename, "w");
    if (f == NULL){
      showMessage("Error al abrir el archivo", currentWindow);
    }else{

      for (int i = 0; i < CANT_NODES; i++) {
        for (int j = 0; j < CANT_NODES; j++) {
          if (success == 1){
            if (fprintf(f, "%f", D[0][i][j]) <= 0){
              success = 0;
            }
          }
          (j == CANT_NODES - 1) ? fprintf(f, " ; ") : fprintf(f, " ");
        }
      }

      if (success == 1){
        showMessage("Archivo exportado correctamente", currentWindow);
      }else{
        showMessage("Ocurrió un error al exportar el archivo", currentWindow);
      }

      fclose(f);
    }
  }
  gtk_widget_destroy (dialog);
}

void printRuta(int salida, int llegada){
  if (llegada == P[currentTable][salida][llegada]){
    printf("%d -> ", P[currentTable][salida][llegada]);
  }
  if (P[currentTable][salida][llegada] == 0){
    printf("no hay camino\n");
  }else{
    printRuta(salida, P[currentTable][salida][llegada]);
    printRuta(P[currentTable][salida][llegada], llegada);
  }
}

void calculatePath(GtkWidget *widget, app_widgets* appWdgets){
  draw_callback(appWdgets->graphArea, crGlobal, appWdgets, 1);

  int salida = getIdName(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(appWdgets->nodoPartida)));
  int llegada = getIdName(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(appWdgets->nodoLlegada)));

  printRuta(salida,llegada);
}

void draw_callback (GtkWidget *widget, cairo_t *cr, app_widgets* appWdgets, int colorInt) {
  crGlobal = cr;
  guint width, height;
  GdkRGBA color;
  GtkStyleContext *context;

  context = gtk_widget_get_style_context(widget);

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);

  gtk_render_background (context, cr, 0, 0, width, height);

  float radius, nodeOffsetX, nodeOffsetY, posX, posY;
  int loneNodes, cantNodesSide, nodesAdded;

  radius = MIN (width, height) / (2 * CANT_NODES);
  loneNodes = CANT_NODES % 4;
  nodesAdded = 0;

  // top
  cantNodesSide = (loneNodes > 0) ? (CANT_NODES / 4) + 1 : CANT_NODES / 4;
  nodeOffsetX = (width - (cantNodesSide*radius))/cantNodesSide;

  posX = nodeOffsetX/2 + radius;
  posY = radius;
  for (int i = 0; i < cantNodesSide; i++) {
    nodePos[nodesAdded][0] = posX;
    nodePos[nodesAdded][1] = posY;
    cairo_move_to(cr, posX, posY);
    cairo_arc (cr, posX, posY, radius, 0, 2 * G_PI);
    posX += nodeOffsetX;
    nodesAdded++;
  }
  loneNodes--;



  // bottom
  cantNodesSide = (loneNodes > 0) ? (CANT_NODES / 4) + 1 : CANT_NODES / 4;
  nodeOffsetX = (width - (cantNodesSide*radius))/cantNodesSide;

  posX = nodeOffsetX/2 + radius;
  posY = height - radius;
  for (int i = 0; i < cantNodesSide; i++) {
    nodePos[nodesAdded][0] = posX;
    nodePos[nodesAdded][1] = posY;
    cairo_move_to(cr, posX, posY);
    cairo_arc (cr, posX, posY+1, radius, 0, 2 * G_PI);
    posX += nodeOffsetX + 1;
    nodesAdded++;
  }
  loneNodes--;

  // left
  cantNodesSide = (loneNodes > 0) ? (CANT_NODES / 4) + 1 : CANT_NODES / 4;
  nodeOffsetY = (height - (cantNodesSide*radius))/cantNodesSide;

  posX = radius;
  posY = nodeOffsetY/2 + radius;
  for (int i = 0; i < cantNodesSide; i++) {
    nodePos[nodesAdded][0] = posX;
    nodePos[nodesAdded][1] = posY;
    cairo_move_to(cr, posX, posY);
    cairo_arc (cr, posX, posY, radius, 0, 2 * G_PI);
    posY += nodeOffsetY;
    nodesAdded++;
  }

  // right
  cantNodesSide = CANT_NODES / 4;
  nodeOffsetY = (height - (cantNodesSide*radius))/cantNodesSide;

  posX = width - radius;
  posY = nodeOffsetY/2 + radius;
  for (int i = 0; i < cantNodesSide; i++) {
    nodePos[nodesAdded][0] = posX;
    nodePos[nodesAdded][1] = posY;
    cairo_move_to(cr, posX, posY);
    cairo_arc (cr, posX+1, posY, radius, 0, 2 * G_PI);
    posY += nodeOffsetY + 1;
    nodesAdded++;
  }

  gtk_style_context_get_color (context, gtk_style_context_get_state (context), &color);
  gdk_cairo_set_source_rgba (cr, &color);


  cairo_fill (cr);

  cairo_set_line_width(cr, 2);

  if (colorInt == 1){
    cairo_set_line_width(cr, 0.5);
  }

  for (int i = 0; i < CANT_NODES; i++) {
      for (int j = 0; j < CANT_NODES; j++) {
        if (D[0][i][j] != INFINITY ){
          if ( nodePos[i][1] == nodePos[j][1] && i!=j){
              double distance = (MAX(nodePos[j][0], nodePos[i][0]) - MIN(nodePos[j][0], nodePos[i][0]))/2;
              double center = (nodePos[j][0] + nodePos[i][0]) /2;
              if (nodePos[i][1] < height/2){
                cairo_move_to(cr, nodePos[i][0], nodePos[i][1]);
                cairo_arc(cr,center, nodePos[i][1], distance, 0.0, M_PI );
              }
              else{
                cairo_move_to(cr, nodePos[j][0], nodePos[j][1]);
                cairo_arc(cr,center, nodePos[i][1], distance, M_PI, 0.0 );
              }
                cairo_stroke(cr);
            }
            else{
              cairo_move_to(cr, nodePos[i][0], nodePos[i][1]);
              cairo_line_to(cr, nodePos[j][0], nodePos[j][1]);

            }
        }
      }
  }

  cairo_stroke(cr);
}

void rutaOptima(GtkButton *button, app_widgets *appWdgets){
  for (int i = 0; i < CANT_NODES; i++) {
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(appWdgets->nodoLlegada), i, "0", names[i+1]);
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(appWdgets->nodoPartida), i, "0", names[i+1]);
  }

  gtk_widget_show(appWdgets->modalRutaOptima);

  gtk_stack_set_visible_child(GTK_STACK(appWdgets->contentPages), appWdgets->contentGrafo);
  currentShow = 0;
}

void editName(GtkButton *button, app_widgets *appWdgets){
  for (int i = 0; i < CANT_NODES; i++) {
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(appWdgets->nameList), i, "0", names[i+1]);
  }

  gtk_widget_show(appWdgets->editName);
}

void closeWindow(GtkButton *button, app_widgets *appWdgets){
  gtk_widget_hide(appWdgets->editName);
  gtk_widget_unparent(appWdgets->editName);
}

void closeWindowR(GtkButton *button, app_widgets *appWdgets){
  gtk_widget_hide(appWdgets->modalRutaOptima);
  gtk_widget_unparent(appWdgets->modalRutaOptima);
}

int getIdName(char* name){
  for (int i = 0; i < CANT_NODES; i++) {
    if (strcmp(name,names[i]) == 0){
      return i;
    }
  }
  return -1;
}

void changeName(GtkButton *button, app_widgets *appWdgets){
  int id = getIdName(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(appWdgets->nameList)));
  const char* newName = gtk_entry_get_text(GTK_ENTRY(appWdgets->targetName));
  if (strlen(newName) > 0){
    if(id >= 0){
      sprintf(names[id], "%s", newName);

      GtkLabel* entryBox = GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(appWdgets->grid), 0, id));
      GtkLabel* tablePEntry = GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(appWdgets->gridP), 0, id));
      gtk_label_set_text(entryBox, names[id]);
      gtk_label_set_text(tablePEntry, names[id]);

      entryBox = GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(appWdgets->grid), id, 0));
      tablePEntry = GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(appWdgets->gridP), id, 0));
      gtk_label_set_text(entryBox, names[id]);
      gtk_label_set_text(tablePEntry, names[id]);

      addTooltips(GTK_GRID(appWdgets->grid), GTK_GRID(appWdgets->gridP));
    }
  }else{
    showMessage("El nombre no puede estar vacío.", currentWindow);
  }

  gtk_widget_show_all(currentWindow);
}

void changeView(GtkButton *button, app_widgets *appWdgets){
  if (currentShow == 0){
    gtk_stack_set_visible_child(GTK_STACK(appWdgets->contentPages), appWdgets->contentGrafo);
    currentShow = 1;
  }else{
    gtk_stack_set_visible_child(GTK_STACK(appWdgets->contentPages), appWdgets->PMatrixContent);
    currentShow = 0;
  }

  updateTableTitle(GTK_LABEL(appWdgets->titleTable), GTK_LABEL(appWdgets->titleTableP));
  gtk_widget_show_all(currentWindow);
}
