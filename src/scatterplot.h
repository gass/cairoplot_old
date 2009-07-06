/***************************************************************************
 *            scatterplot.h
 *
 *  Sun Jul  5 17:24:51 2009
 *  Copyright  2009  Luis Matos
 *  <gass@otiliamatos.ath.cx>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */
 
#ifndef __SCATTERPLOT_H__
#define __SCATTERPLOT_H__
#include <glib.h>
#include "cairoplot.h"

typedef struct _ScatterPlot ScatterPlot;

struct _ScatterPlot {
	/** have axis */
	gboolean axis;
	gboolean discrete;
	int dots;
	gboolean variable_radius;
	float x_label_angle;
	ColorTheme circle_color;
	int borders[2];
	float max_value[2];
	float label_max_size[2];
	float *data[2];
};

/* object settings */
Plot *scatter_plot_init(void);

#endif /* __SCATTERPLOT_H__ */
