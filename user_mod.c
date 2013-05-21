/*
 * =====================================================================================
 *
 *       Filename:  user_mod.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/27/2013 12:23:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <gtk/gtk.h>
#include "user_mod.h"
#include "common.h"

//#define G(str) str==NULL?NULL:g_locale_to_utf8(str, -1, NULL, NULL, NULL)
//#define L(str) str==NULL?NULL:g_locale_from_utf8(str, -1, NULL, NULL, NULL)

extern sqlite3 *db;

static int rc = 0;
static GHashTable *pre_sql = NULL;

gboolean logincheck(const gchar *u, const gchar *p, USER *user)
{
	gboolean rst_val = FALSE;
	sqlite3_stmt *stmt = NULL;

	const gchar *check_sql = "select * from _120236ly where name=? and passwd=?";

	rc = sqlite3_prepare_v2(db, check_sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
		return;
	}
	sqlite3_bind_text(stmt, 1, G(u), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, G(p), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		user->uid = L(sqlite3_column_text(stmt, 0));
		user->name = L(sqlite3_column_text(stmt, 1));
		user->age = L(sqlite3_column_text(stmt, 2));
		user->birth = L(sqlite3_column_text(stmt, 3));
		user->idcard = L(sqlite3_column_text(stmt, 4));
		user->place = L(sqlite3_column_text(stmt, 5));
		user->address = L(sqlite3_column_text(stmt, 6));
		user->phone = L(sqlite3_column_text(stmt, 7));
		user->other = L(sqlite3_column_text(stmt, 8));
		user->authority = sqlite3_column_int(stmt, 9);
		user->passwd = L(sqlite3_column_text(stmt, 10));

		rst_val = TRUE;	
	}
	sqlite3_finalize(stmt);
	return rst_val;
}
void update_auth(gchar *uid, gint auth)
{
	if(pre_sql == NULL)	
	   pre_sql = g_hash_table_new(g_str_hash, g_str_equal);

	sqlite3_stmt *stmt = NULL;
	int idx = -1;

	if (NULL== (stmt=g_hash_table_lookup(pre_sql, "update_auth"))){

		const char* update_auth = "update _120236ly set autflag=? where uid=?";
		rc = sqlite3_prepare_v2(db, update_auth, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
			return;
		}
		g_hash_table_insert(pre_sql, "update_auth", stmt);
	}

	sqlite3_bind_int(stmt, 1, auth);
	sqlite3_bind_text(stmt, 2, G(uid), -1, SQLITE_STATIC);
	sqlite3_step(stmt);
	sqlite3_reset(stmt);
}

void get_user_list(GSList *user_list)
{
	IDENTITY_USER *u;

	if(pre_sql == NULL)	
	   pre_sql = g_hash_table_new(g_str_hash, g_str_equal);
	
	sqlite3_stmt *stmt = NULL;
	int idx = -1;

	if (NULL== (stmt=g_hash_table_lookup(pre_sql, "getusers"))){

		const char* update_auth = "select uid, name from _120236ly";
		rc = sqlite3_prepare_v2(db, update_auth, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
			return;
		}
		g_hash_table_insert(pre_sql, "getusers", stmt);
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		u = (IDENTITY_USER *) g_malloc(sizeof(IDENTITY_USER));
		u->uid = L(sqlite3_column_text(stmt, 0));
		u->name = L(sqlite3_column_text(stmt, 1));
		*user_list = g_slist_insert(*user_list, u);
	}	
	sqlite3_reset(stmt);
}

void inster_user(USER *user)
{
   if(pre_sql == NULL)	
	   pre_sql = g_hash_table_new(g_str_hash, g_str_equal);

	sqlite3_stmt *stmt = NULL;
	int idx = -1;

	if (NULL== (stmt=g_hash_table_lookup(pre_sql, "inster_user"))){

		const char* ins_sql = "insert into _120236ly(uid, name, age, birth, idcard, place, address, phone, other) values(?, ?, ?, ?, ?, ?, ?, ?, ? )";
		rc = sqlite3_prepare_v2(db, ins_sql, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
			return;
		}
		g_hash_table_insert(pre_sql, "inster_user", stmt);
	}

	if (user==NULL)
		return;
	sqlite3_bind_text(stmt, 1, G(user->uid), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, G(user->name), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, G(user->age), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, G(user->birth), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, G(user->idcard), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 6, G(user->place), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 7, G(user->address), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 8, G(user->phone), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 9, G(user->other), -1, SQLITE_STATIC);

	sqlite3_step(stmt);
	sqlite3_reset(stmt);
	g_free(user->uid);
	g_free(user->name);
	g_free(user->age);
	g_free(user->birth);
	g_free(user->idcard);
	g_free(user->place);
	g_free(user->address);
	g_free(user->phone);
	g_free(user->other);

}

void delete_user(USER *user)
{
   if(pre_sql == NULL)	
	   pre_sql = g_hash_table_new(g_str_hash, g_str_equal);

	sqlite3_stmt *stmt = NULL;
	int idx = -1;

	if (NULL== (stmt=g_hash_table_lookup(pre_sql, "delete_user"))){

		const char* ins_sql = "delete from _120236ly where uid=?";
		rc = sqlite3_prepare_v2(db, ins_sql, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
			return;
		}
		g_hash_table_insert(pre_sql, "delete_user", stmt);
	}

	if (user==NULL)
		return;
	sqlite3_bind_text(stmt, 1, user->uid, -1, SQLITE_STATIC);	
	sqlite3_step(stmt);
	sqlite3_reset(stmt);
	g_free(user->uid);
}

void update_user(USER *user)
{
	if(pre_sql == NULL)	
	   pre_sql = g_hash_table_new(g_str_hash, g_str_equal);

	sqlite3_stmt *stmt = NULL;
	int idx = -1;

	if (NULL== (stmt=g_hash_table_lookup(pre_sql, "update_user"))){

		const char* upt_sql = "update _120236ly set \
								name=?, 	\
								age=?, 		\
								birth=?, 	\
								idcard=?, 	\
								place=?, 	\
								address=?, 	\
								phone=?, 	\
								other=? 	\
								where uid=? \
							   ";
		rc = sqlite3_prepare_v2(db, upt_sql, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
			return;
		}
		g_hash_table_insert(pre_sql, "update_user", stmt);
	}

	if (user==NULL)
		return;
	sqlite3_bind_text(stmt, 1, G(user->name), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, G(user->age), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, G(user->birth), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, G(user->idcard), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, G(user->place), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 6, G(user->address), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 7, G(user->phone), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 8, G(user->other), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 9, G(user->uid), -1, SQLITE_STATIC);

	sqlite3_step(stmt);
	sqlite3_reset(stmt);
	g_free(user->uid);
	g_free(user->name);
	g_free(user->age);
	g_free(user->birth);
	g_free(user->idcard);
	g_free(user->place);
	g_free(user->address);
	g_free(user->phone);
	g_free(user->other);

}

void iterator_user(sqlite3_stmt *stmt, GSList **sel_list)
{
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		USER *user = g_malloc(sizeof(USER));
			user->uid = L(sqlite3_column_text(stmt, 0));
			user->name = L(sqlite3_column_text(stmt, 1));
			user->age = L(sqlite3_column_text(stmt, 2));
			user->birth = L(sqlite3_column_text(stmt, 3));
			user->idcard = L(sqlite3_column_text(stmt, 4));
			user->place = L(sqlite3_column_text(stmt, 5));
			user->address = L(sqlite3_column_text(stmt, 6));
			user->phone = L(sqlite3_column_text(stmt, 7));
			user->other = L(sqlite3_column_text(stmt, 8));
			user->authority = sqlite3_column_int(stmt, 9);
			user->passwd = L(sqlite3_column_text(stmt, 10));
			
		*sel_list = g_slist_append(*sel_list, user);
	}
}

void select_user(gchar *filter, GSList **sel_list)
{
	if(pre_sql == NULL)	
	   pre_sql = g_hash_table_new(g_str_hash, g_str_equal);

	sqlite3_stmt *stmt = NULL;
	int idx = -1;

	if (g_strcmp0(filter,"") == 0) {
		if (NULL== (stmt=g_hash_table_lookup(pre_sql, "select_all_user"))){
			const char* select_sql = "select * from _120236ly"; 
			rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, NULL);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
				return;
			}
			g_hash_table_insert(pre_sql, "select_all_user", stmt);
		}
		iterator_user(stmt, sel_list);
		sqlite3_reset(stmt);
	} else {
		if (NULL== (stmt=g_hash_table_lookup(pre_sql, "select_filter_user"))){
			const char* sel_filter_sql = "select * from _120236ly where name like ?";
			rc = sqlite3_prepare_v2(db, sel_filter_sql, -1, &stmt, NULL);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
				return;
			}
			g_hash_table_insert(pre_sql, "select_filter_user", stmt);
		}
		gchar buf[20];
		g_snprintf(buf, 20, "%%%s%%",G(filter));
		sqlite3_bind_text(stmt, 1, buf, -1, SQLITE_STATIC);
		iterator_user(stmt, sel_list);
		sqlite3_reset(stmt);
	}
}
