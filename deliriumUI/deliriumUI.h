 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cairo/cairo.h>
#include "pugl/pugl.h"

typedef struct {
	int	type;
	int	x;
	int	y;
	int	w;
	int	h;
	bool	pressed;
	bool	hover;
	const char* label;
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
} deliriumUI;

typedef struct {
	int         x;
	int         y;
	int         w;
	int         h;
	bool        pressed;
	const char* label;
} Button;


void cleanUpDeliriumUI(deliriumUI*);
void setDeliriumUIGridSize(deliriumUI*, int, int, int, int);
void setDeliriumUICurrentWindowSize(deliriumUI*, int, int);
int addDeliriumUIWidget(deliriumUI*, int, int, int, int, char*);
void displayDeliriumUIWidget(deliriumUI*, cairo_t*, int);
void displayAllDeliriumUIWidgets(deliriumUI*, cairo_t* cr);
void setDeliriumUIWidgetHover(deliriumUI*, int, bool);
void isMouseOverDeliriumUIWidget(deliriumUI*, int, int);
void hasMouseClickedDeliriumUIWidget(deliriumUI*, int, int);





