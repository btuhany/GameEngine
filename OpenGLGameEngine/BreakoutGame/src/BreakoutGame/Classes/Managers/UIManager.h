#pragma once
#include <GameEngine.h>
#include "IEntityProvider.h"
#include "../Objects/UIButton.h"
namespace BreakoutGame
{
	class UIManager : public IEntityProvider
	{
	public:
		void Initialize(float viewPortWidth, float viewPortHeight, int initalScore, int initialLevel, int maxPlayerLive);
		void SetScorePoint(int scorePoint);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
		void Start();
		void ShowPlayerHUD(int playerLiveCount);
		void HidePlayerHUD();

		void ShowMainMenuPanel();
		void HideMainMenuPanel();
	private:
		void initScoreText(std::string initialScoreStr);
		void startScoreText();
		void initLevelText(std::string initialLevelStr);
		void startLevelText();
		void initHeartSpriteEntities(int liveCount);
		void startHeartSpriteEntities();
		void initMainMenuPanelObjects();
		void startMainMenuPanelObjects();

		float m_ViewPortWidth, m_ViewPortHeight;
		std::shared_ptr<Shader> m_TextShader;
		std::shared_ptr<Shader> m_UIScreenSpaceShader;
		std::vector<std::shared_ptr<GameEntity>> m_GameEntityList;

		std::shared_ptr<UITextRendererComponent> m_ScoreCounterTextComponent;
		std::shared_ptr<UITextRendererComponent> m_LevelTextComponent;
		std::vector<std::shared_ptr<GameEntity>> m_HeartSpriteEntities;

		std::shared_ptr<UITextRendererComponent> m_BreakoutText;
		std::shared_ptr<UIButton> m_StartButton;
		std::shared_ptr<UIButton> m_QuitButton;
		const float MARGIN_TOP = 50.0f;
		const float MARGIN_LEFT = 50.0f;
		const float MARGIN_RIGHT = 50.0f;
	};
}

