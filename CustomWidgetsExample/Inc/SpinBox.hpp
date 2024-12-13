#ifndef __SPINBOX_HPP__
#define __SPINBOX_HPP__

#include "TransparentPainter.hpp"
#include "UGFX_AppTimer.hpp"
#include "gfx.h"
#include "pictures.h"

#define SPINBOX_USE_ANIMATION 1
#define SPINBOX_USE_EXTERNAL_TIMER 1

#if SPINBOX_USE_ANIMATION == 0
#undef SPINBOX_USE_EXTERNAL_TIMER
#define SPINBOX_USE_EXTERNAL_TIMER 0
#endif

typedef enum
{
	SPINPOX_SIZE_1 = 0,
	SPINPOX_SIZE_2
} SpinpoxSizesTypedef;

template <SpinpoxSizesTypedef SIZE = SPINPOX_SIZE_1>
class SpinBox
{
private:
	static constexpr uint8_t WIDTH = (SIZE == SPINPOX_SIZE_1) ? 11 : 19;
	static constexpr uint8_t HEIGHT = (SIZE == SPINPOX_SIZE_1) ? 16 : 24;
	static constexpr uint8_t HORIZONTAL_GAP = 2;
	static constexpr uint8_t VERTICAL_GAP = (SIZE == SPINPOX_SIZE_1) ? 2 : 3;
	static constexpr uint8_t ANIMATION_STEP = (SIZE == SPINPOX_SIZE_1) ? 2 : 3;
	static constexpr uint8_t ANIMATION_PERIOD_MS = 30;
	static constexpr size_t ARR_SIZE = (SIZE == SPINPOX_SIZE_1) ? sizeof(dig_size_2[0]) : sizeof(dig_size_3[0]);

	static constexpr const uint8_t (*DigArr)[ARR_SIZE] = []() -> const uint8_t (*)[ARR_SIZE]
	{
		if constexpr (SIZE == SPINPOX_SIZE_1)
		{
			return dig_size_2;
		}
		else
		{
			return dig_size_3;
		}
	}();

	GHandle Container, Dozens, Units;
	TransparentPainter DozPic, UnitPic;
	uint8_t PrevVal = 0;
#if SPINBOX_USE_ANIMATION != 0
#if SPINBOX_USE_EXTERNAL_TIMER == 0
	UGFX_AppTimer Timer;
#endif
	TransparentPainter PrevDozPic, PrevUnitPic;
	gCoord DozOffset = -1;
	gCoord UnOffset = -1;
#if SPINBOX_USE_EXTERNAL_TIMER != 0
	uint32_t ExternalTimerCounter = 0;
#endif
#endif
public:
	SpinBox()
	    : DozPic(WIDTH, HEIGHT),
	      UnitPic(WIDTH, HEIGHT)
#if SPINBOX_USE_ANIMATION != 0
	      ,
	      PrevDozPic(WIDTH, HEIGHT),
	      PrevUnitPic(WIDTH, HEIGHT)
#endif
	{
#if SPINBOX_USE_ANIMATION != 0
#if SPINBOX_USE_EXTERNAL_TIMER == 0
		Timer.SetArg(this);
		Timer.SetTickCallBack(AnimationTickCallBack);
		Timer.SetEndCallBack(AnimationEndCallBack);
#endif
#endif
	}

	GHandle Create(GWidgetInit *widget)
	{
		GWidgetInit NewWidget = *widget;
		NewWidget.g.width = (2 * WIDTH) + HORIZONTAL_GAP;
		NewWidget.g.height = HEIGHT;
		Container = gwinContainerCreate(0, &NewWidget, 0);

		NewWidget.g.show = true;
		NewWidget.g.y = 0;
		NewWidget.g.x = 0;
		NewWidget.g.parent = Container;
		DozPic.SetArr(DigArr[0]);
		DozPic.Create(&NewWidget);

		NewWidget.g.show = true;
		NewWidget.g.y = 0;
		NewWidget.g.x = WIDTH + 2;
		NewWidget.g.parent = Container;
		UnitPic.SetArr(DigArr[0]);
		UnitPic.Create(&NewWidget);

#if SPINBOX_USE_ANIMATION != 0
		NewWidget.g.show = false;
		NewWidget.g.y = 0;
		NewWidget.g.x = 0;
		NewWidget.g.parent = Container;
		PrevDozPic.SetArr(DigArr[0]);
		PrevDozPic.Create(&NewWidget);
		// PrevDozPic.Show();

		NewWidget.g.show = false;
		NewWidget.g.y = 0;
		NewWidget.g.x = WIDTH + HORIZONTAL_GAP;
		NewWidget.g.parent = Container;
		PrevUnitPic.SetArr(DigArr[0]);
		PrevUnitPic.Create(&NewWidget);
		// PrevUnitPic.Show();
#endif
		return Container;
	}

#if SPINBOX_USE_ANIMATION != 0
	bool SetValueAnimation(uint8_t val)
	{
		bool ChangeFlag = false;
		uint8_t prev_dozens = (PrevVal / 10) % 10;
		uint8_t prev_units = PrevVal % 10;

		uint8_t dozens = (val / 10) % 10;
		uint8_t units = val % 10;
		UnitPic.SetArr(DigArr[units]);
		DozPic.SetArr(DigArr[dozens]);

		PrevDozPic.SetArr(DigArr[prev_dozens]);
		PrevUnitPic.SetArr(DigArr[prev_units]);

		if (prev_dozens != dozens)
		{
			DozOffset = HEIGHT + VERTICAL_GAP;
			PrevDozPic.MoveY(0);
			DozPic.MoveY(DozOffset);
			PrevDozPic.Show();
			ChangeFlag = true;
		}

		if (prev_units != units)
		{
			UnOffset = HEIGHT + VERTICAL_GAP;
			PrevUnitPic.MoveY(0);
			UnitPic.MoveY(UnOffset);
			PrevUnitPic.Show();
			ChangeFlag = true;
		}

#if SPINBOX_USE_EXTERNAL_TIMER == 0
		if (ChangeFlag)
		{
			Timer.Start(ANIMATION_PERIOD_MS, ((HEIGHT + VERTICAL_GAP) / ANIMATION_STEP) + 1);
		}
#else
		if (ChangeFlag)
		{
			ExternalTimerCounter = ((HEIGHT + VERTICAL_GAP) / ANIMATION_STEP) + 1;
		}
#endif

		PrevVal = val;
		return ChangeFlag;
	}
#endif

	bool SetValue(uint8_t val)
	{

		bool ChangeFlag = false;
		uint8_t prev_dozens = (PrevVal / 10) % 10;
		uint8_t prev_units = PrevVal % 10;

		uint8_t dozens = (val / 10) % 10;
		uint8_t units = val % 10;

		UnitPic.SetArr(DigArr[units]);
		DozPic.SetArr(DigArr[dozens]);

		gwinRedraw(Container);

		if (prev_dozens != dozens)
		{
			ChangeFlag = true;
		}

		if (prev_units != units)
		{
			ChangeFlag = true;
		}

		PrevVal = val;
		return ChangeFlag;
	}

	~SpinBox()
	{
		GHandle child;

		for (child = gwinGetFirstChild(Container); child; child = gwinGetFirstChild(Container))
		{
			gwinDestroy(child);
		}

		gwinDestroy(Container);
	}

#if SPINBOX_USE_ANIMATION != 0
#if SPINBOX_USE_EXTERNAL_TIMER != 0
	uint8_t GetAnimationStepCount(void)
	{
		return ((HEIGHT + VERTICAL_GAP) / ANIMATION_STEP) + 1;
	}

	void ExternalTimeProccess(void)
	{

		if (ExternalTimerCounter)
		{
			AnimationTickCallBack(this);

			if (ExternalTimerCounter == 1)
			{
				AnimationEndCallBack(this);
			}

			ExternalTimerCounter--;
		}
	}
#endif

private:
	static void AnimationTickCallBack(void *arg)
	{

		SpinBox *obj = (SpinBox *) arg;

		if (obj->DozOffset >= 0)
		{
			obj->PrevDozPic.MoveY(obj->DozOffset - (HEIGHT + VERTICAL_GAP));
			obj->DozPic.MoveY(obj->DozOffset);
			obj->DozOffset -= ANIMATION_STEP;
			// gwinRedraw(obj->Container);
		}

		if (obj->UnOffset >= 0)
		{
			obj->PrevUnitPic.MoveY(obj->UnOffset - (HEIGHT + VERTICAL_GAP));
			obj->UnitPic.MoveY(obj->UnOffset);
			obj->UnOffset -= ANIMATION_STEP;
			// gwinRedraw(obj->Container);
		}

		// gwinFlash(obj->Container);
	}

	static void AnimationEndCallBack(void *arg)
	{
		SpinBox *obj = (SpinBox *) arg;
		// obj->PrevDozPic.Hide();
		// obj->PrevUnitPic.Hide();
		obj->DozOffset = -1;
		obj->UnOffset = -1;
	}
#endif
};

#endif /* __SPINBOX_HPP__ */
