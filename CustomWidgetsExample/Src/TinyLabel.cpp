#include "TinyLabel.hpp"
#include <cstring>
#include "cp1251_converter.hpp"
#include "gfx_extended.h"
#include "src/gwin/gwin_button.h"

/* Modified black style */
const GWidgetStyle TinyLabel::SelectedWidgetStyle = {
    White,                // window background
    HTML2COLOR(0x2A8FCD), // focused

    // enabled color set
    {
        Black,                // text
        HTML2COLOR(0xC0C0C0), // edge
        HTML2COLOR(0x606060), // fill
        HTML2COLOR(0x008000)  // progress - active area
    },

    // disabled color set
    {
        HTML2COLOR(0x808080), // text
        HTML2COLOR(0x404040), // edge
        HTML2COLOR(0x404040), // fill
        HTML2COLOR(0x004000)  // progress - active area
    },

    // pressed color set
    {
        HTML2COLOR(0xFFFFFF), // text
        HTML2COLOR(0xC0C0C0), // edge
        HTML2COLOR(0xE0E0E0), // fill
        HTML2COLOR(0x008000)  // progress - active area
    },
};

TinyLabel::TinyLabel(const sFont *font) : Font(font)
{
}

GHandle TinyLabel::Create(GWidgetInit *widget)
{
	GWidgetInit NewWidget = *widget;
	X = NewWidget.g.x;
	Y = NewWidget.g.y;
	NewWidget.g.height = Font->height;
	NewWidget.g.width = strlen(NewWidget.text) * (Font->width + 1);
	NewWidget.customDraw = Rendering;
	NewWidget.customParam = (void *) this;
	Text = gwinLabelCreate(0, &NewWidget);
	// gwinSetBgColor(Text, GFX_WHITE);
	return Text;
}

void TinyLabel::SetText(char *text, TextAlignTypedef align)
{
	if (utf8_buf_to_cp1251(text, DecodeBuffer, MAX_DECODE_LINE))
	{
		gwinSetText(Text, DecodeBuffer, false);
		gwinResize(Text, (strlen(DecodeBuffer) * (Font->width + 1)) + 1, Font->height + 1);

		switch (align)
		{
			case NON_ALIGNED:

				break;

			case RIGHT_ALIGN:

				Move(Text->parent->width - GetWidth(), Y);
				break;

			case LEFT_ALIGN:
				Move(0, Y);
				break;

			case CENTER_ALIGN:
				Move((Text->parent->width - GetWidth()) >> 1, Y);
				break;

			default:
				break;
		}
	}
}

void TinyLabel::Move(gCoord x, gCoord y)
{
	gwinMove(Text, x, y);
}

gCoord TinyLabel::GetWidth(void)
{
	return gwinGetWidth(Text);
}

gCoord TinyLabel::GetHeight(void)
{
	return gwinGetHeight(Text);
}

void TinyLabel::Redraw(void)
{
	gwinRedraw(Text);
}

void TinyLabel::SetStyle(const GWidgetStyle *style)
{
	gwinSetStyle(Text, style);
}

void TinyLabel::SelectingTextOn(void)
{
	SetStyle(&SelectedWidgetStyle);
}

void TinyLabel::SelectingTextOff(void)
{
	SetStyle(gwinGetDefaultStyle());
}

TinyLabel::~TinyLabel()
{
}

void TinyLabel::Rendering(GWidgetObject *gw, void *param)
{
	const GColorSet *colors = nullptr;
	TinyLabel *obj = (TinyLabel *) param;

	gCoord LeftLim = gw->g.parent->x;
	gCoord RightLim = gw->g.parent->x + gw->g.parent->width;
	gCoord TopLim = gw->g.parent->y;
	gCoord DownLim = gw->g.parent->y + gw->g.parent->height;

	gCoord x_start = gw->g.x + 1;
	gCoord y_start = gw->g.y + 1;

	if (!gwinGetEnabled((GHandle) gw))
		colors = &gw->pstyle->disabled;
	else if ((gw->g.flags & GBUTTON_FLG_PRESSED))
		colors = &gw->pstyle->pressed;
	else
		colors = &gw->pstyle->enabled;

	// gdispFillArea(gw->g.x, gw->g.y, gw->g.width, gw->g.height, gw->g.bgcolor);

	gdispMutexEnter(gw->g.display);

	gdispGFillAreaFast(GDISP, gw->g.x, gw->g.y, gw->g.width, gw->g.height, gw->g.bgcolor);

	const gCoord font_width = obj->Font->width;
	const gCoord font_height = obj->Font->height;
	const size_t font_stride = (font_height + 7) / 8 * font_width;

	for (uint8_t c = 0; gw->text[c] != '\0'; c++)
	{
		uint8_t *pic_arr = (uint8_t *) (obj->Font->data + font_stride * ((uint8_t) gw->text[c] - obj->Font->first_character));

		// Вычисляем диапазоны x и y для текущего символа
		gCoord x_min = obj->Max(x_start, LeftLim);
		gCoord x_max = obj->Min(x_start + font_width, RightLim);
		gCoord y_min = obj->Max(y_start, TopLim);
		gCoord y_max = obj->Min(y_start + font_height, DownLim);

		for (gCoord i = x_min - x_start; i < x_max - x_start; i++)
		{
			for (gCoord j = y_min - y_start; j < y_max - y_start; j++)
			{
				uint8_t j_row = j >> 3;
				uint8_t j_pos = j % 8;

				if (pic_arr[i + j_row * font_width] & (1 << j_pos))
				{
					gdispGDrawPixelFast(gw->g.display, x_start + i, y_start + j, colors->text);
				}
			}
		}

		x_start += font_width + SYMBOL_GAP;
	}

	gdispMutexExit(gw->g.display);
}
