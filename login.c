/*
 * =====================================================================================
 *
 *       Filename:  login.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/09/2013 09:04:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "login.h"
#include "user_mod.h"

extern USER cur_user;
USER cur_user;
LOGIN_WIDGET login_widget;

void init_login(GtkBuilder *login, GtkWindow *loginwin, GtkWindow *mainwin)
{
	login_widget.userentry = GTK_ENTRY(gtk_builder_get_object(login, "userentry"));
	login_widget.passentry = GTK_ENTRY(gtk_builder_get_object(login, "passentry"));
	login_widget.loginwindow = loginwin;
	login_widget.mainwindow = mainwin;	
}

void cb_login_button(GtkButton *button, gpointer data)
{
	LOGIN_WIDGET *login = &login_widget;
	const gchar *username = NULL;
	const gchar *password = NULL;

	username = gtk_entry_get_text(login->userentry);
	password = gtk_entry_get_text(login->passentry);
	if (!logincheck(username, password, &cur_user)) {
		gtk_widget_hide(GTK_WIDGET(login->loginwindow));
		gtk_widget_show(GTK_WIDGET(login->mainwindow));
	}
}
