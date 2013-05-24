/*
 * =====================================================================================
 *
 *       Filename:  inout.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/22/2013 01:31:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "user_mod.h"

static GtkButton 	*create_btn;
static GtkButton 	*add_btn;
static GtkButton 	*del_btn;
static GtkButton 	*commit_btn;
static GtkEntry 	*indate_ety;
static GtkEntry 	*ioid_ety;
static GtkEntry 	*comm_ety;
static GtkComboBox 	*user_combo;

static GtkCellRendererText *io_m_id_txt;
static GtkCellRendererText *io_m_num_txt;
static GtkCellRendererText *io_m_flag_txt;
static GtkCellRendererText *io_m_comm_txt;

void init_inout(GtkBuilder *builder)
{
	create_btn = GTK_BUTTON(gtk_builder_get_object(builder, "create_btn"));
	add_btn = GTK_BUTTON(gtk_builder_get_object(builder, "add_btn"));
	del_btn = GTK_BUTTON(gtk_builder_get_object(builder, "del_btn"));
	commit_btn = GTK_BUTTON(gtk_builder_get_object(builder, "commit_btn"));

	indate_ety = GTK_ENTRY(gtk_builder_get_object(builder, "indate_ety"));
	ioid_ety   = GTK_ENTRY(gtk_builder_get_object(builder, "ioid_ety"));
	comm_ety   = GTK_ENTRY(gtk_builder_get_object(builder, "comm_ety"));

	io_m_id_txt = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder, "io_m_id"));	
	io_m_num_txt = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder, "io_m_num"));	
	io_m_flag_txt = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder, "io_m_flag"));	
	io_m_comm_txt = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder, "io_m_comm"));	
	
	g_object_set_data(G_OBJECT(io_m_id_txt), "column", GINT_TO_POINTER(0));
	g_object_set_data(G_OBJECT(io_m_num_txt), "column", GINT_TO_POINTER(1));
	g_object_set_data(G_OBJECT(io_m_flag_txt), "column", GINT_TO_POINTER(2));
	g_object_set_data(G_OBJECT(io_m_comm_txt), "column", GINT_TO_POINTER(3));

}

/* get_user_list(GSList *user_list) */

static void __add_user_model__(GtkTreeModel *model, IDENTITY_USER *data)
{
	GtkTreeIter iter;
	
	gtk_list_store_append(GTK_LIST_STORE(model), &iter);
	gtk_list_store_set(GTK_LIST_STORE(model), &iter,
			0, data->uid,
			1, data->name,
			-1);
}

void cb_combo_click(GtkComboBox *widget, gpointer data)
{
	GtkTreeModel *model = gtk_combo_box_get_model(widget);
	GSList *user_list = NULL;
	GSList *iterator;

	g_object_ref(model);
	gtk_combo_box_set_model(widget, NULL);
	gtk_list_store_clear(GTK_LIST_STORE(model));

	get_user_list(&user_list);

	for (iterator = user_list; iterator; iterator = iterator->next) {
		__add_user_model__(model, iterator->data);
	}
	gtk_combo_box_set_model(widget, model);
	g_object_unref(model);

	if (user_list != NULL) {
		g_slist_free(user_list);
		user_list = NULL;
	}
}

void cb_io_cell_edited(GtkCellRendererText *cell, const gchar *path_string,
					const gchar *new_text, gpointer data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(data);
	GtkTreePath  *path  = gtk_tree_path_new_from_string(path_string);
	GtkTreeIter   iter;
	
	gint column = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(cell), "column"));
	gtk_tree_model_get_iter(model, &iter, path);
	
	gtk_list_store_set(GTK_LIST_STORE(model), &iter, column, new_text, -1);
}
