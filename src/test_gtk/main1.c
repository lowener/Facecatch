#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void quitter(GtkWidget *widget); void creer_file_selection();
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection);
//void Begin(GtkWidget* widget,gpointer data);
//void Delete(GtkWidget* widget, gpointer data);
void OnQuitter(GtkWidget* widget, gpointer data);
gboolean on_click_button (GtkWidget *button, GdkEventButton *event, gpointer data)
{
  button = button;
  event = event;
  data = data;
  printf("Hello World!" );
  // On redonne la main à GTK
  return FALSE;
}
int main (int argc,char **argv)
{
  //On déclare nos Widgets
GtkWidget *window;
GtkWidget *button,*button2,*button1,*button3,*buttonq;
GtkWidget *pTable;
GtkWidget *pParent;
GtkWidget *win;
GtkWidget *bouton_explorer;

//On initialise GTK
  gtk_init(&argc, &argv);

//On initialise les Widgets
window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_default_size(GTK_WINDOW(window),800,600);


g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

pTable = gtk_table_new(10,10,TRUE);


// On crée un bouton explorer
//bouton_explorer=gtk_button_new_with_mnemonic("_Explorer...");
// on met bouton_explorer dans win
//gtk_container_add(GTK_CONTAINER(window),bouton_explorer);


gtk_container_add(GTK_CONTAINER(window),GTK_WIDGET(pTable));
button=gtk_button_new_with_label("Delete");
button2=gtk_button_new_with_label("Add");
button1=gtk_button_new_with_label("Browse");
button3=gtk_button_new_with_label("Begin");
buttonq=gtk_button_new_with_label("Quit");
bouton_explorer=gtk_button_new_with_mnemonic("_Explorer...");
gtk_container_add(GTK_CONTAINER(window),bouton_explorer);

gtk_table_attach_defaults(GTK_TABLE(pTable),button,0,3,4,5);
gtk_table_attach_defaults(GTK_TABLE(pTable),button1,3,4,1,2);
gtk_table_attach_defaults(GTK_TABLE(pTable),button2,0,3,1,2);
gtk_table_attach_defaults(GTK_TABLE(pTable),button3,0,2,7,9);
gtk_table_attach_defaults(GTK_TABLE(pTable),buttonq,9,10,9,10);
gtk_table_attach_defaults(GTK_TABLE(pTable),bouton_explorer,5,6,6,7);

  
//On connecte le bouton à l'évenement «clicked»
 g_signal_connect(buttonq,"button-press-event",G_CALLBACK(OnQuitter),(GtkWidget*)window);
 //g_signal_connect(buttonq,"button-press-event",G_CALLBACK(Delete),(GtkWidget*)window);
 // g_signal_connect(button2,"button-press-event",G_CALLBACK(Begin),(GtkWidget*)window);
 g_signal_connect(G_OBJECT(bouton_explorer), "clicked", G_CALLBACK(creer_file_selection), NULL);


//On demande enfin à GTK de montrer notre Window et ce qu'elle contient :
gtk_widget_show_all(window);

//Puis on entre dans la boucle GTK qui garde la fenêtre ouvert
 gtk_main();
 return 0;
}

void OnQuitter(GtkWidget* widget, gpointer data)
{
  widget = widget;
  GtkWidget *pQuestion;
 
  pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
				     GTK_DIALOG_MODAL,
				     GTK_MESSAGE_QUESTION,
				     GTK_BUTTONS_YES_NO,
        "Voulez vous vraiment\n"
				     "quitter le programme?");
 
  switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
    case GTK_RESPONSE_YES:
      gtk_main_quit();
      break;
    case GTK_RESPONSE_NONE:
    case GTK_RESPONSE_NO:
      gtk_widget_destroy(pQuestion);
      break;
    }
    
}

void creer_file_selection()
{
  GtkWidget *selection;
     
  selection = gtk_file_selection_new( g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL) );
  gtk_widget_show(selection);
     
  //On interdit l'utilisation des autres fenêtres.
  gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
     
  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(recuperer_chemin), selection );
     
  g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}


void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection)
{
  const gchar* chemin;
  GtkWidget *dialog;
  chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );
     
  dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection),
				  GTK_DIALOG_MODAL,
				  GTK_MESSAGE_INFO,
				  GTK_BUTTONS_OK,
				  "Vous avez choisi :\n%s", chemin);
     
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  gtk_widget_destroy(file_selection);
}


//void destroy(GtkWidget* widget, gpointer data);
//void Delete(GtkWidget* widget, gpointer data);
//void Begin(GtkWidget* widget,gpointer data);
