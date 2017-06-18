#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

static void ping (GtkWidget *widget, gpointer data);
char respuesta[54];

static void
ping (GtkWidget *widget,
      gpointer data)
{
	FILE * log;
	char dir[] ="./log.txt";
	log = fopen(dir,"w");

	system("ping -c 10 google.com");
	fscanf(stdout,"%s",respuesta);
	system("echo Terminado");
	printf("%s",respuesta);

	fclose(log);
	log = fopen (dir,"r");
	fscanf(log,"%s",respuesta);
	printf("%s",respuesta);
	
}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *grid;
  GtkWidget *output;
  
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Ping");
  gtk_container_set_border_width (GTK_CONTAINER (window),10);

  grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("Comprobar señal");
  g_signal_connect (button, "clicked",G_CALLBACK (ping),NULL);
  gtk_grid_attach (GTK_GRID (grid),button,1,0,1,1);
  
  output = gtk_label_new ("Pulse para continuar");
  gtk_grid_attach (GTK_GRID (grid),output,0,0,1,1);
  
  

  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;
  


  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
