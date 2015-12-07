#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include<string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operations.h"
#include "integral_image.h"
#include "haar_features.h"
#include "training.h"
#include "sdl_functions.h"
#include "adab.h"


//#include "database.h"
//include francois

struct photo{
  //  GtkWidget *window;
  GtkWidget *image;
};


struct photo *photo;
struct photo* init_photo(GtkWidget *image)
{
  photo = malloc(sizeof(struct photo));
  photo->image = image;
  // photo->window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
  return photo;
}

//struct photo photo;
//#include "database.h"
void quitter(GtkWidget *widget); void creer_file_selection();
void recuperer_chemin(GtkWidget *bouton,GtkWidget *file_selection);
void creer_file_selection_delete();
void recuperer_chemin_delete(GtkWidget *bouton,GtkWidget *file_selection);

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
GtkWidget *button2,*button1,*button3,*buttonq;
GtkWidget *pTable;
//GtkWidget *image;
GtkWidget *bouton_explorer;



//On initialise GTK
  gtk_init(&argc, &argv);

  // on initialise la struct photo
  photo=init_photo(gtk_image_new_from_file("./pictures/index.png")); 

//On initialise les Widgets
window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_default_size(GTK_WINDOW(window),800,600);
//image =gtk_image_new_from_file(argv[1]);

 g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

pTable = gtk_table_new(10,10,TRUE);


// on met bouton_explorer dans win
gtk_container_add(GTK_CONTAINER(window),GTK_WIDGET(pTable));

button2=gtk_button_new_with_mnemonic("Add");
button1=gtk_button_new_with_label("Browse");
button3=gtk_button_new_with_label("Begin");
buttonq=gtk_button_new_with_label("Quit");
//image =photo->image;

bouton_explorer=gtk_button_new_with_mnemonic("_Delete and more");
//gtk_container_add(GTK_CONTAINER(window),bouton_explorer);
//gtk_container_add(GTK_CONTAINER(window),button2);



 //positionnement des boutons
gtk_table_attach_defaults(GTK_TABLE(pTable),button1,3,4,1,2);
gtk_table_attach_defaults(GTK_TABLE(pTable),button2,0,3,1,2);
gtk_table_attach_defaults(GTK_TABLE(pTable),button3,0,2,7,9);
gtk_table_attach_defaults(GTK_TABLE(pTable),buttonq,9,10,9,10);
gtk_table_attach_defaults(GTK_TABLE(pTable),bouton_explorer,0,3,4,5);
gtk_table_attach_defaults(GTK_TABLE(pTable),photo->image,5,7,4,8);
// gtk_widget_set_size_request(GtkWidget(photo->image,200,300);
//gtk_fixed_put (GTK_FIXED (window), photo->image, 150, 150);

  
//On connecte le bouton à l'évenement «clicked»
// g_signal_connect(buttonq,"button-press-event",G_CALLBACK("quit"),(OnDestroy)window);
g_signal_connect(buttonq,"button-press-event",G_CALLBACK(gtk_main_quit),NULL);
//g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(creer_file_selection),NULL);
g_signal_connect(G_OBJECT(bouton_explorer), "clicked", G_CALLBACK(creer_file_selection_delete), NULL);

g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(creer_file_selection), NULL);


//On demande enfin à GTK de montrer notre Window et ce qu'elle contcient :
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
  //window = window;
  GtkWidget *selection;
     
  selection = gtk_file_selection_new( g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL) );
  gtk_widget_show(selection);
     
  //On interdit l'utilisation des autres fenêtres.
  gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
     
  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(recuperer_chemin), selection);
     
g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}

void creer_file_selection_delete()
{
  //window = window;                                                                                                                             
  GtkWidget *selection;

  selection = gtk_file_selection_new( g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL) );
  gtk_widget_show(selection);

  //On interdit l'utilisation des autres fenêtres.                                                                                               
  gtk_window_set_modal(GTK_WINDOW(selection), TRUE);

  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(recuperer_chemin_delete), selection);

  g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}



void recuperer_chemin_delete(GtkWidget *bouton,GtkWidget *file_selection)
{
 


 bouton = bouton;
 const gchar* chemin;
 GtkWidget *dialog;
 
  chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection));

  dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection),
  				  GTK_DIALOG_MODAL,
  				  GTK_MESSAGE_INFO,
  				  GTK_BUTTONS_OK,
  				  "Vous avez choisi :\n%s", chemin);
  //add(/*list*/,chemin);
  //gtk_image_set_from_file(GTK_IMAGE(photo->image),chemin);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  gtk_widget_destroy(file_selection);

 //RENVOYER CHEMIN A FRANCOIS
}


void recuperer_chemin(GtkWidget *bouton,GtkWidget *file_selection)
{



  bouton = bouton;
  const gchar* chemin;
  GtkWidget *dialog;
  GtkWidget *pEntry;
  const gchar *sNom;

  chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection));

  dialog = gtk_dialog_new_with_buttons("Saisie du nom",
				       GTK_WINDOW(file_selection),
				       GTK_DIALOG_MODAL,
				       GTK_STOCK_OK,GTK_RESPONSE_OK,
				       GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
				       NULL);
 
  /* Création de la zone de saisie */
  pEntry = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(pEntry), "Saisissez votre nom");
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), pEntry, TRUE, FALSE, 0);

  /* Affichage des éléments de la boite de dialogue */
  gtk_widget_show_all(GTK_DIALOG(dialog)->vbox);
 
  /* On lance la boite de dialogue et on récupéré la réponse */
  switch (gtk_dialog_run(GTK_DIALOG(dialog)))
    {
      /* L utilisateur valide */
    case GTK_RESPONSE_OK:
      sNom = gtk_entry_get_text(GTK_ENTRY(pEntry));
      //gtk_label_set_text(GTK_LABEL(pLabel), sNom);
      break;
      /* L utilisateur annule */
    case GTK_RESPONSE_CANCEL:
    case GTK_RESPONSE_NONE:
    default:
      //gtk_label_set_text(GTK_LABEL(pLabel), "Vous n'avez rien saisi !");
      sNom = "inconne";
      break;
    }

  FILE* cur= NULL;
  char buf[32]="";
  strcpy(buf,"data/");
  strcat(buf,(char*)sNom);
  cur = fopen(buf,"w+");
  if(cur)
    {
      fprintf(cur,"%s\n",(char*)chemin);
      fclose(cur);
    }
  
  facial_recognition(chemin);


  gtk_image_set_from_file(GTK_IMAGE(photo->image),chemin);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  gtk_widget_destroy(file_selection);

  //RENVOYER CHEMIN A FRANCOIS                                                                                                                    
}
