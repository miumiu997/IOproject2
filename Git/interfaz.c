#include <gtk/gtk.h>

void executeFloyd(){
    system("gcc -Wall -g -o testFloyd Floyd/FloydInterfaz.c Floyd/logicaFloyd.c `pkg-config --cflags --libs gtk+-3.0`-w -lm");
    system("./testFloyd&");
   
}//end execute floyd

void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

void matricesFunc(GtkWidget *widget, gpointer user_data)
{    
    system("gcc -Wall -g -o testMatrices MultiplicacionMatrices/MatricesInterfaz.c MultiplicacionMatrices/logicaMatrices.c `pkg-config --cflags --libs gtk+-3.0`-w -lm ");
    system("./testMatrices");
}//end MatricesFunc

void mochilaFunc(){
    printf("Mochila Func\n");
    system("gcc -Wall -g -o testMochila Mochila/MochilaInterfaz.c Mochila/logicaMochila.c `pkg-config --cflags --libs gtk+-3.0`-w -lm");
    system("./testMochila&");
    
}//end MochilaFUnc

void seriesFunc(){
    printf("seriesFunc Func\n");
    //system("gcc -Wall -g -o testMochila Mochila/MochilaInterfaz.c Mochila/logicaMochila.c `pkg-config --cflags --libs gtk+-3.0`-w -lm");
    //system("./testMochila");
    
}//end MochilaFUnc

void executeArbolBin(){
    printf("Arbol BInario\n");
}
void reemplazoFunc(){
    printf("Reemplazo de equipos\n");
    system("gcc -Wall -g -o testReemplazo Reemplazo/ReemplazoInterfaz.c Reemplazo/logicaReemplazo.c  `pkg-config --cflags --libs gtk+-3.0`-w -lm");
    system("./testReemplazo&");
}
int main(int argc, char *argv[])
{
    GtkBuilder *gtkBuilder;
    GtkWidget *window;
    GtkWidget *itemSalir;
    GtkWidget *rutasMasCortas;
    GtkWidget *knapSack;
    GtkWidget *reemplazo;
    GtkWidget *matrices;
    GtkWidget *seriesEquipos;
    GtkWidget *arbolBin;


    gtk_init(&argc, &argv);
    
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "mainMenu.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "MENU_PRINCIPAL_ALGORITMOS"));
    itemSalir = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "itemSalir"));
    rutasMasCortas = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnFloyd"));
    knapSack = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnKnapsack"));
    reemplazo = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnReemplazo"));
    matrices = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnMatrices"));
    seriesEquipos= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnSeriesEquipos"));
    arbolBin= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnArboles")); 

    g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
    g_signal_connect (matrices, "clicked",G_CALLBACK (matricesFunc),NULL);
    g_signal_connect (knapSack, "clicked",G_CALLBACK (mochilaFunc),NULL);
    g_signal_connect (seriesEquipos, "clicked",G_CALLBACK (seriesFunc),NULL);
    g_signal_connect (rutasMasCortas, "clicked", G_CALLBACK (executeFloyd), NULL);    
    g_signal_connect (reemplazo, "clicked",G_CALLBACK (reemplazoFunc),NULL);
    g_signal_connect (arbolBin, "clicked", G_CALLBACK (executeArbolBin), NULL);

    gtk_widget_set_tooltip_text (rutasMasCortas, "Es un algoritmo de análisis sobre grafos para encontrar el camino mínimo en grafos dirigidos. ");  
    gtk_widget_set_tooltip_text (knapSack, "Es un problema de optimización combinatoria, busca la mejor solución entre un conjunto de posibles soluciones a un problema."); 
    gtk_widget_set_tooltip_text (reemplazo, "Es un algoritmo que busca minimizar el costo de reemplazos desde un instante especifico. "); 
    //g_signal_connect_object (itemSalir, "activate",G_CALLBACK (on_window_destroy), (gpointer),NULL);
	//itemSalir
    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_widget_show(window);
    gtk_main();
    
    return 0;
}