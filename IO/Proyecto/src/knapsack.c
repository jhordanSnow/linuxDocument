#include <string.h>
#include <math.h>
#include <gtk/gtk.h>
#include "common.c"

typedef struct {
  GtkWidget* selectType;
  GtkWidget* selectQuantity;
  GtkWidget* dataGrid;
  GtkWidget* addEntry;
  GtkWidget* labelQuantity;
  GtkWidget* containerData;
  GtkWidget* name;
  GtkWidget* cost;
  GtkWidget* value;
  GtkWidget* quantity;
  GtkWidget* contentPages;
  GtkWidget* inputSection;
  GtkWidget* resultSection;
  GtkWidget* tableResult;
  GtkWidget* knapSize;
  GtkWidget* labelResult;
  GtkWidget* labelSolution;
  GtkAdjustment* adjustment;
} app_widgets;

typedef struct {
    char* name;
    double costo;
    double valor;
    double cant;
} knapItem;

PangoAttrList* labelColor;
PangoAttrList* labelColor2;

int currentRow;
GtkWidget *currentWindow;
int currentPage;

knapItem* knap;

double **matriz;
double *solution;

void setVisibility(app_widgets* appWdgets, int visible);
int checkEntries(app_widgets* appWdgets);
void showMessage(char* message);
void setWidgetMargin(GtkWidget* widget);
void deleteRow(GtkWidget* button, app_widgets* appWdgets);
void executeKnapsack(app_widgets* appWdgets);
const char* getText(app_widgets* appWdgets, int row, int col);
double getTextBox(app_widgets* appWdgets, int row, int col);
GtkAdjustment* newAdjustment(double value, app_widgets* appWdgets);
void setSelectType(app_widgets* appWdgets, char* selected);

int main(int argc, char *argv[]){
  currentRow = 0;
  currentPage = 0;

  labelColor = pango_attr_list_new();
  pango_attr_list_insert(labelColor, pango_attr_foreground_new(65535,0,0));

  labelColor2 = pango_attr_list_new();
  pango_attr_list_insert(labelColor2, pango_attr_foreground_new(0,65535,0));

  gtk_init(&argc, &argv);
  createBuilder("Knapsack");

  app_widgets *widgets = g_slice_new(app_widgets);
  widgets->selectType = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "selectType"));
  widgets->selectQuantity = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "quantity"));
  widgets->dataGrid = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "dataGrid"));
  widgets->addEntry = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "addEntry"));
  widgets->labelQuantity = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "labelQuantity"));
  widgets->containerData = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "containerData"));
  widgets->name = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "name"));
  widgets->cost = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "cost"));
  widgets->value = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "value"));
  widgets->quantity = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "quantity"));
  widgets->contentPages = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "contentPages"));
  widgets->inputSection = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "inputSection"));
  widgets->resultSection = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "resultSection"));
  widgets->knapSize = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "knapSize"));
  widgets->tableResult = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "tableResult"));
  widgets->labelResult = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "labelResult"));
  widgets->labelSolution = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "labelSolution"));
  widgets->adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(gtkBuilder, "adjustment"));

  gtk_builder_connect_signals(gtkBuilder, widgets);

  currentWindow = showWindow(gtkBuilder, "main");
  gtk_main();

  return 0;
}

char* getSelectedText(GtkWidget* widget){
  return gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));
}

void changeType(GtkWidget* changeButton, app_widgets *appWdgets){
  char* selected = getSelectedText(changeButton);
  if (strcmp(selected, "Bounded") == 0){
    setVisibility(appWdgets, TRUE);
    //showQuantity(appWdgets);
  }else{
    setVisibility(appWdgets, FALSE);
    //hideQuantity(appWdgets);
  }
}

void addEntry(GtkWidget* button, app_widgets* appWdgets){
  if (checkEntries(appWdgets)){
    currentRow++;
    GtkGrid* grid = GTK_GRID(appWdgets->containerData);

    gtk_grid_insert_row(grid, currentRow);
    if (currentRow == 1){
      gtk_grid_insert_column(grid, 1);
      gtk_grid_insert_column(grid, 2);
      gtk_grid_insert_column(grid, 3);
      gtk_grid_insert_column(grid, 4);
      //gtk_grid_insert_column(grid, 5);
    }

    GtkEntry* name = GTK_ENTRY(appWdgets->name);
    GtkSpinButton* cost = GTK_SPIN_BUTTON(appWdgets->cost);
    GtkSpinButton* value = GTK_SPIN_BUTTON(appWdgets->value);
    GtkSpinButton* quantity = GTK_SPIN_BUTTON(appWdgets->quantity);

    GtkWidget* nameGrid = gtk_entry_new_with_buffer(gtk_entry_buffer_new(gtk_entry_get_text(name), -1));
    GtkWidget* costGrid = gtk_spin_button_new(newAdjustment(gtk_spin_button_get_value(cost), appWdgets), 5, 2);
    GtkWidget* valueGrid = gtk_spin_button_new(newAdjustment(gtk_spin_button_get_value(value), appWdgets), 5, 2);
    GtkWidget* quantityGrid = gtk_spin_button_new(newAdjustment(gtk_spin_button_get_value(quantity), appWdgets), 5, 0);
    GtkWidget* btnDelete = gtk_button_new_with_label("Eliminar");

    char btnName[50];
    sprintf(btnName, "%d", currentRow);
    gtk_widget_set_name(btnDelete, btnName);

    gtk_grid_attach(grid, nameGrid, 1, currentRow, 1, 1);
    gtk_grid_attach(grid, costGrid, 2, currentRow, 1, 1);
    gtk_grid_attach(grid, valueGrid, 3, currentRow, 1, 1);
    gtk_grid_attach(grid, quantityGrid, 4, currentRow, 1, 1);
    //gtk_grid_attach(grid, btnDelete, 5, currentRow, 1, 1);

    setWidgetMargin(nameGrid);
    setWidgetMargin(costGrid);
    setWidgetMargin(valueGrid);
    setWidgetMargin(quantityGrid);
    setWidgetMargin(btnDelete);

    gtk_entry_set_text(name, "");
    gtk_spin_button_set_value(cost, 0);
    gtk_spin_button_set_value(value, 0);
    gtk_spin_button_set_value(quantity, 0);


    g_signal_connect(G_OBJECT(btnDelete), "clicked", G_CALLBACK(deleteRow), appWdgets);
    gtk_widget_show_all(currentWindow);
    changeType(appWdgets->selectType, appWdgets);
  }
}

void deleteRow(GtkWidget* button, app_widgets* appWdgets){
  printf("caca");
  printf("%s", gtk_widget_get_name(GTK_WIDGET(button)));
}

void setVisibility(app_widgets* appWdgets, int visible){
  gtk_widget_set_visible(appWdgets->selectQuantity, visible);
  gtk_widget_set_visible(appWdgets->labelQuantity, visible);

  for (int i = 1; i <= currentRow; i++) {
    GtkWidget* quantityLocal = gtk_grid_get_child_at(GTK_GRID(appWdgets->containerData), 4, i);

    gtk_widget_set_visible(quantityLocal, visible);
  }
}

void setWidgetMargin(GtkWidget* widget){
    gtk_widget_set_margin_start(widget, 10);
    gtk_widget_set_margin_end(widget, 10);
    gtk_widget_set_margin_top(widget, 10);
    gtk_widget_set_margin_bottom(widget, 10);
}

int checkEntries(app_widgets* appWdgets){
  const char* name =  gtk_entry_get_text(GTK_ENTRY(appWdgets->name));
  if (strcmp(name, "") == 0){
    showMessage("El nombre no puede ser vacío");
    return 0;
  }
  return 1;
}

void showMessage(char* message){
  GtkWidget *messageDialog = gtk_message_dialog_new(GTK_WINDOW(currentWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, message);

  gtk_dialog_run (GTK_DIALOG (messageDialog));
  gtk_widget_destroy (messageDialog);
}


GtkAdjustment* newAdjustment(double value, app_widgets* appWdgets){
  return gtk_adjustment_new(value,
                            gtk_adjustment_get_lower(appWdgets->adjustment),
                            gtk_adjustment_get_upper(appWdgets->adjustment),
                            gtk_adjustment_get_step_increment(appWdgets->adjustment),
                            gtk_adjustment_get_page_increment(appWdgets->adjustment),
                            gtk_adjustment_get_page_size(appWdgets->adjustment)
                          );
}


void changeView(GtkWidget* button, app_widgets* appWdgets){
  if (currentPage == 0){
    currentPage = 1;
    executeKnapsack(appWdgets);
    gtk_stack_set_visible_child(GTK_STACK(appWdgets->contentPages), appWdgets->resultSection);
  }else{
    currentPage = 0;
    gtk_stack_set_visible_child(GTK_STACK(appWdgets->contentPages), appWdgets->inputSection);
  }
}

void fillKnap(app_widgets* appWdgets){
  char* selected = getSelectedText(appWdgets->selectType);
  knap = malloc((currentRow + 1) * sizeof(knapItem));
  for (int i = 1; i <= currentRow; i++) {

    knap[i-1].name = malloc(100*sizeof(char*));
    sprintf(knap[i-1].name, "%s", getText(appWdgets, i, 1));

    knap[i-1].costo = getTextBox(appWdgets, i, 2);
    knap[i-1].valor = getTextBox(appWdgets, i, 3);

    if (strcmp(selected, "1/0") == 0){
      knap[i-1].cant = 1;
    }else if (strcmp(selected, "Unbounded") == 0){
      knap[i-1].cant = INFINITY;
    }else{
      knap[i-1].cant = (int) getTextBox(appWdgets, i, 4);
    }
  }
}

void attachToGrid(int i, int j, app_widgets* appWdgets, int color){
  GtkGrid* grid = GTK_GRID(appWdgets->tableResult);

  char tmpText[100];
  sprintf(tmpText, "%2.f", matriz[i][j]);
  GtkWidget* lblTmp = gtk_label_new(tmpText);

  gtk_grid_attach(grid, lblTmp, i+1, j+1, 1, 1);

  if (color == 0){
    gtk_label_set_attributes(GTK_LABEL(lblTmp), labelColor);
  }else{
    gtk_label_set_attributes(GTK_LABEL(lblTmp), labelColor2);
  }
  setWidgetMargin(lblTmp);
}

void fillMatriz(app_widgets* appWdgets){
  int knapSize = gtk_spin_button_get_value(GTK_SPIN_BUTTON(appWdgets->knapSize));
  int celda, color;

  double *matrizAux = calloc((currentRow + 1) * (knapSize + 1), sizeof (double));
  matriz = malloc((currentRow + 1) * sizeof (double *));
  matriz[0] = matrizAux;
  for (int i = 1; i <= currentRow; i++) {
      matriz[i] = &matrizAux[i * (knapSize + 1)];
      for (int j = 0; j <= knapSize; j++) {
        color = 0;
          matriz[i][j] = matriz[i - 1][j];
          for (int k = 1; k <= knap[i - 1].cant; k++) {
              if (k * knap[i - 1].costo > j) {
                  break;
              }
              celda = matriz[i - 1][j - k * ((int) knap[i - 1].costo)] + k * knap[i - 1].valor;
              if (celda > matriz[i][j]) {
                  color = 1;
                  matriz[i][j] = celda;
              }
          }
          attachToGrid(i, j, appWdgets, color);
      }
    }
}

void showMatriz(app_widgets* appWdgets){
  int knapSize = gtk_spin_button_get_value(GTK_SPIN_BUTTON(appWdgets->knapSize));
  GtkGrid* grid = GTK_GRID(appWdgets->tableResult);
  gtk_grid_insert_row(grid, currentRow);
  gtk_grid_insert_column(grid, 1);
  for (int j = 1; j <= currentRow; j++) {
    gtk_grid_insert_column(grid, j+1);
    gtk_grid_attach(grid, gtk_label_new(knap[j-1].name), j+1, 0, 1, 1);
  }

  for (int i = 0; i <= knapSize; i++) {
    gtk_grid_insert_row(grid, i+1);

    char tmpText[100];
    sprintf(tmpText, "%d", i);

    gtk_grid_attach(grid, gtk_label_new(tmpText), 1, i+1, 1, 1);
  }
}

void showLabelMate(app_widgets* appWdgets){
  char markup[1024] = "<span font_desc=\"Serif Italic 15\">Z =";
  for (int i = 1; i <= currentRow; i++) {
    char buffer[512];
    if (i > 1){
      snprintf(buffer, sizeof(buffer), " + %0.fX<sub>%s</sub>", knap[i-1].valor, knap[i-1].name);
    }else{
      snprintf(buffer, sizeof(buffer), "%0.fX<sub>%s</sub>", knap[i-1].valor, knap[i-1].name);
    }
    strcat(markup, buffer);
  }

  strcat(markup, "\n \n Sujeto a \n \n");

  for (int i = 1; i <= currentRow; i++) {
    char buffer[512];
    if (i == currentRow){
      snprintf(buffer, sizeof(buffer), "%0.fX<sub>%s</sub> ≤ %0.f", knap[i-1].costo, knap[i-1].name, gtk_spin_button_get_value(GTK_SPIN_BUTTON(appWdgets->knapSize)));
    }else{
      snprintf(buffer, sizeof(buffer), "%0.fX<sub>%s</sub> + ", knap[i-1].costo, knap[i-1].name);
    }
    strcat(markup, buffer);
  }

  strcat(markup, "\n \n");

  for (int i = 1; i <= currentRow; i++) {
    char buffer[512];
    snprintf(buffer, sizeof(buffer), "X<sub>%s</sub> ≤ %0.f \n", knap[i-1].name, knap[i-1].cant);
    strcat(markup, buffer);
  }

  strcat(markup, "</span>");
  gtk_label_set_markup(GTK_LABEL(appWdgets->labelResult), markup);
}

void fillSolution(app_widgets* appWdgets){
  int knapSize = gtk_spin_button_get_value(GTK_SPIN_BUTTON(appWdgets->knapSize));
  solution = calloc(currentRow, sizeof (double));
  for (int i = currentRow, j = knapSize; i > 0; i--) {
        int v = matriz[i][j];
        for (int k = 0; v != matriz[i - 1][j] + k * knap[i - 1].valor; k++) {
            solution[i - 1]++;
            j -= knap[i - 1].costo;
        }
    }
}

void showSolution(app_widgets* appWdgets){
  double total = 0;
  for (int i = 0; i < currentRow; i++) {
    total += solution[i] * knap[i].valor;
  }

  char markup[1024] = "\n<span font_desc=\"Serif Italic 15\">Solución: \n";
  for (int i = 1; i <= currentRow; i++) {
    char buffer[512];
    if (i > 1){
      snprintf(buffer, sizeof(buffer), " + %0.f*%0.f", knap[i-1].valor, solution[i-1]);
    }else{
      snprintf(buffer, sizeof(buffer), "%0.f = %0.f*%0.f", total,knap[i-1].valor, solution[i-1]);
    }
    strcat(markup, buffer);
  }

  strcat(markup, "\n Esto implica llevar: \n");
  if (total > 0){
    for (int i = 1; i <= currentRow; i++) {
      if (solution[i-1]){
        char buffer[512];
        snprintf(buffer, sizeof(buffer), "%0.f %s \n", solution[i-1], knap[i-1].name);
        strcat(markup, buffer);
      }
    }
  }else{
    strcat(markup, "Ningún objeto.");
  }


/*
char markuptmp[1024] = "<span font_desc=\"Serif Italic 15\">";
for (int i = 0; i < currentRow; i++) {
    if (solution[i]) {
      printf("%-22s %5f %5f %5f\n", knap[i].name, solution[i], solution[i] * knap[i].costo, solution[i] * knap[i].valor);
    }else{
      printf("%-22s %5f %5f %5f\n", knap[i].name, 0, 0 * knap[i].costo, solution[i] * knap[i].valor);
    }
}
  char buffer[512];
  snprintf(buffer, sizeof(buffer), " + %0.f*%0.f", knap[i-1].valor, solution[i]);
*/
  strcat(markup, "</span>");
  gtk_label_set_markup(GTK_LABEL(appWdgets->labelSolution), markup);


}

void executeKnapsack(app_widgets* appWdgets){
  for (int i = gtk_spin_button_get_value(GTK_SPIN_BUTTON(appWdgets->knapSize)) + 1; i >= 0; i--) {
    gtk_grid_remove_row(GTK_GRID(appWdgets->tableResult), i);
  }
  fillKnap(appWdgets);
  showMatriz(appWdgets);
  fillMatriz(appWdgets);
  showLabelMate(appWdgets);
  fillSolution(appWdgets);
  showSolution(appWdgets);

  gtk_widget_show_all(appWdgets->resultSection);
}

const char* getText(app_widgets* appWdgets, int row, int col){
  return gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(appWdgets->containerData), col, row)));
}

double getTextBox(app_widgets* appWdgets, int row, int col){
  return gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(appWdgets->containerData), col, row)));
}

void downloadFile(GtkButton* button, app_widgets *appWdgets){
  fillKnap(appWdgets);
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
        if (fprintf(f, "%s", getSelectedText(appWdgets->selectType)) <= 0){
          success = 0;
        }
        fprintf(f, " ");
      }

      if (success == 1){
        if (fprintf(f, "%f", gtk_spin_button_get_value(GTK_SPIN_BUTTON(appWdgets->knapSize))) <= 0){
          success = 0;
        }
        fprintf(f, " ");
      }

      fprintf(f, " ; ");

      for (int i = 1; i <= currentRow; i++) {
        if (success == 1){
          if (fprintf(f, "%s", knap[i-1].name) <= 0){
            success = 0;
          }
          fprintf(f, " ");
        }

        if (success == 1){
          if (fprintf(f, "%f", knap[i-1].costo) <= 0){
            success = 0;
          }
          fprintf(f, " ");
        }

        if (success == 1){
          if (fprintf(f, "%f", knap[i-1].valor) <= 0){
            success = 0;
          }
          fprintf(f, " ");
        }

        if (success == 1){
          if (fprintf(f, "%f", knap[i-1].cant) <= 0){
            success = 0;
          }
          fprintf(f, " ");
        }


        fprintf(f, " ; ");
      }

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

void uploadFile(GtkButton* button, app_widgets *appWdgets){
  for (int i = currentRow; i > 0; i--) {
    gtk_grid_remove_row(GTK_GRID(appWdgets->containerData), i);
  }

  currentRow = 0;

  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;
  GtkWidget *dialog = gtk_file_chooser_dialog_new ("Subir archivo",GTK_WINDOW(currentWindow),action,"Cancelar",GTK_RESPONSE_CANCEL,"Subir",GTK_RESPONSE_ACCEPT,NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT){
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);

    int success = 1;

    FILE *f = fopen(filename, "r");
    if (f == NULL){
      showMessage("Error al abrir el archivo");
    }else{
      knap = malloc(currentRow * sizeof(knapItem));
      char fileContent[100];

      if (fscanf(f, "%s", fileContent) > 0){
        setSelectType(appWdgets, fileContent);
      }else{
        success = 0;
      }

      if (success == 1){
        if (fscanf(f, "%s", fileContent) > 0){
          gtk_spin_button_set_value(GTK_SPIN_BUTTON(appWdgets->knapSize), atof(fileContent));
        }else{
          success = 0;
        }
      }

      int col = 0;
      while(fscanf(f, "%s", fileContent) > 0){
        if (strcmp(fileContent, ";") == 0){
          if (fscanf(f, "%s", fileContent) > 0 && strcmp(fileContent, "") != 0){
            col = 0;
            gtk_entry_set_text(GTK_ENTRY(appWdgets->name), fileContent);
            if (success == 1){
              if (fscanf(f, "%s", fileContent) > 0){
                gtk_spin_button_set_value(GTK_SPIN_BUTTON(appWdgets->cost), atof(fileContent));
              }else{
                success = 0;
              }
            }

            if (success == 1){
              if (fscanf(f, "%s", fileContent) > 0){
                gtk_spin_button_set_value(GTK_SPIN_BUTTON(appWdgets->value), atof(fileContent));
              }else{
                success = 0;
              }
            }

            if (success == 1){
              if (fscanf(f, "%s", fileContent) > 0){
                gtk_spin_button_set_value(GTK_SPIN_BUTTON(appWdgets->quantity), atof(fileContent));
              }else{
                success = 0;
              }
            }

            addEntry(appWdgets->addEntry, appWdgets);
          }
        }
        col++;
      }

      showMessage("Archivo cargado correctamente");
      fclose(f);
    }
  }

  gtk_widget_destroy (dialog);
}


void setSelectType(app_widgets* appWdgets, char* selected){
  if (strcmp(selected, "1/0") == 0){
    gtk_combo_box_set_active(GTK_COMBO_BOX(appWdgets->selectType), 0);
  }else if (strcmp(selected, "Bounded") == 0){
    gtk_combo_box_set_active(GTK_COMBO_BOX(appWdgets->selectType), 1);
  }else{
    gtk_combo_box_set_active(GTK_COMBO_BOX(appWdgets->selectType), 2);
  }
}
