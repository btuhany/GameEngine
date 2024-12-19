#pragma once
#include <functional>
#include "StateController.h"
#include "../Data/MainMenuButtonType.h"
#include "../Managers/UIManager.h"
namespace BreakoutGame
{
	class MainMenuStateController : public StateController
	{	
	public:
		MainMenuStateController(
			std::shared_ptr<UIManager> uiManager);
		void SetCallbacks(std::function<void()> startButtonClickHandler,
			std::function<void()> quitButtonClickHandler);
		void HandleOnActivated() override;
		void HandleOnDeactivated() override;
		void HandleInputs(InputType inputType) override;
	private:
		void resetState();
		std::shared_ptr<UIManager> m_UIManager;
		std::function<void()> m_OnStartButtonClick;
		std::function<void()> m_OnHelpButtonClick;
		std::function<void()> m_OnQuitButtonClick;
		bool m_CanSelectButtons = false;
		int m_CurrentButtonIndex;
		static const int BUTTON_COUNT = 3;
		bool m_IsAnyButtonClick = false;
		const MainMenuButtonType m_ButtonOrder[BUTTON_COUNT] = {
			MainMenuButtonType::Start,
			MainMenuButtonType::Help,
			MainMenuButtonType::Quit,
		};
		bool m_IsHelpPanelActive = false;
		void Tick(float deltaTime) override;
		void handleHelpPanel();
		void openHelpPanel();
		void hideHelpPanel();
		// Inherited via StateController
		void Start() override;
	};
}

