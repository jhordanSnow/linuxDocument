#include <string.h>
#include <math.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include "common.c"

typedef struct {
  GtkWidget *gridSolution;
  GtkWidget *labelRutas;
  GtkWidget *box1;
  GtkWidget *grid;
  GtkWidget *gridP;
  GtkWidget *dataGrid;
  GtkWidget *enterData;
  GtkWidget *costoEquipo;
  GtkWidget *resultWindow;
  GtkWidget *plazo;
  GtkWidget *inflacion;
  GtkWidget *vidaUtil;
  GtkWidget *ingresarGanancias;
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


GtkWidget** costosMantenimiento;
GtkWidget** ganancias;
GtkWidget** preciosReventa;

double* costosMantenimientoDouble;
double* gananciasDouble;
double* preciosReventaDouble;

GtkWidget *currentWindow;
GtkWidget *dataWindow;
PangoAttrList* attrDisable;
PangoAttrList* attrEnable;
PangoAttrList* attrChanged;
PangoAttrList* attrChanged2;

double costoEquipo;
double inflacion;
int plazo;
int vidaUtil;
double maxValue = 99999999999999;
int ingresarGanancias;
double* intervalosReemplazo;
double* minimos;
int **rutas;
double ***D;
int ***P;
double **nodePos;

int currentTable;
int currentColor;

cairo_t *crGlobal;

char **names;
int currentShow;

void fillGrid(GtkGrid *grid, app_widgets* app_wdgts);
void showMessage(char* message);
void submitData(app_widgets *app_wdgts);
void draw_callback (GtkWidget *widget, cairo_t *cr, app_widgets* appWdgets, int color);
void calculateReplacementPlan(app_widgets *app_wdgts);
int getIdName(char* name);
void downloadFile(GtkButton button, app_widgets *appWdgets);

int main(int argc, char *argv[]){
  currentTable = 0;
  currentColor = 0;
  currentShow = 0;

  gtk_init(&argc, &argv);
  createBuilder("reemplazoDeEquipos");

  app_widgets *widgets = g_slice_new(app_widgets);

  widgets->box1  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "box1"));
  widgets->labelRutas  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "labelRutas"));
  widgets->grid  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "containerMatix"));
  widgets->gridP  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "containerMatrixP"));
  widgets->resultWindow  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "resultWindow"));
  widgets->enterData  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "enterData"));
  widgets->dataGrid  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "dataGrid"));
  widgets->costoEquipo  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "costoEquipo"));
  widgets->vidaUtil  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "vidaUtil"));
  widgets->plazo  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "plazo"));
  widgets->inflacion  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "inflacion"));
  widgets->ingresarGanancias  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "ingresarGanancias"));
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
  widgets->gridSolution  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "gridSolution"));

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

void fillDataGrid(){
  for (int i = 0 ; i < vidaUtil; i++ ){
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(costosMantenimiento[i]), costosMantenimientoDouble[i]);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(preciosReventa[i]), preciosReventaDouble[i]);
    if (ingresarGanancias) {
      gtk_spin_button_set_value(GTK_SPIN_BUTTON(ganancias[i]), gananciasDouble[i]);
    }
  }
}

void automatic_entry(GtkButton *button, app_widgets *appWdgets){

  char *filename;
  GtkFileChooser *chooser = GTK_FILE_CHOOSER (appWdgets->uploadFilePicker);
  filename = gtk_file_chooser_get_filename (chooser);

  int success = 1;

  FILE *f = fopen(filename, "r");
  if (f == NULL){
    showMessage("Error al abrir el archivo");
  }else{
    char fileContent[420];

    if (success == 1){
      if (fscanf(f, "%s", fileContent) > 0){
        ingresarGanancias = atoi(fileContent);
      }else{
        success = 0;
      }
    }

    if (success == 1){
      if (fscanf(f, "%s", fileContent) > 0){
        costoEquipo = atof(fileContent);
      }else{
        success = 0;
      }
    }

    if (success == 1){
      if (fscanf(f, "%s", fileContent) > 0){
        plazo = atoi(fileContent);
      }else{
        success = 0;
      }
    }

    if (success == 1){
      if (fscanf(f, "%s", fileContent) > 0){
        vidaUtil = atoi(fileContent);
      }else{
        success = 0;
      }
    }

    if (success == 1){
      if (fscanf(f, "%s", fileContent) > 0){
        inflacion = atof(fileContent);
      }else{
        success = 0;
      }
    }

    costosMantenimientoDouble = calloc(vidaUtil+1, sizeof(double));
    gananciasDouble = calloc(vidaUtil+1, sizeof(double));
    preciosReventaDouble = calloc(vidaUtil+1, sizeof(double));

    for (int i = 0; i < vidaUtil; i++) {
      if (success == 1 && fscanf(f, "%s", fileContent) > 0){
        if (strcmp(fileContent, "") != 0 && strcmp(fileContent, ";") != 0){
            costosMantenimientoDouble[i] = atof(fileContent);
        }else{
            success = 0;
        }
      }
      if (success == 1 && fscanf(f, "%s", fileContent) > 0){
        if (strcmp(fileContent, "") != 0 && strcmp(fileContent, ";") != 0){
            gananciasDouble[i] = atof(fileContent);
        }else{
            success = 0;
        }
      }
      if (success == 1 && fscanf(f, "%s", fileContent) > 0){
        if (strcmp(fileContent, "") != 0 && strcmp(fileContent, ";") != 0){
            preciosReventaDouble[i] = atof(fileContent);
        }else{
            success = 0;
        }
      }
    }

    showMessage("Archivo cargado correctamente");
    fclose(f);

    gtk_widget_destroy(currentWindow);
    fillGrid(GTK_GRID(appWdgets->dataGrid), appWdgets);
    fillDataGrid();

  }


}

void manual_entry(GtkButton *button, app_widgets *app_wdgts){
  plazo = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->plazo));
  costoEquipo = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app_wdgts->costoEquipo));
  inflacion = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app_wdgts->inflacion));
  vidaUtil = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->vidaUtil));
  ingresarGanancias = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->ingresarGanancias));

  gtk_widget_destroy(currentWindow);

  fillGrid(GTK_GRID(app_wdgts->dataGrid), app_wdgts);
}



void fillGrid(GtkGrid *grid, app_widgets* app_wdgts){
  gtk_grid_set_row_spacing(grid, 15);
  gtk_grid_set_column_spacing(grid, 15);

  preciosReventa = calloc((vidaUtil + 1), sizeof(GtkSpinButton*));
  costosMantenimiento = calloc((vidaUtil + 1), sizeof(GtkSpinButton*));

  gtk_grid_insert_row(grid, 0);

  GtkWidget *lblReventa;
  GtkWidget *lblGanancia;
  GtkWidget *lblMantenimiento;

  gtk_grid_insert_column(grid, 0);
  gtk_grid_insert_column(grid, 1);
  gtk_grid_insert_column(grid, 2);
  lblReventa = gtk_label_new("Precio de Reventa");
  gtk_grid_attach(grid, GTK_WIDGET(lblReventa), 0,0,1,1);
  lblMantenimiento = gtk_label_new("Costo de Mantenimiento");
  gtk_grid_attach(grid, GTK_WIDGET(lblMantenimiento), 1,0,1,1);
  if(ingresarGanancias){
    ganancias = malloc((vidaUtil+1) * sizeof(GtkToggleButton*));
    gtk_grid_insert_column(grid, 3);
    lblGanancia = gtk_label_new("Ganancia Recibida");
    gtk_grid_attach(grid, GTK_WIDGET(lblGanancia), 2,0,1,1);
  }
  for (int i = 1; i <= vidaUtil; i++) {

      gtk_grid_insert_row(grid, i);

      GtkWidget *precioReventaEntry;
      GtkWidget *costoMantenimientoEntry;
      GtkAdjustment *adjReventa;
      GtkAdjustment *adjMantenimiento;

      precioReventaEntry = gtk_spin_button_new(0,maxValue, 1);
      adjReventa = gtk_adjustment_new(0,0,maxValue,1,10,0);
      gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(precioReventaEntry), adjReventa);

      costoMantenimientoEntry = gtk_spin_button_new(0,maxValue, 1);
      adjMantenimiento = gtk_adjustment_new(0,0,maxValue,1,10,0);
      gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(costoMantenimientoEntry), adjMantenimiento);


      gtk_grid_attach(grid, GTK_WIDGET(precioReventaEntry), 0,i,1,1);
      gtk_grid_attach(grid, GTK_WIDGET(costoMantenimientoEntry), 1,i,1,1);

      preciosReventa[i - 1] = precioReventaEntry;
      costosMantenimiento[i - 1] = costoMantenimientoEntry;

      if(ingresarGanancias){
        GtkWidget *gananciaEntry;
        GtkAdjustment *adjGanancia;
        gananciaEntry = gtk_spin_button_new(0,maxValue, 1);
        adjGanancia = gtk_adjustment_new(0,0,maxValue,1,10,0);
        gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(gananciaEntry), adjGanancia);
        gtk_grid_attach(grid, GTK_WIDGET(gananciaEntry), 2,i,1,1);
        ganancias[i-1] = gananciaEntry;
      }

    }


  gtk_grid_insert_row(grid, vidaUtil+1);

  GtkWidget *button;
  button = gtk_button_new_with_label("Aceptar");
  gtk_grid_attach(grid, button, 0,vidaUtil+1,1,1);
  g_signal_connect(button, "clicked", G_CALLBACK(submitData), app_wdgts);


  GtkWidget *button2;
  button2 = gtk_button_new_with_label("Exportar");
  gtk_grid_attach(grid, button2, 1,vidaUtil+1,1,1);
  g_signal_connect(button2, "clicked", G_CALLBACK(downloadFile), app_wdgts);


  gtk_widget_show_all(app_wdgts->dataGrid);
  dataWindow = showWindow(gtkBuilder, "enterData");

}

void uploadData(app_widgets* app_wdgts){
  costosMantenimientoDouble = calloc((vidaUtil + 1), sizeof(double));
  preciosReventaDouble = calloc((vidaUtil + 1), sizeof(double));
  gananciasDouble = calloc((vidaUtil + 1), sizeof(double));
  for (int i = 0 ; i < vidaUtil; i++ ){
    costosMantenimientoDouble[i] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(costosMantenimiento[i]));
    preciosReventaDouble[i] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(preciosReventa[i]));
    gananciasDouble[i] = 0.0;
    if (ingresarGanancias) {
      gananciasDouble[i] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ganancias[i]));
    }
  }
}

void ShowResultMatrix(GtkGrid* grid){
  char message[1420] = "t \t|\t G(t) \t|\t Próximo \n";
  char buffer[512] = "---------------------------------\n";
  strcat(message, buffer);

  for (int i = plazo; i >= 0; i--) {
    char buffer2[420];
    if (i != 0){
    snprintf(buffer, sizeof(buffer), "%d \t|\t %0.2f \t|\t ", plazo - i, minimos[i]);
    }else{
      snprintf(buffer, sizeof(buffer), "%d \t|\t %0.2f \t\t|\t ", plazo - i, minimos[i]);
    }

    for (int j = 1 ; j <= vidaUtil ; j++ ){
      if (i == 0){
        snprintf(buffer2, sizeof(buffer2), "-");
        strcat(buffer, buffer2);
      }else{
        if (rutas[i][j] != 0){
          snprintf(buffer2, sizeof(buffer2), "%d,", rutas[i][j]);
          strcat(buffer, buffer2);
        }
      }
    }
    snprintf(buffer2, sizeof(buffer2), " \n");
    strcat(buffer, buffer2);
    strcat(message, buffer);
  }

  for (int j = 0 ; j < vidaUtil ; j++ ){

  }

  snprintf(buffer, sizeof(buffer), "\n\n -> -> ->");
  strcat(message, buffer);

  showMessage(message);
}

void submitData(app_widgets *app_wdgts){
  uploadData(app_wdgts);
  calculateReplacementPlan(app_wdgts);

  gtk_widget_destroy(dataWindow);
  currentWindow = showWindow(gtkBuilder, "content");

  ShowResultMatrix(GTK_GRID(app_wdgts->gridSolution));
}

void calculateReplacementPlan(app_widgets *app_wdgts){

  intervalosReemplazo = malloc((vidaUtil+1) * sizeof(double));
  minimos = malloc((plazo+1) * sizeof(double));
  rutas = malloc((plazo+1) * sizeof(int *));
  double costoMantenimiento = 0;
  double precioReventa;
  double ganancia;
  for (int i = 0 ; i < vidaUtil; i++ ){
    costoMantenimiento += costosMantenimientoDouble[i];
    precioReventa = preciosReventaDouble[i];
    double intervalo =  costoEquipo + costoMantenimiento - precioReventa ;
    if (ingresarGanancias){
      ganancia = gananciasDouble[i];
      intervalo -= ganancia;
    }
    intervalosReemplazo[i] = intervalo * inflacion;
  }
  minimos[0] = 0;
  //int curr = plazo;
  int indexRutas = 0;
  for (int i = 1 ; i <= plazo; i++ ){
    rutas[i] = calloc((vidaUtil+1),  sizeof(int));
    double currMin = maxValue;
    for (int j = 1  ; j <= vidaUtil; j++ ){
      int x = (plazo-i) + j;
      if (x < plazo+1){

        double currValue = intervalosReemplazo[j-1] + minimos[(i-1)-(j-1)];
        if (currValue < currMin){
          indexRutas  = 0;
          rutas[i] = calloc((vidaUtil+1), sizeof(int));
          currMin = currValue;
          rutas[i][indexRutas] = x;
          indexRutas ++;
        }
        if(currValue == currMin){
          rutas[i][indexRutas] = x;
          indexRutas ++;
        }
      }
    }
    minimos[i] = currMin;
    printf("Minimos %f\n", minimos[i]);
    for (int j = 0 ; j <= vidaUtil ; j++ ){
        printf("Ruta %d\n", rutas[i][j]);
    }
  }
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
    //draw_callback(app_wdgts->graphArea, crGlobal, app_wdgts,0);
  }
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



void showMessage(char* message){
  GtkWidget *messageDialog = gtk_message_dialog_new(GTK_WINDOW(currentWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, message);

  gtk_dialog_run (GTK_DIALOG (messageDialog));
  gtk_widget_destroy (messageDialog);
}

void downloadFile(GtkButton button, app_widgets *appWdgets){
  uploadData(appWdgets);
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
      showMessage("Error al abrir el archivo");
    }else{

      if (success == 1){
        if (fprintf(f, "%d", ingresarGanancias) <= 0){
          success = 0;
        }
        fprintf(f, " ");
      }

      if (success == 1){
        if (fprintf(f, "%f", costoEquipo) <= 0){
          success = 0;
        }
        fprintf(f, " ");
      }

      if (success == 1){
        if (fprintf(f, "%d", plazo) <= 0){
          success = 0;
        }
        fprintf(f, " ");
      }

      if (success == 1){
        if (fprintf(f, "%d", vidaUtil) <= 0){
          success = 0;
        }
        fprintf(f, " ");
      }

      if (success == 1){
        if (fprintf(f, "%f", inflacion) <= 0){
          success = 0;
        }
        fprintf(f, " ");
      }

      for (int i = 0; i < vidaUtil; i++) {
        if (success == 1){
          if (fprintf(f, "%f", costosMantenimientoDouble[i]) <= 0){
            success = 0;
          }
          fprintf(f, " ");
        }
        if (success == 1){
          if (fprintf(f, "%f", gananciasDouble[i]) <= 0){
            success = 0;
          }
          fprintf(f, " ");
        }
        if (success == 1){
          if (fprintf(f, "%f", preciosReventaDouble[i]) <= 0){
            success = 0;
          }
          fprintf(f, " ");
        }
      }

      fprintf(f, ";");

      if (success == 1){
        showMessage("Archivo exportado correctamente");
      }else{
        showMessage("Ocurrió un error al exportar el archivo");
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
  //draw_callback(appWdgets->graphArea, crGlobal, appWdgets, 1);

  int salida = getIdName(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(appWdgets->nodoPartida)));
  int llegada = getIdName(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(appWdgets->nodoLlegada)));

  printRuta(salida,llegada);
}

void draw_callback (GtkWidget *widget, cairo_t *cr, app_widgets* appWdgets, int colorInt) {
  crGlobal = cr;
  guint width, height;
  GdkRGBA color;
  GtkStyleContext *context;
  nodePos = calloc(plazo+1, sizeof(double*));

  context = gtk_widget_get_style_context(widget);

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);

  gtk_render_background (context, cr, 0, 0, width, height);

  double radius, posX, posY;


  radius = width / (2.5 * (plazo+1));

  posX = 1.5 * radius;
  posY = height - 1.5 * radius;
  for (int i = 0; i <= plazo; i++) {
    nodePos[i] = calloc(2, sizeof(double));
    nodePos[i][0] = posX;
    nodePos[i][1] = posY;
    cairo_move_to(cr, posX, posY);
    cairo_arc (cr, posX, posY, radius, 0, 2 * G_PI);
    posX += radius * 2.5;
  }


  gtk_style_context_get_color (context, gtk_style_context_get_state (context), &color);
  gdk_cairo_set_source_rgba (cr, &color);
  cairo_fill (cr);


  for (int i = plazo; i >= 0; i--) {
    for (int j = 1 ; j <= vidaUtil ; j++ ){
      cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
      if (i != 0){
        if (rutas[i][j] != 0){
          if (j > 1){
            cairo_set_source_rgb(cr, 0.1, 0.1, 0.99);
          }
          int currNode = rutas[i][j] ;
          double center = (nodePos[plazo-i][0] + nodePos[currNode][0]) /2;
          cairo_move_to(cr, nodePos[plazo-i][0], nodePos[plazo-i][1]);
          cairo_curve_to(cr,nodePos[plazo-i][0], nodePos[plazo-i][1],center, nodePos[0][1] - 240 + (j*10) + (i*10) ,nodePos[currNode][0], nodePos[currNode][1]);
          cairo_stroke(cr);
        }
      }
    }
  }

  int fontSize = radius;
  cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, fontSize);


  cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
  cairo_text_extents_t extents;

  for (int i = 0; i <= plazo; i++) {
    char bufferTittle[10];
    snprintf(bufferTittle, sizeof(bufferTittle), "%d", i);

    cairo_text_extents(cr, bufferTittle, &extents);
    cairo_move_to(cr, nodePos[i][0] - extents.width/2, nodePos[i][1] + extents.height/2);

    cairo_show_text(cr, bufferTittle);
  }

  cairo_set_line_width(cr, 2);


  cairo_stroke(cr);
}

void rutaOptima(GtkButton *button, app_widgets *appWdgets){
  for (int i = 0; i < plazo; i++) {
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(appWdgets->nodoLlegada), i, "0", names[i+1]);
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(appWdgets->nodoPartida), i, "0", names[i+1]);
  }

  gtk_widget_show(appWdgets->modalRutaOptima);

  gtk_stack_set_visible_child(GTK_STACK(appWdgets->contentPages), appWdgets->contentGrafo);
  currentShow = 0;
}

void editName(GtkButton *button, app_widgets *appWdgets){
  for (int i = 0; i < plazo; i++) {
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
  for (int i = 0; i < plazo; i++) {
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


    }
  }else{
    showMessage("El nombre no puede estar vacío.");
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


  gtk_widget_show_all(currentWindow);
}

void nextTable(){

}

void previousTable(){

}
