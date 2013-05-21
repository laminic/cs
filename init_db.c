/*
 * =====================================================================================
 *
 *       Filename:  init_db.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/27/2013 11:06:24 AM
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

sqlite3 *db;

static char* dbname = "120236ly.sqlite.db";
static int n_tables = 2;
static char* tables[1024] = { "create table if not exists _120236ly (    	\
									uid char(12), 			\
									name nchar(10), 		\
									age nchar(4), 			\
									birth date, 			\
									idcard char(18), 		\
									place nchar(40), 		\
									address nchar(400), 	\
									phone varchar(20), 		\
									other nchar(200), 		\
									autflag integer default 65793, 		\
									passwd varchar(20) default '123'     \
								)", 						
								 "create table if not exists material_120236ly ( \
									  mid char(12), 		\
									  mname char(20), 		\
									  mtype char(10), 		\
									  munit char(5), 		\
									  mstock integer, 		\
									  mcomment char(100) 	\
								)",
								"create table if not exists o_120236ly ( \
									oid char(12), 			\
									odate date, 			\
									uid char(12), 			\
									ocomment char(400), 		\
									foreign key(uid) references _120236ly(uid) \
								)",
								"create table if not exists s_120236ly ( \
									oid char(12), 			\
									mid char(12), 			\
									num integer, 			\
									foreign key(oid) references o_120236ly(oid), \
									foreign key(mid) references material_120236ly(mid) \
								)"
							};

static int rc = 0;
static sqlite3_stmt *stmt = NULL;

void init_db()
{
	int i;
	
	sqlite3_initialize();
	rc = sqlite3_open_v2(dbname, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	if (rc != SQLITE_OK) {
		sqlite3_close(db);
	}

	for (i = 0; i < n_tables; i++) {
		rc = sqlite3_prepare_v2(db, tables[i], -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
			exit(-1);
		}
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
			exit(-1);
		}
		sqlite3_finalize(stmt);
	}
}
