#pragma once
#include <GameEngine.h>
#include "IEntityProvider.h"
#include "../Objects/UIButton.h"
#include "../Data/MainMenuButtonType.h"
namespace BreakoutGame
{
	class UIManager : public IEntityProvider
	{
	public:
		void Initialize(float viewPortWidth, float viewPortHeight, int initalScore, int initialLevel, int maxPlayerLive);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
		void Start();

		void ShowPlayerHUD();
		void UpdatePlayerHUDScorePoint(int scorePoint);
		void UpdatePlayerHUDLevel(int level);
		void UpdatePlayerHUDLive(int live);
		void HidePlayerHUD();

		void ShowPausePanel();
		void HidePausePanel();

		void ShowHelpPanel();
		void HideHelpPanel();

		void ShowMainMenuPanel();
		void UpdateMainMenuStartButtonText(std::string text);
		void HideMainMenuPanel();

		void ShowLevelCompletedPanel();
		void HideLevelCompletedPanel();

		void SelectMainMenuButton(MainMenuButtonType buttonType);
	private:
		void initScoreText(std::string initialScoreStr);
		void startScoreText();
		void initLevelText(std::string initialLevelStr);
		void startLevelText();
		void initHeartSpriteEntities(int liveCount);
		void startHeartSpriteEntities();
		void initMainMenuPanelObjects();
		void startMainMenuPanelObjects();
		void initPausePanelObjects();
		void startPausePanelObjects();
		void initLevelCompletedObjects();
		void startLevelCompletedObjects();

		float m_ViewPortWidth, m_ViewPortHeight;
		std::shared_ptr<Shader> m_TextShader;
		std::shared_ptr<Shader> m_UIScreenSpaceShader;
		std::vector<std::shared_ptr<GameEntity>> m_GameEntityList;

		std::shared_ptr<UITextRendererComponent> m_ScoreCounterTextComponent;
		std::shared_ptr<UITextRendererComponent> m_LevelTextComponent;
		std::vector<std::shared_ptr<GameEntity>> m_HeartSpriteEntities;

		std::shared_ptr<UITextRendererComponent> m_PauseText;

		std::shared_ptr<UITextRendererComponent> m_BreakoutCongratsText;

		std::shared_ptr<UITextRendererComponent> m_BreakoutText;
		std::shared_ptr<UIButton> m_StartButton;
		std::shared_ptr<UIButton> m_HelpButton;
		std::shared_ptr<UIButton> m_QuitButton;
		const float MARGIN_TOP = 50.0f;
		const float MARGIN_LEFT = 50.0f;
		const float MARGIN_RIGHT = 50.0f;
	};
}

