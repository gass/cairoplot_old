dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(cairoplot, 2.0)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC




AM_PROG_LIBTOOL




PKG_CHECK_MODULES(libcairoplot, cairo glib-2.0)
AC_SUBST(libcairoplot_CFLAGS)
AC_SUBST(libcairoplot_LIBS)

PKG_CHECK_MODULES(Introduza um novo m&#xF3;dulo, cairo)
AC_SUBST(Introduza um novo m&#xF3;dulo_CFLAGS)
AC_SUBST(Introduza um novo m&#xF3;dulo_LIBS)

AC_OUTPUT([
Makefile
])
