#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>


/* Récupère le nom de fichier sélectionné et l'affiche sur la console. */
 
void file_ok_sel (GtkWidget *w, GtkFileSelection *fs)
{
  g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
}
 
void destroy (GtkWidget *widget, gpointer *data)
{
  gtk_main_quit ();
}

int main (int argc, char *argv[])
{
  GtkWidget *filew;
     
  gtk_init (&argc, &argv);
     
  /* Création d'un widget de sélection de fichier. */
 
  filew = gtk_file_selection_new ("File selection");
     
  gtk_signal_connect (GTK_OBJECT (filew), "destroy",
		      (GtkSignalFunc) destroy, &filew);
 
  /* Connexion de ok_button à la fonction file_ok_sel() */
 
  gtk_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
		      "clicked", (GtkSignalFunc) file_ok_sel, filew );
    
  /* Connexion de cancel_button pour détruire le widget */
 
  gtk_signal_connect_object (GTK_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),
			     "clicked", (GtkSignalFunc) gtk_widget_destroy,
			     GTK_OBJECT (filew));
    
  /* Configuration du nom de fichier, comme s'il s'agissait d'un dialogue de
   * sauvegarde et que nous donnions un nom de fichier par défaut. */
 
  gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), 
				   "penguin.png");
    
  gtk_widget_show(filew);
  gtk_main ();
  return 0;
}
