#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//variables globales
GtkBuilder *gtkBuilder;
GtkWidget *window;
GtkWidget *SRWindwMatrices; // division en la que se van actualizar las dimensiones de las matrices
GtkWidget *spinMatrices;
int nObjetos;
GtkWidget ***capacidades; // capacidades son dimensiones
GtkWidget **objetos; //objetos son matrices
int **valores;
int **pesos;
int **cantidades;
int capacidadMochila;
int tipo; //0 si es bounded y 1 si es unbounded

void convertirEntryBounded(){
    int i;
    int buu;
    valores= (int *)calloc(nObjetos+1,sizeof(int));
    pesos= (int *)calloc(nObjetos+1,sizeof(int));
    cantidades= (int *)calloc(nObjetos+1,sizeof(int));
     
    int x;
    int y;
    int valor;
    gchar *str;
       for(y=0; y<nObjetos; y++){
        printf("vamos por el %d \n" ,y );
           valores[y]=atoi(gtk_entry_get_text(GTK_ENTRY(capacidades[0][y])));
           printf("EStos son los valores %s \n",gtk_entry_get_text (capacidades[0][y]));
                   //peso
           pesos[y]=atoi(gtk_entry_get_text(GTK_ENTRY(capacidades[1][y])));
            printf("EStos son los pesos %s \n",gtk_entry_get_text (capacidades[1][y]));
            cantidades[y]=atoi(gtk_entry_get_text(GTK_ENTRY(capacidades[2][y])));
             printf("EStos son las cantidades %s \n",gtk_entry_get_text (capacidades[2][y]));
    }//end first for

     int **colores = (int **)calloc(nObjetos+1,sizeof(int *));
    for (i=0; i<nObjetos+1; i++)
         colores[i] = (int *)calloc(capacidadMochila+1,sizeof(int));


    int **resultado = (int **)calloc(nObjetos+1,sizeof(int *));
    for (i=0; i<nObjetos+1; i++)
         resultado[i] = (int *)calloc(capacidadMochila+1,sizeof(int));

     int **sub = (int **)calloc(nObjetos+1,sizeof(int *));
    for (i=0; i<nObjetos+1; i++)
         sub[i] = (int *)calloc(capacidadMochila+1,sizeof(int));

    buu=boundedknapSack(capacidadMochila, pesos,valores, cantidades, nObjetos,resultado,colores,sub);
    buu=knapSackBeamer(resultado,capacidadMochila, nObjetos, colores);
    system("evince --fullscreen knapSack.pdf");
}//fin convertirEntry

void convertirEntryUnbounded(){
    printf("Entro a convertir Entry\n");
    int i;
    int buu;
    valores= (int *)calloc(nObjetos+1,sizeof(int));
    pesos= (int *)calloc(nObjetos+1,sizeof(int));
    cantidades= (int *)calloc(nObjetos+1,sizeof(int));
    printf("pase los callocs\n"); 
    int x;
    int y;
    int valor;
    gchar *str;
    for(y=0; y<nObjetos; y++){
        printf("vamos por el %d \n" ,y );
        valores[y]=atoi(gtk_entry_get_text(GTK_ENTRY(capacidades[0][y])));
        printf("EStos son los valores %s \n",gtk_entry_get_text (capacidades[0][y]));
        pesos[y]=atoi(gtk_entry_get_text(GTK_ENTRY(capacidades[1][y])));
        printf("EStos son los pesos %s \n",gtk_entry_get_text (capacidades[1][y]));
        
    }//end first for

     int **colores = (int **)calloc(nObjetos+1,sizeof(int *));
    for (i=0; i<nObjetos+1; i++)
         colores[i] = (int *)calloc(capacidadMochila+1,sizeof(int));


    int **resultado = (int **)calloc(nObjetos+1,sizeof(int *));
    for (i=0; i<nObjetos+1; i++)
         resultado[i] = (int *)calloc(capacidadMochila+1,sizeof(int));

     int **sub = (int **)calloc(nObjetos+1,sizeof(int *));
    for (i=0; i<nObjetos+1; i++)
         sub[i] = (int *)calloc(capacidadMochila+1,sizeof(int));

    buu=unboundedknapSack(capacidadMochila, pesos,valores, nObjetos,resultado,colores,sub);
    buu=knapSackBeamer(resultado,capacidadMochila, nObjetos, colores);
     system("evince --fullscreen knapSack.pdf");
}//fin convertirEntry

void ejecutarBoundedKnapsack(GtkWidget *object, gpointer user_data){
    convertirEntryBounded();

}

void ejecutarUnboundedKnapsack(GtkWidget *object, gpointer user_data){
    convertirEntryUnbounded();

}
void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

void generaCapacidadB(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *table;
    GtkWidget *createKnapsack;
    
    table = gtk_grid_new();
    capacidades= calloc(nObjetos+1,sizeof(GtkWidget));
    int i;
    for(i=0; i<nObjetos+1;i++)
        capacidades[i]=calloc(nObjetos,sizeof(GtkWidget));
    gtk_container_add (GTK_CONTAINER (SRWindowCapacity), table);
    int x;
    int y;
    for(x=0;x<4;x++){
       for(y=0; y<nObjetos+1;y++){
            GtkWidget *label;
            printf("x= %d y y=%d\n",x,y );
            if(x==0 && y==0){
                label=gtk_label_new ("Objetos");
                gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);
            }else{
                if(y==0){
                    if(x==1){
                        label=gtk_label_new("Valor");
                    }else if(x==2){
                        label=gtk_label_new("Peso");
                    }else if(x==3){
                        label=gtk_label_new("Cantidad");
                    }
                    
                    gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);                   
                }else if(x==0){
                    label=gtk_label_new(gtk_entry_get_text (objetos[y-1]));
                    gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);                   
                }else{
                    GtkWidget *entry;
                    entry = gtk_entry_new ();
                    gtk_grid_attach (GTK_GRID (table), entry, x, y, 1, 1);
                     printf("Almacenando en x= %d y y=%d\n",x,y);
                    capacidades[x-1][y-1]= entry;
                    printf("Almacenando en x-1= %d y y-1=%d\n",x-1,y-1 );

                }            

            }//fin if
        }// end primer for
    }//end for
     createKnapsack = gtk_button_new_with_label("Ejecutar algoritmo Bounded Knapsack");
    g_signal_connect (createKnapsack, "clicked", G_CALLBACK (ejecutarBoundedKnapsack), NULL);
    gtk_grid_attach (GTK_GRID (table), createKnapsack, 1, nObjetos+2, 1, 1);
    gtk_widget_show_all (window);
  
}

void generaCapacidadU(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *table;
    GtkWidget *createKnapsack;
    
    table = gtk_grid_new();
    capacidades= calloc(nObjetos+1,sizeof(GtkWidget));
    int i;
    for(i=0; i<nObjetos+1;i++)
        capacidades[i]=calloc(nObjetos+1,sizeof(GtkWidget));
    gtk_container_add (GTK_CONTAINER (SRWindowCapacity), table);
    int x;
    int y;
    for(x=0;x<3;x++){
       for(y=0; y<nObjetos+1;y++){
            GtkWidget *label;
            printf("x= %d y y=%d\n",x,y );
            if(x==0 && y==0){
                label=gtk_label_new ("Objetos");
                gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);
            }else{
                if(y==0){
                    if(x==1){
                        label=gtk_label_new("Valor");
                    }else if(x==2){
                        label=gtk_label_new("Peso");
                    }                    
                    
                    gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);                   
                }else if(x==0){
                    label=gtk_label_new(gtk_entry_get_text (objetos[y-1]));
                    gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);                   
                }else{
                    GtkWidget *entry;
                    entry = gtk_entry_new ();
                    gtk_grid_attach (GTK_GRID (table), entry, x, y, 1, 1);
                    printf("Almacenando en x= %d y y=%d\n",x,y);
                    capacidades[x-1][y-1]= entry;
                    printf("Almacenando en x-1= %d y y-1=%d\n",x-1,y-1);
                }            

            }//fin if
        }// end primer for
    }//end for
     createKnapsack = gtk_button_new_with_label("Ejecutar algoritmo Unbounded Knapsack");
    g_signal_connect (createKnapsack, "clicked", G_CALLBACK (ejecutarUnboundedKnapsack), NULL);
    gtk_grid_attach (GTK_GRID (table), createKnapsack, 1, nObjetos+2, 1, 1);
    gtk_widget_show_all (window);
    printf("Salgo de la funcion\n");
}



void showBounded(GtkWidget *widget, gpointer user_data)
{

    tipo=0;
    GtkWidget *table;
    GtkWidget *generaCapacidad;
    table = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (SRWindwObjs), table);
    gint cantObjs = gtk_spin_button_get_value_as_int (spinObjetos);
    nObjetos=cantObjs;
    gint capMochila=gtk_spin_button_get_value_as_int (spinCapacity);
    capacidadMochila=capMochila;

    objetos= calloc(cantObjs+1,sizeof(GtkWidget*));    
    g_print("Cantidad de objetos %d\n",cantObjs);
    
    int x;    
    for(x=0;x<cantObjs;x++){
        GtkWidget *objeto;
        objeto = gtk_entry_new ();
        objetos[x]= objeto;
        gtk_grid_attach (GTK_GRID (table), objeto, x, 0, 1, 1);      
        printf("X=%d\n",x );
    }//end for
    generaCapacidad = gtk_button_new_with_label("Generar capacidades.");
    g_signal_connect (generaCapacidad, "clicked", G_CALLBACK (generaCapacidadB), NULL);
    gtk_grid_attach (GTK_GRID (table), generaCapacidad, 0, 1, 1, 1);
    gtk_widget_show_all (window);
}

void showUnbounded(GtkWidget *widget, gpointer user_data)
{
    tipo=1;
    GtkWidget *table;
    GtkWidget *generaCapacidad;
    table = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (SRWindwObjs), table);
    gint cantObjs = gtk_spin_button_get_value_as_int (spinObjetos);
    nObjetos=cantObjs;
    gint capMochila=gtk_spin_button_get_value_as_int (spinCapacity);
    capacidadMochila=capMochila;

    objetos= calloc(cantObjs+1,sizeof(GtkWidget*));    
    int x;    
    for(x=0;x<cantObjs;x++){
        GtkWidget *objeto;
        objeto = gtk_entry_new ();
        objetos[x]= objeto;
        gtk_grid_attach (GTK_GRID (table), objeto, x, 0, 1, 1);      
        printf("X=%d\n",x );
    }//end for
    
    generaCapacidad = gtk_button_new_with_label("Generar capacidades.");
    g_signal_connect (generaCapacidad, "clicked", G_CALLBACK (generaCapacidadU), NULL);
    gtk_grid_attach (GTK_GRID (table), generaCapacidad, 0, 1, 1, 1);
    gtk_widget_show_all (window);
}


int main(int argc, char *argv[])
{
    
    GtkWidget *btnBounded;
    GtkWidget *btnUnbounded;
    gtk_init(&argc, &argv);    
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "Mochila.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "windowKnapsack"));
    gtk_widget_set_size_request(GTK_WINDOW(window),900,800);
    btnBounded = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnBounded"));
    btnUnbounded = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnUnbounded"));
    SRWindwObjs = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "SRWindwObjs"));
    gtk_widget_set_size_request(GTK_WINDOW(SRWindwObjs),70,70);
    SRWindowCapacity = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "SRWindowCapacity"));
    gtk_widget_set_size_request(GTK_WINDOW(SRWindowCapacity),200,200);
    spinObjetos= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinObjetos"));
    spinCapacity= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spinCapacity"));
    g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
    gtk_widget_set_tooltip_text (btnBounded, "Se crean los espacios necesarios para el algoritmo Bounded Knapsack. "); 
    gtk_widget_set_tooltip_text (btnUnbounded, "Se crean los espacios necesarios para el algoritmo Unbounded Knapsack. "); 
    g_signal_connect (btnBounded, "clicked",G_CALLBACK (showBounded),NULL);
    g_signal_connect (btnUnbounded, "clicked",G_CALLBACK (showUnbounded),NULL);
    
    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_widget_show(window);
    gtk_main();
    
    return 0;
}
