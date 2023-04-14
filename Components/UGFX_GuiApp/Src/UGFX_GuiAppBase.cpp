#include "UGFX_GuiAppBase.hpp"

void UGFX_GuiAppBase::EventCallBack(void *param, GEvent *pe)
{
    UGFX_GuiAppBase* obj = (UGFX_GuiAppBase *) param;

    if (obj->CurrentScreen)
    {
        if (obj->ScreenReady)
        {
            obj->CurrentScreen->HandleUgfxEvent(pe);
        }  
    }

    obj->HandleUgfxEvent(pe);
}


gThreadreturn UGFX_GuiAppBase::GuiTask(void *arg)
{
    UGFX_GuiAppBase* obj = (UGFX_GuiAppBase *) arg;

    gfxInit();
    geventListenerInit(&obj->Gl);
    geventRegisterCallback(&obj->Gl, EventCallBack, obj);
    gwinAttachListener(&obj->Gl);
    obj->OnInitCallBack();

    for(;;)
    {
        obj->GuiLoop();
    }

    gfxThreadReturn(0);
}


void UGFX_GuiAppBase::Start(uint32_t task_stack, gThreadpriority prio)
{
    gfxThreadCreate(nullptr, task_stack, prio, GuiTask, this);
}


void UGFX_GuiAppBase::DestroyScreen()
{
    ScreenReady = false;
    if (CurrentPresenter)
    {
        CurrentPresenter->DeActivate();
        delete CurrentPresenter;
        CurrentPresenter = nullptr;
    }

    if (CurrentScreen)
    {
        CurrentScreen->OnExitScreen();
        delete CurrentScreen;
        CurrentScreen = nullptr;
    }
}


void UGFX_GuiAppBase::EndScreenTransaction(void)
{
    CurrentScreen->OnSetupScreen();

    CurrentPresenter->Activate();

    CurrentScreen->Show();

    ScreenReady = true;
}


void UGFX_GuiAppBase::OnInitCallBack(void)
{

}


void UGFX_GuiAppBase::HandleUgfxEvent(GEvent* pe)
{

}

void UGFX_GuiAppBase::GuiLoop(void)
{
    gfxSleepMilliseconds(500);
}