/*
 * =====================================================================================
 *
 *       Filename:  material_mod.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/31/2013 09:41:18 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include "common.h"
#include "material_mod.h"

extern sqlite3 *db;

static int rc = 0;
static GHashTable *sql_stmt_hash = NULL;

static const gint n_sql = 5;
static gchar *hash_key[25] = {
							"insert_material",
							"delete_material",
							"update_material",
							"select_all_material",
							"select_filter_material"
						};
static gchar *sql_text[1024] = {
						"insert into material_120236ly values(?, ?, ?, ?, ?, ?)",
						"delete from material_120236ly where mid=?",
						"update material_120236ly set \
							mname=?, 		\
							mtype=?, 		\
							munit=?, 		\
							mstock=?, 		\
							mcomment=?  	\
							where mid=?",
						"select * from material_120236ly",
						"select * from material_120236ly \
							where mid like ? or mname like ? or mtype like ?"  
						};
void SQL_init_material()
{
	int i;
	sqlite3_stmt *stmt = NULL;

	if (sql_stmt_hash == NULL) {

		sql_stmt_hash = g_hash_table_new(g_str_hash, g_str_equal);
		
		for (i = 0; i < n_sql; i++) {
			rc = sqlite3_prepare_v2(db , sql_text[i], -1, &stmt, NULL);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db) );
				return;
			}
			g_hash_table_insert(sql_stmt_hash, hash_key[i], stmt);
		}

	}
}

void SQL_ins_material(MATERIAL *material)
{
	sqlite3_stmt *stmt = NULL;
	int idx = -1;

	stmt = g_hash_table_lookup(sql_stmt_hash, "insert_material");
	if (stmt == NULL) {
		fprintf(stderr, "hash lookup error: %s\n", "result is null");
		return;
	}

	sqlite3_bind_text(stmt, 1, G(material->mid), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, G(material->mname), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, G(material->mtype), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, G(material->munit), -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 5, material->mstock);
	sqlite3_bind_text(stmt, 6, G(material->mcomment), -1, SQLITE_STATIC);

	sqlite3_step(stmt);
	sqlite3_reset(stmt);
}

void SQL_upt_material(MATERIAL *material)
{
	sqlite3_stmt *stmt = NULL;
	int idx = -1;

	stmt = g_hash_table_lookup(sql_stmt_hash, "update_material");
	if (stmt == NULL) {
		fprintf(stderr, "hash lookup error: %s\n", "result is null");
		return;
	}

	sqlite3_bind_text(stmt, 1, G(material->mname), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, G(material->mtype), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, G(material->munit), -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, material->mstock);
	sqlite3_bind_text(stmt, 5, G(material->mcomment), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 6, G(material->mid), -1, SQLITE_STATIC);

	sqlite3_step(stmt);
	sqlite3_reset(stmt);

}

void SQL_del_material(MATERIAL *material)
{
	sqlite3_stmt *stmt = NULL;
	int idx = -1;

	stmt = g_hash_table_lookup(sql_stmt_hash, "delete_material");
	if (stmt == NULL) {
		fprintf(stderr, "hash lookup error: %s\n", "result is null");
		return;
	}

	sqlite3_bind_text(stmt, 1, G(material->mid), -1, SQLITE_STATIC);
		
	sqlite3_step(stmt);
	sqlite3_reset(stmt);

}

void SQL_select_material(const gchar *filter, GSList **list)
{
	sqlite3_stmt *stmt = NULL;

	if (g_strcmp0(filter, "")){
		stmt = g_hash_table_lookup(sql_stmt_hash, "select_filter_material");
		gchar buf[64] = {0};
		snprintf(buf, 64, "%%%s%%", filter);
		sqlite3_bind_text(stmt, 1, G(buf), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, G(buf), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, G(buf), -1, SQLITE_STATIC);
	} else {
		stmt = g_hash_table_lookup(sql_stmt_hash, "select_all_material");
	}

	if (stmt == NULL) {
		fprintf(stderr, "hash lookup error: %s\n", "result is null");
		return;
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		MATERIAL *mat = g_malloc(sizeof(MATERIAL));
		mat->mid = L(sqlite3_column_text(stmt, 0));
		mat->mname = L(sqlite3_column_text(stmt, 1));
		mat->mtype = L(sqlite3_column_text(stmt, 2));
		mat->munit = L(sqlite3_column_text(stmt, 3));
		mat->mstock = sqlite3_column_int(stmt, 4);
		mat->mcomment = L(sqlite3_column_text(stmt, 5));

		*list = g_slist_append(*list, mat);
	}
	sqlite3_reset(stmt);
}
