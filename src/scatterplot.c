/***************************************************************************
 *            scatterplot.c
 *
 *  Sun Jul  5 17:25:42 2009
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

#include <math.h>

#include "scatterplot.h"


/** initializes the scatter plot object */
Plot *scatter_plot_init(void) {
	Plot *p = plot_init();
	ScatterPlot *sp = (ScatterPlot *) p->extend;
	sp = g_malloc (sizeof(ScatterPlot));

	/* init scatter variables */
	sp->axis = TRUE;
	sp->discrete = FALSE;
	sp->variable_radius = FALSE;
	sp->x_label_angle = G_PI / 2.5;
	
	return p;
}

static void scatter_plot_calc_extends_max_dir(Plot *p, int direction) {
	int i;
	ScatterPlot *st = (ScatterPlot *)p->extend;
	cairo_text_extents_t extents;
	
	cairo_text_extents (p->cairoContext,
						&p->labels[direction][0],
						&extents);
	st->label_max_size[direction] = extents.height;
	for (i=0; i<p->data_size; i++)
	{
		
		cairo_text_extents (p->cairoContext,
							&p->labels[direction][i],
							&extents);
		if (extents.height > st->label_max_size[direction])
			st->label_max_size[direction] = extents.height;	
	}
	p->borders[other_direction (direction)] = st->label_max_size[direction] + p->border + 20;
	
}
void scatter_plot_calc_extends (Plot *p) {

	cairo_set_font_size (p->cairoContext, p->fontsize*0.8);
	scatter_plot_calc_extends_max_dir(p, HORZ);
	scatter_plot_calc_extends_max_dir(p, VERT);	
}
	
void scatter_plot_calc_extends_direction (int direction) {
	
}


/*
void scatter_plot_render_grid (Plot *p) {
	if (!st->grid){
		return;
	}
	plot_height = p->dimensions[VERT] - 2 * p->borders[VERT];
	
self.plot_width = self.dimensions[HORZ] - 2* self.borders[HORZ]
	horizontal_step = plot_height ) / ( len( self.labels[VERT] ) - 1 )
        vertical_step = float( self.plot_width ) / ( len( self.labels[HORZ] ) - 1 )
        
        x = self.borders[HORZ] + vertical_step
        y = self.plot_top - horizontal_step
        
        for label in self.labels[HORZ][:-1]:
            cr.set_source_rgba(*self.grid_color)
            cr.move_to(x, self.dimensions[VERT] - self.borders[VERT])
            cr.line_to(x, self.borders[VERT])
            cr.stroke()
            x += vertical_step
        for label in self.labels[VERT][:-1]:
            cr.set_source_rgba(*self.grid_color)
            cr.move_to(self.borders[HORZ], y)
            cr.line_to(self.dimensions[HORZ] - self.borders[HORZ], y)
            cr.stroke()
            y -= horizontal_step

}
*/
