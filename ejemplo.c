#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glib.h>
const int Width = 1200, Height = 800;
char *buffer;

int i = 0;
GdkPixbuf *pixbuf;
GtkWidget *window;
GtkWidget* image;


void delay(int number_of_seconds){
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}


int main (int argc, char *argv[]){
    buffer = (char*)malloc(3 * Width * Height);

    // CREATE AN IMAGE IN BUFFER SOMEHOW
    // buffer = something; 
    // 

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    pixbuf = gdk_pixbuf_new_from_data (buffer, GDK_COLORSPACE_RGB, FALSE, 8, Width, Height, (Width)*3, NULL, NULL);
    image = gtk_image_new_from_pixbuf (pixbuf);
    gtk_container_add(GTK_CONTAINER (window), image);
    gtk_window_set_title (GTK_WINDOW (window), "Visualizador");
    gtk_widget_show_all (window);
    delay(0.04);
    gtk_main ();
    free (buffer);
    return 0;
}