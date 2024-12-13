#include "Label.hpp"
#include <cstring>
// #include "src/gwin/gwin_button.h"

/* Modified black style */
const GWidgetStyle Label::SelectedWidgetStyle = {
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

Label::Label(const char *fontname)
{
	if (fontname[0] == '\0')
	{
		Font = gwinGetDefaultFont();
	}
	else
	{
		Font = gdispOpenFont(fontname);
	}
}

GHandle Label::Create(GWidgetInit *widget)
{
	GWidgetInit NewWidget = *widget;
	X = NewWidget.g.x;
	Y = NewWidget.g.y;
	NewWidget.g.height = gdispGetFontMetric(Font, gFontHeight);
	NewWidget.g.width
	    = strlen(NewWidget.text) * (gdispGetFontMetric(Font, gFontMaxWidth) + gdispGetFontMetric(Font, gFontCharPadding));
	NewWidget.g.width = NewWidget.g.width + 1;
	Text = gwinLabelCreate(0, &NewWidget);
	gwinSetFont(Text, Font);
	// gwinSetBgColor(Text, GFX_WHITE);
	return Text;
}

void Label::SetText(char *text, TextAlignTypedef align)
{

	gwinSetText(Text, text, false);
	gwinResize(Text, (strlen(text) * (gdispGetFontMetric(Font, gFontMaxWidth) + gdispGetFontMetric(Font, gFontCharPadding))) + 1,
	           gdispGetFontMetric(Font, gFontHeight));

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

void Label::Move(gCoord x, gCoord y)
{
	gwinMove(Text, x, y);
}

gCoord Label::GetWidth(void)
{
	return gwinGetWidth(Text);
}

gCoord Label::GetHeight(void)
{
	return gwinGetHeight(Text);
}

void Label::Redraw(void)
{
	gwinRedraw(Text);
}

void Label::SetStyle(const GWidgetStyle *style)
{
	gwinSetStyle(Text, style);
}

void Label::SelectingTextOn(void)
{
	SetStyle(&SelectedWidgetStyle);
}

void Label::SelectingTextOff(void)
{
	SetStyle(gwinGetDefaultStyle());
}

Label::~Label()
{
}
