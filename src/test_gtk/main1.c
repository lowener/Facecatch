#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>


gboolean on_click_button (GtkWidget *button, GdkEventButton *event, gpointer data)
{
printf("Hello World!" );
// On redonne la main à GTK
    return FALSE;
}
int main (int argc,char**argv)
{
  //On déclare nos Widgets
GtkWidget *window;
GtkWidget *vbox;
GtkWidget *button,*button2;
GtkWidget *label;
GtkWidget *entry;
 GtkWidget *pTable;
 // GtkWidget *pButton[2];

//On initialise GTK
gtk_init(&argc,&argv);

//On initialise les Widgets
window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
 gtk_window_set_default_size(GTK_WINDOW(window),800,600);
vbox=gtk_vbox_new(TRUE,10);

 pTable = gtk_table_new(1,2,TRUE);
 gtk_container_add(GTK_CONTAINER(window),GTK_WIDGET(pTable));

button=gtk_button_new_with_label("C'est un Boutton!");
label=gtk_label_new("C'est un Label!");
button2=gtk_button_new_with_label("Bouton2!");
entry=gtk_entry_new();

 gtk_table_attach_defaults(GTK_TABLE(pTable),button,0,1,1,2);
 gtk_table_attach_defaults(GTK_TABLE(pTable),button2,0,2,2,3);


//Tout d'abord, on met la GtkHBox dans la GtkWindow :
gtk_container_add(GTK_CONTAINER(window),vbox);

//Puis on met les Widgets dans la GtkHBox:
gtk_box_pack_start(GTK_BOX(vbox),entry,TRUE,TRUE,0);
//gtk_box_pack_start(GTK_BOX(vbox),button,TRUE,TRUE,0);
//gtk_box_pack_start(GTK_BOX(vbox),button2,TRUE,TRUE,0);
gtk_box_pack_start(GTK_BOX(vbox),label,TRUE,TRUE,0);

//On connecte le bouton à l'évenement «clicked»
g_signal_connect(button,"button-press-event",(GCallback)on_click_button,NULL);
 g_signal_connect(button2,"button-press-event",(GCallback)on_click_button,NULL);

//On demande enfin à GTK de montrer notre Window et ce qu'elle contient :
gtk_widget_show_all(window);

//Puis on entre dans la boucle GTK qui garde la fenêtre ouvert
 gtk_main();
 return 0;
}
