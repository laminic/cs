/*
 * =====================================================================================
 *
 *       Filename:  material_mod.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/31/2013 09:41:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __MATERIAL_MOD__
#define __MATERIAL_MOD__

#include "material.h"
void SQL_init_material();
void SQL_select_material(const gchar *filter, GSList **list);
void SQL_del_material(MATERIAL *material);
void SQL_upt_material(MATERIAL *material);
void SQL_ins_material(MATERIAL *material);

#endif
