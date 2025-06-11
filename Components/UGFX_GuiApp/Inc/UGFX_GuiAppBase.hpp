#ifndef __UGFX_GUIAPPBASE_HPP_
#define __UGFX_GUIAPPBASE_HPP_

#include <cstdio>
#include "UGFX_AppTimer.hpp"
#include "UGFX_PresenterBase.hpp"
#include "UGFX_ScreenBase.hpp"
#include <type_traits>
#include <memory>

class UGFX_GuiAppBase
{
protected:
	std::unique_ptr<UGFX_ScreenBase> CurrentScreen = nullptr;
	std::unique_ptr<UGFX_PresenterBase> CurrentPresenter = nullptr;
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

		CurrentScreen = std::make_unique<TScreen>();

		if (CurrentScreen)
		{
			CurrentPresenter = std::make_unique<TPresenter>(*static_cast<TScreen *>(CurrentScreen.get()));

			if (CurrentPresenter)
			{
				static_cast<TScreen *>(CurrentScreen.get())->Bind(*static_cast<TApp *>(this), *static_cast<TPresenter *>(CurrentPresenter.get()));
			}
		}
	}

	template <typename TPresenter>
	inline TPresenter *GetCurrentPresenter()
	{
		return static_cast<TPresenter *>(CurrentPresenter.get());
	}

	template <typename TView>
	inline TView *GetCurrentView()
	{
		return static_cast<TView *>(CurrentScreen.get());
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