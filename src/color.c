

#include <glib.h>
#include <stdarg.h>
#include "color.h"

static void cp_color_theme_add_colors_va (CpColorTheme *self, CpColor * color, va_list colors);

CpColorTheme *cp_color_theme_new_empty(void) {
			 CpColorTheme *cct = g_new0 (CpColorTheme, 1);
			 cct->type = CP_TYPE_COLOR_THEME;
			 cct->colors = NULL;
			 }

void cp_color_theme_free (CpColorTheme *self) {
	 g_list_foreach (self->colors, (GFunc) &cp_color_free, NULL);
	 g_list_free (self->colors);
	 g_free(self);
	 }

CpColorTheme * cp_color_theme_new (CpColor *color, ...) {
		CpColorTheme *self = cp_color_theme_new_empty ();
		va_list colors;
		va_start (colors, color);
		cp_color_theme_add_colors_va (self, color, colors);
		va_end(colors);
		}

void cp_color_theme_set_colors (CpColorTheme *self, CpColor *color, ...)
{
		va_list colors;
		/* a new color empty list */
		g_list_free (self->colors);

		va_start (colors, color);
		cp_color_theme_add_colors_va (self, color, colors);
		va_end(colors);
}
	
static void cp_color_theme_add_colors_va (CpColorTheme *self, CpColor * color, va_list colors)
{

	while (color) {
		  self->colors = g_list_append (self->colors, color);
		  color = va_arg (colors, CpColor *);
		  }
}
CpColor *cp_color_new_empty(void) {
			 CpColor *cc = g_new0 (CpColor, 1);
			 cc->type = CP_TYPE_COLOR;
			 }

CpColor *cp_color_new(float r, float g, float b, float a) {
			 CpColor *cc = g_new0 (CpColor, 1);
			 cc->type = CP_TYPE_COLOR;
			 cc->r = r;
			 cc->g = g;
			 cc->b = b;
			 cc->a = a;
}

void cp_color_free (CpColor *self) {
	 g_free(self);
	 }

GType cp_color_get_type (void)
{
	static GType cp_color_type_id = 0;
	
	if(!cp_color_type_id)
	{
		static const GTypeInfo g_define_type_info = 
		{
			sizeof (CpColor),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) cp_color_new_empty,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof (CpColor),
			0,
			(GInstanceInitFunc) cp_color_instance_init,
			NULL
		};
		
		cp_plot_type_id = g_type_register_static
		(
			G_TYPE_OBJECT, "CpColor", &g_define_type_info, 0
		);
	}
	
	return cp_plot_type_id;
}
