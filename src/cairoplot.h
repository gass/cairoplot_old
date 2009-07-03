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

#include <cairo.h>
 
typedef struct _plot plot;


 struct _plot {
	
 self.create_surface(surface, width, height)
        self.dimensions = {}
        self.dimensions[HORZ] = width
        self.dimensions[VERT] = height
        self.context = cairo.Context(self.surface)
        self.labels={}
        self.labels[HORZ] = x_labels
        self.labels[VERT] = y_labels
        self.load_series(data, x_labels, y_labels, series_colors)
        self.font_size = 10
        self.set_background (background)
        self.border = border
        self.borders = {}
        self.line_color = (0.5, 0.5, 0.5)
        self.line_width = 0.5
        self.label_color = (0.0, 0.0, 0.0)
        self.grid_color = (0.8, 0.8, 0.8)
 
 
 }
