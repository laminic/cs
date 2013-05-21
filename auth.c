/*
 * =====================================================================================
 *
 *       Filename:  auth.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/09/2013 07:02:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "auth.h"


static GSList *ins_list = NULL;
static GSList *del_list = NULL;
static GSList *upt_list = NULL;
static GSList *sel_list = NULL;

extern USER cur_user;

static AUTH_WIDGET auth_widget;

gchar *authinfo[] = {"只能查看", "全部权限", "禁止所有"};

void init_auth(GtkBuilder *builder)
{
	auth_widget.auth_user_search =  GTK_ENTRY(gtk_builder_get_object(builder, "auth_entry"));

	auth_widget.auth_col.auth_id = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
															"auth_id"));
	auth_widget.auth_col.auth_name = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
															"auth_name"));
	auth_widget.auth_col.auth_u = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
															"auth_u"));
	auth_widget.auth_col.auth_m = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
															"auth_m"));
	auth_widget.auth_col.auth_o = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
															"auth_o"));
	auth_widget.auth_col.auth_a = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
															"auth_a"));
	auth_widget.auth_col.auth_t = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(builder,
															"auth_t"));

	g_object_set_data(G_OBJECT(auth_widget.auth_col.auth_u), "column",
						GINT_TO_POINTER(COLUMN_AUTH_U));
	g_object_set_data(G_OBJECT(auth_widget.auth_col.auth_m), "column",
						GINT_TO_POINTER(COLUMN_AUTH_M));
	g_object_set_data(G_OBJECT(auth_widget.auth_col.auth_o), "column",
						GINT_TO_POINTER(COLUMN_AUTH_O));
	g_object_set_data(G_OBJECT(auth_widget.auth_col.auth_a), "column",
						GINT_TO_POINTER(COLUMN_AUTH_A));
	g_object_set_data(G_OBJECT(auth_widget.auth_col.auth_t), "column",
						GINT_TO_POINTER(COLUMN_AUTH_T));

	auth_widget.u_box = GTK_BOX(gtk_builder_get_object(builder, "u_box"));
	auth_widget.m_box = GTK_BOX(gtk_builder_get_object(builder, "m_box"));
	auth_widget.o_box = GTK_BOX(gtk_builder_get_object(builder, "o_box"));
	auth_widget.a_box = GTK_BOX(gtk_builder_get_object(builder, "a_box"));
	auth_widget.t_box = GTK_BOX(gtk_builder_get_object(builder, "t_box"));

	auth_widget.edit_u = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_u"));
	auth_widget.edit_m = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_m"));
	auth_widget.edit_a = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_a"));

	auth_widget.applybtn = GTK_BUTTON(gtk_builder_get_object(builder, "auth_btn"));
	auth_widget.checkbtn = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "c_btn"));

	auth_widget.s_u = GTK_LABEL(gtk_builder_get_object(builder, "show_u"));
}

void cb_editable_checkbtn(GtkToggleButton *button, gpointer data)
{
	gboolean flag = gtk_toggle_button_get_active(button);

	g_object_set(auth_widget.auth_col.auth_u, "editable", flag, NULL);
	g_object_set(auth_widget.auth_col.auth_m, "editable", flag, NULL);
	g_object_set(auth_widget.auth_col.auth_o, "editable", flag, NULL);
	g_object_set(auth_widget.auth_col.auth_a, "editable", flag, NULL);
	g_object_set(auth_widget.auth_col.auth_t, "editable", flag, NULL);

	gtk_widget_set_visible(GTK_WIDGET(auth_widget.applybtn), flag);
}


void cb_authentry(GtkEntry *entry, gpointer data)
{
	GtkTreeView *treeview = GTK_TREE_VIEW(data);
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	GtkTreeIter iter;
	GSList *iterator;
	USER *user;	
	const gchar *select_filter;

	gchar *u_auth_val = authinfo[2];
	gchar *m_auth_val = authinfo[2];
	gchar *o_auth_val = authinfo[2];
	gchar *a_auth_val = authinfo[2];
	gchar *t_auth_val = authinfo[2];

	select_filter = gtk_entry_get_text(entry);

	select_user(select_filter, &sel_list);

	g_object_ref(model);
	gtk_tree_view_set_model(treeview, NULL);
	gtk_list_store_clear(GTK_LIST_STORE(model));
	
	/* USER 实体在什么地方释放？我没有释放,model清除会不会自动释放实体 */
	for (iterator=sel_list; iterator; iterator= iterator->next) {
		user = iterator->data;
		g_return_if_fail(user!=NULL);

		if ((user->authority & U_S_AUTH) == U_S_AUTH)
			u_auth_val = authinfo[0];
		if ((user->authority & U_U_AUTH) == U_U_AUTH)
			u_auth_val = authinfo[1];
		if ((user->authority & U_N_AUTH) == U_N_AUTH)
			u_auth_val = authinfo[2];

		if ((user->authority & M_S_AUTH) == M_S_AUTH)
			m_auth_val = authinfo[0];
		if ((user->authority & M_U_AUTH) == M_U_AUTH)
			m_auth_val = authinfo[1];
		if ((user->authority & M_N_AUTH) == M_N_AUTH)
			m_auth_val = authinfo[2];

		if ((user->authority & O_S_AUTH) == O_S_AUTH)
			o_auth_val = authinfo[0];
		if ((user->authority & O_U_AUTH) == O_U_AUTH)
			o_auth_val = authinfo[1];
		if ((user->authority & O_N_AUTH) == O_N_AUTH)
			o_auth_val = authinfo[2];

		if ((user->authority & A_S_AUTH) == A_S_AUTH)
			a_auth_val = authinfo[0];
		if ((user->authority & A_U_AUTH) == A_U_AUTH)
			a_auth_val = authinfo[1];
		if ((user->authority & A_N_AUTH) == A_N_AUTH)
			a_auth_val = authinfo[2];

		if ((user->authority & T_S_AUTH) == T_S_AUTH)
			t_auth_val = authinfo[0];
		if ((user->authority & T_U_AUTH) == T_U_AUTH)
			t_auth_val = authinfo[1];
		if ((user->authority & T_N_AUTH) == T_N_AUTH)
			t_auth_val = authinfo[2];


		gtk_list_store_append(GTK_LIST_STORE(model), &iter);
		gtk_list_store_set(GTK_LIST_STORE(model), &iter,
							COLUMN_AUTH_UID, user->uid,
							COLUMN_AUTH_NAME, user->name,
							COLUMN_AUTH_U, u_auth_val,
							COLUMN_AUTH_M, m_auth_val,
							COLUMN_AUTH_O, o_auth_val,
							COLUMN_AUTH_A, a_auth_val,
							COLUMN_AUTH_T, t_auth_val,
							-1);
			
					
	}

	if (sel_list != NULL) {
		g_slist_free(sel_list);
		sel_list = NULL;
	}

	gtk_tree_view_set_model(treeview, model);
	g_object_unref(model);
}


void cb_auth_cell_edited(GtkCellRendererText *cell, const gchar *path_string, 
						const gchar *new_text, gpointer data)
{
	GtkTreeModel *model = (GtkTreeModel *) data;
	GtkTreePath *path = gtk_tree_path_new_from_string(path_string);
	GtkTreeIter iter;
	GSList *iterator;
	GtkTreeRowReference *cur_iter;
	gboolean in = FALSE;

	cur_iter = gtk_tree_row_reference_new(model, path);	


	gint column = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(cell), "column"));

	gtk_tree_model_get_iter(model, &iter, path);

	gtk_list_store_set(GTK_LIST_STORE(model), &iter, column, new_text, -1);				

	for (iterator = upt_list; iterator; iterator = iterator->next) {
		if (cur_iter == iterator->data) {
			in = TRUE;
			break;
		}
	}
	if(!in) {
		upt_list = g_slist_append(upt_list, cur_iter);
	}

	gtk_tree_path_free(path);
}

void cb_apply_auth(GtkButton *button, gpointer data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(data);
	GtkTreePath *path;
	GtkTreeIter iter;
	GSList *iterator;
	gchar *uid;
	gint auth ;
	gchar *u, *m, *o, *a, *t;	
	for (iterator = upt_list; iterator; iterator = iterator->next) {
		path = gtk_tree_row_reference_get_path(iterator->data);	
		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, COLUMN_AUTH_UID, &uid, -1);
		gtk_tree_model_get(model, &iter, COLUMN_AUTH_U, &u, -1);
		gtk_tree_model_get(model, &iter, COLUMN_AUTH_M, &m, -1);
		gtk_tree_model_get(model, &iter, COLUMN_AUTH_O, &o, -1);
		gtk_tree_model_get(model, &iter, COLUMN_AUTH_A, &a, -1);
		gtk_tree_model_get(model, &iter, COLUMN_AUTH_T, &t, -1);
		
		auth = 0;
		if (g_strcmp0(u, authinfo[0]) == 0) {
			auth |= U_S_AUTH;
		}
		if (g_strcmp0(u, authinfo[1]) == 0) {
			auth |= U_U_AUTH;
		}
		if (g_strcmp0(u, authinfo[2]) == 0) {
			auth |= U_N_AUTH;
		}

		if (g_strcmp0(m, authinfo[0]) == 0) {
			auth |= M_S_AUTH;
		}
		if (g_strcmp0(m, authinfo[1]) == 0) {
			auth |= M_U_AUTH;
		}
		if (g_strcmp0(m, authinfo[2]) == 0) {
			auth |= M_N_AUTH;
		}

		if (g_strcmp0(o, authinfo[0]) == 0) {
			auth |= O_S_AUTH;
		}
		if (g_strcmp0(o, authinfo[1]) == 0) {
			auth |= O_U_AUTH;
		}
		if (g_strcmp0(o, authinfo[2]) == 0) {
			auth |= O_N_AUTH;
		}

		if (g_strcmp0(a, authinfo[0]) == 0) {
			auth |= A_S_AUTH;
		}
		if (g_strcmp0(a, authinfo[1]) == 0) {
			auth |= A_U_AUTH;
		}
		if (g_strcmp0(a, authinfo[2]) == 0) {
			auth |= A_N_AUTH;
		}

		if (g_strcmp0(t, authinfo[0]) == 0) {
			auth |= T_S_AUTH;
		}
		if (g_strcmp0(t, authinfo[1]) == 0) {
			auth |= T_U_AUTH;
		}
		if (g_strcmp0(t, authinfo[2]) == 0) {
			auth |= T_N_AUTH;
		}

		update_auth(uid, auth);
		g_free(uid);
		g_free(u);
		g_free(m);
		g_free(o);
		g_free(a);
		g_free(t);
	}

	upt_list = NULL;

}

void cb_realize_window(GtkWidget *win, gpointer data)
{
	if ((cur_user.authority & U_N_AUTH) == U_N_AUTH) {
		gtk_widget_set_visible(GTK_WIDGET(auth_widget.u_box), FALSE);
	}
	if ((cur_user.authority & M_N_AUTH) == M_N_AUTH) {
		gtk_widget_set_visible(GTK_WIDGET(auth_widget.m_box), FALSE);
	}
	if ((cur_user.authority & O_N_AUTH) == O_N_AUTH) {
		gtk_widget_set_visible(GTK_WIDGET(auth_widget.o_box), FALSE);
	}
	if ((cur_user.authority & A_N_AUTH) == A_N_AUTH) {
		gtk_widget_set_visible(GTK_WIDGET(auth_widget.a_box), FALSE);
	}
	if ((cur_user.authority & T_N_AUTH) == T_N_AUTH) {
		gtk_widget_set_visible(GTK_WIDGET(auth_widget.t_box), FALSE);
	}
	/* 有编辑权限时开启按钮有效*/
	if ((cur_user.authority & U_U_AUTH) != U_U_AUTH) {
		gtk_widget_set_sensitive(GTK_WIDGET(auth_widget.edit_u), FALSE);
	}
	if ((cur_user.authority & M_U_AUTH) != M_U_AUTH) {
		gtk_widget_set_sensitive(GTK_WIDGET(auth_widget.edit_m), FALSE);
	}
	if ((cur_user.authority & A_U_AUTH) != A_U_AUTH) {
		gtk_widget_set_sensitive(GTK_WIDGET(auth_widget.edit_a), FALSE);
	}

	gtk_label_set_text(auth_widget.s_u, cur_user.name);

}
