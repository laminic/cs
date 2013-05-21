/*
 * =====================================================================================
 *
 *       Filename:  cell_renderer_popup.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/03/2013 08:39:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __CELL_RENDERER_POPUP__
#define __CELL_RENDERER_POPUP__

#include <gtk/gtk.h>

#define CS_TYPE_CELL_RENDERER_POPUP (cs_cell_renderer_popup_get_type())

#define CS_CELL_RENDERER_POPUP(obj) (GTK_CHECK_CAST((obj), CS_TYPE_CELL_RENDERER_POPUP, CsCellRendererPopup))

#define CS_CELL_RENDERER_POPUP_CLASS(klass) (GTK_CHECK_CLASS_CAST((klass), CS_TYPE_CELL_RENDERER_POPUP, CsCellRendererPopupClass))

#define CS_IS_CELL_RENDERER_POPUP(obj) (GTK_CHECK_TYPE((obj), CS_TYPE_CELL_RENDERER_POPUP))

#define CS_IS_CELL_RENDERER_POPUP_CLASS(klass) (GTK_CHECK_CLASS_TYPE((obj), CS_TYPE_CELL_RENDERER_POPUP))

#define CS_CELL_RENDERER_POPUP_GET_CLASS(obj) (GTK_CHECK_GET_CLASS((obj), CS_TYPE_CELL_RENDERER_POPUP, CsCellRendererPopupClass))

typedef struct _CsCellRendererPopup CsCellRendererPopup;
typedef struct _CsCellRendererPopupClass CsCellRendererPopupClass;

struct _CsCellRendererPopup {
	GtkCellRendererText parent;

	gint 				button_width;
	GtkWidget 			*popup_window;
	GtkWidget 			*focus_window;
	GtkWidget 			*editable;

	gboolean 			shown;
	gboolean 			editing_caceled;
};

struct _CsCellRendererPopupClass {
	GtkCellRendererTextClass parent_class;

	void (*show_popup) (CsCellRendererPopup *cell,
						const gchar 		*path,
						gint 				x1,
						gint 				y1,
						gint 				x2,
						gint 				y2);
	void (*hide_popup) (CsCellRendererPopup *cell);
};

GtkType cs_cell_renderer_popup_get_type(void) G_GNUC_CONST;

GtkCellRenderer *cs_cell_renderer_popup_new(void);

void cs_cell_renderer_popup_show(CsCellRendererPopup *cell,
								const gchar 		*path,
								gint 				x1,
								gint 				y1,
								gint 				x2,
								gint 				y2);
void cs_cell_renderer_popup_hide(CsCellRendererPopup *cell);

#endif 




