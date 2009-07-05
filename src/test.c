/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * test.c
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


#include <gtk/gtk.h>
#include <stdlib.h>
#include "cairoplot.h"

static gboolean on_delete_event(GtkWidget * window,
				GdkEvent * event, gpointer unused_data);

static gboolean
on_expose_event(GtkWidget * widget, GdkEventExpose * event, plot * p);


int main(int argc, char *argv[])
{
	GtkWidget *window, *draw;
	plot *p = plot_init();
	color	red		= {1.0,0.0,0.0,1.0},
			lime    = {0.0,1.0,0.0,1.0};
	plot_set_background_color_theme (p, 2,  &red, &lime);
	/* Initialize GTK+. */
	gtk_set_locale();
	gtk_init(&argc, &argv);

	/* Create the window and widgets. */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	g_signal_connect(window, "delete_event",
			 (GtkSignalFunc) on_delete_event, NULL);

	/* start the drawing area */
	draw = gtk_drawing_area_new();
	gtk_widget_set_size_request(draw, 640, 480);

	gtk_container_add(GTK_CONTAINER(window), draw);
	/* the drawing area is only refreshed when shown */
	g_signal_connect(G_OBJECT(draw), "expose-event",
			 G_CALLBACK(on_expose_event), p);

	gtk_widget_show_all(window);

	/* Pass control to the GTK+ main event loop. */
	gtk_main();

	return 0;
}

  /* This is our handler for the "delete-event" signal of the window, which
     is emitted when the 'x' close button is clicked. We just exit here. */
static gboolean
on_delete_event(GtkWidget * window, GdkEvent * event, gpointer unused_data)
{
	return(0);
}

/* use cairo plot */
static gboolean
on_expose_event(GtkWidget * widget, GdkEventExpose * event, plot * p)
{
	p->cairoContext = gdk_cairo_create(widget->window);
	plot_render_all(p);
	return FALSE;
}
