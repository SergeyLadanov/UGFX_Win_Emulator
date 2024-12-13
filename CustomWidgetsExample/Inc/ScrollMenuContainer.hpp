#ifndef __SCROLLMENUCONTAINER_HPP__
#define __SCROLLMENUCONTAINER_HPP__

#include "TinyLabel.hpp"
#include "TransparentPainter.hpp"
#include "UGFX_AppTimer.hpp"
#include "gfx.h"
#include "pictures.h"

class ScrollMenuContainer
{
public:
	struct Item_t
	{
		const uint8_t *Icon;
		const char *Text;
	};

private:
	typedef enum
	{
		ANIMATION_NONE = 0,
		ANIMATION_LEFT,
		ANIMATION_RIGHT
	} AnimationDirection_t;

	static constexpr uint32_t ANIMATION_PERIOD_MS = 15;
	static constexpr uint8_t WIDTH = 128;
	static constexpr uint8_t HEIGHT = 50;
	static constexpr uint8_t ICON_WIDTH = 32;
	static constexpr uint8_t ICON_HEIGHT = 32;
	static constexpr uint8_t ICON_GAP = ICON_WIDTH >> 1;
	static constexpr gCoord ICONS_OFFSET = ICON_WIDTH + ICON_GAP;
	static constexpr uint8_t ANIMATION_STEP = 8;
	static constexpr uint8_t ANIMATION_STEP_X2 = ANIMATION_STEP * 2;

	GHandle Container = nullptr;
	TinyLabel ItemText;
	TransparentPainter Icons[4];
	Item_t *Items_Array = nullptr;
	TransparentPainter SelectionUp;
	TransparentPainter SelectionDown;
	uint8_t Index = 0;
	uint8_t ArraySize = 0;
	UGFX_AppTimer Timer;
	gCoord Offset = 0;
	gCoord AnimationStep = ANIMATION_STEP;
	AnimationDirection_t AnimationDirection = ANIMATION_NONE;
	uint8_t TargetIndex = 0;

public:
	ScrollMenuContainer(Item_t *items_array = nullptr);
	GHandle Create(GWidgetInit *widget);
	void SetItemsArray(Item_t *items_array);
	void ChangeIcon(uint8_t index, const uint8_t *icon);
	void SetSelectedIndex(uint8_t index);
	uint8_t GetSelectedindex(void);
	void SwitchNext(void);
	void SwitchPrevious(void);
	void SwitchNextAnimation(void);
	void SwitchPrevAnimation(void);
	void Redraw(void);
	~ScrollMenuContainer();

private:
	inline uint8_t GetPreviousIndex(uint8_t val)
	{
		return ((val + (ArraySize - 1)) % ArraySize);
	}

	inline uint8_t GetNextIndex(uint8_t val)
	{
		return ((val + 1) % ArraySize);
	}

	inline uint8_t GetIndex(void)
	{
		return Index;
	}

	inline uint8_t GetTargetIndex(void)
	{
		return TargetIndex;
	}

	void UpdateItemText(uint8_t index);

	void PrepareOffScreenIcon(void);

	void SetDefaultPosition(bool rstOffscreenIcon = true);

	void RedrawAnimation(void);

	static void AnimationTickCallBack(void *arg);

	static void AnimationEndCallBack(void *arg);
};

#endif /* __SCROLLMENUCONTAINER_HPP__ */
