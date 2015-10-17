#include <gtk/gtk.h>

void executeFloyd(){

}
void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

void button_clicked(GtkWidget *widget, gpointer data) {
    
  g_print("clicked\n");
}

int main(int argc, char *argv[])
{
    GtkBuilder *gtkBuilder;
    GtkWidget *window;
    GtkWidget *itemSalir;
    GtkWidget *rutasMasCortas;
    GtkWidget *knapSack;
    GtkWidget *reemplazo;



    gtk_init(&argc, &argv);
    
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "mainMenu.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "MENU_PRINCIPAL_ALGORITMOS"));
    itemSalir = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "itemSalir"));
    rutasMasCortas = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnFloyd"));
    knapSack = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnKnapsack"));
    reemplazo = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnReemplazo"));
    g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
    //g_signal_connect (G_OBJECT(itemSalir), "activate", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (rutasMasCortas, "clicked", G_CALLBACK (executeFloyd), NULL);
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