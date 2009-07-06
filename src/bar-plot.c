#include "bar-plot.h"

/* Declarations */
static void cp_bar_plot_real_render(CpPlot* self);
static void cp_bar_plot_finalize(GObject* obj);
static void cp_bar_plot_get_property(GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void cp_bar_plot_set_property(GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);

/* Private */
enum
{
	DUMMY_PROPERTY,
	ROUND_RECT_PROPERTY,
};

static gpointer cp_bar_plot_parent_class = NULL;

/* Special functions */

static void cp_bar_plot_class_init (CpBarPlotClass* klass)
{
	cp_bar_plot_parent_class = g_type_class_peek_parent(klass);
	CP_PLOT_CLASS (klass)->render = cp_bar_plot_real_render;
	G_OBJECT_CLASS (klass)->get_property = cp_bar_plot_get_property;
	G_OBJECT_CLASS (klass)->set_property = cp_bar_plot_set_property;
	G_OBJECT_CLASS (klass)->finalize = cp_bar_plot_finalize;
	
	/* properties */
	GParamSpec* pspec = g_param_spec_boolean("round-rect", "round-rect", "round-rect", TRUE, 
		G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE);
	g_object_class_install_property(G_OBJECT_CLASS (klass), ROUND_RECT_PROPERTY, pspec);
}

static void cp_bar_plot_instance_init(CpPlot * self)
{
	
}

static void cp_bar_plot_finalize (GObject* obj)
{
	G_OBJECT_CLASS(cp_bar_plot_parent_class)->finalize(obj);
}

GType cp_bar_plot_get_type (void)
{
	static GType cp_bar_plot_type_id = 0;
	
	if(!cp_bar_plot_type_id)
	{
		static const GTypeInfo g_define_type_info = 
		{
			sizeof (CpBarPlotClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) cp_bar_plot_class_init,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof (CpBarPlot),
			0,
			(GInstanceInitFunc) cp_bar_plot_instance_init,
			NULL
		};
		
		cp_bar_plot_type_id = g_type_register_static
		(
			CP_TYPE_PLOT, "CpBarPlot", &g_define_type_info, 0
		);
	}
	
	return cp_bar_plot_type_id;
}

static void cp_bar_plot_get_property (GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
	CpBarPlot* self = CP_BAR_PLOT(object);
	
	switch(property_id)
	{
		case ROUND_RECT_PROPERTY:
			g_value_set_boolean(value, self->round_rect);
			break;
		
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void cp_bar_plot_set_property(GObject * object, guint property_id, const GValue* value, GParamSpec* pspec)
{
	CpBarPlot* self = CP_BAR_PLOT(object);
	
	switch(property_id)
	{
		case ROUND_RECT_PROPERTY:
			self->round_rect = g_value_get_boolean(value);
			break;
			
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
			break;
	}
}

/* Other methods */

CpPlot* cp_bar_plot_new()
{
	return CP_PLOT(g_object_new(CP_TYPE_BAR_PLOT, NULL));
}

void cp_bar_plot_real_render(CpPlot* self)
{
	g_debug("BarPlot rendered with size == (%d, %d)!", self->width, self->height);	
}
