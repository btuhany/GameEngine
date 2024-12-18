#pragma once
#include <unordered_map>
#include <memory>
#include "../Data/BallHitBrickData.h"
#include "../Data/GameStateEnum.h"
#include "../Controllers/InputController.h"
#include "../Controllers/MainMenuController.h"
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
		std::shared_ptr<InputController> GetController();
		void ActivateStateController();
	private:
		GameState m_CurrentGameState;


		void onMainMenuStartButtonClick();
		void onMainMenuQuitButtonClick();
		std::unordered_map<GameState, std::shared_ptr<InputController>> m_StateControllerMap;


		//PLAYER DATA
		int m_ScorePoint;
		int m_PlayerLives;
	};
}


