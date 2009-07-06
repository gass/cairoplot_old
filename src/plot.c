#include "plot.h"
#include "color.h"

/* Declarations */
static void cp_plot_real_render(CpPlot* self);
static void cp_plot_finalize(GObject* obj);
static void cp_plot_get_property(GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void cp_plot_set_property(GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);

/* Private */
enum
{
	WIDTH_PROPERTY,
	HEIGHT_PROPERTY,
	BACKGROUND_PROPERTY,
	BORDER_COLOR_PROPERTY,
	BORDER_WIDTH_PROPERTY,
	CAIRO_OBJ_PROPERTY,
	SURFACE_OBJ_PROPERTY
};

enum
{
	PRE_RENDER_SIGNAL,
	POS_RENDER_SIGNAL,
	LAST_SIGNAL
};

#define DEFAULT_HEIGHT 400
#define DEFAULT_WIDTH 400
#define DEFAULT_BORDER_WIDTH 2

static gpointer cp_plot_parent_class = NULL;
static guint plot_signals[LAST_SIGNAL] = {0};

/* Special functions */

static void cp_plot_class_init (CpPlotClass* klass)
{
	cp_plot_parent_class = g_type_class_peek_parent(klass);
	CP_PLOT_CLASS (klass)->render_all = cp_plot_render_all;
	CP_PLOT_CLASS (klass)->render_background = cp_plot_render_background;
	G_OBJECT_CLASS (klass)->get_property = cp_plot_get_property;
	G_OBJECT_CLASS (klass)->set_property = cp_plot_set_property;
	G_OBJECT_CLASS (klass)->finalize = cp_plot_finalize;
	
	/* properties */
	GParamSpec* pspec = g_param_spec_int("width", "width", "width", 0, G_MAXINT, DEFAULT_WIDTH,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), WIDTH_PROPERTY, pspec);
	
	pspec = g_param_spec_int ("height", "height", "height", 0, G_MAXINT, DEFAULT_HEIGHT,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), HEIGHT_PROPERTY, pspec);
	
	pspec = g_param_spec_boxed ("background", "background", "background", 0, CP_TYPE_COLOR_THEME,
		G_PARAM_CONSTRUCT | G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), BACKGROUND_PROPERTY, pspec);
	
	pspec = g_param_spec_boxed ("border-color", "border-color", "border-color", 0, CP_TYPE_COLOR,
		G_PARAM_CONSTRUCT | G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), BACKGROUND_PROPERTY, pspec);
	
	
	pspec = g_param_spec_int ("border-width", "border-width", "border-width", 0, G_MAXINT, DEFAULT_BORDER_WIDTH,
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), HEIGHT_PROPERTY, pspec);
	
	pspec = g_param_spec_pointer ("cairo-context", "cairo-context", "cairo-context",
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), CAIRO_OBJ_PROPERTY, pspec);
	
	pspec = g_param_spec_pointer ("cairo-surface", "cairo-surface", "cairo-surface",
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), SURFACE_OBJ_PROPERTY, pspec);

	/* signals */
	plot_signals[PRE_RENDER_SIGNAL] = g_signal_new("pre-render", CP_TYPE_PLOT,
		G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	plot_signals[POS_RENDER_SIGNAL] = g_signal_new("pos-render", CP_TYPE_PLOT,
		G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
}

static void cp_plot_instance_init(CpPlot * self)
{
	self->width = DEFAULT_WIDTH;
	self->height = DEFAULT_HEIGHT;
	self->cairo = NULL;
	self->surface = NULL;
}

static void cp_plot_finalize (GObject* obj)
{
	G_OBJECT_CLASS(cp_plot_parent_class)->finalize(obj);
}

GType cp_plot_get_type (void)
{
	static GType cp_plot_type_id = 0;
	
	if(!cp_plot_type_id)
	{
		static const GTypeInfo g_define_type_info = 
		{
			sizeof (CpPlotClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) cp_plot_class_init,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof (CpPlot),
			0,
			(GInstanceInitFunc) cp_plot_instance_init,
			NULL
		};
		
		cp_plot_type_id = g_type_register_static
		(
			G_TYPE_OBJECT, "CpPlot", &g_define_type_info, 0
		);
	}
	
	return cp_plot_type_id;
}

static void cp_plot_get_property (GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
	CpPlot* self = CP_PLOT(object);
	
	switch(property_id)
	{
		case WIDTH_PROPERTY:
			g_value_set_int(value, self->width);
			break;
			
		case HEIGHT_PROPERTY:
			g_value_set_int(value, self->height);
			break;
		case BACKGROUND_PROPERTY:
			 g_value_set_boxed(value, self->background);
			 break;
	    case BORDER_COLOR_PROPERTY:
			 g_value_set_boxed(value, self->border_color);
			 break;
	    case BORDER_WIDTH_PROPERTY:
			 g_value_set_int(value, self->border_width);
			 break;
        case CAIRO_OBJ_PROPERTY:
			  g_value_set_pointer(value, self->cairo);
			  break;
        case SURFACE_OBJ_PROPERTY:
			 g_value_set_pointer(value, self->surface);
		  	 break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void cp_plot_set_property(GObject * object, guint property_id, const GValue* value, GParamSpec* pspec)
{
	CpPlot* self = CP_PLOT(object);
	
	switch(property_id)
	{
		case WIDTH_PROPERTY:
			self->width = g_value_get_int(value);
			break;
			
		case HEIGHT_PROPERTY:
			self->height = g_value_get_int(value);
			break;
			
		case BACKGROUND_PROPERTY:
			 self->background = g_value_boxed(value);
			 break;
			 
	    case BORDER_COLOR_PROPERTY:
			 self->border_color = g_value_boxed(value);
			 break;
			 
	    case BORDER_WIDTH_PROPERTY:
			 self->border_width = g_value_get_int(value);
			 break;
			 
	    case CAIRO_OBJ_PROPERTY:
			  self->cairo = g_value_pointer (value);
			  break;
			  
        case SURFACE_OBJ_PROPERTY:
			 self->surface = g_value_pointer (value);
		  	 break;
		  	 
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

/* Other methods */

CpPlot* cp_plot_new()
{
	return CP_PLOT(g_object_new(CP_TYPE_PLOT, NULL));
}

void cp_plot_render (CpPlot* self)
{
	g_signal_emit(self, plot_signals[PRE_RENDER_SIGNAL], 0);
	CP_PLOT_GET_CLASS(self)->render(self);
	g_signal_emit(self, plot_signals[POS_RENDER_SIGNAL], 0);
}

/** Renders the background with only one color */
static void cp_plot_render_background_one_color (CpPlot *self) {
    CpColor *color = (CpColor *)g_list_nth_data (self->background->colors, 0);

	cairo_set_source_rgba (self->cairoContext,
						   color->r,
						   color->g,
						   color->b,
						   color->a);
}

/** Renders the background as an equal color gradient */
static void cp_plot_render_background_gradient (CpPlot *self) {
	
	GList *colors;
	int i, n_colors;
	cairo_pattern_t *cp;
	CpColor *color;
	
	colors = self->background->colors;
	n_colors = g_list_lenght(colors);
	cp = cairo_pattern_create_linear (self->width / 2, 0,
									  self->width / 2,
									  self->height);
	for (i=0; i<n_colors;i++) {
		color = g_list_nth_data (colors, i);
		cairo_pattern_add_color_stop_rgba   (cp,
											 i,
											 color->r,
                                             color->g,
											 color->b,
											 color->a);
		
	}
	cairo_set_source (self->cairo, cp);
}

/** render the plot's background */
void cp_plot_render_background (CpPlot *self)
{
	int n_colors = g_list_count (self->background->color_array);

	if (n_colors > 1 ) {
		plot_render_gradient_background (self);
	} else if (n_colors == 1) {
		cp_plot_render_background_one_color (self);
	} else {
        return;
    }
	cairo_rectangle (self->cairo,
					 0,
					 0,
					 self->width,
					 self->height);
	cairo_fill (self->cairo);
 }
void cp_plot_render_all(CpPlot* self)
{
 	cp_plot_render_background(self);
	g_debug("Plot rendered with size == (%d, %d)!", self->width, self->height);
}

