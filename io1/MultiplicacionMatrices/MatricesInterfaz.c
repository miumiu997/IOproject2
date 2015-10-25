#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logicaMatrices.h"


//variables globales
GtkBuilder *gtkBuilder;
GtkWidget *window;
GtkWidget *SRWindwMatrices; // division en la que se van actualizar las dimensiones de las matrices
GtkWidget *spinMatrices;
GtkWidget *txtMatrices;
GtkWidget ***dimensiones;
int nMatrices;
GtkWidget ***Matrices; // capacidades son dimensiones
int **matrices;
char nameMat[50]; //0 si es bounded y 1 si es unbounded

void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

void generate_Mats(GtkWidget *widget, gpointer user_data)
{

    gint dimens = gtk_spin_button_get_value_as_int (spinMatrices);
    nMatrices=dimens;

    strcpy(nameMat,gtk_entry_get_text(GTK_ENTRY(txtMatrices)));
    printf("nMatrices= %d\n nombreMatriz %s \n",nMatrices,nameMat );
    /*GtkWidget *table;
    GtkWidget *execute;
    
    table = gtk_grid_new();
    dimensiones= calloc(tamanio,sizeof(GtkWidget));
    int i;
    for(i=0; i<tamanio;i++)
        distancias[i]=calloc(tamanio,sizeof(GtkWidget));
    gtk_container_add (GTK_CONTAINER (container2), table);
    int x;
    int y;
    for(x=0;x<tamanio+1;x++){
       for(y=0; y<tamanio+1;y++){
            GtkWidget *label;
            printf("x= %d y y=%d\n",x,y );
            if(x==0 && y==0){
                label=gtk_label_new ("Nodos");
                gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);
            }else{
                if(x==0){
                    label=gtk_label_new(gtk_entry_get_text (nombres[y-1]));
                    gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);                   
                }else if(y==0){
                    label=gtk_label_new(gtk_entry_get_text (nombres[x-1]));
                    gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);                   
                }else if(x==y){
                    label=gtk_label_new("0");
                    gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);
                    GtkWidget *entry;
                    entry = gtk_entry_new ();
                    gtk_entry_set_text (GTK_ENTRY (entry), "0");
                    distancias[x-1][y-1]= entry;
                    printf("Almacenando en x= %d y y=%d\n",x-1,y-1 );
                }else{
                    GtkWidget *entry;
                    entry = gtk_entry_new ();
                    gtk_grid_attach (GTK_GRID (table), entry, x, y, 1, 1);
                    distancias[x-1][y-1]= entry;
                    printf("Almacenando en x= %d y y=%d\n",x-1,y-1 );

                }            

            }//fin if
        }// end primer for
    }//end for
     createFloyd = gtk_button_new_with_label("Ejecutar algoritmo Floyd");
    g_signal_connect (createFloyd, "clicked", G_CALLBACK (ejecutarFloyd), NULL);
    gtk_grid_attach (GTK_GRID (table), createFloyd, 1, tamanio+2, 1, 1);

    addNode = gtk_button_new_with_label("+");
    g_signal_connect (addNode, "clicked", G_CALLBACK (ejecutarFloyd), NULL);
    gtk_grid_attach (GTK_GRID (table), addNode, 2, tamanio+2, 1, 1);
    gtk_widget_show_all (window);*/
}

int main(int argc, char *argv[])
{
    
    GtkWidget *btnCargar;
    GtkWidget *btnSave;
    GtkWidget *btnInMat;

    gtk_init(&argc, &argv);    
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "Matrices.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "windowMatrices"));
    gtk_widget_set_size_request(GTK_WINDOW(window),900,800);
    btnCargar = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnCargar"));
    btnSave = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnGuardar"));
    btnInMat = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnMatrices"));
    SRWindwMatrices = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "scrlWinMatrices"));
    gtk_widget_set_size_request(GTK_WINDOW(SRWindwMatrices),200,200);
    spinMatrices= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinMats"));
    txtMatrices= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "txtNameMat"));
    g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
    gtk_widget_set_tooltip_text (btnCargar, "Incorpora la informacion de un archivo. "); 
    gtk_widget_set_tooltip_text (btnSave, "Guarda el estado actual de los datos ingresados. "); 
    g_signal_connect (btnInMat, "clicked",G_CALLBACK (generate_Mats),NULL);
    /*g_signal_connect (btnUnbounded, "clicked",G_CALLBACK (showUnbounded),NULL);
    */
    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_widget_show(window);
    gtk_main();
    
    return 0;
}
