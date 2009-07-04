/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * cairoplot.h
 * Copyright (C) Luis Matos 2009 <gass@otiliamatos.ath.cx>
 * 
 * main.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CAIROPLOT_H__
#define __CAIROPLOT_H__

#include <cairo.h>

enum {HORZ=0, VERT=1};

typedef struct _color color;
struct _color {
	float   r;
	float   g;
	float   b;
	float   a;
};

typedef struct _plot plot;

struct _plot {
	cairo_surface_t *surface;
	int		dimensions[2];
	cairo_t *cairoContext;
	void	*data[2];
	char	*labels[2];
	int		fontsize;
	color   background;
	int	border;
	int		*borders;
    color   line_color;
    float   line_width;
    color   label_color;
    color   grid_color;
};
/* object settings */
plot *plot_init();
void plot_set_cairo_context(plot *p, cairo_t *ct);

/* the render group */
void plot_render_bounding_box (plot *p);
void plot_render_background (plot *p);
void plot_render_finnish (plot *p);
void plot_render_all (plot *p);

#endif
