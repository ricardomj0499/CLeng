#include <gtk/gtk.h>
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
			image = gtk_image_new_from_file("/home/ricardo/Desktop/tec/Lenguajes/C/CLeng/pacman1.png");
			gtk_layout_put(GTK_LAYOUT(layout), image, x, y);
            while(gtk_events_pending())
	            gtk_main_iteration();
            cooldown(1);
			x = x + 10;
			gtk_widget_show_all(window);
	} 

}

void redraw(){

}

int main( int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget *image2;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 464, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW(window), "PacMan");
    gtk_window_set_resizable (GTK_WINDOW(window),FALSE);

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window), layout);
    gtk_widget_show(layout);

    image = gtk_image_new_from_file("/home/ricardo/Desktop/tec/Lenguajes/C/CLeng/maze.jpg");
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

    g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    cooldown(2);
    image2 = gtk_image_new_from_file("/home/ricardo/Desktop/tec/Lenguajes/C/CLeng/pacman1.png");
    mover(10,layout,window,image2);
    gtk_main();

    return 0;
}

