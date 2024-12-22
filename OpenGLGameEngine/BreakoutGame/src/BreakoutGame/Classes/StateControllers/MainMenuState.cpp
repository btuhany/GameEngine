#include "MainMenuState.h"

namespace BreakoutGame
{
	const int BUTTON_COUNT = 3;
	MainMenuState::MainMenuState(std::shared_ptr<UIManager> uiManager)
	{
		m_IsHelpPanelActive = false;
		m_UIManager = uiManager;
	}
	void MainMenuState::SetCallbacks(std::function<void()> startButtonClickHandler, std::function<void()> quitButtonClickHandler)
	{
		m_OnStartButtonClick = startButtonClickHandler;
		m_OnQuitButtonClick = quitButtonClickHandler;
	}
	void MainMenuState::HandleOnActivated()
	{
		resetState();
		m_UIManager->ShowMainMenuPanel();
	}
	void MainMenuState::HandleOnDeactivated()
	{
		resetState();
		m_UIManager->HideMainMenuPanel();;
	}
	void MainMenuState::HandleInputs(InputType inputType)
	{
		if (m_IsHelpPanelActive)
		{
			if (inputType == InputType::EnterKey_Release)
			{
				handleHelpPanel();
			}
			return;
		}

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
				handleHelpPanel();
			}
			else if (m_ButtonOrder[m_CurrentButtonIndex] == MainMenuButtonType::Quit)
			{
				m_OnQuitButtonClick();
				m_IsAnyButtonClick = true;
			}
			return;
		}
	}
	void MainMenuState::resetState()
	{
		m_CurrentButtonIndex = -1;
		m_CanSelectButtons = false;
		m_IsAnyButtonClick = false;
	}
	void MainMenuState::Tick(float deltaTime)
	{
	}
	void MainMenuState::handleHelpPanel()
	{
		if (m_IsHelpPanelActive)
		{
			m_IsHelpPanelActive = false;
			hideHelpPanel();
		}
		else
		{
			m_IsHelpPanelActive = true;
			openHelpPanel();
		}
	}
	void MainMenuState::openHelpPanel()
	{
		m_UIManager->HideMainMenuPanel();
		m_UIManager->ShowHelpPanel();
	}
	void MainMenuState::hideHelpPanel()
	{
		m_UIManager->HideHelpPanel();
		m_UIManager->ShowMainMenuPanel();
		m_UIManager->SelectMainMenuButton(MainMenuButtonType::Help);
	}
	void MainMenuState::Start()
	{
	}
}
