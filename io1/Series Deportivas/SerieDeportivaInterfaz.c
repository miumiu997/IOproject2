#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logica_series_deportivas.h"

//variables globales 

GtkBuilder *gtkBuilder;
GtkWidget *window;
GtkWidget *SRWindowSerie;
GtkWidget *btnChooseFile;

GtkWidget *spinPartidos;
GtkWidget *spinProbaH;
GtkWidget *spinProbaR;  
GtkWidget *TamanioSerie;  

GtkWidget ***dimensiones;


int nMatrices;
int **matrices; 
int Partidos;
int ProbaH;
int ProbaR; 
int SerieSize; 

void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

void creaTablaSerie(GtkWidget *widget, gpointer user_data)
{

    gint dimens = gtk_spin_button_get_value_as_int (TamanioSerie);
    nMatrices=dimens; 

    Partidos = gtk_spin_button_get_value_as_int (spinPartidos);  
    ProbaH = gtk_spin_button_get_value_as_int (spinProbaH); 
    ProbaR = gtk_spin_button_get_value_as_int (spinProbaR); 


    printf("Numero de partidos: %d \n", Partidos); 
    printf("Probabilidad Home: %d \n", ProbaH);
    printf("Probabilidad Visit: %d \n", ProbaR);


   // printf("nMatrices= %d\n nombreMatriz %s \n",nMatrices,nameMat );

    GtkWidget *table;
    GtkWidget *execute;

    
    table = gtk_grid_new();
    dimensiones= calloc(nMatrices,sizeof(GtkWidget));
    int i;
    for(i=0; i<nMatrices;i++)
        dimensiones[i]=calloc(3,sizeof(GtkWidget));
    gtk_container_add (GTK_CONTAINER (SRWindowSerie), table);
    int x;
    int y;
    for(x=0;x<nMatrices+1;x++){
       for(y=0; y<2;y++){
            GtkWidget *label;
           // printf("x= %d y y=%d\n",x,y );
            if(x==0 && y==0){
               // label=gtk_label_new ("dimensiones");
                gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);
            }else{
                if(x==0){
                 //   label=gtk_label_new(gtk_entry_get_text (txtMatrices));
                    gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);                   
                }else if(y==0){
                 //   label=gtk_label_new(gtk_entry_get_text (txtMatrices));
                    gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);                  
                
                }else{
                    GtkWidget *entry;
                    entry = gtk_entry_new ();
                    gtk_grid_attach (GTK_GRID (table), entry, x, y, 1, 1);
                    dimensiones[x-1][y-1]= entry;
                   // printf("Almacenando en x= %d y y=%d\n",x-1,y-1 );

                }            

            }//fin if
        }// end primer for
    }//end for
    execute = gtk_button_new_with_label("Ejecutar algoritmo");
    //g_signal_connect (createFloyd, "clicked", G_CALLBACK (ejecutarFloyd), NULL);
    gtk_grid_attach (GTK_GRID (table), execute, 1, nMatrices+2, 1, 1);

    
    gtk_widget_show_all (window);
}
int main(int argc, char *argv[])
{
    
    GtkWidget *buttonIngresarDatos;
    GtkWidget *btnSave;
    GtkWidget *btnCargar; 
    GtkWidget *buttonSerieTable;

    gtk_init(&argc, &argv);    
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "SeriesDeportivas.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "windowDeportes"));
   // gtk_widget_set_size_request(GTK_WINDOW(window),900,800);
    btnCargar = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnCargar"));
    btnSave = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnSave"));
    btnChooseFile = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "filechooserbutton1"));
    buttonIngresarDatos = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "buttonIngresarDatos"));
    buttonSerieTable = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "buttonSerieTable"));
    SRWindowSerie = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "SRWindwSerie"));
   // gtk_widget_set_size_request(GTK_WINDOW(SRWindowSerie,200,200);
    
    spinPartidos = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinPartidos"));
    Partidos = spinPartidos;
    spinProbaH = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinProbaH"));
    ProbaH = spinProbaH;
    spinProbaR = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinProbaR"));
    ProbaR = spinProbaR; 
    TamanioSerie = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinSerie"));
    SerieSize = TamanioSerie; 

    gtk_widget_set_tooltip_text (buttonIngresarDatos, "Implementa el algoritmo con los datos ingresados.");  
    gtk_widget_set_tooltip_text (buttonSerieTable, "Crea los espacios para indicar la cantidad de partidos por serie."); 
    gtk_widget_set_tooltip_text (btnChooseFile, "Seleccionar el archivo que se desea cargar. "); 
    gtk_widget_set_tooltip_text (btnSave, "Guardar el estado actual de las indicaciones."); 

    g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
   // g_signal_connect (buttonIngresarDatos, "clicked",G_CALLBACK (showDatos),NULL); 
    g_signal_connect (buttonSerieTable, "clicked",G_CALLBACK (creaTablaSerie),NULL);
  //  g_signal_connect (btnCargar, "clicked",G_CALLBACK (cargarFile),NULL);
    /*g_signal_connect (btnSave, "clicked",G_CALLBACK (showUnbounded),NULL);
    g_signal_connect (btnChooseFile, "clicked",G_CALLBACK (showUnbounded),NULL);
	*/
    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_widget_show(window);
    gtk_main();
    
    return 0;
}
