#ifndef __UGFX_GUIAPPBASE_HPP_
#define __UGFX_GUIAPPBASE_HPP_

#include <cstdio>
#include "UGFX_AppTimer.hpp"
#include "UGFX_PresenterBase.hpp"
#include "UGFX_ScreenBase.hpp"
#include <type_traits>

class UGFX_GuiAppBase
{
protected:
	UGFX_ScreenBase *CurrentScreen = nullptr;
	UGFX_PresenterBase *CurrentPresenter = nullptr;
	GListener Gl;
	bool ScreenReady = false;

public:
	template <typename TApp, typename TScreen, typename TPresenter>
	void GoToScreen(void)
	{
		static_assert(std::is_base_of<UGFX_GuiAppBase, TApp>::value, "Template parameter TApp must derive from UGFX_GuiAppBase!");
		static_assert(std::is_base_of<UGFX_ScreenBase, TScreen>::value, "Template parameter TScreen must derive from UGFX_ScreenBase!");
		static_assert(std::is_base_of<UGFX_PresenterBase, TPresenter>::value, "Template parameter TPresenter must derive from UGFX_PresenterBase!");

		DestroyScreen();

		CurrentScreen = new TScreen();

		if (CurrentScreen)
		{
			CurrentPresenter = new TPresenter(*(TScreen *) CurrentScreen);

			if (CurrentPresenter)
			{
				((TScreen *) CurrentScreen)->Bind(*(TApp *) this, *(TPresenter *) CurrentPresenter);
			}
		}
	}

	template <typename TPresenter>
	inline TPresenter *GetCurrentPresenter()
	{
		return (TPresenter *) CurrentPresenter;
	}

	template <typename TView>
	inline TView *GetCurrentView()
	{
		return (TView *) CurrentScreen;
	}

	void Start(uint32_t task_stack = 512, gThreadpriority prio = gThreadpriorityLow);

	void DestroyScreen();

	void EndScreenTransaction(void);

protected:
	static gThreadreturn GuiTask(void *arg);

	static void EventCallBack(void *param, GEvent *pe);

	virtual void OnInitCallBack(void);

	virtual void HandleUgfxEvent(GEvent *pe);

	virtual void GuiLoop(void);
};

#endif