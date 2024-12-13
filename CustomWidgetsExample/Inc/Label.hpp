#ifndef __LABEL_HPP__
#define __LABEL_HPP__

#include "gfx.h"

class Label
{
public:
	typedef enum
	{
		NON_ALIGNED = 0,
		LEFT_ALIGN,
		RIGHT_ALIGN,
		CENTER_ALIGN
	} TextAlignTypedef;

private:
	static constexpr size_t MAX_DECODE_LINE = 32;
	static constexpr gCoord SYMBOL_GAP = 1;
	GHandle Text = nullptr;
	gCoord X = 0, Y = 0;
	// const char *FontName = "";
	gFont Font;

public:
	Label(const char *fontname = "");
	~Label();
	GHandle Create(GWidgetInit *widget);
	void SetText(char *text, TextAlignTypedef align = NON_ALIGNED);
	void Move(gCoord x, gCoord y);
	gCoord GetWidth(void);
	gCoord GetHeight(void);
	void Redraw(void);
	void SetStyle(const GWidgetStyle *style);
	void SelectingTextOn(void);
	void SelectingTextOff(void);

private:
	static void Rendering(GWidgetObject *gw, void *param);
	static const GWidgetStyle SelectedWidgetStyle;

	inline gCoord Min(gCoord a, gCoord b)
	{
		return (a < b) ? a : b;
	}

	inline gCoord Max(gCoord a, gCoord b)
	{
		return (a > b) ? a : b;
	}
};

#endif /* __LABEL_HPP__ */
