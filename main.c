#include <gtk/gtk.h>
#include <limits.h> /* PATH_MAX */
#include <stdio.h>
#include <stdlib.h>

char buf1[PATH_MAX];
char buf[PATH_MAX];


void cooldown(float seconds)
{
    clock_t start = clock();
    clock_t period = seconds * CLOCKS_PER_SEC;
    clock_t elapsed;

    do {
        elapsed = clock() - start;
    } while(elapsed < period);
}


void mover(int cant, GtkWidget *layout,GtkWidget *window, GtkWidget *image2)
{
	GtkWidget *image;
	int y = 275;
	int x = 220;
	int a;
	for (a = 0; a < cant; a = a + 1){
<<<<<<< HEAD
			image = gtk_image_new_from_file(buf1);
			gtk_layout_put(GTK_LAYOUT(layout), image, x, y);
=======
			//image = gtk_image_new_from_file(buf1);
			gtk_layout_put(GTK_LAYOUT(layout), image2, x, y);
>>>>>>> origin/ronald
            while(gtk_events_pending())
	            gtk_main_iteration();
            cooldown(1);
			x = x + 10;
			gtk_widget_show_all(window);
	} 

}

<<<<<<< HEAD
void redraw(){

}

=======
void move(GtkWidget *image, int x, int y, float velocidad){
	GtkWidget *container;
	container = gtk_widget_get_parent(image);

}


gboolean my_keypress_function (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_space){
        printf("SPACE KEY PRESSED!");
        return TRUE;
    }
    return FALSE;
}

>>>>>>> origin/ronald
int main( int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *layout;
<<<<<<< HEAD
    GtkWidget *image;
    GtkWidget *image2;
    GtkWidget *button;

=======
    GtkWidget *canvas;
    GtkWidget *image;
    GtkWidget *image2;
    
>>>>>>> origin/ronald
    char *pacman1 = realpath("pacman1.png", buf1);
	char *maze = realpath("maze.jpg", buf);

    gtk_init(&argc, &argv);

<<<<<<< HEAD
=======
    //se inicia el window
>>>>>>> origin/ronald
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 464, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW(window), "PacMan");
    gtk_window_set_resizable (GTK_WINDOW(window),FALSE);

<<<<<<< HEAD
    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window), layout);
    gtk_widget_show(layout);

    image = gtk_image_new_from_file(buf);
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

    g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
=======
    //Se agregan eventos de teclado
    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    g_signal_connect (G_OBJECT(window), "key_press_event", G_CALLBACK(my_keypress_function), NULL);

    //se agrega layout para la imagen
    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window), layout);
    //gtk_widget_show(layout);

    //Se agrega la imagen
    image = gtk_image_new_from_file(buf);
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

    //se crea el area de dibujo
    // canvas = gtk_drawing_area_new();
    //gtk_container_add(GTK_CONTAINER(window), canvas);

    //g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

>>>>>>> origin/ronald
    gtk_widget_show_all(window);
    cooldown(2);
    image2 = gtk_image_new_from_file(buf1);
    mover(10,layout,window,image2);
    gtk_main();

    return 0;
}

