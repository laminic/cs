/*
 * =====================================================================================
 *
 *       Filename:  user.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/19/2013 03:31:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "user.h"
#include "user_mod.h"
USER_WIDGET user_widget;

static GSList *ins_list = NULL;
static GSList *del_list = NULL;
static GSList *upt_list = NULL;
static GSList *sel_list = NULL;


void init_user(GtkBuilder *builder)
{

	user_widget.new_user_button = GTK_BUTTON(gtk_builder_get_object(builder, "newuserbutton"));
	user_widget.del_user_button = GTK_BUTTON(gtk_builder_get_object(builder, "deluserbutton"));
	user_widget.apply_user_button = GTK_BUTTON(gtk_builder_get_object(builder, "applyuserbutton"));
	
	user_widget.user_col.col_user_id = (GtkCellRendererText*)gtk_builder_get_object(builder, "col_user_id");
	user_widget.user_col.col_user_name = (GtkCellRendererText*)gtk_builder_get_object(builder, "col_user_name");
	user_widget.user_col.col_user_age = (GtkCellRendererText*)gtk_builder_get_object(builder, "col_user_age");
	user_widget.user_col.col_user_birth = (GtkCellRendererText*)gtk_builder_get_object(builder, "col_user_birth");
	user_widget.user_col.col_user_idcard = (GtkCellRendererText*)gtk_builder_get_object(builder, "col_user_idcard");
	user_widget.user_col.col_user_place = (GtkCellRendererText*)gtk_builder_get_object(builder, "col_user_place");
	user_widget.user_col.col_user_address = (GtkCellRendererText*)gtk_builder_get_object(builder, "col_user_address");
	user_widget.user_col.col_user_phone = (GtkCellRendererText*)gtk_builder_get_object(builder, "col_user_phone");
	user_widget.user_col.col_user_other = (GtkCellRendererText*)gtk_builder_get_object(builder, "col_user_other");

	g_object_set_data(G_OBJECT(user_widget.user_col.col_user_id), "column", GINT_TO_POINTER(COLUMN_USER_UID));
	g_object_set_data(G_OBJECT(user_widget.user_col.col_user_name), "column", GINT_TO_POINTER(COLUMN_USER_NAME));
	g_object_set_data(G_OBJECT(user_widget.user_col.col_user_age), "column", GINT_TO_POINTER(COLUMN_USER_AGE));
	g_object_set_data(G_OBJECT(user_widget.user_col.col_user_birth), "column", GINT_TO_POINTER(COLUMN_USER_BIRTH));
	g_object_set_data(G_OBJECT(user_widget.user_col.col_user_idcard), "column", GINT_TO_POINTER(COLUMN_USER_IDCARD));
	g_object_set_data(G_OBJECT(user_widget.user_col.col_user_place), "column", GINT_TO_POINTER(COLUMN_USER_PLACE));
	g_object_set_data(G_OBJECT(user_widget.user_col.col_user_address), "column", GINT_TO_POINTER(COLUMN_USER_ADDRESS));
	g_object_set_data(G_OBJECT(user_widget.user_col.col_user_phone), "column", GINT_TO_POINTER(COLUMN_USER_PHONE));
	g_object_set_data(G_OBJECT(user_widget.user_col.col_user_other), "column", GINT_TO_POINTER(COLUMN_USER_OTHER));


}




void cb_newuserbutton(GtkButton *button, gpointer user_data)
{
	GtkTreeModel*model = (GtkTreeModel*) user_data;	
	GtkTreeIter iter;
	GtkTreePath *path;
	GtkTreeRowReference *cur_iter;
	GDateTime *datetime;
	gchar *strtime;
	datetime = g_date_time_new_now_local();
	strtime = g_date_time_format(datetime, "%y%m%d%H%M%S");

	gtk_list_store_append(GTK_LIST_STORE(model), &iter);
	gtk_list_store_set(GTK_LIST_STORE(model), &iter,
						COLUMN_USER_UID, strtime,
						COLUMN_USER_NAME, "",
						COLUMN_USER_AGE, "",
						COLUMN_USER_BIRTH, "",
						-1);
	path = gtk_tree_model_get_path(model, &iter);
	cur_iter = gtk_tree_row_reference_new(model, path);	
	ins_list = g_slist_prepend(ins_list, cur_iter);
	gtk_tree_path_free(path);
}

void cb_edituserbutton(GtkToggleButton *toggle_button)
{

	gboolean flag = gtk_toggle_button_get_active(toggle_button);

	/* id 项不可以编辑 */
	//g_object_set(user_widget.user_col.col_user_id,"editable", flag,	NULL);
	
	g_object_set(user_widget.user_col.col_user_name,"editable", flag,	NULL);
	g_object_set(user_widget.user_col.col_user_age,"editable", flag,	NULL);
	g_object_set(user_widget.user_col.col_user_birth,"editable", flag,	NULL);
	g_object_set(user_widget.user_col.col_user_idcard,"editable", flag,	NULL);
	g_object_set(user_widget.user_col.col_user_place,"editable", flag,	NULL);
	g_object_set(user_widget.user_col.col_user_address,"editable", flag,	NULL);
	g_object_set(user_widget.user_col.col_user_phone,"editable", flag,	NULL);
	g_object_set(user_widget.user_col.col_user_other,"editable", flag,	NULL);

	gtk_widget_set_visible((GtkWidget*)user_widget.new_user_button , flag);
	gtk_widget_set_visible((GtkWidget*)user_widget.del_user_button , flag);
	gtk_widget_set_visible((GtkWidget*)user_widget.apply_user_button , flag);
}

void cb_applybutton(GtkButton *button, gpointer userdata)
{
	GSList *iterator = NULL;
	GtkTreeModel *model;
	GtkTreePath *path;
	GtkTreeIter iter;
	USER user;
	
	model = (GtkTreeModel *) userdata;
	for (iterator=ins_list; iterator; iterator= iterator->next) {
		path = gtk_tree_row_reference_get_path(iterator->data);

		/* gtk_tree_model_get 拷贝新的，需自行释放 */
		if (path==NULL)continue;
		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, COLUMN_USER_UID , &(user.uid), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_NAME, &(user.name), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_AGE, &(user.age), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_BIRTH, &(user.birth), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_IDCARD, &(user.idcard), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_PLACE, &(user.place), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_ADDRESS, &(user.address), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_PHONE, &(user.phone), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_OTHER, &(user.other), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_AUTHORITY, &(user.authority), -1);

		inster_user(&user);

		gtk_tree_path_free(path);
		gtk_tree_row_reference_free(iterator->data);
	}
	if (ins_list != NULL) {
		g_slist_free(ins_list);
		ins_list = NULL;
	}

	for (iterator=del_list; iterator; iterator= iterator->next) {
		user.uid = iterator->data;
		delete_user(&user);
	}
	if (del_list != NULL) {
		g_slist_free(del_list);
		del_list = NULL;
	}

	for (iterator = upt_list; iterator; iterator = iterator->next) {
		path = gtk_tree_row_reference_get_path(iterator->data);
		if (path==NULL)continue;

		/* gtk_tree_model_get 拷贝新的，需自行释放 */

		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, COLUMN_USER_UID , &(user.uid), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_NAME, &(user.name), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_AGE, &(user.age), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_BIRTH, &(user.birth), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_IDCARD, &(user.idcard), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_PLACE, &(user.place), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_ADDRESS, &(user.address), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_PHONE, &(user.phone), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_OTHER, &(user.other), -1);
		gtk_tree_model_get(model, &iter, COLUMN_USER_AUTHORITY, &(user.authority), -1);

		update_user(&user);

		gtk_tree_path_free(path);
		gtk_tree_row_reference_free(iterator->data);
	}
	if (upt_list != NULL) {
		g_slist_free(upt_list);
		upt_list = NULL;
	}

}

void cb_deluserbutton(GtkButton *button, gpointer user_data)
{
	GtkTreeView *treeview = (GtkTreeView*) user_data;	
	GtkTreeIter iter;
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);

	if (gtk_tree_selection_get_selected(selection, NULL, &iter))
	{
		GtkTreePath *path;
		gchar* uid;
		gtk_tree_model_get(model, &iter, COLUMN_USER_UID, &uid, -1);
		del_list = g_slist_append(del_list, uid);

		path = gtk_tree_model_get_path(model, &iter);
		gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
		gtk_tree_path_free(path);
	}
}
void __add_user_model__(GtkTreeModel* model, USER *user)
{
	GtkTreeIter iter;
	
	g_return_if_fail(user!=NULL);
	
	if ( (user->uid==NULL) || (g_strcmp0(user->uid, "")==0) )
		return;

	gtk_list_store_append(GTK_LIST_STORE(model), &iter);
	gtk_list_store_set(GTK_LIST_STORE(model), &iter,
				COLUMN_USER_UID, user->uid,
				COLUMN_USER_NAME, user->name,
				COLUMN_USER_AGE, user->age,
				COLUMN_USER_BIRTH, user->birth,
				COLUMN_USER_IDCARD, user->idcard,
				COLUMN_USER_PLACE, user->place,
				COLUMN_USER_ADDRESS, user->address,
				COLUMN_USER_PHONE, user->phone,
				COLUMN_USER_OTHER, user->other,
				-1);
}
void cb_selectentry(GtkEntry *entry, gpointer data)
{
	GtkTreeView *treeview = GTK_TREE_VIEW(data);
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	GSList *iterator;
	USER *user;	
	const gchar *select_filter;
	
	select_filter = gtk_entry_get_text(entry);

	select_user(select_filter, &sel_list);

	g_object_ref(model);
	gtk_tree_view_set_model(treeview, NULL);
	gtk_list_store_clear(GTK_LIST_STORE(model));
	
	/* USER 实体在什么地方释放？我没有释放,model清除会不会自动释放实体 */
	for (iterator=sel_list; iterator; iterator= iterator->next) {
		user = iterator->data;
		__add_user_model__(model, user);

	}
	if (sel_list != NULL) {
		g_slist_free(sel_list);
		sel_list = NULL;
	}

	gtk_tree_view_set_model(treeview, model);
	g_object_unref(model);
}


void cb_user_cell_edited(GtkCellRendererText *cell, const gchar *path_string, 
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

	switch(column) {
		case COLUMN_USER_BIRTH:
			{

			}
			break;
	}
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




