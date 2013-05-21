/*
 * =====================================================================================
 *
 *       Filename:  user.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/19/2013 03:31:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __USER_H__
#define __USER_H__

#include <gtk/gtk.h>


typedef struct USER_COL {
	GtkCellRendererText *col_user_id;
	GtkCellRendererText *col_user_name;
	GtkCellRendererText *col_user_age;
	GtkCellRendererText *col_user_birth;
	GtkCellRendererText *col_user_idcard;
	GtkCellRendererText *col_user_place;
	GtkCellRendererText *col_user_address;
	GtkCellRendererText *col_user_phone;
	GtkCellRendererText *col_user_other;
}USER_COL;


typedef struct USER_WIDGET {
	GtkButton *new_user_button;
	GtkButton *del_user_button;
	GtkButton *apply_user_button;
	GtkCheckButton *edit_user_button;
	GtkEntry *user_search_entry;

	GtkTreeView *user_view;
	GtkListStore *user_store;

	USER_COL user_col;

}USER_WIDGET;

typedef struct USER {

	gchar* uid;
	gchar* name;
	gchar* age;
	gchar* birth;
	gchar* idcard;
	gchar* place;
	gchar* address;
	gchar* phone;
	gchar* other;
	gint  authority;
	gchar* passwd;
}USER;

enum {
	COLUMN_USER_UID,
	COLUMN_USER_NAME,
	COLUMN_USER_AGE,
	COLUMN_USER_BIRTH,
	COLUMN_USER_IDCARD,
	COLUMN_USER_PLACE,
	COLUMN_USER_ADDRESS,
	COLUMN_USER_PHONE,
	COLUMN_USER_OTHER,
	COLUMN_USER_AUTHORITY,
	COLUMN_USER_USER,
	COLUMN_USER_PASS,
	NUM_COLUMN_USER 
};

void add_user_model(GtkTreeModel* model, USER *user);
void remove_user_model(GtkTreeModel* model, GtkTreeIter *iter);

void cb_newuserbutton(GtkButton *button, gpointer user_data);
void cb_deluserbutton(GtkButton *button, gpointer user_data);
#endif
