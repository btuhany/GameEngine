#include "MainMenuStateController.h"

namespace BreakoutGame
{
	const int BUTTON_COUNT = 3;
	MainMenuStateController::MainMenuStateController(std::shared_ptr<UIManager> uiManager, std::function<void()> startButtonClickHandler,
		std::function<void()> quitButtonClickHandler)
	{
		m_UIManager = uiManager;
		m_OnStartButtonClick = startButtonClickHandler;
		m_OnQuitButtonClick = quitButtonClickHandler;
	}
	void MainMenuStateController::HandleOnActivated()
	{
		resetState();
		m_UIManager->ShowMainMenuPanel();
	}
	void MainMenuStateController::HandleOnDeactivated()
	{
		resetState();
		m_UIManager->HideMainMenuPanel();;
	}
	void MainMenuStateController::HandleInputs(InputType inputType)
	{
		if (!m_CanSelectButtons)
		{
			if (inputType == InputType::EnterKey_Release || inputType == InputType::DownArrow_Release)
			{
				m_CanSelectButtons = true;
				m_CurrentButtonIndex = 0;
				m_UIManager->SelectMainMenuButton(m_ButtonOrder[m_CurrentButtonIndex]);
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
			m_UIManager->SelectMainMenuButton(m_ButtonOrder[m_CurrentButtonIndex]);
		}
		else if (inputType == InputType::UpArrow_Release)
		{
			m_CurrentButtonIndex--;
			if (m_CurrentButtonIndex < 0)
			{
				m_CurrentButtonIndex = BUTTON_COUNT - 1;
			}
			m_UIManager->SelectMainMenuButton(m_ButtonOrder[m_CurrentButtonIndex]);
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
			}
			else if (m_ButtonOrder[m_CurrentButtonIndex] == MainMenuButtonType::Quit)
			{
				m_OnQuitButtonClick();
				m_IsAnyButtonClick = true;
			}
			return;
		}
	}
	void MainMenuStateController::resetState()
	{
		m_CurrentButtonIndex = -1;
		m_CanSelectButtons = false;
		m_IsAnyButtonClick = false;
	}
	void MainMenuStateController::Tick(float deltaTime)
	{
	}
	void MainMenuStateController::Start()
	{
	}
}
