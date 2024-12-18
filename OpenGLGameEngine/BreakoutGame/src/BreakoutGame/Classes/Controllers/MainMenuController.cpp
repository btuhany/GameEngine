#include "MainMenuController.h"

namespace BreakoutGame
{
	const int BUTTON_COUNT = 3;
	MainMenuController::MainMenuController(std::function<void()> startButtonClickHandler, std::function<void()> helpButtonClickHandler, std::function<void()> quitButtonClickHandler, std::function<void(MainMenuButtonType)> onMainMenuButtonSelectedHandler)
	{
		m_OnStartButtonClick = startButtonClickHandler;
		m_OnHelpButtonClick = helpButtonClickHandler;
		m_OnQuitButtonClick = quitButtonClickHandler;
		m_OnMainMenuButtonSelected = onMainMenuButtonSelectedHandler;
		OnActivated();
	}
	void MainMenuController::OnActivated()
	{
		m_CurrentButtonIndex = -1;
		m_CanSelectButtons = false;
		m_IsAnyButtonClick = false;
	}
	void MainMenuController::HandleInputs(InputType inputType)
	{
		if (!m_CanSelectButtons)
		{
			if (inputType == InputType::EnterKey_Release || inputType == InputType::DownArrow_Release)
			{
				m_CanSelectButtons = true;
				m_CurrentButtonIndex = 0;
			}
			return;
		}

		if (inputType == InputType::DownArrow_Release)
		{
			m_CurrentButtonIndex++;
			if (m_CurrentButtonIndex >= BUTTON_COUNT)
			{
				m_CurrentButtonIndex = 0;
			}
		}
		else if (inputType == InputType::UpArrow_Release)
		{
			m_CurrentButtonIndex--;
			if (m_CurrentButtonIndex < 0)
			{
				m_CurrentButtonIndex = BUTTON_COUNT - 1;
			}
		}
		else if (inputType == InputType::EnterKey_Release)
		{
			if (m_ButtonOrder[m_CurrentButtonIndex] == MainMenuButtonType::Start)
			{
				m_IsAnyButtonClick = true;
				m_OnStartButtonClick();
			}
			else if (m_ButtonOrder[m_CurrentButtonIndex] == MainMenuButtonType::Help)
			{
				m_IsAnyButtonClick = true;
				m_OnHelpButtonClick();
			}
			else if (m_ButtonOrder[m_CurrentButtonIndex] == MainMenuButtonType::Quit)
			{
				m_OnQuitButtonClick();
				m_IsAnyButtonClick = true;
			}
			return;
		}
	}
}
