#ifndef __TINYLABEL_HPP__
#define __TINYLABEL_HPP__

#include "fonts.h"
#include "gfx.h"

class TinyLabel
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
	const sFont *Font;
	char DecodeBuffer[MAX_DECODE_LINE];
	gCoord X = 0, Y = 0;

public:
	TinyLabel(const sFont *font);
	~TinyLabel();
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

#endif /* __TINYLABEL_HPP__ */
