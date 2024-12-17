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
		void Initialize();
		void Start();
		int GetScorePoint();
		int GetPlayerLive();
		void ProcessBallHitBrickData(BallHitBrickData hitData);
		GameState GetGameState();
		std::shared_ptr<InputController> GetCurrentInputController();
	private:
		void onStartButtonClick();
		void onQuitButtonClick();
		void onHelpButtonClick();
		GameState m_CurrentGameState;
		std::unordered_map<GameState, std::shared_ptr<InputController>> m_StateControllerMap;
		//PLAYER DATA
		int m_ScorePoint;
		int m_PlayerLives;
	};
}


