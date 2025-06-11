#include "UGFX_GuiAppAnimationBase.hpp"

UGFX_GuiAppAnimationBase::UGFX_GuiAppAnimationBase()
{
	Timer.SetArg(this);
	Timer.SetTickCallBack(AnimationTickCallBack);
	Timer.SetEndCallBack(AnimationEndCallBack);
}

void UGFX_GuiAppAnimationBase::AnimationTickCallBack(void *arg)
{
	UGFX_GuiAppAnimationBase *obj = (UGFX_GuiAppAnimationBase *) arg;

	if (obj->NextScreen)
	{
		obj->NextScreen->MoveOn(obj->X_Step, obj->Y_Step);
		obj->CurrentScreen->MoveOn(obj->X_Step, obj->Y_Step);
	}
}

void UGFX_GuiAppAnimationBase::AnimationEndCallBack(void *arg)
{
	UGFX_GuiAppAnimationBase *obj = (UGFX_GuiAppAnimationBase *) arg;

	obj->DestroyScreen();

	obj->CurrentPresenter = std::move(obj->NextPresenter);

	obj->CurrentScreen = std::move(obj->NextScreen);

	obj->CurrentScreen->SetPos(0, 0);

	obj->ScreenReady = true;
}

void UGFX_GuiAppAnimationBase::EndScreenAnimationTransaction(void)
{
	NextScreen->OnSetupScreen();

	NextPresenter->Activate();

	NextScreen->Show();

	Timer.Start(TransactionPeriod, TransactionStepNumber);
}