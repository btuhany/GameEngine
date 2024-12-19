#pragma once
#include <GameEngine.h>
#include "StateController.h"
#include "../Objects/Ball.h"
#include "../Objects/Paddle.h"
#include "../Managers/BrickManager.h"
#include "../Managers/UIManager.h"
#include "../Managers/PlayerDataManager.h"
#include "../Data/LevelBrickGridData.h"
namespace BreakoutGame
{
	class InGameStateController : public StateController
	{
	public:
		void Initialize(std::shared_ptr<Shader> mainShader, std::shared_ptr<UIManager> uiManager);
		void Start() override;
		void Tick(float deltaTime) override;
		std::vector<std::shared_ptr<GameEntity>> GetEntities();
		void HandleOnDeactivated() override;
		void HandleOnActivated() override;
		void HandleInputs(InputType inputType) override;
	private:
		std::shared_ptr<PlayerDataManager> m_PlayerDataManager;
		bool m_IsGamePaused = false;
		void onPause();
		void startGame();
		void onLevelInitializationCompleted();
		void initLevel(int level);
		void onThereIsNoBrickLeft();
		void onBallColliderEnter(std::shared_ptr<GameEntity> gameEntity);
		std::shared_ptr<Ball> m_Ball;
		std::shared_ptr<Paddle> m_Paddle;
		std::shared_ptr<BrickManager> m_BrickManager;
		std::shared_ptr<UIManager> m_UIManager;


		bool m_InLevelCompletedDelay;
		float m_LevelCompletedDelayTimeCounter = 0.0f;
		const float DELAY_BETWEEN_LEVELS = 2.5f;
	};
}

