#pragma once
#include <GameEngine.h>
#include "../Data/BallHitBrickData.h"
#include "../Data/GameStateEnum.h"
#include "../StateControllers/MainMenuStateController.h"
namespace BreakoutGame
{
	class GameManager
	{
	public:
		void Initialize(std::shared_ptr<UIManager> uiManager);
		void Start();
		int GetScorePoint();
		int GetPlayerLive();
		void ProcessBallHitBrickData(BallHitBrickData hitData);
		GameState GetGameState();
		std::shared_ptr<StateController> GetController();
	private:
		GameState m_CurrentGameState;

		void changeGameState(GameState newState);
		void onMainMenuStartButtonClick();
		void onMainMenuQuitButtonClick();
		std::unordered_map<GameState, std::shared_ptr<StateController>> m_StateControllerMap;


		//PLAYER DATA
		int m_ScorePoint;
		int m_PlayerLives;
	};
}


