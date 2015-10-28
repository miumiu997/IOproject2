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
GtkWidget *fileChooser;

GtkWidget **dimensiones;
char *filename;


int nMatrices;
int **matrices; 
int Partidos;
int ProbaH;
int ProbaR; 
int SerieSize; 

void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

void cargarFile(GtkWidget *widget, gpointer user_data){ 
    filename=gtk_file_chooser_get_filename (fileChooser);   
    //printf("nombre archivo %s\n", gtk_file_chooser_get_filename (fileChooser));   
    FILE *fp;
    fp = fopen(filename, "r"); 

    char ch;
    char* palabra = (char*)calloc(1, sizeof(char));
   	int largo = 0;

    int cantidadPartidos;
    double home;
    double road;
    int* serie = (int*)calloc(1, sizeof(int));

    while((ch=fgetc(fp)) != '\n'){
        largo++;
        palabra = (char*) realloc(palabra,largo * sizeof(char));
        palabra[largo-1] = ch;
    } 
    printf("%s\n",palabra);
    gtk_spin_button_set_value(spinPartidos,atoi(palabra));
    palabra = (char*)calloc(1, sizeof(char));
    largo = 0;

    while((ch=fgetc(fp)) != '\n'){
        largo++;
        palabra = (char*) realloc(palabra,largo * sizeof(char));
        palabra[largo-1] = ch;
    } 
    gtk_spin_button_set_value(spinProbaH,atof(palabra));
    palabra = (char*)calloc(1, sizeof(char));
    largo = 0;

    while((ch=fgetc(fp)) != '\n'){
        largo++;
        palabra = (char*) realloc(palabra,largo * sizeof(char));
        palabra[largo-1] = ch;
    } 
    gtk_spin_button_set_value(spinProbaR,atof(palabra));
    palabra = (char*)calloc(1, sizeof(char));
    largo = 0;

    while((ch=fgetc(fp)) != '\n'){
        largo++;
        palabra = (char*) realloc(palabra,largo * sizeof(char));
        palabra[largo-1] = ch;
    } 
    gtk_spin_button_set_value(TamanioSerie,atoi(palabra));
    palabra = (char*)calloc(1, sizeof(char));
    largo = 0;

    while((ch=fgetc(fp)) != '\n'){
    	if (ch == '.')
    	{
    		printf("%s\n", palabra);
    		palabra = (char*)calloc(1, sizeof(char));
    		largo = 0;

    	}
    	else
    	{
    		largo++;
	        palabra = (char*) realloc(palabra,largo * sizeof(char));
	        palabra[largo-1] = ch;
    	}
    } 
    printf("%s\n", palabra);

}

void ejecutarDeportes(){
    printf("entre a ejecutarDeportes\n");
    //////COnvertir a ints
    int i; 
    int x;
    int games;
    double PHome;
    double PRoad;
    int size;
    
    int valor; 
    int valor2 = 0;    
    games = atoi(gtk_entry_get_text(GTK_ENTRY(spinPartidos)));
    PHome = atof(gtk_entry_get_text(GTK_ENTRY(spinProbaH)));
    PRoad = atof(gtk_entry_get_text(GTK_ENTRY(spinProbaR)));
    size = atoi(gtk_entry_get_text(GTK_ENTRY(TamanioSerie)));

    printf("games %d PHome %f ProbaR %f size %d\n",games,PHome,PRoad,size );
    int* serie= calloc(size,sizeof(GtkWidget));
    printf("esto tiene dimensiones\n");
    for(x=0;x<nMatrices;x++){  
            printf(" %s ",gtk_entry_get_text(GTK_ENTRY(dimensiones[x])));
            
    }
    printf("Entre al ciclo\n");
    for(x=0;x<nMatrices;x++){  
        printf("x == %d\n", x);
 
        if(x == 0){ 
            printf("entre a ==0\n");
            valor = atoi(gtk_entry_get_text(GTK_ENTRY(dimensiones[x])));
            printf("valor %d\n",valor );
        } 
        else{ 
            printf("entre al else con %d\n",x );
            valor = atoi(gtk_entry_get_text(GTK_ENTRY(dimensiones[x]))); 
            printf("--valor %d valor2 %d \n",valor, valor2);
            valor2= valor2 + atoi(gtk_entry_get_text(GTK_ENTRY(dimensiones[x-1])));
            valor= valor+valor2;   
            printf("--valor %d valor2 %d \n",valor, valor2);

        }
        serie[x] = valor; 

    }//end for  
    printf("entre al segundo ciclo\n");
    int **result = (int **)calloc(games+1,sizeof(int *));
    for (i=0; i<games+1; i++){
         result[i] = (int *)calloc(games+1,sizeof(int));
    } 
    printf("voy para serie deportiva\n");
    serie_deportiva(games, PHome, PRoad, serie, result, size); 


}

void creaTablaSerie(GtkWidget *widget, gpointer user_data)
{

    gint dimens = gtk_spin_button_get_value_as_int (TamanioSerie);
    nMatrices=dimens; 

    //Partidos = gtk_spin_button_get_value_as_int (spinPartidos);  
    //ProbaH = gtk_spin_button_get_value_as_int (spinProbaH); 
   // ProbaR = gtk_spin_button_get_value_as_int (spinProbaR); 


   // printf("Numero de partidos: %d \n", Partidos); 
   // printf("Probabilidad Home: %d \n", ProbaH);
   // printf("Probabilidad Visit: %d \n", ProbaR);


   // printf("nMatrices= %d\n nombreMatriz %s \n",nMatrices,nameMat );

    GtkWidget *table;
    GtkWidget *execute;

    
    table = gtk_grid_new();
    dimensiones= calloc(nMatrices,sizeof(GtkWidget));
    
    gtk_container_add (GTK_CONTAINER (SRWindowSerie), table);
    int x;
    int y;
    for(x=0;x<nMatrices;x++){
                    GtkWidget *entry;
                    entry = gtk_entry_new ();
                    gtk_grid_attach (GTK_GRID (table), entry, x, 1, 1, 1);
                    dimensiones[x]= entry;
                   // printf("Almacenando en x= %d y y=%d\n",x-1,y-1 );

    }//end for
    execute = gtk_button_new_with_label("Ejecutar algoritmo");
    g_signal_connect (execute, "clicked", G_CALLBACK (ejecutarDeportes), NULL);
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
    gtk_widget_set_size_request(GTK_WINDOW(window),900,800);
    btnCargar = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnCargar"));
    btnSave = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnSave"));
    btnChooseFile = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "filechooserbutton1"));
    buttonIngresarDatos = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "buttonIngresarDatos"));
    buttonSerieTable = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "buttonSerieTable"));

    SRWindowSerie = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "SRWindwSerie"));
    gtk_widget_set_size_request(GTK_WINDOW(SRWindowSerie),200,200);
    
    spinPartidos = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinPartidos"));
    Partidos = spinPartidos;
    spinProbaH = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinProbaH"));
    ProbaH = spinProbaH;
    spinProbaR = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinProbaR"));
    ProbaR = spinProbaR; 
    TamanioSerie = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinSerie"));
    SerieSize = TamanioSerie; 
    fileChooser=  GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "filechooserbutton1"));

    gtk_widget_set_tooltip_text (buttonIngresarDatos, "Implementa el algoritmo con los datos ingresados.");  
    gtk_widget_set_tooltip_text (buttonSerieTable, "Crea los espacios para indicar la cantidad de partidos por serie."); 
    gtk_widget_set_tooltip_text (btnChooseFile, "Seleccionar el archivo que se desea cargar. "); 
    gtk_widget_set_tooltip_text (btnSave, "Guardar el estado actual de las indicaciones."); 

    g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
   // g_signal_connect (buttonIngresarDatos, "clicked",G_CALLBACK (showDatos),NULL); 
    g_signal_connect (buttonSerieTable, "clicked",G_CALLBACK (creaTablaSerie),NULL);
    g_signal_connect (btnCargar, "clicked",G_CALLBACK (cargarFile),NULL);
    /*g_signal_connect (btnSave, "clicked",G_CALLBACK (showUnbounded),NULL);
    g_signal_connect (btnChooseFile, "clicked",G_CALLBACK (showUnbounded),NULL);
	*/
    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_widget_show(window);
    gtk_main();
    
    return 0;
}
