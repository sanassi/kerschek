#include <gtk/gtk.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


GtkWidget *window;
GtkWidget *binarisation;
GtkWidget *detection;
GtkWidget *results;



GtkWidget *fixed1;
GtkWidget *fixed2;
GtkWidget *load;
GtkWidget *frame1;
GtkWidget *load_button;
GtkWidget *image_plaque;

GtkWidget *car_brand;
GtkWidget *audi;
GtkWidget *bmw;
GtkWidget *renault;
GtkWidget *mercedesbenz;
GtkWidget *peugeot;
GtkWidget *citroen;

GtkWidget *title;
GtkWidget *logo;

GtkWidget *start_color;
GtkWidget *start;

GtkWidget *load2;

//Menu bar
GtkWidget *menu_bar;
GtkWidget *file_new;

GtkBuilder *builder;
GtkBuilder *start_detection;

void on_file_new_activate(GtkMenuItem *m)
{
  printf("File new activated");
}


void on_file_new_select(GtkMenuItem *m)
{
  printf("File new select");
}

void on_file_new_deselect(GtkMenuItem *m)
{
  printf("File new deselected");
}


void on_load_clicked(GtkButton *button)
{
  GtkWidget *Image_display;
  GtkWidget *dialog = NULL;

  dialog = gtk_file_chooser_dialog_new("Open a file", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

  if (gtk_dialog_run(GTK_DIALOG(dialog)) == (GTK_RESPONSE_ACCEPT))
   {
     printf("image ok");

     const gchar *file_name = NULL;
     file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

     Image_display = gtk_image_new_from_file(file_name);
     gtk_container_add(GTK_CONTAINER(fixed2), Image_display);
  
     gtk_widget_show(Image_display);
   }
  gtk_widget_destroy(dialog);
}

/*void on_start_dectection_clicked(GtkButton *button)
{
  GtkWidget *Image_display;

  //char command_start[50];
  //strcpy(command, "../platetoimg/display.c 
  }*/

int main(int argc, char *argv[])
{
  //init Gtk
  gtk_init(&argc, &argv);

  //contact with xml code
  builder = gtk_builder_new_from_file("interface.glade");

  //window
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  gtk_window_set_title(GTK_WINDOW(window), "Project Kerscheck");
  gtk_window_set_default_size(GTK_WINDOW(window),750,750);

  /*
  GdkColor color;
  color.red = 0xcccc;
  color.green = 0xcccc;
  color.blue = 0xd900;
  gtk_widget_modify_bg(GTK_WIDGET(window), GTK_STATE_NORMAL, &color);
  */
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_builder_connect_signals(builder, NULL);

  fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
  fixed2 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed2"));
  load = GTK_WIDGET(gtk_builder_get_object(builder, "load"));
  title = GTK_WIDGET(gtk_builder_get_object(builder, "title"));
  logo = GTK_WIDGET(gtk_builder_get_object(builder, "logo"));
  menu_bar = GTK_WIDGET(gtk_builder_get_object(builder, "menu_bar"));
  file_new = GTK_WIDGET(gtk_builder_get_object(builder, "file_new"));
  //frame1 = GTK_WIDGET(gtk_builder_get_object(builder, "frame1"));
  load_button = GTK_WIDGET(gtk_builder_get_object(builder, "load_button"));

  binarisation = GTK_WIDGET(gtk_builder_get_object(builder, "binarisation"));
  detection = GTK_WIDGET(gtk_builder_get_object(builder, "detection"));
  results = GTK_WIDGET(gtk_builder_get_object(builder, "results"));


  load2 = GTK_WIDGET(gtk_builder_get_object(builder, "load2"));

  image_plaque = GTK_WIDGET(gtk_builder_get_object(builder, "image_plaque"));

  start_color = GTK_WIDGET(gtk_builder_get_object(builder, "start_color"));
  start_detection = GTK_WIDGET(gtk_builder_get_object(builder, "start_detection"));

   
  car_brand = GTK_WIDGET(gtk_builder_get_object(builder, "car_brand"));
  peugeot = GTK_WIDGET(gtk_builder_get_object(builder, "peugeot"));
  audi = GTK_WIDGET(gtk_builder_get_object(builder, "audi"));
  bmw = GTK_WIDGET(gtk_builder_get_object(builder, "bmw"));
  renault = GTK_WIDGET(gtk_builder_get_object(builder, "renault"));
  citroen = GTK_WIDGET(gtk_builder_get_object(builder, "citroen"));
  mercedesbenz = GTK_WIDGET(gtk_builder_get_object(builder, "mercedesbenz"));
  
  //g_signal_connect(G_OBJECT(load), "clicked", G_CALLBACK(on_load_clicked), window);
  //g_signal_connect(load, "clicked", G_CALLBACK(on_load_clicked), NULL);
  
  gtk_widget_show(window);


  gtk_main();

  return 0;
}
    
