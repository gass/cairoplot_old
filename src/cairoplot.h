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

typedef struct _ColorTheme ColorTheme;
struct _ColorTheme {
	int n_colors;
	color *color_array;
};

typedef struct _Plot Plot;

struct _Plot {
	cairo_surface_t *surface;
	int		dimensions[2];
	cairo_t *cairoContext;
	void	*data[2];
	char	*labels[2];
	int		fontsize;
	ColorTheme background;
	int	border;
	int		*borders;
    color   line_color;
    float   line_width;
    color   label_color;
    color   grid_color;
    void	*extend;
};
/* object settings */
Plot *plot_init();
void plot_destroy (Plot *p);
void plot_set_background_color(Plot *p, const color *background_color);
void plot_set_background_color_theme (Plot *p, int n_colors, ...);
void plot_set_cairo_context(Plot *p, cairo_t *ct);

/* the render group */
void plot_render_bounding_box (Plot *p);
void plot_render_background (Plot *p);
void plot_render_commit (Plot *p);
void plot_render_all (Plot *p);

/* auxiliar functions */
void color_theme_unset_colors (ColorTheme *ct);
void create_color_theme (ColorTheme * ct, int n_colors, ...);
void create_color_theme_aux (ColorTheme * ct, int n_colors, va_list colors);
#endif
