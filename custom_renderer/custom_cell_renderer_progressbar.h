/*
 * =====================================================================================
 *
 *       Filename:  custom_renderer_progressbar.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/02/2013 01:19:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __CUSTOM_RENDERER__
#define __CUSTOM_RENDERER__

#include <stdlib.h>

#include <gtk/gtk.h>

#define CUSTOM_TYPE_CELL_RENDERER_PROGRESS (custom_cell_cenderer_progress_get_type())

#define CUSTOM_CELL_RENDERER_PROGRESS(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), CUSTOM_TYPE_CELL_RENDERER_PROGRESS, CustomCellRendererProgressClass))

#define CUSTOM_CELL_RENDERER_PROGRESS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), CUSTOM_TYPE_CELL_RENDERER_PROGRESS))

#define CUSTOM_IS_CELL_PROGRESS_PROGRESS(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), CUSTOM_TYPE_CELL_RENDERER_PROGRESS))

#define CUSTOM_IS_CELL_PROGRESS_PROGRESS_CLASS(klass) (G_TYPE_CLASS_TYPE((klass), CUSTOM_TYPE_CELL_RENDERER_PROGRESS))

#define CUSTOM_CELL_RENDERER_PROGRESS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), CUSTOM_TYPE_CELL_RENDERER_PROGRESS, CustomCellRendererProgressClass))

typedef struct _CustomCellRendererProgress CustomCellRendererProgress;
typedef struct _CustomCellRendererProgressClass CustomCellRendererProgressClass;

struct _CustomCellRendererProgress {
	GtkCellRenderer parent;

	gdouble progress;
};

struct _CustomCellRendererProgressClass {
	GtkCellRendererClass parent_class;
};

GType custom_cell_renderer_progress_get_type(void);
GtkCellRenderer *custom_cell_renderer_progress_new(void);

#endif
