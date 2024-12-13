#include "ScrollMenuContainer.hpp"
#include <cstring>

ScrollMenuContainer::ScrollMenuContainer(Item_t *items_array)
    : ItemText(&Font5x8),
      Icons {
          {32, 32},
          {32, 32},
          {32, 32},
          {32, 32},
      },
      Items_Array(items_array),
      SelectionUp(36, 8, selection[0]),
      SelectionDown(36, 8, selection[1])
{
	if (Items_Array != nullptr)
	{
		for (uint8_t i = 0; Items_Array[i].Icon != nullptr; i++)
		{
			ArraySize++;
		}
	}
}

void ScrollMenuContainer::SetItemsArray(Item_t *icons_array)
{
	Items_Array = icons_array;
}

void ScrollMenuContainer::ChangeIcon(uint8_t index, const uint8_t *icon)
{
	Items_Array[index].Icon = icon;

	for (uint8_t i = 0; i < 3; i++)
	{
		Icons[i].Redraw();
	}
}

GHandle ScrollMenuContainer::Create(GWidgetInit *widget)
{
	GWidgetInit NewWidget = *widget;
	NewWidget.g.height = HEIGHT;
	NewWidget.g.width = WIDTH;

	Container = gwinContainerCreate(0, &NewWidget, 0);

	NewWidget.g.y = 4;
	NewWidget.g.x = 0;
	NewWidget.g.parent = Container;

	for (uint8_t i = 0; i < 4; i++)
	{
		// NewWidget.g.x = 8 + i * 40;
		// Icons[i].SetArr(Icons_Array[i]);
		Icons[i].Create(&NewWidget);
		Icons[i].MoveX(i * ICONS_OFFSET);
	}

	NewWidget.g.x = 46;
	NewWidget.g.y = 0;

	SelectionUp.Create(&NewWidget);

	NewWidget.g.y = HEIGHT - 18;
	SelectionDown.Create(&NewWidget);

	NewWidget.g.y = 41;
	NewWidget.g.x = 52;

	NewWidget.g.width = 32;
	NewWidget.g.height = 10;
	NewWidget.text = "";

	ItemText.Create(&NewWidget);
	UpdateItemText(0);

	Redraw();
	Timer.SetArg(this);
	Timer.SetEndCallBack(AnimationEndCallBack);
	Timer.SetTickCallBack(AnimationTickCallBack);

	return Container;
}

void ScrollMenuContainer::SetSelectedIndex(uint8_t index)
{
	if (index < ArraySize)
	{
		Index = index;
		TargetIndex = index;
		SetDefaultPosition(false);
	}
}

uint8_t ScrollMenuContainer::GetSelectedindex(void)
{
	return GetIndex();
}

ScrollMenuContainer::~ScrollMenuContainer()
{
	GHandle child;

	for (child = gwinGetFirstChild(Container); child; child = gwinGetFirstChild(Container))
	{
		gwinDestroy(child);
	}

	gwinDestroy(Container);
}

void ScrollMenuContainer::SwitchNext(void)
{
	Index = GetNextIndex(Index);
	Redraw();
}

void ScrollMenuContainer::SwitchNextAnimation(void)
{
	if (AnimationDirection == ANIMATION_NONE)
	{
		TargetIndex = GetNextIndex(Index);

		if (TargetIndex != Index)
		{
			if ((GetNextIndex(Index) < Index))
			{
				AnimationDirection = ANIMATION_RIGHT;
				AnimationStep = ANIMATION_STEP_X2;
				Index = GetPreviousIndex(Index);
			}
			else
			{
				AnimationDirection = ANIMATION_LEFT;
				AnimationStep = ANIMATION_STEP;
				Index = GetNextIndex(Index);
			}
		}

		RedrawAnimation();
	}
}

void ScrollMenuContainer::SwitchPrevAnimation(void)
{

	if (AnimationDirection == ANIMATION_NONE)
	{
		TargetIndex = GetPreviousIndex(Index);

		if (TargetIndex != Index)
		{
			if ((GetPreviousIndex(Index) > Index))
			{
				AnimationDirection = ANIMATION_LEFT;
				AnimationStep = ANIMATION_STEP_X2;
				Index = GetNextIndex(Index);
			}
			else
			{
				AnimationDirection = ANIMATION_RIGHT;
				AnimationStep = ANIMATION_STEP;
				Index = GetPreviousIndex(Index);
			}
		}

		RedrawAnimation();
	}
}

void ScrollMenuContainer::SwitchPrevious(void)
{
	Index = GetPreviousIndex(Index);
	Redraw();
}

void ScrollMenuContainer::UpdateItemText(uint8_t index)
{
	const char *text = Items_Array[index].Text;
	ItemText.SetText((char *) text, TinyLabel::CENTER_ALIGN);
}

void ScrollMenuContainer::PrepareOffScreenIcon(void)
{
	if ((GetNextIndex(Index) <= Index) || (GetPreviousIndex(Index) >= Index))
	{
		Icons[3].Hide();
	}
	else
	{
		Icons[3].Show();
	}

	if (AnimationDirection == ANIMATION_RIGHT)
	{
		Icons[3].SetArr(Items_Array[GetPreviousIndex(Index)].Icon);
		Icons[3].MoveX(-ICONS_OFFSET);
	}

	if (AnimationDirection == ANIMATION_LEFT)
	{
		Icons[3].SetArr(Items_Array[GetNextIndex(Index)].Icon);
		Icons[3].MoveX(ICONS_OFFSET * 3);
	}
}

void ScrollMenuContainer::RedrawAnimation(void)
{
	Offset = 0;

	uint32_t Ticks = ICONS_OFFSET / AnimationStep;

	if (AnimationStep == ANIMATION_STEP_X2)
	{
		Ticks = Ticks * (ArraySize - 1);
	}

	PrepareOffScreenIcon();

	Timer.Start(ANIMATION_PERIOD_MS, Ticks);
}

void ScrollMenuContainer::SetDefaultPosition(bool rstOffscreenIcon)
{
	Offset = 0;
	uint8_t icon_cnt = 4;

	if (!rstOffscreenIcon)
	{
		icon_cnt--;
	}
	// Icons[3].Hide();
	if (GetPreviousIndex(Index) >= Index)
	{
		Icons[0].Hide();
	}
	else
	{
		Icons[0].Show();
	}

	if (GetNextIndex(Index) <= Index)
	{
		Icons[2].Hide();
	}
	else
	{
		Icons[2].Show();
	}

	Icons[0].SetArr(Items_Array[GetPreviousIndex(Index)].Icon);
	Icons[1].SetArr(Items_Array[GetIndex()].Icon);
	// UpdateItemText(GetIndex());
	Icons[2].SetArr(Items_Array[GetNextIndex(Index)].Icon);

	for (uint8_t i = 0; i < icon_cnt; i++)
	{
		Icons[i].MoveX((i * ICONS_OFFSET) + Offset);
	}

	// Icons[3].Redraw();
}

void ScrollMenuContainer::Redraw(void)
{
	Icons[0].SetArr(Items_Array[GetPreviousIndex(Index)].Icon);
	Icons[1].SetArr(Items_Array[GetIndex()].Icon);
	Icons[2].SetArr(Items_Array[GetNextIndex(Index)].Icon);

	if (GetPreviousIndex(Index) >= Index)
	{
		Icons[0].Hide();
	}
	else
	{
		Icons[0].Show();
	}

	if (GetNextIndex(Index) <= Index)
	{
		Icons[2].Hide();
	}
	else
	{
		Icons[2].Show();
	}

	gwinRedraw(Container);

	Icons[0].Redraw();
	Icons[1].Redraw();
	Icons[2].Redraw();
	SelectionUp.Redraw();
	SelectionDown.Redraw();
	UpdateItemText(GetIndex());
}

void ScrollMenuContainer::AnimationTickCallBack(void *arg)
{
	ScrollMenuContainer *obj = (ScrollMenuContainer *) arg;

	gCoord Step = 0;

	if (obj->Offset <= -ICONS_OFFSET)
	{
		obj->SetDefaultPosition(false);
		obj->Index++;
		obj->PrepareOffScreenIcon();
	}

	if (obj->Offset >= ICONS_OFFSET)
	{
		obj->SetDefaultPosition(false);
		obj->Index--;
		obj->PrepareOffScreenIcon();
	}

	if ((obj->Offset > -ICONS_OFFSET) && (obj->AnimationDirection == ANIMATION_LEFT))
	{
		obj->Offset -= obj->AnimationStep;
		Step = -obj->AnimationStep;
	}

	if ((obj->Offset < ICONS_OFFSET) && (obj->AnimationDirection == ANIMATION_RIGHT))
	{
		obj->Offset += obj->AnimationStep;
		Step = obj->AnimationStep;
	}

	for (uint8_t i = 0; i < 4; i++)
	{
		obj->Icons[i].MoveOn(Step, 0);
	}
}

void ScrollMenuContainer::AnimationEndCallBack(void *arg)
{
	ScrollMenuContainer *obj = (ScrollMenuContainer *) arg;
	obj->SetDefaultPosition();
	obj->UpdateItemText(obj->GetIndex());
	obj->AnimationDirection = ANIMATION_NONE;
}