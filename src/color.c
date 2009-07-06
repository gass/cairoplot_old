CpColorTheme *cp_color_theme_new_empty(void) {
			 CpColorTheme *cct = g_new0 (CpColorTheme, 1);
			 cct->gtype = CP_TYPE_COLOR_THEME;
			 cct->colors = NULL;
			 }

void cp_color_theme_free (CpColorTheme *self) {
	 g_list_foreach (self->colors,&cp_color_free, NULL);
	 g_list_free (self->colors);
	 g_free(self);
	 }

CpColorTheme * cp_color_new (const CpColor *color, ...) {
		CpColorTheme *self = cp_color_theme_new_empty ();
		va_list colors;
		va_start (colors, color);
		cp_color_theme_add_colors_va (color, colors);
		va_end(colors);
		}

void cp_color_theme_set_colors (CpColorTheme *self, const CpColor *color, ...) {
		va_list colors;
		/* a new color empty list */
		g_list_free (self->colors);

		va_start (colors, color);
		cp_color_theme_add_colors_va (color, colors);
		va_end(colors);
	 }
	
static void cp_color_theme_add_colors_va (CpColorTheme *self, const CpColor * color, valist colors){
	va_start(color, colors);
	while (color) {
		  self->colors = g_list_Append (self->colors, color);
		  color = va_arg (colors, CpColor);
		  }
	 }
CpColor *cp_color_new_empty(void) {
			 CpColor *cc = g_new0 (CpColor, 1);
			 cc->gtype = CP_TYPE_COLOR;
			 }

CpColor *cp_color_new(float r, float g, float b, float a) {
			 CpColor *cc = g_new0 (CpColor, 1);
			 cc->gtype = CP_TYPE_COLOR;
			 cc->r = r;
			 cc->g = g;
			 cc->b = b;
			 cc->a = a;
			 }

void cp_color_free (CpColor *self) {
	 g_free(self);
	 }

