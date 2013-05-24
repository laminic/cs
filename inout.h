/*
 * =====================================================================================
 *
 *       Filename:  inout.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/22/2013 01:32:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __INOUT_H__
#define __INOUT_H__
void cb_combo_click(GtkComboBox *widget, gpointer data);
void cb_io_cell_edited(GtkCellRendererText *cell, const gchar *path_string,
					const gchar *new_text, gpointer data);

#endif
