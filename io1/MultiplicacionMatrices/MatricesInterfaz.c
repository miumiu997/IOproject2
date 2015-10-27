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
GtkWidget *fileChooser;
int nMatrices;
GtkWidget ***Matrices; // capacidades son dimensiones
char nameMat[50]; //0 si es bounded y 1 si es unbounded



/*Cargar desde un archivo*/
void cargarFile(GtkWidget *widget, gpointer user_data){ 
    int cantidad; 
    cantidad = nMatrices;  
    int** matriz; 
    char* filename;
    filename=gtk_file_chooser_get_filename (fileChooser);   

    
    printf("leer matrices \n"); 
    printf("nombre archivo %s\n", filename);   
    FILE *fp;
    fp = fopen(filename, "r"); 

    char ch;
    char* palabra;
    int largo = 0;
    palabra = (char*)calloc(1, sizeof(char));   
    int i,j; 
    int numero;
    int max;
    int fila=0;
    int columna=0;
    
    int f=0;
    while((ch=fgetc(fp)) != '\n'){
        if (ch == ';')
        {
            printf("nom:%s\n", palabra);
            gtk_entry_set_text(txtMatrices,palabra);
            largo =0;
            f++;
        }
        else{
            largo++;
            palabra = (char*) realloc(palabra,largo * sizeof(char));
            palabra[largo-1] = ch;
        }
        
    }
    printf("nom:%s\n", palabra);

    while((ch=fgetc(fp)) != '\n'){
        largo++;
        palabra = (char*) realloc(palabra,largo * sizeof(char));
        palabra[largo-1] = ch;
    }   
    largo = 0;
    numero = atoi(palabra);
    printf("tamanio %d\n",numero);
    int cuantas=0;

    gtk_spin_button_set_value(spinMatrices,numero);

    generate_Mats();

    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n' ){

            printf("%d",atoi(palabra));

            printf("\n");
           // matriz[nodo1-1][nodo2-1] =atoi(palabra);
            gtk_entry_set_text(dimensiones[fila][columna],g_strdup_printf("%d",atoi(palabra)));

            largo=0;
            palabra = (char*) realloc(palabra,1);
            fila=fila+1;
        }
        else if (ch == '-'){
            fseek( fp, ftell(fp)-2, SEEK_SET );
            columna = 1;
            printf("columna:%d - ",columna);
            fgetc(fp);
            largo=0;
            palabra = (char*) realloc(palabra,0);
        }       
        else{
            largo++;
            palabra = (char*) realloc(palabra,largo * sizeof(char));
            palabra[largo-1] = ch;
            columna=0;

        }
    }


    fclose(fp);
    printf("\n");


}//end filechooser

/*Pasar de tipo entry a int*/
void convertirEntry(int** matInterfaz){
    int i;
    printf("entre a convertirEntry\n");
    //////COnvertir a ints
    int x;
    int y;
    int valor;
    gchar *str;
    for(x=0; x<nMatrices;x++){
        for(y=0; y<2; y++){
            printf("entre a los ciclos, esto tiene distancias %s \n",gtk_entry_get_text (dimensiones[x][y]));
            //g_stpcpy(str, gtk_entry_get_text (distancias[x][y]));
            //printf("hola\n" );
            valor = atoi(gtk_entry_get_text(GTK_ENTRY(dimensiones[x][y])));
            printf("voy por aqui x y y %d %d, valor %d\n",x,y,valor );
            matInterfaz[x][y]=valor;
        }//end second for

    }//end first for-

    llenarDimensiones(nameMat,nMatrices ,matInterfaz);
}//fin convertirEntry

void ejecutarMatrices(GtkWidget *object, gpointer user_data){
    int i;
    int **matInterfaz = (int **)calloc(nMatrices+1,sizeof(int *));   
     for (i=0; i<nMatrices+1; i++){
      matInterfaz[i] = (int *)calloc(3,sizeof(int));     
    }
    convertirEntry(matInterfaz);
}

void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

void generate_Mats(GtkWidget *widget, gpointer user_data)
{
    const char label2[100];
    gint dimens = gtk_spin_button_get_value_as_int (spinMatrices);
    nMatrices=dimens;
    strcpy(nameMat,gtk_entry_get_text(GTK_ENTRY(txtMatrices)));
    printf("nMatrices= %d\n nombreMatriz %s \n",nMatrices,nameMat );
    GtkWidget *table;
    GtkWidget *execute;

    
    table = gtk_grid_new();
    dimensiones= calloc(nMatrices,sizeof(GtkWidget));
    int i;
    for(i=0; i<nMatrices;i++)
        dimensiones[i]=calloc(3,sizeof(GtkWidget));
    gtk_container_add (GTK_CONTAINER (SRWindwMatrices), table);
    int fila;
    int columna;
    for(fila=0;fila<nMatrices;fila++){
       for(columna=0; columna<2;columna++){
            GtkWidget *entry;
            entry = gtk_entry_new ();
            gtk_grid_attach (GTK_GRID (table), entry, columna,fila, 1, 1);
            dimensiones[fila][columna]= entry;
            printf("Almacenando en x= %d y y=%d\n", fila,columna);
       }// end primer for
        //fila=fila+1;
    }//end for
    execute = gtk_button_new_with_label("Ejecutar algoritmo");
    g_signal_connect (execute, "clicked", G_CALLBACK (ejecutarMatrices), NULL);
    gtk_grid_attach (GTK_GRID (table), execute, 1, nMatrices+2, 1, 1);

    
    gtk_widget_show_all (window);
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
    fileChooser= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnChooseFile"));
    g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
    gtk_widget_set_tooltip_text (btnCargar, "Incorpora la informacion de un archivo. "); 
    gtk_widget_set_tooltip_text (btnSave, "Guarda el estado actual de los datos ingresados. "); 
    g_signal_connect (btnInMat, "clicked",G_CALLBACK (generate_Mats),NULL);
    g_signal_connect (btnCargar, "clicked",G_CALLBACK (cargarFile),NULL);
    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_widget_show(window);
    gtk_main();
    
    return 0;
}
