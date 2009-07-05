/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * cairoplot.c
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

#include <glib.h>
#include <cairo.h>
#include <string.h>
#include <stdarg.h>
#include "cairoplot.h"
#include <stdio.h>

/* how to solve this problem? */
/* standard colors */
color	red		= {1.0,0.0,0.0,1.0},
		lime    	= {0.0,1.0,0.0,1.0},
		blue		= {0.0,0.0,1.0,1.0},
		maroon		= {0.5,0.0,0.0,1.0},
		green		= {0.0,0.5,0.0,1.0},
		navy		= {0.0,0.0,0.5,1.0},
		yellow		= {1.0,1.0,0.0,1.0},
		magenta 	= {1.0,0.0,1.0,1.0},
		cyan		= {0.0,1.0,1.0,1.0},
		orange		= {1.0,0.5,0.0,1.0},
		white		= {1.0,1.0,1.0,1.0},
		black		= {0.0,0.0,0.0,1.0},
		gray		= {0.5,0.5,0.5,1.0},
		light_gray	= {0.9,0.9,0.9,1.0},
		transparent	= {0.0,0.0,0.0,0.0};


static void plot_render_gradient_background (Plot *p);
static void plot_render_one_color_background (Plot *p);
static void plot_background_theme_destroy (Plot *p);

/** Initialize the plot object.
 This starts the plot object without a cairo reference.
*/
Plot *plot_init() {
	Plot *p;
	/* just to make a point */
	color grid_color = {0.8, 0.8, 0.8, 1.0};
	
	p = g_malloc(sizeof(Plot));
	
	/* initialize the object with default values */
	/* cairo surface */
	p->surface = NULL;
	/* cairo context */
	p->cairoContext = NULL;
	
	/* default size */
	p->dimensions[HORZ] = 640;
	p->dimensions[VERT] = 480;
	
	/* start data arrays as NULL*/
	p->labels[0] = NULL;
	p->labels[1] = NULL;

	p->data[0] = NULL;
	p->data[1] = NULL;

	/* style */
	p->fontsize = 10;
	plot_set_background_color (p, &white);
	p->border = 3;
	p->borders = NULL;
    p->line_color = black;
	p->line_width = 0.5;
    p->label_color = black;
	p->grid_color = grid_color;

	return p;
}

/** frees the plot's memory */
void plot_destroy (Plot *p) {
	plot_background_theme_destroy (p);
	g_free (p);	
}

/** Changes the background color of a Plot */
void plot_set_background_color (Plot *p, const color *background_color) {
	plot_background_theme_destroy (p);
	create_color_theme (&p->background, 1, background_color);
}

/** changes the background color for a color gradient */
void plot_set_background_color_theme (Plot *p, int n_colors, ...){
	color *c;
	int i;
	va_list colors;

	plot_background_theme_destroy (p);
	
	va_start(colors, n_colors);
	create_color_theme_aux (&p->background, n_colors, colors);
	va_end(colors);
}

/** Add a cairo context to the plot object */
void plot_set_cairo_context(Plot *p, cairo_t *ct) {
	p->cairoContext = ct;
	p->surface = cairo_get_target (p->cairoContext);
	p->dimensions[HORZ] = cairo_image_surface_get_width (p->surface);
	p->dimensions[VERT] = cairo_image_surface_get_height (p->surface);
}

/** renders the border for the Plot */
void plot_render_bounding_box (Plot *p) {
	if (!p->cairoContext) {
		return;
	}
	cairo_set_source_rgba (p->cairoContext,
						   p->line_color.r,
						   p->line_color.g,
						   p->line_color.b,
						   p->line_color.a);
	cairo_set_line_width (p->cairoContext,
						  p->line_width);
	
	cairo_rectangle (p->cairoContext,
					 p->border,
					 p->border,
					 p->dimensions[HORZ]- 2*(p->border),
					 p->dimensions[VERT]- 2*(p->border));
	cairo_stroke (p->cairoContext);
}

/** Renders the background with only one color */
static void plot_render_one_color_background (Plot *p) {
	cairo_set_source_rgba (p->cairoContext,
						   p->background.color_array->r,
						   p->background.color_array->g,
						   p->background.color_array->b,
						   p->background.color_array->a);
}

/** Renders the background as an equal color gradient */
static void plot_render_gradient_background (Plot *p) {
	
	int i;
	cairo_pattern_t *cp;
	ColorTheme *ct = &p->background;
	
	cp = cairo_pattern_create_linear (p->dimensions[HORZ] / 2, 0,
									  p->dimensions[HORZ] / 2,
									  p->dimensions[VERT]);
	for (i=0; i<ct->n_colors;i++) {
		cairo_pattern_add_color_stop_rgba   (cp,
											 i,
											 ct->color_array[i].r,
                                             ct->color_array[i].g,
											 ct->color_array[i].b,
											 ct->color_array[i].a);
		
	}
	cairo_set_source (p->cairoContext, cp);
}
/** render the plot background */
void plot_render_background (Plot *p) {
	if (!p->cairoContext) {
		return;
	}
	if (p->background.n_colors >1) {
		plot_render_gradient_background (p);
	} else {
		plot_render_one_color_background (p);
	}
	cairo_rectangle (p->cairoContext,
					 0,
					 0,
					 p->dimensions[HORZ],
					 p->dimensions[VERT]);
	cairo_fill (p->cairoContext);
}

/** finnish the rendering */
void plot_render_commit (Plot *p) {
	if (!p->cairoContext) {
		return;
	}
	cairo_show_page (p->cairoContext);	
}

/** renders all elements of the Plot */
void plot_render_all (Plot *p) {
	if (!p->cairoContext) {
		return;
	}
	plot_render_background (p);
	plot_render_bounding_box(p);
	
	
	/* closing the render */
	plot_render_commit(p);
	
}

/* auxiliar functions */

/** evaluates the background colors information and frees it */
static void plot_background_theme_destroy (Plot *p) {
	if (p->background.n_colors >0)
		g_free(p->background.color_array);
}

/** create a color theme as a color array */
void create_color_theme (ColorTheme * ct, int n_colors, ...) {
	va_list colors;
	
	va_start(colors, n_colors);
	create_color_theme_aux (ct, n_colors, colors);
	va_end(colors);
}
/** auxiliary function that defines the theme */
void create_color_theme_aux (ColorTheme * ct, int n_colors, va_list colors)
{
	color *theme, *c;
	int i;
	
	/* create the color array */
	ct->color_array = g_malloc(n_colors*sizeof(color));
	ct->n_colors = n_colors;
	for (i=0; i<n_colors; i++) {
		c = va_arg (colors, color *);
		g_memmove (&ct->color_array[i], c, sizeof(color));
	}
	va_end (colors);
}
