/*
 * =====================================================================================
 *
 *       Filename:  auth.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/09/2013 07:05:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __AUTH_H__
#define __AUTH_H__

#include <gtk/gtk.h>
#include "user.h"
#include "user_mod.h"


/* 用户 */
#define U_S_AUTH (0x1<<0)    /* 查看权限 */
#define U_U_AUTH (0x1<<1)/* 全部权限 */
#define U_N_AUTH (0x1<<2)/* 禁止所有 */

/* 货物 */
#define M_S_AUTH (0x1<<3)
#define M_U_AUTH (0x1<<4)
#define M_N_AUTH (0x1<<5)

/* 进出 */
#define O_S_AUTH (0x1<<6)
#define O_U_AUTH (0x1<<7)
#define O_N_AUTH (0x1<<8)

/* 权限 */
#define A_S_AUTH (0x1<<9)
#define A_U_AUTH (0x1<<0xA)
#define A_N_AUTH (0x1<<0xB)

/* 报表 */
#define T_S_AUTH (0x1<<0xC)
#define T_U_AUTH (0x1<<0xD)
#define T_N_AUTH (0x1<<0xE)


typedef struct AUTH_COL {
	GtkCellRendererText *auth_id;
	GtkCellRendererText *auth_name;
	GtkCellRendererText *auth_u;
	GtkCellRendererText *auth_m;
	GtkCellRendererText *auth_o;
	GtkCellRendererText *auth_a;
	GtkCellRendererText *auth_t;
}AUTH_COL;

typedef struct AUTH_WIDGET {
	GtkEntry *auth_user_search;
	GtkButton *applybtn;
	GtkCheckButton *checkbtn;

	GtkCheckButton *edit_u;	
	GtkCheckButton *edit_m;	
	GtkCheckButton *edit_a;	


	GtkBox *u_box;
	GtkBox *m_box;
	GtkBox *o_box;
	GtkBox *a_box;
	GtkBox *t_box;

	GtkLabel *s_u;

	AUTH_COL auth_col;
}AUTH_WIDGET;


enum {
	COLUMN_AUTH_UID,
	COLUMN_AUTH_NAME,
	COLUMN_AUTH_U,
	COLUMN_AUTH_M,
	COLUMN_AUTH_O,
	COLUMN_AUTH_A,
	COLUMN_AUTH_T,
};
void cb_auth_cell_edited(GtkCellRendererText *cell, const gchar *path_string, 
						const gchar *new_text, gpointer data);
void cb_authentry(GtkEntry *entry, gpointer data);
void init_auth(GtkBuilder *builder);
void cb_realize_window(GtkWidget *win, gpointer data);
void cb_apply_auth(GtkButton *button, gpointer data);
void cb_editable_checkbtn(GtkToggleButton *button, gpointer data);
#endif 
