/*
 * =====================================================================================
 *
 *       Filename:  material.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/30/2013 10:34:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include "material.h"
#include "material_mod.h"
#include "common.h"

//#define g_memset(s, ch, n) memset(s, ch, n)
#define g_memset(s, ch, n)

static GSList *m_ins_list = NULL;
static GSList *m_del_list = NULL;
static GSList *m_upt_list = NULL;
static GSList *m_sel_list = NULL;
static  M_WIDGET m_widget;

static void __fill_material_iter__(GtkTreeModel *model, GtkTreeIter *iter, MATERIAL *material);
static void __copy_iter_to_model__(GtkTreeModel *model, MATERIAL *mater);

static gchar* __generator_m_id__();

void init_material(GtkBuilder *builder)
{
	m_widget.m_new_btn = GTK_BUTTON(gtk_builder_get_object(builder, "m_new_btn"));
	m_widget.m_save_btn = GTK_BUTTON(gtk_builder_get_object(builder, "m_save_btn"));
	m_widget.m_del_btn = GTK_BUTTON(gtk_builder_get_object(builder, "m_del_btn"));
	m_widget.m_search_entry = GTK_ENTRY(gtk_builder_get_object(builder, "m_search_entry"));
	m_widget.m_view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "materialview"));
	m_widget.m_store = GTK_LIST_STORE(gtk_builder_get_object(builder, "materialstore"));

	m_widget.m_col.col_mid = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
													"col_mid"));
	m_widget.m_col.col_mname = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
													"col_mname"));
	m_widget.m_col.col_mtype = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
													"col_mtype"));
	m_widget.m_col.col_munit = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
													"col_munit"));
	m_widget.m_col.col_mstock = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
													"col_mstock"));
	m_widget.m_col.col_mcomment = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
													"col_mcomment"));

	g_object_set_data(G_OBJECT(m_widget.m_col.col_mid), "column",
							GINT_TO_POINTER(COLUMN_M_MID));
	g_object_set_data(G_OBJECT(m_widget.m_col.col_mname), "column",
							GINT_TO_POINTER(COLUMN_M_MNAME));
	g_object_set_data(G_OBJECT(m_widget.m_col.col_mtype), "column",
							GINT_TO_POINTER(COLUMN_M_MTYPE));
	g_object_set_data(G_OBJECT(m_widget.m_col.col_munit), "column",
							GINT_TO_POINTER(COLUMN_M_MUNIT));
	g_object_set_data(G_OBJECT(m_widget.m_col.col_mstock), "column",
							GINT_TO_POINTER(COLUMN_M_MSTOCK));
	g_object_set_data(G_OBJECT(m_widget.m_col.col_mcomment), "column",
							GINT_TO_POINTER(COLUMN_M_MCOMMENT));

	SQL_init_material();
}
void cb_toggle_button(GtkToggleButton *toggle_button)
{
	gboolean flag = gtk_toggle_button_get_active(toggle_button);

	g_object_set(m_widget.m_col.col_mname, "editable", flag, NULL);
	g_object_set(m_widget.m_col.col_mtype, "editable", flag, NULL);
	g_object_set(m_widget.m_col.col_munit, "editable", flag, NULL);
	g_object_set(m_widget.m_col.col_mstock, "editable", flag, NULL);
	g_object_set(m_widget.m_col.col_mcomment, "editable", flag, NULL);

	gtk_widget_set_visible(GTK_WIDGET(m_widget.m_new_btn), flag);
	gtk_widget_set_visible(GTK_WIDGET(m_widget.m_del_btn), flag);
	gtk_widget_set_visible(GTK_WIDGET(m_widget.m_save_btn), flag);
}
void cb_m_new_btn(GtkButton *button, gpointer data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(data);
	GtkTreeIter iter;
	
	GtkTreePath *path;
	GtkTreeRowReference *keep_iter;

	gtk_list_store_append(GTK_LIST_STORE(model), &iter);
	gtk_list_store_set(GTK_LIST_STORE(model), &iter,
			COLUMN_M_MID, __generator_m_id__(),
			COLUMN_M_MNAME, "xxxxx",
			-1);
	path = gtk_tree_model_get_path(model, &iter);
	keep_iter = gtk_tree_row_reference_new(model, path);

	m_ins_list = g_slist_prepend(m_ins_list, keep_iter);

	gtk_tree_path_free(path);
}

void cb_m_del_btn(GtkButton *button, gpointer data)
{
	GtkTreeView *view = GTK_TREE_VIEW(data);
	GtkTreeModel *model = gtk_tree_view_get_model(view);
	GtkTreeIter iter;
	GtkTreeSelection *selection;

	selection = gtk_tree_view_get_selection(view);
	if (gtk_tree_selection_get_selected(selection, NULL, &iter)) {

		gchar *mid;
		gtk_tree_model_get(model, &iter, COLUMN_M_MID, &mid, -1);
		m_del_list = g_slist_append(m_del_list, mid);

		gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
	}
}

void cb_m_upt_cell(GtkCellRendererText *cell, gchar *path_string, const gchar *new_text, gpointer data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(data);
	GtkTreeIter iter;
	GtkTreePath *path;
	GtkTreeRowReference *keep_iter;

	GSList *iterator;
	gint column;
	gboolean in = FALSE;

	path = gtk_tree_path_new_from_string(path_string);
	gtk_tree_model_get_iter(model, &iter, path);

	column = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(cell), "column"));
	switch (column) {
		case COLUMN_M_MSTOCK:
			{
				int i = atoi(new_text);
				gtk_list_store_set(GTK_LIST_STORE(model), &iter, column, i, -1);
			}
			break;
		default:
			{
				gtk_list_store_set(GTK_LIST_STORE(model), &iter, column, (new_text),-1);
			}

	}

	keep_iter = gtk_tree_row_reference_new(model, path);

	for (iterator = m_upt_list; iterator; iterator = iterator->next) {
		if (keep_iter == iterator->data) {
			in = TRUE;
			break;
		}
	}
	gtk_tree_path_free(path);

	if (!in) {
		m_upt_list = g_slist_append(m_upt_list, keep_iter);
	}
}

void cb_m_apy_btn(GtkButton *button, gpointer data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(data);
	GtkTreeIter iter;
	GtkTreePath *path;
	MATERIAL material;
	GSList *iterator;

	for (iterator = m_ins_list; iterator; iterator = iterator->next) {

		path = gtk_tree_row_reference_get_path(iterator->data);
		if (path == NULL)
			continue;

		gtk_tree_model_get_iter(model, &iter, path);
		
		 __fill_material_iter__(model, &iter, &material);
	
		SQL_ins_material(&material);
		g_memset(&material, 0, sizeof(material));
		gtk_tree_path_free(path);
		gtk_tree_row_reference_free(iterator->data);
	}

	for (iterator = m_upt_list; iterator; iterator = iterator->next) {
		
		path = gtk_tree_row_reference_get_path(iterator->data);
		if (path == NULL)
			continue;

		gtk_tree_model_get_iter(model, &iter, path);
		__fill_material_iter__(model, &iter, &material);
		SQL_upt_material(&material);
		g_memset(&material, 0, sizeof(material));
		gtk_tree_path_free(path);
		gtk_tree_row_reference_free(iterator->data);
	}
	
	for (iterator = m_del_list; iterator; iterator = iterator->next) {
		material.mid = iterator->data;
		SQL_del_material(&material);
		g_free(material.mid);
		g_memset(&material, 0 ,sizeof(material));
	}
	
	if (m_ins_list != NULL) {
		g_slist_free(m_ins_list);
		m_ins_list = NULL;
	}
	if (m_del_list != NULL) {
		g_slist_free(m_del_list);
		m_del_list = NULL;
	}
	if (m_upt_list != NULL) {
		g_slist_free(m_upt_list);
		m_upt_list = NULL;
	}
}

void cb_search_entry(GtkEntry *entry, gpointer data)
{
	GtkTreeView *view = GTK_TREE_VIEW(data);
	GtkTreeModel *model;
	GSList *iterator;
	MATERIAL *mat;
	const gchar *filter;

	model = gtk_tree_view_get_model(view);
	filter = gtk_entry_get_text(entry);

	g_object_ref(model);
	gtk_tree_view_set_model(view, NULL);

	gtk_list_store_clear(GTK_LIST_STORE(model));

	if (m_sel_list != NULL) {
		g_slist_free(m_sel_list);
		m_sel_list = NULL;
	}

	SQL_select_material(filter, &m_sel_list);
	for (iterator = m_sel_list; iterator; iterator = iterator->next) {
		mat = iterator->data;
		__copy_iter_to_model__(model, mat);
	}

	gtk_tree_view_set_model(view, model);
	g_object_unref(model);
}

void __copy_iter_to_model__(GtkTreeModel *model, MATERIAL *mater)
{
	GtkTreeIter iter;
	g_return_if_fail(mater!=NULL);
	gtk_list_store_append(GTK_LIST_STORE(model), &iter);
	gtk_list_store_set(GTK_LIST_STORE(model), &iter,
			COLUMN_M_MID, mater->mid,
			COLUMN_M_MNAME, mater->mname,
			COLUMN_M_MTYPE, mater->mtype,
			COLUMN_M_MUNIT, mater->munit,
			COLUMN_M_MSTOCK, mater->mstock,
			COLUMN_M_MCOMMENT, mater->mcomment,
			-1);
}

void __fill_material_iter__(GtkTreeModel *model, GtkTreeIter *iter, MATERIAL *material)
{
	gtk_tree_model_get(model, iter, COLUMN_M_MID,  &(material->mid), -1);
	gtk_tree_model_get(model, iter, COLUMN_M_MNAME, &(material->mname), -1);
	gtk_tree_model_get(model, iter, COLUMN_M_MTYPE, &(material->mtype), -1);
	gtk_tree_model_get(model, iter, COLUMN_M_MUNIT, &(material->munit), -1);
	gtk_tree_model_get(model, iter, COLUMN_M_MSTOCK, &(material->mstock), -1);
	gtk_tree_model_get(model, iter, COLUMN_M_MCOMMENT, &(material->mcomment), -1);
}

static gchar* __generator_m_id__()
{

	return "xxx";
}
