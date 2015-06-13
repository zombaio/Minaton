
#include "deliriumUI.h"

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

//------------------------------------------------------------------
// Add widget

int addDeliriumUIWidget(deliriumUI* deliriumUI_window, int _x, int _y, int _w, int _h, char* _label)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	deliriumUIWidgets = realloc( deliriumUIWidgets, sizeof(deliriumUIWidget) * numberOfUIWidgets );

	deliriumUI_window->deliriumUIWidgets = deliriumUIWidgets;

	deliriumUIWidgets[numberOfUIWidgets-1].x = _x;
	deliriumUIWidgets[numberOfUIWidgets-1].y = _y;
	deliriumUIWidgets[numberOfUIWidgets-1].w = _w;
	deliriumUIWidgets[numberOfUIWidgets-1].h = _h;
	deliriumUIWidgets[numberOfUIWidgets-1].pressed = false;
	deliriumUIWidgets[numberOfUIWidgets-1].hover = false;
	deliriumUIWidgets[numberOfUIWidgets-1].label = _label;

	numberOfUIWidgets++;

	deliriumUI_window->numberOfUIWidgets = numberOfUIWidgets;

	printf ("\nNumber of widgets now at %d\n", deliriumUI_window->numberOfUIWidgets);

	return numberOfUIWidgets-1; // return handle number
} 

//------------------------------------------------------------------
// set packing grid size

void setDeliriumUIGridSize(deliriumUI* deliriumUI_window, int _w, int _h, int _x, int _y)
{
	deliriumUI_window->originalWidth = _w;
	deliriumUI_window->originalHeight = _h;
	deliriumUI_window->currentWidth = _w;
	deliriumUI_window->currentHeight = _h;
	deliriumUI_window->gridX = _x;
	deliriumUI_window->gridY = _y;
	deliriumUI_window->widgetWidth = _w / _x;
	deliriumUI_window->widgetHeight = _h / _y;
}

//------------------------------------------------------------------
// set current window size

void setDeliriumUICurrentWindowSize(deliriumUI* deliriumUI_window, int _w, int _h)
{
	deliriumUI_window->currentWidth = _w;
	deliriumUI_window->currentHeight = _h;
	deliriumUI_window->widgetWidth = _w / deliriumUI_window->gridX;
	deliriumUI_window->widgetHeight = _h / deliriumUI_window->gridY;
}

//------------------------------------------------------------------
// Display widget
void displayDeliriumUIWidget(deliriumUI* deliriumUI_window, cairo_t* cr, int widgetNumber)
{

	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	int x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
	int y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
	int w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
	int h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

	x += deliriumUIWidgets[widgetNumber].pressed * 2;
	y += deliriumUIWidgets[widgetNumber].pressed * 2;

	cairo_rectangle(cr, x, y, w, h);
	cairo_clip(cr);

	// Draw base
	if (deliriumUIWidgets[widgetNumber].hover) {
		cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 1);
	} else {
		cairo_set_source_rgba(cr, 0.3, 0.3, 0.3, 1);
	}

	roundedBox(cr, x, y, w, h);
	cairo_fill_preserve(cr);

	// Draw border
	cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1);
	cairo_set_line_width(cr, 4.0);
	cairo_stroke(cr);

	// Draw label
	cairo_text_extents_t extents;
	cairo_set_font_size(cr, deliriumUI_window->widgetHeight / 1.5);
	cairo_text_extents(cr, deliriumUIWidgets[widgetNumber].label, &extents);
	cairo_move_to(cr,
	              (x + w / 2) - extents.width / 2,
	              (y + h / 2) + extents.height / 2);

	cairo_set_source_rgba(cr, 0, 0, 0, 1);
	cairo_show_text(cr, deliriumUIWidgets[widgetNumber].label);

	cairo_reset_clip(cr);


}

//------------------------------------------------------------------
// Display all widgets

void displayAllDeliriumUIWidgets(deliriumUI* deliriumUI_window, cairo_t* cr)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		displayDeliriumUIWidget(deliriumUI_window, cr, widgetNumber);
	}
}

//------------------------------------------------------------------
// Set widget hover flag

void setDeliriumUIWidgetHover(deliriumUI* deliriumUI_window, int widgetNumber, bool _hover)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	deliriumUIWidgets[widgetNumber].hover = _hover;
}

//------------------------------------------------------------------
// check if mouse is hovering over widget
void isMouseOverDeliriumUIWidget(deliriumUI* deliriumUI_window, int _x, int _y)
{

	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		int x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
		int y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
		int w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
		int h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

		w -= 2;
		h -= 2;
		
		if (_x>=x && _y>=y && _x<=x+w && _y<=y+h) 
		{
			deliriumUIWidgets[widgetNumber].hover = true;
		}
		else
		{
			deliriumUIWidgets[widgetNumber].hover = false;
		}
	}
}


//------------------------------------------------------------------
// check if widget has been clicked by mouse button

void hasMouseClickedDeliriumUIWidget(deliriumUI* deliriumUI_window, int _x, int _y)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		int x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
		int y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
		int w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
		int h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

		w -= 2;
		h -= 2;
		
		if (_x>=x && _y>=y && _x<=x+w && _y<=y+h) 
		{
			deliriumUIWidgets[widgetNumber].pressed = true;

		}
		else
		{
			deliriumUIWidgets[widgetNumber].pressed = false;
		}
	}
}

//------------------------------------------------------------------
// Initialise widget list

void cleanUpDeliriumUI(deliriumUI* deliriumUI_window)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	free(deliriumUIWidgets);
}





