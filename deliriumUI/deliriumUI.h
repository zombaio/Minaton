 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cairo/cairo.h>
#include "pugl/pugl.h"

typedef enum 
{
	deliriumUI_Button,
	deliriumUI_Knob,
	deliriumUI_MicroKnob,
	deliriumUI_Fader, 
	deliriumUI_Switch
} deliriumUI_WidgetType;

typedef struct {
	deliriumUI_WidgetType	type;
	float	x;
	float	y;
	float	w;
	float	h;
	bool	pressed;
	bool	hover;
	bool	toggleMode;
	const char* label;
	float	value;
	float	min;
	float	max;
	float clickTop;
	float clickBottom;
} deliriumUIWidget;

typedef struct {
	int originalWidth;
	int originalHeight;
	int currentWidth;
	int currentHeight;
	int gridX;
	int gridY;
	int widgetWidth;
	int widgetHeight;
	deliriumUIWidget* deliriumUIWidgets;
	int numberOfUIWidgets;
	int currentWidgetNumber;
	int mouseButton[16];
} deliriumUI;


void cleanUpDeliriumUI(deliriumUI*);
void setDeliriumUIGridSize(deliriumUI*, int, int, int, int);
void setDeliriumUICurrentWindowSize(deliriumUI*, int, int);
int addDeliriumUIWidget(deliriumUI*, deliriumUI_WidgetType, float, float, float, float, char*);
void displayDeliriumUIWidget(deliriumUI*, cairo_t*, int);
void displayAllDeliriumUIWidgets(deliriumUI*, cairo_t*);
void isMouseOverDeliriumUIWidget(deliriumUI*, cairo_t*, int, int);
void setValueFromMousePosition(deliriumUI*, int, int, int);
void hasMouseClickedDeliriumUIWidget(deliriumUI*, int, int);

static void roundedBox(cairo_t* cr, double x, double y, double w, double h)
{
	static const double radius  = 10;
	static const double degrees = 3.14159265 / 180.0;

	cairo_new_sub_path(cr);
	cairo_arc(cr,
	          x + w - radius,
	          y + radius,
	          radius, -90 * degrees, 0 * degrees);
	cairo_arc(cr,
	          x + w - radius, y + h - radius,
	          radius, 0 * degrees, 90 * degrees);
	cairo_arc(cr,
	          x + radius, y + h - radius,
	          radius, 90 * degrees, 180 * degrees);
	cairo_arc(cr,
	          x + radius, y + radius,
	          radius, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);
}


void displayDiliriumUIButton(deliriumUI*, cairo_t*, int);
void displayDiliriumUIKnob(deliriumUI*, cairo_t*, int);
void displayDiliriumUIMicroKnob(deliriumUI*, cairo_t*, int);
void displayDiliriumUIFader(deliriumUI*, cairo_t*, int);
void displayDiliriumUISwitch(deliriumUI*, cairo_t*, int);
int getNumberOfWidgets(deliriumUI*);

void setValueDiliriumUIFader(deliriumUI*, int, float);




