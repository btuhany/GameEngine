#pragma once
#include <functional>
#include "InputController.h"
#include "../Data/MainMenuButtonType.h"
namespace BreakoutGame
{
	class MainMenuController : public InputController
	{
	public:
		MainMenuController(
			std::function<void()> startButtonClickHandler,
			std::function<void()> helpButtonClickHandler,
			std::function<void()> quitButtonClickHandler,
			std::function<void(MainMenuButtonType)> m_OnMainMenuButtonSelected);
		void OnActivated();
		void HandleInputs(InputType inputType) override;
	private:
		std::function<void()> m_OnStartButtonClick;
		std::function<void()> m_OnHelpButtonClick;
		std::function<void()> m_OnQuitButtonClick;
		std::function<void(MainMenuButtonType)> m_OnMainMenuButtonSelected;
		bool m_CanSelectButtons = false;
		int m_CurrentButtonIndex;
		static const int BUTTON_COUNT = 3;
		bool m_IsAnyButtonClick = false;
		const MainMenuButtonType m_ButtonOrder[BUTTON_COUNT] = {
			MainMenuButtonType::Start,
			MainMenuButtonType::Help,
			MainMenuButtonType::Quit,
		};
	};
}

