#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logicaFloyd.h"

//variables globales
GtkBuilder *gtkBuilder;
GtkWidget *window;
GtkWidget *container;
GtkWidget *container2;
GtkWidget *spinNodos;
GtkWidget *fileChooser;
int tamanio;
GtkWidget ***distancias;
GtkWidget **nombres;
int **distanciasFloyd;
gint res;
char *filename;
GtkWidget *txtNewFile;

/*Cargar desde un archivo*/
void cargarFile(GtkWidget *widget, gpointer user_data){ 
    int cantidad; 
    cantidad = tamanio;  
    int** matriz; 
    filename=gtk_file_chooser_get_filename (fileChooser);   

    
    printf("leer floyd \n"); 
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
    int nodo1;
    int nodo2;

    while((ch=fgetc(fp)) != '\n'){
        largo++;
        palabra = (char*) realloc(palabra,largo * sizeof(char));
        palabra[largo-1] = ch;
    }   
    largo = 0;
    numero = atoi(palabra);
    printf("tamanio %d\n",numero);
    int cuantas=0;

    gtk_spin_button_set_value(spinNodos,numero);

    show_nodes();

    int f=0;
    while((ch=fgetc(fp)) != '\n'){
        if (ch == ',')
        {
            printf("nom:%s\n", palabra);
            gtk_entry_set_text(nombres[f],palabra);
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
    gtk_entry_set_text(nombres[f],palabra);

    largo = 0;

    generate_table();

    for (i = 0; i < numero; ++i)
    {
        for (j = 0; j < numero; ++j)
        {
            gtk_entry_set_text(distancias[i][j],g_strdup_printf("%d",9999));
        }
    }

    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n' ){

            printf("%d",atoi(palabra));

            printf("\n");
           // matriz[nodo1-1][nodo2-1] =atoi(palabra);
            gtk_entry_set_text(distancias[nodo2-1][nodo1-1],g_strdup_printf("%d",atoi(palabra)));

            largo=0;
            palabra = (char*) realloc(palabra,1);
        }
        else if (ch == '-'){
            fseek( fp, ftell(fp)-2, SEEK_SET );
            nodo1 = fgetc(fp)- '0';
            printf("nodo1:%d - ",nodo1);
            fgetc(fp);
            largo=0;
            palabra = (char*) realloc(palabra,0);
        }
        else if (ch == '='){
            fseek( fp, ftell(fp)-2, SEEK_SET );
            nodo2 = fgetc(fp)- '0';
            printf("nodo2:%d - ",nodo2);
            fgetc(fp);
            largo=0;
            palabra = (char*) realloc(palabra,0);
        }
        else{
            largo++;
            palabra = (char*) realloc(palabra,largo * sizeof(char));
            palabra[largo-1] = ch;

        }
    }


    fclose(fp);
    printf("\n");


}


/*GUardar lo de la interfaz*/
void save(GtkWidget *widget, gpointer user_data){ 
int a,b,x; 
char newfile[50];
strcpy(newfile,gtk_entry_get_text (GTK_ENTRY(txtNewFile)) );
//char text; 

    g_printf("--------------------- %d\n");  
    printf("%d \n", tamanio);  
    for(x=0; x<tamanio;x++){ 
        if(x==0){
            g_printf("%s\0", gtk_entry_get_text(GTK_ENTRY(nombres[x])));
        } 
        else{ 
            g_printf(",%s\0", gtk_entry_get_text(GTK_ENTRY(nombres[x])));
        }
    }  
    printf("\n");
    for (a = 0; a < tamanio; a++){
        for (b = 0; b < tamanio; b++){ 
            printf("v%d",a); 
            printf("-v%d",b); 
            printf("=%s\n", gtk_entry_get_text (distancias[b][a]) );
        }
    }

printf("--------------------- %d\n"); 

   FILE *fp;

   fp = fopen(newfile, "w"); 

    fprintf(fp, "%d \n", tamanio);  
        for(x=0; x<tamanio;x++){   
        if(strcmp(gtk_entry_get_text(GTK_ENTRY(nombres[x])), " ")){
            if(x==0){
                fprintf(fp, "%s\0", gtk_entry_get_text(GTK_ENTRY(nombres[x])));
            } 
            else{ 
                fprintf(fp, ",%s\0", gtk_entry_get_text(GTK_ENTRY(nombres[x])));
            } 
        } 
        else{  
            if(x==0){
                fprintf(fp, "inf \0");
            } 
            else{ 
                fprintf(fp, ",inf \0");
            } 

        }
    } 
    fprintf(fp, "\n");
    for (a = 0; a < tamanio; a++){
        for (b = 0; b < tamanio; b++){ 
            fprintf(fp,"v%d",a); 
            fprintf(fp, "-v%d",b); 
            fprintf(fp, "=%s\n", gtk_entry_get_text (distancias[b][a]));
        }
    }

   fclose(fp);
} 

/*Pasar de tipo entry a int*/
void convertirEntry(){
	int i;
	printf("entre a convertirEntry\n");
	distanciasFloyd = (int **)calloc(tamanio,sizeof(int *));
	for (i=0; i<tamanio+1; i++)
         distanciasFloyd[i] = (int *)calloc(tamanio+1,sizeof(int));
     int a;
     int b;
    for (a = 0; a < tamanio; a++)
    {
    	/* code */
   		for (b = 0; b < tamanio; b++)
    {
    	/* code */
    	printf("entre a los primeros ciclos\n");
    	printf("distancias %s\n", gtk_entry_get_text (distancias[a][b]) );
    }
    }
    int x;
    int y;
    int valor;
    gchar *str;
    for(x=0; x<tamanio;x++){
    	for(y=0; y<tamanio; y++){
    		printf("entre a los ciclos, esto tiene distancias %s \n",gtk_entry_get_text (distancias[x][y]));
    		//g_stpcpy(str, gtk_entry_get_text (distancias[x][y]));
    		//printf("hola\n" );
   			valor = atoi(gtk_entry_get_text(GTK_ENTRY(distancias[x][y])));
    		//valor=atoi(gtk_entry_get_text (nombres[y-1]));
    		printf("voy por aqui x y y %d %d, valor %d\n",x,y,valor );
    		distanciasFloyd[y][x]=valor;
    	}//end second for

    }//end first for


}//fin convertirEntry

void ejecutarFloyd(GtkWidget *object, gpointer user_data){
	convertirEntry();
    int **p = (int **)malloc(tamanio * sizeof(int *));
    int i,j;
    for (i=0; i<tamanio; i++){
         p[i] = (int *)malloc(tamanio* sizeof(int));
    }

    int **matriz = (int **)malloc(tamanio * sizeof(int *));
    for (i=0; i<tamanio; i++){
         matriz[i] = (int *)malloc(tamanio * sizeof(int));
    }

    for (i = 0; i < tamanio; ++i)
    {
        for (j = 0; j < tamanio; ++j)
        {
            matriz[i][j]=distanciasFloyd[i][j];
        }
    }

	floyd(distanciasFloyd,tamanio,p);
    floydBeamer(matriz,distanciasFloyd,p,tamanio);
    //system("evince --fullscreen floyd.pdf");


}
void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

void button_clicked(GtkWidget *widget, gpointer data) {
    
  g_print("clicked\n");
}

void generate_table(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *table;
    GtkWidget *createFloyd;
    GtkWidget *addNode;
    table = gtk_grid_new();
    distancias= calloc(tamanio,sizeof(GtkWidget));
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

    gtk_widget_show_all (window);
}

void show_nodes(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *table;
    GtkWidget *generaTable;
    table = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (container), table);
    gint nodos = gtk_spin_button_get_value_as_int (spinNodos);
    tamanio=nodos;
    nombres= calloc(nodos,sizeof(GtkWidget*));    
    g_print("Nodos %d\n",nodos);
    int x;
    GtkWidget *entry[nodos];
    for(x=0;x<nodos;x++){
        GtkWidget *distancia;
        distancia = gtk_entry_new ();
        nombres[x]= distancia;
        gtk_grid_attach (GTK_GRID (table), distancia, x, 0, 1, 1);      
        printf("X=%d\n",x );
    }//end for
    generaTable = gtk_button_new_with_label("Distancias");
    g_signal_connect (generaTable, "clicked", G_CALLBACK (generate_table), NULL);
    gtk_grid_attach (GTK_GRID (table), generaTable, 0, 1, 1, 1);
    //gtk_widget_show (window);
   
    gtk_widget_show_all (window);
   
}

int main(int argc, char *argv[])
{
    
    GtkWidget *btnCrearTabla;
    GtkWidget *btnCargar;
    GtkWidget *btnSavee;
    gtk_init(&argc, &argv);    
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "ProblemaFloydProperties.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "windowFloyd"));
    gtk_widget_set_size_request(GTK_WINDOW(window),900,800);
    btnCrearTabla = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnCrearTabla"));
    btnCargar = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnCargar"));
    btnSavee= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnSavee"));
    fileChooser= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "filechooserbutton1"));
    container = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "SRWindw"));
    gtk_widget_set_size_request(GTK_WINDOW(container),70,70);
    container2 = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "scrollDistancias"));
    gtk_widget_set_size_request(GTK_WINDOW(container2),200,200);
    spinNodos= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinNodos"));
	txtNewFile = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "txtNewFile"));
       
        
        
    g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
    gtk_widget_set_tooltip_text (btnCrearTabla, "En base al dato anterior se genera la tabla. "); 
    gtk_widget_set_tooltip_text (btnCargar, "Se cargan los datos desde un archivo. "); 
    gtk_widget_set_tooltip_text (btnSavee, "Se capturan en un archivo los datos suministrados. "); 
    g_signal_connect (btnCrearTabla, "clicked",G_CALLBACK (show_nodes),NULL);
    g_signal_connect (btnCargar, "clicked",G_CALLBACK (cargarFile),NULL);
     g_signal_connect (btnSavee, "clicked",G_CALLBACK (save),NULL);
	//itemSalir
    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_widget_show(window);
    gtk_main();
    
    return 0;
}
