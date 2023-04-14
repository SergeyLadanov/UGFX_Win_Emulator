#ifndef __UGFX_VIEWBASE_HPP_
#define __UGFX_VIEWBASE_HPP_

#include "UGFX_ScreenBase.hpp"


template <typename AppType, typename PresenterType>
class UGFX_ViewBase : public UGFX_ScreenBase
{
protected:
    AppType *Application;
    PresenterType *Presenter;

public:
    UGFX_ViewBase()
        : Application(0), Presenter(0)
    {

    }

    void Bind(AppType& app, PresenterType& pressenter)
    {
        Application = &app;
        Presenter = &pressenter;
    }

};



#endif