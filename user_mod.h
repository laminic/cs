/*
 * =====================================================================================
 *
 *       Filename:  user_mod.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/28/2013 02:28:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __USER_MOD__
#define __USER_MOD__

#include <sqlite3.h>
#include "user.h"

typedef struct IDENTITY_USER {
	gchar* uid;
	gchar* name;
}IDENTITY_USER;

void inster_user(USER *user);
void delete_user(USER *user);
void update_user(USER *user);
gboolean logincheck(const gchar *u, const gchar *p, USER *user);
void get_user_list(GSList *user_list);
#endif 
