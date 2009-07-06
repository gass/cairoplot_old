AM_CPPFLAGS = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" 

AM_CFLAGS =\
	 -Wall\
	 -g

libcairoplot_la_CFLAGS = $(GLIB_CFLAGS) \
						$(CAIRO_CFLAGS) \
						$(GOBJECT_CFLAGS) \
						-I./

libcairoplot_la_LIBADD = $(GLIB_LIBS) \
						$(CAIRO_LIBS) \
						$(GOBJECT_LIBS)

lib_LTLIBRARIES = \
	libcairoplot.la

libcairoplot_la_SOURCES = \
	cairoplot.c  \
	cairoplot.h  \
	scatterplot.h  \
	scatterplot.c  \
	utils.c  \
	utils.h  \
	bar-plot.c  \
	bar-plot.h  \
	color.c  \
	color.h  \
	plot.c  \
	plot.h

bin_PROGRAMS = \
	unit_test

unit_test_CFLAGS = $(GLIB_CFLAGS) \
					$(CAIRO_CFLAGS) \
					$(GTK_CFLAGS) \
					$(GOBJECT_CFLAGS) \
					-I./

unit_test_LDADD = $(GLIB_LIBS) \
				 $(CAIRO_LIBS) \
				 $(GTK_LIBS) \
				 $(GOBJECT_LIBS)

unit_test_SOURCES = \
	cairoplot.c\
	cairoplot.h \
	test.c \
	scatterplot.c \
	scatterplot.h \
	utils.c \
	utils.h \
	bar-plot.c \
	bar-plot.h \
	color.c \
	color.h \
	plot.c \
	plot.h

