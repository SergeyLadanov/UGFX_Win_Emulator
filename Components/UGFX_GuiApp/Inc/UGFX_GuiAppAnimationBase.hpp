#ifndef __UGFX_GUIAPPANIMATIONBASE_HPP_
#define __UGFX_GUIAPPANIMATIONBASE_HPP_

#include "UGFX_GuiAppBase.hpp"
#include <memory>

class UGFX_GuiAppAnimationBase : public UGFX_GuiAppBase
{
public:
	typedef enum
	{
		ANIMATION_UP_TO_DOWN = 0,
		ANIMATION_DOWN_TO_UP,
		ANIMATION_LEFT_TO_RIGHT,
		ANIMATION_RIGHT_TO_LEFT,
	} AinmatoinType;

protected:
	std::shared_ptr<UGFX_PresenterBase> NextPresenter;
	std::shared_ptr<UGFX_ScreenBase> NextScreen;
	UGFX_AppTimer Timer;
	int16_t X_Step = 0;
	int16_t Y_Step = 0;
	uint32_t TransactionPeriod = 0;
	uint32_t TransactionStepNumber = 0;

	static void AnimationTickCallBack(void *arg);
	static void AnimationEndCallBack(void *arg);

public:
	UGFX_GuiAppAnimationBase();

	void EndScreenAnimationTransaction(void);

	template <typename TApp, typename TScreen, typename TPresenter>
	void GoToScreenAnimation(uint16_t step, uint32_t period, AinmatoinType animationType = ANIMATION_UP_TO_DOWN)
	{
		static_assert(std::is_base_of<UGFX_GuiAppAnimationBase, TApp>::value, "Template parameter TApp must derive from UGFX_GuiAppAnimationBase!");
		static_assert(std::is_base_of<UGFX_ScreenBase, TScreen>::value, "Template parameter TScreen must derive from UGFX_ScreenBase!");
		static_assert(std::is_base_of<UGFX_PresenterBase, TPresenter>::value, "Template parameter TPresenter must derive from UGFX_PresenterBase!");

		NextScreen = std::make_shared<TScreen>();

		ScreenReady = false;

		int16_t StartPosY = 0;
		int16_t StartPosX = 0;
		uint32_t Length = 0;

		switch (animationType)
		{
			case ANIMATION_UP_TO_DOWN:
				StartPosY = -gdispGetHeight();
				Length = gdispGetHeight();
				X_Step = 0;
				Y_Step = ((int16_t) step);
				break;

			case ANIMATION_DOWN_TO_UP:
				StartPosY = gdispGetHeight();
				Length = gdispGetHeight();
				X_Step = 0;
				Y_Step = -((int16_t) step);
				break;

			case ANIMATION_LEFT_TO_RIGHT:
				StartPosX = -gdispGetWidth();
				Length = gdispGetWidth();
				X_Step = ((int16_t) step);
				Y_Step = 0;
				break;

			case ANIMATION_RIGHT_TO_LEFT:
				StartPosX = gdispGetWidth();
				Length = gdispGetWidth();
				X_Step = -((int16_t) step);
				Y_Step = 0;

				break;

			default:

				break;
		};

		if (NextScreen)
		{
			NextScreen->SetPos(StartPosX, StartPosY);

			NextPresenter = std::make_shared<TPresenter>(std::static_pointer_cast<TScreen>(NextScreen));
			
			if (NextPresenter)
			{
				std::static_pointer_cast<TScreen>(NextScreen)->Bind(*(TApp *) this, std::static_pointer_cast<TPresenter>(NextPresenter));
			}

			TransactionPeriod = period;
			TransactionStepNumber = Length / step;
		}
	}

	template <typename TPresenter>
	inline std::shared_ptr<TPresenter> GetNextPresenter()
	{
		return std::static_pointer_cast<TPresenter>(NextPresenter);
		
	}

	template <typename TView>
	inline TView *GetNextView()
	{
		return (TView *) NextScreen;
	}
};

#endif