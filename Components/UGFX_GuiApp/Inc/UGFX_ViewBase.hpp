#ifndef __UGFX_VIEWBASE_HPP_
#define __UGFX_VIEWBASE_HPP_

#include "UGFX_ScreenBase.hpp"
#include "UGFX_GuiAppBase.hpp"
#include <type_traits>

template <typename AppType, typename PresenterType>
class UGFX_ViewBase : public UGFX_ScreenBase
{
	static_assert(std::is_base_of<UGFX_GuiAppBase, AppType>::value, "Template parameter AppType must derive from UGFX_GuiAppBase!");
protected:
	AppType *Application;
	std::weak_ptr<PresenterType> Presenter;

public:
	UGFX_ViewBase() : Application(0)
	{
	}

	void Bind(AppType &app, std::weak_ptr<PresenterType> pressenter)
	{
		Application = &app;
		Presenter = pressenter;
	}
};

#endif