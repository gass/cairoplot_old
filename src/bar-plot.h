#ifndef __CP_BAR_PLOT_H__
#define __CP_BAR_PLOT_H__

#include "plot.h"

G_BEGIN_DECLS

#define CP_TYPE_BAR_PLOT (cp_bar_plot_get_type ())
#define CP_BAR_PLOT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CP_TYPE_BAR_PLOT, CpBarPlot))
#define CP_BAR_PLOT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), CP_TYPE_BAR_PLOT, CpBarPlotClass))
#define CP_IS_BAR_PLOT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CP_TYPE_BAR_PLOT))
#define CP_IS_BAR_PLOT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CP_TYPE_BAR_PLOT))
#define CP_BAR_PLOT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), CP_TYPE_BAR_PLOT, CpBarPlotClass))

typedef struct
{
	CpPlot parent_instance;
	gboolean round_rect;
} CpBarPlot;

typedef struct
{
	CpPlotClass parent_class;
} CpBarPlotClass;

GType cp_bar_plot_get_type (void);
CpPlot* cp_bar_plot_new();

G_END_DECLS

#endif
