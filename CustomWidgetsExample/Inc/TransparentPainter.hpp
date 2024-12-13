#ifndef __TRANSPARENTPAINTER_HPP__
#define __TRANSPARENTPAINTER_HPP__

#include "gfx.h"

class TransparentPainter
{
private:
	GHandle Image = nullptr;
	const uint8_t *Arr = nullptr;
	uint8_t Width = 0;
	uint8_t Height = 0;
	gCoord X = 0, Y = 0;

public:
	TransparentPainter(uint8_t width, uint8_t height, const uint8_t *arr = nullptr);
	void Redraw(void);
	void SetArr(const uint8_t *arr);
	GHandle Create(GWidgetInit *widget);
	void Hide(void);
	void Show(void);
	void Move(gCoord x, gCoord y);
	void MoveOn(gCoord dx, gCoord dy);
	void MoveX(gCoord x);
	void MoveY(gCoord y);
	~TransparentPainter();

private:
	static void Rendering(GWidgetObject *gw, void *param);

	inline gCoord Min(gCoord a, gCoord b)
	{
		return (a < b) ? a : b;
	}

	inline gCoord Max(gCoord a, gCoord b)
	{
		return (a > b) ? a : b;
	}
};

#endif /* __TRANSPARENTPAINTER_HPP__ */
