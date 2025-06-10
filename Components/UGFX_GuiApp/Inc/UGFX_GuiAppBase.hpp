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
	std::shared_ptr<UGFX_ScreenBase> CurrentScreen;
	std::shared_ptr<UGFX_PresenterBase> CurrentPresenter;
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

		CurrentScreen = std::make_shared<TScreen>();//new TScreen();

		if (CurrentScreen)
		{
			
			CurrentPresenter = std::make_shared<TPresenter>(std::static_pointer_cast<TScreen>(CurrentScreen));//new TPresenter(*(TScreen *) CurrentScreen);

			if (CurrentPresenter)
			{
				std::static_pointer_cast<TScreen>(CurrentScreen)->Bind(*(TApp *) this, std::static_pointer_cast<TPresenter>(CurrentPresenter));
			}
		}
	}

	template <typename TPresenter>
	inline std::shared_ptr<TPresenter> GetCurrentPresenter()
	{
		return std::static_pointer_cast<TPresenter>(CurrentPresenter);
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