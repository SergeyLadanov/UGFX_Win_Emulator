#include "TransparentPainter.hpp"
#include "gfx_extended.h"

TransparentPainter::TransparentPainter(uint8_t width, uint8_t height, const uint8_t *arr)
    : Arr(arr), Width(width), Height(height)
{
}

void TransparentPainter::Move(gCoord x, gCoord y)
{
	X = x;
	Y = y;
	gwinMove(Image, X, Y);
}

void TransparentPainter::MoveX(gCoord x)
{
	X = x;
	gwinMove(Image, X, Y);
}

void TransparentPainter::MoveY(gCoord y)
{
	Y = y;
	gwinMove(Image, X, Y);
}

void TransparentPainter::MoveOn(gCoord dx, gCoord dy)
{
	X = X + dx;
	Y = Y + dy;
	gwinMove(Image, X, Y);
}

GHandle TransparentPainter::Create(GWidgetInit *widget)
{
	GWidgetInit NewWidget = *widget;

	X = widget->g.x;
	Y = widget->g.y;

	NewWidget.g.height = Height;
	NewWidget.g.width = Width;
	NewWidget.customDraw = Rendering;
	NewWidget.customParam = (void *) this;
	Image = gwinLabelCreate(0, &NewWidget);
	return Image;
}

void TransparentPainter::Redraw(void)
{
	gwinRedraw(Image);
}

void TransparentPainter::SetArr(const uint8_t *arr)
{
	Arr = arr;
}

void TransparentPainter::Hide(void)
{
	gwinHide(Image);
}

void TransparentPainter::Show(void)
{
	gwinShow(Image);
}

void TransparentPainter::Rendering(GWidgetObject *gw, void *param)
{
	TransparentPainter *obj = (TransparentPainter *) param;
	uint8_t *pic_arr = (uint8_t *) obj->Arr;

	if (!pic_arr)
	{
		return;
	}

	// gCoord LeftLim = gw->g.parent->x;
	// gCoord RightLim = gw->g.parent->x + gw->g.parent->width;
	// gCoord TopLim = gw->g.parent->y;
	// gCoord DownLim = gw->g.parent->y + gw->g.parent->height;

	gdispMutexEnter(gw->g.display);

	gCoord start_x = obj->Max(gw->g.parent->x, gw->g.x);
	gCoord end_x = obj->Min(gw->g.parent->x + gw->g.parent->width, gw->g.x + gw->g.width);
	gCoord start_y = obj->Max(gw->g.parent->y, gw->g.y);
	gCoord end_y = obj->Min(gw->g.parent->y + gw->g.parent->height, gw->g.y + gw->g.height);

	for (gCoord i = start_x; i < end_x; i++)
	{
		uint8_t *row_ptr = pic_arr + (i - gw->g.x);
		for (gCoord j = start_y; j < end_y; j++)
		{
			gCoord y_rel = j - gw->g.y;
			uint8_t j_row = y_rel >> 3;
			uint8_t j_pos = y_rel & 7;

			if (row_ptr[j_row * gw->g.width] & (1 << j_pos))
			{
				gdispGDrawPixelFast(gw->g.display, i, j, GFX_WHITE);
			}
		}
	}

	gdispMutexExit(gw->g.display);
}

TransparentPainter::~TransparentPainter()
{
}