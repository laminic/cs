/*
 * =====================================================================================
 *
 *       Filename:  custom_cell_renderer_progressbar.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/02/2013 01:40:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "custom_cell_renderer_progressbar.h"

static void custom_cell_renderer_progress_init (CustomCellRendererProgress *cellprogress);

static void custom_cell_renderer_progress_class_init(CustomCellRendererProgressClass *klass);

static void custom_cell_renderer_progress_get_property(GObject *object,
													guint 	param_id,
													GValue 	*value,
													GParamSpec *pspec);
static void custom_cell_renderer_progress_set_property(GObject *object,
													guint 	param_id,
													GValue 	*value,
													GParamSpec *pspec);
static void custom_cell_renderer_progress_finalize(GObject *gobject);

static void custom_cell_renderer_progress_get_size(GtkCellRenderer *cell,
												GtkWidget *widget,
												GdkRectangle *cell_area,
												gint *x_offset,
												gint *y_offset,
												gint width,
												gint height);
static void custom_cell_renderer_progress_renderer(GtkCellRenderer *cell,
												GdkWindow *window,
												GtkWidget *widget,
												GdkRectangle *background_area,
												GdkRectangle *cell_area,
												guint flags);
enum {
	PROP_PERCENTAGE = 1,
};

GType custom_cell_renderer_progress_get_type(void)
{
	static GType cell_progress_type = 0;

	if (cell_progress_type == 0) {
		static const GTypeInfo cell_progress_info = 
		{
			sizeof(CustomCellRendererProgressClass),
			NULL,
			NULL,
			(GClassInitFunc) custom_cell_renderer_progress_class_init,
			NULL,
			NULL,
			sizeof(CustomCellRendererProgress),
			0,
			(GInstanceInitFunc)custom_cell_renderer_progress_init,
		};
		cell_progress_type = g_type_register_static(GTK_TYPE_CELL_RENDERER,
											"CustomCellRendererProgress",
											&cell_progress_info,
											0);
	}
	return cell_progress_type;
}

static void 
custom_cell_renderer_progress_init(CustomCellRendererProgress *cellrendererprogress)
{
	GTK_CELL_RENDERER(cellrendererprogress)->mode = GTK_CELL_RENDERER_MODE_INERT;
	GTK_CELL_RENDERER(cellrendererprogress)->xpad = 2;
	GTK_CELL_RENDERER(cellrendererprogress)->ypad = 2;
}

static void
custom_cell_renderer_progress_class_init(CustomCellRendererProgressClass *klass)
{
	GtkCellRendererClass *cell_class = GTK_CELL_RENDERER_CLASS(klass);
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	parent_class = g_type_class_peek_parent(klass);
	object_class->finalize = custom_cell_renderer_progress_finalize;

}
