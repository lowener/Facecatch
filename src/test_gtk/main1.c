#include <stdlib.h>
#include <gtk/gtk.h>
 
void OnButton( gpointer data);
 
int main(int argc, char **argv)
{
  GtkWidget *pWindow;
  GtkWidget *pVBox;
  GtkWidget *pNotebook;
  GtkWidget *pButton;
  gint i;
 
  gtk_init(&argc,&argv);
 
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(pWindow), "GtkNotebook");
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
  g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 
  pVBox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
 
  pButton = gtk_button_new_with_label("Informations");
  gtk_box_pack_start(GTK_BOX(pVBox), pButton, FALSE, FALSE, 0);
 
  /* Creation du GtkNotebook */
  pNotebook = gtk_notebook_new();
  gtk_box_pack_start(GTK_BOX(pVBox), pNotebook, TRUE, TRUE, 0);
  /* Position des onglets : en bas */
  gtk_notebook_set_tab_pos(GTK_NOTEBOOK(pNotebook), GTK_POS_BOTTOM);
  /* Ajout des boutons de navigation */
  gtk_notebook_set_scrollable(GTK_NOTEBOOK(pNotebook), TRUE);
 
  for(i = 0 ; i < 3 ; ++i)
    {
      GtkWidget *pLabel;
      GtkWidget *pTabLabel;
      GtkWidget *pMenuLabel;
      gchar *sLabel;
      gchar *sTabLabel;
      gchar *sMenuLabel;
 
      sLabel = g_strdup_printf("Je suis le GtkLabel numero %d", i);
      sTabLabel = g_strdup_printf("Page %d", i);
      sMenuLabel = g_strdup_printf("Menu -> Page %d", i);
 
      /* Creation des differents GtkLabel */
      pLabel = gtk_label_new(sLabel);
      pTabLabel = gtk_label_new(sTabLabel);
      pMenuLabel = gtk_label_new(sMenuLabel);
 
      /* Insertion de la page */
      gtk_notebook_append_page_menu(GTK_NOTEBOOK(pNotebook), pLabel, pTabLabel, pMenuLabel);
 
      g_free(sLabel);
      g_free(sTabLabel);
      g_free(sMenuLabel);
    }
  /* Activation du menu popup */
  gtk_notebook_popup_enable(GTK_NOTEBOOK(pNotebook));
 
  g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnButton), pNotebook);
 
  gtk_widget_show_all(pWindow);
 
  gtk_main();
 
  return EXIT_SUCCESS;
}
 
void OnButton(gpointer data)
{
  GtkWidget *pDialog;
  GtkWidget *pChild;
  gint iPageNum;
  const gchar *sLabel;
  const gchar *sTabLabel;
  const gchar *sMenuLabel;
  gchar *sDialogText;
 
  /* Recuperation de la page active */
  iPageNum = gtk_notebook_get_current_page(GTK_NOTEBOOK(data));
  /* Recuperation du widget enfant */
  pChild = gtk_notebook_get_nth_page(GTK_NOTEBOOK(data), iPageNum);
 
  /* Recuperation du label */
  sLabel = gtk_label_get_text(GTK_LABEL(pChild));
  /* Recuperation du label de l'onglet */
  sTabLabel = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK(data), pChild);
  /* Recuperation du label du menu pop-up */
  sMenuLabel = gtk_notebook_get_menu_label_text(GTK_NOTEBOOK(data), pChild);
 
  /* Creation du label de la boite de dialogue */
  sDialogText = g_strdup_printf("C'est la page %d\n"
        "Le label est \"%s\"\n"
        "Le label de l'onglet est \"%s\"\n"
				"Le label du menu est \"%s\"\n",
				iPageNum,
				sLabel,
				sTabLabel,
				sMenuLabel);
 
  pDialog = gtk_message_dialog_new(NULL,
				   GTK_DIALOG_MODAL,
				   GTK_MESSAGE_INFO,
				   GTK_BUTTONS_OK,
				   sDialogText);
 
  gtk_dialog_run(GTK_DIALOG(pDialog));
 
  gtk_widget_destroy(pDialog);
 
  g_free(sDialogText);
}
