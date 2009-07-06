#ifndef __CP_COLOR_H__
#define __CP_COLOR_H__

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define CP_TYPE_COLOR             (cp_color_get_type())
#define CP_COLOR(object)          ((CpColor*)object)
#define CP_IS_COLOR(object)       ((object) && (CP_COLOR(object)->type == CP_TYPE_COLOR))

#define CP_TYPE_COLOR_THEME       (cp_color_theme_get_type())
#define CP_COLOR_THEME(object)    ((CpColorTheme*)object)
#define CP_IS_COLOR_THEME(object) ((object) && (CP_COLOR_THEME(object)->type == CP_TYPE_COL_OR_THEME))

typedef struct _CpColor CpColor;
struct _CpColor {
	   GType type;
	   float r,g,b,a;
	   };

typedef struct _CpColorTheme CpColorTheme;
struct _CpColorTheme {
		GType type;
		GList *colors;
		};

void cp_color_free (CpColor *self);
GType cp_color_get_type (void);

G_END_DECLS

#endif
