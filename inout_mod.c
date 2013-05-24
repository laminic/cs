/*
 * =====================================================================================
 *
 *       Filename:  inout_mod.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/22/2013 01:32:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

extern sqlite3 *db;

static int rc = 0;
static GHashTable *pre_sql = NULL;


