#include <limits.h>
#include <gtk/gtk.h>
#include "common.c"

typedef struct {
  GtkWidget* CantKeys;
  GtkWidget* DisplayDataGrid;
} AppWidgets;

GtkWidget *CurrentWindow;

// Algoritmo
int CantKeys;
char** Codes;
double* Weigths;

void LoadVariables(GtkGrid* Grid);
void ShowResult();
double optimalSearchTree(double freq[], int n);

// Driver program to test above functions
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    createBuilder("BST");

    AppWidgets *Widgets = g_slice_new(AppWidgets);
    Widgets->CantKeys  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "CantKeys"));
    Widgets->DisplayDataGrid  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "DisplayDataGrid"));

    gtk_builder_connect_signals(gtkBuilder, Widgets);

    CurrentWindow = showWindow(gtkBuilder, "main");
    gtk_main();

    return 0;
}

void ManualEntryClick(GtkWidget* Button, AppWidgets* Widgets){
  CantKeys = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(Widgets->CantKeys));
  GtkGrid* grid = GTK_GRID(Widgets->DisplayDataGrid);
  gtk_grid_set_row_spacing(grid, 15);
  gtk_grid_set_column_spacing(grid, 15);

  Weigths = calloc(CantKeys, sizeof(double));
  Codes = calloc(CantKeys, sizeof(char*));

  for (int i = 0; i < CantKeys; i++) {
    GtkWidget *Number;
    GtkWidget *Code;
    GtkWidget *Weigth;
    GtkAdjustment *WeigthAdjust;

    gtk_grid_insert_row(grid, i + 1);

    char buffer[20];
    sprintf(buffer, "%d", i + 1);
    Number = gtk_label_new(buffer);

    Code = gtk_entry_new();

    WeigthAdjust = gtk_adjustment_new(0, 0, DBL_MAX, 1, 10, 0);
    Weigth = gtk_spin_button_new(WeigthAdjust, 1, 2);

    gtk_grid_attach(grid, GTK_WIDGET(Number), 0, i + 1, 1, 1);
    gtk_grid_attach(grid, GTK_WIDGET(Code), 1, i + 1, 1, 1);
    gtk_grid_attach(grid, GTK_WIDGET(Weigth), 2, i + 1, 1, 1);
  }

  gtk_widget_destroy(CurrentWindow);
  CurrentWindow = showWindow(gtkBuilder, "Data");
}

void AceptAlgorithm(GtkWidget* Button, AppWidgets* Widgets){
  LoadVariables(GTK_GRID(Widgets->DisplayDataGrid));
  //ExecuteAlgorithm();
  printf("Cost of Optimal BST is %f ", optimalSearchTree(Weigths, CantKeys));
  ShowResult();
}

void LoadVariables(GtkGrid* Grid){
  for (int i = 0; i < CantKeys; i++) {
    char Buffer[20];
    sprintf(Buffer, "%s", gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(Grid, 1, i + 1))));
    Codes[i] = Buffer;
    Weigths[i] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(Grid, 2, i + 1)));
  }
}

void ShowResult(){
  gtk_widget_destroy(CurrentWindow);

  CurrentWindow = showWindow(gtkBuilder, "Result");
}

// A utility function to get sum of array elements
// freq[i] to freq[j]
double sum(double freq[], int i, int j);

/* A Dynamic Programming based function that calculates
  minimum cost of a Binary Search Tree. */
double optimalSearchTree(double freq[], int n)
{
    /* Create an auxiliary 2D matrix to store results
      of subproblems */
    double cost[n][n];

    /* cost[i][j] = Optimal cost of binary search tree
       that can be  formed from keys[i] to keys[j].
       cost[0][n-1] will store the resultant cost */

    // For a single key, cost is equal to frequency of the key
    for (int i = 0; i < n; i++)
        cost[i][i] = freq[i];

    // Now we need to consider chains of length 2, 3, ... .
    // L is chain length.
    for (int L=2; L<=n; L++)
    {
        // i is row number in cost[][]
        for (int i=0; i<=n-L+1; i++)
        {
            // Get column number j from row number i and
            // chain length L
            int j = i+L-1;
            cost[i][j] = INT_MAX;

            // Try making all keys in interval keys[i..j] as root
            for (int r=i; r<=j; r++)
            {
               // c = cost when keys[r] becomes root of this subtree
               int c = ((r > i)? cost[i][r-1]:0) +
                       ((r < j)? cost[r+1][j]:0) +
                       sum(freq, i, j);
               if (c < cost[i][j])
                  cost[i][j] = c;
            }
        }
    }
    return cost[0][n-1];
}

// A utility function to get sum of array elements
// freq[i] to freq[j]
double sum(double freq[], int i, int j)
{
    double s = 0;
    for (int k = i; k <=j; k++)
       s += freq[k];
    return s;
}
