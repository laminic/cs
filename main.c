#include <stdlib.h>
#include <gtk/gtk.h>
#include <sqlite3.h>
#include "user.h"
#include "material.h"
#include "auth.h"
#include "login.h"
#include "init_db.h"


extern USER cur_user;
LOGIN_WIDGET login_widget;

int main (int argc, char *argv[])
{

	GtkBuilder *login;
	GtkBuilder *builder;

	GtkWidget  *loginwindow;
    GtkWidget  *window;

	GtkButton 	*loginbtn;


    gtk_init( &argc, &argv );

    /* Create builder */

	builder = gtk_builder_new();
    gtk_builder_add_from_file( builder, "ui.glade", NULL );
    window   = GTK_WIDGET( gtk_builder_get_object( builder, "window1" ) );

	login = gtk_builder_new();
	gtk_builder_add_from_file(login, "login.glade", NULL);
	loginwindow = GTK_WIDGET(gtk_builder_get_object(login, "loginwindow"));

	loginbtn = GTK_BUTTON(gtk_builder_get_object(login, "loginbtn"));
	g_signal_connect(loginbtn, "clicked", G_CALLBACK(cb_login_button), NULL);

	init_db();
	init_login(login, loginwindow, window);
	init_user(builder);
	init_material(builder);
	init_auth(builder);
	init_inout(builder);

    gtk_builder_connect_signals( login, NULL);
    g_object_unref( G_OBJECT( login) );

    gtk_builder_connect_signals( builder, NULL);
    g_object_unref( G_OBJECT( builder ) );


	gtk_widget_show(loginwindow);

    gtk_main();

    return( 0 );
}
