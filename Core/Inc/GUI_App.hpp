#ifndef __GUI_APP_HPP_
#define __GUI_APP_HPP_

#include "UGFX_GuiAppAnimationBase.hpp"
#include "Model.hpp"

class GUI_App : public UGFX_GuiAppAnimationBase
{
private:
    Model &ModelRef;

    void OnInitCallBack(void) override;

public:
    GUI_App(Model &model)
        : ModelRef(model)
    {

    }


    template <typename TScreen, typename TPresenter>
    void GoToScreen(void)
    {
        UGFX_GuiAppAnimationBase::GoToScreen<typeof(*this), TScreen, TPresenter>();
        GetCurrentPresenter<TPresenter>()->BindModel(&ModelRef);
        EndScreenTransaction();
    }


    template <typename TScreen, typename TPresenter>
    void GoToScreenAnimation(void)
    {
        UGFX_GuiAppAnimationBase::GoToScreenAnimation<typeof(*this), TScreen, TPresenter>(20, 20, ANIMATION_RIGHT_TO_LEFT);
        GetNextPresenter<TPresenter>()->BindModel(&ModelRef);
        EndScreenAnimationTransaction();
    }
    
    void GoToMainScreen(void);
    void GoToMainScreenAnimation(void);
    void GoToScreen2(void);
    void GoToScreen2Animation(void);
};



#endif