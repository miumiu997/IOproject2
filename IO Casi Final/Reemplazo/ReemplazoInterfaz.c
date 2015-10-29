#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logicaReemplazo.h"

//variables globales
GtkBuilder *gtkBuilder;
GtkWidget *window;
GtkWidget *SRWindowMantenimiento;
GtkWidget ***mantenimientos;
GtkWidget *btnChooseFile;

GtkWidget *spinCambio;
GtkWidget *spinVidaUtil;
GtkWidget *txtCosto;
GtkWidget *txtnewfile;

char *filename;

int **mantenimientoObjs;
int **venta;
int costo;
int vidaUtil;
int cambio; //0 si es bounded y 1 si es unbounded

void cargarFile(GtkWidget *widget, gpointer user_data){ 
    filename=gtk_file_chooser_get_filename (btnChooseFile);  
    FILE *fp;
    fp = fopen(filename, "r");

    char ch;
    char* palabra = (char*)calloc(0, sizeof(char));
    int largo = 0;
    int vida;
    int plazo;
    int compra;
    int i;

    while((ch=fgetc(fp)) != '\n'){
        largo++;
        palabra = (char*) realloc(palabra,largo * sizeof(char));
        palabra[largo-1] = ch;
    }
    vida = atoi(palabra);
    printf("vida:%d\n",vida);
    gtk_spin_button_set_value(spinVidaUtil,vida);
    largo = 0;
    while((ch=fgetc(fp)) != '\n'){
        largo++;
        palabra = (char*) realloc(palabra,largo * sizeof(char));
        palabra[largo-1] = ch;
    }
    plazo = atoi(palabra);
    printf("plazo:%d\n",plazo);
    gtk_spin_button_set_value(spinCambio,plazo);
    largo = 0;
    while((ch=fgetc(fp)) != '\n'){
        largo++;
        palabra = (char*) realloc(palabra,largo * sizeof(char));
        palabra[largo-1] = ch;
    }
    compra = atoi(palabra);
    printf("compra:%d\n",compra);
    gtk_entry_set_text(txtCosto,palabra);
    largo = 0;
    palabra = (char*) realloc(palabra,0 * sizeof(char));

    showMantenimientos();

    for (i = 0; i < vida; ++i)
    {
        while((ch=fgetc(fp)) != ','){
            largo++;
            palabra = (char*) realloc(palabra,largo * sizeof(char));
            palabra[largo-1] = ch;
        }
        printf("%d,", atoi(palabra));


        gtk_entry_set_text(mantenimientos[0][i],g_strdup_printf("%d",atoi(palabra)));


        largo =0;
        palabra = (char*) realloc(palabra,0 * sizeof(char));
        while((ch=fgetc(fp)) != '\n'){
            largo++;
            palabra = (char*) realloc(palabra,largo * sizeof(char));
            palabra[largo-1] = ch;
        }
        printf("%d,", atoi(palabra));


        gtk_entry_set_text(mantenimientos[1][i],g_strdup_printf("%d",atoi(palabra)));



        largo =0;

        printf("\n");
    }
}


void convertirEntry(){
	int i;
	int buu;
	venta= (int *)calloc(vidaUtil,sizeof(int));
	mantenimientoObjs= (int *)calloc(vidaUtil,sizeof(int));
		 
    int x;
    int y;
    int valor;
    gchar *str;
    for(x=0; x<2;x++){
    	for(y=0; y<vidaUtil; y++){
    		//valor x=1 y=0
    		if(x==0){
    			venta[y]=atoi(gtk_entry_get_text(GTK_ENTRY(mantenimientos[x][y])));
    			printf("EStos son los venta %s \n",gtk_entry_get_text (mantenimientos[x][y]));
    		}else if(x==1){
    			//peso
    			mantenimientoObjs[y]=atoi(gtk_entry_get_text(GTK_ENTRY(mantenimientos[x][y])));
    			printf("EStos son los mantenimientos %s \n",gtk_entry_get_text (mantenimientos[x][y]));
    		}
    		
    	}//end second for

    }//end first for

     int* g=(int*)calloc(cambio+1, sizeof(int));

    int **proximo = (int **)calloc(cambio , sizeof(int *));
    for (i=0; i<cambio; i++){
         proximo[i] = (int *)calloc(1 , sizeof(int));
    }

    buu=equipmentReplacement(costo,vidaUtil,cambio,mantenimientoObjs,venta,g,proximo);
    equipmentBeamer(g,proximo,cambio);
     //system("evince --fullscreen equipment.pdf");
}//fin convertirEntry

void ejecutarReemplazo(GtkWidget *object, gpointer user_data){
    printf("Reemplazo\n");
    convertirEntry();

}
void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

void showMantenimientos(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *table;
    GtkWidget *createReemplazo;
    char val;
    
    gint vidaUtilVal = gtk_spin_button_get_value_as_int (spinVidaUtil);
    vidaUtil= vidaUtilVal;
    int costoVal = atoi(gtk_entry_get_text(GTK_ENTRY(txtCosto)));
    costo= costoVal;
    printf("Spin costo %d\n",costo );
    gint cambVal = gtk_spin_button_get_value_as_int (spinCambio);
    cambio=cambVal;

    table = gtk_grid_new();
    printf("entre a show mantenimientos, vida util %d \n",vidaUtil);
    mantenimientos= calloc(vidaUtil,sizeof(GtkWidget));
    int i;
    for(i=0; i<vidaUtil;i++)
        mantenimientos[i]=calloc(2,sizeof(GtkWidget));
    printf("pase el ciclo de calloc\n");
    gtk_container_add (GTK_CONTAINER (SRWindowMantenimiento), table);
    int x;
    int y;
    for(x=0;x<3;x++){
       for(y=0; y<vidaUtil+1;y++){
    		GtkWidget *label;
            printf("x= %d y=%d\n",x,y );
    		if(x==0 && y==0){
    			label=gtk_label_new ("Lapsos");
    			gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);
                printf("lapsos\n");
    		}else{
	    		if(y==0){
                    if(x==1){
                        label=gtk_label_new("Venta");
                        printf("vemta\n");
                    }else if(x==2){
                        label=gtk_label_new("Mantenimiento");
                        printf("mantenimiento\n");
                    }			    	
			    	gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);                   
	    		}else if(x==0){
                    val=y;
                    printf("Val- %c\n",val );

	    			label=gtk_label_new(g_strdup_printf("%d",val));
                   //gtk_label_set_text (label,y);
                    printf("Lapso\n");
	    			gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);                   
	    		}else{
	    			GtkWidget *entry;
					entry = gtk_entry_new ();
			    	gtk_grid_attach (GTK_GRID (table), entry, x, y, 1, 1);
                    mantenimientos[x-1][y-1]= entry;
                    printf("Almacenando en x= %d y y=%d\n",x-1,y-1 );

			    }            

		    }//fin if
	    }// end primer for
    }//end for
     createReemplazo = gtk_button_new_with_label("Ejecutar algoritmo de Reemplazo");
    g_signal_connect (createReemplazo, "clicked", G_CALLBACK (ejecutarReemplazo), NULL);
    gtk_grid_attach (GTK_GRID (table), createReemplazo, 1, vidaUtil+2, 1, 1);
    gtk_widget_show_all (window);
  
}

int main(int argc, char *argv[])
{
    
    GtkWidget *btnMantenimientos;
    GtkWidget *btnSave;
    GtkWidget *btnCargar;

    gtk_init(&argc, &argv);    
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "Reemplazo.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "windowReemplazo"));
    gtk_widget_set_size_request(GTK_WINDOW(window),900,800);
    btnCargar = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnCargar"));
    btnSave = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnSave"));
    btnChooseFile = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnChooseFile"));
    btnMantenimientos = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnMantenimientos"));
    txtnewfile= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "txtnewfile"));
    

    SRWindowMantenimiento = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "SRWindowMantenimiento"));
    gtk_widget_set_size_request(GTK_WINDOW(SRWindowMantenimiento),200,200);
    
    spinCambio= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinCambio"));
    cambio=spinCambio;
    txtCosto= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "txtCosto"));
    costo= txtCosto;
    spinVidaUtil= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinVidaUtil"));
    vidaUtil=spinVidaUtil;
    g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
    gtk_widget_set_tooltip_text (btnMantenimientos, "Crea los espacios para indicar los costos de mantenimiento. "); 
    gtk_widget_set_tooltip_text (btnChooseFile, "Seleccionar el archivo que se desea cargar. "); 
    gtk_widget_set_tooltip_text (btnSave, "Guardar el estado actual de las indicaciones. "); 

    g_signal_connect (btnMantenimientos, "clicked",G_CALLBACK (showMantenimientos),NULL);
    g_signal_connect (btnCargar, "clicked",G_CALLBACK (cargarFile),NULL);
    /*g_signal_connect (btnSave, "clicked",G_CALLBACK (showUnbounded),NULL);
    g_signal_connect (btnChooseFile, "clicked",G_CALLBACK (showUnbounded),NULL);
	*/
    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_widget_show(window);
    gtk_main();
    
    return 0;
}