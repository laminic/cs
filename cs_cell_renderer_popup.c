/*
 * =====================================================================================
 *
 *       Filename:  cs_cell_renderer_popup.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/03/2013 09:14:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <gtk/gtk.h>

#include "cs_cell_renderer_popup.h"

enum {
	SHOW_POPUP,
	HIDE_POPUP,
	LAST_SIGNAL
};

static void popup_init(CsCellRendererPopup *popup);
static void popup_class_init(CsCellRendererPopupClass *class);

static GtkCellEditable *
popup_start_editing (GtkCellRenderer *cell,
					GdkEvent 		*event,
					GtkWidget 		*widget,
					const gchar 	*path,
					GdkRectangle 	*background_area,
					GdkRectangle 	*cell_area,
					GtkCellRendererState flags);
static popup_show_popu

