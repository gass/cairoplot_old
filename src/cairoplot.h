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

#ifndef __CAIROPLOT_H__
#define __CAIRO_PLOT_H__
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
	char	*labels[2];
	int		fontsize;
	color   background;
	int		border;
	int		*borders;
    color   line_color;
    float   line_width;
    color   label_color;
    color   grid_color;
};
#endif
