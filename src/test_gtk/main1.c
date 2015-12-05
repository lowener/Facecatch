#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>


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
int main (int argc,char**argv)
{
  //On déclare nos Widgets
GtkWidget *window;
GtkWidget *vbox;
GtkWidget *button,*button2,*button1,*button3,*buttonq;
GtkWidget *label;
GtkWidget *entry;
GtkWidget *pTable;
//guint rows = 5;
//guint columns = 5;
 // GtkWidget *pButton[2];

//On initialise GTK
gtk_init(&argc,&argv);

//On initialise les Widgets
window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
 gtk_window_set_default_size(GTK_WINDOW(window),800,600);
vbox=gtk_vbox_new(TRUE,10);

 pTable = gtk_table_new(10,10,TRUE);
 gtk_container_add(GTK_CONTAINER(window),GTK_WIDGET(pTable));

button=gtk_button_new_with_label("Delete");
label=gtk_label_new("C'est un Label!");
button2=gtk_button_new_with_label("Add");
button1=gtk_button_new_with_label("Browse");
button3=gtk_button_new_with_label("Begin");
buttonq=gtk_button_new_with_label("Quit");

entry=gtk_entry_new();
//void gtk_table_resize(GTK_TABLE(pTable),rows, columns);
 gtk_table_attach_defaults(GTK_TABLE(pTable),button,0,3,4,5);
 gtk_table_attach_defaults(GTK_TABLE(pTable),button1,3,4,1,2);
 gtk_table_attach_defaults(GTK_TABLE(pTable),button2,0,3,1,2);
 gtk_table_attach_defaults(GTK_TABLE(pTable),button3,0,2,7,9);
 gtk_table_attach_defaults(GTK_TABLE(pTable),buttonq,9,10,9,10);


//Tout d'abord, on met la GtkHBox dans la GtkWindow :
gtk_container_add(GTK_CONTAINER(window),vbox);

//Puis on met les Widgets dans la GtkHBox:
gtk_box_pack_start(GTK_BOX(vbox),entry,TRUE,TRUE,0);
//gtk_box_pack_start(GTK_BOX(vbox),button,TRUE,TRUE,0);
//gtk_box_pack_start(GTK_BOX(vbox),button2,TRUE,TRUE,0);
gtk_box_pack_start(GTK_BOX(vbox),label,TRUE,TRUE,0);

//On connecte le bouton à l'évenement «clicked»
 g_signal_connect(buttonq,"button-press-event",G_CALLBACK(OnQuitter),(GtkWidget*)window);
 // g_signal_connect(button2,"button-press-event",(GCallback)on_click_button,NULL);

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
