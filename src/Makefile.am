AM_CPPFLAGS = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" 

AM_CFLAGS =\
	 -Wall\
	 -g

libcairoplot_la_CFLAGS = $(GLIB_CFLAGS) \
						$(CAIRO_CFLAGS) \
						-I./

libcairoplot_la_LADD = $(GLIB_LIBS) \
						$(CAIRO_LIBS)

lib_LTLIBRARIES = \
	libcairoplot.la

libcairoplot_la_SOURCES = \
	cairoplot.c  \
	cairoplot.h

bin_PROGRAMS = \
	unit_test

unit_test_CFLAGS = $(GLIB_CFLAGS) \
					$(CAIRO_CFLAGS) \
					$(GTK_CFLAGS) \
					-I./

unit_test_LADD = $(GLIB_LIBS) \
				 $(CAIRO_LIBS) \
				 $(GTK_LIBS)

unit_test_SOURCES = \
	cairoplot.c\
	cairoplot.h \
	test.c

