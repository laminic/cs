/*
 * =====================================================================================
 *
 *       Filename:  login.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/09/2013 09:04:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __LOGIN_H__
#define __LOGIN_H__
#include <gtk/gtk.h>
#include "user.h"
typedef struct  LOGIN_WIDGET {
	GtkEntry 	*userentry;
	GtkEntry 	*passentry;

	GtkWindow  *mainwindow;
	GtkWindow  *loginwindow;
}LOGIN_WIDGET;

void cb_login_button(GtkButton *button, gpointer data);
#endif
