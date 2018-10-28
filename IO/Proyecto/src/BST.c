#include <limits.h>
#include <gtk/gtk.h>
#include "common.c"

typedef struct {
  GtkWidget* CantKeys;
  GtkWidget* DisplayDataGrid;
  GtkWidget* UploadFilePicker;
  GtkWidget* GridProba;
  GtkWidget* GridRoot;
  GtkWidget* LblAverageResult;
} AppWidgets;

GtkWidget *CurrentWindow;

// Algoritmo
int CantKeys;
char** Keys;
double WeigthsSum;
double* Weigths;
double* Probabilities;

double** TreeTable;
int** RTable;

void LoadVariables(GtkGrid* Grid);
void LoadDataEntries(GtkGrid* Grid);
void ShowDataEntries(GtkGrid* Grid);
void ShowResultTree(GtkGrid* Grid);
void ShowResultRoots(GtkGrid* Grid);
void ShowResultLabel(GtkLabel* Label);
double optimalSearchTree(double freq[], int n);

void ExecuteAlgorithm();
void CalculateProbabilities();
void SortData();
void FillAlgorithmTables();

// Driver program to test above functions
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    createBuilder("BST");

    AppWidgets *Widgets = g_slice_new(AppWidgets);
    Widgets->CantKeys  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "CantKeys"));
    Widgets->DisplayDataGrid  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "DisplayDataGrid"));
    Widgets->UploadFilePicker  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "UploadFilePicker"));
    Widgets->GridProba  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "GridProba"));
    Widgets->GridRoot  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "GridRoot"));
    Widgets->LblAverageResult  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "LblAverageResult"));

    gtk_builder_connect_signals(gtkBuilder, Widgets);

    CurrentWindow = showWindow(gtkBuilder, "main");
    gtk_main();

    return 0;
}

void ManualEntryClick(GtkWidget* Button, AppWidgets* Widgets){
  CantKeys = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(Widgets->CantKeys));
  ShowDataEntries(GTK_GRID(Widgets->DisplayDataGrid));

  gtk_widget_destroy(CurrentWindow);
  CurrentWindow = showWindow(gtkBuilder, "Data");
}

void AceptAlgorithm(GtkWidget* Button, AppWidgets* Widgets){
  LoadVariables(GTK_GRID(Widgets->DisplayDataGrid));
  ExecuteAlgorithm();
  ShowResultTree(GTK_GRID(Widgets->GridProba));
  ShowResultRoots(GTK_GRID(Widgets->GridRoot));
  ShowResultLabel(GTK_LABEL(Widgets->LblAverageResult));

  gtk_widget_destroy(CurrentWindow);
  CurrentWindow = showWindow(gtkBuilder, "Result");
}

void ExecuteAlgorithm(){
  SortData();
  CalculateProbabilities();
  FillAlgorithmTables();
}

void SortData(){
  printf("-------------------------no Sorted ---------------------- \n");
  for (int i = 0; i < CantKeys; i++) {
    printf("%s: %f\n", Keys[i], Weigths[i]);
  }

  for (int i = 0; i < CantKeys; i++) {
    for (int j = 0; j < CantKeys - 1; j++) {
      if (strcmp(Keys[j + 1], Keys[j]) < 0){

        double WeigthTmp = Weigths[j + 1];
        char* KeyTmp = Keys[j + 1];

        Keys[j + 1] = Keys[j];
        Weigths[j + 1] = Weigths[j];

        Keys[j] = KeyTmp;
        Weigths[j] = WeigthTmp;
      }
    }
  }

  printf("------------------------- Sorted ---------------------- \n");
  for (int i = 0; i < CantKeys; i++) {
    printf("%s: %f\n", Keys[i], Weigths[i]);
  }

}

void CalculateProbabilities(){
  Probabilities = calloc(CantKeys, sizeof(double));
  for (int i = 0; i < CantKeys; i++) {
    Probabilities[i] = Weigths[i] / WeigthsSum;
  }
}

void FillAlgorithmTables(){
  TreeTable = calloc(CantKeys, sizeof(double*));
  RTable = calloc(CantKeys, sizeof(int*));

  for (int i = 0; i < CantKeys ; i++) {
    TreeTable[i] = calloc(CantKeys, sizeof(double));
    RTable[i] = calloc(CantKeys, sizeof(int));
  }

  for (int j = 0; j < CantKeys ; j++) {
    for (int i = CantKeys - 1; i >= 0 ; i--) {
      if (i > j){
        TreeTable[i][j] = 0;
        RTable[i][j] = -1;
      }else if(j == i){
        TreeTable[i][j] = Probabilities[i];
        RTable[i][j] = i;
      }else{
        double WeigthConst = 0;
        double minWeight = DBL_MAX;
        int minK = 0;

        //printf("-------------------------------------------------------------\n");
        for (int k = i; k <= j; k++) {
          WeigthConst += Weigths[k];
          double newProba = 0;
          if (k - 1 >= 0){
            newProba += TreeTable[i][k-1];
          }
          if (k + 1 < CantKeys){
            newProba += TreeTable[k+1][j];
          }

          //printf("%f < %f = %d\n", newProba, minWeight, newProba < minWeight);
          if(newProba < minWeight){
            minWeight = newProba;
            minK = k;
          }

          //printf("-> %d\t-\t%d\n", k, minK);
        }

        TreeTable[i][j] = minWeight + WeigthConst;
        RTable[i][j] = minK;
      }
    }
  }


  printf("-------------------- Tree -------------------------\n");
  for (int i = 0; i < CantKeys; i++) {
    for (int j = 0; j < CantKeys; j++) {
      printf("%f ", TreeTable[i][j]);
    }
    printf("\n");
  }

  printf("-------------------- Proba -------------------------\n");
  for (int i = 0; i < CantKeys; i++) {
    for (int j = 0; j < CantKeys; j++) {
      printf("%d ", RTable[i][j] + 1);
    }
    printf("\n");
  }

}

void ShowDataEntries(GtkGrid* Grid){
  gtk_grid_set_row_spacing(Grid, 15);
  gtk_grid_set_column_spacing(Grid, 15);

  Weigths = calloc(CantKeys, sizeof(double));
  Keys = calloc(CantKeys, sizeof(char*));

  for (int i = 0; i < CantKeys; i++) {
    GtkWidget *Number;
    GtkWidget *Key;
    GtkWidget *Weigth;
    GtkAdjustment *WeigthAdjust;

    gtk_grid_insert_row(Grid, i + 1);

    char buffer[20];
    sprintf(buffer, "%d", i + 1);
    Number = gtk_label_new(buffer);

    Key = gtk_entry_new();

    WeigthAdjust = gtk_adjustment_new(0, 0, DBL_MAX, 1, 10, 0);
    Weigth = gtk_spin_button_new(WeigthAdjust, 1, 2);

    gtk_grid_attach(Grid, GTK_WIDGET(Number), 0, i + 1, 1, 1);
    gtk_grid_attach(Grid, GTK_WIDGET(Key), 1, i + 1, 1, 1);
    gtk_grid_attach(Grid, GTK_WIDGET(Weigth), 2, i + 1, 1, 1);
  }
}

void LoadVariables(GtkGrid* Grid){
  WeigthsSum = 0;
  for (int i = 0; i < CantKeys; i++) {
    char* Buffer = calloc(20, sizeof(char));
    sprintf(Buffer, "%s", gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(Grid, 1, i + 1))));
    Keys[i] = Buffer;
    Weigths[i] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(Grid, 2, i + 1)));
    WeigthsSum += Weigths[i];
  }
}

void LoadDataEntries(GtkGrid* Grid){
  for (int i = 0; i < CantKeys; i++) {
    gtk_entry_set_text(GTK_ENTRY(gtk_grid_get_child_at(Grid, 1, i + 1)), Keys[i]);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(Grid, 2, i + 1)), Weigths[i]);
  }
}

void ShowResultTree(GtkGrid* Grid){
  gtk_grid_set_row_spacing(Grid, 15);
  gtk_grid_set_column_spacing(Grid, 15);

  gtk_grid_insert_row(Grid, 0);
  gtk_grid_insert_column(Grid, 0);
  for (int i = 0; i < CantKeys; i++) {
    gtk_grid_insert_row(Grid, i + 1);

    for (int j = 0; j < CantKeys; j++) {
      if (i == 0){
        gtk_grid_insert_column(Grid, j + 1);
        gtk_grid_attach(Grid, gtk_label_new(Keys[j]), j + 1, i, 1, 1);
      }

      if (j == 0){
        gtk_grid_attach(Grid, gtk_label_new(Keys[i]), j, i + 1, 1, 1);
      }

      char buffer[20];
      sprintf(buffer, "%.4f", TreeTable[i][j]);

      GtkWidget* Label = gtk_label_new(buffer);
      gtk_grid_attach(Grid, Label, j + 1, i + 1, 1, 1);
    }
  }
}

void ShowResultRoots(GtkGrid* Grid){
  gtk_grid_set_row_spacing(Grid, 15);
  gtk_grid_set_column_spacing(Grid, 15);

  gtk_grid_insert_row(Grid, 0);
  gtk_grid_insert_column(Grid, 0);
  for (int i = 0; i < CantKeys; i++) {
    gtk_grid_insert_row(Grid, i + 1);

    for (int j = 0; j < CantKeys; j++) {
      if (i == 0){
        gtk_grid_insert_column(Grid, j + 1);
        gtk_grid_attach(Grid, gtk_label_new(Keys[j]), j + 1, i, 1, 1);
      }

      if (j == 0){
        gtk_grid_attach(Grid, gtk_label_new(Keys[i]), j, i + 1, 1, 1);
      }

      char buffer[20];
      sprintf(buffer, "%d", RTable[i][j] + 1);

      GtkWidget* Label = gtk_label_new(buffer);
      gtk_grid_attach(Grid, Label, j + 1, i + 1, 1, 1);
    }
  }
}

void ShowResultLabel(GtkLabel* Label){
  char buffer[420];
  sprintf(buffer, "<span font_desc=\"Serif Italic 15\">Costo promedio: %.4f</span>", TreeTable[0][CantKeys - 1]);
  gtk_label_set_markup(Label, buffer);
}


void DrawNodes(double PosX, double PosY, double Radius, int RowStart, int RowEnd, cairo_t *cr, double offset){
  cairo_move_to(cr, PosX, PosY);
  cairo_arc(cr, PosX, PosY, Radius, 0, 2 * G_PI);

  int root = RTable[RowStart][RowEnd];
  double newPosY = PosY + (3*Radius);
  int CantChild = 2;
  CantChild -= (RowStart > root-1) ? 1 : 0;
  CantChild -= (RowEnd < root+1) ? 1 : 0;


  if (RowStart <= root - 1){
    double newPosX = (CantChild == 1) ? PosX : PosX - offset/2;
    DrawNodes(newPosX, newPosY, Radius, RowStart, root - 1, cr, offset/2);
  }

  if (RowEnd >= root + 1){
    double newPosX = (CantChild == 1) ? PosX : PosX + offset/2;
    DrawNodes(newPosX, newPosY, Radius, root + 1, RowEnd, cr, offset/2);
  }
}

void DrawNames(double PosX, double PosY, double Radius, int RowStart, int RowEnd, cairo_t *cr, double offset){
  int root = RTable[RowStart][RowEnd];
  double newPosY = PosY + (3*Radius);
  int CantChild = 2;
  CantChild -= (RowStart > root-1) ? 1 : 0;
  CantChild -= (RowEnd < root+1) ? 1 : 0;


  cairo_text_extents_t extents;

  char bufferTittle[100];
  snprintf(bufferTittle, sizeof(bufferTittle), "%.2f", Weigths[root]);

  cairo_text_extents(cr, Keys[root], &extents);
  cairo_move_to(cr,  PosX - extents.width/2, PosY);
  cairo_show_text(cr, Keys[root]);


  cairo_text_extents(cr, bufferTittle, &extents);
  cairo_move_to(cr,  PosX - extents.width/2, PosY + extents.height*1.1);
  cairo_show_text(cr, bufferTittle);


  if (RowStart <= root - 1){
    double newPosX = (CantChild == 1) ? PosX : PosX - offset/2;
    DrawNames(newPosX, newPosY, Radius, RowStart, root - 1, cr, offset/2);
  }

  if (RowEnd >= root + 1){
    double newPosX = (CantChild == 1) ? PosX : PosX + offset/2;
    DrawNames(newPosX, newPosY, Radius, root + 1, RowEnd, cr, offset/2);
  }
}

void RenderTree(GtkWidget *widget, cairo_t *cr, AppWidgets* Widgets){
  guint width, height;
  GdkRGBA color;
  GtkStyleContext *context;

  context = gtk_widget_get_style_context(widget);
  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);

  gtk_render_background (context, cr, 0, 0, width, height);

  double NodeRadius = height/( ((int) TreeTable[0][CantKeys - 1] + 1) * CantKeys * 0.8);

  cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, NodeRadius/2);

  DrawNodes(width/2, NodeRadius*2, NodeRadius, 0, CantKeys - 1, cr, width/2);
  gtk_style_context_get_color (context, gtk_style_context_get_state (context), &color);
  gdk_cairo_set_source_rgba (cr, &color);
  cairo_fill (cr);

  cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
  DrawNames(width/2, NodeRadius*2, NodeRadius, 0, CantKeys - 1, cr, width/2);

  cairo_stroke(cr);

}

void ExportFile(GtkWidget* Button, AppWidgets* Widgets){
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;
  GtkWidget *dialog = gtk_file_chooser_dialog_new ("Guardar Como",GTK_WINDOW(CurrentWindow),action,"Cancelar",GTK_RESPONSE_CANCEL,"Guardar",GTK_RESPONSE_ACCEPT,NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT){
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);

    int success = 1;

    FILE *f = fopen(filename, "w");
    if (f == NULL){
      showMessage("Error al abrir el archivo", CurrentWindow);
    }else{
      LoadVariables(GTK_GRID(Widgets->DisplayDataGrid));

      if (success == 1){
        if (fprintf(f, "%d", CantKeys) <= 0){
          success = 0;
        }
        fprintf(f, " ");
      }

      for (int i = 0; i < CantKeys; i++) {
        printf("2. %s\n", Keys[i]);
        if (success == 1){
          if (fprintf(f, "%s", Keys[i]) <= 0){
            success = 0;
          }
          fprintf(f, " ");
        }

        if (success == 1){
          if (fprintf(f, "%f", Weigths[i]) <= 0){
            success = 0;
          }
          fprintf(f, " ");
        }
      }

      fprintf(f, ";");

      if (success == 1){
        showMessage("Archivo exportado correctamente", CurrentWindow);
      }else{
        showMessage("Ocurrió un error al exportar el archivo", CurrentWindow);
      }

      fclose(f);
    }
  }
  gtk_widget_destroy (dialog);
}


void ImportFile(GtkWidget* Button, AppWidgets* Widgets){
  char *filename;
  GtkFileChooser *chooser = GTK_FILE_CHOOSER (Widgets->UploadFilePicker);
  filename = gtk_file_chooser_get_filename (chooser);

  int success = 1;

  FILE *f = fopen(filename, "r");
  if (f == NULL){
    showMessage("Error al abrir el archivo", CurrentWindow);
  }else{
    char fileContent[420];

    if (success == 1){
      if (fscanf(f, "%s", fileContent) > 0){
        CantKeys = atoi(fileContent);
        ShowDataEntries(GTK_GRID(Widgets->DisplayDataGrid));
      }else{
        success = 0;
      }
    }

    for (int i = 0; i < CantKeys; i++) {
      if (success == 1){
        if (fscanf(f, "%s", fileContent) > 0){
          char* Buffer = calloc(20, sizeof(char));
          sprintf(Buffer, "%s", fileContent);
          Keys[i] = Buffer;
        }else{
          success = 0;
        }
      }

      if (success == 1){
        if (fscanf(f, "%s", fileContent) > 0){
          Weigths[i] = atof(fileContent);
        }else{
          success = 0;
        }
      }
    }
  }

  fclose(f);

  if (success == 0){
    showMessage("Ocurrió un error al cargar el archivo.", CurrentWindow);
  }else{
    LoadDataEntries(GTK_GRID(Widgets->DisplayDataGrid));
    showMessage("Archivo cargado correctamente", CurrentWindow);
    gtk_widget_destroy(CurrentWindow);
    CurrentWindow = showWindow(gtkBuilder, "Data");
  }
}
