#ifndef __UGFX_SCREENBASE_HPP_
#define __UGFX_SCREENBASE_HPP_

#include <cstdio>
#include "gfx.h"

class UGFX_ScreenBase
{
protected:
	GHandle Container;
	GWidgetInit Widget;

public:
	UGFX_ScreenBase()
	{
		gwinWidgetClearInit(&Widget);
		Widget.g.show = FALSE;
		Widget.g.width = gdispGetWidth();
		Widget.g.height = gdispGetHeight();
		Widget.g.y = 0;
		Widget.g.x = 0;
		Widget.text = "";
		Container = gwinContainerCreate(0, &Widget, 0);
		Widget.g.parent = Container;
	}

	void Show(void)
	{
		gwinShow(Container);
	}

	void Hide(void)
	{
		gwinHide(Container);
	}

	void MoveOn(int16_t dx, int16_t dy)
	{
		int16_t x = gwinGetScreenX(Container);
		int16_t y = gwinGetScreenY(Container);

		x = x + dx;
		y = y + dy;

		SetPos(x, y);
	}

	void SetPos(int16_t x, int16_t y)
	{
		gwinMove(Container, x, y);
	}

	virtual void HandleUgfxEvent(GEvent *pe)
	{
	}

	virtual void OnSetupScreen(void)
	{
	}

	virtual void OnExitScreen(void)
	{
	}

	virtual void HandleHardwareInput(uint8_t key)
	{
	}

	virtual ~UGFX_ScreenBase()
	{
		GHandle child;

		for (child = gwinGetFirstChild(Container); child; child = gwinGetFirstChild(Container))
		{
			gwinDestroy(child);
		}

		gwinDestroy(Container);
	}
};

#endif
