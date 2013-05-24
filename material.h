/*
 * =====================================================================================
 *
 *       Filename:  material.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/30/2013 10:34:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <gtk/gtk.h>
typedef struct MATERIAL_COL {
	GtkCellRendererText *col_mid;
	GtkCellRendererText *col_mname;
	GtkCellRendererText *col_mtype;
	GtkCellRendererText *col_munit;
	GtkCellRendererText *col_mstock;
	GtkCellRendererText *col_mcomment;
}MATERIAL_COL;

typedef struct MATERIAL_WIDGET {
	GtkButton *m_new_btn;
	GtkButton *m_del_btn;
	GtkButton *m_save_btn;
	GtkEntry *m_search_entry;
	
	GtkTreeView *m_view;
	GtkListStore *m_store;

	MATERIAL_COL m_col;
}M_WIDGET;

typedef struct MATERIAL {
	gchar *mid;
	gchar *mname;
	gchar *mtype;
	gchar *munit;
	int   mstock;
	gchar *mcomment;
}MATERIAL;

typedef struct MATERIAL_IDENTITY {
	gchar *mid;
	gchar *mname;
}MATERIAL_IDENTITY;

enum {
	COLUMN_M_MID,
	COLUMN_M_MNAME,
	COLUMN_M_MTYPE,
	COLUMN_M_MUNIT,
	COLUMN_M_MSTOCK,
	COLUMN_M_MCOMMENT
};

void init_material(GtkBuilder *builder);
void cb_m_new_btn(GtkButton *button, gpointer data);
void cb_m_del_btn(GtkButton *button, gpointer data);
void cb_m_apy_btn(GtkButton *button, gpointer data);
void cb_toggle_button(GtkToggleButton *toggle_button);


#endif
