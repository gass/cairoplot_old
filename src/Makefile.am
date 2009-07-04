AM_CPPFLAGS = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" 

AM_CFLAGS =\
	 -Wall\
	 -g
libcairoplot_la_CFLAGS = $(GLIB_CFLAGS) \
						$(CAIRO_CFLAGS) \
						-I ./

libcairoplot_la_LADD = $(GLIB_LIBS) \
						$(CAIRO_LIBS)

lib_LTLIBRARIES = \
	libcairoplot.la

libcairoplot_la_SOURCES = \
	cairoplot.c  \
	cairoplot.h

